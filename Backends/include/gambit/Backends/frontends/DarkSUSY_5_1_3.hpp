//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Fronted header for the DarkSUSY backend
///
///  Compile-time registration of available
///  functions and variables from this backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2013 Mar
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Apr
///        2015 Mar
///        2018 Sep
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 Jul
///
///  \author Torsten Bringmann
///          (torsten.bringmann@fys.uio.no)
///  \date 2013 Jul, 2014 Mar, 2015 May
///
///  \author Lars A. Dal
///          (l.a.dal@fys.uio.no)
///  \date 2014 Mar
///
///  \author Joakim Edsjo
///          (edsjo@fysik.su.se)
///  \date 2015 May
///  *********************************************

#define BACKENDNAME DarkSUSY
#define BACKENDLANG FORTRAN
#define VERSION 5.1.3
#define SAFE_VERSION 5_1_3

// Load the library
LOAD_LIBRARY

// Functions
BE_FUNCTION(dsinit, void, (), "dsinit_", "dsinit")
BE_FUNCTION(dshainit, void, (const int&), "dshainit_", "dshainit")
BE_FUNCTION(dssusy, void, (int&,int&), "dssusy_", "dssusy")
BE_FUNCTION(dsrdomega, double, (int&,int&,double&,int&,int&,int&), "dsrdomega_", "dsrdomega")
BE_FUNCTION(dsrdinit, void, (), "dsrdinit_", "dsrdinit")
BE_FUNCTION(dsrdset, void, (char*, int&, char*, int&), "dsrdset_", "dsrdset")
BE_FUNCTION(dsrdthlim, void, (), "dsrdthlim_", "dsrdthlim")
BE_FUNCTION(dsrdtab, void, (double(*)(double&),double&,int&), "dsrdtab_", "dsrdtab")
BE_FUNCTION(dsrdeqn, void, (double(*)(double&),double&,double&,double&,double&,int&), "dsrdeqn_", "dsrdeqn")
BE_FUNCTION(dsrdwintp, double, (double&), "dsrdwintp_", "dsrdwintp")
BE_FUNCTION(dsanwx, double, (double&), "dsanwx_", "dsanwx")
BE_FUNCTION(dshayield, double, (double&,double&,int&,int&,int&), "dshayield_", "dshayield")
BE_FUNCTION(dssusy_isasugra, void, (int&,int&), "dssusy_isasugra_", "dssusy_isasugra")
BE_FUNCTION(dsgive_model_isasugra, void, (double&,double&,double&,double&,double&), "dsgive_model_isasugra_", "dsgive_model_isasugra")
BE_FUNCTION(dssigmav, double, (int&), "dssigmav_", "dssigmav")
BE_FUNCTION(dsIBffdxdy, double, (int&, double&, double&), "dsibffdxdy_", "dsIBffdxdy")
BE_FUNCTION(dsIBfsrdxdy, double, (int&, double&, double&), "dsibfsrdxdy_", "dsIBfsrdxdy")
BE_FUNCTION(dsIBhhdxdy, double, (int&, double&, double&), "dsibhhdxdy_", "dsIBhhdxdy")
BE_FUNCTION(dsIBwhdxdy, double, (int&, double&, double&), "dsibwhdxdy_", "dsIBwhdxdy")
BE_FUNCTION(dsIBwwdxdy, double, (int&, double&, double&), "dsibwwdxdy_", "dsIBwwdxdy")
BE_FUNCTION(dsddgpgn, void, (double&, double&, double&, double&), "dsddgpgn_", "dsddgpgn")
BE_FUNCTION(dsSLHAread, void, (const char*, int&, int), "dsslharead_", "dsSLHAread")
BE_FUNCTION(dsprep, void, (), "dsprep_", "dsprep")
BE_FUNCTION(dsIByieldone, double, (double&, int&, int&, int&), "dsibyieldone_", "dsibyieldone")
BE_FUNCTION(dsntcapsuntab, double, (const double&, const double&, const double&), "dsntcapsuntab_", "cap_Sun_v0q0_isoscalar")
BE_FUNCTION(dsntmuonyield, double, (const double&, const double&, const char&, const int&, const int&, const int&, const int&), "dsntmuonyield_", "raw_muonyield")
BE_FUNCTION(dswspectrum, void, (int&), "dswspectrum_", "dswspectrum")
BE_FUNCTION(dswwidth, void, (int&), "dswwidth_", "dswwidth")
BE_FUNCTION(dssuconst, void, (), "dssuconst_", "dssuconst")
BE_FUNCTION(dsmssmzero, void, (), "dsmssmzero_", "dsmssmzero")
BE_FUNCTION(dsvertx, void, (), "dsvertx_", "dsvertx")
BE_FUNCTION(dsorder_flavour, void, (), "dsorder_flavour_", "dsorder_flavour")
BE_FUNCTION(dshigwid, void, (), "dshigwid_", "dshigwid")
BE_FUNCTION(dsspwid, void, (), "dsspwid_", "dsspwid")
BE_FUNCTION(dsfindmtmt, void, (), "dsfindmtmt_", "dsspwid")
BE_FUNCTION(dssuconst_ckm, void, (), "dssuconst_ckm_", "dssuconst_ckm")
BE_FUNCTION(dssuconst_yukawa_running, void, (), "dssuconst_yukawa_running_", "dssuconst_yukawa_running")
BE_FUNCTION(dsmqpole4loop, double, (int&, double&), "dsmqpole4loop_", "dsmqpole4loop")
BE_FUNCTION(dsspectrum, void, (int&, int&), "dsspectrum_", "dsspectrum")
BE_FUNCTION(dsgf2s2thw, double, (const double&, const double&, const double&, const double&, const int&), "dsgf2s2thw_", "dsgf2s2thw")

// Variables
BE_VARIABLE(pacodes, DS_PACODES, "pacodes_", "pacodes")
BE_VARIABLE(mssmiuseful, DS_MSSMIUSEFUL, "mssmiuseful_", "mssmiuseful")
BE_VARIABLE(mspctm, DS_MSPCTM, "mspctm_", "mspctm")
BE_VARIABLE(widths, DS_WIDTHS, "widths_", "widths")
BE_VARIABLE(intdof, DS_INTDOF, "intdof_", "intdof")
BE_VARIABLE(vrtxs, DS_VRTXS, "vrtxs_", "vrtxs")
BE_VARIABLE(smruseful, DS_SMRUSEFUL, "smruseful_", "smruseful")
BE_VARIABLE(smcuseful, DS_SMCUSEFUL, "smcuseful_", "smcuseful")
BE_VARIABLE(couplingconstants, DS_COUPLINGCONSTANTS, "couplingconstants_", "couplingconstants")
BE_VARIABLE(sckm, DS_SCKM, "sckm_", "sckm")
BE_VARIABLE(mixing, DS_MIXING, "mixing_", "mixing")
BE_VARIABLE(mssmtype, DS_MSSMTYPE, "mssmtype_", "mssmtype")
BE_VARIABLE(mssmpar, DS_MSSMPAR, "mssmpar_", "mssmpar")
BE_VARIABLE(mssmswitch, DS_MSSMSWITCH, "mssmswitch_", "mssmswitch")
BE_VARIABLE(sfermionmass, DS_SFERMIONMASS, "sfermionmass_", "sfermionmass")
BE_VARIABLE(mssmwidths, DS_MSSMWIDTHS, "mssmwidths_", "mssmwidths")
BE_VARIABLE(mssmmixing, DS_MSSMMIXING, "mssmmixing_", "mssmmixing")
// Used in RD_eff_annrate_SUSY_DSprep_func, RD_oh2_general and RD_thresholds_resonances_SingletDM
BE_VARIABLE(rdmgev, DS_RDMGEV,     "rdmgev_",    "rdmgev")    // Contains information about coannihilation
// Appears only in RD_oh2_general
BE_VARIABLE(rdpth, DS_RDPTH,       "rdpth_",     "rdpth")     // gRD thresholds
BE_VARIABLE(rddof, DS_RDDOF,       "rddof_",     "rddof")     // gRD dofs
BE_VARIABLE(rderrors, DS_RDERRORS, "rderrors_", "rderrors")   // gRD errors
BE_VARIABLE(rdpars, DS_RDPARS,     "rdpars_",    "rdpars")    // gRD Parameters
BE_VARIABLE(rdswitch, DS_RDSWITCH, "rdswitch_",  "rdswitch")  // gRD Switches
BE_VARIABLE(rdlun, DS_RDLUN,       "rdlun_",     "rdlun")     // gRD I/O
BE_VARIABLE(rdpadd, DS_RDPADD,     "rdpadd_",    "rdpadd")    // gRD I/O
BE_VARIABLE(rdtime, DS_RDTIME,     "rdtime_",    "rdtime")    // gRD timeout
// IB stuff
BE_VARIABLE(IBintvars, DS_IBINTVARS,"ibintvars_", "IBintvars")
// Direct detection
BE_VARIABLE(ddcom, DS_DDCOM, "ddcom_",    "ddcom")
// Neutrino detection
BE_VARIABLE(wabranch, DS_NUCOM, "wabranch_", "nu_common_block")
// Halo model common blocks
BE_VARIABLE(dshmcom, DS_HMCOM, "dshmcom_", "dshmcom")
BE_VARIABLE(dshmframevelcom, DS_HMFRAMEVELCOM, "dshmframevelcom_", "dshmframevelcom")
BE_VARIABLE(dshmisodf, DS_HMISODF, "dshmisodf_", "dshmisodf")
BE_VARIABLE(dshmnoclue, DS_HMNOCLUE, "dshmnoclue_", "dshmnoclue")

// Convenience functions (registration)
BE_CONV_FUNCTION(neutrino_yield, double, (const double&, const int&, void*&), "nuyield")
BE_CONV_FUNCTION(dsgenericwimp_nusetup, void, (const double(&)[29], const double(&)[29][3], const double(&)[15],
                                               const double(&)[3], const double&, const double&), "nuyield_setup")
BE_CONV_FUNCTION(DSparticle_code, int, (const str&), "particle_code")
BE_CONV_FUNCTION(init_diskless, int, (const SLHAstruct&, const DecayTable&), "initFromSLHAeaAndDecayTable")
BE_CONV_FUNCTION(DS_neutral_h_decay_channels, std::vector<std::vector<str>>, (), "get_DS_neutral_h_decay_channels")
BE_CONV_FUNCTION(DS_charged_h_decay_channels, std::vector<std::vector<str>>, (), "get_DS_charged_h_decay_channels")

// Fraction of DM that is accounted for by model
// BE_INI_DEPENDENCY(RD_fraction, double)

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
