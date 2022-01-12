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

def recursiveTest(typeName, typeList):
    typeName = typeName.lstrip(' ').rstrip(' ')
    
    # Create required lists to store info
    stack = []
    bracketPairs = []
    commaLocs = []

    # For index and character in typeName
    for i, ch in enumerate(typeName):
        if ch == '<':
            # If it's an opening bracket append the index
            stack.append(i)
        elif ch == '>':
            # If it's a closing bracket,
            # assert that there's at least one corresponding opening bracket
            assert(len(stack) != 0)

            # Remove corresponding opening bracket and add it to pair
            # of brackets if it's the outermost bracket
            top = stack.pop()
            if len(stack) == 0:
                bracketPairs.append((top, i))
        elif ch == ',' and len(stack) == 0:
            # There's a comma outside of all the '<...>'
            commaLocs.append(i)

    # Again, assert that every opening bracket had a closing bracket
    assert(len(stack) == 0)

    if len(commaLocs) != 0:
        # If there are commas outside the brackets,
        # split the string based on the commas and try calling the function again
        commaLocs.append(len(typeName))
        prevComma = -1
        for comma in commaLocs:
            # seperatedType is the substring between the previous comma and this comma,
            # without the leading/lagging spaces
            seperatedType = typeName[prevComma + 1:comma]
            prevComma = comma
            
            # Call the function again on this substring
            recursiveTest(seperatedType, typeList)
    else:
        # There were no annoying commas, search deeper into the next bracket.
        # If you think about it, there can be at most 1 pair of bracket here.
        if not typeName.isdigit():
            typeList.append(typeName)
        
        # Iterate through each bracket and search them
        for (lo, hi) in bracketPairs:
            insideBrackets = typeName[lo + 1:hi]
            recursiveTest(insideBrackets, typeList)

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
    recursiveTest('std::map<std::vector<int>, std::pair<std::string, bool>>', list4)
    print(list4)
    print()
    print("--------------------------------")
    print()

    
    list5 = []
    print('All types in std::array<int, 3>')
    recursiveTest('std::array<int, 3>', list5)
    print(list5)
    print()
    print("--------------------------------")
    print()

    

    
    list6 = []
    print('All types in   std::vector<   int  >   ')
    recursiveTest('  std::vector<   int  >   ', list6)
    print(list6)
    print()
    print("--------------------------------")
    print()

    
    
    list7 = []
    print('All types in std::map < bool                          ,  char  >  ')
    recursiveTest('std::map < bool                          ,  char  >  ', list7)
    print(list7)
    print()
    print("--------------------------------")
    print()

    

    list8 = []
    print('All types in std::array<  std::vector< std::map<std::pair<bool,   std::string>,some_templated_type<T ,char>>>,3>')
    recursiveTest('std::array<  std::vector< std::map<std::pair<bool,   std::string>,some_templated_type<T ,char>>>,3>', list8)
    print(list8)
    print()
    print("--------------------------------")
    print()

