//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Defines the python scannerbit module to be 
///  used in the python plugins.
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

typedef std::unordered_map<std::string, double> map_doub_type_;
typedef std::vector<std::string> vec_str_type_;

/**
 * @brief A macro to retrieve a value from the INI file.
 * 
 * This macro is used to retrieve a value from the INI file used by the scan plugin. The value is retrieved based on a given key.
 */
#define __SCAN_PLUGIN_GET_INIFILE_VALUE__(GET_INIFILE_VALUE)                                            \
{                                                                                                       \
    using namespace Gambit::Scanner;                                                                    \
                                                                                                        \
    if (args.contains("default"))                                                                       \
    {                                                                                                   \
        if (is_pytype<py::int_>(args, "dtype"))                                                         \
            return py::cast(GET_INIFILE_VALUE<int>(val, args["default"].template cast<int>()));         \
        else if (is_pytype<py::str>(args, "dtype"))                                                     \
            return py::cast(GET_INIFILE_VALUE<std::string>(val,                                         \
                                                           args["default"].template cast<std::string>() \
                                                           ));                                          \
        else if (is_pytype<py::list>(args, "dtype"))                                                    \
        {                                                                                               \
            py::list def = args["default"].template cast<py::list>();                                   \
            py::list list;                                                                              \
                                                                                                        \
            if (is_pytype<py::int_>(args, "etype"))                                                     \
            {                                                                                           \
                std::vector<int> defv;                                                                  \
                for (auto &&l : def)                                                                    \
                    defv.push_back(l.template cast<int>());                                             \
                                                                                                        \
                std::vector<int> ret = GET_INIFILE_VALUE<std::vector<int>>(val, defv);                  \
                                                                                                        \
                for (auto &&r : ret)                                                                    \
                    list.append(r);                                                                     \
            }                                                                                           \
            else if (is_pytype<py::str>(args, "etype"))                                                 \
            {                                                                                           \
                std::vector<std::string> defv;                                                          \
                for (auto &&l : def)                                                                    \
                    defv.push_back(l.template cast<std::string>());                                     \
                                                                                                        \
                std::vector<std::string> ret = GET_INIFILE_VALUE<std::vector<std::string>>(val, defv);  \
                                                                                                        \
                for (auto &&r : ret)                                                                    \
                    list.append(r);                                                                     \
            }                                                                                           \
            else                                                                                        \
            {                                                                                           \
                std::vector<double> defv;                                                               \
                for (auto &&l : def)                                                                    \
                    defv.push_back(l.template cast<double>());                                          \
                                                                                                        \
                std::vector<double> ret = GET_INIFILE_VALUE<std::vector<double>>(val, defv);            \
                                                                                                        \
                for (auto &&r : ret)                                                                    \
                    list.append(r);                                                                     \
            }                                                                                           \
                                                                                                        \
            return list;                                                                                \
        }                                                                                               \
        else                                                                                            \
            return py::cast(GET_INIFILE_VALUE<double>(val, args["default"].template cast<double>()));   \
    }                                                                                                   \
    else                                                                                                \
    {                                                                                                   \
        if (is_pytype<py::int_>(args, "dtype"))                                                         \
            return py::cast(GET_INIFILE_VALUE<int>(val));                                               \
        else if (is_pytype<py::bool_>(args, "dtype"))                                                   \
            return py::cast(GET_INIFILE_VALUE<bool>(val));                                              \
        else if (is_pytype<py::str>(args, "dtype"))                                                     \
            return py::cast(GET_INIFILE_VALUE<std::string>(val));                                       \
        else if (is_pytype<py::list>(args, "dtype"))                                                    \
        {                                                                                               \
            py::list list;                                                                              \
                                                                                                        \
            if (is_pytype<py::int_>(args, "etype"))                                                     \
            {                                                                                           \
                std::vector<int> ret = GET_INIFILE_VALUE<std::vector<int>>(val);                        \
                                                                                                        \
                for (auto &&r : ret)                                                                    \
                    list.append(r);                                                                     \
            }                                                                                           \
            else if (is_pytype<py::bool_>(args, "etype"))                                               \
            {                                                                                           \
                std::vector<bool> ret = GET_INIFILE_VALUE<std::vector<bool>>(val);                      \
                                                                                                        \
                for (auto &&r : ret)                                                                    \
                    list.append(bool(r));                                                               \
            }                                                                                           \
            else if (is_pytype<py::str>(args, "etype"))                                                 \
            {                                                                                           \
                std::vector<std::string> ret = GET_INIFILE_VALUE<std::vector<std::string>>(val);        \
                                                                                                        \
                for (auto &&r : ret)                                                                    \
                    list.append(r);                                                                     \
            }                                                                                           \
            else                                                                                        \
            {                                                                                           \
                std::vector<double> ret = GET_INIFILE_VALUE<std::vector<double>>(val);                  \
                                                                                                        \
                for (auto &&r : ret)                                                                    \
                    list.append(r);                                                                     \
            }                                                                                           \
                                                                                                        \
            return list;                                                                                \
        }                                                                                               \
        else                                                                                            \
            return py::cast(GET_INIFILE_VALUE<double>(val));                                            \
    }                                                                                                   \
}                                                                                                       \

/**
 * @brief This macro defines a lambda function that takes a string and a dictionary of keyword arguments.
 * The lambda function calls the `__SCAN_PLUGIN_GET_INIFILE_VALUE__` macro with `get_inifile_value` as an argument.
 * 
 * @param val A string that represents the value to be retrieved from the INI file.
 * @param args A dictionary of keyword arguments.
 * @return Returns a Python object that represents the value retrieved from the INI file.
 */
#define SCAN_PLUGIN_GET_INIFILE_VALUE_FUNC                  \
[](const std::string &val, py::kwargs args) -> py::object   \
__SCAN_PLUGIN_GET_INIFILE_VALUE__(get_inifile_value)        \

/**
 * @brief This macro defines a lambda function that takes a plugin_data object, a string, and a dictionary of keyword arguments.
 * The lambda function calls the `__SCAN_PLUGIN_GET_INIFILE_VALUE__` macro with `self.get_inifile_value` as an argument.
 * 
 * @param self A plugin_data object.
 * @param val A string that represents the value to be retrieved from the INI file.
 * @param args A dictionary of keyword arguments.
 * @return Returns a Python object that represents the value retrieved from the INI file.
 */
#define SCAN_PLUGIN_GET_INIFILE_VALUE_MEM_FUNC                                  \
[](plugin_data &self, const std::string &val, py::kwargs args) -> py::object    \
__SCAN_PLUGIN_GET_INIFILE_VALUE__(self.get_inifile_value)                       \

typedef std::unordered_map<std::string, double> map_doub_type_;
typedef std::vector<std::string> vec_str_type_;

PYBIND11_MAKE_OPAQUE(map_doub_type_)
PYBIND11_MAKE_OPAQUE(vec_str_type_)

/**
 * @brief A pybind11 module named "scannerbit".
 * 
 * This module is used to bind Python and C++ code using the pybind11 library. It binds the map and vector types and defines some functions and attributes for the module.
 * 
 * @param m The pybind11 module to which the bindings are added.
 */
PYBIND11_EMBEDDED_MODULE(scannerbit, m) 
{
    
    // Bind the map and vector types to the module
    py::bind_map<map_doub_type_, std::shared_ptr<map_doub_type_>>(m, "std_unordered_map_double");
    py::bind_vector<vec_str_type_, std::shared_ptr<vec_str_type_>>(m, "std_vector_string");
    
    // Check if MPI is enabled
#ifdef WITH_MPI
    m.attr("with_mpi") = py::bool_(true);
    m.def("rank", []()
    {
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
        return rank;
    });
    
     m.def("numtasks", []()
    {
        int numtasks;
        MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
        
        return numtasks;
    });
#else
    // If MPI is not enabled, define the "with_mpi", "rank", and "numtasks" attributes and functions for the module
    m.attr("with_mpi") = py::bool_(false);
    m.def("rank", [](){return 0;});
    m.def("numtasks", [](){return 1;});
#endif
    
    // Define the "get_inifile_value" function for the module
    m.def("assign_aux_numbers", [](py::args params)
    {
        for (auto &&param : params)
            ::Gambit::Printers::get_aux_param_id(param.template cast<std::string>());
    });
    
    // Bind the "printer" class to the module
    py::class_<Gambit::Printers::BaseBasePrinter, std::unique_ptr<Gambit::Printers::BaseBasePrinter, py::nodelete>>(m, "printer")
    .def("print", [](Gambit::Printers::BaseBasePrinter &self, double in, const std::string& label,
                   const int vertexID, const unsigned int rank,
                   const unsigned long pointID)
    {
        self.print(in, label, vertexID, rank, pointID);
    })
    .def("print", [](Gambit::Printers::BaseBasePrinter &self, double in, const std::string& label,
                   const unsigned int rank,
                   const unsigned long pointID)
    {
        self.print(in, label, rank, pointID);
    })
    .def("flush", [](Gambit::Printers::BaseBasePrinter &self)
    {
        self.flush();
    })
    .def("reset", [](Gambit::Printers::BaseBasePrinter &self, bool force)
    {
        self.reset(force);
    }, py::arg("force")=false);
    
    // Bind the "prior" class to the module
    py::class_<Gambit::Priors::BasePrior, std::unique_ptr<Gambit::Priors::BasePrior, py::nodelete>>(m, "prior")
    .def("transform", [](Gambit::Priors::BasePrior &self, Gambit::Scanner::hyper_cube_ref<double> unit, std::unordered_map<std::string, double> &physical)
    {
        self.transform(unit, physical);
    })
    .def("transform", [](Gambit::Priors::BasePrior &self, Gambit::Scanner::hyper_cube_ref<double> unit, py::dict physical)
    {
        static std::unordered_map<std::string, double> map;
        self.transform(unit, map);
        
        for (auto &&m : map)
            physical[py::cast(m.first)] = py::cast(m.second);
    })
    .def("transform", [](Gambit::Priors::BasePrior &self, Gambit::Scanner::hyper_cube_ref<double> unit)
    {
        py::dict physical;
        static std::unordered_map<std::string, double> map;
        
        self.transform(unit, map);
        
        for (auto &&m : map)
            physical[py::cast(m.first)] = py::cast(m.second);
        
        return physical;
    })
    .def("inverse_transform", [](Gambit::Priors::BasePrior &self, std::unordered_map<std::string, double> &physical, Gambit::Scanner::hyper_cube_ref<double> unit)
    {
        self.inverse_transform(physical, unit);
    })
    .def("inverse_transform", [](Gambit::Priors::BasePrior &self, py::dict physical, Gambit::Scanner::hyper_cube_ref<double> unit)
    {
        std::unordered_map<std::string, double> map;
        for (auto &&d : physical)
            map[d.first.template cast<std::string>()] = d.second.template cast<double>();
        
        self.inverse_transform(map, unit);
    })
    .def("inverse_transform", [](Gambit::Priors::BasePrior &self, std::unordered_map<std::string, double> &physical)
    {
        Gambit::Scanner::vector<double> unit(self.size());
        self.inverse_transform(physical, unit);
        
        return unit;
    })
    .def("inverse_transform", [](Gambit::Priors::BasePrior &self, py::dict physical)
    {
        Gambit::Scanner::vector<double> unit(self.size());
        std::unordered_map<std::string, double> map;
        for (auto &&d : physical)
            map[d.first.template cast<std::string>()] = d.second.template cast<double>();
        
        self.inverse_transform(map, unit);
        
        return unit;
    })
    .def("getShownParameters", [](Gambit::Priors::BasePrior &self)
    {
        return self.getShownParameters();
    })
    .def("getParameters", [](Gambit::Priors::BasePrior &self)
    {
        return self.getParameters();
    })
    .def("log_prior_density", [](Gambit::Priors::BasePrior &self, std::unordered_map<std::string, double> &physical)
    {
        return self.log_prior_density(physical);
    });
    
    //Mmember functions not exported:
    //  virtual void new_stream(const std::string&, const Options&) = 0;
    //  virtual void new_reader(const std::string&, const Options&) = 0;
    //  virtual void create_resume_reader() = 0;
    //  virtual BaseBaseReader* get_reader(const std::string&) = 0;
    //  virtual bool reader_exists(const std::string&) = 0;
    //  virtual void delete_reader(const std::string&) = 0;

    // Bind the "printer_interface" class to the module
    py::class_<Gambit::Scanner::printer_interface, std::unique_ptr<Gambit::Scanner::printer_interface, py::nodelete>>(m, "printer_interface")
    .def("new_stream", [&](Gambit::Scanner::printer_interface &self, const std::string name, py::kwargs opts)
    {
        self.new_stream(name, ::Gambit::Scanner::dict_to_yaml(opts));
    })
    .def("resume_mode", [&](Gambit::Scanner::printer_interface &self)
    {
        return self.resume_mode();
    })
    .def("set_resume_mode", [&](Gambit::Scanner::printer_interface &self, bool rflag){
        return self.set_resume_mode(rflag);
    })
    .def("get_stream", [&](Gambit::Scanner::printer_interface &self)
    {
        return self.get_stream("");
    })
    .def("get_stream", [&](Gambit::Scanner::printer_interface &self, const std::string &in)
    {
        return self.get_stream(in);
    })
    .def("delete_stream", [&](Gambit::Scanner::printer_interface &self)
    {
        self.delete_stream("");
    })
    .def("delete_stream", [&](Gambit::Scanner::printer_interface &self, const std::string &in)
    {
        self.delete_stream(in);
    })
    .def("finalise", [&](Gambit::Scanner::printer_interface &self)
    {
        self.finalise(false);
    })
    .def("finalise", [&](Gambit::Scanner::printer_interface &self, bool abnormal)
    {
        self.finalise(abnormal);
    })
    .def_static("assign_aux_numbers", [](py::args params)
    {
        for (auto &&param : params)
            ::Gambit::Printers::get_aux_param_id(param.template cast<std::string>());
    });
    
    typedef std::shared_ptr<Gambit::Scanner::Function_Base<double (std::unordered_map<std::string, double> &)>> s_ptr;
    typedef Gambit::Scanner::Function_Base<double (std::unordered_map<std::string, double> &)> s_func;
    using Gambit::Scanner::like_ptr;
    
    // Bind the "like" class to the module
    py::class_<s_func, s_ptr>(m, "like_ptr")
    .def("__call__", [](s_ptr self, Gambit::Scanner::hyper_cube_ref<double> vec)
    {
        return static_cast<like_ptr &>(self)(vec);
    })
    .def("__call__", [](s_ptr self, std::unordered_map<std::string, double> &map)
    {
        return static_cast<like_ptr &>(self)(map);
    })
    .def("__call__", [](s_ptr self, py::dict params)
    {
        auto &map = self->getMap();
        for(auto &&p: params)
            map[p.first.template cast<std::string>()] = p.second.template cast<double>();
        
        return static_cast<like_ptr &>(self)(map);
    })
    .def("getPtID", [&](s_ptr self)
    {
        return self->getPtID();
    })
    .def("getPrinter", [&](s_func &self)
    {
        return &self.getPrinter();
    })
    .def("getPrior", [&](s_func &self)
    {
        return &self.getPrior();
    });
    
}
