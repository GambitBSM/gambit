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
            
            namespace ScannerPyPlugin
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
                 * @brief A function to retrieve the dimension.
                 * 
                 * This function is used to retrieve a reference to the dimension. The dimension could represent various aspects depending on the context, such as the dimension of a data structure, a mathematical space, etc.
                 * 
                 * @return Returns a reference to the dimension.
                 */
                inline unsigned int &get_dimension() {return get_input_value<unsigned int>(0);}
                
                /**
                 * @brief A function to retrieve a function object based on its purpose.
                 * 
                 * This function is used to retrieve a function object from the Gambit::Scanner namespace based on its purpose. The purpose is passed as a parameter to the function.
                 * 
                 * @param purpose The purpose of the function to be retrieved.
                 * @return Returns a shared pointer to the function object associated with the given purpose.
                 */
                inline std::shared_ptr<Gambit::Scanner::Function_Base<double (std::unordered_map<std::string, double> &)>>
                get_purpose(const std::string &purpose)
                {
                    void *ptr = (get_input_value<Factory_Base>(1))(purpose);
                    static_cast <Function_Base<void(void)>*>(ptr)->setPurpose(purpose);
                    static_cast <Function_Base<void(void)>*>(ptr)->setPrinter(get_printer().get_stream());
                    static_cast <Function_Base<void(void)>*>(ptr)->setPrior(&get_prior());
                    assign_aux_numbers(purpose, "pointID", "MPIrank");

                    return Gambit::Scanner::like_ptr(ptr);
                }

                /**
                 * @brief A class that wraps a shared pointer to a Function_Base object.
                 * 
                 * This class is used to manage the lifetime of Function_Base objects and to provide a uniform interface for using them.
                 * 
                 * @tparam T The specific type of the Function_Base object.
                 */
                template <typename T>
                class like_ptr_base : public std::enable_shared_from_this<T>
                {
                protected:
                    typedef std::shared_ptr<Gambit::Scanner::Function_Base<double (std::unordered_map<std::string, double> &)>> s_ptr;
                    typedef Gambit::Scanner::Function_Base<double (std::unordered_map<std::string, double> &)> s_func;
                    s_ptr ptr;
                    
                public:
                    /**
                     * @brief Constructs a like_ptr_base object.
                     * 
                     * @param s A reference to the Function_Base object to be managed.
                     */
                    like_ptr_base(s_func &s) : ptr(s.shared_from_this()) {}
                    
                    /**
                     * @brief Retrieves the underlying shared pointer.
                     * 
                     * @return A reference to the underlying shared pointer.
                     */
                    Gambit::Scanner::like_ptr &get(){return static_cast<Gambit::Scanner::like_ptr&>(ptr);}
                };
                
                /**
                 * @brief A derived class of like_ptr_base for managing Function_Base objects related to hypercubes.
                 * 
                 * This class is specifically designed to manage Function_Base objects that represent hypercubes in a multidimensional space.
                 */
                struct like_hypercube : like_ptr_base<like_hypercube>
                {
                    /**
                     * @brief Constructs a like_hypercube object.
                     * 
                     * @param s A reference to the Function_Base object to be managed.
                     */
                    like_hypercube(s_func &s) : like_ptr_base<like_hypercube>(s) {}
                };
                
                /**
                 * @brief A derived class of like_ptr_base for managing Function_Base objects related to physical properties.
                 * 
                 * This class is specifically designed to manage Function_Base objects that represent physical properties in a system.
                 */
                struct like_physical : like_ptr_base<like_physical>
                {
                    /**
                     * @brief Constructs a like_physical object.
                     * 
                     * @param s A reference to the Function_Base object to be managed.
                     */
                    like_physical(s_func &s) : like_ptr_base<like_physical>(s) {}
                };
                
                /**
                 * @brief A derived class of like_ptr_base for managing Function_Base objects related to physical priors.
                 * 
                 * This class is specifically designed to manage Function_Base objects that represent physical priors and likelihood in a system.
                 */
                struct like_prior_physical : like_ptr_base<like_prior_physical>
                {
                    /**
                     * @brief Constructs a like_prior_physical object.
                     * 
                     * @param s A reference to the Function_Base object to be managed.
                     */
                    like_prior_physical(s_func &s) : like_ptr_base<like_prior_physical>(s) {}
                };
                
                /**
                 * @brief A derived class of like_ptr_base for managing Function_Base objects related to physical priors.
                 * 
                 * This class is specifically designed to manage Function_Base objects that represent physical priors in a system.
                 */
                struct prior_physical : like_ptr_base<prior_physical>
                {
                    /**
                     * @brief Constructs a prior_physical object.
                     * 
                     * @param s A reference to the Function_Base object to be managed.
                     */
                    prior_physical(s_func &s) : like_ptr_base<prior_physical>(s) {}
                };
                
                /**
                 * @class scanner_base
                 * @brief A base class for scanner functionality.
                 * 
                 * This class provides a base for scanner functionality. It defines several types related to the Gambit::Scanner namespace and can be extended by other classes to provide more specific functionality.
                 * 
                 * @typedef s_ptr A shared pointer to a function object in the Gambit::Scanner namespace.
                 * @typedef s_func A function object in the Gambit::Scanner namespace.
                 * @typedef s_hyper_func A hypercube function object in the Gambit::Scanner::Plugins::ScannerPyPlugin namespace.
                 * @typedef s_phys_func A physical function object in the Gambit::Scanner::Plugins::ScannerPyPlugin namespace.
                 * @typedef s_phys_pr_func A physical prior function object in the Gambit::Scanner::Plugins::ScannerPyPlugin namespace.
                 * @typedef s_pr_func A prior physical function object in the Gambit::Scanner::Plugins::ScannerPyPlugin namespace.
                 */     
                class scanner_base
                {
                public:
                    typedef std::shared_ptr<Gambit::Scanner::Function_Base<double (std::unordered_map<std::string, double> &)>> s_ptr;
                    typedef Gambit::Scanner::Function_Base<double (std::unordered_map<std::string, double> &)> s_func;
                    typedef Gambit::Scanner::Plugins::ScannerPyPlugin::like_hypercube s_hyper_func;
                    typedef Gambit::Scanner::Plugins::ScannerPyPlugin::like_physical s_phys_func;
                    typedef Gambit::Scanner::Plugins::ScannerPyPlugin::like_prior_physical s_phys_pr_func;
                    typedef Gambit::Scanner::Plugins::ScannerPyPlugin::prior_physical s_pr_func;
                    
                    /**
                     * @brief A method to run the scanner.
                     * 
                     * This method is intended to be overridden by derived classes. If not overridden, it will print an error message and return 1.
                     * 
                     * @return Returns 1 if the method is not overridden in a derived class.
                     */
                    int run()
                    {
                        scan_err << "\"run()\" method not defined in python scanner plugin." << scan_end;
                        return 1;
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
                    
                    /**
                     * @brief Retrieves the likelihood function.
                     * 
                     * This static method is used to retrieve the likelihood function. If the function has not been initialized, it is set to the result of the `get_purpose` function with the "like" node from the YAML node as the argument.
                     * 
                     * @return Returns a shared pointer to the likelihood function.
                     */
                    static std::shared_ptr<s_func> getLike()
                    {
                        static std::shared_ptr<s_func> like = getNode()["like"] ? get_purpose(getNode()["like"].template as<std::string>()) : nullptr;
                        
                        return like;
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
                        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
                        
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
                        MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
                        
                        return numtasks;
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
PYBIND11_EMBEDDED_MODULE(scanner_plugin, m) 
{
    
    using namespace Gambit::Scanner::Plugins::ScannerPyPlugin;
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
    
    typedef Gambit::Scanner::Plugins::ScannerPyPlugin::like_hypercube s_hyper_func;
    typedef Gambit::Scanner::Plugins::ScannerPyPlugin::like_physical s_phys_func;
    typedef Gambit::Scanner::Plugins::ScannerPyPlugin::like_prior_physical s_phys_pr_func;
    typedef Gambit::Scanner::Plugins::ScannerPyPlugin::prior_physical s_pr_func;
    using namespace Gambit::Scanner::Plugins::ScannerPyPlugin;
    


    py::class_<s_hyper_func, std::shared_ptr<s_hyper_func>> pylike_hypercube_ptr(m, "like_hypercube_ptr");
    pylike_hypercube_ptr
    .def(py::init([]()
    {
        return std::shared_ptr<scanner_base::s_hyper_func> (scanner_base::getLike() == nullptr ? nullptr : new scanner_base::s_hyper_func(*scanner_base::getLike().get()));
    }))
    .def("__reduce__", [pylike_hypercube_ptr](s_hyper_func &)
    {
        return py::make_tuple(pylike_hypercube_ptr, py::tuple());
    })
    .def("__call__", [](s_hyper_func &self, Gambit::Scanner::hyper_cube_ref<double> vec)
    {
        return self.get()(vec);
    })
    .def("__call__", [](s_hyper_func &self, Gambit::Scanner::hyper_cube_ref<float> vecf)
    {
        Gambit::Scanner::vector<double> vec = vecf.template cast<double>();
        return self.get()(vec);
    })
    .def("__call__", [](s_hyper_func &self, py::dict params)
    {
        auto &like = self.get();
        auto &map = like->getMap();
        for(auto &&p: params)
            map[p.first.template cast<std::string>()] = p.second.template cast<double>();
        
        return like(map);
    })
    .def("__call__", [](s_hyper_func &self, std::unordered_map<std::string, double> &map)
    {
        return self.get()(map);
    });
    


    py::class_<s_phys_func, std::shared_ptr<s_phys_func>> pylike_physical_ptr(m, "like_physical_ptr");
    pylike_physical_ptr
    .def(py::init([]()
    {
        return std::shared_ptr<scanner_base::s_phys_func> (scanner_base::getLike() == nullptr ? nullptr : new scanner_base::s_phys_func(*scanner_base::getLike().get()));
    }))
    .def("__reduce__", [pylike_physical_ptr](s_phys_func &)
    {
        return py::make_tuple(pylike_physical_ptr, py::tuple());
    })
    .def("__call__", [](s_phys_func &self, Gambit::Scanner::hyper_cube_ref<double> vec)
    {
        auto &like = self.get();
        auto &map = like->getMap();
        int i = 0;
        for(auto &&name : like->getShownParameters())
            map[name] = vec[i++];
        
        return like(map);
    })
    .def("__call__", [](s_phys_func &self, Gambit::Scanner::hyper_cube_ref<float> vecf)
    {
        Gambit::Scanner::vector<double> vec = vecf.template cast<double>();
        auto &like = self.get();
        auto &map = like->getMap();
        int i = 0;
        for(auto &&name : like->getShownParameters())
            map[name] = vec[i++];
        
        return like(map);
    })
    .def("__call__", [](s_phys_func &self, py::dict params)
    {
        auto &like = self.get();
        auto &map = like->getMap();
        for(auto &&p: params)
            map[p.first.template cast<std::string>()] = p.second.template cast<double>();
        
        return like(map);
    })
    .def("__call__", [](s_phys_func &self, std::unordered_map<std::string, double> &map)
    {
        return self.get()(map);
    });
    


    py::class_<s_phys_pr_func, std::shared_ptr<s_phys_pr_func>> pylike_prior_physical_ptr(m, "like_prior_physical_ptr");
    pylike_prior_physical_ptr
    .def(py::init([]()
    {
        return std::shared_ptr<scanner_base::s_phys_pr_func> (scanner_base::getLike() == nullptr ? nullptr : new scanner_base::s_phys_pr_func(*scanner_base::getLike().get()));
    }))
    .def("__reduce__", [pylike_prior_physical_ptr](s_phys_pr_func &)
    {
        return py::make_tuple(pylike_prior_physical_ptr, py::tuple());
    })
    .def("__call__", [](s_phys_pr_func &self, Gambit::Scanner::hyper_cube_ref<double> vec)
    {
        auto &like = self.get();
        auto &map = like->getMap();
        int i = 0;
        for(auto &&name : like->getShownParameters())
            map[name] = vec[i++];
        
        return like(map, true);
    })
    .def("__call__", [](s_phys_pr_func &self, Gambit::Scanner::hyper_cube_ref<float> vecf)
    {
        Gambit::Scanner::vector<double> vec = vecf.template cast<double>();
        auto &like = self.get();
        auto &map = like->getMap();
        int i = 0;
        for(auto &&name : like->getShownParameters())
            map[name] = vec[i++];
        
        return like(map, true);
    })
    .def("__call__", [](s_phys_pr_func &self, py::dict params)
    {
        auto &like = self.get();
        auto &map = like->getMap();
        for(auto &&p: params)
            map[p.first.template cast<std::string>()] = p.second.template cast<double>();
        
        return like(map, true);
    })
    .def("__call__", [](s_phys_pr_func &self, std::unordered_map<std::string, double> &map)
    {
        return self.get()(map, true);
    });
    


    py::class_<s_pr_func, std::shared_ptr<s_pr_func>> pyprior_physical_ptr(m, "prior_physical_ptr");
    pyprior_physical_ptr
    .def(py::init([]()
    {
        return std::shared_ptr<scanner_base::s_pr_func> (scanner_base::getLike() == nullptr ? nullptr : new scanner_base::s_pr_func(*scanner_base::getLike().get()));
    }))
    .def("__reduce__", [pyprior_physical_ptr](s_pr_func &)
    {
        return py::make_tuple(pyprior_physical_ptr, py::tuple());
    })
    .def("__call__", [](s_pr_func &self, Gambit::Scanner::hyper_cube_ref<double> vec)
    {
        auto &like = self.get();
        auto &map = like->getMap();
        int i = 0;
        for(auto &&name : like->getShownParameters())
            map[name] = vec[++i];
        
        return like->getPrior().log_prior_density(map);
    })
    .def("__call__", [](s_pr_func &self, Gambit::Scanner::hyper_cube_ref<float> vecf)
    {
        Gambit::Scanner::vector<double> vec = vecf.template cast<double>();
        auto &like = self.get();
        auto &map = like->getMap();
        int i = 0;
        for(auto &&name : like->getShownParameters())
            map[name] = vec[++i];
        
        return like->getPrior().log_prior_density(map);
    })
    .def("__call__", [](s_phys_pr_func &self, py::dict params)
    {
        auto &like = self.get();
        auto &map = like->getMap();
        for(auto &&p: params)
            map[p.first.template cast<std::string>()] = p.second.template cast<double>();
        
        return like->getPrior().log_prior_density(map);
    })
    .def("__call__", [](s_phys_pr_func &self, std::unordered_map<std::string, double> &map)
    {
        return self.get()->getPrior().log_prior_density(map);
    });
    
    // Define the "get_inifile_value" function for the module
    m.def("get_inifile_value", SCAN_PLUGIN_GET_INIFILE_VALUE_FUNC);
    // Define the "get_dimension" function for the module
    m.def("get_dimension", get_dimension);
    // Define the "get_purpose" function for the module
    m.def("get_purpose", get_purpose);
    
    // Bind the scanner base class to the module
    py::class_<scanner_base, std::shared_ptr<scanner_base>>(m, "scanner")
    .def(py::init([](bool 
        #ifdef WITH_MPI
                     use_mpi
        #endif 
                    , bool use_resume)
        {
        #ifdef WITH_MPI
            if (!use_mpi)
            {
                int numtasks;
                MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
                if (numtasks != 1)
                {
                    scan_err << "This scanner does not support MPI." << scan_end;
                }
            }
        #endif
        
            if (!use_resume && Gambit::Scanner::Plugins::ScannerPyPlugin::get_printer().resume_mode())
            {
                scan_err << "This scanner does not support resuming." << scan_end;
            }
                
            return new scanner_base();
        }), py::arg("use_mpi")=true, py::arg("use_resume")=true)
    .def("run", &scanner_base::run)
    .def_static("print", [](double val, const std::string &name)
    {
        static int my_rank = scanner_base::rank();
        
        get_printer().get_stream()->print(val, name, my_rank, scanner_base::getLike()->getPtID());
    })
    .def_static("print", [](double val, const std::string &name, const unsigned int rank, const unsigned long pointID)
    {
        get_printer().get_stream()->print(val, name, rank, pointID);
    })
    .def_static("transform", [](Gambit::Scanner::hyper_cube_ref<double> unit)
    {
        py::dict physical;
        //auto &map = getLike()->getMap();
        static std::unordered_map<std::string, double> map;
        get_prior().transform(unit, map);
        
        for (auto &&m : map)
            physical[py::cast(m.first)] = py::cast(m.second);
        
        return physical;
    })
    .def_static("transform", [](Gambit::Scanner::hyper_cube_ref<double> unit, std::unordered_map<std::string, double> &physical)
    {
        get_prior().transform(unit, physical);
    })
    .def_static("transform", [](Gambit::Scanner::hyper_cube_ref<double> unit, py::dict physical)
    {
        //auto &map = getLike()->getMap();
        static std::unordered_map<std::string, double> map;
        get_prior().transform(unit, map);
        for (auto &&m : map)
            physical[py::cast(m.first)] = py::cast(m.second);
    })
    .def_static("transform_to_vec", [](Gambit::Scanner::hyper_cube_ref<double> unit)
    {
        //auto &map = getLike()->getMap();
        static std::unordered_map<std::string, double> map;
        get_prior().transform(unit, map);
        auto params = get_prior().getShownParameters();
        Gambit::Scanner::vector<double> vec(params.size());
        
        for (size_t i = 0, end = params.size(); i < end; ++i)
            vec[i] = map[params[i]];
        
        return vec;
    })
    .def_static("transform", [](Gambit::Scanner::hyper_cube_ref<float> unitf)
    {
        Gambit::Scanner::vector<double> unit = unitf.template cast<double>();
        py::dict physical;
        //auto &map = getLike()->getMap();
        static std::unordered_map<std::string, double> map;
        get_prior().transform(unit, map);
        
        for (auto &&m : map)
            physical[py::cast(m.first)] = py::cast(m.second);
        
        return physical;
    })
    .def_static("transform", [](Gambit::Scanner::hyper_cube_ref<float> unitf, std::unordered_map<std::string, double> &physical)
    {
        Gambit::Scanner::vector<double> unit = unitf.template cast<double>();
        get_prior().transform(unit, physical);
    })
    .def_static("transform", [](Gambit::Scanner::hyper_cube_ref<float> unitf, py::dict physical)
    {
        Gambit::Scanner::vector<double> unit = unitf.template cast<double>();
        //auto &map = getLike()->getMap();
        static std::unordered_map<std::string, double> map;
        get_prior().transform(unit, map);
        for (auto &&m : map)
            physical[py::cast(m.first)] = py::cast(m.second);
    })
    .def_static("transform_to_vec", [](Gambit::Scanner::hyper_cube_ref<float> unitf)
    {
        Gambit::Scanner::vector<double> unit = unitf.template cast<double>();
        //auto &map = getLike()->getMap();
        static std::unordered_map<std::string, double> map;
        get_prior().transform(unit, map);
        auto params = get_prior().getShownParameters();
        Gambit::Scanner::vector<double> vec(params.size());
        
        for (size_t i = 0, end = params.size(); i < end; ++i)
            vec[i] = map[params[i]];
        
        return vec;
    })
    .def_static("inverse_transform", [](std::unordered_map<std::string, double> &physical)
    {
        Gambit::Scanner::vector<double> unit(get_prior().size());
        get_prior().inverse_transform(physical, unit);
        
        return unit;
    })
    .def_static("inverse_transform", [](py::dict physical)
    {
        Gambit::Scanner::vector<double> unit(get_prior().size());
        std::unordered_map<std::string, double> map;
        for (auto &&m : physical)
            map[m.first.template cast<std::string>()] = m.second.template cast<double>();
        
        get_prior().inverse_transform(map, unit);
        
        return unit;
    })
    .def_static("inverse_transform", [](std::unordered_map<std::string, double> &physical, Gambit::Scanner::hyper_cube_ref<double> unit)
    {
        get_prior().inverse_transform(physical, unit);
    })
    .def_static("inverse_transform", [](py::dict physical, Gambit::Scanner::hyper_cube_ref<double> unit)
    {
        std::unordered_map<std::string, double> map;
        for (auto &&m : physical)
            map[m.first.template cast<std::string>()] = m.second.template cast<double>();
        
        get_prior().inverse_transform(map, unit);
    })
    .def_property_readonly_static("point_id", [](py::object)
    {
        return scanner_base::getLike()->getPtID();
    })
    .def_property_readonly_static("printer", [](py::object)->Gambit::Printers::BasePrinterManager&
    {
        return get_printer();
    })
    .def_property_readonly_static("loglike_hypercube", [](py::object)
    {
        static std::shared_ptr<scanner_base::s_hyper_func> like_hypercube(scanner_base::getLike() == nullptr ? nullptr : new scanner_base::s_hyper_func(*scanner_base::getLike().get()));
                                        
        return like_hypercube;
    })
    .def_property_readonly_static("loglike_physical", [](py::object)
    {
        static std::shared_ptr<scanner_base::s_phys_func> like_physical(scanner_base::getLike() == nullptr ? nullptr : new scanner_base::s_phys_func(*scanner_base::getLike().get()));
                                        
        return like_physical;
    })
    .def_property_readonly_static("log_target_density", [](py::object)
    {
        static std::shared_ptr<scanner_base::s_phys_pr_func> like_prior_physical(scanner_base::getLike() == nullptr ? nullptr : new scanner_base::s_phys_pr_func(*scanner_base::getLike().get()));
                                        
        return like_prior_physical;
    })
    .def_property_readonly_static("log_prior_density", [](py::object)
    {
        static std::shared_ptr<scanner_base::s_pr_func> prior_physical(scanner_base::getLike() == nullptr ? nullptr : new scanner_base::s_pr_func(*scanner_base::getLike().get()));
                                        
        return prior_physical;
    })
    .def_property_readonly_static("loglike", [](py::object)
    {
        return scanner_base::getLike();
    })
    .def_property_readonly_static("args", [](py::object)
    {
        static py::dict opts = ::Gambit::Scanner::yaml_to_dict(scanner_base::getNode());
        
        return opts;
    })
    .def_property_readonly_static("init_args", [](py::object)
    {
        static py::dict init_opts = ::Gambit::Scanner::yaml_to_dict(scanner_base::getNode()["init"] ? scanner_base::getNode()["init"] : YAML::Node());
                        
        return init_opts;
    })
    .def_property_readonly_static("run_args", [](py::object)
    {
        static py::dict run_opts = ::Gambit::Scanner::yaml_to_dict(scanner_base::getNode()["run"] ? scanner_base::getNode()["run"] : YAML::Node());
                        
        return run_opts;
    })
    .def_property_readonly_static("parameter_names", [](py::object)
    {
        static py::list names = scanner_base::to_list<std::string>(get_prior().getShownParameters());
        
        return names;
    })
    .def_property_readonly_static("mpi_rank", [](py::object)
    {
        static int my_rank = scanner_base::rank();
                        
        return my_rank;
    })
    .def_property_readonly_static("mpi_size", [](py::object)
    {
        static int tasks = scanner_base::numtasks();
        
        return tasks;
    })
    .def_property_readonly_static("dim", [](py::object)
    {
        static int dim = get_dimension();
                        
        return dim;
    })
    .def_static("assign_aux_numbers", [](py::args params)
    {
        for (auto &&param : params)
            ::Gambit::Printers::get_aux_param_id(param.template cast<std::string>());
    });

}
