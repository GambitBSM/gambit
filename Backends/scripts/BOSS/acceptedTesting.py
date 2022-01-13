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
"""

def isEnumeration(el):
    return el.tag == 'Enumeration'

def isFundamental(el):
    has_fundamental_tag = (el.tag == 'FundamentalType')
    is_exception = (el.attrib['name'] in ('long', 'long long', 'short', 'short short', 'unsigned long', 'unsigned short'))
    return has_fundamental_tag or is_exception


def findOutsideBracketsAndCommas(string, bracketLocs, commaLocs):
    stack = []
    # For index and character in typeName
    for i, ch in enumerate(string):
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
                bracketLocs.append((top, i))
        elif ch == ',' and len(stack) == 0:
            # There's a comma outside of all the '<...>'
            commaLocs.append(i)

    # Again, assert that every opening bracket had a closing bracket
    assert(len(stack) == 0)


def removeCharsInRange(string, lo, hi):
    assert(lo <= hi and lo >= 0 and hi < len(string))
    return string[0:lo] + string[hi + 1:]


def removeThisSpace(ch1, ch2):
    return (ch1 in ('<', '>', ',')) or (ch2 in ('<', '>', ','))


def isAcceptedType(typeName):
    return typeName in ('int', 'std::vector', 'bool', 'char', 'std::map')


def stripWhitespace(string):
    # Strip the whitespace to the left and right
    string = string.lstrip(' ').rstrip(' ')

    # Return if empty
    if string == '':
        return ''

    # Now have a non-empty string with no leading
    # or lagging spaces
    unnecessarySpaces = True
    while unnecessarySpaces:
        unnecessarySpaces = False
        lastNonSpaceIndex = 0
        lastNonSpaceCharacter = string[0]
        for i, ch in enumerate(string):
            if ch != ' ':
                # Check if the last non-space
                # and now has anything between it
                if i - lastNonSpaceIndex > 1 and removeThisSpace(ch, lastNonSpaceCharacter):
                    # Must remove the middle bit
                    string = removeCharsInRange(
                        string, lastNonSpaceIndex + 1, i - 1)
                    unnecessarySpaces = True
                    break

                # Update the new indexes
                lastNonSpaceIndex = i
                lastNonSpaceCharacter = ch

    return string


def recursiveTest(typeName):
    # Need a function to strip
    typeName = stripWhitespace(typeName)
    print(f"recursiveTest called on and filtered to: {typeName}")

    # Create required lists to store info
    typeNameBracketLocs = []
    typeNameCommaLocs = []
    findOutsideBracketsAndCommas(
        typeName, typeNameBracketLocs, typeNameCommaLocs)

    # If there are more than 1 angle brackets pair on the outermost level
    # OR there are any commas outside angle brackets there's a problem
    assert(len(typeNameBracketLocs) <= 1)
    assert(len(typeNameCommaLocs) == 0)

    if (len(typeNameBracketLocs) == 0):
        # Not templated
        print(f"{typeName} isn't templated, stop here")
        return isAcceptedType(typeName)
    else:
        # Is templated
        # Grab the locations of the outer brackets
        (lo, hi) = typeNameBracketLocs[0]
        strippedType = typeName[:lo]

        print(f"{strippedType} is templated, go deeper")

        if not isAcceptedType(strippedType):
            return False

        insideBrackets = typeName[lo + 1:hi]

        # Strip the commas between insideBrackets if there are any,
        # E.g., if typeName = 'std::map<int, bool>'
        # insideBrackets = 'int, bool'
        # We want to separate it into 'int' and 'bool' before we go any deeper
        insideBracketsBracketLocs = []
        insideBracketsCommaLocs = []
        findOutsideBracketsAndCommas(
            insideBrackets, insideBracketsBracketLocs, insideBracketsCommaLocs)

        insideBracketsCommaLocs.append(len(insideBrackets))
        prevComma = -1
        for comma in insideBracketsCommaLocs:
            # For each comma, get the substring between this comma and the last one
            # and strip it for leading/lagging whitespace.
            # Then, add it to the list of section
            section = insideBrackets[prevComma + 1:comma]
            prevComma = comma

            # Recurse through each section unless it's a digit
            # E.g., typeName = 'std::array<int, 3>'
            # insideBrackets = 'int, 3'
            # The first section = 'int', which we want to recurse on
            # Second section = '3', which isn't a type so we don't want to recurse on
            if not section.isdigit() and not recursiveTest(section):
                return False

        return True

<<<<<<< HEAD
# std::vector<long int,bool>
# 'const wchar_t *'
# 'char const (&)[44]'

=======
>>>>>>> 2b5b019387850bed298cfbd618d6acf26292780e

if __name__ == '__main__':
    print('All types in int')
    print(recursiveTest('int'))
    print()
    print("--------------------------------")
    print()

    print('All types in std::vector<int>')
    print(recursiveTest('std::vector<int>'))
    print()
    print("--------------------------------")
    print()

    print('All types in std::map<std::vector<int>, bool>')
    print(recursiveTest('std::map<std::vector<int>, bool>'))
    print()
    print("--------------------------------")
    print()

    print('All types in std::map<std::vector<int>, std::pair<std::string, bool>>')
    print(recursiveTest('std::map<std::vector<int>, std::pair<std::string, bool>>'))
    print()
    print("--------------------------------")
    print()

    print('All types in std::array<int, 3>')
    print(recursiveTest('std::array<int, 3>'))
    print()
    print("--------------------------------")
    print()

    print('All types in   std::vector<   int  >   ')
    print(recursiveTest('  std::vector<   int  >   '))
    print()
    print("--------------------------------")
    print()

    print('All types in std::map < bool                          ,  char  >  ')
    print(recursiveTest('std::map < bool                          ,  char  >  '))
    print()
    print("--------------------------------")
    print()

    print('All types in std::array<  std::vector< std::map<std::pair<bool,   std::string>,some_templated_type<T ,char>>>,3>')
    print(recursiveTest(
        'std::array<  std::vector< std::map<std::pair<bool,   std::string>,some_templated_type<T ,char>>>,3>'))
    print()
    print("--------------------------------")
    print()
