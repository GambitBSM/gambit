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

#include <vector>
#include <map>
#include <string>

#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>

#include "gambit/Utils/ascii_table_reader.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/interp_collection.hpp"

namespace Gambit
{

  namespace Utils
  {

    // 
    // interp1d_collection class methods
    // 

    // Constructor
    interp1d_collection::interp1d_collection(const std::string collection_name_in, const std::string file_name_in, const std::vector<std::string> colnames_in)
    {
      // Check if file exists.
      if (not(Utils::file_exists(file_name_in)))
      {
        utils_error().raise(LOCAL_INFO, "ERROR! File '" + file_name_in + "' not found!");
      }

      // Read numerical values from data file.
      ASCIItableReader tab(file_name_in);

      // Check that there's more than one column
      if (tab.getncol() < 2)
      {
        utils_error().raise(LOCAL_INFO, "ERROR! Less than two columns found in the input file '" + file_name_in + "'."); 
      }

      // Check that the number of columns matches the number of column names
      if (colnames_in.size() != (size_t) tab.getncol())
      {
        utils_error().raise(LOCAL_INFO, "ERROR! Mismatch between number of columns and number of column names."); 
      }

      // Set the column names
      tab.setcolnames(colnames_in);

      // Save some names
      collection_name = collection_name_in;
      file_name = file_name_in;
      x_name = colnames_in.at(0);
      interpolator_names = {colnames_in.begin() + 1, colnames_in.end()};

      // Number of interpolators
      n_interpolators = interpolator_names.size();

      // 
      // Create one GSL spline for each interpolator
      // 
      std::vector<double> x_data = tab[x_name];
      int nx = x_data.size();

      // Get first and last value of the "x" component.
      x_min = x_data.front();
      x_max = x_data.back();

      for (size_t interp_index = 0; interp_index < n_interpolators; ++interp_index)
      {
        std::string interp_name = interpolator_names[interp_index];
        std::vector<double> interp_data = tab[interp_name];

        int n_points = interp_data.size();
        if (nx != n_points)
        {
          utils_error().raise(LOCAL_INFO, "ERROR! The number of data points ("+std::to_string(n_points)+") does not agree with the number of 'x' points ("+std::to_string(nx)+") for the interpolator '"+interp_name+"'.\n Check formatting of the file: '"+file_name_in+"'.");
        }

        // Initialize a gsl_spline pointer and a gsl_interp_accel pointer and store them
        gsl_interp_accel* acc = gsl_interp_accel_alloc();
        x_accels.push_back(acc);

        gsl_spline* sp = gsl_spline_alloc(gsl_interp_linear, nx);  // For now only using linear interpolation
        gsl_spline_init(sp, &x_data[0], &interp_data[0], nx);
        splines.push_back(sp);
      }
    }

    // Destructor
    interp1d_collection::~interp1d_collection()
    {
      for (size_t interp_index = 0; interp_index < n_interpolators; ++interp_index)
      {
        gsl_spline_free(splines[interp_index]);
        gsl_interp_accel_free(x_accels[interp_index]);
      }
    }

    // Evaluate a given interpolation
    double interp1d_collection::eval(double x, size_t interp_index) const
    {
      return gsl_spline_eval(splines[interp_index], x, x_accels[interp_index]);
    }
    
    // If there is only one interpolator, we can evaluate it without specifying the index
    double interp1d_collection::eval(double x) const
    {
      if (n_interpolators != 1)
      {
          utils_error().raise(LOCAL_INFO, "ERROR! This interp1d_collection instance contains more than one interpolator, so the interpolator index must be specified.");
      }
      return eval(x, 0);
    }

    // Check if point is inside interpolation range
    bool interp1d_collection::is_inside_range(double x) const
    {
      return ((x >= x_min) && (x <= x_max));
    }



    // 
    // interp2d_collection class methods
    // 

    // Constructor
    interp2d_collection::interp2d_collection(const std::string collection_name_in, const std::string file_name_in, const std::vector<std::string> colnames_in)
    {
      // Check if file exists.
      if (not(Utils::file_exists(file_name_in)))
      {
        utils_error().raise(LOCAL_INFO, "ERROR! File '" + file_name_in + "' not found!");
      }

      // Read numerical values from data file.
      ASCIItableReader tab(file_name_in);

      // Check that there's more than two columns
      if (tab.getncol() < 3)
      {
        utils_error().raise(LOCAL_INFO, "ERROR! Less than three columns found in the input file '" + file_name_in + "'."); 
      }

      // Check that the number of columns matches the number of column names
      if (colnames_in.size() != (size_t) tab.getncol())
      {
        utils_error().raise(LOCAL_INFO, "ERROR! Mismatch between number of columns and number of column names."); 
      }

      // Set the column names
      tab.setcolnames(colnames_in);

      // Save some names
      collection_name = collection_name_in;
      file_name = file_name_in;
      x_name = colnames_in.at(0);
      y_name = colnames_in.at(1);
      interpolator_names = {colnames_in.begin() + 2, colnames_in.end()};

      // Number of interpolators
      n_interpolators = interpolator_names.size();

      // 
      // Create one GSL spline for each interpolator
      // 

      // Get unique entries of "x" and "y" for the grid and grid size.
      std::vector<double> x_vec = tab[x_name];
      sort(x_vec.begin(), x_vec.end());
      x_vec.erase(unique(x_vec.begin(), x_vec.end()), x_vec.end());
      int nx = x_vec.size();
      x_min = x_vec.front();
      x_max = x_vec.back();

      std::vector<double> y_vec = tab[y_name];
      sort(y_vec.begin(), y_vec.end());
      y_vec.erase(unique(y_vec.begin(), y_vec.end()), y_vec.end());
      int ny = y_vec.size();
      y_min = y_vec.front();
      y_max = y_vec.back();

      for (size_t interp_index = 0; interp_index < n_interpolators; ++interp_index)
      {
        std::string interp_name = interpolator_names[interp_index];
        std::vector<double> interp_data = tab[interp_name];

        int n_points = interp_data.size();

        if (nx * ny != n_points)
        {
          utils_error().raise(LOCAL_INFO, "ERROR! The number of grid points ("+std::to_string(n_points)+") does not agree with the number of unique 'x' and 'y' values ("+std::to_string(nx)+" and "+std::to_string(ny)+") for the interpolator '"+interp_name+"'.\n Check formatting of the file: '"+file_name_in+"'.");
        }

        // Initialize a gsl_spline pointer and two gsl_interp_accel pointers and store them
        gsl_interp_accel* x_acc = gsl_interp_accel_alloc();
        x_accels.push_back(x_acc);
        gsl_interp_accel* y_acc = gsl_interp_accel_alloc();
        y_accels.push_back(y_acc);

        gsl_spline2d* sp = gsl_spline2d_alloc(gsl_interp2d_bilinear, nx, ny);
        gsl_spline2d_init(sp, &x_vec[0], &y_vec[0], &interp_data[0], nx, ny);
        splines.push_back(sp);
      }
    }

    // Destructor
    interp2d_collection::~interp2d_collection()
    {
      for (size_t interp_index = 0; interp_index < n_interpolators; ++interp_index)
      {
        gsl_spline2d_free(splines[interp_index]);
        gsl_interp_accel_free(x_accels[interp_index]);
        gsl_interp_accel_free(y_accels[interp_index]);
      }
    }

    // Evaluate a given interpolation
    double interp2d_collection::eval(double x, double y, size_t interp_index) const
    {
      return gsl_spline2d_eval(splines[interp_index], x, y, x_accels[interp_index], y_accels[interp_index]);
    }
    
    // If there is only one interpolator, we can evaluate it without specifying the index
    double interp2d_collection::eval(double x, double y) const
    {
      if (n_interpolators != 1)
      {
          utils_error().raise(LOCAL_INFO, "ERROR! This interp2d_collection instance contains more than one interpolator, so the interpolator index must be specified.");
      }
      return eval(x, y, 0);
    }

    // Check if point is inside interpolation range
    bool interp2d_collection::is_inside_range(double x, double y) const
    {
      return ((x >= x_min) && (x <= x_max) && (y >= y_min) && (y <= y_max));
    }


  }
}
