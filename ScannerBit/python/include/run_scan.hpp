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
                    scan_err << "'inverse_transfrom' method is not defined" << scan_end;
                }
                
                double log_prior_density(const std::unordered_map<std::string, double> &) const
                {
                    scan_err << "'log_prior_density' method is not defined" << scan_end;
                    return 0.0;
                }
            };

            //int run_scan(IniParser::Parser &iniFile, const Gambit::Scanner::Factory_Base *, Gambit::Priors::BasePrior *, bool resume);

        }
        
    }
    
}

#endif
