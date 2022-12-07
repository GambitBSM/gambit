//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  implementation of the Contur_output class (and helpers)
///  that converts the python dictionary output from
///  the contur API main into a simple class.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomasz Procter
///          (t.procter.1@research.gla.ac.uk)
///  \date 2021 October
///
///  *********************************************

#include "gambit/Backends/backend_types/Contur.hpp"

namespace Gambit
{

  #ifdef HAVE_PYBIND11

    void Contur_output::print_Contur_output_debug(std::ostream&outstream) const
    {
      outstream << "\nContur Output Object.\n\tLLR is: " <<
        LLR << "\n\tPool LLR's:";

      for (auto pool : pool_LLR){
        outstream << "\n\t\t" << pool.first << ": " << pool.second;
      }
      outstream << "\n\tPool Histotags:";
      for (auto pool : pool_tags){
        outstream << "\n\t\t" << pool.first << ": " << pool.second;
      }
      outstream << std::endl;
    }

    Contur_output merge_contur_outputs(const Contur_output& output1, const Contur_output& output2)
    {
      map_str_str new_pool_tags {};
      map_str_dbl new_pool_LLR {};

      //Concatenate the maps
      //TODO I presume there's something better than this syntax
      for(auto const& pool : output1.pool_LLR){
        new_pool_LLR[pool.first] = pool.second;
      }
      for(auto const& pool : output1.pool_tags){
        new_pool_tags[pool.first] = pool.second;
      }
      for(auto const& pool : output2.pool_LLR){
        new_pool_LLR[pool.first] = pool.second;
      }
      for(auto const& pool : output2.pool_tags){
        new_pool_tags[pool.first] = pool.second;
      }

      //Return the object
      return Contur_output(output1.LLR + output2.LLR, new_pool_LLR, new_pool_tags);
    }

    //This assumes that the same contur instances belong in each run. If this isn't the case, something very bad has gone wrong!
     Multi_Contur_output merge_multi_contur_outputs(const Multi_Contur_output& output1, const Multi_Contur_output& output2){
       Multi_Contur_output final_output = {};
       for(const auto &output_object_1 : output1){
         final_output[output_object_1.first] = merge_contur_outputs(output_object_1.second, output2.at(output_object_1.first));
       }
     }

    void print_Multi_Contur_output_debug(const Multi_Contur_output& multi_contur_out, std::ostream& outstream){
      for (auto contur_instance : multi_contur_out){
        outstream << contur_instance.first << ":\n";
        contur_instance.second.print_Contur_output_debug(outstream);
      }
    }

  #endif
}
