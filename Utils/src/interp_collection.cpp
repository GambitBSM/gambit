//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Utils classes for holding a 
///  collection of 1D/2D gsl interpolators and
///  1D/2D/4D/5D linear interpolators.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2021 Sep
///
///  \author Christopher Chang
///          (christopher.chang@uq.net.au)
///  \date 2022 June
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
    // interp1d_gsl_collection class methods
    // 

    // Constructor
    interp1d_gsl_collection::interp1d_gsl_collection(const std::string collection_name_in, const std::string file_name_in, const std::vector<std::string> colnames_in)
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
    interp1d_gsl_collection::~interp1d_gsl_collection()
    {
      for (size_t interp_index = 0; interp_index < n_interpolators; ++interp_index)
      {
        gsl_spline_free(splines[interp_index]);
        gsl_interp_accel_free(x_accels[interp_index]);
      }
    }

    // Evaluate a given interpolation
    double interp1d_gsl_collection::eval(double x, size_t interp_index) const
    {
      return gsl_spline_eval(splines[interp_index], x, x_accels[interp_index]);
    }

    // If there is only one interpolator, we can evaluate it without specifying the index
    double interp1d_gsl_collection::eval(double x) const
    {
      if (n_interpolators != 1)
      {
          utils_error().raise(LOCAL_INFO, "ERROR! This interp1d_gsl_collection instance contains more than one interpolator, so the interpolator index must be specified.");
      }
      return eval(x, 0);
    }

    // Check if point is inside interpolation range
    bool interp1d_gsl_collection::is_inside_range(double x) const
    {
      return ((x >= x_min) && (x <= x_max));
    }


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

      // Check that there's more than one columns
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
      x1_name = colnames_in.at(0);
      interpolator_names = {colnames_in.begin() + 1, colnames_in.end()};

      // Number of interpolators
      n_interpolators = interpolator_names.size();

      // Get unique entries of "xi" for the grid and grid size.
      x1_vec = tab[x1_name];
      x1_vec_unsorted = tab[x1_name];
      sort(x1_vec.begin(), x1_vec.end());
      x1_vec.erase(unique(x1_vec.begin(), x1_vec.end()), x1_vec.end());
      int nx1 = x1_vec.size();
      x1_min = x1_vec.front();
      x1_max = x1_vec.back();

      for (size_t interp_index = 0; interp_index < n_interpolators; ++interp_index)
      {
        // Store the interpolation data to be used later
        std::string interp_name = interpolator_names[interp_index];

        int n_points = (tab[interp_name]).size();

        if (nx1 != n_points)
        {
          utils_error().raise(LOCAL_INFO, "ERROR! The number of grid points ("+std::to_string(n_points)+") does not agree with the number of unique 'x' values ("+std::to_string(nx1)+") for the interpolator '"+interp_name+"'.\n Check formatting of the file: '"+file_name_in+"'.");
        }

        interp_data.push_back(tab[interp_name]);
      }
    }

    // Destructor
    interp1d_collection::~interp1d_collection() {}

    // Evaluate a given interpolation
    double interp1d_collection::eval(double x1, size_t interp_index)
    {
      std::vector<double> fi_values = interp_data[interp_index];

      // Determine upper and lower bounds
      double xi_upper[] = {0.0};
      double xi_lower[] = {0.0};
      bool x1_equal = false;

      for (size_t i=0;i<(x1_vec.size());i++)
      {
        // In case of exact match
        if (x1 == x1_vec[i])
        {
          xi_lower[0] = x1_vec[i];
          xi_upper[0] = x1_vec[i];
          x1_equal = true;
        }
        // Otherwise bounds as normal
        if (x1 > x1_vec[i] && x1 < x1_vec[i+1])
        {
          xi_lower[0] = x1_vec[i];
          xi_upper[0] = x1_vec[i+1];
        }
        // End early if you have found all of the bounds
        if (x1 < x1_vec[i] ) break;
      }

      // Find the corresponding function values
      std::vector<double> fi = {-1.0,-1.0};
      bool test_u[] = {false};
      bool test_l[] = {false};

      //Loop over all interp_data, and match value to coresponding value. 
      for (size_t k=0;k<fi_values.size();k++)
      {
        // Reset Values
        test_u[0] = false; test_u[1] = false;
        test_l[0] = false; test_l[1] = false;

        // Check whether the values correspond to any of the upper/lower values. skip calculation if not...
        if (x1_vec_unsorted[k]==xi_upper[0]) { test_u[0]=true;}
        else if (x1_vec_unsorted[k]==xi_lower[0]) { test_l[0]=true;}
        else continue;

        // Set the values of fi in the correct order
        if (test_l[0]) {fi[0] = fi_values[k];}
        if (test_u[0]) {fi[1] = fi_values[k];}
      }

      // Perform Calculation taking care for exact cases
      double Y_interp;
      if (x1_equal)
      {
        Y_interp = fi[0];
      } else {
        Y_interp = (xi_upper[0] - x1) / (xi_upper[0] - xi_lower[0]) * (fi[1]-fi[0]);
      }

      return Y_interp;
    }

    // Check if point is inside interpolation range
    bool interp1d_collection::is_inside_range(double x1)
    {
      return ((x1 >= x1_min) && (x1 <= x1_max));
    }


    // 
    // interp2d_gsl_collection class methods
    // 

    // Constructor
    interp2d_gsl_collection::interp2d_gsl_collection(const std::string collection_name_in, const std::string file_name_in, const std::vector<std::string> colnames_in)
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
    interp2d_gsl_collection::~interp2d_gsl_collection()
    {
      for (size_t interp_index = 0; interp_index < n_interpolators; ++interp_index)
      {
        gsl_spline2d_free(splines[interp_index]);
        gsl_interp_accel_free(x_accels[interp_index]);
        gsl_interp_accel_free(y_accels[interp_index]);
      }
    }

    // Evaluate a given interpolation
    double interp2d_gsl_collection::eval(double x, double y, size_t interp_index) const
    {
      return gsl_spline2d_eval(splines[interp_index], x, y, x_accels[interp_index], y_accels[interp_index]);
    }

    // If there is only one interpolator, we can evaluate it without specifying the index
    double interp2d_gsl_collection::eval(double x, double y) const
    {
      if (n_interpolators != 1)
      {
          utils_error().raise(LOCAL_INFO, "ERROR! This interp2d_gsl_collection instance contains more than one interpolator, so the interpolator index must be specified.");
      }
      return eval(x, y, 0);
    }

    // Check if point is inside interpolation range
    bool interp2d_gsl_collection::is_inside_range(double x, double y) const
    {
      return ((x >= x_min) && (x <= x_max) && (y >= y_min) && (y <= y_max));
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
      x1_name = colnames_in.at(0);
      x2_name = colnames_in.at(1);
      interpolator_names = {colnames_in.begin() + 2, colnames_in.end()};

      // Number of interpolators
      n_interpolators = interpolator_names.size();

      // Get unique entries of "xi" for the grid and grid size.
      x1_vec = tab[x1_name];
      x1_vec_unsorted = tab[x1_name];
      sort(x1_vec.begin(), x1_vec.end());
      x1_vec.erase(unique(x1_vec.begin(), x1_vec.end()), x1_vec.end());
      int nx1 = x1_vec.size();
      x1_min = x1_vec.front();
      x1_max = x1_vec.back();

      x2_vec = tab[x2_name];
      x2_vec_unsorted = tab[x2_name];
      sort(x2_vec.begin(), x2_vec.end());
      x2_vec.erase(unique(x2_vec.begin(), x2_vec.end()), x2_vec.end());
      int nx2 = x2_vec.size();
      x2_min = x2_vec.front();
      x2_max = x2_vec.back();

      for (size_t interp_index = 0; interp_index < n_interpolators; ++interp_index)
      {
        // Store the interpolation data to be used later
        std::string interp_name = interpolator_names[interp_index];

        int n_points = (tab[interp_name]).size();

        if (nx1 * nx2 != n_points)
        {
          utils_error().raise(LOCAL_INFO, "ERROR! The number of grid points ("+std::to_string(n_points)+") does not agree with the number of unique 'x' and 'y' values ("+std::to_string(nx1)+" and "+std::to_string(nx2)+") for the interpolator '"+interp_name+"'.\n Check formatting of the file: '"+file_name_in+"'.");
        }

        interp_data.push_back(tab[interp_name]);
      }
    }

    // Destructor
    interp2d_collection::~interp2d_collection() {}

    // Evaluate a given interpolation
    double interp2d_collection::eval(double x1,double x2, size_t interp_index)
    {
      std::vector<double> fi_values = interp_data[interp_index];

      // Determine upper and lower bounds
      double xi_upper[] = {0.0,0.0};
      double xi_lower[] = {0.0,0.0};
      bool x1_equal = false;
      bool x2_equal = false;

      for (size_t i=0;i<(x1_vec.size());i++)
      {
        // In case of exact match
        if (x1 == x1_vec[i])
        {
          xi_lower[0] = x1_vec[i];
          xi_upper[0] = x1_vec[i];
          x1_equal = true;
        }
        // Otherwise bounds as normal
        if (x1 > x1_vec[i] && x1 < x1_vec[i+1])
        {
          xi_lower[0] = x1_vec[i];
          xi_upper[0] = x1_vec[i+1];
        }
        // End early if you have found all of the bounds
        if (x1 < x1_vec[i] ) break;
      }

      for (size_t i=0;i<(x2_vec.size());i++)
      {
        // In case of exact match
        if (x2 == x2_vec[i])
        {
          xi_lower[1] = x2_vec[i];
          xi_upper[1] = x2_vec[i];
          x2_equal = true;
        }
        // Otherwise bounds as normal
        if (x2 > x2_vec[i] && x2 < x2_vec[i+1])
        {
          xi_lower[1] = x2_vec[i];
          xi_upper[1] = x2_vec[i+1];
        }
        
        if (x2 < x2_vec[i]) break;
      }

      // Find the corresponding function values
      std::vector<double> fi = {-1.0,-1.0,-1.0,-1.0};
      bool test_u[] = {false,false};
      bool test_l[] = {false,false};

      //Loop over all interp_data, and match value to coresponding value. 
      for (size_t k=0;k<fi_values.size();k++)
      {
        // Reset Values
        test_u[0] = false; test_u[1] = false;
        test_l[0] = false; test_l[1] = false;

        // Check whether the values correspond to any of the upper/lower values. skip calculation if not...
        if (x1_vec_unsorted[k]==xi_upper[0]) { test_u[0]=true;}
        else if (x1_vec_unsorted[k]==xi_lower[0]) { test_l[0]=true;}
        else continue;

        if (x2_vec_unsorted[k]==xi_upper[1]) { test_u[1]=true;}
        else if (x2_vec_unsorted[k]==xi_lower[1]) { test_l[1]=true;}
        else continue;

        // Set the values of fi in the correct order
        if (test_l[0] && test_l[1] ) {fi[0] = fi_values[k];}
        if (test_u[0] && test_l[1] ) {fi[1] = fi_values[k];}
        if (test_l[0] && test_u[1] ) {fi[2] = fi_values[k];}
        if (test_u[0] && test_u[1] ) {fi[3] = fi_values[k];}
      }

      // Perform Calculation taking care for exact cases
      double Y_interp;
      double y_U;
      double y_L;
      if (x1_equal && !x2_equal)
      {
        fi[0] = fi[1];
        fi[2] = fi[3];

        y_L = fi[0];
        y_U = fi[2];
        Y_interp = y_U - (y_U-y_L) * (xi_upper[1] - x2) / (xi_upper[1] - xi_lower[1]);
      } else if (!x1_equal && x2_equal) {
        fi[0] = fi[2];
        fi[1] = fi[3];
        Y_interp = fi[1] - (fi[1]-fi[0]) * (xi_upper[0] - x1) / (xi_upper[0] - xi_lower[0]);
      } else if (x1_equal && x2_equal) {
        Y_interp = fi[0];
      } else {
        y_L = fi[1] - (fi[1]-fi[0]) * (xi_upper[0] - x1) / (xi_upper[0] - xi_lower[0]);
        y_U = fi[3] - (fi[3]-fi[2]) * (xi_upper[0] - x1) / (xi_upper[0] - xi_lower[0]);
        Y_interp = y_U - (y_U-y_L) * (xi_upper[1] - x2) / (xi_upper[1] - xi_lower[1]);
      }

      return Y_interp;
    }

    // Check if point is inside interpolation range
    bool interp2d_collection::is_inside_range(double x1,double x2)
    {
      return ((x1 >= x1_min) && (x1 <= x1_max) && (x2 >= x2_min) && (x2 <= x2_max));
    }


    // 
    // interp4d_collection class methods
    // 

    // Constructor
    interp4d_collection::interp4d_collection(const std::string collection_name_in, const std::string file_name_in, const std::vector<std::string> colnames_in, bool allow_missing_points, double missing_pts_val)
    {
      // Check if file exists.
      if (not(Utils::file_exists(file_name_in)))
      {
        utils_error().raise(LOCAL_INFO, "ERROR! File '" + file_name_in + "' not found!");
      }

      // Read numerical values from data file.
      ASCIItableReader tab(file_name_in);

      // Check that there's more than 4 columns
      if (tab.getncol() < 5)
      {
        utils_error().raise(LOCAL_INFO, "ERROR! Less than five columns found in the input file '" + file_name_in + "'.");
      }

      // Check that the number of columns matches the number of column names
      if (colnames_in.size() != (size_t) tab.getncol())
      {
        utils_error().raise(LOCAL_INFO, "ERROR! Mismatch between number of columns and number of column names.");
      }

      // Set whether to allow missing points in the interpolation grid
      allow_missing_pts = allow_missing_points;
      missing_point_val = missing_pts_val;

      // Set the column names
      tab.setcolnames(colnames_in);

      // Save some names
      collection_name = collection_name_in;
      file_name = file_name_in;
      x1_name = colnames_in.at(0);
      x2_name = colnames_in.at(1);
      x3_name = colnames_in.at(2);
      x4_name = colnames_in.at(3);
      interpolator_names = {colnames_in.begin() + 4, colnames_in.end()};

      // Number of interpolators
      n_interpolators = interpolator_names.size();

      // Get unique entries of "xi" for the grid and grid size.
      x1_vec = tab[x1_name];
      x1_vec_unsorted = tab[x1_name];
      sort(x1_vec.begin(), x1_vec.end());
      x1_vec.erase(unique(x1_vec.begin(), x1_vec.end()), x1_vec.end());
      int nx1 = x1_vec.size();
      x1_min = x1_vec.front();
      x1_max = x1_vec.back();

      x2_vec = tab[x2_name];
      x2_vec_unsorted = tab[x2_name];
      sort(x2_vec.begin(), x2_vec.end());
      x2_vec.erase(unique(x2_vec.begin(), x2_vec.end()), x2_vec.end());
      int nx2 = x2_vec.size();
      x2_min = x2_vec.front();
      x2_max = x2_vec.back();

      x3_vec = tab[x3_name];
      x3_vec_unsorted = tab[x3_name];
      sort(x3_vec.begin(), x3_vec.end());
      x3_vec.erase(unique(x3_vec.begin(), x3_vec.end()), x3_vec.end());
      int nx3 = x3_vec.size();
      x3_min = x3_vec.front();
      x3_max = x3_vec.back();

      x4_vec = tab[x4_name];
      x4_vec_unsorted = tab[x4_name];
      sort(x4_vec.begin(), x4_vec.end());
      x4_vec.erase(unique(x4_vec.begin(), x4_vec.end()), x4_vec.end());
      int nx4 = x4_vec.size();
      x4_min = x4_vec.front();
      x4_max = x4_vec.back();

      // Store the interpolation data to be used later
      for (size_t interp_index = 0; interp_index < n_interpolators; ++interp_index)
      {
        std::string interp_name = interpolator_names[interp_index];

        int n_points = (tab[interp_name]).size();

        if (!allow_missing_pts && (nx1 * nx2 * nx3 * nx4 != n_points))
        {
          utils_error().raise(LOCAL_INFO, "ERROR! The number of grid points ("+std::to_string(n_points)+") does not agree with the number of unique 'x' and 'y' values ("+std::to_string(nx1)+" and "+std::to_string(nx2)+") for the interpolator '"+interp_name+"'.\n Check formatting of the file: '"+file_name_in+"'. This could be the case if the interpolation grid is missing points.");
        }

        interp_data.push_back(tab[interp_name]);
      }
    }

    // Destructor
    interp4d_collection::~interp4d_collection() {}

    // Just some forward declarations...
    void InterpIter(int Ntemp,double xi_1,double xi_2,std::vector<double>& fi,double test);

    // Evaluate a given interpolation
    double interp4d_collection::eval(double x1,double x2,double x3,double x4, size_t interp_index)
    {
      double xi[] = {x1,x2,x3,x4};
      std::vector<double> fi_values = interp_data[interp_index];

      // Determine upper and lower bounds
      double xi_upper[] = {0.0,0.0,0.0,0.0};
      double xi_lower[] = {0.0,0.0,0.0,0.0};

      // Determine edges (-1 to make sure it doesn't run over the last element)
      for (size_t i=0;i<(x1_vec.size());i++)
      {
        // // In case of exact match
        if (x1 == x1_vec[i])
        {
          xi_lower[0] = x1_vec[i];
          xi_upper[0] = x1_vec[i];
        }
        // Otherwise bounds as normal
        if (x1 > x1_vec[i] && x1 < x1_vec[i+1])
        {
          xi_lower[0] = x1_vec[i];
          xi_upper[0] = x1_vec[i+1];
        }
        // End early if you have found all of the bounds
        if (x1 < x1_vec[i] ) break;
      }

      for (size_t i=0;i<(x2_vec.size());i++)
      {
        if (x2 == x2_vec[i])
        {
          xi_lower[1] = x2_vec[i];
          xi_upper[1] = x2_vec[i];
        }
        if (x2 > x2_vec[i] && x2 < x2_vec[i+1])
        {
          xi_lower[1] = x2_vec[i];
          xi_upper[1] = x2_vec[i+1];
        }
        if (x2 < x2_vec[i]) break;
      }

      for (size_t i=0;i<(x3_vec.size());i++)
      {
        if (x3 == x3_vec[i])
        {
          xi_lower[2] = x3_vec[i];
          xi_upper[2] = x3_vec[i];
        }
        if (x3 > x3_vec[i] && x3 < x3_vec[i+1])
        {
          xi_lower[2] = x3_vec[i];
          xi_upper[2] = x3_vec[i+1];
        }
        if (x3 < x3_vec[i]) break;
      }

      for (size_t i=0;i<(x4_vec.size());i++)
      {
        if (x4 == x4_vec[i])
        {
          xi_lower[3] = x4_vec[i];
          xi_upper[3] = x4_vec[i];
        }
        if (x4 > x4_vec[i] && x4 < x4_vec[i+1])
        {
          xi_lower[3] = x4_vec[i];
          xi_upper[3] = x4_vec[i+1];
        }
        if (x4 < x4_vec[i]) break;
      }

      // Find the corresponding function values
      // Using a default value of -1 as this is assumed not a valid result
      std::vector<double> fi = {-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0};
      bool test_u[] = {false,false,false,false};
      bool test_l[] = {false,false,false,false};

      //Loop over all interp_data, and match value to coresponding value. 
      for (size_t k=0;k<fi_values.size();k++)
      {
        // Reset Values
        test_u[0] = false; test_u[1] = false; test_u[2] = false; test_u[3] = false;
        test_l[0] = false; test_l[1] = false; test_l[2] = false; test_l[3] = false;

        // Check whether the values correspond to any of the upper/lower values. skip calculation if not...
        if (x1_vec_unsorted[k]==xi_upper[0]) { test_u[0]=true;}
        if (x1_vec_unsorted[k]==xi_lower[0]) { test_l[0]=true;}
        if (test_u[0]==false && test_l[0]==false) continue;

        if (x2_vec_unsorted[k]==xi_upper[1]) { test_u[1]=true;}
        if (x2_vec_unsorted[k]==xi_lower[1]) { test_l[1]=true;}
        if (test_u[1]==false && test_l[1]==false) continue;

        if (x3_vec_unsorted[k]==xi_upper[2]) { test_u[2]=true;}
        if (x3_vec_unsorted[k]==xi_lower[2]) { test_l[2]=true;}
        if (test_u[2]==false && test_l[2]==false) continue;

        if (x4_vec_unsorted[k]==xi_upper[3]) { test_u[3]=true;}
        if (x4_vec_unsorted[k]==xi_lower[3]) { test_l[3]=true;}
        if (test_u[3]==false && test_l[3]==false) continue;

        // Set the values of fi in the correct order
        if (test_l[0] && test_l[1] && test_l[2] && test_l[3]) {fi[0] = fi_values[k];}
        if (test_u[0] && test_l[1] && test_l[2] && test_l[3]) {fi[1] = fi_values[k];}
        if (test_l[0] && test_u[1] && test_l[2] && test_l[3]) {fi[2] = fi_values[k];}
        if (test_u[0] && test_u[1] && test_l[2] && test_l[3]) {fi[3] = fi_values[k];}
        if (test_l[0] && test_l[1] && test_u[2] && test_l[3]) {fi[4] = fi_values[k];}
        if (test_u[0] && test_l[1] && test_u[2] && test_l[3]) {fi[5] = fi_values[k];}
        if (test_l[0] && test_u[1] && test_u[2] && test_l[3]) {fi[6] = fi_values[k];}
        if (test_u[0] && test_u[1] && test_u[2] && test_l[3]) {fi[7] = fi_values[k];}
        if (test_l[0] && test_l[1] && test_l[2] && test_u[3]) {fi[8] = fi_values[k];}
        if (test_u[0] && test_l[1] && test_l[2] && test_u[3]) {fi[9] = fi_values[k];}
        if (test_l[0] && test_u[1] && test_l[2] && test_u[3]) {fi[10] = fi_values[k];}
        if (test_u[0] && test_u[1] && test_l[2] && test_u[3]) {fi[11] = fi_values[k];}
        if (test_l[0] && test_l[1] && test_u[2] && test_u[3]) {fi[12] = fi_values[k];}
        if (test_u[0] && test_l[1] && test_u[2] && test_u[3]) {fi[13] = fi_values[k];}
        if (test_l[0] && test_u[1] && test_u[2] && test_u[3]) {fi[14] = fi_values[k];}
        if (test_u[0] && test_u[1] && test_u[2] && test_u[3]) {fi[15] = fi_values[k];}

      }

      // If failed to find all points needed for interpolation, throw an error.
      // If the user allows missing pts, e.g. for additional cuts on what grid points were simulated, just return missing_point_val
      size_t index = 0;
      while(index<16)
      {
        // Checking against a default value
        if (fi[index]==-1.0)
        {
          if (allow_missing_pts)
          {
            return missing_point_val;
          } else {
            utils_error().raise(LOCAL_INFO, "ERROR! 4D Interpolation fails for this parameter point.");
          }
        }
        index++;
      }

      // Variables to track repetitions
      int it = 0;
      int itmax = 4;

      // Perform the actual Calculation
      while (it < itmax)
      {
        InterpIter((itmax-it),xi_lower[it],xi_upper[it],fi,xi[it]);
        it++;
      }

      return fi[0];
    }

    // Check if point is inside interpolation range
    bool interp4d_collection::is_inside_range(double x1, double x2, double x3, double x4)
    {
      return ((x1 >= x1_min) && (x1 <= x1_max) && (x2 >= x2_min) && (x2 <= x2_max) && (x3 >= x3_min) && (x3 <= x3_max) && (x4 >= x4_min) && (x4 <= x4_max));
    }


    // 
    // interp5d_collection class methods
    // 

    // Constructor
    interp5d_collection::interp5d_collection(const std::string collection_name_in, const std::string file_name_in, const std::vector<std::string> colnames_in, bool allow_missing_points, double missing_pts_val)
    {
      // Check if file exists.
      if (not(Utils::file_exists(file_name_in)))
      {
        utils_error().raise(LOCAL_INFO, "ERROR! File '" + file_name_in + "' not found!");
      }

      // Read numerical values from data file.
      ASCIItableReader tab(file_name_in);

      // Check that there's more than 5 columns
      if (tab.getncol() < 6)
      {
        utils_error().raise(LOCAL_INFO, "ERROR! Less than six columns found in the input file '" + file_name_in + "'.");
      }

      // Check that the number of columns matches the number of column names
      if (colnames_in.size() != (size_t) tab.getncol())
      {
        utils_error().raise(LOCAL_INFO, "ERROR! Mismatch between number of columns and number of column names.");
      }

      // Set whether to allow missing points in the interpolation grid
      allow_missing_pts = allow_missing_points;
      missing_point_val = missing_pts_val;

      // Set the column names
      tab.setcolnames(colnames_in);

      // Save some names
      collection_name = collection_name_in;
      file_name = file_name_in;
      x1_name = colnames_in.at(0);
      x2_name = colnames_in.at(1);
      x3_name = colnames_in.at(2);
      x4_name = colnames_in.at(3);
      x5_name = colnames_in.at(4);
      interpolator_names = {colnames_in.begin() + 5, colnames_in.end()};

      // Number of interpolators
      n_interpolators = interpolator_names.size();

      // Get unique entries of "xi" for the grid and grid size.
      x1_vec = tab[x1_name];
      x1_vec_unsorted = tab[x1_name];
      sort(x1_vec.begin(), x1_vec.end());
      x1_vec.erase(unique(x1_vec.begin(), x1_vec.end()), x1_vec.end());
      int nx1 = x1_vec.size();
      x1_min = x1_vec.front();
      x1_max = x1_vec.back();

      x2_vec = tab[x2_name];
      x2_vec_unsorted = tab[x2_name];
      sort(x2_vec.begin(), x2_vec.end());
      x2_vec.erase(unique(x2_vec.begin(), x2_vec.end()), x2_vec.end());
      int nx2 = x2_vec.size();
      x2_min = x2_vec.front();
      x2_max = x2_vec.back();

      x3_vec = tab[x3_name];
      x3_vec_unsorted = tab[x3_name];
      sort(x3_vec.begin(), x3_vec.end());
      x3_vec.erase(unique(x3_vec.begin(), x3_vec.end()), x3_vec.end());
      int nx3 = x3_vec.size();
      x3_min = x3_vec.front();
      x3_max = x3_vec.back();

      x4_vec = tab[x4_name];
      x4_vec_unsorted = tab[x4_name];
      sort(x4_vec.begin(), x4_vec.end());
      x4_vec.erase(unique(x4_vec.begin(), x4_vec.end()), x4_vec.end());
      int nx4 = x4_vec.size();
      x4_min = x4_vec.front();
      x4_max = x4_vec.back();

      x5_vec = tab[x5_name];
      x5_vec_unsorted = tab[x5_name];
      sort(x5_vec.begin(), x5_vec.end());
      x5_vec.erase(unique(x5_vec.begin(), x5_vec.end()), x5_vec.end());
      int nx5 = x5_vec.size();
      x5_min = x5_vec.front();
      x5_max = x5_vec.back();

      for (size_t interp_index = 0; interp_index < n_interpolators; ++interp_index)
      {
        // Store the interpolation data to be used later
        std::string interp_name = interpolator_names[interp_index];

        int n_points = (tab[interp_name]).size();

        if (!allow_missing_pts && (nx1 * nx2 * nx3 * nx4 * nx5 != n_points))
        {
          utils_error().raise(LOCAL_INFO, "ERROR! The number of grid points ("+std::to_string(n_points)+") does not agree with the number of unique 'x' and 'y' values ("+std::to_string(nx1)+" and "+std::to_string(nx2)+") for the interpolator '"+interp_name+"'.\n Check formatting of the file: '"+file_name_in+"'. This could be the case if the interpolation grid is missing points.");
        }

        interp_data.push_back(tab[interp_name]);
      }
    }

    // Destructor
    interp5d_collection::~interp5d_collection() {}

    // Just some forward declarations... 
    void InterpIter(int Ntemp,double xi_1,double xi_2,std::vector<double>& fi,double test);

    // Evaluate a given interpolation
    double interp5d_collection::eval(double x1,double x2,double x3,double x4, double x5, size_t interp_index)
    {
      double xi[] = {x1,x2,x3,x4,x5};
      std::vector<double> fi_values = interp_data[interp_index];

      // Determine upper and lower bounds
      double xi_upper[] = {0.0,0.0,0.0,0.0,0.0};
      double xi_lower[] = {0.0,0.0,0.0,0.0,0.0};

      // Determine edges
      // This is split into 5 different loops since the number in each dimension may be different
      for (size_t i=0;i<(x1_vec.size());i++)
      {
        // In case of exact match
        if (x1 == x1_vec[i])
        {
          xi_lower[0] = x1_vec[i];
          xi_upper[0] = x1_vec[i];
        }
        // Otherwise bounds as normal
        if (x1 > x1_vec[i] && x1 < x1_vec[i+1])
        {
          xi_lower[0] = x1_vec[i];
          xi_upper[0] = x1_vec[i+1];
        }
        // End early if you have found all of the bounds
        if (x1 < x1_vec[i] ) break;
      }

      for (size_t i=0;i<(x2_vec.size());i++)
      {
        if (x2 == x2_vec[i])
        {
          xi_lower[1] = x2_vec[i];
          xi_upper[1] = x2_vec[i];
        }
        if (x2 > x2_vec[i] && x2 < x2_vec[i+1])
        {
          xi_lower[1] = x2_vec[i];
          xi_upper[1] = x2_vec[i+1];
        }
        if (x2 < x2_vec[i]) break;
      }

      for (size_t i=0;i<(x3_vec.size());i++)
      {
        if (x3 == x3_vec[i])
        {
          xi_lower[2] = x3_vec[i];
          xi_upper[2] = x3_vec[i];
        }
        if (x3 > x3_vec[i] && x3 < x3_vec[i+1])
        {
          xi_lower[2] = x3_vec[i];
          xi_upper[2] = x3_vec[i+1];
        }
        if (x3 < x3_vec[i]) break;
      }

      for (size_t i=0;i<(x4_vec.size());i++)
      {
        if (x4 == x4_vec[i])
        {
          xi_lower[3] = x4_vec[i];
          xi_upper[3] = x4_vec[i];
        }
        if (x4 > x4_vec[i] && x4 < x4_vec[i+1])
        {
          xi_lower[3] = x4_vec[i];
          xi_upper[3] = x4_vec[i+1];
        }
        if (x4 < x4_vec[i]) break;
      }

      for (size_t i=0;i<(x5_vec.size());i++)
      {
        if (x5 == x5_vec[i])
        {
          xi_lower[4] = x5_vec[i];
          xi_upper[4] = x5_vec[i];
        }
        if (x5 > x5_vec[i] && x5 < x5_vec[i+1])
        {
          xi_lower[4] = x5_vec[i];
          xi_upper[4] = x5_vec[i+1];
        }
        if (x5 < x5_vec[i]) break;
      }

      // Find the corresponding function values
      // Using a default value of -1 as this is assumed not a valid result.
      // Note: This will cause a problem if your interpolation is using -1. 
      //       However, this should not be the case in any scenarios I can envision.
      std::vector<double> fi = {-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,
                                -1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,
                                -1.0,-1.0,-1.0,-1.0};
      bool test_u[] = {false,false,false,false,false};
      bool test_l[] = {false,false,false,false,false};

      //Loop over all interp_data, and match value to coresponding value. 
      for (size_t k=0;k<fi_values.size();k++)
      {
        // Reset Values
        test_u[0] = false; test_u[1] = false; test_u[2] = false; test_u[3] = false; test_u[4] = false;
        test_l[0] = false; test_l[1] = false; test_l[2] = false; test_l[3] = false; test_l[4] = false;

        // Check whether the values correspond to any of the upper/lower values. skip calculation if not...
        if (x1_vec_unsorted[k]==xi_upper[0]) { test_u[0]=true;}
        if (x1_vec_unsorted[k]==xi_lower[0]) { test_l[0]=true;}
        if (test_u[0]==false && test_l[0]==false) continue;

        if (x2_vec_unsorted[k]==xi_upper[1]) { test_u[1]=true;}
        if (x2_vec_unsorted[k]==xi_lower[1]) { test_l[1]=true;}
        if (test_u[1]==false && test_l[1]==false) continue;

        if (x3_vec_unsorted[k]==xi_upper[2]) { test_u[2]=true;}
        if (x3_vec_unsorted[k]==xi_lower[2]) { test_l[2]=true;}
        if (test_u[2]==false && test_l[2]==false) continue;

        if (x4_vec_unsorted[k]==xi_upper[3]) { test_u[3]=true;}
        if (x4_vec_unsorted[k]==xi_lower[3]) { test_l[3]=true;}
        if (test_u[3]==false && test_l[3]==false) continue;

        if (x5_vec_unsorted[k]==xi_upper[4]) { test_u[4]=true;}
        if (x5_vec_unsorted[k]==xi_lower[4]) { test_l[4]=true;}
        if (test_u[4]==false && test_l[4]==false) continue;

        // Set the values of fi in the correct order
        if (test_l[0] && test_l[1] && test_l[2] && test_l[3] && test_l[4]) {fi[0] = fi_values[k];}
        if (test_u[0] && test_l[1] && test_l[2] && test_l[3] && test_l[4]) {fi[1] = fi_values[k];}
        if (test_l[0] && test_u[1] && test_l[2] && test_l[3] && test_l[4]) {fi[2] = fi_values[k];}
        if (test_u[0] && test_u[1] && test_l[2] && test_l[3] && test_l[4]) {fi[3] = fi_values[k];}
        if (test_l[0] && test_l[1] && test_u[2] && test_l[3] && test_l[4]) {fi[4] = fi_values[k];}
        if (test_u[0] && test_l[1] && test_u[2] && test_l[3] && test_l[4]) {fi[5] = fi_values[k];}
        if (test_l[0] && test_u[1] && test_u[2] && test_l[3] && test_l[4]) {fi[6] = fi_values[k];}
        if (test_u[0] && test_u[1] && test_u[2] && test_l[3] && test_l[4]) {fi[7] = fi_values[k];}
        if (test_l[0] && test_l[1] && test_l[2] && test_u[3] && test_l[4]) {fi[8] = fi_values[k];}
        if (test_u[0] && test_l[1] && test_l[2] && test_u[3] && test_l[4]) {fi[9] = fi_values[k];}
        if (test_l[0] && test_u[1] && test_l[2] && test_u[3] && test_l[4]) {fi[10] = fi_values[k];}
        if (test_u[0] && test_u[1] && test_l[2] && test_u[3] && test_l[4]) {fi[11] = fi_values[k];}
        if (test_l[0] && test_l[1] && test_u[2] && test_u[3] && test_l[4]) {fi[12] = fi_values[k];}
        if (test_u[0] && test_l[1] && test_u[2] && test_u[3] && test_l[4]) {fi[13] = fi_values[k];}
        if (test_l[0] && test_u[1] && test_u[2] && test_u[3] && test_l[4]) {fi[14] = fi_values[k];}
        if (test_u[0] && test_u[1] && test_u[2] && test_u[3] && test_l[4]) {fi[15] = fi_values[k];}
        if (test_l[0] && test_l[1] && test_l[2] && test_l[3] && test_u[4]) {fi[16] = fi_values[k];}
        if (test_u[0] && test_l[1] && test_l[2] && test_l[3] && test_u[4]) {fi[17] = fi_values[k];}
        if (test_l[0] && test_u[1] && test_l[2] && test_l[3] && test_u[4]) {fi[18] = fi_values[k];}
        if (test_u[0] && test_u[1] && test_l[2] && test_l[3] && test_u[4]) {fi[19] = fi_values[k];}
        if (test_l[0] && test_l[1] && test_u[2] && test_l[3] && test_u[4]) {fi[20] = fi_values[k];}
        if (test_u[0] && test_l[1] && test_u[2] && test_l[3] && test_u[4]) {fi[21] = fi_values[k];}
        if (test_l[0] && test_u[1] && test_u[2] && test_l[3] && test_u[4]) {fi[22] = fi_values[k];}
        if (test_u[0] && test_u[1] && test_u[2] && test_l[3] && test_u[4]) {fi[23] = fi_values[k];}
        if (test_l[0] && test_l[1] && test_l[2] && test_u[3] && test_u[4]) {fi[24] = fi_values[k];}
        if (test_u[0] && test_l[1] && test_l[2] && test_u[3] && test_u[4]) {fi[25] = fi_values[k];}
        if (test_l[0] && test_u[1] && test_l[2] && test_u[3] && test_u[4]) {fi[26] = fi_values[k];}
        if (test_u[0] && test_u[1] && test_l[2] && test_u[3] && test_u[4]) {fi[27] = fi_values[k];}
        if (test_l[0] && test_l[1] && test_u[2] && test_u[3] && test_u[4]) {fi[28] = fi_values[k];}
        if (test_u[0] && test_l[1] && test_u[2] && test_u[3] && test_u[4]) {fi[29] = fi_values[k];}
        if (test_l[0] && test_u[1] && test_u[2] && test_u[3] && test_u[4]) {fi[30] = fi_values[k];}
        if (test_u[0] && test_u[1] && test_u[2] && test_u[3] && test_u[4]) {fi[31] = fi_values[k];}

      }

      // If failed to find all points needed for interpolation, throw an error.
      // If the user allows missing pts, e.g. for additional cuts on what grid points were simulated, just return missing_point_val
      size_t index = 0;
      while(index<32)
      {
        // Checking against a default value
        if (fi[index]==-1.0)
        {
          if (allow_missing_pts)
          {
            return missing_point_val;
          } else {
            utils_error().raise(LOCAL_INFO, "ERROR! 5D Interpolation fails for this parameter point.");
          }
        }
        index++;
      }

      // Variables to track repetitions
      int it = 0;
      int itmax = 5;

      // Perform the actual Calculation
      while (it < itmax)
      {
        InterpIter((itmax-it),xi_lower[it],xi_upper[it],fi,xi[it]);
        it++;
      }

      return fi[0];
    }

    // Linear interpolation in 1D
    double linearinterp1D(double x1, double x2, double y1, double y2, double xtest)
    {
      // Avoid NaNs
      if(x2==x1) return y1;
      return (y1 + (xtest-x1)/(x2-x1) * (y2 - y1));
    }

    // Function to evaluate set of 1D interps, requires careful formatting of original data...
    void InterpIter(int Ntemp,double xi_1,double xi_2,std::vector<double>& fi,double test)
    {
      std::vector<double> vi;
      size_t j=0;

      // Loop over the number of required 1D interpolations
      while(j < pow(2,Ntemp))
      {
        if (fi.size() < j)
        {
          utils_error().raise(LOCAL_INFO, "ERROR! Something has gone wrong with sizes in InterpIter (4D/5D interpolation)");
        }

        vi.push_back(linearinterp1D(xi_1,xi_2,fi[j],fi[j+1],test));
        j = j + 2;
      }

      // Set values of fi to vi
      fi.clear();
      fi = vi;
    }

    // Check if point is inside interpolation range
    bool interp5d_collection::is_inside_range(double x1,double x2, double x3, double x4 , double x5)
    {
      return ((x1 >= x1_min) && (x1 <= x1_max) && (x2 >= x2_min) && (x2 <= x2_max) && (x3 >= x3_min) && (x3 <= x3_max) && (x4 >= x4_min) && (x4 <= x4_max)  && (x5 >= x5_min) && (x5 <= x5_max));
    }

  }
}
