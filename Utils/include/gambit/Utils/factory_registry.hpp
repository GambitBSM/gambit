//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
/// \file
///
///  Utility functions used by ScannerBit and the
///  GAMBIT printers to register available scanners
///  and printers.
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
///  \date 2014 Mar
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2014 May
///
///  *********************************************

#ifndef __factory_registry_hpp__
#define __factory_registry_hpp__

#include <type_traits>
#include <utility>
#include <ostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

#define REGISTER(reg_map, tag, ...) REGISTER_ELEM(reg_map, #tag, __VA_ARGS__)

#define REGISTER_ELEM(reg_map, tag, ...)                                                        \
namespace __gambit_registry__                                                                   \
{                                                                                               \
    namespace                                                                                   \
    {                                                                                           \
        template<>                                                                              \
        class __create_class__ < __VA_ARGS__ >                                                  \
        {                                                                                       \
        public:                                                                                 \
            __create_class__(decltype(reg_map) &creators)                                       \
            {                                                                                   \
                creators[ tag ] = __create_class__< __VA_ARGS__ >::init;                        \
            }                                                                                   \
                                                                                                \
            template<typename T, typename... args>                                              \
            static T *init(args... params)                                                      \
            {                                                                                   \
                return static_cast<T *>(new __VA_ARGS__ (std::forward<args>(params)...));       \
            }                                                                                   \
        };                                                                                      \
                                                                                                \
        template <>                                                                             \
        __create_class__ < __VA_ARGS__ > __reg_init__ < __VA_ARGS__ >::reg(reg_map);            \
    }                                                                                           \
}                                                                                                               \

#define gambit_registry                             \
namespace __gambit_registry__                       \
{                                                   \
    namespace                                       \
    {                                               \
        template <class T>                          \
        class __create_class__ {};                  \
                                                    \
        template <class T>                          \
        struct __reg_init__                         \
        {                                           \
            static __create_class__ <T> reg;        \
        };                                          \
    }                                               \
}                                                   \
                                                    \
namespace                                           \


namespace Gambit
{

    template <typename T>
    class reg_elem : public std::unordered_map<std::string, T *>
    {
    private:
            
    public:
        std::string print()
        {
            std::ostringstream out;
            
            out << "The options are:  \n";
            for (auto it = this->begin(); it != this->end(); it++)
            {
                    out << "\t" << it->first << "\n";
            }
            
            return out.str();
        }
    };
}

#endif
