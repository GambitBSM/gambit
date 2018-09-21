//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of container classes
///  for the micrOMEGAs backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Jonathan Cornell
///          (jcornell@ucsc.edu)
///  \date 2014 Sep
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///  \date 2016 Aug
///
///  *********************************************

#ifndef __MicrOmegas_types_hpp__
#define __MicrOmegas_types_hpp__

namespace Gambit
{
    namespace MicrOmegas
    {
    typedef  struct { double par[36]; }  MOcommonSTR;
    typedef  struct { double weight; char *prtcl[5];} aChannel;
    }
}

#endif // defined __MicrOmegas_types_hpp__
