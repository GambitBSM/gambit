//   GUM: GAMBIT Universal Model Machine
//   ***********************************
///  \file
///
///  Declarations of mother class for
///  Mathematica packages.
///
///  **********************************
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 July, Aug
///
///  ***********************************

#ifndef MATH_PACKAGE_H
#define MATH_PACKAGE_H

#include <math.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <exception>

#include "wstp.h"

#include "cmake_variables.hpp"
#include "options.hpp"

namespace GUM
{

  class Math_Package
  {
    protected:

      // Link to WSTP
      WSLINK link;

      // Name of model
      std::string name;


    public:

      // Constructor
      Math_Package(std::string);

      // Destructor
      ~Math_Package();

      // Set model name
      void set_name(std::string);

      // Create the link to WSTP
      void create_wstp_link();

      // Close link to WSTP
      void close_wstp_link();

      // Wait to receive a packet from the kernel
      void wait_for_packet();

      // Send a string to be evaluated in Mathematica via WSTP
      void send_to_math(std::string input);

      // Get a character variable from Mathematica via WSTP
      void get_from_math(char &);

      // Get a string variable from Mathematica via WSTP
      void get_from_math(std::string &);

      // Get an integer variable from Mathematica via WSTP
      void get_from_math(int &);

      // Get a float variable from Mathematica via WSTP
      void get_from_math(float &);

      // Get a double variable from Mathematica via WSTP
      void get_from_math(double &);

      // Get a bool variable from Mathematica via WSTP
      void get_from_math(bool &);

      // Get a list variable from Mathematica via WSTP
      template<typename T> void get_from_math(std::vector<T> &list)
      {
        long int dim;
        if(!WSCheckFunction(link, "List", &dim))
          throw "WSTP Error: Failed to retrieve a list";
        for(int i=0; i<dim; i++)
        {
          T value;
          try { get_from_math(value); }
          catch(std::exception& e) { throw e; }
          list.push_back(value);
        }
      }

      // Load package
      void load_package();

      // Load model
      void load_model(std::string);

      // Model checks
      void check_model();

      // Get model name
      std::string get_modelname();

      // Particle list
      void get_partlist(std::vector<Particle>&);

      // Parameters list
      void get_paramlist(std::vector<Parameter>&);

      // Flags (boolean only)
      void get_flags(std::map<std::string,bool>&);

  };

} // namespace GUM

#endif // MATHEMATICA_H
