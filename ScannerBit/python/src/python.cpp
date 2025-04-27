#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/eigen.h>
#include <dlfcn.h>
#include <memory>
#include <regex>
#include <tuple>
#ifdef WITH_HDF5
    #include <hdf5.h>
    #include <hdf5_hl.h>
#endif
#include "interface.hpp"
#include "python_utils.hpp"
#include "python.hpp"

namespace py = pybind11;
namespace scanpy = Gambit::Scanner::Python;

typedef std::unordered_map<std::string, double> map_type;
typedef std::vector<double> vec_type;

namespace Gambit
{
    
    namespace Scanner 
    {
        
        namespace Python
        {
            
            std::shared_ptr<printer_wrapper> printer_manager;
            
            class scan
            {
            private:
                scan_interface gambit_scan;
                diagnostics diag;
                std::shared_ptr<printer_wrapper> printer; 
                
            public:
                scan(bool init_mpi) : gambit_scan(init_mpi)
                {
                    printer_manager = printer = gambit_scan.get_printer();
                }
                
                std::shared_ptr<printer_wrapper> get_printer()
                {
                    return printer;
                }
                
                void dianostic(py::args args, py::kwargs)
                {
                    for (auto &&arg : args)
                    {
                        diag(arg.cast<std::string>());
                    }
                }
                
                static void print(const std::string &key, const double &value)
                {
                    printer_manager->aux_printer(key, value);
                }
            
                int run(py::object file_obj, py::object func_obj, py::object prior_obj, bool restart)
                {
                    try
                    {
                        Gambit::Priors::BasePrior *prior = 0;
                        scanpy::python_factory *factory = 0;
                        
                        if (PyCallable_Check(func_obj.ptr()))
                        {
                            factory = new scanpy::python_factory(func_obj, printer);
                        }
                        else if (py::isinstance<py::dict>(func_obj))
                        {
                            for (auto &&func : py::cast<py::dict>(func_obj))
                            {
                                if (not py::isinstance<py::str>(func.first))
                                {
                                    throw std::runtime_error("Inputted purpose is not a \'str\'");
                                }
                                
                                if (not PyCallable_Check(func.second.ptr()))
                                {
                                    throw std::runtime_error("Inputted function for purpose \"" + pyconvert<std::string>(func.first) + " is call callable.");
                                }
                            }
                            
                            factory = new scanpy::python_factory(func_obj, printer);
                        }
                        
                        if (!py::isinstance<py::none>(prior_obj))
                        {
                            if (pytype(prior_obj) != "type" && PyCallable_Check(prior_obj.ptr()))
                            {
                                prior = new scanpy::python_prior(prior_obj);
                            }
                            else
                            {
                                prior = new scanpy::python_prior_class(prior_obj);
                            }
                        }
                        
                        
                        if (py::isinstance<py::str>(file_obj))
                        {
                            std::string filename = pyconvert<std::string>(file_obj);
                        
                            return gambit_scan.run_scan_str(&filename, factory, prior, !restart);
                        }
                        else if (py::isinstance<py::dict>(file_obj))
                        {
                            YAML::Node node = pyyamlconvert(file_obj);

                            //std::cerr<<"DEBUG: Result of dict -> yaml conversion:"<<std::endl;
                            //std::cerr<<"-----------------"<<std::endl;
                            //std::cerr<<node<<std::endl;

                            return gambit_scan.run_scan_node(&node, factory, prior, !restart);
                        }
                        else
                        {
                            throw std::runtime_error("infile parameter should be either a str or dict.");
                            return -1;
                        }
                    }
                    catch(const std::exception& e)
                    {
                        throw std::runtime_error(e.what());
                        return -1;
                    }
                }
                
                ~scan(){}
            };
            
            void ensure_size_fake(scanpy::fake_vector &vec, size_t i)
            {
                if (vec.size() != i)
                {
                    vec.resize(i);
                    for (auto &&v : vec)
                    {
                        v = 0.5;
                    }
                }
            }
            
            void ensure_size_vec(std::vector<double> &, size_t)
            {
            } 
            
            void ensure_size_evec(hyper_cube_ref<double>, size_t)
            {
            }
            
        }
        
    }
    
}

PYBIND11_MAKE_OPAQUE(vec_type);
PYBIND11_MAKE_OPAQUE(map_type);
PYBIND11_MAKE_OPAQUE(scanpy::fake_vector);

PYBIND11_MODULE(ScannerBit, m)
{
    
    py::class_<scanpy::scan>(m, "scan")
        .def(py::init<bool>())
        .def("run", &scanpy::scan::run, py::arg("inifile"), py::arg("lnlike")="", py::arg("prior")=py::none(), py::arg("restart")=false)
        .def("diagnostics", &scanpy::scan::dianostic)
        .def("get_printer", &scanpy::scan::get_printer);
        
    py::class_<scanpy::printer_wrapper, std::shared_ptr<scanpy::printer_wrapper>>(m, "printer_manager")
        .def("aux_printer", [](scanpy::printer_wrapper &in, const std::string &key, const double &val)
        {
            in.aux_printer(key, val);
        })
        .def("main_printer", [](scanpy::printer_wrapper &in, const std::string &key, const double &val)
        {
            in.main_printer(key, val);
        })
        .def("main_printer", [](scanpy::printer_wrapper &in, map_type &map)
        {
            in.main_printer(map);
        });

#ifdef WITH_MPI 
    m.attr("WITH_MPI") = true;
#else
    m.attr("WITH_MPI") = false;  
#endif

    m.def("check_hdf5_version", [&]()
    {
#ifdef WITH_HDF5
        std::string name = "INFO:" H5_VERSION;
        std::smatch m;
        std::regex e ("^INFO:([0-9]+)\\.([0-9]+)\\.([0-9]+)(-patch([0-9]+))?");
        unsigned int major, minor, patch;
        
        if (std::regex_match (name,m,e))
        {
            if (m.size() < 4)
                std::runtime_error("check_hdf5_version: internal hdf5 version error");
            
            std::stringstream(m[1]) >> major;
            std::stringstream(m[2]) >> minor;
            std::stringstream(m[3]) >> patch;
            H5check_version(major, minor, patch);
        }
        else
        {
            throw std::runtime_error("check_hdf5_version: internal hdf5 version error");
        }
#endif
    });
    
    m.def("get_hdf5_version", [&]()
    {
        unsigned int major=0, minor=0, patch=0;
#ifdef WITH_HDF5
        std::string name = "INFO:" H5_VERSION;
        std::smatch m;
        std::regex e ("^INFO:([0-9]+)\\.([0-9]+)\\.([0-9]+)(-patch([0-9]+))?");
        
        if (std::regex_match (name,m,e))
        {
            if (m.size() < 4)
                std::runtime_error("get_hdf5_version: internal hdf5 version error");
            
            std::stringstream(m[1]) >> major;
            std::stringstream(m[2]) >> minor;
            std::stringstream(m[3]) >> patch;
            return std::make_tuple(major, minor, patch);
        }
        else
        {
            throw std::runtime_error("get_hdf5_version: internal hdf5 version error");
        }
#endif
        return std::make_tuple(major, minor, patch);
    });
    
    m.def("print", &scanpy::scan::print);
        
    m.def("ensure_size", &scanpy::ensure_size_vec);
    
    m.def("ensure_size", &scanpy::ensure_size_evec);
    
    m.def("ensure_size", &scanpy::ensure_size_fake);
    
    py::bind_vector<vec_type, std::shared_ptr<vec_type>>(m, "std_vector")
        .def("ensure_size", &scanpy::ensure_size_vec);
        
    py::bind_vector<scanpy::fake_vector, std::shared_ptr<scanpy::fake_vector>>(m, "fake_vector")
        .def("ensure_size", &scanpy::ensure_size_fake);
       
    py::bind_map<map_type, std::shared_ptr<map_type>>(m, "std_unordered_map")
    .def(py::init<>())
    .def(py::init([](py::handle d)
    {
        auto m = new map_type();
        for (auto &&it : py::cast<py::dict>(d))
        {
            (*m)[it.first.cast<std::string>()] = it.second.cast<double>();
        }
        
        return std::shared_ptr<map_type>(m);
    }))
    .def("has_key", [](std::unordered_map<std::string, double> &map, const std::string &key) -> bool
    {
        return map.find(key) != map.end();
    })
    .def("keys", [](py::handle o) -> py::list
    {
        return py::list(py::iter(o));
    })//, py::keep_alive<0, 1>())
    .def("items", [](py::handle o) -> py::list
    {
        return py::list(o.begin());
    })//, py::keep_alive<0, 1>())
    .def("values", [](py::handle o) -> py::list
    {
        py::list l;
        for (auto &&i : py::cast<py::dict>(o))
            l.append(i.second);
        
        return l;
    });//, py::keep_alive<0, 1>());
    
    py::implicitly_convertible<py::dict, std::unordered_map<std::string, double>>();
    
}
