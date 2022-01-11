"""
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
"""

# Function assumes a valid input


def topBracketLevels(string):
    stack = []
    bracketPairs = []
    for i, c in enumerate(string):
        if c == '<':
            stack.append(i)
        elif c == '>':
            assert(len(stack) != 0)

            top = stack.pop()
            if len(stack) == 0:
                # This was the outermost pair, add them to my list of brackets
                bracketPairs.append((top, i))

    assert(len(stack) == 0)

    return bracketPairs


def recursiveTest(typeName, typeList):
    stack = []
    bracketPairs = []
    commaLocs = []
    for i, c in enumerate(typeName):
        if c == '<':
            stack.append(i)
        elif c == '>':
            assert(len(stack) != 0)

            top = stack.pop()
            if len(stack) == 0:
                # This was the outermost pair, add them to my list of brackets
                bracketPairs.append((top, i))
        elif c == ',' and len(stack) == 0:
            # There's a comma outside of '<...>'
            commaLocs.append(i)

    numBracketPairs = len(bracketPairs)
    assert(len(stack) == 0)

    if len(commaLocs) != 0:
        prevComma = -1
        for comma in commaLocs:
            seperatedType = typeName[prevComma +
                                     1:comma].lstrip(' ').rstrip(' ')
            recursiveTest(seperatedType, typeList)
        seperatedType = typeName[commaLocs[-1] + 1:].lstrip(' ').rstrip(' ')
        recursiveTest(seperatedType, typeList)
    else:
        typeList.append(typeName)
        # Iterate through each bracket and search them
        for (lo, hi) in bracketPairs:
            recursiveTest(typeName[lo + 1:hi], typeList)


if __name__ == '__main__':
    list1 = []
    print('All types in int')
    recursiveTest('int', list1)
    print(list1)
    print()
    print("--------------------------------")
    print()

    list2 = []
    print('All types in std::vector<int>')
    recursiveTest('std::vector<int>', list2)
    print(list2)
    print()
    print("--------------------------------")
    print()

    list3 = []
    print('All types in std::map<std::vector<int>, bool>')
    recursiveTest('std::map<std::vector<int>, bool>', list3)
    print(list3)
    print()
    print("--------------------------------")
    print()

    list4 = []
    print('All types in std::map<std::vector<int>, std::pair<std::string, bool>>')
    recursiveTest(
        'std::map<std::vector<int>, std::pair<std::string, bool>>', list4)
    print(list4)
    print()
    print("--------------------------------")
    print()
