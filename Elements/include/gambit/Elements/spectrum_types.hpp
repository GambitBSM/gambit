//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Spectrum specific types.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Peter Athron
///          (peter.athron@monash.edu)
///  \date 2019 Oct
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Oct
///
///  *********************************************

#ifndef __spectrum_types_hpp__
#define __spectrum_types_hpp__

#include "gambit/Utils/util_types.hpp"
#include "gambit/Elements/sminputs.hpp"
#include "gambit/Elements/spectrum_contents.hpp"

namespace Gambit
{

  struct SpectrumInputs
  {
    SMInputs sminputs;
    SpectrumContents::Contents contents;
    std::map<str, safe_ptr<const double> > param;
    safe_ptr<Options> options;

    SpectrumInputs(SMInputs smi, 
                   SpectrumContents::Contents cont,
                   std::map<str, safe_ptr<const double> > par, 
                   safe_ptr<Options> opt):
      sminputs(smi),
      contents(cont), 
      param(par), 
      options(opt)
    {}
  };

}
#endif //defined __spectrum_types_hpp__
