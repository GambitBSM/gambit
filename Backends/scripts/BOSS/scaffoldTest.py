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
    first_input_type = extract_first_type(input)
    if first_input_type == "A" and is_template(input):
        return is_B(input) or is_C(input) or is_D(input)
    elif first_input_type == "A" and not is_template(input):
        return True
    else:
        return False


def is_B(input):
    first_input_type = extract_first_type(input)
    if first_input_type == "B" and is_template(input):
        return is_A(input) or is_C(input) or is_D(input)
    elif first_input_type == "B" and not is_template(input):
        return True
    else:
        return False


def is_C(input):
    first_input_type = extract_first_type(input)
    if first_input_type == "C" and is_template(input):
        return is_B(input) or is_A(input) or is_D(input)
    elif first_input_type == "C" and not is_template(input):
        return True
    else:
        return False


def is_D(input):
    first_input_type = extract_first_type(input)
    if first_input_type == "D" and is_template(input):
        return is_B(input) or is_C(input) or is_A(input)
    elif first_input_type == "D" and not is_template(input):
        return True
    else:
        return False


if __name__ == "__main__":
    input = "std::vector<int>"
    print(
        f"result is {is_A(input) or is_B(input) or is_C(input) or is_D(input)}")
