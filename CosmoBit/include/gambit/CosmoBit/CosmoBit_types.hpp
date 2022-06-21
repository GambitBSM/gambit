//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Type definition header for module CosmoBit.
///
///  Compile-time registration of type definitions
///  required for the rest of the code to
///  communicate with CosmoBit.
///
///  Add to this if you want to define a new type
///  for the functions in CosmoBit to return, but
///  you don't expect that type to be needed by
///  any other modules.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2017 Nov
///  \date 2018 May
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 Oct
///  \date 2019 Mar
///
///  \author Sebastian Hoof
///          (hoof@uni-goettingen.de)
///  \date 2020 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Apr
///
///  *********************************************


#ifndef __CosmoBit_types_hpp__
#define __CosmoBit_types_hpp__

#include "gambit/Utils/util_types.hpp"
#include "gambit/Backends/backend_types/MontePythonLike.hpp"
#include <valarray>
#include <tuple>

#ifdef HAVE_PYBIND11
  #include <pybind11/stl.h>
#endif

namespace Gambit
{

  namespace CosmoBit
  {

    // Forward declaration of warnings and errors
    error& CosmoBit_error();
    warning& CosmoBit_warning();

    typedef std::map< str,std::valarray < double > > map_str_valarray_dbl;
    #ifdef HAVE_PYBIND11
      typedef std::tuple<pybind11::object, map_str_str, map_str_pyobj> MPLike_objects_container;
    #endif

    /// Class containing the primordial power spectrum.
    /// Members:
    /// - vector of modes k (1/Mpc)
    /// - scalar power spectrum of these modes P_s(k) (dimensionless)
    /// - tensor power spectrum of these modes P_t(k) (dimensionless)
    /// - scalar power spectrum of isocurvature modes P_s_iso(k) (dimensionless)
    class Primordial_ps
    {
        public:
            Primordial_ps() {};
            ~Primordial_ps() {};

            /// Fill k from an array of doubles
            void set_N_pivot(double npiv) { N_pivot = npiv; }
            void fill_k(double*, int);
            void fill_P_s(double*, int);
            void fill_P_s_iso(double*, int);
            void fill_P_t(double*, int);

            double get_N_pivot() { return N_pivot; }
            std::vector<double>& get_k() { return k; }
            std::vector<double>& get_P_s() { return P_s; }
            std::vector<double>& get_P_t() { return P_t; }
            std::vector<double>& get_P_s_iso() { return P_s_iso; }
            int get_vec_size() { return vec_size; }

        private:
            double N_pivot;
            std::vector<double> k;
            std::vector<double> P_s;
            std::vector<double> P_s_iso;
            std::vector<double> P_t;
            /// needed to pass vector length to CLASS; set in 'fill_k' method
            int vec_size;
    };

    /// Class containing the *parametrised* primordial power spectrum.
    /// Members:
    /// - spectral tilt n_s
    /// - amplitude of scalar perturbations A_s [as ln(10^{10}A_s)]
    /// - scalar to tensor ratio r
    class Parametrised_ps
    {
        public:
            Parametrised_ps() {};
            ~Parametrised_ps() {};

            void set_N_pivot(double npiv) { N_pivot = npiv; }
            void set_n_s(double ns) { n_s = ns; }
            void set_ln10A_s(double ln10As) { ln10A_s = ln10As; }
            void set_r(double rr) { r = rr; }

            double get_N_pivot() { return N_pivot; }
            double get_n_s() { return n_s; }
            double get_ln10A_s() { return ln10A_s; }
            double get_r() { return r; }

            /// return members as str to double map for printing
            map_str_dbl get_parametrised_ps_map();

        private:
            double N_pivot;
            double n_s;
            double ln10A_s;
            double r;
    };
  }
}

#endif // defined __CosmoBit_types_hpp__
