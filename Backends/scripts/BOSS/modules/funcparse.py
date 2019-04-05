###############################
#                             #
#  Function parsing for BOSS  #
#                             #
###############################

from __future__ import print_function
from collections import OrderedDict
import os

import modules.active_cfg as active_cfg
exec("import configs." + active_cfg.module_name + " as cfg")

import modules.gb as gb
import modules.utils as utils
import modules.funcutils as funcutils
import modules.classutils as classutils
import modules.infomsg as infomsg


#
# Module-level globals
#



# ====== run ========

# Main function for parsing functions

def run():


    #
    # Loop over all functions 
    #
    
    for func_name_full, func_el in gb.func_dict.items():

        # Clear all info messages
        infomsg.clearInfoMessages()

        # Number of functions done
        func_i = len(gb.functions_done)

        # Generate dict with different variations of the function name
        func_name = funcutils.getFunctionNameDict(func_el)


        # Print current function
        print()
        print('  ' + utils.modifyText('Function:','underline') + ' ' + func_name['long_templ_args'])


        # Check if this function is accepted
        if funcutils.ignoreFunction(func_el):
            continue
       
        # Function namespace
        namespaces = utils.getNamespaces(func_el)
        has_namespace = bool(len(namespaces))


        # Check if this is a template function
        is_template = utils.isTemplateFunction(func_el)


        # If template function, figure out template variables
        if is_template == True:
            template_bracket, template_types = utils.getTemplateBracket(func_el)
            spec_template_types = utils.getSpecTemplateTypes(func_el)
            print('TEMPLATE: ', template_bracket, template_types, spec_template_types)


        #
        # Generate extra source file with overloaded and wrapper class versions
        #

        # Construct a wrapper function name, eg "someFunction__BOSS_7"
        wr_func_name = func_el.get('name') + gb.code_suffix + '_' + str(gb.symbol_name_counter)
        gb.symbol_name_counter += 1

        # New source file name
        new_source_file_name = gb.function_files_prefix + func_el.get('name') + cfg.source_extension
        new_source_file_path = os.path.join(gb.boss_output_dir, new_source_file_name)

        # Get include statements
        include_statements = []

        # - Generate include statements based on the types used in the function
        include_statements += utils.getIncludeStatements(func_el, convert_loaded_to='none', input_element='function')
        include_statements += utils.getIncludeStatements(func_el, convert_loaded_to='wrapper', input_element='function', use_full_path=True)
        include_statements.append( '#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.abstract_typedefs_fname + cfg.header_extension) + '"' )
        include_statements.append( '#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.wrapper_typedefs_fname + cfg.header_extension) + '"' )
        
        # - Then check if we have a header file for the function in question.
        #   If not, declare the original function as 'extern'
        file_el = gb.id_dict[func_el.get('file')]
        has_function_header = utils.isHeader(file_el)
        if has_function_header:
            header_full_path = file_el.get('name')
            use_path = utils.shortenHeaderPath(header_full_path)
            include_statements.append( '#include "' + use_path + '"')

        # Add include statement for gambit/Backends/function_return_utils.hpp
        include_statements.append( '#include "' + os.path.join(gb.gambit_backend_incl_dir,'function_return_utils.hpp') + '"')

        include_statements = list( OrderedDict.fromkeys(include_statements) )
        include_statements_code = '\n'.join(include_statements) + 2*'\n'


        # If no header file is found for the original function, generate 'extern' declaration
        extern_declaration = ''
        if not has_function_header:
            extern_declaration += funcutils.constrExternFuncDecl(func_el)
            extern_declaration += '\n'


        # If we have access to the function header, we can implement one overloaded versions
        # to account for default value arguments.
        if has_function_header:
            n_overloads = funcutils.numberOfDefaultArgs(func_el)
        else:
            n_overloads = 0


        #
        # Generate code for wrapper class version
        #
        
        # # Register the wrapper name
        # func_name['wr_name'] = wr_func_name

        # Construct wrapper function code
        wrapper_code = generateFunctionWrapperClassVersion(func_el, wr_func_name, namespaces, n_overloads) 
        wrapper_code = utils.addIndentation(wrapper_code, len(namespaces)*cfg.indent)
        wrapper_code += '\n'


        # Prepare element in gb.new_code
        if new_source_file_path not in gb.new_code.keys():
            gb.new_code[new_source_file_path] = {'code_tuples':[], 'add_include_guard':False}

        # Define code string
        n_indents = len(namespaces)
        new_code  = 2*'\n'

        # - Add include statements
        new_code += include_statements_code

        # - Add extern function declaration
        new_code += extern_declaration

        # - Construct the beginning of the namespaces
        new_code += utils.constrNamespace(namespaces, 'open')

        # - Add code for 'wrapper' version
        new_code += wrapper_code

        # - Construct the closing of the namespaces
        new_code += utils.constrNamespace(namespaces, 'close')
        
        new_code += '\n'


        # Register new code in return_code_dict
        insert_pos = -1   # end of file
        # return_code_dict[new_source_file_path]['code_tuples'].append( (insert_pos, new_code) )
        gb.new_code[new_source_file_path]['code_tuples'].append( (insert_pos, new_code) )


        # Register that this function has a source file
        gb.function_file_dict[func_name['long_templ_args']] = new_source_file_path


        #
        # Keep track of functions done
        #
        gb.functions_done.append(func_name)
        gb.wr_func_names.append(wr_func_name)

        print()

    #
    # End loop over functions
    #

# ====== END: run ========




# ====== generateFunctionWrapperClassVersion ========

# Function for generating a source file containing wrapper
# functions that make use of the wrapper classes.

def generateFunctionWrapperClassVersion(func_el, wr_func_name, namespaces, n_overloads):

    new_code = ''

    # Check if this function makes use of any loaded types
    uses_loaded_type = funcutils.usesLoadedType(func_el)

    # Function name
    func_name = func_el.get('name')

    # Determine return type
    return_type_dict = utils.findType(func_el)
    return_el      = return_type_dict['el']
    pointerness    = return_type_dict['pointerness']
    is_ref         = return_type_dict['is_reference']
    return_type_kw = return_type_dict['cv_qualifiers']
    
    return_kw_str  = ' '.join(return_type_kw) + ' '*bool(len(return_type_kw))
    
    return_is_loaded    = utils.isLoadedClass(return_el)

    return_type   = return_type_dict['name'] + '*'*pointerness + '&'*is_ref

    # If return type is a known class, add '::' for absolute namespace.
    if (not return_is_loaded) and utils.isKnownClass(return_el):
        return_type = '::' + return_type 


    # If return-by-value, then a const qualifier on the return value is meaningless
    # (will result in a compiler warning)
    if (pointerness == 0) and (is_ref == False):
        if 'const' in return_type_kw:
            return_type_kw.remove('const')


    # Arguments
    args = funcutils.getArgs(func_el)


    # One function for each set of default arguments
    n_overloads = funcutils.numberOfDefaultArgs(func_el)
    for remove_n_args in range(n_overloads+1):

        # Check that the function is acceptable
        if funcutils.ignoreFunction(func_el, limit_pointerness=True, remove_n_args=remove_n_args):
            continue

        if remove_n_args == 0:
            use_args = args
        else:
            use_args = args[:-remove_n_args]

        # Argument bracket
        args_bracket = funcutils.constrArgsBracket(use_args, include_arg_name=True, include_arg_type=True, include_namespace=True, use_wrapper_class=True)

        # Name of original function to call
        call_func_name = func_name

        # Convert return type if loaded class
        if utils.isLoadedClass(return_el):
            wrapper_return_type = classutils.toWrapperType(return_type, remove_reference=True)
        else:
            wrapper_return_type = return_type

        # Write declaration line
        new_code += return_kw_str + wrapper_return_type + ' ' + wr_func_name + args_bracket + '\n'

        # Write function body
        indent = ' '*cfg.indent
        new_code += '{\n'

        if return_type == 'void':
            new_code += indent
        else:
            new_code += indent + 'return '

        # args_bracket_notypes = funcutils.constrArgsBracket(use_args, include_arg_name=True, include_arg_type=False, wrapper_to_pointer=True)
        args_bracket_notypes = funcutils.constrArgsBracket(use_args, include_arg_name=True, include_arg_type=False, cast_to_original=True, wrapper_to_pointer=True)

        if return_is_loaded: 

            abs_return_type_simple = classutils.toAbstractType(return_type, include_namespace=True, remove_reference=True, remove_pointers=True)
            wrapper_return_type_simple = wrapper_return_type.replace('*','').replace('&','')

            if is_ref:  # Return-by-reference
                new_code += 'reference_returner< ' + wrapper_return_type_simple + ', ' + abs_return_type_simple +  ' >( ' + call_func_name + args_bracket_notypes + ' );\n'

            elif (not is_ref) and (pointerness > 0):  # Return-by-pointer
                new_code += 'pointer_returner< ' + wrapper_return_type_simple + ', ' + abs_return_type_simple +  ' >( ' + call_func_name + args_bracket_notypes + ' );\n'
            
            else:  # Return-by-value
                new_code += wrapper_return_type + '( ' + call_func_name + args_bracket_notypes + ' );\n'
        
        else:                
            new_code += call_func_name + args_bracket_notypes + ';\n'

        new_code += '}\n'
        new_code += '\n'

    # Add 'extern "C" {...}' block
    new_code = 'extern "C"\n{\n' + new_code + '}\n'

    return new_code

# ====== END: generateFunctionWrapperClassVersion ========



