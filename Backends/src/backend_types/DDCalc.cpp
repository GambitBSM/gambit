//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper types for DDCalc backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2019 Jul
///
///  \author Felix Kahlhofer
///          (kahlhoefer@physik.rwth-aachen.de)
///  \date 2020 May
///
///  *************************

#include "gambit/Backends/backend_types/DDCalc.hpp"
#include "gambit/Utils/model_parameters.hpp"
#include "gambit/Utils/util_types.hpp" 
#include "gambit/Models/safe_param_map.hpp"
#include <sstream>

namespace Gambit
{
    /// Default NREO_DM_nucleon_couplings constructor
    NREO_DM_nucleon_couplings::NREO_DM_nucleon_couplings()
    {
      CPTbasis = 0;
    }

    /// Default NREO_DM_nucleon_couplings constructor
    NREO_DM_nucleon_couplings::NREO_DM_nucleon_couplings(int CPT)
    {
      if(CPT)
      {

        int OpCoeffList[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,100,104};
        int OpCoeff;

        for(int i=0; i<25; i++)
        {

          OpCoeff = OpCoeffList[i];
          c0[OpCoeff] = 0;
          c1[OpCoeff] = 0;
        }

        CPTbasis = 1;

      }
      else
      {

        int OpCoeffList[] = {1,3,4,5,6,7,8,9,10,11,12,13,14,15,17,18,-1,-4};
        int OpCoeff;

        for(int i=0; i<18; i++)
        {

          OpCoeff = OpCoeffList[i];
          c0[OpCoeff] = 0;
          c1[OpCoeff] = 0;
        }

        CPTbasis = 0;
      }

    }

    /// NREO_DM_nucleon_couplings constuctor from ModelParameters object
    NREO_DM_nucleon_couplings::NREO_DM_nucleon_couplings(const ModelParameters& pars)
    {
       for(int i=1; i<=15; i++)
       {
          if (i != 2)
          {
            std::stringstream ss0;
            std::stringstream ss1;
            ss0<<"c0_"<<i;
            ss1<<"c1_"<<i;
            if(not pars.has(ss0.str()) or not pars.has(ss1.str()))
            {
              std::stringstream msg;
              msg<<"Error constructing NREO_DM_nucleon_couplings from ModelParameters! The supplied ModelParameters object (model name: "<<pars.getModelName()<<") does not contain NREO coupling parameters! Please check that an NREO-related ModelParameters object has been supplied.";
              backend_error().raise(LOCAL_INFO, msg.str());
            }
            c0[i] = pars[ss0.str()];
            c1[i] = pars[ss1.str()];
          }
       } 
    }

    /// NREO_DM_nucleon_couplings constuctor from functor 'Params', i.e. 'safe_param_map' used to hold collected model parameters 
    NREO_DM_nucleon_couplings::NREO_DM_nucleon_couplings(const Models::safe_param_map<safe_ptr<const double>>& pars)
    {
       for(int i=1; i<=15; i++)
       {
          if (i != 2)
          {
            std::stringstream ss0;
            std::stringstream ss1;
            ss0<<"c0_"<<i;
            ss1<<"c1_"<<i;
            if(pars.find(ss0.str())==pars.end() or pars.find(ss1.str())==pars.end())
            {
              std::stringstream msg;
              msg<<"Error constructing NREO_DM_nucleon_couplings from functor Params map! The supplied Params map does not contain NREO coupling parameters! Please check that an NREO-related model has been activated with ALLOW_MODELS in the rollcall declaration for this module function.";
              backend_error().raise(LOCAL_INFO, msg.str());
            }
            c0[i] = *pars[ss0.str()];
            c1[i] = *pars[ss1.str()];
          }
       }  
    }


}
