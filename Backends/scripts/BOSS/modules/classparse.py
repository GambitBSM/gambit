############################
#                          #
#  Class parsing for BOSS  #
#                          #
############################

from __future__ import print_function
from collections import OrderedDict
import os

import modules.active_cfg as active_cfg
exec("import configs." + active_cfg.module_name + " as cfg")
import modules.gb as gb
import modules.utils as utils
import modules.classutils as classutils
import modules.funcutils as funcutils
import modules.infomsg as infomsg

#
# Module-level globals
#

template_done   = []
templ_spec_done = []
added_parent    = []

includes = OrderedDict()


# ====== run ========

# Main function for parsing classes

def run():

    # Clear the module-level dict that keeps track of include statements
    includes.clear()

    #
    # Loop over all classes 
    #
    
    for class_name_long, class_el in gb.loaded_classes_in_xml.items():

        # Clear all info messages
        infomsg.clearInfoMessages()

        # Generate dicts with different variations of the class name
        class_name       = classutils.getClassNameDict(class_el)
        abstr_class_name = classutils.getClassNameDict(class_el, abstract=True)

        # Print current class
        print()
        print('  ' + utils.modifyText('Class:','underline') + ' ' + class_name['long_templ'])

        # Check if this is a template class
        is_template = utils.isTemplateClass(class_el)


        # Make list of all types used in this class
        all_types_in_class = utils.getAllTypesInClass(class_el, include_parents=True)

        # Set a bunch of generally useful variables 
        original_class_file_el   = gb.id_dict[class_el.get('file')]
        original_file_name       = original_class_file_el.get('name')
        original_file_name_base  = os.path.basename(original_file_name)
        original_class_file_dir  = os.path.split(original_file_name)[0]
        extras_src_file_name     = os.path.join(gb.boss_output_dir, gb.general_src_file_prefix + class_name['short'] + cfg.source_extension)

        short_abstr_class_fname  = gb.new_header_files[class_name['long']]['abstract']
        abstr_class_fname        = os.path.join(gb.boss_output_dir, short_abstr_class_fname)

        # namespaces    = class_name['long'].split('::')[:-1]
        namespaces    = utils.getNamespaces(class_el, include_self=False)
        has_namespace = bool(len(namespaces))

        has_copy_constructor, copy_constructor_id         = classutils.checkCopyConstructor(class_el, return_id=True)
        has_assignment_operator, assignment_is_artificial = classutils.checkAssignmentOperator(class_el)
        
        if has_assignment_operator and assignment_is_artificial:
            construct_assignment_operator = True
        else:
            construct_assignment_operator = False


        # Register paths of original files in global dict
        gb.original_file_paths[original_file_name_base] = original_file_name


        # Read content of original class file
        f = open(original_file_name, 'r')
        original_file_content = f.read()
        f.close()
        original_file_content_nocomments = utils.removeComments(original_file_content, insert_blanks=True)


        # Prepare entries in gb.new_code and includes
        if abstr_class_fname not in gb.new_code.keys():
            gb.new_code[abstr_class_fname] = {'code_tuples':[], 'add_include_guard':True}
            gb.new_code[abstr_class_fname + '.FOR_GAMBIT'] = {'code_tuples':[], 'add_include_guard':True}
        if original_file_name not in gb.new_code.keys():
            gb.new_code[original_file_name] = {'code_tuples':[], 'add_include_guard':False}
        if original_file_name not in includes.keys():
            includes[original_file_name] = []
        if extras_src_file_name not in gb.new_code.keys():
            gb.new_code[extras_src_file_name] = {'code_tuples':[], 'add_include_guard':False}


        # Treat the first specialization of a template class differently
        if is_template and class_name['long'] not in template_done:
            template_bracket, template_types = utils.getTemplateBracket(class_el)
            
            empty_templ_class_decl = ''
            empty_templ_class_decl += classutils.constrEmptyTemplClassDecl(abstr_class_name['short'], namespaces, template_bracket, indent=cfg.indent)
            empty_templ_class_decl += classutils.constrTemplForwDecl(class_name['short'], namespaces, template_bracket, indent=cfg.indent)

            gb.new_code[abstr_class_fname]['code_tuples'].append( (0, empty_templ_class_decl) )


        # Get template arguments for specialization, 
        # and check that they are acceptable
        if is_template and class_name['long'] not in templ_spec_done:
            spec_template_types = utils.getSpecTemplateTypes(class_el)
            for template_type in spec_template_types:
                if (template_type not in gb.accepted_types):
                    raise Exception("The template specialization type '" + template_type + "' for class " + class_name['long'] + " is not among accepted types.")


        #
        # For the backend: Construct code for the abstract class header file and register it
        #
        
        constrAbstractClassHeaderCode(class_el, class_name, abstr_class_name, namespaces, is_template, 
                                      has_copy_constructor, construct_assignment_operator, abstr_class_fname, file_for_gambit=False)

        #
        # For GAMBIT: Construct code for the abstract class header file and register it
        #
        
        constrAbstractClassHeaderCode(class_el, class_name, abstr_class_name, namespaces, is_template, 
                                      has_copy_constructor, construct_assignment_operator, abstr_class_fname, file_for_gambit=True)



        #
        # Add abstract class to inheritance list of original class
        #

        addAbsClassToInheritanceList(class_el, class_name, abstr_class_name, is_template,
                                     original_file_name, original_file_content_nocomments)
        

        #
        # Generate code for #include statements in orginal header/source file 
        #

        addIncludesToOriginalClassFile(class_el, namespaces, is_template, original_file_name, 
                                       original_file_content_nocomments, original_file_content,
                                       short_abstr_class_fname)



        #
        # Generate additional member functions in the original class:
        # - Abstract class versions of member functions that make use of loaded types.
        # - Extra versions of functions that use default value arguments.
        # - Functions for returning references to public member variables. 
        # Declarations go in the original class header while implementations go in a separate source file.
        #

        generateClassMemberInterface(class_el, class_name, abstr_class_name, namespaces,
                                     original_file_name, original_file_content_nocomments, 
                                     original_class_file_el, extras_src_file_name)
        

        #
        # Generate factory functions source file
        #

        generateFactoryFunctions(class_el, class_name, is_template)


        #
        # Generate a header containing the GAMBIT wrapper class
        #

        generateWrapperHeader(class_el, class_name, abstr_class_name, namespaces, short_abstr_class_fname,
                              construct_assignment_operator, has_copy_constructor, copy_constructor_id)


        #
        # Construct utility functions for dealing with pointer-to-wrapper from Abstract class.
        # ('wrapper_creator', 'wrapper_deleter', 'set_delete_BEptr')
        #

        constrWrapperUtils(class_name)


        #
        # Add typedef to 'abstracttypedefs.hpp'
        #

        addAbstractTypedefs(abstr_class_name, namespaces)


        #
        # Add typedef to 'wrappertypdefs.hpp'
        #

        addWrapperTypedefs(class_name, namespaces)


        #
        # Add include guards to the original headers
        #
        gb.new_code[original_file_name]['add_include_guard'] = True
        gb.new_code[original_file_name]['include_guard_prefix'] = 'boss'

        #
        # Keep track of classes done
        #

        gb.classes_done.append(class_name)
        if is_template: 
            if class_name['long'] not in template_done:
                template_done.append(class_name['long'])
            if class_name['long'] not in templ_spec_done:
                templ_spec_done.append(class_name['long'])
        

        print()

    #
    # END: Loop over all classes in gb.loaded_classes_in_xml
    #    

# ====== END: run ========



# ====== constrAbstractClassHeaderCode ========

# Construct code for the abstract class header file and register it

def constrAbstractClassHeaderCode(class_el, class_name, abstr_class_name, namespaces, is_template,
                                  has_copy_constructor, construct_assignment_operator, abstr_class_fname, file_for_gambit=False):

    if file_for_gambit:
        abstr_class_fname = abstr_class_fname + '.FOR_GAMBIT'

    class_decl = ''

    # Add include statements
    include_statements  = []
    include_statements += ['#include "' + os.path.join(gb.gambit_backend_incl_dir, 'abstractbase.hpp') + '"']
    include_statements += ['#include "' + gb.frwd_decls_abs_fname + cfg.header_extension + '"']
    include_statements += ['#include "' + gb.frwd_decls_wrp_fname + cfg.header_extension + '"']
    include_statements += utils.getIncludeStatements(class_el, convert_loaded_to='wrapper_decl', exclude_types=[class_name], include_parents=True, use_full_path=False, forward_declared='include')
    include_statements += ['#include <cstddef>']
    if gb.debug_mode or file_for_gambit: 
        include_statements += ['#include <iostream>']
    include_statements_code = '\n'.join(include_statements) + 2*'\n'
    class_decl += include_statements_code

    # # Add include statement for the enum declaration header. Put this inside a #ifndef ... #endif block
    # # to avoid multiple declaration when the abstract class header is included from the original class header. 
    # enum_include_statement_code  = ''
    # enum_include_statement_code += '#ifndef ENUMS_DECLARED\n'
    # enum_include_statement_code += '#define ENUMS_DECLARED\n'
    # enum_include_statement_code += '#include "' + gb.enum_decls_wrp_fname + cfg.header_extension + '"\n'
    # # enum_include_statement_code += '#include "' + os.path.join(gb.backend_types_basedir, gb.gambit_backend_name_full, gb.enum_decls_wrp_fname + cfg.header_extension) + '"\n'
    # enum_include_statement_code += '#endif\n'
    # enum_include_statement_code += '\n'
    # class_decl += enum_include_statement_code

    # Add the the code for the abstract class
    if (is_template == True) and (class_name['long'] in templ_spec_done):
        pass
    elif (is_template == True) and (class_name['long'] not in templ_spec_done):
        class_decl += classutils.constrAbstractClassDecl(class_el, class_name, abstr_class_name, namespaces, 
                                                         indent=cfg.indent, file_for_gambit=file_for_gambit, 
                                                         template_types=spec_template_types, construct_assignment_operator=construct_assignment_operator)
        class_decl += '\n'
    else:
        class_decl += classutils.constrAbstractClassDecl(class_el, class_name, abstr_class_name, namespaces, 
                                                         indent=cfg.indent, file_for_gambit=file_for_gambit,
                                                         construct_assignment_operator=construct_assignment_operator)
        class_decl += '\n'

    # - Register code
    gb.new_code[abstr_class_fname]['code_tuples'].append( (-1, class_decl) )

# ====== END: constrAbstractClassHeaderCode ========



# ====== addAbsClassToInheritanceList ========

# Add abstract class to inheritance list of original class

def addAbsClassToInheritanceList(class_el, class_name, abstr_class_name, is_template,
                                 original_file_name, original_file_content_nocomments):

    # Find positions in the original file
    line_number    = int(class_el.get('line'))
    class_name_pos = classutils.findClassNamePosition(class_el, original_file_content_nocomments)
    newline_pos    = utils.findNewLinePos(original_file_content_nocomments, line_number)


    # Special preparations for template classes:
    if is_template:
    
        # - Determine whether this is the source for the general template 
        #   or for a specialization (look for '<' after class name)
        temp_pos = class_name_pos + len(class_name['short'])
        while True:
            next_char = original_file_content_nocomments[temp_pos]
            if next_char not in [' ', '\t', '\n']:
                break
            else:
                temp_pos += 1
        if next_char == '<':
            src_is_specialization = True
        else:
            src_is_specialization = False

        # - Prepare the template bracket string
        if src_is_specialization:
            add_template_bracket = '<' + ','.join(spec_template_types) + '>'
        else:
            add_template_bracket = '<' + ','.join(template_types) + '>'


    # If no previous parent classes:
    if ('bases' not in class_el.keys()) and (class_name['long'] not in added_parent):

        # - Calculate insert position
        insert_pos = class_name_pos + len(class_name['short'])
        if is_template and src_is_specialization:
            insert_pos += len(add_template_bracket)

        # - Generate code
        add_code = ' : public virtual ' + abstr_class_name['short']
        if is_template == True:
            add_code += add_template_bracket

    # If there are previous parent classes
    else:

        # - Get colon position
        if is_template and src_is_specialization:
            temp_pos = class_name_pos + len(class_name['short']) + len(add_template_bracket)
        else:
            temp_pos = class_name_pos + len(class_name['short'])
        colon_pos = temp_pos + original_file_content_nocomments[temp_pos:newline_pos].find(':')

        # - Calculate insert position
        insert_pos = colon_pos + 1

        # - Generate code
        add_code = ' public virtual ' + abstr_class_name['short']
        if is_template == True:
            add_code += add_template_bracket
        add_code += ','

    # - Register new code
    gb.new_code[original_file_name]['code_tuples'].append( (insert_pos, add_code) )

    # - Update added_parent dict
    added_parent.append(class_name['long'])

# ====== END: addAbsClassToInheritanceList ========



# ====== addIncludesToOriginalClassFile ========

# Generate code for #include statements in orginal header/source file

def addIncludesToOriginalClassFile(class_el, namespaces, is_template, original_file_name, 
                                   original_file_content_nocomments, original_file_content,
                                   short_abstr_class_fname):

    # Generate include statement for abstract class header
    include_line = '#include "' + os.path.join(gb.backend_types_basedir, gb.gambit_backend_name_full, short_abstr_class_fname ) + '"'

    # Check that we haven't included that statement already
    if include_line in includes[original_file_name]:
        return

    # Check for namespace
    has_namespace = bool(len(namespaces))

    # Find class name position in the original file
    class_name_pos = classutils.findClassNamePosition(class_el, original_file_content_nocomments)


    # Find insert position
    if is_template == True:
        insert_pos = original_file_content_nocomments[:class_name_pos].rfind('template')
    else:
        insert_pos = max(original_file_content_nocomments[:class_name_pos].rfind('class'), original_file_content_nocomments[:class_name_pos].rfind('struct'))
    # - Adjust for the indentation
    use_indent = ''
    while insert_pos > 0:
        char = original_file_content[insert_pos-1]
        if char in [' ','\t']:
            use_indent += char
            insert_pos -= 1
        else:
            break

    # Construct code
    include_code = ''
    include_code += use_indent

    for ns in namespaces:
        include_code += '} '

    include_code += '\n'*has_namespace
    include_code += use_indent + '#define ENUMS_DECLARED\n'
    include_code += use_indent + include_line + '\n'
    include_code += use_indent + '#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.abstract_typedefs_fname + cfg.header_extension) +  '"\n'
    include_code += use_indent + '#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.wrapper_typedefs_fname + cfg.header_extension) +  '"\n'
    include_code += use_indent

    for ns in namespaces:
        include_code += 'namespace ' + ns + ' { '

    include_code += '\n'*has_namespace

    # Register code
    gb.new_code[original_file_name]['code_tuples'].append( (insert_pos, include_code) )

    # Register include line
    includes[original_file_name].append(include_line)

# ====== END: addIncludesToOriginalClassFile ========



# ====== generateClassMemberInterface ========

# Generate additional member functions in the original class:
# - Abstract class versions of member functions that make use of loaded types.
# - Extra versions of functions that use default value arguments.
# - Functions for returning references to public member variables. 
# Declarations go in the original class header while implementations go in a separate source file.
    
def generateClassMemberInterface(class_el, class_name, abstr_class_name, namespaces,
                                 original_file_name, original_file_content_nocomments,
                                 original_class_file_el, extras_src_file_name):

    # Find class name position in the original file
    class_name_pos = classutils.findClassNamePosition(class_el, original_file_content_nocomments)

    # Create lists of all public, 'non-artificial' members of the class
    member_methods   = []
    member_variables = []
    member_operators = []
    if 'members' in class_el.keys():
        for mem_id in class_el.get('members').split():
            el = gb.id_dict[mem_id]
            if not 'artificial' in el.keys():
                if el.get('access') == 'public':
                    if (el.tag == 'Method'): # and (not funcutils.ignoreFunction(el)):
                        member_methods.append(el)
                    elif (el.tag == 'OperatorMethod'): #and (not funcutils.ignoreFunction(el)):
                        if funcutils.usesNativeType(el):
                            member_operators.append(el)
                    elif (el.tag in ('Field', 'Variable')):
                        if classutils.isAcceptedMemberVariable(el):
                            member_variables.append(el)

    # Determine insert position
    rel_pos_start, rel_pos_end = utils.getBracketPositions(original_file_content_nocomments[class_name_pos:], delims=['{','}'])
    class_body_start = class_name_pos + rel_pos_start
    class_body_end   = class_name_pos + rel_pos_end
    insert_pos = class_body_end

    # Generate code for wrapper functions for each each member function.
    # A declaration goes into the original class header, 
    # while implementations are put in a new source file.

    declaration_code     = '\n'
    implementation_code  = '\n'
    current_access = None
    for method_el in member_methods:

        # We need to generate as many overloaded versions as there are arguments with default values
        n_overloads = funcutils.numberOfDefaultArgs(method_el)
        
        # Check for native types
        uses_native_type = funcutils.usesNativeType(method_el)

        # If no native types are used and no arguments have default values, we don't need a wrapper
        if (not uses_native_type) and (n_overloads == 0):
            continue

        # Generate wrapper code
        for remove_n_args in range(n_overloads+1):
            
            # Check that function is acceptable
            if funcutils.ignoreFunction(method_el, remove_n_args=remove_n_args):
                continue

            if (remove_n_args==0) and (not uses_native_type):
                continue

            # The declaration is put inside the original class
            method_access = method_el.get('access')
            if method_access != current_access:
                declaration_code += ' '*(len(namespaces)+1)*cfg.indent + method_access +':\n'
                current_access = method_access
            declaration_code += classutils.constrWrapperFunction(method_el, indent=cfg.indent, n_indents=len(namespaces)+2, 
                                                                 remove_n_args=remove_n_args, only_declaration=True)
            declaration_code += '\n'

            
            # The implementation goes into a new source file
            implementation_code += classutils.constrWrapperFunction(method_el, indent=cfg.indent, n_indents=0, 
                                                                    remove_n_args=remove_n_args, include_full_namespace=True)
            implementation_code += 2*'\n'

    # - Register code
    gb.new_code[original_file_name]['code_tuples'].append( (insert_pos, declaration_code) )            
    gb.new_code[extras_src_file_name]['code_tuples'].append( (-1, implementation_code) )            


    # Generate code for each member operator
    operator_declaration_code    = '\n'
    operator_implementation_code = '\n'
    for operator_el in member_operators:
        operator_access = operator_el.get('access')
        if operator_access != current_access:
            operator_declaration_code += ' '*(len(namespaces)+1)*cfg.indent + operator_access +':\n'
            current_access = operator_access

        # If default arguments are used, we need several overloads
        n_overloads = funcutils.numberOfDefaultArgs(operator_el)
        for remove_n_args in range(n_overloads+1):

            # Put declaration in original class
            operator_declaration_code += classutils.constrWrapperFunction(operator_el, indent=cfg.indent, n_indents=len(namespaces)+2, 
                                                                          remove_n_args=remove_n_args, only_declaration=True)
            operator_declaration_code += '\n'


            # Put implementation in a new source file
            operator_implementation_code += classutils.constrWrapperFunction(operator_el, indent=cfg.indent, n_indents=0, 
                                                                             remove_n_args=remove_n_args, include_full_namespace=True)
            operator_implementation_code += 2*'\n'


    # - Register code
    gb.new_code[original_file_name]['code_tuples'].append( (insert_pos, operator_declaration_code) )            
    gb.new_code[extras_src_file_name]['code_tuples'].append( (-1, operator_implementation_code) )            


    # Generate a reference-returning method for each (public) member variable:
    ref_func_declaration_code    = ''
    ref_func_implementation_code = ''
    if len(member_variables) > 0:
        n_indents = len(namespaces)
        ref_func_declaration_code += '\n'
        ref_func_declaration_code += ' '*cfg.indent*(n_indents+1) + 'public:\n'
        for var_el in member_variables:

            # Put declaration in original code
            ref_func_declaration_code += classutils.constrVariableRefFunction(var_el, virtual=False, indent=cfg.indent, n_indents=n_indents+2, 
                                                                              only_declaration=True, add_return_type_suffix=True)
            ref_func_declaration_code += '\n'

            # Put implementation in a new source file
            ref_func_implementation_code += classutils.constrVariableRefFunction(var_el, virtual=False, indent=cfg.indent, n_indents=0,
                                                                                 include_full_namespace=True, add_return_type_suffix=True) 
            ref_func_implementation_code += '\n'


    # - Register code
    if ref_func_declaration_code != '':
        gb.new_code[original_file_name]['code_tuples'].append( (insert_pos, ref_func_declaration_code) )            
        gb.new_code[extras_src_file_name]['code_tuples'].append( (-1, ref_func_implementation_code) )            



    # Generate pointer-based copy and assignment functions

    # If class contains pure virtual members, do not generate any factory functions
    if class_name['long_templ'] in gb.contains_pure_virtual_members:
        reason = "Contains pure virtual member functions."
        infomsg.NoPointerCopyAndAssignmentFunctions(class_name['long_templ'], reason).printMessage()
    else:

        n_indents = len(namespaces)
        ptr_declaration_code = '\n'
        ptr_implementation_code = '\n'

        ptr_declaration_code += ' '*cfg.indent*(n_indents+1) + 'public:\n'
        ptr_declaration_code += classutils.constrPtrCopyFunc(class_el, abstr_class_name['short'], class_name['short'], virtual=False, indent=cfg.indent, n_indents=n_indents+2, only_declaration=True)
        ptr_declaration_code += '\n'

        ptr_declaration_code += ' '*cfg.indent*(n_indents+2) + 'using ' + abstr_class_name['short'] + '::pointer_assign' + gb.code_suffix + ';\n'
        ptr_declaration_code += classutils.constrPtrAssignFunc(class_el, abstr_class_name['short'], class_name['short'], virtual=False, indent=cfg.indent, n_indents=n_indents+2, only_declaration=True)
        
        ptr_implementation_code += '#include "' + os.path.join(gb.backend_types_basedir, gb.gambit_backend_name_full,'identification.hpp') + '"\n'
        ptr_implementation_code += '\n'
        ptr_implementation_code += classutils.constrPtrCopyFunc(class_el, abstr_class_name['short'], class_name['short'], virtual=False, indent=cfg.indent, n_indents=0, include_full_namespace=True)
        ptr_implementation_code += '\n'
        ptr_implementation_code += classutils.constrPtrAssignFunc(class_el, abstr_class_name['short'], class_name['short'], virtual=False, indent=cfg.indent, n_indents=0, include_full_namespace=True)
        ptr_implementation_code += '\n'
        ptr_implementation_code += '#include "' + os.path.join(gb.gambit_backend_incl_dir, 'backend_undefs.hpp') + '"\n'

        # - Generate include statements for the new source file
        include_statements = []
        include_statements += utils.getIncludeStatements(class_el, convert_loaded_to='none', input_element='class', use_full_path=True, forward_declared='only')
        include_statements += utils.getIncludeStatements(class_el, convert_loaded_to='wrapper', input_element='class', use_full_path=True, forward_declared='exclude')
        include_statements.append('#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.abstract_typedefs_fname + cfg.header_extension) + '"')
        include_statements.append('#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.wrapper_typedefs_fname + cfg.header_extension) + '"')

        if utils.isHeader(original_class_file_el):
            use_path = utils.shortenHeaderPath(original_file_name)
            include_statements.append( '#include "' + use_path + '"')

        include_statements = list( OrderedDict.fromkeys(include_statements) )
        include_statements_code = '\n'.join(include_statements) + '\n'

        # - Register the code
        gb.new_code[original_file_name]['code_tuples'].append( (insert_pos, ptr_declaration_code) )

        gb.new_code[extras_src_file_name]['code_tuples'].append( (0, include_statements_code) )            
        gb.new_code[extras_src_file_name]['code_tuples'].append( (-1, ptr_implementation_code) )


# ====== END: generateClassMemberInterface ========



# ====== generateFactoryFunctions ========

# Generate factory functions source file

def generateFactoryFunctions(class_el, class_name, is_template):

    # If class contains pure virtual members, do not generate any factory functions
    if class_name['long_templ'] in gb.contains_pure_virtual_members:
        reason = "Contains pure virtual member functions."
        infomsg.NoFactoryFunctions(class_name['long_templ'], reason).printMessage()
        return 

    # Generate factory file content
    factory_file_content  = ''

    if is_template:
        spec_template_types = utils.getSpecTemplateTypes(class_el)
        factory_file_content += classutils.constrFactoryFunctionCode(class_el, class_name, indent=cfg.indent, template_types=spec_template_types, skip_copy_constructors=True, use_wrapper_return=False, use_wrapper_args=True)
    else:
        factory_file_content += classutils.constrFactoryFunctionCode(class_el, class_name, indent=cfg.indent, skip_copy_constructors=True, use_wrapper_return=False, use_wrapper_args=True)
    factory_file_content += '\n'

    # If no file content has been generated (no public constructors), return without doing anything
    if factory_file_content.strip() == '':
        return

    # Generate factory file name
    dir_name = gb.boss_output_dir
    factory_file_name = os.path.join(dir_name, gb.factory_file_prefix + class_name['short'] + cfg.source_extension)

    # Register code
    if factory_file_name not in gb.new_code.keys():
        gb.new_code[factory_file_name] = {'code_tuples':[], 'add_include_guard':False}
    gb.new_code[factory_file_name]['code_tuples'].append( (-1, factory_file_content) )

    # Register that this class has a factory file
    gb.class_factory_file_dict[class_name['long_templ']] = factory_file_name

# ====== END: generateFactoryFunctions ========



# ====== generateWrapperHeader ========

# Generate a header containing the GAMBIT wrapper class

def generateWrapperHeader(class_el, class_name, abstr_class_name, namespaces, short_abstr_class_fname,
                          construct_assignment_operator, has_copy_constructor, copy_constructor_id):

    # Set file names and paths
    wrapper_decl_header_fname = gb.new_header_files[class_name['long']]['wrapper_decl']
    wrapper_def_header_fname  = gb.new_header_files[class_name['long']]['wrapper_def']
    wrapper_header_fname      = gb.new_header_files[class_name['long']]['wrapper']

    wrapper_decl_header_path = os.path.join(gb.boss_output_dir, wrapper_decl_header_fname)
    wrapper_def_header_path  = os.path.join(gb.boss_output_dir, wrapper_def_header_fname)
    wrapper_header_path      = os.path.join(gb.boss_output_dir, wrapper_header_fname)
    
    # Get code for the declaration and implementation headers
    wrapper_decl_header_content, wrapper_def_header_content = classutils.generateWrapperHeaderCode(class_el, class_name, abstr_class_name,
                                                                                                   namespaces, short_abstr_class_fname, 
                                                                                                   construct_assignment_operator, has_copy_constructor,
                                                                                                   copy_constructor_id=copy_constructor_id)

    # Code for the overall header file
    wrapper_decl_header_include_path = gb.new_header_files[class_name['long']]['wrapper_decl']
    wrapper_def_header_include_path  = gb.new_header_files[class_name['long']]['wrapper_def']
    wrapper_header_content  = '\n'
    wrapper_header_content += '#include "' + wrapper_decl_header_include_path + '"\n'
    wrapper_header_content += '#include "' + wrapper_def_header_include_path + '"\n'
    wrapper_header_content += '\n'


    # Register code
    if wrapper_decl_header_path not in gb.new_code.keys():
        gb.new_code[wrapper_decl_header_path] = {'code_tuples':[], 'add_include_guard':True}
    gb.new_code[wrapper_decl_header_path]['code_tuples'].append( (0, wrapper_decl_header_content) )

    if wrapper_def_header_path not in gb.new_code.keys():
        gb.new_code[wrapper_def_header_path] = {'code_tuples':[], 'add_include_guard':True}
    gb.new_code[wrapper_def_header_path]['code_tuples'].append( (0, wrapper_def_header_content) )

    if wrapper_header_path not in gb.new_code.keys():
        gb.new_code[wrapper_header_path] = {'code_tuples':[], 'add_include_guard':True}
    gb.new_code[wrapper_header_path]['code_tuples'].append( (0, wrapper_header_content) )

# ====== END: generateWrapperHeader ========


# ====== constrWrapperUtils ========

# Construct functions for dealing with wrapper pointer from abstract class 
# ('wrapper_creator', 'wrapper_deleter', 'set_delete_BEptr')

def constrWrapperUtils(class_name):

    wrapper_class_name = classutils.toWrapperType(class_name['long'], include_namespace=True)
    abstr_class_name = classutils.toAbstractType(class_name['long'], include_namespace=True)

    # Include statement for the header file
    wrapper_include_statement_decl = '#include "' + gb.new_header_files[class_name['long']]['wrapper_fullpath'] + '"\n'

    wr_utils_decl = ''
    wr_utils_impl = ''


    #
    # wrapper_creator
    #

    # Function declaration
    wr_utils_decl  = '\n'
    wr_utils_decl += wrapper_class_name + '* wrapper_creator(' + abstr_class_name + '*);\n'

    # Function implementation
    wr_utils_impl  = '\n'
    wr_utils_impl += wrapper_class_name + '* wrapper_creator(' + abstr_class_name + '* abs_ptr)\n'
    wr_utils_impl += '{\n'
    wr_utils_impl += ' '*cfg.indent + 'return new ' + wrapper_class_name + '(abs_ptr);\n'
    wr_utils_impl += '}\n'

    # #
    # # wrapper_creator
    # #

    # # Function declaration
    # wr_utils_decl  = '\n'
    # wr_utils_decl += 'void wrapper_creator(' + abstr_class_name + '*);\n'

    # # Function implementation
    # wr_utils_impl  = '\n'
    # wr_utils_impl += 'void wrapper_creator(' + abstr_class_name + '* abs_ptr)\n'
    # wr_utils_impl += '{\n'
    # wr_utils_impl += ' '*cfg.indent + 'abs_ptr->set_wptr( new ' + wrapper_class_name + '(abs_ptr) );\n'
    # wr_utils_impl += '}\n'


    #
    # wrapper_deleter
    #

    # Function declaration
    wr_utils_decl += '\n'
    wr_utils_decl += 'void wrapper_deleter(' + wrapper_class_name + '*);\n'

    # Function implementation
    wr_utils_impl += '\n'
    wr_utils_impl += 'void wrapper_deleter(' + wrapper_class_name + '* wptr)\n'
    wr_utils_impl += '{\n'
    wr_utils_impl += ' '*cfg.indent + 'wptr->set_delete_BEptr(false);\n'
    wr_utils_impl += ' '*cfg.indent + 'delete wptr;\n'
    wr_utils_impl += '}\n'


    #
    # set_delete_BEptr
    #

    # Function declaration
    wr_utils_decl += '\n'
    wr_utils_decl += 'void set_delete_BEptr(' + wrapper_class_name + '*, bool);\n'

    # Function implementation
    wr_utils_impl += '\n'
    wr_utils_impl += 'void set_delete_BEptr(' + wrapper_class_name + '* wptr, bool setting)\n'
    wr_utils_impl += '{\n'
    wr_utils_impl += ' '*cfg.indent + 'wptr->set_delete_BEptr(setting);\n'
    wr_utils_impl += '}\n'


    # Register code
    w_creator_header_path = os.path.join(gb.boss_output_dir, gb.wrapper_utils_fname + cfg.header_extension)
    w_creator_source_path = os.path.join(gb.boss_output_dir, gb.wrapper_utils_fname + cfg.source_extension)

    if w_creator_header_path not in gb.new_code.keys():
        gb.new_code[w_creator_header_path] = {'code_tuples':[], 'add_include_guard':True}

        gb.new_code[w_creator_header_path]['code_tuples'].append( (0, '#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.wrapper_typedefs_fname + cfg.header_extension) + '"\n') )
        gb.new_code[w_creator_header_path]['code_tuples'].append( (0, '#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.abstract_typedefs_fname + cfg.header_extension) + '"\n') )

    gb.new_code[w_creator_header_path]['code_tuples'].append( (0, wrapper_include_statement_decl) )        
    gb.new_code[w_creator_header_path]['code_tuples'].append( (-1, wr_utils_decl) )        

    if w_creator_source_path not in gb.new_code.keys():
        w_creator_include = '#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.wrapper_utils_fname + cfg.header_extension) + '"\n'
        gb.new_code[w_creator_source_path] = {'code_tuples':[(0,w_creator_include)], 'add_include_guard':False}
    gb.new_code[w_creator_source_path]['code_tuples'].append( (-1, wr_utils_impl) )        

# ====== END: constrWrapperUtils ========




# ====== addAbstractTypedefs ========

# Add typedef to 'abstracttypedefs.hpp'

def addAbstractTypedefs(abstr_class_name, namespaces):

    indent = ' '*cfg.indent*len(namespaces)
    abstr_typedef_code  = ''
    abstr_typedef_code += utils.constrNamespace(namespaces, 'open', indent=cfg.indent)

    temp_namespace_list = [gb.gambit_backend_namespace] + namespaces
    abstr_typedef_code += indent + 'typedef ' + '::'.join(temp_namespace_list) + '::' + abstr_class_name['short'] + ' ' + abstr_class_name['short'] + ';\n'

    abstr_typedef_code += utils.constrNamespace(namespaces, 'close', indent=cfg.indent)
    abstr_typedef_code += '\n'

    frw_decl_include_statement       = '#include "' + os.path.join(gb.backend_types_basedir, gb.gambit_backend_name_full, gb.frwd_decls_abs_fname + cfg.header_extension) + '"\n'
    identification_include_statement = '#include "' + os.path.join(gb.backend_types_basedir, gb.gambit_backend_name_full, 'identification.hpp') + '"\n\n'
    undef_include_statement          = '#include "' + os.path.join(gb.gambit_backend_incl_dir, 'backend_undefs.hpp') + '"\n'

    abstracts_typedefs_header_path = os.path.join(gb.boss_output_dir, gb.abstract_typedefs_fname + cfg.header_extension)
    if abstracts_typedefs_header_path not in gb.new_code.keys():
        gb.new_code[abstracts_typedefs_header_path] = {'code_tuples':[], 'add_include_guard':False}

        gb.new_code[abstracts_typedefs_header_path]['code_tuples'].append( (0,  frw_decl_include_statement) ) 
        gb.new_code[abstracts_typedefs_header_path]['code_tuples'].append( (len(frw_decl_include_statement), identification_include_statement) ) 
        gb.new_code[abstracts_typedefs_header_path]['code_tuples'].append( (-1, undef_include_statement) ) 

    gb.new_code[abstracts_typedefs_header_path]['code_tuples'].append( (-len(undef_include_statement), abstr_typedef_code) )

# ====== END: addAbstractTypedefs ========



# ====== addWrapperTypedefs ========

# Add typedef to 'wrappertypdefs.hpp'

def addWrapperTypedefs(class_name, namespaces):

    short_wrapper_class_name = classutils.toWrapperType(class_name['short'])

    indent = ' '*cfg.indent*len(namespaces)

    wrapper_typedef_code  = ''
    wrapper_typedef_code += utils.constrNamespace(namespaces,'open')

    temp_namespace_list = [gb.gambit_backend_namespace] + namespaces
    wrapper_typedef_code += indent + 'typedef ' + '::'.join(temp_namespace_list) + '::' + class_name['short'] + ' ' + short_wrapper_class_name + ';\n'

    wrapper_typedef_code += utils.constrNamespace(namespaces,'close')
    wrapper_typedef_code += '\n'

    frw_decl_include_statement       = '#include "' + os.path.join(gb.backend_types_basedir, gb.gambit_backend_name_full, gb.frwd_decls_wrp_fname + cfg.header_extension) + '"\n'
    identification_include_statement = '#include "' + os.path.join(gb.backend_types_basedir, gb.gambit_backend_name_full, 'identification.hpp') + '"\n\n'
    undef_include_statement          = '#include "' + os.path.join(gb.gambit_backend_incl_dir, 'backend_undefs.hpp') + '"\n'

    wrapper_typedefs_path = os.path.join(gb.boss_output_dir, gb.wrapper_typedefs_fname + cfg.header_extension)

    if wrapper_typedefs_path not in gb.new_code.keys():
        gb.new_code[wrapper_typedefs_path] = {'code_tuples':[], 'add_include_guard':False}

        gb.new_code[wrapper_typedefs_path]['code_tuples'].append( (0,  frw_decl_include_statement) ) 
        gb.new_code[wrapper_typedefs_path]['code_tuples'].append( (len(frw_decl_include_statement), identification_include_statement) ) 
        gb.new_code[wrapper_typedefs_path]['code_tuples'].append( (-1, undef_include_statement) ) 

    gb.new_code[wrapper_typedefs_path]['code_tuples'].append( (-len(undef_include_statement), wrapper_typedef_code) )

# ====== END: addWrapperTypedefs ========

