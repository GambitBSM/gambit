//   GUM: GAMBIT Universal Model Macine
//   ***********************************
///  \file
///
///  Declarations of Feynrules class
///
///  **********************************
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2017, 2018, 2019
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 July
///
///  ***********************************

#ifndef FEYNRULES_H
#define FEYNRULES_H

#include "math_package.hpp"

namespace GUM
{
  class FeynRules : public Math_Package
  {

    public:

      // Constructor
      FeynRules(std::string, std::string);

      // Load package
      void load_feynrules();

      // Load model
      void load_model(std::string model, std::string base_model);

      // Load restriction e.g. diagonal CKM, etc.
      void load_restriction(std::string model, std::string base_model, std::string rst);

      // Check the Lagrangian makes sense
      void check_lagrangian(std::string LTot);

      // Hermiticity check
      void check_herm(std::string);

      // Get model name
      std::string get_modelname();

      // Particle list
      void get_partlist(std::vector<Particle>&);

      // Parameters list
      void get_paramlist(std::vector<Parameter>&);

      // Set gauge: unitary, or feynman
      void set_gauge(std::string);

      // Outputs: CalcHEP, MadGraph, ...
      void write_ch_output(std::string);
      void write_mg_output(std::string);

  };

  // Everything
  void all_feynrules(Options, std::vector<Particle>&, std::vector<Parameter>&, Outputs&, std::vector<std::string>&, Error&);

} // namespace GUM

#endif
