def isKnownClass(el, class_name=None):

    import modules.classutils as classutils

    is_known = False

    type_dict = findType(el)
    type_el = type_dict['el']

    # - Any known class should have a "name" XML entry
    if not 'name' in type_el.keys():
        is_known = False
        return is_known

    # Get class_name dict if it is not passed in as an argument
    if class_name is None:
        class_name = classutils.getClassNameDict(type_el)

    # Check if standard library class
    if isStdType(el, class_name=class_name):
        is_known = True
        return is_known

    # Check if listed among the user-specified known types
    if isInList(class_name['long_templ'], cfg.known_classes.keys(), return_index=False, ignore_whitespace=True):
        is_known = True
    elif isInList(class_name['long'], cfg.known_classes.keys(), return_index=False, ignore_whitespace=True):
        is_known = True

    # if not a is_known type
    if not is_known:
        return is_known
    else:
        if not is_templated:

    return is_known


def isFundamental(el):

    is_fundamental = False
    # TODO: ZELUN MARK add exception check of long, long long, short, short short, unsigned long, unsigned short
    if el.tag == 'FundamentalType':
        is_fundamental = True

    return is_fundamental


def isStdType(el, class_name=None):

    # Makes use of global variables:  base_paths

    is_std = False
    can_check_tags = ['Class', 'Struct', 'Union', 'Enumeration']

    if el.tag in can_check_tags:

        # Use the optional class_name dict?
        if class_name is not None:
            if len(class_name['long_templ']) >= 5:
                if class_name['long_templ'][0:5] == 'std::':
                    is_std = True

        elif 'name' in el.keys():
            namespaces_list = getNamespaces(el, include_self=True)
            if namespaces_list[0] == 'std':
                is_std = True

    else:
        is_std = False

    return is_std


def isLoadedClass(input_type, byname=False, class_name=None):

    is_loaded_class = False

    # If the class_name dict is passed as an argument, use it.
    if class_name is not None:

        if class_name['long_templ'] in cfg.load_classes:
            is_loaded_class = True

    else:

        if byname:
            type_name = input_type

            # Remove '*' and '&'
            type_name = type_name.replace('*', '').replace('&', '')

            # Remove template bracket
            type_name = type_name.split('<')[0]

            # Check against cfg.load_classes
            if type_name in cfg.load_classes:
                is_loaded_class = True

        else:
            type_dict = findType(input_type)
            type_el = type_dict['el']

            if type_el.tag in ['Class', 'Struct']:

                if type_dict['name'] in cfg.load_classes:
                    is_loaded_class = True

    return is_loaded_class


def isEnumeration(el):

    is_enumeration = False

    if el.tag == 'Enumeration':
        is_enumeration = True

    return is_enumeration


def initGlobalXMLdicts(xml_path, id_and_name_only=False):

    import modules.classutils as classutils
    import modules.funcutils as funcutils
    import modules.enumutils as enumutils

    # Clear dicts
    # clearGlobalXMLdicts()

    # Set some global dicts directly
    gb.id_dict = copy.deepcopy(gb.all_id_dict[xml_path])
    gb.name_dict = copy.deepcopy(gb.all_name_dict[xml_path])

    # Stop here?
    if id_and_name_only:
        return

    #
    # Loop over all elements in this xml file
    # to fill the remaining dicts. (The order is important!)
    #

    for xml_id, el in gb.id_dict.items():

        # Update global dict: file name --> file xml element
        if el.tag == 'File':
            gb.file_dict[el.get('name')] = el

        # Update global dict: std type --> type xml element
        if isStdType(el):
            class_name = classutils.getClassNameDict(el)
            gb.std_types_dict[class_name['long_templ']] = el

        # Update global dict of loaded classes in this xml file: class name --> class xml element
        if el.tag in ['Class', 'Struct']:

            try:
                class_name = classutils.getClassNameDict(el)
            except KeyError:
                continue

            # Check if we have done this class already
            if class_name in gb.classes_done:
                infomsg.ClassAlreadyDone(
                    class_name['long_templ']).printMessage()
                continue

            # Check that class is requested
            if (class_name['long_templ'] in cfg.load_classes):

                # Check that class is complete
                if isComplete(el):

                    # Store class xml element
                    gb.loaded_classes_in_xml[class_name['long_templ']] = el

        # Update global dict: typedef name --> typedef xml element
        if el.tag == 'Typedef':

            # Only accept native typedefs:
            if isNative(el):

                typedef_name = el.get('name')

                type_dict = findType(el)
                type_el = type_dict['el']

                # If underlying type is a fundamental or standard type, accept it right away
                if isFundamental(type_el) or isStdType(type_el):
                    gb.typedef_dict[typedef_name] = el

                # If underlying type is a class/struct, check if it's acceptable
                elif type_el.tag in ['Class', 'Struct']:

                    type_name = classutils.getClassNameDict(type_el)

                    if type_name['long_templ'] in cfg.load_classes:
                        gb.typedef_dict[typedef_name] = el

                # If neither fundamental or class/struct, ignore it.
                else:
                    pass

        # Create an enum dictionary
        if el.tag == 'Enumeration':

            # Only accept native enumerations
            if isNative(el):

                enum_name = enumutils.getEnumNameDict(el)

                # Only take enumerations that are not members of a class or a struct
                parent = gb.id_dict[el.get('context')]
                if parent.tag in ('Class', 'Struct'):
                    continue

                # Check if we have done this function already
                if enum_name in gb.enums_done:
                    infomsg.EnumAlreadyDone(enum_name['long']).printMessage()
                    continue

                # If the enum is in the requested list of loaded enums, add it to the dict
                if enum_name['long'] in cfg.load_enums:
                    gb.enum_dict[enum_name['long']] = el

        # Update global dict: function name --> function xml element
        if el.tag == 'Function':

            try:
                func_name = funcutils.getFunctionNameDict(el)
            except KeyError:
                continue

            # Check if we have done this function already
            if func_name in gb.functions_done:
                infomsg.FunctionAlreadyDone(
                    func_name['long_templ_args']).printMessage()
                continue

            if func_name['long_templ_args'] in cfg.load_functions:
                gb.func_dict[func_name['long_templ_args']] = el

        # Add entries to global dict: new header files
        if el in gb.loaded_classes_in_xml.values():

            class_name = classutils.getClassNameDict(el)

            class_name_short = class_name['short']
            class_name_long = class_name['long']

            if class_name_long not in gb.new_header_files.keys():

                abstract_header_name = gb.abstr_header_prefix + \
                    class_name_short + cfg.header_extension
                wrapper_header_name = gb.wrapper_header_prefix + \
                    class_name_short + cfg.header_extension
                wrapper_decl_header_name = gb.wrapper_header_prefix + \
                    class_name_short + '_decl' + cfg.header_extension
                wrapper_def_header_name = gb.wrapper_header_prefix + \
                    class_name_short + '_def' + cfg.header_extension

                abstract_header_fullpath = os.path.join(
                    gb.backend_types_basedir, gb.gambit_backend_name_full, gb.abstr_header_prefix + class_name_short + cfg.header_extension)
                wrapper_header_fullpath = os.path.join(
                    gb.backend_types_basedir, gb.gambit_backend_name_full, gb.wrapper_header_prefix + class_name_short + cfg.header_extension)
                wrapper_decl_header_fullpath = os.path.join(
                    gb.backend_types_basedir, gb.gambit_backend_name_full, gb.wrapper_header_prefix + class_name_short + '_decl' + cfg.header_extension)
                wrapper_def_header_fullpath = os.path.join(
                    gb.backend_types_basedir, gb.gambit_backend_name_full, gb.wrapper_header_prefix + class_name_short + '_def' + cfg.header_extension)

                gb.new_header_files[class_name_long] = {'abstract': abstract_header_name,
                                                        'wrapper': wrapper_header_name,
                                                        'wrapper_decl': wrapper_decl_header_name,
                                                        'wrapper_def': wrapper_def_header_name,
                                                        'abstract_fullpath': abstract_header_fullpath,
                                                        'wrapper_fullpath': wrapper_header_fullpath,
                                                        'wrapper_decl_fullpath': wrapper_decl_header_fullpath,
                                                        'wrapper_def_fullpath': wrapper_def_header_fullpath}

            if class_name_long not in gb.new_source_files.keys():

                wrapper_src_name = gb.wrapper_source_prefix + \
                    class_name_short + cfg.source_extension

                gb.new_source_files[class_name_long] = {
                    'wrapper': wrapper_src_name}


xml_file = 'BOSS_temp/ExampleBackend_1_234/tempfile_0_classes_hpp.xml'
