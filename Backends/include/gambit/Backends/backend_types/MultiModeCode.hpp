//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper types for MultiModeCode backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Selim C. Hotinli
///          selim.hotinli14@imperial.ac.uk
///  \date 2017 June
///  \date 2017 Oct
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Feb
///
///  *************************

#include "gambit/Utils/util_types.hpp"

#ifndef __MultiModeCode_hpp__
#define __MultiModeCode_hpp__

namespace Gambit
{

    // type definition for the multimodecode output.
    struct gambit_inflation_observables
    {
        bool check_ic_ok;
        double As;
        double A_iso;
        double A_pnad;
        double A_ent;
        double A_cross_ad_iso;
        double ns;
        double nt;
        double n_iso;
        double n_pnad;
        double n_ent;
        double N_pivot;
        double r;
        double alpha_s;
        double runofrun;
        double f_NL;
        double tau_NL;
        double k_array[1000];
        double pks_array[1000];
        double pks_array_iso[1000];
        double pkt_array[1000];
        int k_size;
        int err = 0;
    };

    /// Class containing the inputs used for inputs to MultiModeCode
    class Multimode_inputs
    {
        public:
            // Constructor
            Multimode_inputs();
            // Debugging options
            int silence_output;
            // k values where to evaluate the power spectrum
            double k_min;
            double k_max;
            int numsteps;
            // Parameters realted to the pivot scale
            double k_pivot;
            double N_pivot;
            double dlnk;
            // Parameters related to the potential and initial condidtions
            int num_inflaton = -1;
            int potential_choice = -1;
            int vparam_rows = -1;
            std::vector<double> vparams;
            std::vector<double> phi_init0;
            std::vector<double> dphi_init0;
            // Parameters realted to the scenario for initial conditions
            int slowroll_infl_end;
            int instreheat;
            // Parameters related to approximations and observables
            int use_deltaN_SR;
            int evaluate_modes;
            int use_horiz_cross_approx;
            int get_runningofrunning;
    };
}

#endif // defined __MultiModeCode_hpp__
