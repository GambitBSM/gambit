//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for the DDCalc backend.
///
///  Actual implementation of DDCalc ini function.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  Authors (add name and date if you modify):
///
///  \author Lars A. Dal
///          (l.a.dal@fys.uio.no)
///  \date 2014 Jul
///
///  \author Christopher Savage
///          (chris@savage.name)
///  \date 2014 Sept
///  \date 2015 Jan,Feb,June
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2016 Apr, Aug
///
///  \author Felix Kahlhoefer
///          (felix.kahlhoefer@desy.de)
///  \date 2016 August
///  \date 2020 May
///
///  \author Sebastian Wild
///          (felix.kahlhoefer@desy.de)
///  \date 2016 Aug
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2020 Feb, May
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/DDCalc_2_2_0.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"

#include <map>
#include <stdexcept>

// File-local globals
BE_NAMESPACE
{
  // Map returning detector index given an analysis name.
  std::map<str,int> ex_map;
  // DM model and halo model singleton indices.
  int WIMP, Halo;
}
END_BE_NAMESPACE


// Initialisation function
BE_INI_FUNCTION
{

  // Halo model parameters and pointers to their entries in the Params map.
  static double rho0_eff = 0.4, vrot = 235, v0 = 235, vesc = 550;
  static safe_ptr<LocalMaxwellianHalo> LocalHaloParameters_ptr;

  // Fraction of DM
  double fraction = *Dep::RD_fraction;

  // Scan-level initialization -----------------------------
  static bool scan_level = true;
  if (scan_level)
  {
    // Initialize halo model
    Halo = DDCalc_InitHalo();
    WIMP = DDCalc_InitWIMP();

    // Initialize experiments
    if (*InUse::DDCalc_Experiment)
    {
      ex_map["XENON100_2012"] = XENON100_2012_Init();
      ex_map["XENON1T_2017"] = XENON1T_2017_Init();
      ex_map["XENON1T_2018"] = XENON1T_2018_Init();
      ex_map["LUX_2013"] = LUX_2013_Init();
      ex_map["SuperCDMS_2014"] = SuperCDMS_2014_Init();
      ex_map["CDMSlite"] = CDMSlite_Init();
      ex_map["SIMPLE_2014"] = SIMPLE_2014_Init();
      ex_map["LUX_2016"] = LUX_2016_Init();
      ex_map["PandaX_2016"] = PandaX_2016_Init();
      ex_map["PandaX_2017"] = PandaX_2017_Init();
      ex_map["LUX_2015"] = LUX_2015_Init();
      ex_map["PICO_2L"] = PICO_2L_Init();
      ex_map["PICO_60"] = PICO_60_Init();
      ex_map["PICO_60_2017"] = PICO_60_2017_Init();
      ex_map["PICO_60_2019"] = PICO_60_2019_Init();
      ex_map["CRESST_II"] = CRESST_II_Init();
      ex_map["CRESST_III"] = CRESST_III_Init();
      ex_map["LZ"] = LZ_Init();
      ex_map["PICO_500"] = PICO_500_Init();
      ex_map["DarkSide_50"] = DarkSide_50_Init();
      ex_map["DarkSide_50_S2"] = DarkSide_50_S2_Init();
      ex_map["DARWIN"] = DARWIN_Init();
      //ex_map["DARWIN_Ar"] = DARWIN_Ar_Init();
      //ex_map["DARWIN_Xe"] = DARWIN_Xe_Init();
    }

    // Save safe pointers to local halo parameters.
    LocalHaloParameters_ptr = Dep::LocalHalo.safe_pointer();
  }

  // Point-level initialization -----------------------------
  scan_level = false;

  // Set WIMP parameters
  DD_coupling_container couplings = *Dep::DDCalc_Couplings;

  // Initialise WIMP object with spin-independent/spin-dependent interactions only
  if (couplings.coeff_structure == 1)
  {
    DM_nucleon_couplings DD_couplings = couplings.DM_nucleon_coeffs;

    // Set DM parameters
    DDCalc_SetWIMP_mG(WIMP, *Dep::mwimp, DD_couplings.gps,DD_couplings.gns,
                                         DD_couplings.gpa,DD_couplings.gna);
  }
  // Initialise WIMP object with non-relativistic effective operator coupling structure
  // Within this coefficient structure DDCalc can use one of 2 coupling structures internally:
  // 1 (CPTbasis == 1):
  //     NREFT_CPT coupling structure as used as output from DirectDM (see arXiv:1708.02678)
  // 2 (CPTbasis == 0): 
  //     NREffectiveTheory coupling structure as used in e.g. arXiv:1505.03117
  else if (couplings.coeff_structure == 2)
  {
    NREO_DM_nucleon_couplings wilsonCoeffs = couplings.DD_nonrel_WCs;
    int OpCoeff;

    // Initialse WIMP object with NREFT_CPT coupling structure 
    if( wilsonCoeffs.CPTbasis )
    {

      // Set the WIMP object in DDCalc to expect non-relativistic EFT coeffs.
      DDCalc_SetWIMP_NREFT_CPT(WIMP, *Dep::mwimp, (double) *Dep::spinwimpx2/2.);
    
      // Loop through non-relativistic WCs and assign the correct coefficients to DDCalc WIMP object.

      for (std::map<int, double>::iterator it = wilsonCoeffs.c0.begin(); it != wilsonCoeffs.c0.end(); it++ )
      {
        OpCoeff = it->first;
        if( (OpCoeff >=1 && OpCoeff <= 23) || OpCoeff == 100 || OpCoeff == 104 )
        { 
          DDCalc_SetNRCoefficient(WIMP, OpCoeff, 0, it->second);
        }
        else { backend_error().raise(LOCAL_INFO, "Unknown operator coefficient " + std::to_string(it->first) + " (c0) given to DDCalc for NREFT_CPT."); }
      }
      for (std::map<int, double>::iterator it = wilsonCoeffs.c1.begin(); it != wilsonCoeffs.c1.end(); it++ )
      {
        OpCoeff = it->first;
        if( (OpCoeff >=1 && OpCoeff <= 23) || OpCoeff == 100 || OpCoeff == 104 )
        { 
          DDCalc_SetNRCoefficient(WIMP, OpCoeff, 1, it->second);
        }
        else { backend_error().raise(LOCAL_INFO, "Unknown operator coefficient " + std::to_string(it->first) + " (c1) given to DDCalc for NREFT_CPT."); }
      }
    }
    // Initialise WIMP object with NREffectiveTheory coupling structure 
    else
    {

      // Set the WIMP object in DDCalc to expect non-relativistic EFT coeffs.
      DDCalc_SetWIMP_NREffectiveTheory(WIMP, *Dep::mwimp, (double) *Dep::spinwimpx2/2.);
    
      // Loop through non-relativistic WCs and assign the correct coefficients to DDCalc WIMP object.
      for (std::map<int, double>::iterator it = wilsonCoeffs.c0.begin(); it != wilsonCoeffs.c0.end(); it++ )
      {
        OpCoeff = it->first;
        if( (OpCoeff >=3 && OpCoeff <= 15) || OpCoeff == 1 || OpCoeff == 17 || OpCoeff == 18 || OpCoeff == -1 || OpCoeff == -4 )
        { 
          DDCalc_SetNRCoefficient(WIMP, OpCoeff, 0, it->second);
        }
        else { backend_error().raise(LOCAL_INFO, "Unknown operator coefficient " + std::to_string(it->first) + " (c0) given to DDCalc for NREffectiveTheory."); }
      }
      for (std::map<int, double>::iterator it = wilsonCoeffs.c1.begin(); it != wilsonCoeffs.c1.end(); it++ )
      {
        OpCoeff = it->first;
        if( (OpCoeff >=3 && OpCoeff <= 15) || OpCoeff == 1 || OpCoeff == 17 || OpCoeff == 18 || OpCoeff == -1 || OpCoeff == -4 )
        { 
          DDCalc_SetNRCoefficient(WIMP, OpCoeff, 1, it->second);
        }
        else { backend_error().raise(LOCAL_INFO, "Unknown operator coefficient " + std::to_string(it->first) + " (c1) given to DDCalc for NREffectiveTheory."); }
      }

    }
  }
  // If DDCalc doesn't know what to do...
  else { backend_error().raise(LOCAL_INFO, "Unknown WIMP type given to DDCalc, with DD_coupling_container.coeff_structure = " + std::to_string(couplings.coeff_structure) + "."); }

  // Change halo parameters.
  bool halo_changed = false;

  if (LocalHaloParameters_ptr->rho0 * fraction != rho0_eff) {rho0_eff = LocalHaloParameters_ptr->rho0 * fraction; halo_changed = true;}
  if (LocalHaloParameters_ptr->vrot != vrot)                {vrot     = LocalHaloParameters_ptr->vrot;            halo_changed = true;}
  if (LocalHaloParameters_ptr->v0   != v0)                  {v0       = LocalHaloParameters_ptr->v0;              halo_changed = true;}
  if (LocalHaloParameters_ptr->vesc != vesc)                {vesc     = LocalHaloParameters_ptr->vesc;            halo_changed = true;}

  if (halo_changed)
  {
    DDCalc_SetSHM(Halo,rho0_eff,vrot,v0,vesc);

    // Log stuff if in debug mode
    #ifdef DDCALC_DEBUG
      logger() << "Updated DDCalc halo parameters:" << EOM;
      logger() << "    rho0 [GeV/cm^3]     = " << LocalHaloParameters_ptr->rho0 << EOM;
      logger() << "    rho0_eff [GeV/cm^3] = " << rho0_eff << EOM;
      logger() << "    vrot [km/s]         = " << vrot << EOM;
      logger() << "    v0   [km/s]         = " << v0   << EOM;
      logger() << "    vesc [km/s]         = " << vesc << EOM;
    #endif
  }

  // Log stuff if in debug mode
  #ifdef DDCALC_DEBUG
    double sigmapSI,sigmanSI,sigmapSD,sigmanSD;
    DDCalc_GetWIMP_msigma(WIMP,*Dep::mwimp,sigmapSI,&sigmanSI,&sigmapSD,&sigmanSD);
    logger() << "DDCalc WIMP-nucleon cross-sections [pb]:" << std::endl;
    logger() << "  sigmapSI = " << sigmapSI << std::endl;
    logger() << "  sigmanSI = " << sigmanSI << std::endl;
    logger() << "  sigmapSD = " << sigmapSD << std::endl;
    logger() << "  sigmanSD = " << sigmanSD << EOM;
  #endif

}
END_BE_INI_FUNCTION

// Convenience functions
BE_NAMESPACE
{
  // Convenience function for returning detector index given an analysis name.
  int DDCalc_Experiment(const str& ex)
  {
    int result = -1;
    try { result = ex_map.at(ex); }
    catch(std::out_of_range&) { backend_error().raise(LOCAL_INFO, "Unknown experiment requested from DDCalc."); }
    return result;
  }

  // Convenience function for calling CalcRates with internally-initialised WIMP and halo objects.
  void DDCalc_CalcRates_simple(const int& D) { DDCalc_CalcRates(D, WIMP, Halo); }
}
END_BE_NAMESPACE
