//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
/// \file
///  Utility Functions for the Gambit Scanner
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2013 July
///  \date 2014 Feb
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar, Dec
///
///  *********************************************

#ifndef __scanner_utils_hpp__
#define __scanner_utils_hpp__

#include <type_traits>
#include <utility>
#include <ostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/range.hpp>

#ifdef __GNUG__
  #include <cstdlib>
  #include <memory.h>
  #include <cxxabi.h>
#endif

#include "gambit/Utils/exceptions.hpp"
#include "gambit/Utils/local_info.hpp"
#include "gambit/Utils/util_macros.hpp"
#include "gambit/Utils/factory_registry.hpp"
#include "gambit/Utils/variadic_functions.hpp"
#include "gambit/Utils/yaml_options.hpp"

/// Defined to macros to output errors in the form:
/// scan_err << "error" << scan_end;
/// scan_warn << "warning" << scan_end;
/// @{
#define scan_err        SCAN_ERR
#define scan_warn       SCAN_WARN
#define scan_end        SCAN_END
#define scan_flush      SCAN_FLUSH
///@}

#define SCAN_ERR                                                \
Gambit::Scanner::Errors::_bool_() = true,                       \
Gambit::Scanner::Errors::_err_()                                \

#define SCAN_WARN                                               \
Gambit::Scanner::Errors::_bool_() = false,                      \
Gambit::Scanner::Errors::_warn_()                               \

#define SCAN_END_INTERNAL                                       \
(Gambit::Scanner::Errors::_bool_()) ?                           \
(                                                               \
    Gambit::Scanner::scan_error().raise(LOCAL_INFO,             \
        Gambit::Scanner::Errors::_err_().str()),                \
    Gambit::Scanner::Errors::_err_().str("")                    \
)                                                               \
:                                                               \
(                                                               \
    Gambit::Scanner::scan_warning().raise(LOCAL_INFO,           \
        Gambit::Scanner::Errors::_warn_().str()),               \
    Gambit::Scanner::Errors::_warn_().str("")                   \
)                                                               \

#define SCAN_END std::endl, SCAN_END_INTERNAL

#define SCAN_FLUSH std::flush, SCAN_END_INTERNAL                                                             \

namespace Gambit
{
    namespace Scanner
    {
        /**********************************/
        /****** error and warnings ********/
        /**********************************/

        namespace Errors
        {
            inline std::stringstream &_err_()
            {
                static std::stringstream error;
                return error;
            }

            inline std::stringstream &_warn_()
            {
                static std::stringstream warn;
                return warn;
            }

            inline bool &_bool_()
            {
                static bool error;
                return error;
            }
        }
        /// Scanner errors
        EXPORT_SYMBOLS error& scan_error();
        /// Scanner warnings
        EXPORT_SYMBOLS warning& scan_warning();

        /**********************************/
        /****** zip for range loop ********/
        /**********************************/

        /// Use for combine container in a range loop:  for (auto &&x : zip(a, b)){...}.
        template <typename... T>
        inline auto zip(const T&... containers) -> boost::iterator_range<boost::zip_iterator<decltype(boost::make_tuple(std::begin(containers)...))>>
        {
            return boost::make_iterator_range(
                boost::make_zip_iterator(boost::make_tuple(std::begin(containers)...)),
                boost::make_zip_iterator(boost::make_tuple(std::end(containers)...)));
        }

        /*********************************/
        /****** demangle function ********/
        /*********************************/

        /// Demangles gnu c++ name.
        inline std::string demangle(const std::string &in)
        {
#ifdef __GNUG__
            int status = -4;
            char *result = abi::__cxa_demangle (in.c_str(), NULL, NULL, &status);

            if (status)
            {
                    scan_err << "Error demangling \"" << in << "\" status code:  " << status << scan_end;
                    return in;
            }

            std::string ret(result);
            std::free(result);
            return ret;
#else
            return in;
#endif
        }

        /****************************************/
        /****** get_yaml_vector function ********/
        /****************************************/

        /// Input a vector from the yaml file of the following forms:
        /// vec: [a, b, ...]
        /// vec: a, b, ...
        /// vec: a; b; ...
        template <typename T>
        inline std::vector<T> get_yaml_vector(const YAML::Node &node)
        {
            if (node.IsSequence())
            {
                return node.as< std::vector<T> >();
            }
            else if (node.IsScalar())
            {
                std::string plug = node.as<std::string>();

                std::string::size_type pos = plug.find_first_of(",;");
                while (pos != std::string::npos)
                {
                    plug[pos] = ' ';
                    pos = plug.find_first_of(",;", pos + 1);
                }

                std::stringstream ss;
                ss << plug;
                std::vector<T> ret;
                T temp;
                while (ss >> temp) ret.push_back(temp);

                return ret;
            }
            else if (node.IsMap())
            {
                std::vector<T> ret;
                for (auto it = node.begin(), end = node.end(); it != end; ++it)
                {
                    ret.push_back(it->first.as<T>());
                }

                return ret;
            }
            else
            {
                scan_err << "\"" << node << "\" input value not usable in the inifile." << scan_end;
                return std::vector <T> ();
            }
        }

        /*****************************/
        /****** func_ptr_type ********/
        /*****************************/

        template <typename T> struct func_ptr_type;

        template <typename... args>
        struct func_ptr_type <void (args...)>
        {
            typedef void (*type) (args...);
        };

        /*************************************/
        /****** input_variadic_vector ********/
        /*************************************/

        /// Inputs a varibadic pack into a vector
        /// @{
        inline void input_variadic_vector(std::vector<void *> &){}

        template <typename T, typename... args>
        inline void input_variadic_vector(std::vector<void *> &input, const T& value, const args&... params)
        {
            input.push_back((void *)&value);
            input_variadic_vector(input, params...);
        }
        /// @}

        /*****************************/
        /****** String to Int ********/
        /*****************************/

        /// Converts a string to an int
        inline int StringToInt(const std::string &str)
        {
            int ret;
            std::stringstream ss(str);
            if (ss >> ret)
                    return ret;
            else
                    return 0;
        }

        /// Converts a int into a string
        inline std::string IntToString(const int &in)
        {
            std::stringstream ss;
            ss << in;
            return ss.str();
        }

        /********************************/
        /********* pi function **********/
        /********************************/

        /// Output pi.
        inline double pi() {return 3.14159265358979323846;}

        /***********************************/
        /********* convert_to_map **********/
        /***********************************/

        /// Turns a vector with enters [model::parameter, ...] into a map with [{model, parameter}, ...].
        inline std::map<std::string, std::vector<std::string>> convert_to_map(const std::vector<std::string> &vec)
        {
            std::map<std::string, std::vector<std::string>> ret;

            for (auto it = vec.begin(), end = vec.end(); it != end; it++)
            {
                std::string::size_type pos = it->find("::");
                ret[it->substr(0, pos)].push_back(*it);
            }

            return ret;
        }

        /*******************************************/
        /********* scanner_plugin_def_ret **********/
        /*******************************************/

        /// Turns a type into an object.  If it's a floating point number, it replaces it with a big negative number.
        /// @{
        template <typename ret>
        typename std::enable_if<!std::is_floating_point<ret>::value, ret>::type scanner_plugin_def_ret()
        {
            return ret();
        }

        template <typename ret>
        typename std::enable_if<std::is_floating_point<ret>::value, ret>::type scanner_plugin_def_ret()
        {
            return -std::pow(10.0, std::numeric_limits<double>::max_exponent10);
        };
        /// @}

        /********************************/
        /******** pow function **********/
        /********************************/

        /// Outputs a^i
        /// @{
        template <int i>
        inline double pow(const double &a)
        {
            return a*pow<i-1>(a);
        };

        template <>
        inline double pow<0>(const double &)
        {
            return 1.0;
        };

        template <>
        inline double pow<1>(const double &a)
        {
            return a;
        };

        template <int i>
        inline int pow(const int &a)
        {
            return a*pow<i-1>(a);
        };

        template <>
        inline int pow<0>(const int &)
        {
            return 1;
        };

        template <>
        inline int pow<1>(const int &a)
        {
            return a;
        };
        /// @}

        /********************************/
        /****** Remove All Func *********/
        /********************************/

        template <typename T>
        struct remove_all_func;

        template <typename ret, typename... args>
        struct remove_all_func <ret (args...)>
        {
            typedef ret type(typename remove_all<args>::type...);
        };

        /***************************/
        /****** return type ********/
        /***************************/

        template <typename...>
        struct return_type;

        template <typename ret, typename... args>
        struct return_type <ret (args...)>
        {
            typedef ret type;
        };

        /******************************/
        /****** first_arg_type ********/
        /******************************/

        template <typename...>
        struct first_arg_type;

        template <typename ret, typename T, typename... args>
        struct first_arg_type <ret (T, args...)>
        {
            typedef T type;
        };

        template <typename ret>
        struct first_arg_type <ret ()>
        {
            typedef void type;
        };

        /***********************************/
        /****** is_args_convertible ********/
        /***********************************/

        template <typename... T>
        struct is_args_convertible
        {
            static const bool value = false;
        };

        template <bool, typename T1, typename T2>
        struct __is_args_convertible__
        {
            static const bool value = is_args_convertible<T1, T2>::value;
        };

        template <typename T1, typename T2>
        struct __is_args_convertible__<false, T1, T2>
        {
            static const bool value = false;
        };

        template <typename ret1, typename ret2, typename arg1, typename arg2, typename... args1, typename... args2>
        struct is_args_convertible <ret1 (arg1, args1...), ret2 (arg2, args2...)>
        {
            static const bool value = __is_args_convertible__<std::is_convertible<arg1, arg2>::value, ret1 (args1...), ret2 (args2...)>::value;
        };

        template <typename ret1, typename ret2>
        struct is_args_convertible <ret1(), ret2()>
        {
            static const bool value = true;
        };

        /********************************************/
        /****** find_variadic_type_not_exact ********/
        /********************************************/

        template <typename... T>
        struct __find_variadic_type_not_exact__;

        template <typename... T>
        struct _find_variadic_type_not_exact_;

        template <typename T1, typename T2, typename... T>
        struct _find_variadic_type_not_exact_<T1, T2, T...>
        {
            typedef typename __find_variadic_type_not_exact__ <typename remove_all_func<T1>::type, typename remove_all_func<T2>::type, T2, T...>::ret_type ret_type;
            typedef typename __find_variadic_type_not_exact__ <typename remove_all_func<T1>::type, typename remove_all_func<T2>::type, T2, T...>::func_type func_type;
            static const bool value = __find_variadic_type_not_exact__ <typename remove_all_func<T1>::type, typename remove_all_func<T2>::type, T2, T...>::value;
        };

        template <typename... T>
        struct find_variadic_type_not_exact
        {
            typedef typename _find_variadic_type_not_exact_ <T...>::ret_type ret_type;
            typedef typename _find_variadic_type_not_exact_ <T...>::func_type func_type;
            static const bool value = _find_variadic_type_not_exact_ <T...>::value;
        };

        template <typename... args>
        struct find_variadic_type_not_exact <void (args...)>
        {
            typedef int ret_type;
            typedef void func_type;
            static const bool value = false;
        };

        template <typename ret, typename... args, typename T1, typename... T>
        struct __find_variadic_type_not_exact__ <void (args...), ret (args...), T1, T...>
        {
            typedef ret ret_type;
            typedef T1 func_type;
            static const bool value = true;
        };

        template <typename ret, typename... args, typename... args2, typename T1, typename... T>
        struct __find_variadic_type_not_exact__ <void (args...), ret (args2...), T1, T...>
        {
            typedef typename find_variadic_type_not_exact <void (args...), T...>::ret_type ret_type;
            typedef typename find_variadic_type_not_exact <void (args...), T...>::func_type func_type;
            static const bool value = find_variadic_type_not_exact <void (args...), T...>::value;
        };


        /****************************************/
        /****** find_variadic_type_exact ********/
        /****************************************/

        template <typename... T>
        struct find_variadic_type_exact;

        template <typename ret, typename... args, typename... args2, typename... T>
        struct find_variadic_type_exact<void (args...), ret (args2...), T...>
        {
            typedef typename find_variadic_type_exact<void (args...), T...>::ret_type ret_type;
            typedef typename find_variadic_type_exact<void (args...), T...>::func_type func_type;
            static const bool value = find_variadic_type_exact<void (args...), T...>::value;
        };

        template <typename ret, typename... args, typename... T>
        struct find_variadic_type_exact<void (args...), ret (args...), T...>
        {
            typedef ret ret_type;
            typedef ret func_type(args...);
            static const bool value = true;
        };

        template <typename... args>
        struct find_variadic_type_exact<void (args...)>
        {
            typedef int ret_type;
            typedef void func_type;
            static const bool value = false;
        };

        /******************************************/
        /****** find_variadic_type_convert ********/
        /******************************************/

        template<bool, typename... T>
        struct __find_variadic_type_convert__;

        template<typename... T>
        struct _find_variadic_type_convert_;

        template<typename Tc, typename T1, typename... T>
        struct _find_variadic_type_convert_<Tc, T1, T...>
        {
            typedef typename __find_variadic_type_convert__<is_args_convertible<Tc, T1>::value, T1, T...>::ret_type ret_type;
            typedef typename __find_variadic_type_convert__<is_args_convertible<Tc, T1>::value, T1, T...>::func_type func_type;
            static const bool value = __find_variadic_type_convert__<is_args_convertible<Tc, T1>::value, T1, T...>::value;
        };

        template <typename... T>
        struct find_variadic_type_convert
        {
            typedef typename _find_variadic_type_convert_<T...>::ret_type ret_type;
            typedef typename _find_variadic_type_convert_<T...>::func_type func_type;
            static const bool value = _find_variadic_type_convert_<T...>::value;
        };

        template <typename ret, typename... args>
        struct find_variadic_type_convert<ret (args...)>
        {
            typedef int ret_type;
            typedef void func_type;
            static const bool value = false;
        };

        template <bool b, typename Tc, typename T1, typename... T>
        struct __find_variadic_type_convert__<b, Tc, T1, T...>
        {
            typedef typename find_variadic_type_convert<Tc, T...>::ret_type ret_type;
            typedef typename find_variadic_type_convert<Tc, T...>::func_type func_type;
            static const bool value = find_variadic_type_convert<Tc, T...>::value;
        };

        template <typename Tc, typename T1, typename... T>
        struct __find_variadic_type_convert__<true, Tc, T1, T...>
        {
            typedef typename return_type<T1>::type ret_type;
            typedef T1 func_type;
            static const bool value = true;
        };

        /**********************************/
        /****** find_variadic_type ********/
        /**********************************/

        template <bool, bool, bool, typename...>
        struct __find_variadic_type__
        {
            typedef int ret_type;
            typedef void func_type;
            static const bool value = false;
        };

        template <typename... T>
        struct find_variadic_type
        {
            typedef typename __find_variadic_type__<find_variadic_type_exact<T...>::value,find_variadic_type_not_exact<T...>::value,find_variadic_type_convert<T...>::value, T...>::ret_type ret_type;
            typedef typename __find_variadic_type__<find_variadic_type_exact<T...>::value,find_variadic_type_not_exact<T...>::value,find_variadic_type_convert<T...>::value, T...>::func_type func_type;
            static const bool value = __find_variadic_type__<find_variadic_type_exact<T...>::value,find_variadic_type_not_exact<T...>::value,find_variadic_type_convert<T...>::value, T...>::value;
        };

        template <bool b1, bool b2, typename... T>
        struct __find_variadic_type__<true, b1, b2, T...>
        {
            typedef typename find_variadic_type_exact<T...>::ret_type ret_type;
            typedef typename find_variadic_type_exact<T...>::func_type func_type;
            static const bool value = true;
        };

        template <bool b2, typename... T>
        struct __find_variadic_type__<false, true, b2, T...>
        {
            typedef typename find_variadic_type_not_exact<T...>::ret_type ret_type;
            typedef typename find_variadic_type_not_exact<T...>::func_type func_type;
            static const bool value = true;
        };

        template <typename... T>
        struct __find_variadic_type__<false, false, true, T...>
        {
            typedef typename find_variadic_type_convert<T...>::ret_type ret_type;
            typedef typename find_variadic_type_convert<T...>::func_type func_type;
            static const bool value = true;
        };

        /********************************/
        /****** Stream Operators ********/
        /********************************/

        /// Outputs containers to an output stream
        /// @{
        template <typename T>
        inline typename std::enable_if <is_container<T>::value, std::ostream &>::type
        operator << (std::ostream &out, const T &in)
        {
            if (in.size() == 0)
                return out << "[]";


            auto it = in.begin();
            auto end = in.end();
            out << "[" << *it;
            for (++it; it != end; ++it)
            {
                out << ", " << *it;
            }

            return out << "]";
        }

        template <typename T>
        inline typename std::enable_if <is_pair<T>::value, std::ostream &>::type
        operator << (std::ostream &out, const T &in)
        {
            return out << "{" << in.first << " : " << in.second << "}";
        }
        /// @}

        /********************************/
        /****** Output Functions ********/
        /********************************/

        /// Functions to output data for the plugin resume functions
        /// @{
        template<typename T>
        inline typename std::enable_if<!is_container<T>::value && !is_pair<T>::value, void>::type
        resume_file_output(std::ofstream &out, T &param)
        {
            out.write(reinterpret_cast<char *>(&param), sizeof(T));
            //out << param << std::endl;
        };

        template <typename T>
        inline typename std::enable_if <is_container<T>::value, void>::type
        resume_file_output (std::ofstream &out, T &param)
        {
            for (auto it = param.begin(); it != param.end(); it++)
            {
                resume_file_output(out, *it);
            }
        }

        template <typename T>
        inline typename std::enable_if <is_pair<T>::value, void>::type
        resume_file_output (std::ofstream &out, T &param)
        {
            resume_file_output(out, param.first);
            resume_file_output(out, param.second);
        }

        template<typename T>
        typename std::enable_if<!is_container<T>::value && !is_pair<T>::value, void>::type
        resume_file_input(std::ifstream &in, T &param)
        {
            in.read((char *)&param, sizeof(T));
            //in >> param;
        };

        template <typename T>
        inline typename std::enable_if <is_container<T>::value, void>::type
        resume_file_input (std::ifstream &in, T &param)
        {
            for (auto it = param.begin(); it != param.end(); it++)
            {
                resume_file_input(in, *it);
            }
        }

        template <typename T>
        inline typename std::enable_if <is_pair<T>::value, void>::type
        resume_file_input (std::ifstream &in, T &param)
        {
            resume_file_input(in, param.first);
            resume_file_input(in, param.second);
        }

        template<typename T>
        inline typename std::enable_if<!is_container<T>::value && !is_pair<T>::value, size_t>::type
        resume_size_of(T &)
        {
            return sizeof(T);
        };

        template <typename T>
        inline typename std::enable_if <is_container<T>::value, size_t>::type
        resume_size_of (T &param)
        {
            return param.size()*sizeof(typename is_container<T>::type);
        }

        template <typename T>
        inline typename std::enable_if <is_pair<T>::value, size_t>::type
        resume_size_of (T &)
        {
            return sizeof(typename is_pair<T>::first_type) + sizeof(typename is_pair<T>::second_type);
        }

        inline void resume_file_input(std::ifstream &in, std::string &param)
        {
            in.read((char *)param.c_str(), param.length());
        }

        inline void resume_file_output(std::ofstream &out, std::string &param)
        {
            out.write((char *)param.c_str(), param.length());
        }

        inline size_t resume_size_of(std::string &param)
        {
            return param.length();
        }
        /// @}
    }
}

#endif
