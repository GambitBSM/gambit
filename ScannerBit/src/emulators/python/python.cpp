//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Make an instance of python scanner and define 
///  method to run it
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2023 May
///
///  \author Andrew Fowlie
///          (andrew.j.fowlie@googlemail.com)
///  \date 2023 May
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)   
///  \date 2023 May
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)   
///  \date 2023 May
///
///  \author Pat Scott
///          (patrickcolinscott@gmail.com)   
///  \date 2023 May
///
///  *********************************************

#include "gambit/cmake/cmake_variables.hpp"

#ifdef HAVE_PYBIND11

#ifdef WITH_MPI
    #include "gambit/Utils/begin_ignore_warnings_mpi.hpp"
    #include "mpi.h"
    #include "gambit/Utils/end_ignore_warnings.hpp"
#endif

#include "gambit/Utils/begin_ignore_warnings_pybind11.hpp"
#include <pybind11/embed.h>
#include "gambit/Utils/end_ignore_warnings.hpp"

#include <tuple>
#include "gambit/Utils/python_interpreter.hpp"
#include "gambit/ScannerBit/emulator_plugin.hpp"
#include "gambit/ScannerBit/python_utils.hpp"
#include "gambit/ScannerBit/emulator_utils.hpp"

namespace py = pybind11;

namespace Gambit
{
        
    namespace Scanner 
    {
    
        namespace Plugins 
        {
            
            namespace EmulatorPyPlugin 
            {
                
                pluginData *&pythonPluginData();
                
            }  // end namespace ScannerPyPlugin
            
        }  // end namespace Plugins
        
    }  // end namespace Scanner
    
}  // end namespace Gambit

emulator_plugin(python, version(1, 0, 0))
{
    
    reqd_headers("Python3");
    reqd_headers("pybind11");

    Gambit::Utils::python_interpreter_guard g;
    
    /*!
     * Instance of python scanner
     */
    py::object instance;
    py::object train_func;
    py::object predict_func;
    py::object master_func;

    plugin_constructor
    {
        // export plugin data to python plugin
        Gambit::Scanner::Plugins::EmulatorPyPlugin::pythonPluginData() = &__gambit_plugin_namespace__::myData;

        // get plugin name
        std::string plugin_name = get_inifile_value<std::string>("plugin");

        // get yaml as dict
        py::kwargs options = yaml_to_dict(get_inifile_node());
        
        // make instance of plugin
        py::module file;
        std::string pkg = get_inifile_value<std::string>("pkg", "");
        
        try 
        {
            if (pkg == "")
            {
                Gambit::Scanner::Plugins::plugin_info.load_python_plugins();
                decltype(auto) details =  Gambit::Scanner::Plugins::plugin_info.load_python_plugin("emulator", plugin_name);
                py::list(py::module::import("sys").attr("path")).append(py::cast(details.loc));
                file = py::module::import(details.package.c_str());
            }
            else
            {
                std::string::size_type pos = pkg.rfind("/");
                std::string pkg_name;
                if (pos != std::string::npos)
                {
                    pkg_name = pkg.substr(pos+1);
                    while(pos != 0 && pkg[pos-1] == '/') --pos;
                    std::string path = pkg.substr(0, pos);
                    py::list(py::module::import("sys").attr("path")).append(py::cast(path));
                }
                else
                    pkg_name = pkg;
                
                py::list(py::module::import("sys").attr("path")).append(py::cast(GAMBIT_DIR "/ScannerBit/src/emulators/python/plugins"));
                file = py::module::import(pkg_name.c_str());
            }
            
            instance = py::dict(file.attr("__plugins__"))[plugin_name.c_str()](**options);
            train_func = instance.attr("train");
            predict_func = instance.attr("predict");
            master_func = instance.attr("master");
        }
        catch (std::exception &ex)
        {
            scan_err << "Error loading plugin \"" << plugin_name << "\": " << ex.what() << scan_end;
        }
    }

    //training
    void plugin_main(map_vector<double> x, map_vector<double> y, map_vector<double> sigs, unsigned short int &flag, int source)
    {
        Gambit::Scanner::Emulator::flag_wrapper in_flag(flag, source);
        train_func(x, y, sigs, in_flag);

        return;
    }

    // training on a batch of points (routing: master). x, y and sigs hold n_rows rows each, row-major.
    // Calls the same train() as a single point, with flag.n_rows and flag.batch set.
    void plugin_main(map_vector<double> x, map_vector<double> y, map_vector<double> sigs, unsigned short int &flag, int source, int n_rows)
    {
        Gambit::Scanner::Emulator::flag_wrapper in_flag(flag, source, n_rows, true);
        train_func(x, y, sigs, in_flag);

        return;
    }

    // master (routing: master): called on the master egg rank for every message from gambit, and on a
    // timer with an empty message (neither train nor predict set) so the plugin can flush its cache.
    // The plugin returns (destination, n_rows, X, Y, Z):
    //   destination < 0 : nothing to forward
    //   n_rows == 0     : forward this predict request to egg rank 'destination' (the rank numbers are
    //                     those of the plugin's MPI communicator); X, Y, Z are ignored
    //   n_rows > 0      : send a batch of n_rows training points (X, Y, Z, row-major) to 'destination'
    std::tuple<int, int, vector<double>, vector<double>, vector<double>> plugin_main(unsigned short int &flag, int source, map_vector<double> x, map_vector<double> y, map_vector<double> sigs)
    {
        Gambit::Scanner::Emulator::flag_wrapper in_flag(flag, source);
        py::tuple ret = master_func(x, y, sigs, in_flag);

        return std::make_tuple(ret[0].cast<int>(), ret[1].cast<int>(),
                               ret[2].cast<vector<double>>(), ret[3].cast<vector<double>>(), ret[4].cast<vector<double>>());
    }

    //predict
    std::pair<vector<double>, vector<double>> plugin_main(map_vector<double> x, unsigned short int &flag, int source)
    {
        Gambit::Scanner::Emulator::flag_wrapper in_flag(flag, source);
        py::tuple ret = predict_func(x, in_flag);

        // The plugin must explicitly set flag.result = True to vouch for the values
        // it returned. If it didn't (e.g. it declined to predict), don't trust or
        // even try to cast whatever it handed back -- default to not_valid instead.
        if (!in_flag.result())
        {
            in_flag.set_not_valid(true);
            return std::make_pair(vector<double>::Zero(1), vector<double>::Zero(1));
        }

        return std::make_pair(ret[0].cast<vector<double>>(), ret[1].cast<vector<double>>());
    }

    plugin_deconstructor 
    {
    }
    
}

#endif
