#ifndef __SCANNERBIT_PYTHON_UTILS_HPP__
#define __SCANNERBIT_PYTHON_UTILS_HPP__

#include <iterator>
#include <pybind11/pybind11.h>
//#include <pybind11/stl.h>
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
                
                if (py::isinstance<py::dict>(o))
                {
                    for (auto &&it : py::cast<py::dict>(o))
                    {
                        node[pyyamlconvert(it.first)] = pyyamlconvert(it.second);
                    }
                }
                else if(py::isinstance<py::list>(o))
                {
                    for (auto &&it : py::cast<py::list>(o))
                    {
                        node.push_back(pyyamlconvert(it));
                    }
                    
                }
                else if(py::isinstance<py::tuple>(o))
                {
                    for (auto &&it : py::cast<py::tuple>(o))
                    {
                        node.push_back(pyyamlconvert(it));
                    }
                    
                }
                else if (py::isinstance<py::bool_>(o))
                {
                    node = pyconvert<bool>(o);
                }
                else if (py::isinstance<py::int_>(o))
                {
                    node = pyconvert<int>(o);
                }
                else if (py::isinstance<py::float_>(o))
                {
                    node = pyconvert<double>(o);
                }
                else if (py::isinstance<py::str>(o))
                {
                    node = pyconvert<std::string>(o);
                }
                else if (py::isinstance<py::none>(o))
                {
                    node = YAML::Node(); // Needs to be a Null node, not just an empty node (YAML::NodeType::Null)
                }
                else
                {
                    throw std::invalid_argument("Error converting python dictionary to YAML node:  " + pytype(o) + " type not recognized.");
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
