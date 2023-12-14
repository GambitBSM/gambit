#ifndef __SCAN_PYTHON_UTILS_HPP__
#define __SCAN_PYTHON_UTILS_HPP__

#include "gambit/Utils/begin_ignore_warnings_pybind11.hpp"
#include "gambit/Utils/begin_ignore_warnings_eigen.hpp"
#include <pybind11/embed.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include "gambit/Utils/end_ignore_warnings.hpp"

namespace py = pybind11;

namespace Gambit
{
    
    namespace Scanner
    {
        
        /**
         * @brief Determines the Python type of a given object.
         * 
         * This function inspects a Python object and returns a string representation of its type.
         * 
         * @param obj The Python object whose type is to be determined.
         * @return A string representation of the Python object's type.
         */
        inline std::string pytype(py::handle o)
        {
            return o.attr("__class__").attr("__name__").template cast<std::string>();
        }
        
        /**
         * @brief Checks if a given Python object matches a specified type.
         * 
         * This function inspects a Python object and checks if it matches the specified type.
         * 
         * @tparam T The type to check against.
         * @param args The Python kwargs object containing the arguments.
         * @param type The key in the kwargs to check the type of. Defaults to "dtype".
         * @param def_type The default return value if the type key is not found in the kwargs. Defaults to false.
         * @return True if the object matches the specified type, false otherwise.
         */
        template<typename T>
        bool is_pytype(py::kwargs args, const std::string &type = "dtype", bool def_type = false)
        {
            if (args.contains(type.c_str())) 
            {
                auto arg = args[type.c_str()];
                
                if (pytype(arg) == "type" ? py::handle(arg).is(T().get_type()) : 
                    pytype(arg) == "str" || pytype(arg) == "unicode" ? arg.template cast<std::string>() == pytype(T()) : false)
                    return true;
                else
                    return false;
            }
            else
                return def_type;
        }
        
        /**
         * @brief Converts a YAML node to a Python dictionary.
         * 
         * This function recursively traverses a YAML node and constructs a corresponding Python dictionary.
         * 
         * @param node The YAML node to be converted.
         * @return A Python dictionary that represents the YAML node.
         */
        inline py::object yaml_to_dict(const YAML::Node &node)
        {
            if (node.IsNull())
            {
                return py::dict();
            }
            else if (node.IsMap())
            {
                py::dict d;
                for (auto &&n : node)
                {
                    d[py::cast(n.first.template as<std::string>())] = yaml_to_dict(n.second);
                }
                
                return d;
            }
            else if (node.IsSequence())
            {
                py::list l;
                
                for (auto &&n : node)
                {
                    l.append(yaml_to_dict(n));
                }
                
                return l;
            }
            else if (node.IsScalar())
            {
                int ret_i;
                if (YAML::convert<int>::decode(node, ret_i))
                {
                    return py::cast(ret_i);
                }

                double ret_d;
                if (YAML::convert<double>::decode(node, ret_d))
                {
                    return py::cast(ret_d);
                }

                bool ret_b;
                if (YAML::convert<bool>::decode(node, ret_b))
                {
                    return py::cast(ret_b);
                }

                return py::cast(node.template as<std::string>());
            }
            else
            {
                return py::object();
            }
        }
        
        /**
         * @brief Converts a Python dictionary to a YAML node.
         * 
         * This function recursively traverses a Python dictionary and constructs a corresponding YAML node.
         * 
         * @param o The Python object to be converted.
         * @return A YAML node that represents the Python dictionary.
         */
        inline YAML::Node dict_to_yaml(py::handle o)
        {
            YAML::Node node;
            std::string type = pytype(o);
            
            if (type == "dict")
            {
                for (auto &&it : py::cast<py::dict>(o))
                {
                    node[dict_to_yaml(it.first)] = dict_to_yaml(it.second);
                }
            }
            else if(type == "list")
            {
                for (auto &&it : py::cast<py::list>(o))
                {
                    node.push_back(dict_to_yaml(it));
                }
                
            }
            else if(type == "tuple")
            {
                for (auto &&it : py::cast<py::tuple>(o))
                {
                    node.push_back(dict_to_yaml(it));
                }
                
            }
            else if (type == "float" || type == "float64")
            {
                node = o.template cast<double>();
            }
            else if (type == "int")
            {
                node = o.template cast<int>();
            }
            else if (type == "str" || type == "unicode")
            {
                node = o.template cast<std::string>();
            }
            else if (type == "bool")
            {
                node = o.template cast<bool>();
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
                
    }
    
}

#endif
