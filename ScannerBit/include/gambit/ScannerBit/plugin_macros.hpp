//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  declaration for gambit module
///
///  *********************************************
///
///  Authors (add name and date if you modify):
//
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2013 August
///  \date 2014 Feb
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2014 Dec
///
///  *********************************************

#include "gambit/ScannerBit/plugin_details.hpp"
#include "gambit/ScannerBit/printer_interface.hpp"
#include "gambit/Utils/type_index.hpp"
#include "gambit/Utils/variadic_functions.hpp"

#ifndef SCANNER_PLUGIN_MACROS_HPP
#define SCANNER_PLUGIN_MACROS_HPP

// Tell clang not to warn about usage of extern "C" even when the types involved are C++ (we just use it to avoid name-mangling)
#ifdef __clang__
  #pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
#endif

/// \name gambit plugin macros
/// The main macros to be used by the user.
/// @{
/// Makes an abstract type of type "name" available to the plugin interface.
#define export_abstract(name, ...)      EXPORT_ABSTRACT(name, __VA_ARGS__)
/// Makes the object "name" available to the plugin interface.
#define export_object(name, ...)        EXPORT_OBJECT(name, __VA_ARGS__)
/// Declaration of the main function which will be ran by the interface
#define plugin_main(...)                PLUGIN_MAIN( __VA_ARGS__ )
/// Generic plugin declaration of the from gambit_plugin(name, type, version)
#define gambit_plugin(...)              GAMBIT_PLUGIN( __VA_ARGS__ )
/// Runs when the plugin is loaded.
#define plugin_constructor              PLUGIN_CONSTRUCTOR
/// Runs when the plugin is destroyed.
#define plugin_deconstructor            PLUGIN_DECONSTRUCTOR
/// Sets the version number
#define __PLUGIN_version(...)           __PLUGIN_VERSION( __VA_ARGS__ )
/// Set version number to 0.0.0.
#define __PLUGIN_no_version             __PLUGIN_VERSION()
/// Tells ScannerBit that these tags are required
#define reqd_inifile_entries(...) void reqd_inifile_entries()
/// Tells ScannerBit that these libraries are requested
#define reqd_libraries(...) void reqd_libraries()
/// Tells ScannerBit that these include files must exist
#define reqd_headers(...) void reqd_headers()
/// Tells ScannerBit to set a flag
#define set_flag(...) void set_flag()
#define cxx_flags(...) void scc_flags()
/// @}

#define REQD_INIFILE_ENTRIES(...)
#define REQD_LIRBARIES(...)
#define REQD_HEADERS(...)
#define SET_FLAG(...)
#define CXX_FLAGS(...)

#define _ARG_N_(_1_, _2_, _3_, _4_, ret, ...) ret
#define __ARG_N__(...) _ARG_N_(__VA_ARGS__ , 4, 3, 2, 1, 0)
#define __COMBINE__(a, b) _COMBINE_(a, b)
#define _COMBINE_(a, b) a ## b
#define _STR_(a) #a
#define __STR__(a) _STR_(a)

#define __PLUGIN_VERSION___4(major, minor, patch, release) major ## _ ## minor ## _ ## patch ## _ ## release
#define __PLUGIN_VERSION___3(major, minor, patch) __PLUGIN_VERSION___4(major, minor, patch, )
#define __PLUGIN_VERSION___2(major, minor) __PLUGIN_VERSION___4(major, minor,,)
#define __PLUGIN_VERSION___1(major) __PLUGIN_VERSION___4(major,,,)
#define __PLUGIN_VERSION___0() __PLUGIN_VERSION___(,,,)
#define __PLUGIN_VERSION(...) __COMBINE__(__PLUGIN_VERSION___,__ARG_N__(__VA_ARGS__))( __VA_ARGS__ )

/*Allows Gambit to declare an object of type "..."*/
#define EXPORT_ABSTRACT(name, ...)                                                                      \
namespace __gambit_plugin_namespace__                                                                   \
{                                                                                                       \
    namespace LoadTags                                                                                  \
    {                                                                                                   \
        struct name{};                                                                                  \
    }                                                                                                   \
                                                                                                        \
    namespace                                                                                           \
    {                                                                                                   \
        template<>                                                                                      \
        class interface <LoadTags::name>                                                                \
        {                                                                                               \
        public:                                                                                         \
                                                                                                        \
            interface(pluginData &myData)                                                               \
            {                                                                                           \
                myData.inits.push_back(interface <LoadTags::name>::init);                               \
            }                                                                                           \
                                                                                                        \
            static void init(pluginData &myData)                                                        \
            {                                                                                           \
                myData.outputFuncs[#name] = new Gambit::Scanner::Plugins::classFactory<__VA_ARGS__>;    \
            }                                                                                           \
                                                                                                        \
            ~interface()                                                                                \
            {                                                                                           \
                if (myData.outputFuncs.find(#name) != myData.outputFuncs.end())                         \
                    delete myData.outputFuncs[#name];                                                   \
            }                                                                                           \
                                                                                                        \
        };                                                                                              \
                                                                                                        \
        template <>                                                                                     \
        interface <LoadTags::name> reg_init <LoadTags::name>::reg(myData);                              \
    }                                                                                                   \
}                                                                                                       \

/*Allows Gambit to use object "obj" of type "..."*/
#define EXPORT_OBJECT(name, ...)                                                                        \
namespace __gambit_plugin_namespace__                                                                   \
{                                                                                                       \
    namespace LoadTags                                                                                  \
    {                                                                                                   \
        struct name{};                                                                                  \
    }                                                                                                   \
                                                                                                        \
    namespace                                                                                           \
    {                                                                                                   \
        template<>                                                                                      \
        class interface <LoadTags::name>                                                                \
        {                                                                                               \
        public:                                                                                         \
                                                                                                        \
            interface(pluginData &myData)                                                               \
            {                                                                                           \
                myData.inits.push_back(interface <LoadTags::name>::init);                               \
            }                                                                                           \
                                                                                                        \
            static void init(pluginData &myData)                                                        \
            {                                                                                           \
                myData.outputFuncs[#name]                                                               \
                    = new Gambit::Scanner::Plugins::funcFactory <decltype(__VA_ARGS__)>(&__VA_ARGS__);  \
            }                                                                                           \
                                                                                                        \
            ~interface()                                                                                \
            {                                                                                           \
                if (myData.outputFuncs.find(#name) != myData.outputFuncs.end())                         \
                    delete myData.outputFuncs[#name];                                                   \
            }                                                                                           \
                                                                                                        \
        };                                                                                              \
                                                                                                        \
        template <>                                                                                     \
        interface <LoadTags::name> reg_init <LoadTags::name>::reg(myData);                              \
    }                                                                                                   \
}                                                                                                       \

//constructor
#define PLUGIN_CONSTRUCTOR                                                                              \
void PLUGIN_CONSTRUCTOR();                                                                              \
namespace __gambit_plugin_namespace__                                                                   \
{                                                                                                       \
    namespace                                                                                           \
    {                                                                                                   \
        template<>                                                                                      \
        class interface <void (int)>                                                                    \
        {                                                                                               \
        public:                                                                                         \
                                                                                                        \
            interface(pluginData &myData)                                                               \
            {                                                                                           \
                myData.inits.push_back(interface <void (int)>::init);                                   \
            }                                                                                           \
                                                                                                        \
            static void init(pluginData&)                                                               \
            {                                                                                           \
                PLUGIN_CONSTRUCTOR();                                                                   \
            }                                                                                           \
        };                                                                                              \
                                                                                                        \
        template <>                                                                                     \
        interface <void (int)> reg_init <void (int)>::reg(myData);                                      \
    }                                                                                                   \
}                                                                                                       \
void PLUGIN_CONSTRUCTOR()                                                                               \

#define PLUGIN_DECONSTRUCTOR                                                                            \
void PLUGIN_DECONSTRUCTOR();                                                                            \
namespace __gambit_plugin_namespace__                                                                   \
{                                                                                                       \
    namespace                                                                                           \
    {                                                                                                   \
        template<>                                                                                      \
        class interface <void (void)>                                                                   \
        {                                                                                               \
        public:                                                                                         \
                                                                                                        \
            interface(pluginData &myData)                                                               \
            {                                                                                           \
                myData.inits.push_back(interface <void (void)>::init);                                  \
            }                                                                                           \
                                                                                                        \
            static void init(pluginData &myData)                                                        \
            {                                                                                           \
                myData.deconstructor = PLUGIN_DECONSTRUCTOR;                                            \
            }                                                                                           \
        };                                                                                              \
                                                                                                        \
        template <>                                                                                     \
        interface <void (void)> reg_init <void (void)>::reg(myData);                                    \
    }                                                                                                   \
}                                                                                                       \
void PLUGIN_DECONSTRUCTOR()                                                                             \

#define __PLUGIN_MAIN_RET_VAL__(...)                                                                    \
decltype(__plugin_main_ret_val__(typename Gambit::Scanner::func_ptr_type<void (__VA_ARGS__)>::type()))  \

/*Declared the "main" for the module.  This is function that will be ran by the module interface*/
#define PLUGIN_MAIN(...)                                                                                \
 __plugin_main_ret_val__(void (*)(__VA_ARGS__));                                                        \
__PLUGIN_MAIN_RET_VAL__(__VA_ARGS__) PLUGIN_MAIN (__VA_ARGS__);                                         \
namespace __gambit_plugin_namespace__                                                                   \
{                                                                                                       \
    namespace                                                                                           \
    {                                                                                                   \
        template<>                                                                                      \
        class interface <int (__VA_ARGS__)>                                                             \
        {                                                                                               \
        public:                                                                                         \
                                                                                                        \
            interface(pluginData &myData)                                                               \
            {                                                                                           \
                myData.inits.push_back(interface <int (__VA_ARGS__)>::init);                            \
            }                                                                                           \
                                                                                                        \
            static void init(pluginData &myData)                                                        \
            {                                                                                           \
                myData.plugin_mains[typeid(__PLUGIN_MAIN_RET_VAL__(__VA_ARGS__) (__VA_ARGS__))] =       \
                    Gambit::Scanner::Plugins::funcFactory                                               \
                            <__PLUGIN_MAIN_RET_VAL__(__VA_ARGS__) (__VA_ARGS__)>(PLUGIN_MAIN)();        \
            }                                                                                           \
        };                                                                                              \
                                                                                                        \
        template <>                                                                                     \
        interface <int (__VA_ARGS__)> reg_init <int (__VA_ARGS__)>::reg(myData);                        \
    }                                                                                                   \
}                                                                                                       \
__PLUGIN_MAIN_RET_VAL__(__VA_ARGS__) PLUGIN_MAIN (__VA_ARGS__)                                          \

/*Defines a Gambit plugin*/
#define __GAMBIT_PLUGIN__(plug_name, plug_type, plug_version)                                               \
namespace __gambit_plugin_ ## plug_name ## __t__ ## plug_type ## __v__ ## plug_version ##  _namespace__     \
{                                                                                                           \
    namespace __gambit_plugin_namespace__                                                                   \
    {                                                                                                       \
        using Gambit::Scanner::Plugins::pluginData;                                                         \
                                                                                                            \
        namespace LoadTags                                                                                  \
        {                                                                                                   \
            struct plug_name{};                                                                             \
        }                                                                                                   \
                                                                                                            \
        namespace                                                                                           \
        {                                                                                                   \
            pluginData myData( #plug_name , #plug_type, #plug_version );                                    \
                                                                                                            \
            template <class T>                                                                              \
            class interface {};                                                                             \
                                                                                                            \
            template <class T>                                                                              \
            struct reg_init                                                                                 \
            {                                                                                               \
                    static interface <T> reg;                                                               \
            };                                                                                              \
        }                                                                                                   \
                                                                                                            \
        extern "C" const std::map<Gambit::type_index, void *> &                                             \
            __gambit_plugin_pluginInit_ ## plug_name ## __t__ ## plug_type ## __v__ ## plug_version ## __   \
            (const std::string *tag, const YAML::Node *node, Gambit::Scanner::printer_interface &printer,   \
                                    Gambit::Scanner::prior_interface &prior, std::vector<void *> *input )   \
        {                                                                                                   \
            if (!myData.loaded)                                                                             \
            {                                                                                               \
                myData.tag = *tag;                                                                          \
                myData.printer = &printer;                                                                  \
                myData.prior = &prior;                                                                      \
                myData.loaded = true;                                                                       \
                                                                                                            \
                if (input != 0)                                                                             \
                    myData.inputData = *input;                                                              \
                                                                                                            \
                myData.node = *node;                                                                        \
                                                                                                            \
                for(auto it = myData.inits.begin(), end = myData.inits.end(); it != end; it++)              \
                {                                                                                           \
                    (*it)(myData);                                                                          \
                }                                                                                           \
                                                                                                            \
                myData.inits.clear();                                                                       \
            }                                                                                               \
            else                                                                                            \
            {                                                                                               \
                scan_err << "plugin:\n" << __gambit_plugin_namespace__::myData.print()                      \
                        << "is already loaded" << scan_end;                                                 \
            }                                                                                               \
                                                                                                            \
            return myData.plugin_mains;                                                                     \
        }                                                                                                   \
                                                                                                            \
        extern "C" void *                                                                                   \
            __gambit_plugin_getMember_ ## plug_name ## __t__ ## plug_type ## __v__ ## plug_version ## __    \
                                                                                            (std::string in)\
        {                                                                                                   \
            if (myData.outputFuncs.find(in) != myData.outputFuncs.end())                                    \
            {                                                                                               \
                return (*myData.outputFuncs[in])();                                                         \
            }                                                                                               \
            else                                                                                            \
                return NULL;                                                                                \
        }                                                                                                   \
    }                                                                                                       \
                                                                                                            \
    inline Gambit::Scanner::printer_interface &get_printer()                                                \
    {                                                                                                       \
        return *__gambit_plugin_namespace__::myData.printer;                                                \
    }                                                                                                       \
                                                                                                            \
    inline Gambit::Scanner::prior_interface &get_prior()                                                    \
    {                                                                                                       \
        return *__gambit_plugin_namespace__::myData.prior;                                                  \
    }                                                                                                       \
                                                                                                            \
    template <typename T>                                                                                   \
    inline T get_inifile_value(std::string in)                                                              \
    {                                                                                                       \
        if (!__gambit_plugin_namespace__::myData.node[in])                                                  \
        {                                                                                                   \
            scan_err << "Missing iniFile entry \""<< in << "\" needed by a gambit plugin:  \n"              \
                    << __gambit_plugin_namespace__::myData.print() << scan_end;                             \
            return T();                                                                                     \
        }                                                                                                   \
                                                                                                            \
        return __gambit_plugin_namespace__::myData.node[in].as<T>();                                        \
    }                                                                                                       \
                                                                                                            \
    inline YAML::Node get_inifile_node(std::string in)                                                      \
    {                                                                                                       \
        return __gambit_plugin_namespace__::myData.node[in];                                                \
    }                                                                                                       \
                                                                                                            \
    inline YAML::Node get_inifile_node()                                                                    \
    {                                                                                                       \
        return __gambit_plugin_namespace__::myData.node;                                                    \
    }                                                                                                       \
                                                                                                            \
    template <typename T>                                                                                   \
    inline T get_inifile_value(std::string in, T defaults)                                                  \
    {                                                                                                       \
        if (!__gambit_plugin_namespace__::myData.node[in])                                                  \
        {                                                                                                   \
            return defaults;                                                                                \
        }                                                                                                   \
                                                                                                            \
        return __gambit_plugin_namespace__::myData.node[in].as<T>();                                        \
    }                                                                                                       \
                                                                                                            \
    template <>                                                                                             \
    inline YAML::Node get_inifile_value<YAML::Node>(std::string in)                                         \
    {                                                                                                       \
        if (!__gambit_plugin_namespace__::myData.node[in])                                                  \
        {                                                                                                   \
            scan_err << "Missing iniFile node \""<< in << "\" needed by a gambit plugin:  \n"               \
                    << __gambit_plugin_namespace__::myData.print() << scan_end;                             \
            YAML::Node node;                                                                                \
            return node;                                                                                    \
        }                                                                                                   \
        return __gambit_plugin_namespace__::myData.node[in];                                                \
    }                                                                                                       \
                                                                                                            \
    template <>                                                                                             \
    inline YAML::Node get_inifile_value<YAML::Node>(std::string in, YAML::Node defaults)                    \
    {                                                                                                       \
        if (!__gambit_plugin_namespace__::myData.node[in])                                                  \
        {                                                                                                   \
            return defaults;                                                                                \
        }                                                                                                   \
                                                                                                            \
        return __gambit_plugin_namespace__::myData.node[in];                                                \
    }                                                                                                       \
                                                                                                            \
    template <typename T>                                                                                   \
    inline T &get_input_value(int i)                                                                        \
    {                                                                                                       \
        return *static_cast<T*>(__gambit_plugin_namespace__::myData.inputData[i]);                          \
    }                                                                                                       \
                                                                                                            \
    Gambit::Scanner::resume_params_func                                                                     \
                    set_resume_params(__STR__(plug_name ## __t__ ## plug_type ## __v__ ## plug_version));   \
}                                                                                                           \
namespace __gambit_plugin_ ## plug_name ## __t__ ## plug_type ## __v__ ## plug_version ## _namespace__      \


#define _GAMBIT_PLUGIN_(plug_name, plug_type, plug_version)                                                 \
        __GAMBIT_PLUGIN__(plug_name, plug_type, plug_version)                                               \

#define GAMBIT_PLUGIN_1(plugin_name)                                                                        \
        _GAMBIT_PLUGIN_(plug_name,, __PLUGIN_no_version)                                                    \

#define GAMBIT_PLUGIN_2(plugin_name, plug_type)                                                             \
        _GAMBIT_PLUGIN_(plug_name, plug_type, __PLUGIN__no_version)                                         \

#define GAMBIT_PLUGIN_3(plug_name, plug_type, plug_version)                                                 \
        _GAMBIT_PLUGIN_(plug_name, plug_type, __PLUGIN_ ## plug_version)                                    \

#define GAMBIT_PLUGIN(...) __COMBINE__(GAMBIT_PLUGIN_, __ARG_N__(__VA_ARGS__))(__VA_ARGS__ )


#define ___GAMBIT_PLUGIN_NAMESPACE___(plug_name, plug_type, plug_version)                                   \
namespace __gambit_plugin_ ## plug_name ## __t__ ## plug_type ## __v__ ## plug_version ## _namespace__      \

#define _GAMBIT_PLUGIN_NAMESPACE_(plug_name, plug_type, plug_version)                                       \
        ___GAMBIT_PLUGIN_NAMESPACE___(plug_name, plug_type, plug_version)                                   \

#define __GAMBIT_PLUGIN_NAMESPACE___1(plug_name)                                                            \
        _GAMBIT_PLUGIN_NAMESPACE_(plug_name,, __PLUGIN_no_version)                                          \

#define __GAMBIT_PLUGIN_NAMESPACE___2(plug_name, plug_type)                                                 \
        _GAMBIT_PLUGIN_NAMESPACE_(plug_name, plug_type, __PLUGIN_no_version)                                \

#define __GAMBIT_PLUGIN_NAMESPACE___3(plug_name, plug_type, plug_version)                                   \
        _GAMBIT_PLUGIN_NAMESPACE_(plug_name, plug_type, __PLUGIN_ ## plug_version)                          \

#define __GAMBIT_PLUGIN_NAMESPACE__(...)                                                                    \
        __COMBINE__(__GAMBIT_PLUGIN_NAMESPACE___, __ARG_N__(__VA_ARGS__))(__VA_ARGS__)                      \


#define GAMBIT_PLUGIN_INITIALIZE(setup, ...)                                                                \
GAMBIT_PLUGIN(__VA_ARGS__)                                                                                  \
{                                                                                                           \
    setup                                                                                                   \
}                                                                                                           \
__GAMBIT_PLUGIN_NAMESPACE__(__VA_ARGS__)                                                                    \

#endif
