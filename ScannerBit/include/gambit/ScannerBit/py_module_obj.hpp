//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Defines the python objective_plugin module to 
///  be used in the python plugins.
///
///  *********************************************
///
///  Authors:
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2023 Dec
///
///  *********************************************

namespace Gambit
{
    
    namespace Scanner 
    {
        
        namespace Plugins
        {
            
            namespace ObjPyPlugin
            {
                
                /**
                 * @brief A function to export Python plugin data.
                 * 
                 * This function is used to export data related to the Python plugin. It returns a reference to a pointer to the pluginData object.
                 * 
                 * @return Returns a reference to a pointer to the pluginData object.
                 */
                EXPORT_SYMBOLS pluginData*& pythonPluginData()
                {
                    static pluginData *data = nullptr;
                    
                    return data;
                }
                
                /**
                 * @brief A function to execute a Python function with a map of doubles as an argument.
                 * 
                 * This function is used to execute a Python function that is passed as an argument. The function is executed with a map of doubles as its argument.
                 * 
                 * @param func The Python function to be executed.
                 * @param map The map of doubles to be passed as an argument to the Python function.
                 * @return Returns the result of the Python function execution as a double.
                 */
                EXPORT_SYMBOLS double run(py::object &func, map_doub_type_ &map)
                {
                    return func(&map).template cast<double>();
                }
                
                /**
                 * @brief A function to retrieve a value from the ini file.
                 * 
                 * This function is used to retrieve a value of a specified type from the ini file. The key for the value is passed as a parameter to the function.
                 * 
                 * @tparam T The type of the value to be retrieved.
                 * @param in The key for the value to be retrieved.
                 * @return Returns the value from the ini file associated with the given key. If the key does not exist, an error message is printed and a default-constructed object of type T is returned.
                 */
                template <typename T>
                inline T get_inifile_value(const std::string &in)
                {
                    if (!pythonPluginData()->node[in])
                    {
                        scan_err << "Missing iniFile entry \""<< in << "\" needed by a gambit plugin:  \n"
                                << pythonPluginData()->print() << scan_end;
                        return T();
                    }

                    return pythonPluginData()->node[in].template as<T>();
                }
                
                /**
                 * @brief A function to retrieve a value from the ini file with a default value.
                 * 
                 * This function is used to retrieve a value of a specified type from the ini file. The key for the value is passed as a parameter to the function. If the key does not exist in the ini file, a default value is returned.
                 * 
                 * @tparam T The type of the value to be retrieved.
                 * @param in The key for the value to be retrieved.
                 * @param defaults The default value to be returned if the key does not exist in the ini file.
                 * @return Returns the value from the ini file associated with the given key. If the key does not exist, the default value is returned.
                 */
                template <typename T>
                T get_inifile_value(const std::string &in, const T &defaults)
                {
                    if (!pythonPluginData()->node[in])
                    {
                        return defaults;
                    }

                    return pythonPluginData()->node[in].template as<T>();
                }
                
                /**
                 * @brief A function to retrieve a node from the ini file.
                 * 
                 * This function is used to retrieve a node from the ini file. The key for the node is passed as a parameter to the function.
                 * 
                 * @param in The key for the node to be retrieved.
                 * @return Returns the node from the ini file associated with the given key.
                 */
                inline YAML::Node get_inifile_node(const std::string &in)                                                      
                {
                    return pythonPluginData()->node[in];
                }
                
                /**
                 * @brief A function to retrieve the root node from the ini file.
                 * 
                 * This function is used to retrieve the root node from the ini file. No parameters are required as it always returns the root node.
                 * 
                 * @return Returns the root node from the ini file.
                 */
                inline YAML::Node get_inifile_node()                                                      
                {
                    return pythonPluginData()->node;
                }
                
                /**
                 * @brief A function to retrieve an input value of a specified type.
                 * 
                 * This function is used to retrieve an input value of a specified type from the input data. The index of the input value is passed as a parameter to the function.
                 * 
                 * @tparam T The type of the input value to be retrieved.
                 * @param i The index of the input value to be retrieved.
                 * @return Returns a reference to the input value at the given index.
                 */
                template <typename T>
                T &get_input_value(int i)
                {
                    return *static_cast<T*>(pythonPluginData()->inputData[i]);
                }
                
                /**
                 * @brief A function to retrieve the printer interface.
                 * 
                 * This function is used to retrieve the printer interface from the plugin data. No parameters are required as it always returns the printer interface.
                 * 
                 * @return Returns a reference to the printer interface.
                 */
                inline Gambit::Scanner::printer_interface &get_printer()
                {
                    return *pythonPluginData()->printer;
                }

                /**
                 * @brief A function to retrieve the prior interface.
                 * 
                 * This function is used to retrieve the prior interface from the plugin data. No parameters are required as it always returns the prior interface.
                 * 
                 * @return Returns a reference to the prior interface.
                 */
                inline Gambit::Scanner::prior_interface &get_prior()
                {
                    return *pythonPluginData()->prior;
                }
                
                using Gambit::Printers::get_point_id;

                /**
                 * @brief A function to retrieve the keys.
                 * 
                 * This function is used to retrieve the keys from the input data. No parameters are required as it always returns the keys.
                 * 
                 * @return Returns a reference to the vector of keys.
                 */
                std::vector<std::string> &get_keys() {return get_input_value<std::vector<std::string>>(0);} 
                
                /**
                 * @brief A function to set the dimension.
                 * 
                 * This function is used to set the dimension in the input data. The dimension value is passed as a parameter to the function.
                 * 
                 * @param val The value to be set as the dimension.
                 */
                void set_dimension(unsigned int val) {get_input_value<unsigned int>(1) = val;}
                
                /**
                 * @brief A function to print parameters.
                 * 
                 * This function is used to print parameters from the input data. The parameters are passed as a map where the key is the parameter name and the value is the parameter value.
                 * 
                 * @param key_map The map of parameters to be printed.
                 */
                void print_parameters(std::unordered_map<std::string, double> &key_map)
                {
                    using Gambit::Printers::get_main_param_id;
                    Gambit::Scanner::printer *printer = get_printer().get_stream();

                    for (auto it = get_keys().begin(), end = get_keys().end(); it != end; ++it)
                    {
                        auto temp = get_main_param_id(*it);
                        printer->print(key_map[*it], *it, temp, printer->getRank(), get_point_id());
                    }
                }
        
            }

        }
        
    }
    
}

/**
 * @brief A pybind11 module named "objective_plugin".
 * 
 * This module is used to bind Python and C++ code using the pybind11 library. It imports the "scannerbit" module and defines some functions and attributes for the module.
 * 
 * @param m The pybind11 module to which the bindings are added.
 */
PYBIND11_EMBEDDED_MODULE(objective_plugin, m) 
{
    
    using namespace ::Gambit::Scanner::Plugins::ObjPyPlugin;

    // Import the "scannerbit" module
    m.attr("scannerbit") = m.import("scannerbit");
    
    // Define the "get_inifile_node" function for the module
    m.def("get_inifile_node", [](py::args args) -> py::object
    {
        py::object ret = Gambit::Scanner::yaml_to_dict(get_inifile_node());
        
        for (auto &&arg : args)
            ret = py::dict(ret)[py::cast(arg.template cast<std::string>())];
        
        return ret;
    });
    
    // Define the "get_inifile_value" function for the module
    m.def("get_inifile_value", SCAN_PLUGIN_GET_INIFILE_VALUE_FUNC);
    // Define the "get_keys" function for the module
    m.def("get_keys", get_keys);
    // Define the "set_dimension" function for the module
    m.def("set_dimension", set_dimension);
    // Define the "print_parameters" function for the module
    m.def("print_parameters", print_parameters);
    
}
