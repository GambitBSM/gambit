//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Likelihood container factory declarations.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///    (c.weniger@uva.nl)
///  \date 2013 May, June, July
//
///  \author Gregory Martinez
///    (gregory.david.martinez@gmail.com)
///  \date 2013 July 2013 Feb 2014
///
///  \author Pat Scott
///    (patscott@physics.mcgill.ca)
///  \date 2013 Aug
///  \date 2014 May
///
///  *********************************************

#ifndef __container_factory_hpp__
#define __container_factory_hpp__

#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <string>

#include "gambit/Core/depresolver.hpp"
#include "gambit/Elements/functors.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/Printers/basebaseprinter.hpp"
#include "gambit/ScannerBit/priors_rollcall.hpp"
#include "gambit/ScannerBit/scanner_utils.hpp"
#include "gambit/ScannerBit/scan.hpp"

#define LOAD_SCANNER_FUNCTION(tag, ...) REGISTER(__scanner_factories__, tag, __VA_ARGS__)

namespace Gambit
{

  gambit_registry
  {
    typedef void* factory_type(const std::map<str, primary_model_functor *> &,
     DRes::DependencyResolver &b, IniParser::IniFile &c, const str &purpose, Printers::BaseBasePrinter& p);
    reg_elem <factory_type> __scanner_factories__;
  }

  class Likelihood_Container_Factory : public Scanner::Factory_Base
  {
    private:
      DRes::DependencyResolver &dependencyResolver;
      IniParser::IniFile &iniFile;
      std::map<str, primary_model_functor *> functorMap;
      Printers::BaseBasePrinter &printer;

    public:
      Likelihood_Container_Factory(const gambit_core &core, DRes::DependencyResolver &dependencyResolver,
       IniParser::IniFile &iniFile, Printers::BaseBasePrinter& printer);
      ~Likelihood_Container_Factory(){}
      void * operator() (const str &purpose) const;
  };

}

#endif
