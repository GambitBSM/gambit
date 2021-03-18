//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for the DirectDM backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2018 Sep, Oct
///        2019 Dec
///        2020 Mar
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2019 Jul
///
///  \author Felix Kahlhofer
///          (kahlhoefer@physik.rwth-aachen.de)
///  \date 2020 May
///
///  \author Markus Prim
///          (markus.prim@cern.ch)
///  \date 2020 Dec
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/DirectDM_2_2_0.hpp"
#include "gambit/Backends/backend_types/DDCalc.hpp" // Using DDCalc (frontend) container objects

#include <boost/algorithm/string/predicate.hpp>

#include <pybind11/stl.h>

BE_INI_FUNCTION
{
  // Empty ini function.
}
END_BE_INI_FUNCTION

BE_NAMESPACE
{
  /* Simple local helper function to copy map of coefficients into GAMBIT (DDCalc) container */
  NREO_DM_nucleon_couplings copy_couplings_to_NREO_container(const map_str_dbl& nonrel_WCs)
  {
    // Copy coefficients into GAMBIT container object
    // Note that c0 = cp and c1 = cn
    NREO_DM_nucleon_couplings NRWCs;

    int OpCoeffList[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,100,104};
    int OpCoeff;

    for(int i=0; i<25; i++)
    {
      OpCoeff = OpCoeffList[i];
      std::stringstream sp;
      std::stringstream sn;
      sp<<"cNR"<<OpCoeff<<"p";
      sn<<"cNR"<<OpCoeff<<"n";
      auto icp = nonrel_WCs.find(sp.str());
      auto icn = nonrel_WCs.find(sn.str());
      if(icp!=nonrel_WCs.end())
        NRWCs.c0[OpCoeff]=(icp->second);
      else
        backend_error().raise(LOCAL_INFO, "Operator " + sp.str() + " not found in nonrel_WCs!");
      if(icn!=nonrel_WCs.end()) 
        NRWCs.c1[OpCoeff]=(icn->second);
      else
        backend_error().raise(LOCAL_INFO, "Operator " + sn.str() + " not found in nonrel_WCs!");
    }

    NRWCs.CPTbasis = 1;

    return NRWCs;
  }

  /* Convenience functions */

  /// Get Wilson Coefficients at 2 GeV from the SM unbroken phase.
  /// Requires a dictionary of relatavistic WCs, , the DM mass, dchi is the dimension of the DM SU2 representation,
  /// Ychi is the DM hypercharge such that Q = I^3 + Y/2, scale is the scale the Lagrangian is defined at, and
  /// the DM type -- "D" for Dirac fermion; "M" for Majorana fermion; "C" for complex scalar; "R" for real scalar.
  NREO_DM_nucleon_couplings get_NR_WCs_EW(map_str_dbl& relativistic_WCs, double& mDM, 
                                          double& dchi, double& Ychi, double& scale, 
                                          std::string& DM_type, map_str_dbl& input_dict)
  {
    // S.B. 19/09/18: currently only Dirac supported
    if (DM_type != "D")
    {
      backend_error().raise(LOCAL_INFO, "DirectDM at unbroken scale currenly only supports Dirac DM.");
    }

    // Cast the input dict to a Python object
    pybind11::dict inputs = pybind11::cast(input_dict);

    // Import Python class WC_EW from module DirectDM
    pybind11::object WC_EW = DirectDM.attr("WC_EW")(relativistic_WCs, Ychi, dchi, DM_type, inputs);
    
    // Obtain a dictionary of non-relativistic WCs, given the DM mass and the scale the Lagrangian is specified at.
    pybind11::dict cNRs = WC_EW.attr("_my_cNR")(mDM, scale);
    
    // Cast python dictionary to C++ type known to GAMBIT    
    map_str_dbl nonrel_WCs = cNRs.cast<map_str_dbl>(); 

    // Copy coefficients into GAMBIT container object (converting to isoscalar/isovector basis in the process)
    return copy_couplings_to_NREO_container(nonrel_WCs);
  }

  /// Get Wilson Coefficients at 2 GeV in a quark flavour matching scheme.
  /// Requires a dictionary of relatavistic WCs, the DM mass, an integer specifying the number
  /// of quark flavours to match onto, i.e. the 3, 4 or 5 quark flavour scheme, and
  /// the DM type -- "D" for Dirac fermion; "M" for Majorana fermion; "C" for complex scalar; "R" for real scalar.
  NREO_DM_nucleon_couplings get_NR_WCs_flav(map_str_dbl& relativistic_WCs, double& mDM, 
                                            int& scheme, std::string& DM_type,
                                            map_str_dbl& input_dict)
  {
    // We can only load up 3, 4, 5 flavour scheme.
    if (scheme != 3 && scheme != 4 && scheme != 5)
    {
      backend_error().raise(LOCAL_INFO, "DirectDM quark flavour matching scheme must be for "
        "3, 4 or 5 quark flavors.");
    }

    // Remove entries that should not be passed to DirectDM, i.e. any WC referring to a 
    // quark not present in a given scheme.
    for (auto &WC : relativistic_WCs)
    {
      // Remove b quarks for schemes that are 3 and 4..
      if (scheme < 5)
      { 
        if (boost::ends_with(WC.first, "b")) { relativistic_WCs.erase(WC.first); }
      }
      // And remove c for 3.
      if (scheme == 3)
      {
        if (boost::ends_with(WC.first, "c")) { relativistic_WCs.erase(WC.first); }
      }
    }

    // Cast the input dict to a Python object
    pybind11::dict inputs = pybind11::cast(input_dict);

    // Python dictionary of non-relativistic Wilson Coefficients
    pybind11::dict cNRs;

    // Initialise Python class according to number of quark flavours specified from module DirectDM,
    // then obtain a dictionary of non-relativistic WCs, given the DM mass.
    if (scheme == 5)
    {
      pybind11::object WC_5f = DirectDM.attr("WC_5f")(relativistic_WCs, DM_type, inputs);
      cNRs = WC_5f.attr("_my_cNR")(mDM);
    }
    else if (scheme == 4)
    {
      pybind11::object WC_4f = DirectDM.attr("WC_4f")(relativistic_WCs, DM_type, inputs);
      cNRs = WC_4f.attr("_my_cNR")(mDM);
    }
    else if (scheme == 3)
    {
      pybind11::object WC_3f = DirectDM.attr("WC_3f")(relativistic_WCs, DM_type, inputs);
      cNRs = WC_3f.attr("_my_cNR")(mDM);
    }

    // Cast python dictionary to C++ type known to GAMBIT    
    map_str_dbl nonrel_WCs = cNRs.cast<map_str_dbl>();

    // Copy coefficients into GAMBIT container object (converting to isoscalar/isovector basis in the process)
    return copy_couplings_to_NREO_container(nonrel_WCs);
  }

}
END_BE_NAMESPACE
