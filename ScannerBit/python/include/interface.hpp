#ifndef __SCANNERBIT_PYTHON_DIAGOSTICS_HPP__
#define __SCANNERBIT_PYTHON_DIAGOSTICS_HPP__

#include <string>
#include <unordered_set>
#include <vector>
#include <yaml-cpp/yaml.h>

#include "gambit/Printers/printermanager.hpp"
#include "gambit/Utils/yaml_parser_base.hpp"
#include "gambit/ScannerBit/base_prior.hpp"

namespace Gambit
{
    
    namespace Scanner
    {
        
        class Factory_Base;
        
        namespace Python
        {

            class diagnostics
            {
            private:
                std::unordered_set<std::string> valid_commands;
                
            public:
                diagnostics();
                void operator()(const std::vector<std::string> &args);
                void operator()(const std::string &command);
                ~diagnostics(){}
            };
            
            class scan_interface;
            
            class printer_wrapper
            {
            private:
                scan_interface *scanner;
                
            public:
                printer_wrapper(scan_interface *scanner) : scanner(scanner) {}
                void main_printer(std::unordered_map<std::string, double> &);
                void main_printer(const std::string &, const double &);
                void aux_printer(const std::string &, const double &);
                ~printer_wrapper(){}
            };
            
            class scan_interface
            {
            private:
                Printers::PrinterManager *global_printer;
                #ifdef WITH_MPI
                const bool init_mpi;
                #endif  
            public:
                scan_interface(bool);
                Printers::PrinterManager &get_printer_manager() const
                {
                    return *global_printer;
                }
                std::shared_ptr<printer_wrapper> get_printer();
                int run_scan(Gambit::IniParser::Parser &, const Gambit::Scanner::Factory_Base *, Gambit::Priors::BasePrior *, bool );
                int run_scan_node(YAML::Node *, const Gambit::Scanner::Factory_Base *, Gambit::Priors::BasePrior *, bool);
                int run_scan_str(std::string *, const Gambit::Scanner::Factory_Base *, Gambit::Priors::BasePrior *, bool);
                ~scan_interface(){}
            };
            
        }
        
    }
    
}

#endif
