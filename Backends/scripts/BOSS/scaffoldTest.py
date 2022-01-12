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

# Unfished function


def stripWhitespace(string):
    if string == '':
        return ''

    # Strip the whitespace to the left and right
    string = string.lstrip(' ').rstrip(' ')

    lastNonSpaceIndex = 0
    lastNonSpaceCharacter = None
    for i, ch in enumerate(string):
        if ch != ' ':
            lastNonSpaceIndex = i
            lastNonSpaceCharacter = ch
        else:
            print('owo')


def recursiveTest(typeName):
    # Need a function to strip
    typeName = typeName.lstrip(' ').rstrip(' ')

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
        # Add test here
        if is_A(typeName) or is_B(typeName) or is_C(typeName) or is_D(typeName):
            # return True
            print(f"{typeName} is accepted")
            pass
        else:
            print(f"{typeName} is Rejected")
            return False
    else:
        # Is templated
        # Grab the locations of the outer brackets
        (lo, hi) = typeNameBracketLocs[0]
        strippedType = typeName[:lo].rstrip(' ')

        if is_A(strippedType) or is_B(strippedType) or is_C(strippedType) or is_D(strippedType):
            # return True
            print(f"{strippedType} is accepted")
            pass
        else:
            print(f"{strippedType} is Rejected")
            return False

        print(f"{strippedType} is templated, go deeper")

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
        insideBracketsSections = []
        for comma in insideBracketsCommaLocs:
            # For each comma, get the substring between this comma and the last one
            # and strip it for leading/lagging whitespace.
            # Then, add it to the list of section
            insideBracketsSections.append(
                insideBrackets[prevComma + 1:comma].lstrip(' ').rstrip(' '))
            prevComma = comma

        for section in insideBracketsSections:
            # Recurse through each section
            # Unless they're a digit
            # E.g., typeName = 'std::array<int, 3>'
            # insideBrackets = 'int, 3'
            # insideBracketsSections = ['int', '3']
            if not section.isdigit():
                recursiveTest(section)


def is_template(input):
    if input.count(">") == 0 and input.count("<") == 0:
        return False
    else:
        return True


def extract_first_type(input):
    # getting the first type
    type_check = input.split("<", 1)[0]
    return type_check


def is_A(input):
    return True if input == "A" else False
    # first_input_type = extract_first_type(input)
    # print(f"A is {first_input_type}")

    # parsed_list = []
    # recursiveTest(input, parsed_list)
    # print(f"{parsed_list}")
    # next_input = parsed_list[1] if len(parsed_list) > 1 else None

    # print(f"A Next input is {next_input}")

    # if first_input_type == "A" and is_template(input):
    #     return is_A(next_input) or is_C(next_input) or is_D(next_input) or is_B(next_input)
    # elif first_input_type == "A" and not is_template(input) and next_input is None:
    #     return True
    # else:
    #     return False


def is_B(input):
    return True if input == "B" else False
    # first_input_type = extract_first_type(input)
    # print(f"B is {first_input_type}")

    # parsed_list = []
    # recursiveTest(input, parsed_list)
    # print(f"{parsed_list}")
    # next_input = parsed_list[1] if len(parsed_list) > 1 else None

    # print(f"B Next input is {next_input}")

    # if first_input_type == "B" and is_template(input):
    #     return is_A(next_input) or is_C(next_input) or is_D(next_input) or is_B(next_input)
    # elif first_input_type == "B" and not is_template(input) and next_input is None:
    #     return True
    # else:
    #     return False


def is_C(input):
    return True if input == "C" else False

    # first_input_type = extract_first_type(input)
    # print(f"C is {first_input_type}")

    # parsed_list = []
    # recursiveTest(input, parsed_list)
    # print(f"{parsed_list}")
    # next_input = parsed_list[1] if len(parsed_list) > 1 else None

    # print(f"C Next input is {next_input}")

    # if first_input_type == "C" and is_template(input):
    #     return is_B(next_input) or is_A(next_input) or is_D(next_input) or is_A(next_input)
    # elif first_input_type == "C" and not is_template(input) and next_input is None:
    #     return True
    # else:
    #     return False


def is_D(input):
    return True if input == "D" else False
    # first_input_type = extract_first_type(input)
    # print(f"D is {first_input_type}")

    # parsed_list = []
    # recursiveTest(input, parsed_list)
    # print(f"{parsed_list}")
    # next_input = parsed_list[1] if len(parsed_list) > 1 else None

    # next_input = parsed_list.join
    # print(f"D Next input is {next_input}")

    # if first_input_type == "D" and is_template(input):
    #     return is_B(next_input) or is_A(next_input) or is_D(next_input) or is_A(next_input)
    # elif first_input_type == "D" and not is_template(input) and next_input is None:
    #     return True
    # else:
    #     return False


if __name__ == "__main__":

    input = "A<B,E>"
    print(
        f"result is {recursiveTest(input)}")


# std: : vector < int > , bool -> int, bool -> bool
