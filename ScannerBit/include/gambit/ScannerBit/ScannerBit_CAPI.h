//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Header for ScannerBit interface function 
///  library, for running ScannerBit via an 
//   external interface.
///  (For example, see pyScannerBit for a python
///   interface to these functions)
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2017 Nov
///
///  *********************************************

#include <unordered_map>
#include <string>
#include "yaml-cpp/yaml.h"

// Interface function declarations

/// Required signature of the user-supplied likelihood function
typedef double (*user_funcptr)(const std::unordered_map<std::string, double> &in);    

#ifdef __cplusplus
extern "C"
{
#endif

    void hello_world();
    void run_scan_from_file(const char[], const user_funcptr);
    void run_scan(YAML::Node, const user_funcptr);
#ifdef __cplusplus
}
#endif
