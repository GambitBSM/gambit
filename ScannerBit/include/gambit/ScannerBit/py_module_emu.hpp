//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Defines the python scanner_plugin module to 
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

            namespace EmulatorPyPlugin
            {

                using Gambit::Scanner::map_vector;
                using Gambit::Scanner::vector;
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
                 * @brief A function to retrieve a value from the INI file.
                 * 
                 * This function is used to retrieve a value from the INI file based on a given key. The key is passed as a parameter to the function.
                 * 
                 * @tparam T The type of the value to be retrieved from the INI file.
                 * @param in The key for which the value is to be retrieved from the INI file.
                 * @return Returns the value associated with the given key in the INI file.
                 */
                template <typename T>
                T get_inifile_value(const std::string &in)
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
                 * @brief A function to retrieve a value from the INI file.
                 * 
                 * This function is used to retrieve a value from the INI file based on a given key. If the key is not found, a default value is returned.
                 * 
                 * @tparam T The type of the value to be retrieved from the INI file.
                 * @param in The key for which the value is to be retrieved from the INI file.
                 * @param defaults The default value to be returned if the key is not found in the INI file.
                 * @return Returns the value associated with the given key in the INI file, or the default value if the key is not found.
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
                 * @brief A function to retrieve a node from the INI file.
                 * 
                 * This function is used to retrieve a YAML::Node from the INI file based on a given key. The key is passed as a parameter to the function.
                 * 
                 * @param in The key for which the node is to be retrieved from the INI file.
                 * @return Returns the YAML::Node associated with the given key in the INI file.
                 */
                inline YAML::Node get_inifile_node(const std::string &in)                                                      
                {
                    return pythonPluginData()->node[in];
                }

                /**
                 * @brief A function to retrieve the root node from the INI file.
                 * 
                 * This function is used to retrieve the root YAML::Node from the INI file.
                 * 
                 * @return Returns the root YAML::Node of the INI file.
                 */
                inline YAML::Node get_inifile_node()                                                      
                {
                    return pythonPluginData()->node;
                }
                
                /**
                 * @brief A function to retrieve an input value by index.
                 * 
                 * This function is used to retrieve an input value from a data structure based on the given index.
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
                 * This function is used to retrieve a reference to the printer interface from the Gambit::Scanner namespace.
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
                 * This function is used to retrieve a reference to the prior interface from the Gambit::Scanner namespace.
                 * 
                 * @return Returns a reference to the prior interface.
                 */
                inline Gambit::Scanner::prior_interface &get_prior()
                {
                    return *pythonPluginData()->prior;
                }

                /**
                 * @class emulator_base
                 * @brief A base class for emulator functionality.
                 * 
                 * This class provides a base for emulator functionality. It defines several types related to the Gambit::Scanner namespace and can be extended by other classes to provide more specific functionality.
                 */     
                class emulator_base
                {
                public:

                    void train(map_vector<double>, map_vector<double>, map_vector<double>)
                    {
                        scan_err << "\"train()\" method not defined in python scanner plugin." << scan_end;
                        return;
                    }

                    //predict
                    std::pair<vector<double>, vector<double>> predict(map_vector<double>)
                    {
                        scan_err << "\"predict()\" method not defined in python scanner plugin." << scan_end;
                        return std::pair<vector<double>, vector<double>>();
                    }

                    /**
                     * @brief Converts a vector to a Python list.
                     * 
                     * This static method is used to convert a standard C++ vector into a Python list. Each element of the vector is appended to the Python list.
                     * 
                     * @tparam T The type of the elements in the vector.
                     * @param vec The vector to be converted.
                     * @return Returns a Python list containing the elements of the input vector.
                     */
                    template<typename T>
                    static py::list to_list(const std::vector<T> &vec)
                    {
                        py::list l;
                        for (auto &&elem : vec)
                            l.append(py::cast(elem));
                        
                        return l;
                    }

                    /**
                     * @brief Retrieves the YAML node.
                     * 
                     * This static method is used to retrieve the YAML node. If the node has not been initialized, it is set to the result of the `get_inifile_node` function.
                     * 
                     * @return Returns a reference to the YAML node.
                     */
                    static YAML::Node &getNode()
                    {
                        static YAML::Node node = get_inifile_node();
                        
                        return node;
                    }
                    
                #ifdef WITH_MPI
                    /**
                     * @brief Checks if MPI is enabled.
                     * 
                     * This static method is used to check if MPI is enabled.
                     * 
                     * @return Returns true if MPI is enabled.
                     */
                    static bool with_mpi() {return true;}

                    /**
                     * @brief Retrieves the rank of the MPI process.
                     * 
                     * This static method is used to retrieve the rank of the MPI process.
                     * 
                     * @return Returns the rank of the MPI process.
                     */
                    static int rank()
                    {
                        int rank;
                        MPI_Comm_rank(*Gambit::Scanner::Plugins::plugin_info.scanComm().get_boundcomm(), &rank);
                        
                        return rank;
                    }
                    
                    /**
                     * @brief Retrieves the number of MPI processes.
                     * 
                     * This static method is used to retrieve the number of MPI processes.
                     * 
                     * @return Returns the number of MPI processes.
                     */
                    static int numtasks()
                    {
                        int numtasks;
                        MPI_Comm_size(*Gambit::Scanner::Plugins::plugin_info.scanComm().get_boundcomm(), &numtasks);
                        
                        return numtasks;
                    }

                    static MPI_Fint get_mpi_comm()
                    {
                        return MPI_Comm_c2f(*Gambit::Scanner::Plugins::plugin_info.scanComm().get_boundcomm());
                    }
                #else
                    /**
                     * @brief Checks if MPI is enabled.
                     * 
                     * This static method is used to check if MPI is enabled.
                     * 
                     * @return Returns false if MPI is not enabled.
                     */
                    static bool with_mpi() {return false;}

                    /**
                     * @brief Retrieves the rank of the MPI process.
                     * 
                     * This static method is used to retrieve the rank of the MPI process.
                     * 
                     * @return Returns 0 if MPI is not enabled.
                     */
                    static int rank() {return 0;}

                    /**
                     * @brief Retrieves the number of MPI processes.
                     * 
                     * This static method is used to retrieve the number of MPI processes.
                     * 
                     * @return Returns 1 if MPI is not enabled.
                     */
                    static int numtasks() {return 1;}
                #endif
                };
                
            }
            
        }
        
    }
    
}

/**
 * @brief A pybind11 module named "scanner_plugin".
 * 
 * This module is used to bind Python and C++ code using the pybind11 library. It imports the "scannerbit" module and defines some functions and attributes for the module.
 * 
 * @param m The pybind11 module to which the bindings are added.
 */
PYBIND11_EMBEDDED_MODULE(emulator_plugin, m)
{
    
    using namespace Gambit::Scanner::Plugins::EmulatorPyPlugin;
    using namespace Gambit::Scanner;
    
    // Import the "scannerbit" module
    m.attr("scannerbit") = m.import("scannerbit");
    
    // Define the "get_printer" function for the module
    m.def("get_printer", []()
    {
        return &get_printer();
    }, "", py::return_value_policy::reference);
    
    // Define the "get_prior" function for the module
    m.def("get_prior", []()
    {
        return &get_prior();
    }, "", py::return_value_policy::reference);
    
    // Define the "get_inifile_node" function for the module
    m.def("get_inifile_node", [](py::args args) -> py::object
    {
        py::object ret = yaml_to_dict(get_inifile_node());
        
        for (auto &&arg : args)
            ret = py::dict(ret)[py::cast(arg.template cast<std::string>())];
        
        return ret;
    });
    
    // Define the "get_inifile_value" function for the module
    m.def("get_inifile_value", SCAN_PLUGIN_GET_INIFILE_VALUE_FUNC);
    
    // Bind the scanner base class to the module
    py::class_<emulator_base, std::shared_ptr<emulator_base>>(m, "emulator")
    .def(py::init([]()
    {
        return std::shared_ptr<emulator_base>(new emulator_base());
    }))
    .def("train", [](emulator_base &, py::object, py::object, py::object)
    {
        scan_err << "\"train()\" method not defined in python scanner plugin." << scan_end;
    })
    .def("predict", [](emulator_base &, py::object)
    {
        scan_err << "\"train()\" method not defined in python scanner plugin." << scan_end;
        return py::object();
    })
    .def_property_readonly_static("args", [](py::object)
    {
        static py::dict opts = ::Gambit::Scanner::yaml_to_dict(emulator_base::getNode());
        
        return opts;
    })
    .def_property_readonly_static("init_args", [](py::object)
    {
        static py::dict init_opts = ::Gambit::Scanner::yaml_to_dict(emulator_base::getNode()["init"] ? emulator_base::getNode()["init"] : YAML::Node());
                        
        return init_opts;
    })
    .def_property_readonly_static("run_args", [](py::object)
    {
        static py::dict run_opts = ::Gambit::Scanner::yaml_to_dict(emulator_base::getNode()["run"] ? emulator_base::getNode()["run"] : YAML::Node());
                        
        return run_opts;
    })
    .def_property_readonly_static("mpi_rank", [](py::object)
    {
        static int my_rank = emulator_base::rank();
                        
        return my_rank;
    })
    .def_property_readonly_static("mpi_size", [](py::object)
    {
        static int tasks = emulator_base::numtasks();
        
        return tasks;
    })
#ifdef WITH_MPI
    .def_property_readonly_static("mpi_comm", [](py::object)
    {
        MPI_Fint comm = emulator_base::get_mpi_comm();

        return comm;
    })
#endif
    ;

}
