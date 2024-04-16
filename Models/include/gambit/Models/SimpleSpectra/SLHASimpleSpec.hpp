//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper base class for simple subspectrum
///  wrappers that want to use SLHAea features
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Apr
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2016 Oct
///
///  *********************************************

#ifndef __SLHASimpleSpec_hpp__
#define __SLHASimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"

namespace Gambit
{

      /// Skeleton "model" class which interacts with an SLHAea object
      class SLHAeaModel
      {
         protected:
           /// SLHAea object
           SLHAea::Coll data;
           /// SLHA version of SLHAea object
           int wrapped_slha_version;
           /// PDG translation map (e.g. from SLHA1 to SLHA2 for MSSMskeleton)
           std::map<int, int> PDG_translation_map;

         public:
           /// @{ Constructors
           SLHAeaModel();
           SLHAeaModel(const SLHAea::Coll& input);
           /// @}

           /// Get the SLHA version of the internal SLHAea object
           int slha_version() const;

           /// Get the internal SLHAea object
           const SLHAea::Coll& get_slhaea() const;

           /// PDG code translation map, for special cases where an SLHA file has been read in and the PDG codes changed.
           const std::map<int, int>& PDG_translator() const;

           /// Helper functions to do error checking for SLHAea object contents
           double getdata(const std::string& block, int index) const;
           double getdata(const std::string& block, int i, int j) const;
           bool checkdata(const std::string& block, int index) const;
      };

      template<class Derived>
      class SLHASimpleSpec : public Spec<Derived>
      {
         public:
            // Grab typedefs from derived wrapper traits class
            // (only needed because this is a template class, and would have to
            // qualify the name all over the place in order to use the equivalent
            // typedef which is inherited from the base class)
            typedef typename SpecTraits<Derived>::Model Model;
            typedef typename SpecTraits<Derived>::Input Input;

         protected:
            // Store SLHAea object internally (via wrapper)
            Model slhawrap;

            // Dummy placeholder for potential Inputs object
            Input dummyinput;

         public:
            typedef MapTypes<Derived,MapTag::Get> MTget;

            // Constructors/destructors
            SLHASimpleSpec()
             : slhawrap()
            {}

            SLHASimpleSpec(const SLHAea::Coll& input_slha)
             : slhawrap(input_slha)
            {}

            virtual ~SLHASimpleSpec() {};

            // Functions to interface Model and Input objects with the base 'Spec' class
            // Need both const and non-const versions of it, so that wrapped objects cannot be modified
            // if the wrapper is const
            Model& get_Model() { return slhawrap; }
            Input& get_Input() { return dummyinput; /*unused, but needs to be defined for the interface*/ }
            const Model& get_Model() const { return slhawrap; }
            const Input& get_Input() const { return dummyinput; /*unused, but needs to be defined for the interface*/ }

            /// Add spectrum information to an SLHAea object
            void add_to_SLHAea(int, SLHAea::Coll&) const;

            /// (using bass class version of getSLHAea)
 
            /// @{ RunningPars interface overrides
            virtual double GetScale() const
            {
               /// TODO: Currently assumes all blocks at same scale. Should at least check if this
               /// is true in constructor.
               const SLHAea::Coll& data(slhawrap.get_slhaea());
               double scale = 0.0;
               try
               {
                 scale = SLHAea::to<double>(data.at("GAUGE").find_block_def()->at(3));
               }
               catch (const std::out_of_range& e)
               {
                 std::ostringstream errmsg;
                 errmsg << "Could not find block \"GAUGE\" in SLHAea object. Received out_of_range error with message: " << e.what();
                 utils_error().raise(LOCAL_INFO,errmsg.str());
               }
               return scale;
            }

            virtual void SetScale(double)
            {
              // this is actually a bit of a drag since one should go through all the blocks
              // that have Q defined and set them accordingly. Leave for now.
               utils_error().raise(LOCAL_INFO,
                  "Call made to SetScale function of SLHASimpleSpec! This is currently not implemented!");
            }

            virtual void RunToScaleOverride(double)
            {
               utils_error().raise(LOCAL_INFO,
                  "Call made to RunToScale function of SLHASimpleSpec!  This is not allowed; this\n"
                  "version of the SubSpectrum wrapper cannot perform RGE   It is just a\n"
                  "simple box containing SLHA information read from a file or SLHAea object.\n");
            }
            /// @}

         protected:
            /// Map fillers go in derived class

      };

      /// @{ Member functions for SLHASimpleSpec class

      /// Add spectrum information to an SLHAea object
      // NOTE! This is just a kind of catch-all default! Wrappers for particular models
      // should more carefully extract the model information and perform SLHA2->SLHA1
      // conversions if required. 
      template<class Derived>
      void SLHASimpleSpec<Derived>::add_to_SLHAea(int /*slha_version*/, SLHAea::Coll& slha) const
      {
        // Get the internal SLHAea data object
        const SLHAea::Coll& data = get_Model().get_slhaea();

        // NO version check. Cannot assume that this is required or makes sense for whatever
        // model this might be. If it does matter, then the wrapper for that model should
        // replace this function and do the check itself.
        //int wrapped_slha_version = get_Model().slha_version();
        //if (slha_version != wrapped_slha_version)
        //{
        //  std::stringstream x;
        //  x << "Wrapped SLHA file is in SLHA" << wrapped_slha_version << ", but something requested to add it to an SLHAea object in SLHA" << slha_version << " format.";
        //  model_error().raise(LOCAL_INFO, x.str());
        //}

        // Make a copy of the internal SLHAea object, remove any SM info from it and add the rest to the slhaea object. 
        // (we will assume that if SM is wanted then it is provided by the SMSimpleSpec wrapper, or similar)
        SLHAea::Coll data_copy = data;
        SLHAea::Coll::key_matches target_blocks[4] = { SLHAea::Coll::key_matches("SMINPUTS"), SLHAea::Coll::key_matches("VCKMIN"), SLHAea::Coll::key_matches("UPMNSIN"), SLHAea::Coll::key_matches("MASS") };
        for (SLHAea::Coll::iterator sblock = slha.begin(); sblock != slha.end(); ++sblock)
        {
          for (SLHAea::Coll::iterator dblock = data_copy.begin(); dblock != data_copy.end();)
          {
            bool delete_dblock = false;
            for (int i = 0; i < 3; i++)
            {
              if (target_blocks[i](*sblock) and target_blocks[i](*dblock)) delete_dblock = true;
            }
            if (delete_dblock) dblock = data_copy.erase(dblock);
            else ++dblock;
          }
        }
        for (SLHAea::Coll::iterator sblock = slha.begin(); sblock != slha.end();)
        {
          if (target_blocks[3](*sblock))
          {
            if(slha["MASS"][24].is_data_line()) data_copy["MASS"][24] = slha["MASS"][24];
            sblock = slha.erase(sblock);
          }
          else
          {
            ++sblock;
          }
        }
        slha.insert(slha.end(), data_copy.cbegin(), data_copy.cend());
      }
 
      /// @}
  

} // end Gambit namespace

#endif
