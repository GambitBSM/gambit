//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Utils classes for holding a 
///  collection of interpolators.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2021 Sep
///
///  \author Chris Chang
///          (christopher.chang@uq.net.au)
///  \date 2022 Jun
///
///  *********************************************


#ifndef __interp_collection_hpp__
#define __interp_collection_hpp__

#include <vector>
#include <string>

#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>

namespace Gambit
{

  namespace Utils
  {

    /// A class for holding a collection of 1D interpolators, created from reading a tabulated ascii file. 
    /// - The first column is taken as the x value. 
    /// - For each remaining column a 1D interpolation function f(x) is created
    class interp1d_gsl_collection
    {
      public:

        // Member variables
        std::string collection_name;
        std::string file_name;
        std::string x_name;
        std::vector<std::string> interpolator_names;

        std::vector<gsl_spline*> splines;
        std::vector<gsl_interp_accel*> x_accels;

        double x_min;
        double x_max;
        size_t n_interpolators;


        // Class methods

        // Constructor
        interp1d_gsl_collection(const std::string, const std::string, const std::vector<std::string>);

        // Destructor
        ~interp1d_gsl_collection();

        // Evaluate a given interpolation
        double eval(double, size_t) const;

        // If there is only one interpolator, we can evaluate it without specifying the index
        double eval(double) const;

        // Check if point is inside interpolation range
        bool is_inside_range(double) const;
    };


    /// A class for holding a collection of 1D interpolators, created from reading a tabulated ascii file. 
    /// - The first column is taken as the x value. 
    /// - For each remaining column a 1D interpolation function f(x) is created
    /// - This is a simple linear interpolator that does not use GSL
    class interp1d_collection
    {
      public:

        // Member variables
        std::string collection_name;
        std::string file_name;
        std::string x1_name;
        std::vector<std::string> interpolator_names;

        std::vector<double> x1_vec;
        std::vector<double> x1_vec_unsorted;

        std::vector<std::vector<double>> interp_data;

        double x1_min;
        double x1_max;

        size_t n_interpolators;

        // Class methods

        // Constructor
        interp1d_collection(const std::string, const std::string, const std::vector<std::string>);

        // Destructor
        ~interp1d_collection();

        // Evaluate a given interpolation
        double eval(double, size_t);

        // Check if point is inside interpolation range
        bool is_inside_range(double);

    };


    /// A class for holding a collection of 2D interpolators, created from reading a tabulated ascii file. 
    /// - The first two columns are taken to be the x and y grid points. 
    /// - For each remaining column a 2D interpolation function f(x,y) is created
    /// - Note that GLS assumes the points are ordered according to increasing x (first) and y (second) values, 
    ///   i.e. an ordering like (x0,y0), (x1,y0), (x2,y0), ... (x0,y1), (x1,y1), (x2,y1), ...
    ///
    class interp2d_gsl_collection
    {
      public:

        // Member variables
        std::string collection_name;
        std::string file_name;
        std::string x_name;
        std::string y_name;
        std::vector<std::string> interpolator_names;

        std::vector<gsl_spline2d*> splines;
        std::vector<gsl_interp_accel*> x_accels;
        std::vector<gsl_interp_accel*> y_accels;

        double x_min;
        double x_max;
        double y_min;
        double y_max;

        size_t n_interpolators;


        // Class methods

        // Constructor
        interp2d_gsl_collection(const std::string, const std::string, const std::vector<std::string>);

        // Destructor
        ~interp2d_gsl_collection();

        // Evaluate a given interpolation
        double eval(double, double, size_t) const;

        // If there is only one interpolator, we can evaluate it without specifying the index
        double eval(double, double) const;

        // Check if point is inside interpolation range
        bool is_inside_range(double, double) const;

    };


    /// A class for holding a collection of 2D interpolators, created from reading a tabulated ascii file. 
    /// - The first two columns are taken to be the x and y grid points. 
    /// - For each remaining column a 2D interpolation function f(x,y) is created
    /// - This is a simple linear interpolator that does not use GSL
    class interp2d_collection
    {
      public:

        // Member variables
        std::string collection_name;
        std::string file_name;
        std::string x1_name;
        std::string x2_name;
        std::vector<std::string> interpolator_names;

        std::vector<double> x1_vec;
        std::vector<double> x2_vec;
        std::vector<double> x1_vec_unsorted;
        std::vector<double> x2_vec_unsorted;

        std::vector<std::vector<double>> interp_data;

        double x1_min;
        double x1_max;
        double x2_min;
        double x2_max;

        size_t n_interpolators;

        // Class methods

        // Constructor
        interp2d_collection(const std::string, const std::string, const std::vector<std::string>);

        // Destructor
        ~interp2d_collection();

        // Evaluate a given interpolation
        double eval(double, double, size_t);

        // Check if point is inside interpolation range
        bool is_inside_range(double, double);

    };


    /// A class for holding a collection of 4D interpolators, created from reading a tabulated ascii file. 
    /// - The first 4 columns are taken to be the x1,x2,x3,x4 grid points. 
    /// - A series of 1D interpolations is performed repeatedly to form the result.
    class interp4d_collection
    {
      public:

        // Member variables
        std::string collection_name;
        std::string file_name;
        std::string x1_name;
        std::string x2_name;
        std::string x3_name;
        std::string x4_name;
        std::vector<std::string> interpolator_names;

        // Stored values
        std::vector<double> x1_vec;
        std::vector<double> x2_vec;
        std::vector<double> x3_vec;
        std::vector<double> x4_vec;
        std::vector<double> x1_vec_unsorted;
        std::vector<double> x2_vec_unsorted;
        std::vector<double> x3_vec_unsorted;
        std::vector<double> x4_vec_unsorted;

        std::vector<std::vector<double>> interp_data;

        double x1_min;
        double x1_max;
        double x2_min;
        double x2_max;
        double x3_min;
        double x3_max;
        double x4_min;
        double x4_max;

        size_t n_interpolators;

        bool allow_missing_pts;
        double missing_point_val;

        // Class methods

        // Constructor
        interp4d_collection(const std::string, const std::string, const std::vector<std::string>, bool, double);

        // Destructor
        ~interp4d_collection();

        // Simple linear 1D interpolation
        double linearinterp1D(double x1, double x2, double y1, double y2, double xtest);

        // Evaluate a given interpolation
        double eval(double, double, double, double, size_t);

        // Check if point is inside interpolation range
        bool is_inside_range(double, double, double, double);
    };


    /// A class for holding a collection of 5D interpolators, created from reading a tabulated ascii file. 
    /// - The first 5 columns are taken to be the x1,x2,x3,x4,x5 grid points. 
    /// - A series of 1D linear interpolations are performed repeatedly to form the result.
    class interp5d_collection
    {
      public:

        // Member variables
        std::string collection_name;
        std::string file_name;
        std::string x1_name;
        std::string x2_name;
        std::string x3_name;
        std::string x4_name;
        std::string x5_name;
        std::vector<std::string> interpolator_names;

        // Stored values
        std::vector<double> x1_vec;
        std::vector<double> x2_vec;
        std::vector<double> x3_vec;
        std::vector<double> x4_vec;
        std::vector<double> x5_vec;
        std::vector<double> x1_vec_unsorted;
        std::vector<double> x2_vec_unsorted;
        std::vector<double> x3_vec_unsorted;
        std::vector<double> x4_vec_unsorted;
        std::vector<double> x5_vec_unsorted;

        std::vector<std::vector<double>> interp_data;

        double x1_min;
        double x1_max;
        double x2_min;
        double x2_max;
        double x3_min;
        double x3_max;
        double x4_min;
        double x4_max;
        double x5_min;
        double x5_max;

        size_t n_interpolators;

        bool allow_missing_pts;
        double missing_point_val;

        // Class methods

        // Constructor
        interp5d_collection(const std::string, const std::string, const std::vector<std::string>, bool, double);

        // Destructor
        ~interp5d_collection();

        // Simple linear 1D interpolation
        double linearinterp1D(double x1, double x2, double y1, double y2, double xtest);

        // Evaluate a given interpolation
        double eval(double, double, double, double, double, size_t);

        // Check if point is inside interpolation range
        bool is_inside_range(double, double,double,double,double);

    };

  }
}

#endif //defined __interp_collection_hpp__
