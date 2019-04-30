#ifndef __SCANNERBIT_PYTHON_RUN_SCAN_HPP__
#define __SCANNERBIT_PYTHON_RUN_SCAN_HPP__

#include <memory>
//#include "gambit/ScannerBit/factory_defs.hpp"
#include "gambit/ScannerBit/base_prior.hpp"
#include <yaml-cpp/yaml.h>
//#include "gambit/Utils/yaml_parser_base.hpp"

namespace Gambit
{
    
    namespace Scanner
    {
        
        template<typename T>
        class Function_Base;
        
        template<typename ret, typename... args>
        class Function_Base <ret (args...)> : public std::enable_shared_from_this<Function_Base <ret (args...)>>
        {
        private:
            void *main_printer;
            Priors::BasePrior *prior;
            std::string purpose;
            int myRealRank; 
            double purpose_offset;
            bool use_alternate_min_LogL;
            bool _scanner_can_quit;

            virtual void deleter(Function_Base <ret (args...)> *in) const
            {
                delete in;
            }

            virtual const std::type_info & type() const {return typeid(ret (args...));}

        public:
            Function_Base(double offset = 0.) : myRealRank(0), purpose_offset(offset), use_alternate_min_LogL(false), _scanner_can_quit(false) {}
            virtual ret main(const args&...) = 0;
            virtual ~Function_Base(){}
        };
        
        class Factory_Base
        {
        public:
                virtual void * operator() (const std::string &purpose) const = 0;
                virtual ~Factory_Base() {};
        };
            
            
            
        namespace Python
        {
            typedef void (*print_type)(std::unordered_map<std::string, double> &);
            class python_function_base : public Gambit::Scanner::Function_Base<double (std::unordered_map<std::string, double> &)>
            {
            private:
                void (*print)(std::unordered_map<std::string, double> &);
                boost::python::object obj;
                
            public:
                python_function_base(boost::python::object obj, print_type print) : obj(obj), print(print) {}
                
                double main(std::unordered_map<std::string, double> &map)
                {
                    print(map);
                    return double(boost::python::extract<double>(obj(boost::ref(map))));
                }
                
            };

            class python_factory : public Factory_Base
            {
            private:
                void (*print)(std::unordered_map<std::string, double> &);
                boost::python::dict map;
                
            public:
                python_factory(boost::python::object obj, print_type print) : print(print)
                {
                    if (std::string(boost::python::extract<std::string>(obj.attr("__class__").attr("__name__"))) == "dict")
                        map = boost::python::dict(obj);
                    else
                        map["Likelihood"] = obj;
                }
                
                void *operator()(const std::string &purpose) const
                {
                    return new python_function_base(map[purpose], print);
                }
            };
            
            class python_prior : public Gambit::Priors::BasePrior
            {
            private:
                boost::python::object obj;
                
            public:
                python_prior(boost::python::object obj) : obj(obj)
                {
                    fake_vector vec;
                    std::unordered_map<std::string, double> map;
                    obj(boost::ref(vec), boost::ref(map));
                    this->setSize(vec.size());
                    
                    for (auto it = map.begin(), end = map.end(); it != end; ++it)
                    {
                        this->param_names.push_back(it->first);
                    }
                }
                
                void transform(const std::vector<double> &vec, std::unordered_map<std::string, double> &map) const
                {
                    obj(boost::ref(vec), boost::ref(map));
                }
            };

            //int run_scan(IniParser::Parser &iniFile, const Gambit::Scanner::Factory_Base *, Gambit::Priors::BasePrior *, bool resume);

        }
        
    }
    
}

#endif
