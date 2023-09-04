//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declaration of reader class for FlavBit YAML
///  database.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Marcin Chrzaszcz
///          (mchrzasz@cern.ch)
///  \date 2016 August
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Mar
///
///  *********************************************

#ifndef __Flav_reader_hpp__
#define __Flav_reader_hpp__

#include "yaml-cpp/yaml.h"
#include "gambit/FlavBit/FlavBit_types.hpp"
#include "gambit/Utils/util_types.hpp"

#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>


namespace Gambit
{

  namespace FlavBit
  {

    /// Reader class for FlavBit YAML database
    class Flav_reader
    {

      private:

        std::vector<Measurement> measurements;
        str measurement_location;
        bool use_P;
        bool use_S;
        bool debug;

        /// Find the second measurement that corresponds to a given correlation
        int get_measurement_for_corr(str);

        /// Check that a correlation matrix has 1s on the diagonal and is symmetric
        void check_corr_matrix(boost::numeric::ublas::matrix<double>&);

        /// Print a measurement previously read in from the database
        void print(Measurement);

        boost::numeric::ublas::matrix<double> M_measurements;
        boost::numeric::ublas::matrix<double> M_cor_cov;
        boost::numeric::ublas::matrix< std::pair<double, bool> > M_th_err;

      public:

        int number_measurements;

        /// Constructor that takes the location of the database as an argument
        Flav_reader(str loc);

        /// Read the entire database into memory
        void read_yaml(str name);

        /// Read a single measurement from the database into memory
        void read_yaml_measurement(str name, str measurement_name);

        /// Compute the covariance matrix and populate the measurement and theory error vectors
        void initialise_matrices();

        /// Print a boost ublas matrix
        void print_matrix(boost::numeric::ublas::matrix<double>&, str, bool is_true_matrix = true);

        /// Print a boost ublas matrix with a pair type
        void print_matrix(boost::numeric::ublas::matrix< std::pair<double, bool> >&, str, bool is_true_matrix = true);

        /// Set debug mode for reader
        void debug_mode(bool k) {debug = k;}

        /// Return the covariance matrix
        boost::numeric::ublas::matrix<double> get_exp_cov() {return M_cor_cov;};

        /// Return the experimental central values
        boost::numeric::ublas::matrix<double> get_exp_value() {return M_measurements;};

        /// Return the (uncorrelated) theory errors
        boost::numeric::ublas::matrix< std::pair<double,bool> > get_th_err() {return M_th_err;};

        /// Calculates the experimental statistical error from confidence levels
        static double get_error_from_confidence_levels(double, double, double, bool);

    };

  }

}

#endif //#defined __Flav_reader_hpp__
