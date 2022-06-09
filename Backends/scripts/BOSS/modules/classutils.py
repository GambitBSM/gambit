####################################
#                                  #
#  Utility functions for handling  #
#  C++ classes with BOSS           #
#                                  #
####################################

from __future__ import print_function
from inspect import getargs
from operator import is_
import re
from collections import OrderedDict
import os
import modules.gb as gb
import modules.funcutils as funcutils
import modules.utils as utils
import modules.exceptions as exceptions
import modules.infomsg as infomsg


# import modules.cfg as cfg
import modules.active_cfg as active_cfg
exec("import configs." + active_cfg.module_name + " as cfg")


# ====== isLoadable ========

def isLoadable(class_el, print_warning=False, check_pure_virtual_members=True):
    # - Any loadable class should have a "name" XML entry
    if not 'name' in class_el.keys():
        return False

    class_name = utils.getClassNameDict(class_el)

    # - Check if class should be ditched. If yes, return right away.
    if class_name['long_templ'] in cfg.ditch:
        return False

    # - Check that class is complete (not only forward declared).
    if not utils.isComplete(class_el):
        if print_warning:
            reason = "Class is incomplete, at least based on XML file {0}".format(gb.xml_file_name)
            infomsg.ClassNotLoadable(class_name['long_templ'], reason).printMessage()
        return False

    # - Check that class has at least one public constructor.
    constructor_elements = getAcceptableConstructors(class_el, skip_copy_constructors=True)
    if not constructor_elements:
        if print_warning:
            reason = "No (acceptable) public constructors identified."
            infomsg.ClassNotLoadable(class_name['long_templ'], reason).printMessage()
        return False

    # - Check for pure virtual members.
    if check_pure_virtual_members:
        pure_virtual_members = pureVirtualMembers(class_el)
        if pure_virtual_members:
            gb.contains_pure_virtual_members.append(class_name['long_templ'])

    return True

# ====== END: isLoadable ========


# ====== getMemberFunctions ========

def getMemberFunctions(class_el, include_artificial=False, include_inherited=False, only_accepted=True, limit_pointerness=True, include_operators=False):
    all_classes = [class_el]
    all_members = []
    all_functions = []

    # If include_inherited=True, append all (native) parent classes
    # the list 'all_classes'
    if include_inherited:
        all_classes += utils.getAllParentClasses(class_el, only_loaded_classes=True)

    # Get all member elements
    for el in all_classes:
        all_members += utils.getMemberElements(el, include_artificial=include_artificial)

    # Extract only regular member functions (no variables, constructors, destructors, ...)
    for mem_el in all_members:
        if (mem_el.tag == 'Method' or (include_operators and mem_el.tag == 'OperatorMethod')) and (mem_el.get('access') == 'public'):

            if only_accepted and funcutils.ignoreFunction(mem_el, limit_pointerness=limit_pointerness):
                method_name = mem_el.get('name')
                if mem_el.tag == 'OperatorMethod':
                    method_name = 'operator' + method_name

                reason = "Makes use of a non-accepted type."
                infomsg.IgnoredFunction(method_name, reason).printMessage()
                continue

            all_functions.append(mem_el)

    return all_functions

# ====== END: getMemberFunctions ========


# ====== addParentClasses ========

# Adds parent classes to cfg.load_classes.

def addParentClasses():
    for xml_file in gb.all_id_dict.keys():

        # If new xml file, initialise global dicts
        if xml_file != gb.xml_file_name:
            gb.xml_file_name = xml_file
            utils.initGlobalXMLdicts(xml_file, id_and_name_only=True)

        # Loop over all named elements in the xml file
        for full_name, el in gb.name_dict.items():
            if el.tag in ['Class', 'Struct'] and utils.isLoadedClass(el):
                parents_el_list = utils.getAllParentClasses(
                    el, only_native_classes=True)

                for parent_el in parents_el_list:

                    # Skip classes that are not loadable (incomplete, abstract, ...)
                    if not isLoadable(el, print_warning=True):
                        continue

                    class_name = utils.getClassNameDict(parent_el)

                    # - Update cfg.load_classes
                    if class_name['long_templ'] not in cfg.load_classes:
                        cfg.load_classes.append(class_name['long_templ'])

# ====== END: addParentClasses ========


# ====== fillParentsOfLoadedClassesList ========

# Adds parent classes to cfg.load_classes.

def fillParentsOfLoadedClassesList():
    messages = []

    for xml_file in gb.all_id_dict.keys():

        # If new xml file, initialise global dicts
        if xml_file != gb.xml_file_name:
            gb.xml_file_name = xml_file
            utils.initGlobalXMLdicts(xml_file, id_and_name_only=True)

        # Loop over all named elements in the xml file
        for full_name, el in gb.name_dict.items():

            if el.tag in ['Class', 'Struct'] and utils.isLoadedClass(el):

                parents_el_list = utils.getAllParentClasses(
                    el, only_native_classes=True)

                for parent_el in parents_el_list:

                    # Skip classes that are not loadable (incomplete, abstract, ...)
                    if not isLoadable(parent_el, print_warning=True, check_pure_virtual_members=False):
                        continue

                    class_name = utils.getClassNameDict(parent_el)

                    # Append to gb.parents_of_loaded_classes
                    if class_name['long_templ'] not in gb.parents_of_loaded_classes:
                        gb.parents_of_loaded_classes.append(
                            class_name['long_templ'])

                    # Print info
                    msg = '  - %s is parent of %s.' % (
                        class_name['long_templ'], full_name)
                    if msg not in messages:
                        print(msg)
                        messages.append(msg)

# ====== END: fillParentsOfLoadedClassesList ========


# ====== constrAbstractClassDecl ========

def constrAbstractClassDecl(class_el, class_name, namespaces, indent=4, file_for_gambit=False, has_copy_constructor=True, construct_assignment_operator=True, current_code=""):

    n_indents = len(namespaces)

    class_decl = current_code

    # Check template_types argument:
    if utils.isTemplateClass(class_name):
        is_template = True
        templ_bracket = class_name['templ_bracket']
        templ_vars = class_name['templ_vars']
    else:
        is_template = False


    # Create list of all 'non-artificial' members of the class
    member_elements = utils.getMemberElements(class_el, include_artificial=False)


    # Get list of dicts with info on parent classes
    parent_classes = utils.getParentClasses(class_el)


    #
    # Construct the abstract class declaration
    #

    # - Construct the beginning of the namespaces
    class_decl += utils.constrNamespace(namespaces, 'open')

    # - If this class is a template specialization, add 'template <>' at the top
    # - If this class is a full template, add template bracket
    if is_template:
        class_decl += ' '*n_indents*indent + 'template ' + templ_bracket + '\n'

    # - Construct the declaration line, with inheritance of abstract classes
    inheritance_line = ''
    for parent_dict in parent_classes:

        if parent_dict['loaded']:
            if is_template:
                inheritance_line += 'virtual ' + parent_dict['access'] + ' ' + parent_dict['class_name']['abstr_long'] + templ_vars + ', '
            else:
                inheritance_line += 'virtual ' + parent_dict['access'] + ' ' + parent_dict['class_name']['abstr_long_templ'] + ', '

        elif parent_dict['fundamental'] or parent_dict['std']:
            # inheritance_line += 'virtual ' + parent_dict['access'] + ' ' + parent_dict['class_name']['long_templ'] + ', '
            reason = 'Avoid inheritance ambiguity.'
            infomsg.ParentClassIgnored(class_name['abstr_short'], parent_dict['class_name']['long_templ'], reason).printMessage()

        else:
            reason = 'Not loaded or accepted type.'
            infomsg.ParentClassIgnored(class_name['abstr_short'], parent_dict['class_name']['long_templ'], reason).printMessage()
            continue
    inheritance_line = inheritance_line.rstrip(', ')

    # If no other parent classes, add AbstractBase
    if inheritance_line == '':
        inheritance_line = ' : public virtual AbstractBase'
    else:
        inheritance_line = ' : ' + inheritance_line



    class_decl += ' '*n_indents*indent
    class_decl += 'class ' + class_name['abstr_short'] + inheritance_line + '\n'

    # - Construct body of class declaration
    current_access = ''
    class_decl += ' '*n_indents*indent
    class_decl += '{' + '\n'
    ptr_members_for_init = []
    locally_defined_types = []

    for el in member_elements:

        # Check access
        element_access = el.get('access')

        if element_access != 'public':
            continue

        if current_access != element_access:
            class_decl += ' '*(n_indents+1)*indent
            class_decl += element_access + ':' +'\n'
            current_access = element_access

        #
        # Add code based on what element type this is
        #
        if el.tag in ('Constructor', 'Destructor'):
            pass   # (An empty virtual destructor will be added later)

        elif el.tag in ('Method', 'OperatorMethod'):

            # Check if this is an operator function
            is_operator = False
            if el.tag == 'OperatorMethod':
                is_operator = True

            # Check if this member function should be ignored.
            if funcutils.ignoreFunction(el):
                # infomsg.IgnoredMemberFunction( is_operator*'operator' + el.get('name') ).printMessage()
                continue

            # Check if this member function makes use of loaded types
            uses_loaded_type = funcutils.usesLoadedType(el)

            return_type_dict = utils.findType( gb.id_dict[el.get('returns')] )
            return_el     = return_type_dict['el']
            pointerness   = return_type_dict['pointerness']
            is_ref        = return_type_dict['is_reference']
            return_kw     = return_type_dict['cv_qualifiers']

            return_kw_str = ' '.join(return_kw) + ' '*bool(len(return_kw))
            
            if is_template:
                func_types = utils.getTemplatedMethodTypes(el, class_name)

                return_type = func_types['return']
                args = func_types['args']


            else:
                args = utils.getArgs(el)
                return_name = return_type_dict['name']
                return_type   = return_name + '*'*pointerness + '&'*is_ref
            # If any of the arg types is a locally defined type, remove all namespaces
            for arg in args:
                if utils.typeInList(arg, locally_defined_types):
                    arg_type = utils.removeNamespace(arg.get('type'))
                    arg['type'] = arg_type

            w_args = funcutils.constrWrapperArgs(args, add_ref=True)


            # If return type is a locally defined type, remove all namespaces
            if utils.typeInList(return_el, locally_defined_types) :
                return_type = utils.removeNamespace(return_type)

            return_is_loaded = utils.isLoadedClass(return_el)

            

            # If return type is a known class, add '::' for absolute namespace.
            if (not return_is_loaded) and utils.isKnownClass(return_el):
                return_type = '::' + return_type

            # Check constness
            if ('const' in el.keys() and el.get('const') == '1'):
                is_const = True
            else:
                is_const = False


            # If default arguments are used, we need to generate overloaded versions
            n_overloads = funcutils.numberOfDefaultArgs(el)

            # One overloaded version for each set of default arguments
            for remove_n_args in range(n_overloads+1):

                if remove_n_args == 0:
                    use_w_args = w_args
                else:
                    use_w_args = w_args[:-remove_n_args]


                w_args_bracket_nonames = utils.constrArgsBracket(use_w_args, include_arg_name=False, include_arg_type=True, include_namespace=True)

                if is_operator:
                    if uses_loaded_type:
                        w_func_name = 'operator_' + gb.operator_names[el.get('name')] + gb.code_suffix
                    else:
                        w_func_name = 'operator' + el.get('name')
                else:
                    if uses_loaded_type or (remove_n_args>0):
                        w_func_name = el.get('name') + gb.code_suffix
                    else:
                        w_func_name = el.get('name')

                #
                # If the method makes use of a loaded class, construct a pair of wrapper methods.
                #
                if uses_loaded_type:

                    # Construct the virtual member function that is overridden, e.g.:
                    #
                    #   virtual X* getX_GAMBIT(arguments) {}
                    #

                    if return_is_loaded:
                        if is_ref:
                            w_return_type = utils.toAbstractType(return_type, include_namespace=True)
                        elif (not is_ref) and (pointerness > 0):
                            w_return_type = utils.toAbstractType(return_type, include_namespace=True)
                        else:
                            w_return_type = utils.toAbstractType(return_type, include_namespace=True, add_pointer=True, remove_reference=True)
                    else:
                        w_return_type = return_type

                    class_decl += '\n'
                    class_decl += ' '*(n_indents+2)*indent
                    class_decl += 'virtual ' + return_kw_str + w_return_type + ' ' + w_func_name + w_args_bracket_nonames + is_const*' const' + ' =0;' + '\n'


                #
                # If the method does not make use of any loaded class, construct a single virtual method
                #
                else:
                    class_decl += '\n'
                    class_decl += ' '*(n_indents+2)*indent
                    class_decl += 'virtual ' + return_kw_str + return_type + ' ' + w_func_name + w_args_bracket_nonames + is_const*' const' + ' =0;' + '\n'


        #
        # If element is a public member variable of accepted type, construct virtual method that returns a reference to this variable
        #
        elif (el.tag in ('Field', 'Variable')) and (el.get('access') == 'public') and isAcceptedMemberVariable(el):

            class_decl += '\n'
            class_decl += constrVariableRefFunction(el, class_el, virtual=True, indent=indent, n_indents=n_indents+2)

            # For member variables that are of type pointer-to-loaded-class, create a pointer-to-wrapper-class member variable
            if utils.isLoadedClass(el):

                el_type_dict = utils.findType(el)

                pointerness = el_type_dict['pointerness']
                is_ref      = el_type_dict['is_reference']

                if (pointerness > 0) and (not is_ref):

                    # If class is templated, pull type from file
                    if is_template:
                        el_type = utils.getTemplatedMemberVariableType(el)
                    else:
                        el_type       = el_type_dict['name'] + '*'*pointerness
                    variable_name = el.get('name') + gb.code_suffix

                    class_decl += ' '*(n_indents+2)*indent + el_type + ' ' + variable_name + ';\n'

                    # Register variable name so that it can be initialized in the constructor
                    ptr_members_for_init.append(variable_name)

        #
        # If an enumeration type add this to the abstract class
        #
        elif el.tag == 'Enumeration' :
            class_decl += '\n'
            class_decl += constrEnumDecl(el, indent=indent, n_indents=n_indents+2)

            # add this to a list of locally defined types
            if not el in locally_defined_types :
                locally_defined_types.append(el)

            # mark this type for deletion in the original file
            if not el in gb.moved_to_abstract_class :
                gb.moved_to_abstract_class.append(el)

        #
        # Ignore element
        #
        else:
            pass

    # - Member functions of the abstract class living in GAMBIT should never be called. If that happens, something is very wrong.
    # general_boss_warning = 'BOSS WARNING: Problem detected with the BOSSed class %s from backend %s. The function %s::%s in GAMBIT should never have been called...'

    # - Construct 'pointer_assign' and 'pointer_copy' functions
    if class_name['long_templ'] in gb.contains_pure_virtual_members:
        reason = "Contains pure virtual member functions."
        infomsg.NoPointerCopyAndAssignmentFunctions(class_name['long_templ'], reason).printMessage()
    else:
        class_decl += '\n'
        if has_copy_constructor or construct_assignment_operator:
            class_decl += ' '*(n_indents+1)*indent + 'public:\n'
        if construct_assignment_operator:
            for parent_dict in parent_classes:
                if (parent_dict['loaded']) and (parent_dict['class_name']['long_templ'] not in gb.contains_pure_virtual_members):
                    if is_template:
                        class_decl += ' '*(n_indents+2)*indent + 'using ' + parent_dict['class_name']['abstr_long'] + templ_vars + '::pointer_assign' + gb.code_suffix + ';\n'
                    else:
                        class_decl += ' '*(n_indents+2)*indent + 'using ' + parent_dict['class_name']['abstr_long_templ'] + '::pointer_assign' + gb.code_suffix + ';\n'
            class_decl += constrPtrAssignFunc(class_el, class_name, virtual=True, indent=indent, n_indents=n_indents+2, only_declaration=True)
        if has_copy_constructor:
            class_decl += constrPtrCopyFunc(class_el, class_name, virtual=True, indent=indent, n_indents=n_indents+2, only_declaration=True)

    # - Construct code needed for 'destructor pattern' (abstract class and wrapper class must can delete each other)
    class_decl += '\n'
    class_decl += ' '*(n_indents+1)*indent + 'private:\n'
    # Wrapper class needs to be templated
    wrapper_class_name = class_name['wrp_short']
    if is_template:
        wrapper_class_name += templ_vars

    class_decl +=  ' '*(n_indents+2)*indent +  wrapper_class_name

    class_decl += '* wptr;\n'
    class_decl += ' '*(n_indents+2)*indent + 'bool delete_wrapper;\n'
    class_decl += ' '*(n_indents+1)*indent + 'public:\n'
    class_decl += ' '*(n_indents+2)*indent + wrapper_class_name
    class_decl += '* get_wptr() { return wptr; }\n'
    class_decl += ' '*(n_indents+2)*indent + 'void set_wptr(' + wrapper_class_name
    class_decl += '* wptr_in) { wptr = wptr_in; }\n'
    class_decl += ' '*(n_indents+2)*indent + 'bool get_delete_wrapper() { return delete_wrapper; }\n'
    class_decl += ' '*(n_indents+2)*indent + 'void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }\n'


    # - Constructor
    class_decl += '\n'
    class_decl += ' '*(n_indents+1)*indent + 'public:\n'
    class_decl += ' '*(n_indents+2)*indent + class_name['abstr_short'] + '()\n'
    class_decl += ' '*(n_indents+2)*indent + '{\n'
    if gb.debug_mode:
        class_decl += ' '*(n_indents+3)*indent + 'std::cerr << "DEBUG: " << this << " ' + class_name['abstr_short'] + ' ctor" << std::endl;\n'
    class_decl += ' '*(n_indents+3)*indent + 'wptr = 0;\n'
    class_decl += ' '*(n_indents+3)*indent + 'delete_wrapper = false;\n'
    class_decl += ' '*(n_indents+2)*indent + '}\n'


    # - Copy constructor
    # -- Construct code for calling copy constructors of *all* parent classes.
    #    (Required because this is the copy ctor of an abstract base class.)
    all_parent_classes = utils.getAllParentClasses(class_el, only_loaded_classes=True, return_dicts=True, reverse_order=True)
    parent_cctors_line = ''
    for parent_dict in all_parent_classes:
        if parent_dict['loaded']:
            if is_template:
                parent_cctors_line += parent_dict['class_name']['abstr_long'] + class_name['templ_vars'] + '(in), '
            else:
                parent_cctors_line += parent_dict['class_name']['abstr_long_templ'] + '(in), '
        elif parent_dict['fundamental'] or parent_dict['std']:
            reason = 'Avoid inheritance ambiguity.'
            infomsg.ParentClassIgnored(class_name['abstr_short'], parent_dict['class_name']['long_templ'], reason).printMessage()
        else:
            reason = 'Not loaded or accepted type.'
            infomsg.ParentClassIgnored(class_name['abstr_short'], parent_dict['class_name']['long_templ'], reason).printMessage()
            continue
    parent_cctors_line = parent_cctors_line.rstrip(', ')

    class_decl += '\n'
    if parent_cctors_line == '':
        class_decl += ' '*(n_indents+2)*indent + class_name['abstr_short'] + '(const ' + class_name['abstr_short'] + '&)\n'
    else:
        parent_cctors_line = parent_cctors_line.rstrip(',\n') + '\n'
        class_decl += ' '*(n_indents+2)*indent + class_name['abstr_short'] + '(const ' + class_name['abstr_short'] + '& in) : \n'
        class_decl += ' '*(n_indents+3)*indent + parent_cctors_line
    class_decl += ' '*(n_indents+2)*indent + '{\n'
    if gb.debug_mode:
        class_decl += ' '*(n_indents+3)*indent + 'std::cerr << "DEBUG: " << this << " ' + class_name['abstr_short'] + ' copy ctor" << std::endl;\n'
    class_decl += ' '*(n_indents+3)*indent + 'wptr = 0;\n'
    class_decl += ' '*(n_indents+3)*indent + 'delete_wrapper = false;\n'
    class_decl += ' '*(n_indents+2)*indent + '}\n'


    # - Assignment operator. (Actually, no copying should be done. It only returns *this.)
    class_decl += '\n'
    class_decl += ' '*(n_indents+2)*indent + class_name['abstr_short'] + '& operator=(const ' + class_name['abstr_short'] + '&) { return *this; }\n'

    # - Function init_wrapper()
    if file_for_gambit:
        class_decl += '\n'
        class_decl += ' '*(n_indents+2)*indent + 'virtual void init_wrapper() =0;\n'
    else:
        class_decl += '\n'
        class_decl += ' '*(n_indents+2)*indent + 'virtual void init_wrapper()\n'
        class_decl += ' '*(n_indents+2)*indent + '{\n'
        class_decl += ' '*(n_indents+3)*indent + 'if (wptr == 0)\n'
        class_decl += ' '*(n_indents+3)*indent + '{\n'
        class_decl += ' '*(n_indents+4)*indent + 'wptr = wrapper_creator'
        if is_template:
            class_decl += templ_vars
        class_decl += '(this);\n'
        class_decl += ' '*(n_indents+4)*indent + 'delete_wrapper = true;\n'
        class_decl += ' '*(n_indents+3)*indent + '}\n'
        class_decl += ' '*(n_indents+2)*indent + '}\n'


    # - Function get_init_wptr()
    class_decl += '\n'
    class_decl += ' '*(n_indents+2)*indent + wrapper_class_name
    class_decl += '* get_init_wptr()\n'
    class_decl += ' '*(n_indents+2)*indent + '{\n'
    class_decl += ' '*(n_indents+3)*indent + 'init_wrapper();\n'
    class_decl += ' '*(n_indents+3)*indent + 'return wptr;\n'
    class_decl += ' '*(n_indents+2)*indent + '}\n'

    # - Function get_init_wref()
    class_decl += '\n'
    class_decl += ' '*(n_indents+2)*indent + wrapper_class_name
    class_decl += '& get_init_wref()\n'
    class_decl += ' '*(n_indents+2)*indent + '{\n'
    class_decl += ' '*(n_indents+3)*indent + 'init_wrapper();\n'
    class_decl += ' '*(n_indents+3)*indent + 'return *wptr;\n'
    class_decl += ' '*(n_indents+2)*indent + '}\n'

    # - Destructor
    if file_for_gambit:
        class_decl += '\n'
        class_decl += ' '*(n_indents+2)*indent + 'virtual ~' + class_name['abstr_short'] + '() =0;\n'
    else:
        class_decl += '\n'
        class_decl += ' '*(n_indents+2)*indent + 'virtual ~' + class_name['abstr_short'] + '()\n'
        class_decl += ' '*(n_indents+2)*indent + '{\n'
        if gb.debug_mode:
            class_decl += ' '*(n_indents+3)*indent + 'std::cerr << "DEBUG: " << this << " ' + class_name['abstr_short'] + ' dtor (BEGIN)" << std::endl;\n'
        class_decl += ' '*(n_indents+3)*indent + 'if (wptr != 0)\n'
        class_decl += ' '*(n_indents+3)*indent + '{\n'
        class_decl += ' '*(n_indents+4)*indent + 'set_delete_BEptr'
        if is_template:
            class_decl += templ_vars
        class_decl += '(wptr, false);\n'
        class_decl += ' '*(n_indents+4)*indent + 'if (delete_wrapper == true)\n'
        class_decl += ' '*(n_indents+4)*indent + '{\n'
        class_decl += ' '*(n_indents+5)*indent + 'wrapper_deleter'
        if is_template:
            class_decl += templ_vars
        class_decl += '(wptr);\n'
        class_decl += ' '*(n_indents+5)*indent + 'wptr = 0;\n'
        # Set wptr = 0 in all parent classes as well
        for parent_dict in all_parent_classes:
            if parent_dict['loaded']:
                if is_template:
                    class_decl += ' '*(n_indents+5)*indent + parent_dict['class_name']['abstr_long'] + templ_vars + '::set_wptr(0);\n'
                else:
                    class_decl += ' '*(n_indents+5)*indent + parent_dict['class_name']['abstr_long_templ'] + '::set_wptr(0);\n'

        class_decl += ' '*(n_indents+5)*indent + 'delete_wrapper = false;\n'
        class_decl += ' '*(n_indents+4)*indent + '}\n'
        class_decl += ' '*(n_indents+3)*indent + '}\n'
        if gb.debug_mode:
            class_decl += ' '*(n_indents+3)*indent + 'std::cerr << "DEBUG: " << this << " ' + class_name['abstr_short'] + ' dtor (END)" << std::endl;\n'
        class_decl += ' '*(n_indents+2)*indent + '}\n'


    # - Close the class body
    class_decl += ' '*n_indents*indent + '};' + '\n'

    # - Construct the closing of the namespaces
    class_decl += utils.constrNamespace(namespaces, 'close')


    # Insert tags for the GAMBIT namespace
    class_decl = '\n__START_GAMBIT_NAMESPACE__\n\n' + class_decl + '\n__END_GAMBIT_NAMESPACE__\n'


    # - Add forward declaration of wrapper_creator function (needed by the 'destructor pattern')
    if not file_for_gambit:
        class_decl = forwardDeclGenerator(class_el, class_name) + class_decl


    # Insert include statements needed by GAMBIT
    backend_undef_incl_statement  = '#include "' + os.path.join(gb.gambit_backend_incl_dir, 'backend_undefs.hpp') + '"\n'
    identification_incl_statement = '#include "' + 'identification.hpp' + '"\n'

    class_decl = identification_incl_statement + class_decl + '\n' + backend_undef_incl_statement


    return class_decl

# ====== END: constrAbstractClassDecl ========


# ====== forwardDeclGenerator ========

def forwardDeclGenerator(class_el, class_name):

    is_template = utils.isTemplateClass(class_name)

    # Add the declaration for the wrapper_creator
    if is_template:
        frwd_decl_creator = 'template '+class_name['templ_bracket']+'\n'+gb.gambit_backend_namespace+'::'+class_name['wrp_long']+class_name['templ_vars']+'* wrapper_creator'
        frwd_decl_creator += '('+gb.gambit_backend_namespace+'::'+class_name['abstr_long']+class_name['templ_vars']+'*);\n'
    else :
        frwd_decl_creator = gb.gambit_backend_namespace+'::'+class_name['wrp_long']+'* wrapper_creator('+gb.gambit_backend_namespace+'::'+class_name['abstr_long']+'*);\n'
    frwd_decl_creator += '\n'



    # Add the declaration for the wrapper_deleter
    if is_template:
        frwd_decl_deleter = 'template '+class_name['templ_bracket']+'\nvoid wrapper_deleter'
        frwd_decl_deleter += '('+gb.gambit_backend_namespace+'::'+class_name['wrp_long']+class_name['templ_vars']+'*);\n'
    else :
        frwd_decl_deleter = 'void wrapper_deleter('+gb.gambit_backend_namespace+'::'+class_name['wrp_long']+'*);\n'
    frwd_decl_deleter += '\n'



    # Add the declaration for set_delete_BEptr
    if is_template:
        frwd_decl_setdel = 'template '+class_name['templ_bracket']+'\nvoid set_delete_BEptr'
        frwd_decl_setdel += '('+gb.gambit_backend_namespace+'::'+class_name['wrp_long']+class_name['templ_vars']+'*, bool);\n'
    else :
        frwd_decl_setdel = 'void set_delete_BEptr('+gb.gambit_backend_namespace+'::'+class_name['wrp_long']+'*, bool);\n'
    frwd_decl_setdel += '\n'

    # Return all 3
    return frwd_decl_setdel + frwd_decl_deleter + frwd_decl_creator

# ====== END: forwardDeclGenerator ========

# ====== getAcceptableConstructors ========

def getAcceptableConstructors(class_el, skip_copy_constructors=False):

    # Check for copy constructor?
    if skip_copy_constructors:
        has_copy_constructor, copy_constr_id = checkCopyConstructor(class_el, return_id=True)

    # Create list of all acceptable constructors of the class
    constructor_elements = []
    if 'members' in class_el.keys():
        for mem_id in class_el.get('members').split():
            el = gb.id_dict[mem_id]
            if el.tag == 'Constructor': #and ('artificial' not in el.keys()):  #(el.get('explicit') == "1"):
                if skip_copy_constructors and (el.get('id') == copy_constr_id):
                    pass
                else:
                    constructor_elements.append(el)

    return constructor_elements

# ====== END: getAcceptableConstructors ========



# ====== constrFactoryFunctionCode ========

def constrFactoryFunctionCode(class_el, class_name, indent=4, template_types=[], skip_copy_constructors=False, use_wrapper_return=False, use_wrapper_args=False, add_include_statements=True, add_signatures_comment=True):

    # Replace '*' and '&' in list of template types
    is_template = utils.isTemplateClass(class_name)
    if is_template:
      template_types = [e.replace('*','P').replace('&','R') for e in class_name['templ_types']]

    constructor_elements = getAcceptableConstructors(class_el, skip_copy_constructors=skip_copy_constructors)


    # If no public constructors are found, return nothing
    if len(constructor_elements) == 0:
        reason = "No public constructors."
        infomsg.NoFactoryFunctions(class_name['long_templ'], reason).printMessage()
        return ''

    # List to hold include statements that are generated based on the types used
    # in the constructors
    if add_include_statements:
        include_statements = []

    # Construct factory function definition(s)
    func_def = ''

    counter = 0
    for el in constructor_elements:
        if (el.tag == 'Constructor') and ((el.get('access') == 'protected') or (el.get('access') == 'private')):
            continue

        if add_include_statements:
            # - Generate include statements based on the types used in the constructor
            include_statements += utils.getIncludeStatements(el, convert_loaded_to='none', input_element='function', forward_declared='exclude')
            include_statements += utils.getIncludeStatements(el, convert_loaded_to='wrapper', input_element='function', forward_declared='exclude', use_full_path=True)

        # We need to generate as many overloaded versions as there are arguments with default values
        n_overloads = funcutils.numberOfDefaultArgs(el)

        # Identify arguments
        args = utils.getArgs(el)

        # Translate argument type of loaded classes
        if use_wrapper_args:
            w_args = funcutils.constrWrapperArgs(args, add_ref=True, convert_loaded_to_abstract=False)
        else:
            w_args = funcutils.constrWrapperArgs(args, add_ref=True, convert_loaded_to_abstract=True)

        # Invent argument names if missing
        argc = 1
        for i in range(len(args)):
            if args[i]['name'] == '':
                args[i]['name'] = "arg_{0}".format(argc)
                argc += 1

        # Generate one factory function for each set of default arguments
        for remove_n_args in range(n_overloads + 1):

            # Check that the constructor is acceptable
            if funcutils.ignoreFunction(el, limit_pointerness=True, remove_n_args=remove_n_args):
                continue

            # - Factory function name
            factory_name = "Factory_{0}_{1}".format(class_name['wrp_short'],counter)
            if is_template:
                factory_name += '_' + '_'.join(template_types)
            factory_name += gb.code_suffix + '_' + str(gb.symbol_name_counter)
            gb.symbol_name_counter += 1

            if remove_n_args == 0:
                use_args   = args
                use_w_args = w_args
            else:
                use_args   = args[:-remove_n_args]
                use_w_args = w_args[:-remove_n_args]

            # Construct bracket with input arguments
            if use_wrapper_args:
                args_bracket         = utils.constrArgsBracket(use_w_args, include_namespace=True, use_wrapper_class=True)
                args_bracket_notypes = utils.constrArgsBracket(use_args, include_arg_type=False, cast_to_original=True, wrapper_to_pointer=True)
            else:
                args_bracket         = utils.constrArgsBracket(use_w_args, include_namespace=True)
                args_bracket_notypes = utils.constrArgsBracket(use_args, include_arg_type=False, cast_to_original=True)
            args_bracket_nonames = utils.constrArgsBracket(use_args, include_namespace=True, include_arg_type=True, include_arg_name=False, add_namespace_to_loaded='my_ns')

            # Generate declaration line:
            if use_wrapper_return:
                return_type = utils.toWrapperType(class_name['wrp_short_templ'], include_namespace=True)
            else:
                return_type = utils.toAbstractType(class_name['wrp_short_templ'], add_pointer=True, include_namespace=True)

            func_def += return_type + ' ' + factory_name + args_bracket + '\n'

            # Generate body
            func_def += '{' + '\n'
            if use_wrapper_return:
                func_def += indent*' ' + 'return ' + return_type + '( new ' + class_name['wrp_long_templ'] + args_bracket_notypes + ' );' + '\n'
            else:
                func_def += indent*' ' + 'return new ' + class_name['short_templ'] + args_bracket_notypes + ';' + '\n'
            func_def += '}' + 2*'\n'

            # Add info to global dict with factory function info
            info_dict = OrderedDict()
            info_dict['name']         = factory_name
            info_dict['args_bracket'] = args_bracket_nonames

            if class_name['wrp_long'] not in gb.factory_info.keys():
                gb.factory_info[class_name['wrp_long']] = []
            gb.factory_info[class_name['wrp_long']].append( info_dict )

            # Increment counter
            counter += 1


    # If no functions were generated, return nothing
    if func_def == '':
        reason = "No accepted constructors."
        infomsg.NoFactoryFunctions(class_name['long_templ'], reason).printMessage()
        return ''


    # Encapsulate code in the correct namespace
    namespaces = utils.getNamespaces(class_el)
    n_indents = len(namespaces)

    func_def_in_ns  = ''
    func_def_in_ns += utils.constrNamespace(namespaces, 'open')
    func_def_in_ns += utils.addIndentation(func_def, n_indents*cfg.indent)
    func_def_in_ns += utils.constrNamespace(namespaces, 'close')

    # Encapsulate code in 'extern "C" {...}'
    func_def_in_ns = 'extern "C"\n{\n' + func_def_in_ns + '}\n'

    return_code = func_def_in_ns

    if add_include_statements:
        try:
            original_header_fname = utils.getOriginalHeaderPath(class_el, full_path=True)
            use_path = utils.shortenHeaderPath(original_header_fname)
            include_statements.append( '#include "' + use_path + '"')

        except exceptions.ReturnError:
            reason =  "No original header file found."
            infomsg.NoIncludeStatementGenerated(class_name['long_templ'], reason).printMessage()

        include_statements.append( '#include "' + gb.new_header_files[class_name['wrp_long']]['wrapper_fullpath'] + '"' )
        include_statements.append( '#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.abstract_typedefs_fname + cfg.header_extension) + '"' )
        include_statements.append( '#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.wrapper_typedefs_fname + cfg.header_extension) + '"' )


        include_statements = list( OrderedDict.fromkeys(include_statements) )
        include_statements = utils.orderIncludeStatements(include_statements)
        include_statements_code = '\n'.join(include_statements) + 2*'\n'
        return_code = include_statements_code + return_code

    return return_code

# ====== END: constrFactoryFunctionCode ========



# ====== constrWrapperFunction ========

def constrWrapperFunction(class_el, method_el, indent=cfg.indent, n_indents=0, remove_n_args=0, only_declaration=False, include_full_namespace=False):

    class_name = utils.getClassNameDict(class_el)
    is_template = utils.isTemplateClass(class_name)

    # Check if this is an operator function
    is_operator = (method_el.tag == 'OperatorMethod')

    # If operator, check that we have a name for it
    if (is_operator) and (method_el.get('name') not in gb.operator_names.keys()):
        raise Exception('No known name for the operator: %s  -- Add an entry to the following dictionary: gb.operator_names' % method_el.get('name'))

    # Function name
    if is_operator:
        func_name = 'operator' + method_el.get('name')
    else:
        func_name = method_el.get('name')

    return_type_dict = utils.findType(gb.id_dict[method_el.get('returns')])
    return_el     = return_type_dict['el']
    pointerness   = return_type_dict['pointerness']
    is_ref        = return_type_dict['is_reference']
    return_kw     = return_type_dict['cv_qualifiers']   

    # Check constness (in the following sense: "double someFunction() const", i.e. a function that does not modify member variables.)
    is_const = ('const' in method_el.keys()) and (method_el.get('const') == '1')

    return_is_loaded_class = utils.isLoadedClass(return_el)

    # Function return type
    if is_template:
        # Get the function's types from config file
        func_types = utils.getTemplatedMethodTypes(method_el, class_name)

        return_type = func_types['return']
        args = func_types['args']
    else:
        # return_kw_str = ' '.join(return_kw) + ' '*bool(len(return_kw))
        return_type   = return_type_dict['name'] + '*'*pointerness + '&'*is_ref

        # Function arguments (get list of dicts with argument info)
        args = utils.getArgs(method_el)

    # Remove arguments when creating overloaded versions (for dealing with default argument values)
    if remove_n_args > 0:
        args = args[:-remove_n_args]

    # Construct wrapper function name
    if is_template:
      w_func_name = funcutils.constrWrapperName(method_el, include_full_namespace=False)
      if include_full_namespace:
          namespaces = utils.getNamespaces(method_el)
          namespaces[-1] = class_name['short'] + class_name['templ_vars']
          if len(namespaces) > 0:
              w_func_name = '::'.join(namespaces) + '::' + w_func_name
    else:
      w_func_name = funcutils.constrWrapperName(method_el, include_full_namespace=include_full_namespace)

    # Choose wrapper return type
    if return_is_loaded_class:
        if (pointerness == 0) and (is_ref):
            w_return_type = utils.toAbstractType(return_type, include_namespace=True)
        elif (pointerness == 0) and (not is_ref):
            w_return_type = utils.toAbstractType(return_type, include_namespace=True, add_pointer=True, remove_reference=True)
        else:
            w_return_type = utils.toAbstractType(return_type, include_namespace=True)

    else:
        w_return_type = return_type


    # Construct list of arguments for wrapper function
    w_args = funcutils.constrWrapperArgs(args, add_ref=True, convert_loaded_to_abstract=True)

    # Construct bracket with input arguments for wrapper function
    if only_declaration:
        w_args_bracket = utils.constrArgsBracket(w_args, include_arg_name=False, include_namespace=True)
    else:
        w_args_bracket = utils.constrArgsBracket(w_args, include_namespace=True)

    # Construct declaration line for wrapper function
    w_func_line = funcutils.constrDeclLine(w_return_type, w_func_name, w_args_bracket, keywords=return_kw, is_const=is_const)

    # Construct function body for wrapper function
    if only_declaration:
        pass
    else:
        w_func_body = funcutils.constrWrapperBody(return_type, func_name, args, return_is_loaded_class)

    # Combine code and add indentation
    wrapper_code  = ''
    if only_declaration:
        wrapper_code += utils.addIndentation(w_func_line, n_indents*indent) + ';\n'
    else:
        if is_template:
            wrapper_code += 'template ' + class_name['templ_bracket'] + '\n'
        wrapper_code += utils.addIndentation(w_func_line, n_indents*indent) + '\n'
        wrapper_code += utils.addIndentation(w_func_body, n_indents*indent) + '\n'

    # Return result
    return wrapper_code

# ====== END: constrWrapperFunction ========



# ====== constrEnumDecl ========

def constrEnumDecl(enum_el, indent=cfg.indent, n_indents=0):

    enum_code = ' '*(n_indents)*indent

    enum_name = enum_el.get('name')

    enum_type_dict = utils.findType( enum_el )
    enum_values    = enum_type_dict['enum_values']

    enum_code += 'enum ' + enum_name + ' {\n'
    for val in enum_values:
        enum_code += ' '*(n_indents+1)*indent + val + ',\n'
    enum_code = enum_code.rstrip(',')
    enum_code += ' '*n_indents*indent + '};\n'

    return enum_code

# ====== END: constrEnumDecl ========



# ====== constrVariableRefFunction ========

def constrVariableRefFunction(var_el, class_el, virtual=False, indent=cfg.indent, n_indents=0, only_declaration=False,
                              include_full_namespace=False, add_return_type_suffix=False):

    func_code = ''

    var_name = var_el.get('name')
    class_name = utils.getClassNameDict(class_el)

    var_type_dict    = utils.findType( var_el )
    var_type_name    = var_type_dict['name']
    pointerness      = var_type_dict['pointerness']
    is_ref           = var_type_dict['is_reference']
    var_kw           = var_type_dict['cv_qualifiers']
    var_array_limits = var_type_dict['array_limits']
    is_array         = var_type_dict['is_array']

    var_array_limits_str = ''.join([ '[%i]' % i for i in var_array_limits ])

    var_kw_str = ' '.join(var_kw) + ' '*bool(len(var_kw))

    is_template = utils.isTemplateClass(class_name)

    # If class is templated, pull type from file
    if is_template:
        var_type = utils.getTemplatedMemberVariableType(var_el)
    else:
        var_type   = var_type_dict['name'] + '*'*pointerness + '&'*is_ref

    # pointerness, is_ref = utils.pointerAndRefCheck(var_el)

    ref_method_name = var_name + '_ref' + gb.code_suffix

    if include_full_namespace:
        namespaces = utils.getNamespaces(var_el)
        if len(namespaces) > 0:
            if is_template:
                namespaces[-1] = class_name['short'] + class_name['templ_vars']
            ref_method_name = '::'.join(namespaces) + '::' + ref_method_name


    var_is_loaded_class = utils.isLoadedClass(var_el)

    if (var_is_loaded_class) and (pointerness == 0):
        return_type = utils.toAbstractType(var_type)
    elif (var_is_loaded_class) and (pointerness == 1) and (add_return_type_suffix):
        return_type   = utils.toWrapperType(var_type, include_namespace=include_full_namespace)
        var_type_name = utils.toWrapperType(var_type_name, include_namespace=include_full_namespace)
    else:
        return_type = var_type


    # If variable type is a known class, add '::' for absolute namespace.
    if (not var_is_loaded_class) and utils.isKnownClass(var_el):
        return_type = '::' + return_type


    if (not is_ref) and (not is_array):
        return_type = return_type + '&'
    else:
        pass


    func_code += ' '*n_indents*indent

    if virtual:
        if is_array:
            func_code += 'virtual ' + var_kw_str + return_type + ' (&' + ref_method_name + '())' + var_array_limits_str + ' =0;\n'
        else:
            func_code += 'virtual ' + var_kw_str + return_type + ' ' + ref_method_name + '() =0;\n'

    else:

        if is_template and not only_declaration:
            func_code += 'template ' + class_name['templ_bracket'] + '\n'

        if is_array:
            func_code += var_kw_str + return_type + ' (&' + ref_method_name + '())' + var_array_limits_str
        else:
            func_code += var_kw_str + return_type + ' ' + ref_method_name + '()'

        if only_declaration:
            func_code += ';\n'
        else:
            if (var_is_loaded_class) and (pointerness > 0):

                wrapper_var_name = var_name + gb.code_suffix

                func_code += '\n'
                func_code += ' '*n_indents*indent + '{\n'
                func_code += ' '*(n_indents+1)*indent + 'if (not ' + wrapper_var_name + ') { ' + wrapper_var_name + ' = new ' + var_type_name + '(' + var_name + ', true); }\n'
                func_code += ' '*(n_indents+1)*indent + 'return ' + wrapper_var_name + ';\n'
                func_code += ' '*n_indents*indent + '}\n'

            else:
                func_code += ' { return ' + var_name  +'; }\n'

    return func_code

# ====== END: constrVariableRefFunction ========



# ====== constrPtrCopyFunc ========

def constrPtrCopyFunc(class_el, class_name, virtual=False, indent=cfg.indent, n_indents=0, only_declaration=False, include_full_namespace=False):

    func_name = 'pointer_copy' + gb.code_suffix

    is_template = utils.isTemplateClass(class_name)
    ptr_code = ''

    if is_template:
       if not only_declaration:
           ptr_code = 'template ' + class_name['templ_bracket'] + '\n'
       abstr_class_name_short = class_name['abstr_short'] + class_name['templ_vars']
       class_name_short = class_name['short'] + class_name['templ_vars']
    else:
        class_name_short = class_name['short_templ']
        abstr_class_name_short = class_name['abstr_short']

    class_name_long = class_name_short
    abstr_class_name_long = abstr_class_name_short

    if include_full_namespace:
        namespaces = utils.getNamespaces(class_el)
        if len(namespaces) > 0:
            abstr_class_name_long = '::'.join(namespaces) + '::' + abstr_class_name_short
            class_name_long = '::'.join(namespaces) + '::' + class_name_short
        func_name = class_name_long + "::" + func_name

    if virtual:
        ptr_code += ' '*cfg.indent*n_indents + 'virtual '+ abstr_class_name_long + '*' + ' ' + func_name + '() =0;\n'
    else:
        ptr_code += ' '*cfg.indent*n_indents + abstr_class_name_long + '*' + ' ' + func_name + '()'

        if only_declaration:
            ptr_code += ';\n'
        else:
            ptr_code += '\n'
            ptr_code += ' '*cfg.indent*n_indents + '{\n'
            ptr_code += ' '*cfg.indent*(n_indents+1) + abstr_class_name_long + '* new_ptr = new ' + class_name_short + '(*this);\n'
            ptr_code += ' '*cfg.indent*(n_indents+1) + 'return new_ptr;\n'
            ptr_code += ' '*cfg.indent*n_indents + '}\n'

    return ptr_code

# ====== END: constrPtrCopyFunc ========



# ====== constrPtrAssignFunc ========

def constrPtrAssignFunc(class_el, class_name, virtual=False, indent=cfg.indent, n_indents=0, only_declaration=False, include_full_namespace=False):

    func_name  = 'pointer_assign' + gb.code_suffix

    # Some shorthand variable names for different cases
    if class_name['is_template']:
        abstr_class_name_short = class_name['abstr_short'] + class_name['templ_vars']
        class_name_short = class_name['short'] + class_name['templ_vars']
        wrp_class_name_short = class_name['wrp_short'] + class_name['templ_vars']
    else:
        abstr_class_name_short = class_name['abstr_short_templ']
        class_name_short = class_name['short_templ']
        wrp_class_name_short = class_name['wrp_short_templ']

    abstr_class_name_long = abstr_class_name_short
    class_name_long = class_name_short
    wrp_class_name_long = wrp_class_name_short

    if include_full_namespace:
        namespaces = utils.getNamespaces(class_el)
        if len(namespaces) > 0:
            abstr_class_name_long = '::'.join(namespaces) + '::' + abstr_class_name_short
            class_name_long = '::'.join(namespaces) + '::' + class_name_short
            wrp_class_name_long = '::'.join(namespaces) + '::' + wrp_class_name_short
        func_name = class_name_long + "::" + func_name

    # Now generate the code
    ptr_code = ''

    if (class_name['is_template']) and (not only_declaration):
       ptr_code = 'template ' + class_name['templ_bracket'] + '\n'

    if virtual:
        ptr_code += ' '*cfg.indent*n_indents + 'virtual void ' + func_name + '(' + abstr_class_name_long + '*) =0;\n'

    else:
        ptr_code += ' '*cfg.indent*n_indents + 'void ' + func_name + '(' + abstr_class_name_long + '* in)'

        if only_declaration:
            ptr_code += ';\n'
        else:
            ptr_code += '\n'
            ptr_code += ' '*cfg.indent*n_indents + '{\n'
            ptr_code += ' '*cfg.indent*(n_indents+1) + gb.gambit_backend_namespace + '::' + wrp_class_name_long + '* wptr_temp = ' + abstr_class_name_long + '::get_wptr();\n'
            ptr_code += ' '*cfg.indent*(n_indents+1) + '*this = *dynamic_cast<' + class_name_short + '*>(in);\n'
            ptr_code += ' '*cfg.indent*(n_indents+1) + abstr_class_name_short + '::set_wptr(wptr_temp);\n'
            ptr_code += ' '*cfg.indent*n_indents + '}\n'

    return ptr_code

# ====== END: constrPtrAssignFunc ========



# ====== checkAssignmentOperator ========

def checkAssignmentOperator(class_el):

    found_assignment_operator = False
    is_artificial = False

    # Get list of all class members
    class_members = utils.getMemberElements(class_el, include_artificial=True)

    # Look for assignment operator
    for mem_el in class_members:
        if (mem_el.tag == 'OperatorMethod') and (mem_el.get('name') == '='):

            # Check that return type is either void or the class type itself (possibly as a reference)
            return_type_dict = utils.findType(mem_el)
            return_type    = return_type_dict['name'] + '*'*return_type_dict['pointerness'] + '&'*return_type_dict['is_reference']
            return_type_id = return_type_dict['id']

            if (return_type == 'void') or (return_type_id == class_el.get('id')):

                # Check that the only argument is another class instance
                args = utils.getArgs(mem_el)
                if (len(args) == 1) and (args[0]['id'] == class_el.get('id')):

                    found_assignment_operator = True

                    if ('artificial' in mem_el.keys()) and (mem_el.get('artificial')=='1'):
                        is_artificial = True

    return found_assignment_operator, is_artificial

# ====== END: checkAssignmentOperator ========



# ====== checkCopyConstructor ========

def checkCopyConstructor(class_el, return_id=False):

    found_copy_constructor = False
    copy_constr_id = ''

    # Get list of all class members
    class_members = utils.getMemberElements(class_el, include_artificial=True)

    # Look for copy constructor
    for mem_el in class_members:
        if mem_el.tag == 'Constructor':

            if (mem_el.get('access') == 'protected') or (mem_el.get('access') == 'private'):
                return found_copy_constructor, copy_constr_id

            # Check that the only argument is another class instance
            args = utils.getArgs(mem_el)
            if (len(args) == 1) and (args[0]['id'] == class_el.get('id')):

                found_copy_constructor = True
                copy_constr_id = mem_el.get('id')

    if return_id:
        return found_copy_constructor, copy_constr_id
    else:
        return found_copy_constructor

# ====== END: checkCopyConstructor ========


# ====== constrWrapperDecl ========

def constrWrapperDecl(class_el, class_name, loaded_parent_classes, class_variables, class_functions, class_constructors, class_operators, construct_assignment_operator, has_copy_constructor, indent=' '*cfg.indent):

    decl_code = ''

    # short_wrapper_class_name = utils.toWrapperType(class_name['short'])
    # wrapper_class_name = utils.toWrapperType(class_name['long'], include_namespace=True)

    # Check if class is template
    is_template = utils.isTemplateClass(class_name)

    # Construct inheritance line
    inheritance_line = ''
    for parent_dict in loaded_parent_classes:
        inheritance_line += 'virtual '*parent_dict['virtual'] + parent_dict['access'] + ' '
        if parent_dict['class_name']['namespace'] == class_name['namespace'] :
            inheritance_line += parent_dict['class_name']['wrp_short_templ'] + ', '
        else :
            inheritance_line += parent_dict['class_name']['wrp_long_templ'] + ', '
    inheritance_line = inheritance_line.rstrip(', ')

    # If no other parent classes, add WrapperBase
    if inheritance_line == '':
        # inheritance_line = ' : public virtual WrapperBase'
        inheritance_line = ' : public WrapperBase'
    else:
        inheritance_line = ' : ' + inheritance_line

    # Class declaration line
    decl_code += '\n'
    if is_template:
      decl_code += 'template <>\n'
    decl_code += 'class ' + class_name['wrp_short_templ'] + inheritance_line + '\n'

    # Class body
    decl_code += '{\n'

    #
    # Add any typedefs needed for types moved to the abstract class
    #
    for abstr_type in gb.moved_to_abstract_class:
        if utils.getNamespaces(abstr_type)[-1] == class_name['short'] :
            # get the type
            abstr_type_dict = utils.findType(abstr_type)
            abstr_type_name = utils.removeNamespace(abstr_type_dict['name'])
            abstr_type_enum_values = abstr_type_dict['enum_values']

            # Add code
            decl_code += 2*indent + '// Types: \n'
            decl_code += indent + 'public:\n'
            decl_code += 2*indent + 'typedef ' + class_name['abstr_long'] + '::' + abstr_type_name + ' ' + abstr_type_name + ';\n'

            # If its an enumeration, add all values as static constexpr members
            if abstr_type.tag in ['Enumeration'] :
                for val in abstr_type_enum_values :
                    decl_code += 2*indent + "static constexpr " + abstr_type_name + ' ' + val + ' = ' + class_name['abstr_long'] + '::' + val + ';\n\n'

    #
    # Variables:
    #
    decl_code += 2*indent + '// Member variables: \n'

    # Add a static function pointer for each factory function
    decl_code += indent + 'public:\n'
    decl_code += 2*indent + '// -- Static factory pointers: \n'
    factory_counter = 0
    for constr_el in class_constructors:


        # We need pointers for all the overloaded factory functions (generated due to default value arguments)
        n_overloads = funcutils.numberOfDefaultArgs(constr_el)

        # Identify arguments, translate argument type of loaded classes
        # and construct the argument bracket
        args = utils.getArgs(constr_el)

        # One factory function pointer for each set of default arguments
        for remove_n_args in range(n_overloads+1):

            # Check that the constructor is acceptable
            if funcutils.ignoreFunction(constr_el, limit_pointerness=True, remove_n_args=remove_n_args):
                continue

            if remove_n_args == 0:
                use_args = args
            else:
                use_args = args[:-remove_n_args]
            
            args_bracket = utils.constrArgsBracket(use_args, include_arg_name=False, include_arg_type=True, include_namespace=True)

            # Factory pointer name
            factory_ptr_name = '__factory' + str(factory_counter)

            # Construct factory pointer code
            decl_code += 2*indent + 'static ' + class_name['abstr_short_templ']
            decl_code += '* (*' + factory_ptr_name + ')' + args_bracket + ';\n'

            # Increment factory counter
            factory_counter += 1

    # Add references to all public variables
    decl_code += '\n'
    decl_code += 2*indent + '// -- Other member variables: \n'
    current_access = ''
    for var_el in class_variables:

        # Accessor
        accessor = var_el.get('access')
        if accessor != current_access:
            decl_code += indent + accessor + ':\n'
            current_access = accessor

        # Variable name
        var_name = var_el.get('name')

        # Determine variable type
        var_type_dict = utils.findType(var_el)
        pointerness      = var_type_dict['pointerness']
        is_ref           = var_type_dict['is_reference']
        var_kw           = var_type_dict['cv_qualifiers']
        var_array_limits = var_type_dict['array_limits']
        is_array         = var_type_dict['is_array']

        var_array_limits_str = ''.join(['[%i]' % i for i in var_array_limits])


        var_kw_str = ' '.join(var_kw) + ' '*bool(len(var_kw))
        
        var_type = var_type_dict['name'] + '*'*pointerness + '&'*is_ref

        var_is_loaded_class = utils.isLoadedClass(var_el)
        var_is_known_class  = utils.isKnownClass(var_el)

        # # FIXME: At the moment there are problems with member variables that are pointer-to-loaded-class. For now, skip them:
        # if var_is_loaded_class and pointerness > 0:
        #     print('WARNING: The member variable %s is of a loaded type and has pointerness > 0. This BOSS cannot yet handle. Ignored for now...' % var_name)
        #     continue


        if var_is_loaded_class:

            use_var_type = var_type

            if not is_ref:
                use_var_type = var_type + '&'

            decl_code += 2*indent + var_kw_str + use_var_type + ' ' + var_name + var_array_limits_str  + ';\n'

        else:
            if var_is_known_class:
                var_type = '::' + var_type

            if is_ref:
                use_var_type = var_type
            else:
                if not is_array:
                    use_var_type = var_type + '&'
                else:
                    use_var_type = var_type

            if is_array:
                decl_code += 2*indent + var_kw_str + use_var_type + ' (&' + var_name +')' + var_array_limits_str  + ';\n'
            else:
                decl_code += 2*indent + var_kw_str + use_var_type + ' ' + var_name + ';\n'


    #
    # Functions:
    #
    decl_code += '\n'
    decl_code += 2*indent + '// Member functions: \n'

    # Add wrappers for all member functions, including operator functions
    # and overloaded versions of functions with default value arguments

    current_access = ''
    for func_el in class_functions:

        # Accessor
        accessor = func_el.get('access')
        if accessor != current_access:
            decl_code += indent + accessor + ':\n'
            current_access = accessor

        # Check if this is an operator function
        is_operator = (func_el.tag == 'OperatorMethod')

        # Check if this function makes use of any loaded types
        uses_loaded_type = funcutils.usesLoadedType(func_el)

        # Function name
        if is_operator:
            func_name = 'operator' + func_el.get('name')
        else:
            func_name = func_el.get('name')

        # Skip the assignment operator (we implement our own later on)
        if func_name == 'operator=':
            continue

        # Check for const function
        is_const = utils.isConstFunction(func_el)

        # Determine return type
        return_type_dict = utils.findType(func_el)
        return_type_el = return_type_dict['el']
        pointerness    = return_type_dict['pointerness']
        is_ref         = return_type_dict['is_reference']
        return_type_kw = return_type_dict['cv_qualifiers']

        return_kw_str  = ' '.join(return_type_kw) + ' '*bool(len(return_type_kw))

        return_is_loaded    = utils.isLoadedClass(return_type_el)

        return_type   = return_type_dict['name'] + '*'*pointerness + '&'*is_ref

        # If return type was moved to abstract class, change namespace
        if utils.typeInList(return_type_el, gb.moved_to_abstract_class) :
            return_type = class_name['abstr_long_templ'] + "::" + utils.removeNamespace(return_type)


        # If return type is a known class, add '::' for absolute namespace.
        if (not return_is_loaded) and utils.isKnownClass(return_type_el):
            return_type = '::' + return_type

        # If return-by-value, then a const qualifier on the return value is meaningless
        # (will result in a compiler warning)
        if (pointerness == 0) and (is_ref is False) and ('const' in return_type_kw):
            return_kw_str = return_kw_str.replace('const', '')

        # Arguments
        args = utils.getArgs(func_el)

        # If any of the arg types was move to the abstract class, change namespace
        for arg in args:
            if utils.typeInList(arg, gb.moved_to_abstract_class) :
                arg_type = class_name['abstr_long_templ'] + "::" + utils.removeNamespace(arg.get('type'))
                arg['type'] =  arg_type

        # One function for each set of default arguments
        n_overloads = funcutils.numberOfDefaultArgs(func_el)
        for remove_n_args in range(n_overloads+1):

            # Check that the function is acceptable
            if funcutils.ignoreFunction(func_el, remove_n_args=remove_n_args):
                continue

            if remove_n_args == 0:
                use_args = args
            else:
                use_args = args[:-remove_n_args]

            # Argument bracket
            args_bracket = utils.constrArgsBracket(use_args, include_arg_name=True, include_arg_type=True, include_namespace=True)

            # Name of function to call (in abstract class)
            if is_operator:
                if uses_loaded_type:
                    pass
                    # call_func_name = 'operator_' + gb.operator_names[func_el.get('name')] + gb.code_suffix
                else:
                    pass
                    # call_func_name = 'operator' + func_el.get('name')
            else:
                # call_func_name = func_name + gb.code_suffix
                if uses_loaded_type or (remove_n_args>0):
                    pass
                    # call_func_name = func_name + gb.code_suffix
                else:
                    pass
                    # call_func_name = func_name


           # Write declaration line
            decl_code += 2*indent + return_kw_str + return_type + ' ' + func_name + args_bracket + is_const*' const' + ';\n'
            decl_code += '\n'


    #
    # Add all constructors here...
    #


    # Add wrappers for all original constructors except the copy constructor
    temp_code = ''
    current_access = ''
    for constr_el in class_constructors:

        # Accessor
        accessor = constr_el.get('access')
        if accessor != current_access:
            temp_code += indent + accessor + ':\n'
            current_access = accessor

        # Identify arguments
        args = utils.getArgs(constr_el)
        factory_args = funcutils.constrWrapperArgs(args, add_ref=True)

        # If default arguments are use, we need overloaded constructors to connect to the overloaded
        # factory function pointers
        n_overloads = funcutils.numberOfDefaultArgs(constr_el)

        # One constructor for each set of default arguments
        for remove_n_args in range(n_overloads+1):

            # Check that the constructor is acceptable
            if funcutils.ignoreFunction(constr_el, limit_pointerness=True, remove_n_args=remove_n_args):
                continue
            
            
            if remove_n_args == 0:
                use_args         = args
                # factory_use_args = factory_args
            else:
                use_args         = args[:-remove_n_args]
                # factory_use_args = factory_args[:-remove_n_args]

            args_bracket = utils.constrArgsBracket(use_args, include_arg_name=True, include_arg_type=True, include_namespace=True, use_wrapper_class=False)

            temp_code += 2*indent + class_name['wrp_short'] + args_bracket + ';\n'

    if temp_code != '':
        decl_code += '\n'
        decl_code += 2*indent + '// Wrappers for original constructors: \n'
        decl_code += temp_code + '\n'

    if current_access != 'public':
        decl_code += indent + 'public:\n'


    # Add special constructor based on abstract pointer
    decl_code += 2*indent + '// Special pointer-based constructor: \n'
    decl_code += 2*indent + class_name['wrp_short'] + '(' + class_name['abstr_short_templ']
    decl_code += '* in);\n'
    # decl_code += 2*indent + class_name['short'] + '(const ' + class_name['abstr_long'] +'* in);\n'


    # Add copy constructor
    if has_copy_constructor:
        decl_code += '\n'
        decl_code += 2*indent + '// Copy constructor: \n'
        decl_code += 2*indent + class_name['wrp_short'] + '(const ' + class_name['wrp_short'] +'& in);\n'

    # Add wrappers for all operators except the artificial ones which were filtered out prior
    # TODO: ZELUN subject to change
    # This is used to load the operators in wrapper_decl however I am not exactly sure about the 
    # format we want it in so it is still subject to update
    # TODO: I'm pretty sure this shouldn't be here, operators are treated as normal methods
#    temp_code = ''
#    current_access = ''
#    for oper_el in class_operators:
#
#        # Accessor
#        accessor = oper_el.get('access')
#        if accessor != current_access:
#            temp_code += indent + accessor + ':\n'
#            current_access = accessor
#
#        # Identify arguments
#        args = utils.getArgs(oper_el)
#        factory_args = funcutils.constrWrapperArgs(args, add_ref=True)
#
#        # If default arguments are use, we need overloaded constructors to connect to the overloaded
#        # factory function pointers
#        n_overloads = funcutils.numberOfDefaultArgs(oper_el)
#
#        # One constructor for each set of default arguments
#        for remove_n_args in range(n_overloads+1):
#
#            # Check that the constructor is acceptable
#            if funcutils.ignoreFunction(oper_el, limit_pointerness=True, remove_n_args=remove_n_args):
#                continue
#
#            if remove_n_args == 0:
#                use_args = args
#                # factory_use_args = factory_args
#            else:
#                use_args = args[:-remove_n_args]
#                # factory_use_args = factory_args[:-remove_n_args]
#
#            args_bracket = utils.constrArgsBracket(
#                use_args, include_arg_name=True, include_arg_type=True, include_namespace=True, use_wrapper_class=False)
#
#            temp_code += 2*indent + class_name['wrp_short'] + '& ' + 'operator ' + oper_el.get('name') + args_bracket + ';\n'
#
#    if temp_code != '':
#        decl_code += temp_code + '\n'
    #
    # Add assignment operator
    #
    if construct_assignment_operator:
        decl_code += '\n'
        decl_code += 2*indent + '// Assignment operator: \n'
        decl_code += 2*indent + class_name['wrp_short'] + '& ' + 'operator=(const ' + class_name['wrp_short'] +'& in);\n'


    #
    # Add destructor
    #
    decl_code += '\n'
    decl_code += 2*indent + '// Destructor: \n'
    decl_code += 2*indent + '~' + class_name['wrp_short'] + '();\n'


    #
    # Add get_BEptr function
    #
    decl_code += '\n'
    # decl_code += indent + 'private:\n'
    decl_code += 2*indent + '// Returns correctly casted pointer to Abstract class: \n'
    decl_code += 2*indent + class_name['abstr_short_templ']
    decl_code += '* get_BEptr() const;\n'


    # Close class body
    decl_code += '\n'
    decl_code += '};\n'


    # Add namespace
    namespace, class_name_short = utils.removeNamespace(class_name['wrp_long'], return_namespace=True)

    if namespace == '':
        namespace_list = []
    else:
        namespace_list = namespace.split('::')

    n_indents = len(namespace_list)

    decl_code_with_ns  = ''
    decl_code_with_ns += utils.constrNamespace(namespace_list,'open')
    decl_code_with_ns += utils.addIndentation(decl_code, cfg.indent*n_indents)
    decl_code_with_ns += utils.constrNamespace(namespace_list,'close')

    # Return result
    return decl_code_with_ns

# ====== END: constrWrapperDecl ========



# ====== constrWrapperDef ========

def constrWrapperDef(class_el, class_name, loaded_parent_classes, class_variables, class_functions, class_constructors, construct_assignment_operator, has_copy_constructor, indent=' '*cfg.indent, do_inline=False):

    def_code = ''

    short_wrapper_class_name = utils.toWrapperType(class_name['wrp_short'])
    # wrapper_class_name = utils.toWrapperType(class_name['long'], include_namespace=True)

    # Check if class is template
    is_template = utils.isTemplateClass(class_name)

    # Functions:
    def_code += '\n'
    def_code += '// Member functions: \n'

    # Add wrappers for all member functions, including operator functions
    # and overloaded versions of functions with default value arguments

    for func_el in class_functions:

        # Check if this is an operator function
        is_operator = (func_el.tag == 'OperatorMethod')

        # Check if this function makes use of any loaded types
        uses_loaded_type = funcutils.usesLoadedType(func_el)

        # Function name
        if is_operator:
            func_name = 'operator' + func_el.get('name')
        else:
            func_name = func_el.get('name')

        # Skip the assignment operator (we implement out own later on)
        if func_name == 'operator=':
            continue

        # Check for const function
        is_const = utils.isConstFunction(func_el)


        # Determine return type
        return_type_dict = utils.findType(func_el)
        return_type_el = return_type_dict['el']
        pointerness    = return_type_dict['pointerness']
        is_ref         = return_type_dict['is_reference']
        return_type_kw = return_type_dict['cv_qualifiers']

        return_kw_str  = ' '.join(return_type_kw) + ' '*bool(len(return_type_kw))

        return_is_loaded    = utils.isLoadedClass(return_type_el)

        return_type   = return_type_dict['name'] + '*'*pointerness + '&'*is_ref

        # If return type was moved to abstract class, change namespace
        if utils.typeInList(return_type_el, gb.moved_to_abstract_class) :
            return_type = class_name['abstr_long_templ'] + "::" +  utils.removeNamespace(return_type)

        # If return type is a known class, add '::' for absolute namespace.
        return_type_name = utils.getClassNameDict(return_type_el)
        if (not return_is_loaded) and utils.isKnownClass(return_type_el):
            return_type = '::' + return_type



        # If return-by-value, then a const qualifier on the return value is meaningless
        # (will result in a compiler warning)
        if (pointerness == 0) and (is_ref is False) and ('const' in return_type_kw):
            return_kw_str = return_kw_str.replace('const', '')

        # Arguments
        args = utils.getArgs(func_el)

        # If any of the arg types was move to the abstract class, change namespace
        for arg in args:
            if utils.typeInList(arg, gb.moved_to_abstract_class) :
                arg_type = class_name['abstr_long_templ'] + "::" + utils.removeNamespace(arg.get('type'))
                arg['type'] =  arg_type


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

            # Arguments bracket
            args_bracket = utils.constrArgsBracket(use_args, include_arg_name=True, include_arg_type=True, include_namespace=True)

            # Name of function to call (in abstract class)
            if is_operator:
                if uses_loaded_type:
                    call_func_name = 'operator_' + gb.operator_names[func_el.get('name')] + gb.code_suffix
                else:
                    call_func_name = 'operator' + func_el.get('name')
            else:
                if uses_loaded_type or (remove_n_args>0):
                    call_func_name = func_name + gb.code_suffix
                else:
                    call_func_name = func_name


            # Write declaration line
            def_code += do_inline*'inline ' + return_kw_str + return_type + ' ' + class_name['wrp_short_templ'] + '::' + func_name + args_bracket + is_const*' const' + '\n'

            # Write function body
            def_code += '{\n'

            if return_type == 'void':
                def_code += indent
            else:
                def_code += indent + 'return '

            args_bracket_notypes = utils.constrArgsBracket(use_args, include_arg_name=True, include_arg_type=False, wrapper_to_pointer=True)

            if return_is_loaded:

                abs_return_type_simple = utils.toAbstractType(return_type, include_namespace=True, remove_reference=True, remove_pointers=True)
                # return_type_simple     = return_type.replace('*','').replace('&','')

                if is_const:
                    get_BEptr_call = 'const_cast<const ' + class_name['abstr_short_templ'] +'*>(get_BEptr())'
                else:
                    get_BEptr_call = 'get_BEptr()'

                # Return-by-reference
                if is_ref:
                    if 'const' in return_type_kw:
                        def_code += 'const_cast<' + abs_return_type_simple + '&>(' + get_BEptr_call + '->' + call_func_name + args_bracket_notypes + ').get_init_wref();\n'
                    else:
                        def_code += get_BEptr_call + '->' + call_func_name + args_bracket_notypes + '.get_init_wref();\n'

                # Return-by-pointer
                elif (not is_ref) and (pointerness > 0):
                    if 'const' in return_type_kw:
                        def_code += 'const_cast<' + abs_return_type_simple + '*>(' + get_BEptr_call + '->' + call_func_name + args_bracket_notypes + ')->get_init_wptr();\n'
                    else:
                        def_code += get_BEptr_call + '->' + call_func_name + args_bracket_notypes + '->get_init_wptr();\n'

                # Return-by-value
                else:
                    if 'const' in return_type_kw:
                        # def_code += return_type + '( const_cast<' + abs_return_type_simple + '*>(' + get_BEptr_call + '->' + call_func_name + args_bracket_notypes + ')->get_init_wref() );\n'
                        def_code += return_type + '( const_cast<' + abs_return_type_simple + '*>(' + get_BEptr_call + '->' + call_func_name + args_bracket_notypes + ') );\n'
                    else:
                        # def_code += return_type + '( ' + get_BEptr_call + '->' + call_func_name + args_bracket_notypes + '->get_init_wref() );\n'
                        def_code += return_type + '( ' + get_BEptr_call + '->' + call_func_name + args_bracket_notypes + ' );\n'

            else:
                def_code += 'get_BEptr()->' + call_func_name + args_bracket_notypes + ';\n'

            def_code += '}\n'
            def_code += '\n'


    #
    # Add all constructors here...
    #

    # First generate some code common to all constructors

    common_init_list_code   = ''

    common_constructor_body = ''
    if gb.debug_mode:
        common_constructor_body += indent + 'std::cerr << "DEBUG: " << this << " ' + short_wrapper_class_name + ' ctor" << std::endl;\n'
    common_constructor_body += indent + 'get_BEptr()->set_wptr(this);\n'
    common_constructor_body += indent + 'get_BEptr()->set_delete_wrapper(false);\n'

    # mem_var_init_body = ''
    # has_loaded_class_mem_var = False

    for var_el in class_variables:

        # Get info
        var_name = var_el.get('name')

        var_type_dict = utils.findType(var_el)
        # var_type_name = var_type_dict['name']
        var_type_el   = var_type_dict['el']
        pointerness   = var_type_dict['pointerness']
        is_ref        = var_type_dict['is_reference']

        # var_type = var_type_dict['name'] + '*'*pointerness + '&'*is_ref

        var_is_loaded_class = utils.isLoadedClass(var_type_el)

        # wrapper_type_name = utils.toWrapperType(var_type, remove_reference=True, remove_pointers=True, include_namespace=True)
        # var_abstr_class_name = utils.getClassNameDict(var_type_el, abstract=True)
        # var_wrapper_base_class_name = 'WrapperBase<' + var_abstr_class_name['long'] + '>'

        # # FIXME: At the moment there are problems with member variables that are pointer-to-loaded-class. For now, skip them:
        # if var_is_loaded_class and pointerness > 0:
        #     print('WARNING: The member variable %s is of a loaded type and has pointerness > 0. This BOSS cannot yet handle. Ignored for now...' % var_name)
        #     continue

        # Construct common initialization list
        if var_is_loaded_class:
            if pointerness == 0:
                common_init_list_code += indent + var_name + '( get_BEptr()->' + var_name + '_ref' + gb.code_suffix + '().get_init_wref()),\n'
            elif pointerness == 1:
                common_init_list_code += indent + var_name + '( get_BEptr()->' + var_name + '_ref' + gb.code_suffix + '()->get_init_wptr()),\n'
                # common_init_list_code += indent + var_name + '(wrapperbase::BEptr->' + var_name + '_ref' + gb.code_suffix + '()),\n'
            else:
                raise Exception('The BOSS wrapper class system cannot presently handle member variables that have a pointerness > 1')
        else:
            common_init_list_code += indent + var_name + '( get_BEptr()->' + var_name + '_ref' + gb.code_suffix + '()),\n'


    # Clean up initialization list
    if common_init_list_code != '':
        common_init_list_code = common_init_list_code.rstrip(',\n') + '\n'


    # Add wrappers for all original constructors except the copy constructor
    temp_code = ''
    factory_counter = 0
    for constr_el in class_constructors:

        # Identify arguments
        args = utils.getArgs(constr_el)
        # factory_args = funcutils.constrWrapperArgs(args, add_ref=True)

        # If default arguments are used, we need overloaded constructors to connect to the overloaded
        # factory function pointers
        n_overloads = funcutils.numberOfDefaultArgs(constr_el)

        # One constructor for each set of default arguments
        for remove_n_args in range(n_overloads+1):

            # Check that the constructor is acceptable
            if funcutils.ignoreFunction(constr_el, limit_pointerness=True, remove_n_args=remove_n_args):
                continue

            if remove_n_args == 0:
                use_args         = args
                # factory_use_args = factory_args
            else:
                use_args         = args[:-remove_n_args]
                # factory_use_args = factory_args[:-remove_n_args]

            args_bracket = utils.constrArgsBracket(use_args, include_arg_name=True, include_arg_type=True, include_namespace=True, use_wrapper_class=False)
            args_bracket_notypes = utils.constrArgsBracket(use_args, include_arg_name=True, include_arg_type=False, wrapper_to_pointer=False)
            # factory_args_bracket = utils.constrArgsBracket(factory_use_args, include_arg_name=False, include_arg_type=True, include_namespace=True)

            # Factory pointer name
            factory_ptr_name = '__factory' + str(factory_counter)

            temp_code += 'inline ' + class_name['wrp_short_templ'] + '::' + class_name['wrp_short'] + args_bracket + ' :\n'

            parent_class_init_list = ''
            # parent_class_init_list += indent + 'WrapperBase(' + factory_ptr_name + args_bracket_notypes + '),\n'
            for parent_dict in loaded_parent_classes:
                parent_class_init_list += indent + parent_dict['class_name']['wrp_short_templ'] + '(' + factory_ptr_name + args_bracket_notypes + '),\n'
            if parent_class_init_list == '':
                parent_class_init_list += indent + 'WrapperBase(' + factory_ptr_name + args_bracket_notypes + '),\n'

            if common_init_list_code != '':
                temp_code += parent_class_init_list + common_init_list_code
            else:
                temp_code += parent_class_init_list.rstrip(',\n') + '\n'
            temp_code += '{\n'
            temp_code += common_constructor_body
            temp_code += '}\n'

            temp_code += '\n'

            # Increment factory counter
            factory_counter += 1

    if temp_code != '':
        def_code += '\n'
        def_code += '// Wrappers for original constructors: \n'
        def_code += temp_code

    # Add special constructor based on abstract class pointer.
    def_code += '// Special pointer-based constructor: \n'
    def_code += do_inline*'inline ' + class_name['wrp_short_templ'] + '::' + class_name['wrp_short'] + '(' + class_name['abstr_short_templ']
    def_code += '* in) :\n'

    parent_class_init_list = ''
    # parent_class_init_list += indent + 'WrapperBase(in),\n'
    for parent_dict in loaded_parent_classes:
        parent_class_init_list += indent + parent_dict['class_name']['wrp_short_templ'] + '(in),\n'
    if parent_class_init_list == '':
        parent_class_init_list += indent + 'WrapperBase(in),\n'

    if common_init_list_code != '':
        def_code += parent_class_init_list + common_init_list_code
    else:
        def_code += parent_class_init_list.rstrip(',\n') + '\n'
    def_code += '{\n'
    def_code += common_constructor_body
    def_code += '}\n'

    # # Const version of constructor from abstract class pointer
    # TODO: TG: Might not be needed but added for completion
    # def_code += do_inline*'inline ' + class_name['long_templ'] + '::' + class_name['short'] + '(const ' + class_name['abstr_long_templ']
    # def_code += '* in) :\n'

    # parent_class_init_list = ''
    # for parent_dict in loaded_parent_classes:
    #     parent_class_init_list += indent + parent_dict['class_name']['wrp_short'] + '(in),\n'
    # if parent_class_init_list == '':
    #     parent_class_init_list += indent + 'WrapperBase(in),\n'

    # if common_init_list_code != '':
    #     def_code += parent_class_init_list + common_init_list_code
    # else:
    #     def_code += parent_class_init_list.rstrip(',\n') + '\n'
    # def_code += '{\n'
    # def_code += common_constructor_body
    # def_code += '}\n'



    # Add copy constructor
    if has_copy_constructor:
        def_code += '\n'
        def_code += '// Copy constructor: \n'
        def_code += do_inline*'inline ' + class_name['wrp_short_templ'] + '::' + class_name['wrp_short'] + '(const ' + class_name['wrp_short'] +'& in) :\n'

        parent_class_init_list = ''
        # parent_class_init_list += indent + 'WrapperBase(in.get_BEptr()->pointer_copy' + gb.code_suffix + '()),\n'
        for parent_dict in loaded_parent_classes:
            parent_class_init_list += indent + parent_dict['class_name']['wrp_short_templ'] + '(in.get_BEptr()->pointer_copy' + gb.code_suffix + '()),\n'
        if parent_class_init_list == '':
            parent_class_init_list += indent + 'WrapperBase(in.get_BEptr()->pointer_copy' + gb.code_suffix + '()),\n'

        if common_init_list_code != '':
            def_code += parent_class_init_list + common_init_list_code
        else:
            def_code += parent_class_init_list.rstrip(',\n') + '\n'
        def_code += '{\n'
        def_code += common_constructor_body
        def_code += '}\n'


    #
    # Add assignment operator
    #
    if construct_assignment_operator:
        def_code += '\n'
        def_code += '// Assignment operator: \n'
        def_code += do_inline*'inline ' + class_name['wrp_short_templ'] + '& ' + class_name['wrp_short_templ'] + '::operator=(const ' + class_name['wrp_short'] +'& in)\n'
        def_code += '{\n'
        def_code +=   indent + 'if (this != &in)\n'
        def_code +=   indent + '{\n'
        def_code += 2*indent + 'get_BEptr()->pointer_assign' + gb.code_suffix + '(in.get_BEptr());\n'
        def_code +=   indent + '}\n'
        def_code +=   indent + 'return *this;\n'
        def_code += '}\n\n'


    #
    # Add destructor
    #
    def_code += '\n'
    def_code += '// Destructor: \n'
    def_code += do_inline*'inline ' + class_name['wrp_short_templ'] + '::~' + class_name['wrp_short'] + '()\n'
    def_code += '{\n'
    if gb.debug_mode:
        def_code += indent + 'std::cerr << "DEBUG: " << this << " ' + short_wrapper_class_name + ' dtor (BEGIN)" << std::endl;\n'
    def_code +=   indent + 'if (get_BEptr() != 0)\n'
    def_code +=   indent + '{\n'
    def_code += 2*indent + 'get_BEptr()->set_delete_wrapper(false);\n'
    def_code += 2*indent + 'if (can_delete_BEptr())\n'
    def_code += 2*indent + '{\n'
    def_code += 3*indent + 'delete BEptr;\n'
    def_code += 3*indent + 'BEptr = 0;\n'
    def_code += 2*indent + '}\n'
    def_code +=   indent + '}\n'
    def_code +=   indent + 'set_delete_BEptr(false);\n'
    if gb.debug_mode:
        def_code += indent + 'std::cerr << "DEBUG: " << this << " ' + short_wrapper_class_name + ' dtor (END)" << std::endl;\n'
    def_code += '}\n'


    #
    # Add get_BEptr function
    #
    def_code += '\n'
    def_code += '// Returns correctly casted pointer to Abstract class: \n'
    def_code += do_inline*'inline ' + class_name['abstr_short_templ']
    def_code += '* ' + class_name['wrp_long_templ'] + '::get_BEptr() const\n'
    def_code += '{\n'
    def_code += indent + 'return dynamic_cast<' + class_name['abstr_short_templ']
    def_code += '*>(BEptr);\n'
    def_code += '}\n'


    # Add namespace
    namespace, class_name_short = utils.removeNamespace(class_name['wrp_long'], return_namespace=True)

    if namespace == '':
        namespace_list = []
    else:
        namespace_list = namespace.split('::')

    n_indents = len(namespace_list)

    def_code_with_ns  = ''
    def_code_with_ns += utils.constrNamespace(namespace_list,'open')
    def_code_with_ns += utils.addIndentation(def_code, cfg.indent*n_indents)
    def_code_with_ns += utils.constrNamespace(namespace_list,'close')


    # Return
    return def_code_with_ns

# ====== END: constrWrapperDef ========


# ======= constrWrapperSrc ========

def constrWrapperSrc(class_name, indent=' '*cfg.indent):
    src_code = ''

    #
    # For enumerations moved to the abstract class, redefinitions are needed in a source file
    #
    for abstr_type in gb.moved_to_abstract_class:
        if utils.getNamespaces(abstr_type)[-1] == class_name['short'] :
            # get the type
            abstr_type_dict = utils.findType(abstr_type)
            abstr_type_name = abstr_type_dict['name']
            abstr_type_enum_values = abstr_type_dict['enum_values']

            # Add code
            if abstr_type.tag in ['Enumeration'] :
                for val in abstr_type_enum_values :
                    src_code += 2*indent + "constexpr " + abstr_type_name + ' ' + class_name['wrp_short'] + '::' + val + ';\n'

                # Add this to a global variable to know whether we need to write the source file
                gb.needs_wrapper_source_file.append(class_name['wrp_short'])



    # Add namespace
    namespace, class_name_short = utils.removeNamespace(class_name['wrp_long'], return_namespace=True)

    if namespace == '':
        namespace_list = []
    else:
        namespace_list = namespace.split('::')

    n_indents = len(namespace_list)

    src_code_with_ns  = ''
    src_code_with_ns += utils.constrNamespace(namespace_list,'open')
    src_code_with_ns += utils.addIndentation(src_code, cfg.indent*n_indents)
    src_code_with_ns += utils.constrNamespace(namespace_list,'close')

    return src_code_with_ns


# ======= END: constrWrapperSrc ========



# ====== pureVirtualMembers ========

def pureVirtualMembers(class_el):

    # Return a list with the names of all pure virtual member functions of a class.

    check_member_elements = utils.getMemberElements(class_el)
    pure_virtual_members = []

    for mem_el in check_member_elements:
        if mem_el.tag in ['Constructor', 'Destructor', 'Method', 'OperatorMethod']:
            if ('pure_virtual' in mem_el.keys()) and (mem_el.get('pure_virtual')=='1'):
                pure_virtual_members.append(mem_el.get('name'))

    return pure_virtual_members

# ====== END: pureVirtualMembers ========



# ====== generateWrapperHeaderCode ========

# Generate a header file with a GAMBIT wrapper class.

def generateWrapperHeaderCode(class_el, class_name, namespaces, short_abstr_class_fname,
                          construct_assignment_operator, has_copy_constructor,
                          copy_constructor_id=''):

    # Useful variables
    indent = ' '*cfg.indent

    # Useful lists
    class_variables    = []
    class_functions    = getMemberFunctions(class_el, include_artificial=False, include_inherited=cfg.wrap_inherited_members,
                                                            only_accepted=True, limit_pointerness=True, include_operators=True)
    class_constructors = []
    class_operators = []
    class_members      = utils.getMemberElements(class_el, include_artificial=False)
    class_members_full = utils.getMemberElements(class_el, include_artificial=True)

    for mem_el in class_members:

        if (mem_el.tag in ('Field', 'Variable')) and (mem_el.get('access') == 'public'):
            if isAcceptedMemberVariable(mem_el):
                class_variables.append(mem_el)
        else:
            pass

    for mem_el in class_members_full:

        # Skip the copy constructor
        if has_copy_constructor and (mem_el.get('id') == copy_constructor_id):
            continue

        # Store constructor if acceptable
        if (mem_el.tag == 'Constructor') and (mem_el.get('access') == 'public'):
            class_constructors.append(mem_el)
        elif (mem_el.tag == 'OperatorMethod') and (mem_el.get('access') == 'public') and ('artificial' not in mem_el.keys()):
            class_operators.append(mem_el)

    # Create a list of dicts with info on the (loaded) parent classes
    loaded_parent_classes = utils.getParentClasses(class_el, only_loaded_classes=True)


    #
    # Start code generation
    #

    decl_code = constrWrapperDecl(class_el, class_name, loaded_parent_classes, class_variables, class_functions, class_constructors, class_operators, construct_assignment_operator, has_copy_constructor, indent=indent)
    def_code  = constrWrapperDef(class_el, class_name, loaded_parent_classes, class_variables, class_functions, class_constructors, construct_assignment_operator, has_copy_constructor, indent=indent, do_inline=True)

    # Insert tags for the GAMBIT namespace
    decl_code = '\n__START_GAMBIT_NAMESPACE__\n' + decl_code + '\n__END_GAMBIT_NAMESPACE__\n'
    def_code  = '\n__START_GAMBIT_NAMESPACE__\n' + def_code  + '\n__END_GAMBIT_NAMESPACE__\n'

    # Insert include statements needed by GAMBIT
    backend_undef_incl_statement  = '#include "' + os.path.join(gb.gambit_backend_incl_dir, 'backend_undefs.hpp') + '"\n'
    identification_incl_statement = '#include "' + 'identification.hpp' + '"\n'

    decl_code = identification_incl_statement + decl_code + '\n' + backend_undef_incl_statement
    def_code  = identification_incl_statement + def_code + '\n' + backend_undef_incl_statement



    #
    # Add #include statements for the declaration code
    #

    decl_code_include_statements = []

    # - Header where NULL is defined
    decl_code_include_statements.append( '#include <cstddef>' )

    # - If debug_mode, include <iostream> for some output
    if gb.debug_mode:
        decl_code_include_statements.append( '#include <iostream>' )

    # - Header with forward declarations to all wrapper classes
    decl_code_include_statements.append( '#include "' + gb.frwd_decls_wrp_fname + cfg.header_extension + '"')

    # - Base class for all wrapper classes
    decl_code_include_statements.append( '#include "' + os.path.join(gb.gambit_backend_incl_dir, 'wrapperbase.hpp') + '"')

    # - Abstract class for the original class
    decl_code_include_statements.append( '#include "' + gb.new_header_files[class_name['wrp_long']]['abstract'] + '"' )

    # - Wrapper parent classes
    for parent_dict in loaded_parent_classes:
        decl_code_include_statements.append('#include "' + gb.new_header_files[ parent_dict['class_name']['wrp_long'] ]['wrapper_decl'] + '"')

    # - Any other types (excluding the current wrapper class)
    decl_code_include_statements += utils.getIncludeStatements(class_el, convert_loaded_to='wrapper_decl', exclude_types=[class_name], use_full_path=False, forward_declared='exclude')

    # Remove duplicates and construct code
    decl_code_include_statements = list( OrderedDict.fromkeys(decl_code_include_statements) )
    decl_code_include_statements = utils.orderIncludeStatements(decl_code_include_statements)
    decl_include_statements_code = '\n'.join(decl_code_include_statements) + 2*'\n'
    decl_code = decl_include_statements_code + decl_code


    #
    # Add #include statements for the definition code
    #

    def_code_include_statements = []

    # - Any other types (excluding the current wrapper class)
    def_code_include_statements += utils.getIncludeStatements(class_el, convert_loaded_to='wrapper_decl', exclude_types=[class_name], use_full_path=False, forward_declared='include')

    # Remove duplicates and construct code
    def_code_include_statements = list( OrderedDict.fromkeys(def_code_include_statements) )
    def_code_include_statements = utils.orderIncludeStatements(def_code_include_statements)
    def_include_statements_code = '\n'.join(def_code_include_statements) + 2*'\n'
    def_code = def_include_statements_code + def_code


    # Return code
    return decl_code, def_code

# ====== END: generateWrapperHeaderCode ========


# ====== generateWrapperSourceCode ========

def generateWrapperSourceCode(class_el, class_name, namespaces) :

     # This generates a source file for the wrapper class that contains the redefinitions of static members of class, for compatibility with C++11/14

     # Useful variables
    indent = ' '*cfg.indent

    #
    # Start code generation
    #

    src_code = constrWrapperSrc(class_name, indent=indent)

    # Insert tags for the GAMBIT namespace
    src_code = '\n__START_GAMBIT_NAMESPACE__\n' + src_code + '\n__END_GAMBIT_NAMESPACE__\n'

    # Insert include statements needed by GAMBIT
    backend_undef_incl_statement  = '#include "' + os.path.join(gb.gambit_backend_incl_dir, 'backend_undefs.hpp') + '"\n'
    incl_statement = '#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.backend_types_basedir, gb.gambit_backend_name_full, gb.wrapper_header_prefix + class_name['short'] + cfg.header_extension) + '"\n'
    incl_statement += '#include "' + os.path.join(gb.gambit_backend_incl_dir, gb.backend_types_basedir, gb.gambit_backend_name_full, 'identification.hpp') + '"\n'



    src_code = incl_statement + src_code + '\n' + backend_undef_incl_statement

    # Return code
    return src_code

# ====== END: generateWrapperSourceCode



# ====== findClassNamePosition ========

# Find the position of a class name

def findClassNamePosition(class_el, file_content_nocomments):

    class_name = utils.getClassNameDict(class_el)

    # Find the index of the \n after the first line of the class declaration
    line_number = int(class_el.get('line'))
    newline_pos = utils.findNewLinePos(file_content_nocomments, line_number)

    # Find position of class name
    search_limit = newline_pos
    while search_limit > -1:
        class_name_pos = file_content_nocomments[:search_limit].rfind(class_name['short'])
        pre_char  = file_content_nocomments[class_name_pos-1]
        post_char = file_content_nocomments[class_name_pos+len(class_name['short'])]
        if (pre_char in [' ','\n','\t']) and (post_char in [' ', ':', '\n', '<', '{']):
            break
        else:
            search_limit = class_name_pos

    return class_name_pos

# ====== END: findClassNamePosition ========



# ====== findClassMemberPosition ========

# Find the position of a member of a class

def findClassMemberPosition(class_el, member_el, file_content_nocomments):

    # Find the position of a class
    class_pos = findClassNamePosition(class_el, file_content_nocomments)

    # Find the line the member is at
    file_content_list = file_content_nocomments.split('\n')
    member_line = int(member_el.get('line'))-1

    # Get the position in the file contents
    member_pos = file_content_nocomments[class_pos:].find(file_content_list[member_line])


    return class_pos + member_pos

# ====== END: findClassMemberPosition ========



# ====== isAcceptedMemberVariable ========

def isAcceptedMemberVariable(mem_el):

    is_accepted = True

    if not utils.isAcceptedType(mem_el):
        reason = "Non-accepted type."
        infomsg.IgnoredMemberVariable(mem_el.get('name'), reason).printMessage()
        is_accepted = False
        return is_accepted

    # Should this member be ditched?
    if 'name' in mem_el.keys():
        namespaces_list = utils.getNamespaces(mem_el, include_self=True)
        full_name = '::'.join(namespaces_list)
        if full_name in cfg.ditch:
            is_accepted = False
            return is_accepted

    # BOSS cannot yet handle member variables that are pointer-to-loaded-class.
    type_dict = utils.findType(mem_el)
    # type_name = type_dict['name']
    pointerness = type_dict['pointerness']

    if utils.isLoadedClass(mem_el) and pointerness > 0:
        reason = "BOSS cannot yet handle member variables of type pointer-to-loaded-class."
        infomsg.IgnoredMemberVariable(mem_el.get('name'), reason).printMessage()
        is_accepted = False
        return is_accepted

    return is_accepted

# ====== END: isAcceptedMemberVariable ========
