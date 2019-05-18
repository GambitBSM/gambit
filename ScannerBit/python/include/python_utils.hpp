#ifndef __SCANNERBIT_PYTHON_UTILS_HPP__
#define __SCANNERBIT_PYTHON_UTILS_HPP__

#include <iterator>
#include <pybind11/pybind11.h>
#include <yaml-cpp/yaml.h>

namespace Gambit
{
    
    namespace Scanner
    {
        
        namespace Python
        {
            namespace py = pybind11;
            
            inline std::string pytype(py::handle o)
            {
                return o.attr("__class__").attr("__name__").cast<std::string>();
            }
            
            template<typename T>
            T pyconvert(py::handle o)
            {
                return o.cast<T>();
            }
            
            inline YAML::Node pyyamlconvert(py::handle o)
            {
                YAML::Node node;
                std::string type = pytype(o);
                
                if (type == "dict")
                {
                    for (auto &&it : py::cast<py::dict>(o))
                    {
                        node[pyyamlconvert(it.first)] = pyyamlconvert(it.second);
                    }
                }
                else if(type == "list")
                {
                    for (auto &&it : py::cast<py::list>(o))
                    {
                        node.push_back(pyyamlconvert(it));
                    }
                    
                }
                else if(type == "tuple")
                {
                    for (auto &&it : py::cast<py::tuple>(o))
                    {
                        node.push_back(pyyamlconvert(it));
                    }
                    
                }
                else if (type == "float")
                {
                    node = pyconvert<double>(o);
                }
                else if (type == "int")
                {
                    node = pyconvert<int>(o);
                }
                else if (type == "str" || type == "unicode")
                {
                    node = pyconvert<std::string>(o);
                }
                else if (type == "bool")
                {
                    node = pyconvert<bool>(o);
                }
                else if (type == "NoneType")
                {
                    node = YAML::Node();
                }
                else
                {
                    throw std::invalid_argument("Error converting python dictionary to YAML node:  " + type + " type not recognized.");
                }
                
                return node;
            }
            
            class fake_vector : public std::vector<double>
            {
            private:
                typedef std::vector<double> vec_type;
                
            public:
                using vec_type::vec_type;
            };
            
        }
        
    }
    
}

#endif
