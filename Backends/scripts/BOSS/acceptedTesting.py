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


import re


def isEnumeration(el):
    # Check if castxml has tagged it as an enumeration
    return el.tag == 'Enumeration'


def isFundamental(el):
    # Check if either castxml has correctly tagged it as fundamental
    # OR it's missed it and it's fundamental since it treats for example,
    # 'long' and 'long int' as different things (even though they're the same) - and only 'long int' is fundamental.
    return (el.tag == 'FundamentalType') or\
        (el.attrib['name'] in ('short', 'short int', 'signed short', 'signed short int', 'unsigned short',
                               'int', 'signed', 'signed int',
                               'unsigned', 'unsigned int',
                               'long', 'long int', 'signed long', 'signed long int',
                               'unsigned long', 'unsigned long int',
                               'long long', 'long long int', 'signed long long', 'signed long long int',
                               'unsigned long long', 'unsigned long long int'))
    # JOEL: Is this list what we want? Is it missing anything? And this is kinda messy, a new file would possibly help?
    # Also, for the list, does castxml give these names? Confused with for example

# ====== validType ========


def validType(typeName):
    # Need a function to strip
    typeName = stripWhitespace(typeName)
    print(f"typeName = {typeName}")

    # Create required lists to store info
    typeNameBracketLocs = []
    typeNameCommaLocs = []
    findOutsideBracketsAndCommas(
        typeName, typeNameBracketLocs, typeNameCommaLocs)

    # If there are more than 1 angle brackets pair on the outermost level
    # OR there are any commas outside angle brackets there's a problem
    numBracketPairs = len(typeNameBracketLocs)
    assert(numBracketPairs <= 1)
    assert(len(typeNameCommaLocs) == 0)

    if numBracketPairs == 0:
        # Not templated
        return isNonTemplatedTypeValid(typeName)
    else:
        # Is templated
        # Grab the locations of the outer brackets
        (lo, hi) = typeNameBracketLocs[0]
        strippedType = typeName[:lo]

        if not isTemplatedTypeValid(strippedType):
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
            if not section.isdigit() and not validType(section):
                return False

        return True

# ====== END: validType ========


# ====== isNonTemplatedTypeValid ========

def isNonTemplatedTypeValid(typeName):
    return True

# ====== END: isNonTemplatedTypeValid ========


# ====== isTemplatedTypeValid ========

def isTemplatedTypeValid(typeName):
    return True

# ====== END: isTemplatedTypeValid ========


# ====== findOutsideBracketsAndCommas ========

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

# ====== END: findOutsideBracketsAndCommas ========


# ====== removeCharsInRange ========

def removeCharsInRange(string, lo, hi):
    assert(lo <= hi and lo >= 0 and hi < len(string))
    return string[0:lo] + string[hi + 1:]

# ====== END: removeCharsInRange ========


# ====== removeThisSpace ========

def removeThisSpace(ch1, ch2):
    return not (ch1.isalpha() and ch2.isalpha())

# ====== END: removeThisSpace ========


# ====== stripWhitespace ========

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


def stripWhitespace(string):
    # Strip the whitespace to the left and right
    string = string.lstrip(' ').rstrip(' ')

    # Return if empty
    if string == '':
        return ''

    # Now we have no leading/lagging spaces.

    # Find all matches to each regular expression
    # p = re.compile(r"[A-Z]{4}[0-9]{4}")
    # return bool(p.match(string))

    f = open("name_dict.txt", "r")
    fileContents = f.read()
    # Find all instances of two closing brackets together

    # Note - All closing brackets when they're in this form
    # have exactly 1 space, unless they have type std::is_constructible
    # as the outermost template?
    # std::is_constructible<std::allocator<char>>
    # std::is_constructible<std::allocator<wchar_t>>
    # std::is_constructible<std::allocator<char16_t>>
    # std::is_constructible<std::allocator<char32_t>>
    # Produces 1223 matches
    # 16 are '>>'
    # 1207 are '> >'
    # Total of 1207 spaces

    # All ampersands fall into a few categories
    # '&' - 604 and always have 1 space before
    # '&&' - 224 and always have 1 space before
    # '(&)' - 16 and always have 1 space before
    # '*&' - 64 and always have 1 space before
    # '*&&' - 112 and always have 1 space before
    # Total of 1020 spaces

    # Always exactly 1 space before an *
    # Total of 708 (new) spaces since some of these are getting double counted from '*&' and '*&&'

    # Always exactly 1 space after a ,
    # Total of 3007 spaces

    # There are also 1031 matches when there are two word characters seperated by a space
    # Ie, in regex it's of the form "\w \w"

    spaces = re.compile(r" \n")
    matches = re.finditer(spaces, fileContents)

    # allSpacesIndexes = set()
    # spacesCounter = 0
    # discardedSpaces = 0
    # for match in allSpacesMatches:
    #     lo = match.start()
    #     allSpacesIndexes.add(lo)
    #     spacesCounter += 1
#
    # allUnaccountedSpaces = allSpacesIndexes
#
    # allSpaceAmpersand = re.compile(r" &")
    # allSpaceAmpersandMatches = re.finditer(allSpaceAmpersand, fileContents)
    # for match in allSpaceAmpersandMatches:
    #     lo = match.start()
    #     allUnaccountedSpaces.discard(lo)
    #     discardedSpaces += 1
#
    # allSpaceAsterisk = re.compile(r" \*")
    # allSpaceAsteriskMatches = re.finditer(allSpaceAsterisk, fileContents)
    # for match in allSpaceAsteriskMatches:
    #     lo = match.start()
    #     allUnaccountedSpaces.discard(lo)
    #     discardedSpaces += 1
    #
    # allSpaceBracketsAmpersand = re.compile(r" (&)")
    # allSpaceBracketsAmpersandMatches = re.finditer(allSpaceBracketsAmpersand, fileContents)
    # for match in allSpaceBracketsAmpersandMatches:
    #     lo = match.start()
    #     allUnaccountedSpaces.discard(lo)
    #     discardedSpaces += 1
    #
    # allMultiWordTypes = re.compile(r"\w \w")
    # allMultiWordTypesMatches = re.finditer(allMultiWordTypes, fileContents)
    # for match in allMultiWordTypesMatches:
    #     lo = match.start()
    #     allUnaccountedSpaces.discard(lo + 1)
    #     discardedSpaces += 1
    #
    # allCommas = re.compile(r", ")
    # allCommasMatches = re.finditer(allCommas, fileContents)
    # for match in allCommasMatches:
    #     lo = match.start()
    #     allUnaccountedSpaces.discard(lo + 1)
    #     discardedSpaces += 1
    #
    # allAngles = re.compile(r"> >")
    # allAnglesMatches = re.finditer(allAngles, fileContents)
    # for match in allAnglesMatches:
    #     lo = match.start()
    #     allUnaccountedSpaces.discard(lo + 1)
    #     discardedSpaces += 1

    counter = 0
    for index in matches:
        counter += 1
        print(f"{counter}: [{fileContents[index - 1:index + 4]}]")
    print(len(allSpacesIndexes))
    print(
        f"There were {spacesCounter} matches and {discardedSpaces} discarded")

# ====== END: stripWhitespace ========

def getBasicTypeName(type_name):

    # If type name contains a template brackets
    if '<' in type_name:

        type_name_notempl, templ_bracket = removeTemplateBracket(
            type_name, return_bracket=True)
        before_bracket, after_bracket = type_name.rsplit(templ_bracket, 1)

        if (len(after_bracket) > 0) and (after_bracket[0] == ' '):
            space_after_bracket = True
        else:
            space_after_bracket = False

        # Remove asterix and/or ampersand
        before_bracket = before_bracket.replace('*', '').replace('&', '')
        after_bracket = after_bracket.replace('*', '').replace('&', '')

        # Remove 'const' and 'volatile'
        before_bracket_list = before_bracket.split()
        before_bracket_list = [
            item for item in before_bracket_list if item != 'const']
        before_bracket_list = [
            item for item in before_bracket_list if item != 'volatile']
        before_bracket = ' '.join(before_bracket_list)

        after_bracket_list = after_bracket.split()
        after_bracket_list = [
            item for item in after_bracket_list if item != 'const']
        after_bracket_list = [
            item for item in after_bracket_list if item != 'volatile']
        after_bracket = ' '.join(after_bracket_list)

        basic_type_name = before_bracket + templ_bracket + \
            ' '*space_after_bracket + after_bracket

    # If no template bracket
    else:

        basic_type_name = type_name

        # Remove asterix and/or ampersand
        basic_type_name = basic_type_name.replace('*', '').replace('&', '')

        # Remove 'const' and 'volatile'
        basic_type_name_list = basic_type_name.split()
        basic_type_name_list = [
            item for item in basic_type_name_list if item != 'const']
        basic_type_name_list = [
            item for item in basic_type_name_list if item != 'volatile']
        basic_type_name = ' '.join(basic_type_name_list)

    # Return result
    return basic_type_name

def removeTemplateBracket(type_name, return_bracket=False):

    if ('<' in type_name) and ('>' in type_name):

        r_pos = type_name.rfind('>')

        if r_pos <= 0:
            raise Exception(
                "Unbalanced template brackets in type name '%s'" % type_name)

        pos = r_pos-1
        count = 1
        while pos > -1:
            if type_name[pos] == '>':
                count += 1
            elif type_name[pos] == '<':
                count -= 1

            if count == 0:
                break

            pos -= 1

        if count != 0:
            raise Exception(
                "Unbalanced template brackets in type name '%s'" % type_name)

        l_pos = pos

        type_name_notempl = type_name[:l_pos] + type_name[r_pos+1:]
        template_bracket = type_name[l_pos:r_pos+1]

    else:
        type_name_notempl = type_name
        template_bracket = ''

    if return_bracket:
        return type_name_notempl, template_bracket
    else:
        return type_name_notempl

if __name__ == '__main__':
    # print('All types in int')
    # print(validType('int'))
    # print()
    # print("--------------------------------")
    # print()

    # print('All types in std::vector<int>')
    # print(validType('std::vector<int>'))
    # print()
    # print("--------------------------------")
    # print()

    # print('All types in std::map<std::vector<int>, bool>')
    # print(validType('std::map<std::vector<int>, bool>'))
    # print()
    # print("--------------------------------")
    # print()

    # print('All types in std::map<std::vector<int>, std::pair<std::string, bool>>')
    # print(validType('std::map<std::vector<int>, std::pair<std::string, bool>>'))
    # print()
    # print("--------------------------------")
    # print()

    # print('All types in std::array<int, 3>')
    # print(validType('std::array<int, 3>'))
    # print()
    # print("--------------------------------")
    # print()

    # print('All types in   std::vector<   int  >   ')
    # print(validType('  std::vector<   int  >   '))
    # print()
    # print("--------------------------------")
    # print()

    # print('All types in std::map < bool                          ,  char  >  ')
    # print(validType('std::map < bool                          ,  char  >  '))
    # print()
    # print("--------------------------------")
    # print()

    # print('All types in std::array<  std::vector< std::map<std::pair<bool,   std::string>,some_templated_type<T ,char>>>,3>')
    # print(validType(
    #     'std::array<  std::vector< std::map<std::pair<bool,   std::string>,some_templated_type<T ,char>>>,3>'))
    # print()
    # print("--------------------------------")
    # print()
    print(getBasicTypeName(' char const (&)[44]'))
    print(getBasicTypeName('char[44]'))
    # r"(&)[]"