//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  GAMBIT-side type definitions for the smoking backend.
///
///  These structs mirror the definitions in smoking's
///  include/smoking/settings.h and include/smoking/input_parser.h.
///  Both sides must remain in sync so that the binary layout matches
///  when a smoking_variables reference is passed across the dlopen
///  boundary into init_SMOKING / Calculate_cross_section.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher Chang
///  \date 2026 Apr
///
///  *********************************************

#ifndef __smoking_types_hpp__
#define __smoking_types_hpp__

#include <string>
#include <vector>
#include <cmath>
#include <iostream>

// ---------------------------------------------------------------------------
// Types from smoking's include/smoking/settings.h
// ---------------------------------------------------------------------------

struct IntegratorConfig
{
  std::string backend  = "GSL";
  std::string strategy = "VEGAS";
  bool   use_GPU_integrator = false;
  int    chunksize          = 8192;
  double err_tol_rel        = 5e-2;
  size_t max_iters          = 10;
  size_t n_call             = 0;
};

struct VegasParams   { double alpha = 1.5; };
struct SuaveParams   {};
struct DivonneParams {};
struct CuhreParams   {};

// ---------------------------------------------------------------------------
// Types from smoking's include/smoking/input_parser.h
// ---------------------------------------------------------------------------

struct smoking_variables
{
  double sqrt_s = 13600.0;
  int    ipid1  = 2212;
  int    ipid2  = 2212;
  std::vector<int> pid1;
  std::vector<int> pid2;

  int  order = 1;
  bool dm    = false;
  bool dt    = false;
  std::vector<std::string> diff_name;
  std::vector<double>      diff_val;
  int default_scheme = 0;

  int scale_scheme = 0;
  std::vector<double> central_scale;
  double central_scale_F, central_scale_R;
  std::vector<double> scale_ratio;
  double scale_ratio_F, scale_ratio_R;
  bool scale_error    = false;
  int  scale_strategy = 3;

  bool        alphas_error = false;
  bool        pdf_error    = false;
  std::string pdf_set      = "PDF4LHC15_nnlo_100";
  bool        model_alphas;     // intentionally uninitialised, matching smoking
  std::string slha_file    = "example/sps1a.slha";
  SLHAea::Coll slhaea;
  bool        output       = false;
  std::string output_file;

  bool diffname_flag       = false;
  bool diffval_flag        = false;
  bool scale_flag          = false;
  bool central_scale_flag  = false;
  bool scale_ratio_flag    = false;
  bool output_file_name    = false;

  double xmin                    = 0;
  bool   PDFxmin                 = false;
  bool   invMellin_force_physical = false;

  double NLP    = 1;
  double NLL    = 1;
  double NNLL   = 0;
  double H_1loop = 0;
  double H_2loop = 0;

  IntegratorConfig int_config;
  VegasParams      vegas_params;
  SuaveParams      suave_params;
  DivonneParams    divonne_params;
  CuhreParams      cuhre_params;
};

//
// Structures for keeping track of results
//


// Struct for single cross section calculations with numerical errors
// Errors propagate under addition, subtraction and multiplication by constant
// The struct has a simple printing << operator
struct xsec{
  double central;
  double upper;
  double lower;
  
  // Status flag, not used to store fatal errors
  int status;
  
  // Constructor
  xsec(double central=0, double upper=0, double lower=0, int status=0): central(central), upper(upper), lower(lower), status(status) {}

  // Addition of cross sections, does not modify object therefore const
  xsec operator+(const xsec& a) const {
    // If an error occurred, return the first error
    int combined_status = 0;
    if (status < 0) {combined_status = status;}
    else if (a.status < 0)  {combined_status = a.status;}
    else {combined_status = std::max(status, a.status);}

    return xsec(central+a.central, sqrt(upper*upper+a.upper*a.upper), sqrt(lower*lower+a.lower*a.lower), combined_status);
  }

  // Subtraction of cross sections, does not modify object therefore const
  xsec operator-(const xsec& a) const {
    // If an error occurred, return the first error
    int combined_status = 0;
    if (status < 0) {combined_status = status;}
    else if (a.status < 0)  {combined_status = a.status;}
    else {combined_status = std::max(status, a.status);}

    return xsec(central-a.central, sqrt(upper*upper+a.upper*a.upper), sqrt(lower*lower+a.lower*a.lower), combined_status);
  }

  // Scalar multiplication, does modify object
  xsec operator*(const double a) {
    return xsec(a*central, a*upper, a*lower, status);
  }
  
};

xsec operator*(const double k, const xsec& a);
std::ostream& operator<<(std::ostream& os, const xsec& a);


// Struct for bookkeeping results of a complete calculation
struct Result{
  xsec cross_section {0,0,0};
  xsec upper_sca_err {0,0,0};
  xsec lower_sca_err {0,0,0};
  std::vector<xsec> sca_err; // Contains cross-section for other scales: For strategy 3 (mu_F,mu_R)/mu_0 = [(0.5,0.5), (2,2)]
                             // For strategy 7 (mu_F,mu_R)/mu_0 = [(0.5,0.5), (0.5,1), (1,0.5), (1,2), (2,1), (2,2)]
  std::vector<xsec> pdf_err;
  double upper_pdf_err;
  double lower_pdf_err;
  double upper_alphas_err;
  double lower_alphas_err;

  // Used to indicate success/failure. Anything other than zero is a failure.
  int status;

  // Constructor
  Result() = default;
  Result(xsec cross_section, std::vector<xsec> sca_err, std::vector<xsec> pdf_err): cross_section(cross_section), sca_err(sca_err), pdf_err(pdf_err) {}
  
  // Addition of results, does not modify object therefore const
  Result operator+(const Result& a) const {
    std::vector<xsec> total_pdferr;
    for(size_t i=0; i < pdf_err.size(); i++){
      total_pdferr.push_back(pdf_err[i]+a.pdf_err[i]);
    }
    std::vector<xsec> total_scaerr;
    for(size_t i=0; i < sca_err.size(); i++){
      total_scaerr.push_back(sca_err[i]+a.sca_err[i]);
    }
    Result res = Result(cross_section+a.cross_section, total_scaerr, total_pdferr);
    res.status = std::min(status, a.status);
    
    return res;
  }

  // Subtraction of results, does not modify object therefore const
  Result operator-(const Result& a) const {
    std::vector<xsec> total_pdferr;
    for(size_t i=0; i < pdf_err.size(); i++){
      total_pdferr.push_back(pdf_err[i]-a.pdf_err[i]);
    }
    std::vector<xsec> total_scaerr;
    for(size_t i=0; i < sca_err.size(); i++){
      total_scaerr.push_back(sca_err[i]-a.sca_err[i]);
    }
    Result res = Result(cross_section-a.cross_section, total_scaerr, total_pdferr);
    res.status = std::min(status, a.status);
    return res;
  }

  // Scalar multiplication, does modify object
  Result operator*(const double a) {
    std::vector<xsec> total_pdferr;
    for(size_t i=0; i < pdf_err.size(); i++){
      total_pdferr.push_back(a*pdf_err[i]);
    }
    std::vector<xsec> total_scaerr;
    for(size_t i=0; i < pdf_err.size(); i++){
      total_scaerr.push_back(a*sca_err[i]);
    }
    Result res = Result(a*cross_section, total_scaerr, total_pdferr);
    return res;
  }
  
  // Set values equal to a xsec struct (cross section result)
  Result& operator=(const xsec& a) {
    cross_section = a;
    return *this;
  }

    
};

Result operator*(const double k, const Result& a);


#endif /* defined __smoking_types_hpp__ */
