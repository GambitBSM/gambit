#ifndef __SCANNERBIT_PYTHON_RUN_SCAN_HPP__
#define __SCANNERBIT_PYTHON_RUN_SCAN_HPP__

#include <memory>
#include "gambit/ScannerBit/factory_defs.hpp"
#include "gambit/ScannerBit/base_prior.hpp"
#include <yaml-cpp/yaml.h>
#include "interface.hpp"

namespace Gambit
{
    
    namespace Scanner
    {
        
        namespace Python
        {
            namespace py = pybind11;
            
            class __attribute__ ((visibility("default"))) python_function_base : public Gambit::Scanner::Function_Base<double (std::unordered_map<std::string, double> &)>
            {
            private:
                typedef std::shared_ptr<printer_wrapper> print_ptr;
                py::object obj;
                print_ptr print;
                
            public:
                python_function_base(py::object obj, print_ptr print) : obj(obj), print(print) {}
                
                double main(std::unordered_map<std::string, double> &map)
                {
                    print->main_printer(map);
                    return pyconvert<double>(obj(py::cast(&map)));
                }
                
            };

            class __attribute__ ((visibility("default"))) python_factory : public Factory_Base
            {
            private:
                typedef std::shared_ptr<printer_wrapper> print_ptr;
                py::dict map;
                print_ptr print;
                
            public:
                python_factory(py::object obj, print_ptr print) : print(print)
                {
                    if (pytype(obj) == "dict")
                        map = py::cast<py::dict>(obj);
                    else
                        map["Likelihood"] = obj;
                }
                
                void *operator()(const std::string &purpose) const
                {
                    return new python_function_base(map[py::cast(&purpose)], print);
                }
            };
            
            class __attribute__ ((visibility("default"))) python_prior_class : public Gambit::Priors::BasePrior
            {
            private:
                bool has_transform;
                bool has_inverse_transform;
                bool has_log_prior_density;
                py::object obj;
                py::object transform_obj;
                py::object inverse_transform_obj;
                py::object log_prior_density_obj;
                
            public:
                python_prior_class(py::object obj) : has_transform(false), 
                                                     has_inverse_transform(false),
                                                     has_log_prior_density(false),
                                                     obj(obj)
                {
                    if (py::hasattr(obj, "transform"))
                    {
                        has_transform = true;
                        transform_obj = obj.attr("transform");
                    }
                    
                    if (py::hasattr(obj, "inverse_transform"))
                    {
                        has_inverse_transform = true;
                        inverse_transform_obj = obj.attr("inverse_transform");
                    }
                    
                    if (py::hasattr(obj, "log_prior_density"))
                    {
                        has_log_prior_density = true;
                        log_prior_density_obj = obj.attr("log_prior_density");
                    }
                    
                    std::unordered_map<std::string, double> map;
                    
                    if (py::hasattr(obj, "__hyper_cube_size__"))
                    {
                        int dim = obj.attr("__hyper_cube_size__").cast<int>();
                        vector<double> vec(dim);
                        for (int i = 0; i < dim; ++i) vec[i] = 0.5;
                        this->setSize(dim);
                        transform_obj(py::cast(&vec), py::cast(&map));
                    }
                    else
                    {
                        fake_vector vec;
                        transform_obj(py::cast(&vec), py::cast(&map));
                        this->setSize(vec.size());
                    }
                    
                    for (auto it = map.begin(), end = map.end(); it != end; ++it)
                    {
                        this->param_names.push_back(it->first);
                    }
                }
                
                void transform(hyper_cube_ref<double> unit, std::unordered_map<std::string, double> &physical) const
                {
                    if (has_transform)
                        transform_obj(py::cast(unit), py::cast(&physical));
                    else
                        scan_err << "'transform' method is not defined" << scan_end;
                }
                
                void inverse_transform(const std::unordered_map<std::string, double> &physical, hyper_cube_ref<double> unit) const 
                {
                    if (has_inverse_transform)
                        inverse_transform_obj(py::cast(&physical), py::cast(unit));
                    else
                        scan_err << "'inverse_transform' method is not defined" << scan_end;
                }
                
                double log_prior_density(const std::unordered_map<std::string, double> &physical) const
                {
                    if (has_log_prior_density)
                        return log_prior_density_obj(py::cast(&physical)).cast<double>();
                    else
                    {
                        scan_err << "'log_prior_density' method is not defined" << scan_end;
                        return 0.0;
                    }
                }
                
                ~python_prior_class(){}
            };
            
            class __attribute__ ((visibility("default"))) python_prior : public Gambit::Priors::BasePrior
            {
            private:
                py::object obj;
                
            public:
                python_prior(py::object obj) : obj(obj)
                {
                    fake_vector vec;
                    std::unordered_map<std::string, double> map;
                    obj(py::cast(&vec), py::cast(&map));
                    this->setSize(vec.size());
                    
                    for (auto it = map.begin(), end = map.end(); it != end; ++it)
                    {
                        this->param_names.push_back(it->first);
                    }
                }
                
                void transform(hyper_cube_ref<double> unit, std::unordered_map<std::string, double> &physical) const
                {
                    obj(py::cast(unit), py::cast(&physical));
                }
                
                void inverse_transform(const std::unordered_map<std::string, double> &, hyper_cube_ref<double>) const 
                {
                    scan_err << "'inverse_transform' method is not defined" << scan_end;
                }
                
                double log_prior_density(const std::unordered_map<std::string, double> &) const
                {
                    scan_err << "'log_prior_density' method is not defined" << scan_end;
                    return 0.0;
                }
                
                ~python_prior(){}
            };

            //int run_scan(IniParser::Parser &iniFile, const Gambit::Scanner::Factory_Base *, Gambit::Priors::BasePrior *, bool resume);

        }
        
    }
    
}

#endif
