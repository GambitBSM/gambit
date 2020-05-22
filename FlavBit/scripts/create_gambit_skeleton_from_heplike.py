from yaml import load

try:
    from yaml import CLoader as Loader, CDumper as Dumper
except ImportError:
    from yaml import Loader, Dumper


def get_data_from_yaml(path):
    with open(path, 'r') as f:
        data = load(f, Loader=Loader)
    return data


def create_flavbit_function(capability_name, *path_to_yaml):
    likelihood_types = [get_data_from_yaml(path)['HL_Type'] for path in path_to_yaml]

    likelihood_variable_names = [
        likelihood_type[3].lower() + likelihood_type[4:] + '_' + str(i)
        for i, likelihood_type in enumerate(likelihood_types)
    ]

    code_inputfiles = ['static const std::string inputfile_%s = path_to_latest_heplike_data() + "/%s";' % (i, path)
                       for i, path in enumerate(path_to_yaml)]
    code_likelihood_defs = [
        'static HepLike_default::%s %s(inputfile_%s);' % (likelihood_type, likelihood_variable_name, i)
        for i, (likelihood_type, likelihood_variable_name) in
        enumerate(zip(likelihood_types, likelihood_variable_names))]

    code_read_inputs = [
        'std::cout << "Debug: Reading HepLike data file: " << inputfile_%s << endl;\n      %s.Read();' % (
        i, likelihood_variable_name)
        for i, likelihood_variable_name in enumerate(likelihood_variable_names)]

    code_sum_result = [
        '//result += %s.GetLogLikelihood(theory /* , theory_error */);' % likelihood_variable_name
        for likelihood_variable_name in likelihood_variable_names
    ]

    code = """/// HEPLike LogLikelihood TODO: NAME
void %s(double &result)
  {
    using namespace Pipes::%s;
""" % (capability_name, capability_name)

    for define_input in code_inputfiles:
        code += "    " + define_input + '\n'

    for define_variable in code_likelihood_defs:
        code += "    " + define_variable + '\n'

    code += """
    static bool first = true;
    if (first)
    {
"""
    for code_read_input in code_read_inputs:
        code += "      " + code_read_input + '\n'

    code += """
      first = false;
    }
    // TODO: Remove the line below
    assert(false && "Theory prediction not available");
    // TODO: and add theory prediction here and request from likelihoods (commented block below)
    result = 0;
"""

    for code_sum_element in code_sum_result:
        code += "    " + code_sum_element + '\n'

    code += """    
    std::cout << "%s result: " << result << std::endl;
  }
"""
    return code

#     likelihood_type = get_data_from_yaml(path_to_yaml)['HL_Type']
#     likelihood_variable_name = likelihood_type.strip("HL_")
#     likelihood_variable_name = likelihood_variable_name[0].lower() + likelihood_variable_name[1:]
#
#     code_string = """/// HEPLike LogLikelihood TODO: NAME
# void %s(double &result)
#   {
#     using namespace Pipes::%s;
#     static const std::string inputfile = path_to_latest_heplike_data() + "/%s";
#     static HepLike_default::%s %s(inputfile);
#     static bool first = true;
#     if (first)
#     {
#       std::cout << "Debug: Reading HepLike data file: " << inputfile << endl;
#       %s.Read();
#       first = false;
#     }
#     // TODO: Remove the two lines below
#     assert(false && "Theory prediction not available");
#     result = -999;
#     // TODO: and add theory prediction here
#     // result = %s.GetLogLikelihood(theory /* , theory_error */);
#     std::cout << "%s result: " << result << std::endl;
#   }
# """ % (capability_name, capability_name, *path_to_yaml, likelihood_type, likelihood_variable_name,
#        likelihood_variable_name, likelihood_variable_name, capability_name)
#
#     return code_string


def create_rollcall_entry(capability_name):
    return """/// HEPLike LogLikelihood TODO: NAME
#define CAPABILITY %s
START_CAPABILITY
  #define FUNCTION %s
  START_FUNCTION(double);
  // TODO: add dependencies
  NEEDS_CLASSES_FROM(HepLike);
  #undef FUNCTION
#undef CAPABILITY
""" % (capability_name, capability_name)


if __name__ == '__main__':
    import sys

    try:
        print(create_flavbit_function(sys.argv[1], *sys.argv[2:]))
        print(create_rollcall_entry(sys.argv[1]))
    except IndexError:
        print("Argument 1: name of capability")
        print("Argument 2: path in HEPLikeData repository starting with data/... in HEPLikeData repository. Multiple files possible.")
