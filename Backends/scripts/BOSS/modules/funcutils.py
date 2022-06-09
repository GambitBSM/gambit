####################################
#                                  #
#  Utility functions for handling  #
#  C++ functions with BOSS         #
#                                  #
####################################

from __future__ import print_function
from collections import OrderedDict
import copy
import modules.infomsg as infomsg
import modules.utils as utils
import modules.gb as gb
import modules.active_cfg as active_cfg

exec("import configs." + active_cfg.module_name + " as cfg")


# ======== constrWrapperName ========

def constrWrapperName(func_el, include_full_namespace=True):

    # Check if this is an operator function
    is_operator = (func_el.tag == 'OperatorMethod')

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

    # Copy input list
    w_args = copy.deepcopy(args)

    # The dict entry 'id' does not make sense for arguments that are translated from
    # native to abstract type
    for arg_dict in w_args:
        if 'id' in arg_dict:
            del arg_dict['id']

    for arg_dict in w_args:
        unpacked_template_args = utils.getAllTemplateTypes(arg_dict['type'])
        if not arg_dict['enumeration'] and (arg_dict['loaded_class']  or arg_dict['uses_loaded_class']):

                if convert_loaded_to_abstract:
                    arg_dict['type'] = utils.toAbstractType(arg_dict['type'])

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
        decl_line += ' const'

    return decl_line

# ======== END: constrDeclLine ========


# ======== constrWrapperBody ========

def constrWrapperBody(return_type, func_name, args, return_is_loaded_class):
    # Input:
    #   - Return type of original function
    #   - List of dicts for original arguments
    #   - Name of original function
    #   - Boolean stating whether the orignal return type is native

    # Pointer and reference check
    pointerness, is_ref = utils.pointerAndRefCheck(return_type, byname=True)

    # Generate bracket for calling original function
    args_bracket_notypes = utils.constrArgsBracket(args, include_arg_type=False, cast_to_original=True)

    w_func_body = ''
    w_func_body += '{\n'

    w_func_body += ' ' * cfg.indent

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
    func_name = utils.getFunctionNameDict(func_el)

    # Should this function be ditched?
    if func_name['long_templ_args'] in cfg.ditch:
        return True

    # TODO: When BOSS starts accepting template functions, add a check for the template arguments
    # TODO: TG: Checking that the template arguments are not ignored and they are accepted types
    if utils.isTemplateFunction(func_el):
        spec_template_types = utils.getSpecTemplateTypes(func_el)
        for template_type in spec_template_types:
            if template_type in cfg.ditch or template_type not in gb.accepted_types:
                return True

    # Ignore templated functions (BOSS cannot deal with that yet...)
    # TODO: TG: We kind of do now
    # if utils.isTemplateFunction(func_el):
    #    if print_warning:
    #        reason = "Templated function. BOSS cannot deal with this yet."
    #        infomsg.IgnoredFunction(func_name['long_templ_args'], reason).printMessage()
    #    return True

    # Check if this is an operator function
    is_operator = (func_el.tag == 'OperatorMethod')

    # Check function return type
    if 'returns' in func_el.keys():
        return_type_dict = utils.findType(func_el)
        return_type = return_type_dict['name'] + \
            '*' * return_type_dict['pointerness'] + \
            '&' * return_type_dict['is_reference']
        return_el = return_type_dict['el']
        if not utils.isAcceptedType(return_el):
            if print_warning:
                reason = f"Non-accepted return type '{return_type}'."
                infomsg.IgnoredFunction(is_operator*'operator'+func_name['long_templ_args'], reason).printMessage()
            return True

    # Check argument types
    args = utils.getArgs(func_el)

    # use_n_args = len(args) - remove_n_args

    if remove_n_args > 0:
        args = args[:-remove_n_args]

    for arg_dict in args:
        arg_type_name = arg_dict['type']
        arg_el = gb.id_dict[arg_dict['id']]

        # Find out if argument type is base type of any accepted type

        # Commented out some parts because is_parent_of_accepted and arg_class_name are never used
        # is_parent_of_accepted = False
        # if utils.isNative(arg_el):
            # arg_class_name = utils.getClassNameDict(arg_el)
            # if arg_class_name['long_templ'] in gb.parents_of_loaded_classes:
                # is_parent_of_accepted = True

        if arg_dict['function_pointer']:
            if print_warning:
                reason = f"Function pointer type argument, '{arg_dict['name']}'."
                infomsg.IgnoredFunction(is_operator*'operator'+func_name['long_templ_args'], reason).printMessage()
            return True

        # and (not is_parent_of_accepted):
        if not utils.isAcceptedType(arg_el):
            if print_warning:
                reason = "Non-accepted argument type '%s'." % arg_type_name
                infomsg.IgnoredFunction(is_operator*'operator'+func_name['long_templ_args'], reason).printMessage()
            return True

        if limit_pointerness and utils.isLoadedClass(arg_el) and (('**' in arg_type_name) or ('*&' in arg_type_name)):
            if print_warning:
                reason = "Argument of type pointer-to-pointer/reference-to-pointer to loaded class, '%s'." % arg_type_name
                infomsg.IgnoredFunction(is_operator*'operator'+func_name['long_templ_args'], reason).printMessage()
            return True

    # Function accepted (i.e. should *not* be ignored)
    return False

# ======== END: ignoreFunction ========


# # ======== getFunctionTemplateBracket ========

# def getFunctionTemplateBracket(func_el):

#     #
#     #
#     # TODO: everything!
#     #
#     #

# # ======== END: getFunctionTemplateBracket ========


# ======== usesNativeType ========

def usesNativeType(func_el):
    return_type_dict = utils.findType(func_el)
    return_is_native = utils.isNative(return_type_dict['el'])

    args = utils.getArgs(func_el)
    is_arg_native = [arg_dict['native'] for arg_dict in args]

    return (return_is_native) or (True in is_arg_native)

# ======== END: usesNativeType ========


# ======== usesLoadedType ========

def usesLoadedType(func_el):
    return_type_dict = utils.findType(func_el)
    return_is_loaded = utils.isLoadedClass(return_type_dict['el'])
    return_uses_loaded = utils.usesLoadedClass(return_type_dict['el'])

    args = utils.getArgs(func_el)
    args_are_loaded = False
    for arg_dict in args:
      args_are_loaded = args_are_loaded or arg_dict['loaded_class'] or arg_dict['uses_loaded_class']

    return (return_is_loaded) or (return_uses_loaded) or (args_are_loaded)

# ======== END: usesLoadedType ========


# ======== numberOfDefaultArgs ========

def numberOfDefaultArgs(func_el):
    n_def_args = 0

    args = utils.getArgs(func_el)
    for arg_dict in args:
        if arg_dict['default']:
            n_def_args += 1

    return n_def_args

# ======== END: numberOfDefaultArgs ========


# ======== constrExternFuncDecl ========

def constrExternFuncDecl(func_el):
    extern_decl = ''

    return_type_dict = utils.findType(gb.id_dict[func_el.get('returns')])
    return_type = return_type_dict['name'] + \
        '*' * return_type_dict['pointerness'] + \
        '&' * return_type_dict['is_reference']

    func_name = utils.getFunctionNameDict(func_el)

    namespaces = utils.getNamespaces(func_el)
    n_indents = len(namespaces)

    extern_decl += utils.constrNamespace(namespaces, 'open')
    extern_decl += ' ' * cfg.indent * n_indents + 'extern ' + \
        return_type + ' ' + func_name['short_templ_args'] + ';\n'
    extern_decl += utils.constrNamespace(namespaces, 'close')

    return extern_decl

# ======== END: constrExternFuncDecl ========


