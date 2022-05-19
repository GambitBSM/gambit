//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for Prospino 2.1 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///  \date 2019 Apr, Nov
///
///  *********************************************

#include "gambit/Backends/backend_singleton.hpp"
#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/Prospino_2_1.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/Utils/slhaea_helpers.hpp"
#include "gambit/Utils/version.hpp"

#define BACKEND_DEBUG 0


// Map from PID_pair to prospino_settings
BE_NAMESPACE
{
  // One giant map initializer:
  static const std::map<PID_pair, prospino_settings> PID_pairs_to_prospino_settings
  {
    //
    // Prospino settings: inlo, isq_ng_in, icoll_in, energy_in, i_error_in, finalState, ipart1, ipart2, isquark1_in, isquark2_in
    // gg
    std::make_pair( PID_pair(1000021, 1000021), prospino_settings(1, 1, 1, 13000., 0, "gg", 1, 1, 0, 0) ),
    // sg
    std::make_pair( PID_pair(1000021, 1000004), prospino_settings(1, 1, 1, 13000., 0, "sg", 1, 1, 4, 4) ),
    std::make_pair( PID_pair(1000021, 1000003), prospino_settings(1, 1, 1, 13000., 0, "sg", 1, 1, 3, 3) ),
    std::make_pair( PID_pair(1000021, 1000001), prospino_settings(1, 1, 1, 13000., 0, "sg", 1, 1, 2, 2) ),
    std::make_pair( PID_pair(1000021, 1000002), prospino_settings(1, 1, 1, 13000., 0, "sg", 1, 1, 1, 1) ),
    std::make_pair( PID_pair(1000021, 2000002), prospino_settings(1, 1, 1, 13000., 0, "sg", 1, 1, 1, 1) ),
    std::make_pair( PID_pair(1000021, 2000001), prospino_settings(1, 1, 1, 13000., 0, "sg", 1, 1, 2, 2) ),
    std::make_pair( PID_pair(1000021, 2000003), prospino_settings(1, 1, 1, 13000., 0, "sg", 1, 1, 3, 3) ),
    std::make_pair( PID_pair(1000021, 2000004), prospino_settings(1, 1, 1, 13000., 0, "sg", 1, 1, 4, 4) ),
    // sb
    std::make_pair( PID_pair(1000004,-1000004), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 4, 4) ),
    std::make_pair( PID_pair(1000004,-1000003), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 4, 3) ),
    std::make_pair( PID_pair(1000004,-1000001), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 4, 2) ),
    std::make_pair( PID_pair(1000004,-1000002), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 4, 1) ),
    std::make_pair( PID_pair(1000004,-2000002), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 4, 1) ),
    std::make_pair( PID_pair(1000004,-2000001), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 4, 2) ),
    std::make_pair( PID_pair(1000004,-2000003), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 4, 3) ),
    std::make_pair( PID_pair(1000004,-2000004), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 4, 4) ),
    std::make_pair( PID_pair(1000003,-1000003), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 3, 3) ),
    std::make_pair( PID_pair(1000003,-1000001), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 3, 2) ),
    std::make_pair( PID_pair(1000003,-1000002), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 3, 1) ),
    std::make_pair( PID_pair(1000003,-2000002), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 3, 1) ),
    std::make_pair( PID_pair(1000003,-2000001), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 3, 2) ),
    std::make_pair( PID_pair(1000003,-2000003), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 3, 3) ),
    std::make_pair( PID_pair(1000003,-2000004), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 3, 4) ),
    std::make_pair( PID_pair(1000001,-1000001), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 2, 2) ),
    std::make_pair( PID_pair(1000001,-1000002), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 2, 1) ),
    std::make_pair( PID_pair(1000001,-2000002), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 2, 1) ),
    std::make_pair( PID_pair(1000001,-2000001), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 2, 2) ),
    std::make_pair( PID_pair(1000001,-2000003), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 2, 3) ),
    std::make_pair( PID_pair(1000001,-2000004), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 2, 4) ),
    std::make_pair( PID_pair(1000002,-1000002), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 1, 1) ),
    std::make_pair( PID_pair(1000002,-2000002), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 1, 1) ),
    std::make_pair( PID_pair(1000002,-2000001), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 1, 2) ),
    std::make_pair( PID_pair(1000002,-2000003), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 1, 3) ),
    std::make_pair( PID_pair(1000002,-2000004), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 1, 4) ),
    std::make_pair( PID_pair(2000002,-2000002), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 1, 1) ),
    std::make_pair( PID_pair(2000002,-2000001), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 1, 2) ),
    std::make_pair( PID_pair(2000002,-2000003), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 1, 3) ),
    std::make_pair( PID_pair(2000002,-2000004), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 1, 4) ),
    std::make_pair( PID_pair(2000001,-2000001), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 2, 2) ),
    std::make_pair( PID_pair(2000001,-2000003), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 2, 3) ),
    std::make_pair( PID_pair(2000001,-2000004), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 2, 4) ),
    std::make_pair( PID_pair(2000003,-2000003), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 3, 3) ),
    std::make_pair( PID_pair(2000003,-2000004), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 3, 4) ),
    std::make_pair( PID_pair(2000004,-2000004), prospino_settings(1, 1, 1, 13000., 0, "sb", 1, 1, 4, 4) ),
    // ss
    std::make_pair( PID_pair(1000004, 1000004), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 4, 4) ),
    std::make_pair( PID_pair(1000004, 1000003), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 4, 3) ),
    std::make_pair( PID_pair(1000004, 1000001), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 4, 2) ),
    std::make_pair( PID_pair(1000004, 1000002), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 4, 1) ),
    std::make_pair( PID_pair(1000004, 2000002), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 4, 1) ),
    std::make_pair( PID_pair(1000004, 2000001), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 4, 2) ),
    std::make_pair( PID_pair(1000004, 2000003), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 4, 3) ),
    std::make_pair( PID_pair(1000004, 2000004), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 4, 4) ),
    std::make_pair( PID_pair(1000003, 1000003), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 3, 3) ),
    std::make_pair( PID_pair(1000003, 1000001), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 3, 2) ),
    std::make_pair( PID_pair(1000003, 1000002), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 3, 1) ),
    std::make_pair( PID_pair(1000003, 2000002), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 3, 1) ),
    std::make_pair( PID_pair(1000003, 2000001), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 3, 2) ),
    std::make_pair( PID_pair(1000003, 2000003), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 3, 3) ),
    std::make_pair( PID_pair(1000003, 2000004), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 3, 4) ),
    std::make_pair( PID_pair(1000001, 1000001), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 2, 2) ),
    std::make_pair( PID_pair(1000001, 1000002), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 2, 1) ),
    std::make_pair( PID_pair(1000001, 2000002), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 2, 1) ),
    std::make_pair( PID_pair(1000001, 2000001), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 2, 2) ),
    std::make_pair( PID_pair(1000001, 2000003), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 2, 3) ),
    std::make_pair( PID_pair(1000001, 2000004), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 2, 4) ),
    std::make_pair( PID_pair(1000002, 1000002), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 1, 1) ),
    std::make_pair( PID_pair(1000002, 2000002), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 1, 1) ),
    std::make_pair( PID_pair(1000002, 2000001), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 1, 2) ),
    std::make_pair( PID_pair(1000002, 2000003), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 1, 3) ),
    std::make_pair( PID_pair(1000002, 2000004), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 1, 4) ),
    std::make_pair( PID_pair(2000002, 2000002), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 1, 1) ),
    std::make_pair( PID_pair(2000002, 2000001), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 1, 2) ),
    std::make_pair( PID_pair(2000002, 2000003), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 1, 3) ),
    std::make_pair( PID_pair(2000002, 2000004), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 1, 4) ),
    std::make_pair( PID_pair(2000001, 2000001), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 2, 2) ),
    std::make_pair( PID_pair(2000001, 2000003), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 2, 3) ),
    std::make_pair( PID_pair(2000001, 2000004), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 2, 4) ),
    std::make_pair( PID_pair(2000003, 2000003), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 3, 3) ),
    std::make_pair( PID_pair(2000003, 2000004), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 3, 4) ),
    std::make_pair( PID_pair(2000004, 2000004), prospino_settings(1, 1, 1, 13000., 0, "ss", 1, 1, 4, 4) ),
    // tb
    std::make_pair( PID_pair(1000006,-1000006), prospino_settings(1, 1, 1, 13000., 0, "tb", 1, 1, 0, 0) ),
    std::make_pair( PID_pair(2000006,-2000006), prospino_settings(1, 1, 1, 13000., 0, "tb", 2, 2, 0, 0) ),
    // bb
    std::make_pair( PID_pair(1000005,-1000005), prospino_settings(1, 1, 1, 13000., 0, "bb", 1, 1, 0, 0) ),
    std::make_pair( PID_pair(2000005,-2000005), prospino_settings(1, 1, 1, 13000., 0, "bb", 2, 2, 0, 0) ),
    // nn
    std::make_pair( PID_pair(1000022, 1000022), prospino_settings(1, 1, 1, 13000., 0, "nn", 1, 1, 0, 0) ),
    std::make_pair( PID_pair(1000022, 1000023), prospino_settings(1, 1, 1, 13000., 0, "nn", 1, 2, 0, 0) ),
    std::make_pair( PID_pair(1000022, 1000025), prospino_settings(1, 1, 1, 13000., 0, "nn", 1, 3, 0, 0) ),
    std::make_pair( PID_pair(1000022, 1000035), prospino_settings(1, 1, 1, 13000., 0, "nn", 1, 4, 0, 0) ),
    std::make_pair( PID_pair(1000022, 1000024), prospino_settings(1, 1, 1, 13000., 0, "nn", 1, 5, 0, 0) ),
    std::make_pair( PID_pair(1000022, 1000037), prospino_settings(1, 1, 1, 13000., 0, "nn", 1, 6, 0, 0) ),
    std::make_pair( PID_pair(1000022,-1000024), prospino_settings(1, 1, 1, 13000., 0, "nn", 1, 7, 0, 0) ),
    std::make_pair( PID_pair(1000022,-1000037), prospino_settings(1, 1, 1, 13000., 0, "nn", 1, 8, 0, 0) ),
    std::make_pair( PID_pair(1000023, 1000023), prospino_settings(1, 1, 1, 13000., 0, "nn", 2, 2, 0, 0) ),
    std::make_pair( PID_pair(1000023, 1000025), prospino_settings(1, 1, 1, 13000., 0, "nn", 2, 3, 0, 0) ),
    std::make_pair( PID_pair(1000023, 1000035), prospino_settings(1, 1, 1, 13000., 0, "nn", 2, 4, 0, 0) ),
    std::make_pair( PID_pair(1000023, 1000024), prospino_settings(1, 1, 1, 13000., 0, "nn", 2, 5, 0, 0) ),
    std::make_pair( PID_pair(1000023, 1000037), prospino_settings(1, 1, 1, 13000., 0, "nn", 2, 6, 0, 0) ),
    std::make_pair( PID_pair(1000023,-1000024), prospino_settings(1, 1, 1, 13000., 0, "nn", 2, 7, 0, 0) ),
    std::make_pair( PID_pair(1000023,-1000037), prospino_settings(1, 1, 1, 13000., 0, "nn", 2, 8, 0, 0) ),
    std::make_pair( PID_pair(1000025, 1000025), prospino_settings(1, 1, 1, 13000., 0, "nn", 3, 3, 0, 0) ),
    std::make_pair( PID_pair(1000025, 1000035), prospino_settings(1, 1, 1, 13000., 0, "nn", 3, 4, 0, 0) ),
    std::make_pair( PID_pair(1000025, 1000024), prospino_settings(1, 1, 1, 13000., 0, "nn", 3, 5, 0, 0) ),
    std::make_pair( PID_pair(1000025, 1000037), prospino_settings(1, 1, 1, 13000., 0, "nn", 3, 6, 0, 0) ),
    std::make_pair( PID_pair(1000025,-1000024), prospino_settings(1, 1, 1, 13000., 0, "nn", 3, 7, 0, 0) ),
    std::make_pair( PID_pair(1000025,-1000037), prospino_settings(1, 1, 1, 13000., 0, "nn", 3, 8, 0, 0) ),
    std::make_pair( PID_pair(1000035, 1000035), prospino_settings(1, 1, 1, 13000., 0, "nn", 4, 4, 0, 0) ),
    std::make_pair( PID_pair(1000035, 1000024), prospino_settings(1, 1, 1, 13000., 0, "nn", 4, 5, 0, 0) ),
    std::make_pair( PID_pair(1000035, 1000037), prospino_settings(1, 1, 1, 13000., 0, "nn", 4, 6, 0, 0) ),
    std::make_pair( PID_pair(1000035,-1000024), prospino_settings(1, 1, 1, 13000., 0, "nn", 4, 7, 0, 0) ),
    std::make_pair( PID_pair(1000035,-1000037), prospino_settings(1, 1, 1, 13000., 0, "nn", 4, 8, 0, 0) ),
    std::make_pair( PID_pair(1000024, 1000024), prospino_settings(1, 1, 1, 13000., 0, "nn", 5, 5, 0, 0) ),
    std::make_pair( PID_pair(1000024, 1000037), prospino_settings(1, 1, 1, 13000., 0, "nn", 5, 6, 0, 0) ),
    std::make_pair( PID_pair(1000024,-1000024), prospino_settings(1, 1, 1, 13000., 0, "nn", 5, 7, 0, 0) ),
    std::make_pair( PID_pair(1000024,-1000037), prospino_settings(1, 1, 1, 13000., 0, "nn", 5, 8, 0, 0) ),
    std::make_pair( PID_pair(1000037, 1000037), prospino_settings(1, 1, 1, 13000., 0, "nn", 6, 6, 0, 0) ),
    std::make_pair( PID_pair(1000037,-1000024), prospino_settings(1, 1, 1, 13000., 0, "nn", 6, 7, 0, 0) ),
    std::make_pair( PID_pair(1000037,-1000037), prospino_settings(1, 1, 1, 13000., 0, "nn", 6, 8, 0, 0) ),
    // ll
    std::make_pair( PID_pair(1000011,-1000011), prospino_settings(1, 1, 1, 13000., 0, "ll", 1, 1, 0, 0) ),
    std::make_pair( PID_pair(2000011,-2000011), prospino_settings(1, 1, 1, 13000., 0, "ll", 2, 1, 0, 0) ),
    std::make_pair( PID_pair(1000012,-1000012), prospino_settings(1, 1, 1, 13000., 0, "ll", 3, 1, 0, 0) ),
    std::make_pair( PID_pair(1000012,-1000011), prospino_settings(1, 1, 1, 13000., 0, "ll", 4, 1, 0, 0) ),
    std::make_pair( PID_pair(1000011,-1000012), prospino_settings(1, 1, 1, 13000., 0, "ll", 5, 1, 0, 0) ),
    std::make_pair( PID_pair(1000015,-1000015), prospino_settings(1, 1, 1, 13000., 0, "ll", 6, 1, 0, 0) ),
    std::make_pair( PID_pair(2000015,-2000015), prospino_settings(1, 1, 1, 13000., 0, "ll", 7, 1, 0, 0) ),
    std::make_pair( PID_pair(1000015,-2000015), prospino_settings(1, 1, 1, 13000., 0, "ll", 8, 1, 0, 0) ),
    std::make_pair( PID_pair(1000016,-1000016), prospino_settings(1, 1, 1, 13000., 0, "ll", 9, 1, 0, 0) ),
    std::make_pair( PID_pair(1000016,-1000015), prospino_settings(1, 1, 1, 13000., 0, "ll", 10, 1, 0, 0) ),
    std::make_pair( PID_pair(1000015,-1000016), prospino_settings(1, 1, 1, 13000., 0, "ll", 11, 1, 0, 0) ),
    std::make_pair( PID_pair(1000016,-2000015), prospino_settings(1, 1, 1, 13000., 0, "ll", 12, 1, 0, 0) ),
    std::make_pair( PID_pair(2000015,-1000016), prospino_settings(1, 1, 1, 13000., 0, "ll", 13, 1, 0, 0) ),
  };

  // Input arrays for prospino 
  Farray<Fdouble,1,20> unimass;
  Farray<Fdouble,0,99> lowmass;
  Farray<Fdouble,1,2,1,2> uu_in, vv_in;
  Farray<Fdouble,1,4,1,4> bw_in;
  Farray<Fdouble,1,2,1,2> mst_in, msb_in, msl_in;

}
END_BE_NAMESPACE


// Helper function to apply mass spectrum modifications required for specific processes.
BE_NAMESPACE
{
  Farray<Fdouble,0,99> process_specific_lowmass_mods(Farray<Fdouble,0,99> lowmass_in, const PID_pair& pid_pair, int& trust_level)
  {
    // Copy input array to output array
    Farray<Fdouble,0,99> lowmass_out(lowmass_in);

    // Read the absolute-value pids
    int abs_pid1 = abs(pid_pair.pid1());
    int abs_pid2 = abs(pid_pair.pid2());

    double delta_m = 0;

    // These mass values are on purpose set just below the true values
    const static double mZ = 91.18;
    const static double mW = 80.37;

    // Useful maps and vectors
    static const std::map<int,int> pid_lowmass_map = {{1000022,5},
                                                      {1000023,6},
                                                      {1000025,7},
                                                      {1000035,8},
                                                      {1000024,9}, 
                                                      {1000037,10}};
    
    static const std::vector<int> neutralino_pids = {1000022, 1000023, 1000025, 1000035};
    static const std::vector<int> chargino_pids = {1000024, 1000037};


    // Neutralino and chargino processes
    bool pid1_neutralino = false; 
    bool pid2_neutralino = false; 
    bool pid1_chargino = false; 
    bool pid2_chargino = false; 

    if(std::find(neutralino_pids.begin(), neutralino_pids.end(), abs_pid1) != neutralino_pids.end())
    {
      pid1_neutralino = true;
    }
    else if(std::find(chargino_pids.begin(), chargino_pids.end(), abs_pid1) != chargino_pids.end())
    {
      pid1_chargino = true;
    }

    if(std::find(neutralino_pids.begin(), neutralino_pids.end(), abs_pid2) != neutralino_pids.end())
    {
      pid2_neutralino = true;
    }
    else if(std::find(chargino_pids.begin(), chargino_pids.end(), abs_pid2) != chargino_pids.end())
    {
      pid2_chargino = true;
    }

    // neutralino--neutralino 
    if(pid1_neutralino && pid2_neutralino)
    {
      int pid1_index = pid_lowmass_map.at(abs_pid1);
      int pid2_index = pid_lowmass_map.at(abs_pid2);
      delta_m = abs(lowmass_out(pid1_index)) + abs(lowmass_out(pid2_index)) - mZ;
    }
    // neutralino--chargino 
    else if((pid1_neutralino && pid2_chargino) || (pid1_chargino && pid2_neutralino))
    {
      int pid1_index = pid_lowmass_map.at(abs_pid1);
      int pid2_index = pid_lowmass_map.at(abs_pid2);
      delta_m = abs(lowmass_out(pid1_index)) + abs(lowmass_out(pid2_index)) - mW;
    }
    // chargino--chargino 
    else if((pid1_chargino && pid2_chargino) || (pid1_chargino && pid2_chargino))
    {
      int pid1_index = pid_lowmass_map.at(abs_pid1);
      int pid2_index = pid_lowmass_map.at(abs_pid2);
      delta_m = abs(lowmass_out(pid1_index)) + abs(lowmass_out(pid2_index)) - mZ;
    }


    // Now increase the masses if necessary
    if(delta_m < 0)
    {
      int pid1_index = pid_lowmass_map.at(abs_pid1);
      int pid2_index = pid_lowmass_map.at(abs_pid2);

      int sign_mass_pid1 = lowmass_out(pid1_index) < 0 ? -1 : 1;
      int sign_mass_pid2 = lowmass_out(pid2_index) < 0 ? -1 : 1;
      
      lowmass_out(pid1_index) = sign_mass_pid1 * (abs(lowmass_out(pid1_index)) + 0.5 * abs(delta_m));
      lowmass_out(pid2_index) = sign_mass_pid2 * (abs(lowmass_out(pid2_index)) + 0.5 * abs(delta_m));

      // Setting trust_level = 0, since we're in the region were we can't really trust the result
      trust_level = 0;
    }

    return lowmass_out;
  }
}
END_BE_NAMESPACE


// Callback function for error handling
BE_NAMESPACE
{
  // This function will be called from Prospino. Needs C linkage, and thus also
  // a backend-specific name to guard against name clashes.
  extern "C"
  void CAT_4(BACKENDNAME,_,SAFE_VERSION,_ErrorHandler)()
  {
    throw std::runtime_error("Prospino backend called HARD_STOP.");
  }
}
END_BE_NAMESPACE


// Backend init function
BE_INI_FUNCTION
{
  // Scan-level initialisation
  static bool scan_level = true;
  if (scan_level)
  {
    // Point the function pointer variable from Prospino to our ErrorHandler callback function
    *ErrorHandler_cptr = & CAT_4(BACKENDNAME,_,SAFE_VERSION,_ErrorHandler);

    // Help Prospino find itself
    std::string prospino_dir = Backends::backendInfo().path_dir(STRINGIFY(BACKENDNAME), STRINGIFY(VERSION));
    Fstring<500> prospino_dir_in = prospino_dir.c_str();
    try{ prospino_gb_init(prospino_dir_in); }
    catch(std::runtime_error& e) { invalid_point().raise(e.what()); }
  }
  scan_level = false;

  // Point-level initialisation
  // Clear the input arrays
  std::fill(std::begin(unimass.array), std::end(unimass.array), 0.0);
  std::fill(std::begin(lowmass.array), std::end(lowmass.array), 0.0);
  std::fill(std::begin(uu_in.array), std::end(uu_in.array), 0.0);
  std::fill(std::begin(vv_in.array), std::end(vv_in.array), 0.0);
  std::fill(std::begin(bw_in.array), std::end(bw_in.array), 0.0);
  std::fill(std::begin(mst_in.array), std::end(mst_in.array), 0.0);
  std::fill(std::begin(msb_in.array), std::end(msb_in.array), 0.0);
  std::fill(std::begin(msl_in.array), std::end(msl_in.array), 0.0);
}
END_BE_INI_FUNCTION


// Convenience functions (definition)
BE_NAMESPACE
{
  // Convenience function to fill Prospino arrays from SLHA1 input
  void prospino_read_slha1_input(const SLHAstruct& slha)
  {
    // Get type converter 
    using SLHAea::to;

    // Fill input arrays
    lowmass(0) = to<double>(slha.at("HMIX").at(1).at(1));
    lowmass(1) = to<double>(slha.at("MSOFT").at(1).at(1));
    lowmass(2) = to<double>(slha.at("MSOFT").at(2).at(1));
    lowmass(3) = to<double>(slha.at("MSOFT").at(3).at(1));

    lowmass(4) = to<double>(slha.at("MASS").at(1000021).at(1));

    lowmass(5) = to<double>(slha.at("MASS").at(1000022).at(1));
    lowmass(6) = to<double>(slha.at("MASS").at(1000023).at(1));
    lowmass(7) = to<double>(slha.at("MASS").at(1000025).at(1));
    lowmass(8) = to<double>(slha.at("MASS").at(1000035).at(1));

    lowmass(9) = to<double>(slha.at("MASS").at(1000024).at(1));
    lowmass(10) = to<double>(slha.at("MASS").at(1000037).at(1));

    lowmass(11) = to<double>(slha.at("MASS").at(1000001).at(1));
    lowmass(52) = lowmass(11);

    lowmass(12) = to<double>(slha.at("MASS").at(2000001).at(1));
    lowmass(58) = lowmass(12);

    lowmass(13) = to<double>(slha.at("MASS").at(1000002).at(1));
    lowmass(51) = lowmass(13);

    lowmass(14) = to<double>(slha.at("MASS").at(2000002).at(1));
    lowmass(57) = lowmass(14);

    lowmass(17) = to<double>(slha.at("MASS").at(1000005).at(1));
    lowmass(55) = lowmass(17);

    lowmass(18) = to<double>(slha.at("MASS").at(2000005).at(1));
    lowmass(61) = lowmass(18);

    lowmass(19) = to<double>(slha.at("MASS").at(1000006).at(1));
    lowmass(56) = lowmass(19);

    lowmass(20) = to<double>(slha.at("MASS").at(2000006).at(1));
    lowmass(62) = lowmass(20);

    lowmass(30) = to<double>(slha.at("MASS").at(1000011).at(1));

    lowmass(31) = to<double>(slha.at("MASS").at(2000011).at(1));

    lowmass(32) = to<double>(slha.at("MASS").at(1000012).at(1));

    lowmass(33) = to<double>(slha.at("MASS").at(1000015).at(1));

    lowmass(34) = to<double>(slha.at("MASS").at(2000015).at(1));

    lowmass(35) = to<double>(slha.at("MASS").at(1000016).at(1));

    lowmass(40) = to<double>(slha.at("MASS").at(36).at(1));

    lowmass(41) = to<double>(slha.at("MASS").at(25).at(1));

    lowmass(42) = to<double>(slha.at("MASS").at(35).at(1));

    lowmass(43) = to<double>(slha.at("MASS").at(37).at(1));

    lowmass(53) = to<double>(slha.at("MASS").at(1000003).at(1));

    lowmass(59) = to<double>(slha.at("MASS").at(2000003).at(1));

    lowmass(54) = to<double>(slha.at("MASS").at(1000004).at(1));

    lowmass(60) = to<double>(slha.at("MASS").at(2000004).at(1));

    // Degenerate squark masses
    double degen_squark_mass_8 = 0.;
    degen_squark_mass_8 += lowmass(51) + lowmass(52) + lowmass(53) + lowmass(54);
    degen_squark_mass_8 += lowmass(57) + lowmass(58) + lowmass(59) + lowmass(60);
    degen_squark_mass_8 = degen_squark_mass_8/8.;
    lowmass(15) = degen_squark_mass_8;

    double degen_squark_mass_10 = 0.;
    degen_squark_mass_10 += lowmass(51) + lowmass(52) + lowmass(53) + lowmass(54) + lowmass(55);
    degen_squark_mass_10 += lowmass(57) + lowmass(58) + lowmass(59) + lowmass(60) + lowmass(61);
    degen_squark_mass_10 = degen_squark_mass_10/10.;
    lowmass(16) = degen_squark_mass_10;

    // BLOCK ALPHA
    double alpha = to<double>( slha.at("ALPHA").back().front() );
    lowmass(44) = sin(alpha);
    lowmass(45) = cos(alpha);

    // AD, AU, AE
    lowmass(21) = -to<double>(slha.at("AD").at(3,3).at(2));   // Note sign!
    lowmass(24) = -to<double>(slha.at("AU").at(3,3).at(2));   // Note sign!
    lowmass(36) = -to<double>(slha.at("AE").at(3,3).at(2));   // Note sign!

    // Neutralino mixing matrix
    bw_in(1,1) = to<double>(slha.at("NMIX").at(1,1).at(2));
    bw_in(1,2) = to<double>(slha.at("NMIX").at(1,2).at(2));
    bw_in(1,3) = to<double>(slha.at("NMIX").at(1,3).at(2));
    bw_in(1,4) = to<double>(slha.at("NMIX").at(1,4).at(2));
    bw_in(2,1) = to<double>(slha.at("NMIX").at(2,1).at(2));
    bw_in(2,2) = to<double>(slha.at("NMIX").at(2,2).at(2));
    bw_in(2,3) = to<double>(slha.at("NMIX").at(2,3).at(2));
    bw_in(2,4) = to<double>(slha.at("NMIX").at(2,4).at(2));
    bw_in(3,1) = to<double>(slha.at("NMIX").at(3,1).at(2));
    bw_in(3,2) = to<double>(slha.at("NMIX").at(3,2).at(2));
    bw_in(3,3) = to<double>(slha.at("NMIX").at(3,3).at(2));
    bw_in(3,4) = to<double>(slha.at("NMIX").at(3,4).at(2));
    bw_in(4,1) = to<double>(slha.at("NMIX").at(4,1).at(2));
    bw_in(4,2) = to<double>(slha.at("NMIX").at(4,2).at(2));
    bw_in(4,3) = to<double>(slha.at("NMIX").at(4,3).at(2));
    bw_in(4,4) = to<double>(slha.at("NMIX").at(4,4).at(2));

    // Chargino mixing matrix
    uu_in(1,1) = to<double>(slha.at("UMIX").at(1,1).at(2));
    uu_in(1,2) = to<double>(slha.at("UMIX").at(1,2).at(2));
    uu_in(2,1) = to<double>(slha.at("UMIX").at(2,1).at(2));
    uu_in(2,2) = to<double>(slha.at("UMIX").at(2,2).at(2));

    vv_in(1,1) = to<double>(slha.at("VMIX").at(1,1).at(2));
    vv_in(1,2) = to<double>(slha.at("VMIX").at(1,2).at(2));
    vv_in(2,1) = to<double>(slha.at("VMIX").at(2,1).at(2));
    vv_in(2,2) = to<double>(slha.at("VMIX").at(2,2).at(2));

    // Sfermion mixing matrices
    mst_in(1,1) = to<double>(slha.at("STOPMIX").at(1,1).at(2));
    mst_in(1,2) = to<double>(slha.at("STOPMIX").at(1,2).at(2));
    mst_in(2,1) = to<double>(slha.at("STOPMIX").at(2,1).at(2));
    mst_in(2,2) = to<double>(slha.at("STOPMIX").at(2,2).at(2));

    msb_in(1,1) = to<double>(slha.at("SBOTMIX").at(1,1).at(2));
    msb_in(1,2) = to<double>(slha.at("SBOTMIX").at(1,2).at(2));
    msb_in(2,1) = to<double>(slha.at("SBOTMIX").at(2,1).at(2));
    msb_in(2,2) = to<double>(slha.at("SBOTMIX").at(2,2).at(2));

    msl_in(1,1) = to<double>(slha.at("STAUMIX").at(1,1).at(2));
    msl_in(1,2) = to<double>(slha.at("STAUMIX").at(1,2).at(2));
    msl_in(2,1) = to<double>(slha.at("STAUMIX").at(2,1).at(2));
    msl_in(2,2) = to<double>(slha.at("STAUMIX").at(2,2).at(2));
  }


  // Convenience function to run Prospino and get a vector of cross-sections,
  // with Prospino settings from YAML options
  map_str_dbl prospino_run(const PID_pair& pid_pair, const Options& runOptions)
  {
    // Get run options
    // @todo Should the collider settings (e.g. energy) be automatically matched to the Pythia instance?
    int inlo = runOptions.getValueOrDef<int>(1, "inlo");                 // specify LO only[0] or complete NLO (slower)[1]
    int isq_ng_in = runOptions.getValueOrDef<int>(1, "isq_ng_in");       // specify degenerate [0] or free [1] squark masses
    int icoll_in = runOptions.getValueOrDef<int>(1, "icoll_in");         // collider : tevatron[0], lhc[1]
    double energy_in = runOptions.getValueOrDef<double>(13000.0, "energy_in");  // collider energy in GeV
    int i_error_in = runOptions.getValueOrDef<int>(0, "i_error_in");     // with central scale [0] or scale variation [1]
    bool set_missing_cross_sections_to_zero = runOptions.getValueOrDef<bool>(false, "set_missing_cross_sections_to_zero");

    return prospino_run_alloptions(pid_pair, inlo, isq_ng_in, icoll_in, energy_in, i_error_in, set_missing_cross_sections_to_zero);
  }

  // Convenience function to run Prospino and get a vector of cross-sections,
  // with Prospino settings directly as function arguments
  map_str_dbl prospino_run_alloptions(const PID_pair& pid_pair, const int& inlo, const int& isq_ng_in, const int& icoll_in, const double& energy_in, const int& i_error_in,
                                      const bool& set_missing_cross_sections_to_zero)
  {
    // Initially set trust_level = 1
    int trust_level = 1;

    // Check that we have a set of prospino settings for the given PID_pair
    if(PID_pairs_to_prospino_settings.find(pid_pair) == PID_pairs_to_prospino_settings.end())
    {
      if(set_missing_cross_sections_to_zero)
      {
        map_str_dbl result;
        result["LO[pb]"] = 0.0;
        result["LO_rel_error"] = 0.0;
        result["NLO[pb]"] = 0.0;
        result["NLO_rel_error"] = 0.0;
        result["K"] = 0.0;
        result["LO_ms[pb]"] = 0.0;
        result["NLO_ms[pb]"] = 0.0;
        result["trust_level"] = 1.0;
        return result;
      }
      else
      {
        str errmsg;
        errmsg = "No prospino settings found for the PID_pair " + pid_pair.str() + ".";
        backend_error().raise(LOCAL_INFO, errmsg);
      }
    }

    // Get prospino settings
    prospino_settings ps( PID_pairs_to_prospino_settings.at(pid_pair) );

    // Update the prospino_settings instance with the run options
    ps.inlo = inlo;
    ps.isq_ng_in = isq_ng_in;
    ps.icoll_in = icoll_in;
    ps.energy_in = energy_in;
    ps.i_error_in = i_error_in;

    // Are any process-specific modifications required for this process? And do they affect the trust_level?
    Farray<Fdouble,0,99> lowmass_mod;
    lowmass_mod = process_specific_lowmass_mods(lowmass, pid_pair, trust_level);

    // Call prospino
    Farray<Fdouble,0,6> prospino_result;

    try
    { 
        prospino_gb(prospino_result, ps.inlo, ps.isq_ng_in, ps.icoll_in, ps.energy_in, ps.i_error_in, 
                    ps.final_state_in, ps.ipart1_in, ps.ipart2_in, ps.isquark1_in, ps.isquark2_in,
                    unimass, lowmass_mod, uu_in, vv_in, bw_in, mst_in, msb_in, msl_in);
    }
    catch(std::runtime_error& e) { invalid_point().raise(e.what()); }

    // Fill the result map with the content of prospino_result
    map_str_dbl result;
    result["LO[pb]"] = prospino_result(0);
    result["LO_rel_error"] = prospino_result(1);
    result["NLO[pb]"] = prospino_result(2);
    result["NLO_rel_error"] = prospino_result(3);
    result["K"] = prospino_result(4);
    result["LO_ms[pb]"] = prospino_result(5);
    result["NLO_ms[pb]"] = prospino_result(6);

    result["trust_level"] = static_cast<double>(trust_level);

    return result;
  }

}
END_BE_NAMESPACE
