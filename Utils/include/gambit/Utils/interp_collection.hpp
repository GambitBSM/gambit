//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Utils classes for holding a 
///  collection of 1D/2D interpolators.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2021 Sep
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
    class interp1d_collection
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
        interp1d_collection(const std::string, const std::string, const std::vector<std::string>);

        // Destructor
        ~interp1d_collection();

        // Evaluate a given interpolation
        double eval(double, size_t) const;
        
        // If there is only one interpolator, we can evaluate it without specifying the index
        double eval(double) const;

        // Check if point is inside interpolation range
        bool is_inside_range(double) const;
    };


    /// A class for holding a collection of 2D interpolators, created from reading a tabulated ascii file. 
    /// - The first two columns are taken to be the x and y grid points. 
    /// - For each remaining column a 2D interpolation function f(x,y) is created
    /// - Note that GLS assumes the points are ordered according to increasing x (first) and y (second) values, 
    ///   i.e. an ordering like (x0,y0), (x1,y0), (x2,y0), ... (x0,y1), (x1,y1), (x2,y1), ...
    ///
    class interp2d_collection
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
        interp2d_collection(const std::string, const std::string, const std::vector<std::string>);

        // Destructor
        ~interp2d_collection();

        // Evaluate a given interpolation
        double eval(double, double, size_t) const;
        
        // If there is only one interpolator, we can evaluate it without specifying the index
        double eval(double, double) const;

        // Check if point is inside interpolation range
        bool is_inside_range(double, double) const;

    };


  }
}

#endif //defined __interp_collection_hpp__
