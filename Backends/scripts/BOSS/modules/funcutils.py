####################################
#                                  #
#  Utility functions for handling  # 
#  C++ functions with BOSS         #
#                                  #
####################################

from __future__ import print_function
from collections import OrderedDict
import copy

import modules.active_cfg as active_cfg
exec("import configs." + active_cfg.module_name + " as cfg")

import modules.gb as gb
import modules.utils as utils
import modules.infomsg as infomsg


# ======== getArgs ========

def getArgs(func_el):
    
    #
    # Returns a list with one dict per argument.
    # Each dict contains the following keywords:
    # 
    #   'name', 'type', 'kw', 'id', 'native', 'fundamental', 'enumeration', 'loaded_class',
    #   'known_class', 'type_namespaces', 'default', 'function_pointer'
    #

    args = []
    argc = 1
    for sub_el in func_el.getchildren():
        if sub_el.tag == 'Argument':

            arg_dict = OrderedDict()
            if 'name' in sub_el.keys():
                arg_dict['name'] = sub_el.get('name')
            else:
                arg_dict['name'] = 'arg_' + str(argc)
                argc += 1

            arg_type_dict = utils.findType(sub_el)
            pointerness = arg_type_dict['pointerness']
            is_ref      = arg_type_dict['is_reference']
            arg_kw      = arg_type_dict['cv_qualifiers']
            arg_id      = arg_type_dict['id']
            arg_type_el = arg_type_dict['el']
            is_func_ptr = arg_type_dict['is_function_pointer']

            arg_type = arg_type_dict['name'] + '*'*pointerness + '&'*is_ref

            arg_dict['type'] = arg_type
            arg_dict['kw'] = arg_kw
            arg_dict['id'] = arg_id
            arg_dict['function_pointer'] = is_func_ptr

            arg_dict['native']      = utils.isNative(arg_type_el)
            arg_dict['fundamental'] = utils.isFundamental(arg_type_el)
            arg_dict['enumeration'] = utils.isEnumeration(arg_type_el)
            arg_dict['loaded_class'] = utils.isLoadedClass(arg_type_el)
            arg_dict['known_class'] = utils.isKnownClass(arg_type_el)
            arg_dict['type_namespaces'] = utils.getNamespaces(arg_type_el)

            if 'default' in sub_el.keys():
                arg_dict['default'] = True
            else:
                arg_dict['default'] = False

            args.append(arg_dict)

    return args

# ======== END: getArgs ========



# ======== constrArgsBracket ========

def constrArgsBracket(args, include_arg_name=True, include_arg_type=True, include_namespace=False,
                      cast_to_original=False, use_wrapper_class=False, wrapper_to_pointer=False, 
                      add_namespace_to_loaded=''):

    #
    # Requires a list of dicts as input, as returned by 'getArgs' or 'constrWrapperArgs'.
    #

    import modules.classutils as classutils

    # Construct bracket with input arguments
    args_seq = ''
    argc = 1
    for i in range(len(args)):

        # We must create a new copy since we may be altering the content later
        arg_dict = OrderedDict(args[i])

        if arg_dict['loaded_class'] and (add_namespace_to_loaded != ''):
            add_namespaces = add_namespace_to_loaded.split('::')
            arg_dict['type_namespaces'] = add_namespaces + arg_dict['type_namespaces']
            arg_dict['type'] = add_namespace_to_loaded + '::' + arg_dict['type']

        if include_arg_name and cast_to_original:

            if arg_dict['loaded_class']:

                # We assume that arg_dict['type'] *is* the original type!
                cast_to_type = arg_dict['type']
        
                if include_namespace:
                    namespaces = arg_dict['type_namespaces']
                    if len(namespaces)>0:
                        cast_to_type = '::'.join(namespaces) + '::' + cast_to_type

                # If argument type is not pointer or reference, add a reference operator '&'
                check_type = cast_to_type.split('<')[0]
                if ('*' not in check_type) and ('&' not in check_type):
                    cast_to_type = cast_to_type + '&'

                # Add qualifiers
                if len(arg_dict['kw']) > 0:
                    qualifiers = ' '.join(arg_dict['kw'])
                    cast_to_type = qualifiers + ' ' + cast_to_type

                # Determine what argument name to use (arg_name or *arg_name.get_BEptr() or ...)
                if wrapper_to_pointer:
                    if arg_dict['type'].count('*') == 0:
                        use_name = '*' + arg_dict['name'] + '.get_BEptr()'
                    elif arg_dict['type'].count('*') == 1:
                        use_name = '(*' + arg_dict['name'] + ')' + '.get_BEptr()'
                    args_seq += 'dynamic_cast< ' + cast_to_type + ' >(' + use_name + ')'
                else:
                    args_seq += 'dynamic_cast< ' + cast_to_type + ' >(' + arg_dict['name'] + ')'

            else:

                args_seq += arg_dict['name']


        else:
            if include_arg_type:
                args_seq += ''.join([ kw+' ' for kw in arg_dict['kw'] ])

                if use_wrapper_class and arg_dict['loaded_class'] == True:
                    args_seq += classutils.toWrapperType(arg_dict['type'], include_namespace=include_namespace)

                else:
                    if include_namespace:
                        # If known class, add '::' for absolute namespace
                        if arg_dict['known_class']:
                            args_seq += '::' + arg_dict['type']                       
                        else:
                            args_seq += arg_dict['type']
                    else:
                        args_seq += utils.removeNamespace(arg_dict['type'])

            if include_arg_type and include_arg_name:
                args_seq += ' '

            if include_arg_name:
                if utils.isLoadedClass(arg_dict['type'], byname=True) and wrapper_to_pointer:
                    if arg_dict['type'].count('*') == 0:
                        args_seq += '*' + arg_dict['name'] + '.get_BEptr()'
                    elif arg_dict['type'].count('*') == 1:
                        args_seq += '(*' + arg_dict['name'] + ')' + '.get_BEptr()'
                    else:
                        raise Exception('funcutils.constrArgsBracket cannot presently deal with arguments of type pointer-to-pointer for wrapper classes.')
                else:
                    args_seq += arg_dict['name']

        args_seq += ', '

    args_seq = args_seq.rstrip(', ')
    args_seq = args_seq.strip()
    args_bracket = '(' + args_seq + ')'

    return args_bracket

# ======== END: constrArgsBracket ========



# ======== constrWrapperName ========

def constrWrapperName(func_el, include_full_namespace=True):

    # Check if this is an operator function
    is_operator = False
    if func_el.tag == 'OperatorMethod':
        is_operator = True

    func_name_short = func_el.get('name')

    if is_operator:
        w_func_name = 'operator_' + gb.operator_names[func_name_short] + gb.code_suffix
    else:
        w_func_name = func_name_short + gb.code_suffix

    if include_full_namespace:
        namespaces = utils.getNamespaces(func_el)
        if len(namespaces) > 0:
            w_func_name = '::'.join(namespaces) + '::' + w_func_name

    return w_func_name

# ======== END: constrWrapperName ========



# ======== constrWrapperArgs ========

def constrWrapperArgs(args, add_ref=False, convert_loaded_to_abstract=True):

    #
    # Requires a list of dicts as input, as returned by 'getArgs'.
    #

    import modules.classutils as classutils

    # Copy input list
    w_args = copy.deepcopy(args) 

    # The dict entry 'id' does not make sense for arguments that are translated from 
    # native to abstract type
    for arg_dict in w_args:
        del arg_dict['id']

    for arg_dict in w_args:
        if arg_dict['native'] and not arg_dict['enumeration']:
            if arg_dict['loaded_class']:

                if convert_loaded_to_abstract:
                    arg_dict['type'] = classutils.toAbstractType(arg_dict['type'])

                if add_ref:
                    if ('&' not in arg_dict['type']) and ('*' not in arg_dict['type']):
                        arg_dict['type'] = arg_dict['type'] + '&'

            # else:
            #     print('INFO: ' + 'The argument "%s" is of a native type "%s" that BOSS is not parsing. The function using this should be ignored.' % (arg_dict['name'], arg_dict['type']))

    return w_args

# ======== END: constrWrapperArgs ========



# ======== constrDeclLine ========

def constrDeclLine(return_type, func_name, args_bracket, keywords=[], is_const=False):

    decl_line = ''
    for keyw in keywords: 
        decl_line += keyw + ' '
    decl_line += return_type + ' ' + func_name + args_bracket

    if is_const:
        decl_line = decl_line + ' const'

    return decl_line

# ======== END: constrDeclLine ========




# ======== constrWrapperBody ========

def constrWrapperBody(return_type, func_name, args, return_is_loaded_class, keywords=[]):

    #
    # Input:
    # 
    #   - Return type of original function
    #   - List of dicts for original arguments
    #   - Name of original function
    #   - Boolean stating whether the orignal return type is native

    # Pointer and reference check
    pointerness, is_ref = utils.pointerAndRefCheck(return_type, byname=True)

    # Generate bracket for calling original function
    args_bracket_notypes = constrArgsBracket(args, include_arg_type=False, cast_to_original=True)

    w_func_body = ''
    w_func_body += '{\n'

    w_func_body += ' '*cfg.indent
    
    if return_type == 'void':
        w_func_body += func_name + args_bracket_notypes + ';\n'

    else:
        w_func_body += 'return '

        use_return_type = return_type
        if is_ref:
            use_return_type = return_type.rstrip('&')

        # The 'new SomeType'-statement should have one less '*' than the return type
        use_return_type.rstrip('*')

        if return_is_loaded_class:
            if is_ref:
                w_func_body += func_name + args_bracket_notypes + ';\n'
            elif (not is_ref) and (pointerness > 0):
                w_func_body += func_name + args_bracket_notypes + ';\n'
            else:
                w_func_body += 'new ' + use_return_type + '(' + func_name + args_bracket_notypes + ');\n'
        else:
            w_func_body += func_name + args_bracket_notypes + ';\n'

    w_func_body += '}'

    return w_func_body

# ======== END: constrWrapperBody ========



# ======== ignoreFunction ========

def ignoreFunction(func_el, limit_pointerness=False, remove_n_args=0, print_warning=True):

    # TODO: When BOSS starts accepting template functions, add a check for the template arguments

    import modules.classutils as classutils

    func_name = getFunctionNameDict(func_el)

    # Should this function be ditched?
    if func_name['long_templ_args'] in cfg.ditch:
        return True

    # Ignore templated functions (BOSS cannot deal with that yet...)
    if utils.isTemplateFunction(func_el):
        if print_warning:
            reason = "Templated function. BOSS cannot deal with this yet."
            infomsg.IgnoredFunction(func_name['long_templ_args'], reason).printMessage()
        return True


    # Check if this is an operator function
    is_operator = False
    if func_el.tag == 'OperatorMethod':
        is_operator = True



    # Check function return type
    if 'returns' in func_el.keys():
        return_type_dict = utils.findType(func_el)
        return_type = return_type_dict['name'] + '*'*return_type_dict['pointerness'] + '&'*return_type_dict['is_reference']
        return_el   = return_type_dict['el']  
        if not utils.isAcceptedType(return_el):
            if print_warning:
                reason = "Non-accepted return type '%s'." % return_type
                infomsg.IgnoredFunction(is_operator*'operator'+func_name['long_templ_args'], reason).printMessage()
            return True 


    # Check argument types
    arg_types_accepted = True
    args = getArgs(func_el)

    use_n_args = len(args) - remove_n_args
    
    if remove_n_args > 0:
        args = args[:-remove_n_args]

    for arg_dict in args:
        arg_type_name = arg_dict['type']
        arg_el = gb.id_dict[arg_dict['id']]

        # Find out if argument type is base type of any accepted type
        is_parent_of_accepted= False
        if utils.isNative(arg_el):
            arg_class_name = classutils.getClassNameDict(arg_el)
            if arg_class_name['long_templ'] in gb.parents_of_loaded_classes:
                is_parent_of_accepted = True


        if arg_dict['function_pointer']:
            if print_warning:
                reason = "Function pointer type argument, '%s'." % arg_dict['name']
                infomsg.IgnoredFunction(is_operator*'operator'+func_name['long_templ_args'], reason).printMessage()
            arg_types_accepted = False
            break
        if (not utils.isAcceptedType(arg_el)):  # and (not is_parent_of_accepted):
            if print_warning:
                reason = "Non-accepted argument type '%s'." % arg_type_name
                infomsg.IgnoredFunction(is_operator*'operator'+func_name['long_templ_args'], reason).printMessage()
            arg_types_accepted = False
            break
        if limit_pointerness == True:
            if utils.isLoadedClass(arg_el):
                if ('**' in arg_type_name) or ('*&' in arg_type_name):
                    if print_warning:
                        reason = "Argument of type pointer-to-pointer/reference-to-pointer to loaded class, '%s'." % arg_type_name
                        infomsg.IgnoredFunction(is_operator*'operator'+func_name['long_templ_args'], reason).printMessage()
                    arg_types_accepted = False
                    break
    if (not arg_types_accepted):
        return True

    # Function accepted (i.e. should *not* be ignored)
    return False 

# ======== END: ignoreFunction ========


# # ======== getFunctionTemplateBracket ========

# def getFunctionTemplateBracket(func_el):

#     #
#     #
#     #  TODO: everything!
#     #
#     #

# # ======== END: getFunctionTemplateBracket ========



# ======== usesNativeType ========

def usesNativeType(func_el):

    uses_native_type = False

    return_type_dict = utils.findType(func_el)
    return_is_native = utils.isNative( return_type_dict['el'] )

    args = getArgs(func_el)
    is_arg_native = [arg_dict['native'] for arg_dict in args]

    if (return_is_native) or (True in is_arg_native):
        uses_native_type = True

    return uses_native_type

# ======== END: usesNativeType ========



# ======== usesLoadedType ========

def usesLoadedType(func_el):

    uses_loaded_type = False

    return_type_dict = utils.findType(func_el)
    return_is_loaded = utils.isLoadedClass( return_type_dict['el'] )

    args = getArgs(func_el)
    is_arg_loaded = [arg_dict['loaded_class'] for arg_dict in args]

    if (return_is_loaded) or (True in is_arg_loaded):
        uses_loaded_type = True

    return uses_loaded_type

# ======== END: usesLoadedType ========



# ======== numberOfDefaultArgs ========

def numberOfDefaultArgs(func_el):

    n_def_args = 0

    args = getArgs(func_el)
    for arg_dict in args:
        if arg_dict['default']:
            n_def_args += 1

    return n_def_args

# ======== END: numberOfDefaultArgs ========



# ======== constrExternFuncDecl ========

def constrExternFuncDecl(func_el):

    extern_decl = ''

    return_type_dict = utils.findType( gb.id_dict[func_el.get('returns')] )
    return_type = return_type_dict['name'] + '*'*return_type_dict['pointerness'] + '&'*return_type_dict['is_reference']

    func_name = getFunctionNameDict(func_el)

    namespaces = utils.getNamespaces(func_el)
    n_indents = len(namespaces)

    extern_decl += utils.constrNamespace(namespaces, 'open')
    extern_decl += ' '*cfg.indent*n_indents + 'extern ' + return_type + ' ' + func_name['short_templ_args'] + ';\n'
    extern_decl += utils.constrNamespace(namespaces, 'close')

    return extern_decl

# ======== END: constrExternFuncDecl ========



# ====== getFunctionNameDict ========

def getFunctionNameDict(func_el):

    func_name = OrderedDict()

    # Check that the 'name' XML entry exists.
    xml_id = func_el.get('id')
    if 'name' not in func_el.keys():
        raise KeyError('XML element %s does not contain the key "name".' % (xml_id))

    # Get information about the return type.
    return_type_dict = utils.findType(func_el)
    return_el     = return_type_dict['el']
    pointerness   = return_type_dict['pointerness']
    is_ref        = return_type_dict['is_reference']
    return_kw     = return_type_dict['cv_qualifiers']
    
    return_kw_str = ' '.join(return_kw) + ' '*bool(len(return_kw))

    return_type   = return_type_dict['name'] + '*'*pointerness + '&'*is_ref

    # Get information about the arguments
    args = getArgs(func_el)


    #
    # Start filling the name dict
    #
    
    func_name['short_templ'] = func_el.get('name')

    namespaces_list = utils.getNamespaces(func_el, include_self=True)
    func_name['long_templ'] = '::'.join(namespaces_list)

    func_name['short'], template_bracket = utils.removeTemplateBracket(func_name['short_templ'], return_bracket=True)
    func_name['long'], template_bracket = utils.removeTemplateBracket(func_name['long_templ'], return_bracket=True)

    # Construct argument bracket
    args_bracket = constrArgsBracket(args, include_arg_name=False, include_arg_type=True, include_namespace=True)
    func_name['long_templ_args'] = func_name['long_templ'] + args_bracket

    # Add return type
    func_name['long_templ_return_args'] = return_type + ' ' + func_name['long_templ_args']

    return func_name

# ====== END: getFunctionNameDict ========
