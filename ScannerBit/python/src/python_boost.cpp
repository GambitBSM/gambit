#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <dlfcn.h>
#include <memory>

#include "interface.hpp"
#include "python_utils_boost.hpp"
#include "run_scan_boost.hpp"

namespace py = boost::python;
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
            
            struct printer_wrapper_cont{std::shared_ptr<printer_wrapper> printer;};
            
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
                
                std::shared_ptr<printer_wrapper_cont> get_printer()
                {
                    return std::shared_ptr<printer_wrapper_cont>(new printer_wrapper_cont{printer});
                }
                
                static py::object dianostic(py::tuple args, py::dict)
                {
                    scan &self = py::extract<scan &>(args[0]);
                    
                    for (int i = 1, end = py::len(args); i < end; i++)
                    {
                        self.diag(std::string(py::extract<std::string>(args[i])));
                    }
                    
                    return py::object();
                }
                
                static void print(const std::string &key, const double &value)
                {
                    printer_manager->aux_printer(key, value);
                }
            
                int run(py::object file_obj, py::object func_obj, py::object prior_obj, bool restart)
                {
                    try
                    {
                        scanpy::python_prior *prior = 0;
                        scanpy::python_factory *factory = 0;
                        
                        if (PyCallable_Check(func_obj.ptr()))
                        {
                            factory = new scanpy::python_factory(func_obj, printer);
                        }
                        else if (pytype(func_obj) == "dict")
                        {
                            py::dict d = py::dict(func_obj);
                    
                            for (auto it = py::stl_input_iterator< py::tuple >(d.items()), 
                                     end = py::stl_input_iterator< py::tuple >(); it != end; it++)
                            {
                                if (pytype((*it)[0]) != "str")
                                {
                                    throw std::runtime_error("Inputted purpose is not a \'str\'");
                                }
                                
                                if (not PyCallable_Check(py::object((*it)[1]).ptr()))
                                {
                                    throw std::runtime_error("Inputted function for purpose \"" + pyconvert<std::string>((*it)[0]) + " is call callable.");
                                }
                            }
                            
                            factory = new scanpy::python_factory(func_obj, printer);
                        }
                        
                        if (PyCallable_Check(prior_obj.ptr()))
                        {
                            prior = new scanpy::python_prior(prior_obj);
                        }
                        
                        if (pytype(file_obj) == "str")
                        {
                            std::string filename = std::string(py::extract<std::string>(file_obj));
                        
                            return gambit_scan.run_scan_str(&filename, factory, prior, !restart);
                        }
                        else if (pytype(file_obj) == "dict")
                        {
                            YAML::Node node = pyyamlconvert(file_obj);
                            
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
            };

            std::shared_ptr<vec_type> std_vector_init( py::object l)
            {
                return std::shared_ptr<vec_type>(new vec_type(py::stl_input_iterator< double >(l), py::stl_input_iterator< double >()));
            }
            
            std::shared_ptr<scanpy::fake_vector> fake_vector_init( py::object l)
            {
                return std::shared_ptr<scanpy::fake_vector>(new scanpy::fake_vector(py::stl_input_iterator< double >(l), py::stl_input_iterator< double >()));
            }
            
            std::shared_ptr<map_type> std_map_init( py::dict l)
            {
                map_type *map = new map_type();
                for(auto it = py::stl_input_iterator< py::tuple >(l.items()), 
                        end = py::stl_input_iterator< py::tuple >(); it != end; ++it)
                {
                    (*map)[pyconvert<std::string>((*it)[0])] = pyconvert<double>((*it)[1]);
                }
                
                return std::shared_ptr<map_type>(map);
            }
            
            std::string std_vector_format(vec_type &x)
            {
                std::stringstream ss;
                
                if (x.size() == 0)
                    return "[]";
                    
                ss << "[" << x[0];
                for (int i = 1, end = x.size(); i < end; i++)
                {
                    ss << ", " << x[i];
                }
                ss << "]";
                
                return ss.str();
            }
            
            std::string fake_vector_format(scanpy::fake_vector &x)
            {
                std::stringstream ss;
                
                if (x.size() == 0)
                    return "[]";
                    
                ss << "[" << x[0];
                for (int i = 1, end = x.size(); i < end; i++)
                {
                    ss << ", " << x[i];
                }
                ss << "]";
                
                return ss.str();
            }
            
            std::string std_map_format(map_type &x)
            {
                std::stringstream ss;
                
                if (x.size() == 0)
                    return "{}";
                    
                auto it = x.begin(), end = x.end();
                ss << "{" << it->first << ": " << it->second;
                for (++it; it != end; ++it)
                {
                    ss << it->first << ": " << it->second << ", ";
                }
                ss << "}";
                
                return ss.str();
            }
            
            void printer_aux(scanpy::printer_wrapper_cont &in, const std::string &key, const double &val)
            {
                in.printer->aux_printer(key, val);
            }
            
            void printer_main1(scanpy::printer_wrapper_cont &in, const std::string &key, const double &val)
            {
                in.printer->main_printer(key, val);
            }
            
            void printer_main2(scanpy::printer_wrapper_cont &in, map_type &map)
            {
                in.printer->main_printer(map);
            }
            
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
            
        }
        
    }
    
}

BOOST_PYTHON_MODULE(BoostScannerBit)
{
    py::class_<scanpy::scan>("scan", py::init<bool>())
        .def("run", &scanpy::scan::run, (py::arg("inifile"), py::arg("lnlike")="", py::arg("prior")="", py::arg("restart")=false))
        .def("diagnostics", py::raw_function(&scanpy::scan::dianostic))
        .def("get_printer", &scanpy::scan::get_printer);
    
    py::def("print", &scanpy::scan::print);
        
    py::def("ensure_size", &scanpy::ensure_size_vec);
    
    py::def("ensure_size", &scanpy::ensure_size_fake);
    
    py::class_<vec_type, std::shared_ptr<vec_type>>("std_vector")
        .def("__init__", py::make_constructor(&scanpy::std_vector_init))
        .def("__repr__", &scanpy::std_vector_format)
        .def("__str__", &scanpy::std_vector_format)
        .def("ensure_size", &scanpy::ensure_size_vec)
        .def(py::vector_indexing_suite< vec_type >());
       
    py::class_<map_type, std::shared_ptr<map_type>>("std_unordered_map")
        .def("__init__", py::make_constructor(&scanpy::std_map_init))
        .def("__repr__", &scanpy::std_map_format)
        .def("__str__", &scanpy::std_map_format)
        .def(py::map_indexing_suite< map_type >());
       
    py::class_<scanpy::fake_vector, std::shared_ptr<scanpy::fake_vector>>("fake_vector")
        .def("__init__", py::make_constructor(&scanpy::fake_vector_init))
        .def("__repr__", &scanpy::fake_vector_format)
        .def("__str__", &scanpy::fake_vector_format)
        .def("ensure_size", &scanpy::ensure_size_fake)
        .def(py::vector_indexing_suite< scanpy::fake_vector >());
       
    py::class_<scanpy::printer_wrapper_cont, std::shared_ptr<scanpy::printer_wrapper_cont>>("printer_manager")
        .def("aux_printer", scanpy::printer_aux)
        .def("main_printer", scanpy::printer_main1)
        .def("main_printer", scanpy::printer_main2);
       
}
