//   GUM: GAMBIT Universal Model Machine
//   ***********************************
///  \file
///
///  Declarations of SARAH class
///
///  **********************************
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2017, 2018, 2019
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 July, Aug
///
///  ***********************************

#ifndef SARAH_H
#define SARAH_H

#include "math_package.hpp"

namespace GUM
{
  class SARAH : public Math_Package
  {
    
    public:
  
      // SARAH constructor
      SARAH(std::string);

      // Load package
      void load_sarah();
    
      // Load model
      void load_model(std::string name);
    
      // Model exists
      bool model_exists(std::string name);

      // Check model
      void check_model(std::string name, std::vector<std::string>&);
    
      // Get model name
      std::string get_modelname();

      // Vertex list
      void calculate_vertices();
    
      // Particle list
      void get_partlist(std::vector<Particle>&);
  
      // Parameters list
      void get_paramlist(std::vector<Parameter>&, std::vector<Parameter>&);

      // MINPAR, EXTPAR
      void get_minpar_extpar(std::vector<Parameter>&);

      // Get in-out blocks
      void get_inout_blocks(std::vector<Parameter> &);

      // Get boundary conditions
      //void get_boundary_conditions(std::vector<Parameter>&);
      void get_boundary_conditions(std::map<std::string, std::string>&, std::vector<Parameter>);

      // Add SPheno masses
      void add_SPheno_mass_names(std::vector<Particle>&);

      // Leave only the parameters that SPheno uses
      void SPheno_parameters(std::vector<Parameter> &parameters);

      // Get tadpoles
      void get_tadpoles(std::vector<Parameter>&);

      // Get mixings
      void get_mixing_matrices(std::map<std::string, std::string>&);
    
      // Outputs: CalcHEP, MadGraph, ...
      void write_ch_output();
      void write_micromegas_output();
      void write_madgraph_output();
      void write_spheno_output(std::map<std::string,std::string>);
      void write_flexiblesusy_output();
      void write_vevacious_output();

  };

   
  // Everything
  void all_sarah(Options, std::vector<Particle>&, std::vector<Parameter>&, 
                 Outputs&, std::vector<std::string>&, std::map<std::string,bool>&, 
                 std::map<std::string, std::string>&, std::map<std::string, std::string>&,
                 std::vector<Parameter>&, Error &error);

} // namespace GUM
 
#endif
