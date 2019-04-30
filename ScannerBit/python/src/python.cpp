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

#include "diagnostics.hpp"
#include "python_utils.hpp"
#include "run_scan.hpp"

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
            
            typedef void (*print_aux_type)(const std::string &, const double &);
            static print_aux_type aux_printer;
            
            class scan
            {
            private:
                typedef int (*run_scan_node_type)(YAML::Node *, const Gambit::Scanner::Factory_Base *, Gambit::Priors::BasePrior *, bool);
                typedef int (*run_scan_str_type)(std::string *, const Gambit::Scanner::Factory_Base *, Gambit::Priors::BasePrior *, bool);
                typedef diagnostics *(*diag_factory_type)();
                typedef void (*diag_del_type)(diagnostics *);
                typedef void (*print_main_type)(std::unordered_map<std::string, double> &key_map);
                
                void *plugin;
                std::shared_ptr<diagnostics> diag;
                
                run_scan_str_type run_scan_str;
                run_scan_node_type run_scan_node;
                print_main_type main_printer;
                
            public:
                scan()
                {
                    plugin = dlopen ("lib/libScannerBit.so", RTLD_NOW|RTLD_GLOBAL);
                    if (bool(plugin))
                    {
                        run_scan_str = (run_scan_str_type)dlsym(plugin, "run_scan_str");
                        run_scan_node = (run_scan_node_type)dlsym(plugin, "run_scan_node");
                        diag_factory_type factory = (diag_factory_type)dlsym(plugin, "get_diagnostics");
                        diag_del_type diag_del = (diag_del_type)dlsym(plugin, "del_diagnostics");
                        main_printer = (print_main_type)dlsym(plugin, "print_main_parameters");
                        aux_printer = (print_aux_type)dlsym(plugin, "print_aux_parameters");
                        
                        const char *errmesg = dlerror();
                        if (errmesg != NULL)
                        {
                            std::string msg = "error loading lib/libScannerBit.so: " + std::string(errmesg) + "\n";
                            throw std::runtime_error(msg);
                        }
                        else
                        {
                            diag = std::shared_ptr<diagnostics>(factory(), diag_del);
                        }
                    }
                    else
                    {
                        std::string msg = "Cannot open lib/libScannerBit.so: " + std::string(dlerror());
                        throw std::runtime_error(msg);
                    }
                }
                
                static py::object dianostic(py::tuple args, py::dict)
                {
                    scan &self = py::extract<scan &>(args[0]);
                    
                    for (int i = 1, end = py::len(args); i < end; i++)
                    {
                        (*self.diag.get())(std::string(py::extract<std::string>(args[i])));
                    }
                    
                    return py::object();
                }
                
                static void print(const std::string &key, const double &value)
                {
                    (*aux_printer)(key, value);
                }
            
                int run(py::object file_obj, py::object func_obj, py::object prior_obj, bool restart)
                {
                    try
                    {
                        scanpy::python_prior *prior = 0;
                        scanpy::python_factory *factory = 0;
                        
                        if (std::string(py::extract<std::string>(func_obj.attr("__class__").attr("__name__"))) != "str")
                        {
                            factory = new scanpy::python_factory(func_obj, main_printer);
                        }
                        
                        if (std::string(py::extract<std::string>(prior_obj.attr("__class__").attr("__name__"))) != "str")
                        {
                            prior = new scanpy::python_prior(prior_obj);
                        }
                        
                        if (std::string(py::extract<std::string>(file_obj.attr("__class__").attr("__name__"))) == "str")
                        {
                            std::string filename = std::string(py::extract<std::string>(file_obj));
                        
                            return run_scan_str(&filename, factory, prior, !restart);
                        }
                        else if (std::string(py::extract<std::string>(file_obj.attr("__class__").attr("__name__"))) == "dict")
                        {
                            YAML::Node node = pyyconvert(file_obj);
                            
                            return run_scan_node(&node, factory, prior, !restart);
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
                
                ~scan(){dlclose(plugin);}
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
                for(auto it = py::stl_input_iterator< py::tuple >(l.items()), end = py::stl_input_iterator< py::tuple >(); it != end; ++it)
                {
                    (*map)[std::string(py::extract<std::string>((*it)[0]))] = double(py::extract<double>((*it)[1]));
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

BOOST_PYTHON_MODULE(ScannerBit)
{
    py::class_<scanpy::scan>("scan", py::init<>())
        .def("run", &scanpy::scan::run, (py::arg("inifile"), py::arg("lnlike")="", py::arg("prior")="", py::arg("restart")=false))
        .def("diagnostics", py::raw_function(&scanpy::scan::dianostic));
    
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
       
}
