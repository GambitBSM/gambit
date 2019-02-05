//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit for the NMSSM
///
///  These functions link ModelParameters to
///  Spectrum objects in various ways (by running
///  spectrum generators, etc.)
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2018 Oct
///
///  \author José Eliel Camargo-Molina
///        (elielcamargomolina@gmail.com)
///  \date 2018 Dec
///
///  *********************************************

//#include <string>
//#include <sstream>
#include <cmath>
//#include <complex>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum_factories.hpp"
#include "gambit/Elements/smlike_higgs.hpp"
#include "gambit/Models/SimpleSpectra/NMSSMSimpleSpec.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

// Switch for debug mode
//#define SPECBIT_DEBUG

namespace Gambit
{

  namespace SpecBit
  {
    using namespace LogTags;

    bool only_alignment_limit(const Spectrum& result)
    {
        // getting the mixing matrix for neutral scalars, from the SUSY basis to the mass basis.

        boost::numeric::ublas::matrix<double> ZSusyToMassBasis (3,3);

        for (int i = 1; i <= 3; i++) {
            for (int j = 1; j <= 3; j++) {

                ZSusyToMassBasis(i-1,j-1) = result.get(Par::Pole_Mixing, "h0",i,j); // causes program to stop working

            }
        }


        double tanbeta = result.get(Par::dimensionless, "tanbeta");
        double sinbeta = tanbeta/(sqrt(1 + tanbeta * tanbeta));
        double cosbeta = 1/(sqrt(1 + tanbeta * tanbeta));

        cout<<"Got sinbeta and cosb: " << sinbeta << " " << cosbeta <<endl;

        // Writing the mixing from the Higgs Basis to the SUSY basis. It is just a rotation by angle beta

        boost::numeric::ublas::matrix<double> ZHiggsToSusyBasis (3,3);

        ZHiggsToSusyBasis(0,0) = cosbeta;
        ZHiggsToSusyBasis(0,1) = -sinbeta;
        ZHiggsToSusyBasis(0,2) = 0;
        ZHiggsToSusyBasis(1,0) = sinbeta;
        ZHiggsToSusyBasis(1,1) = cosbeta;
        ZHiggsToSusyBasis(1,2) = 0;
        ZHiggsToSusyBasis(1,0) = 0;
        ZHiggsToSusyBasis(1,1) = 0;
        ZHiggsToSusyBasis(1,2) = 1;


        // Getting the mixing matrix from the Higgs Basis to the mass basis
        // This works as SPheno gives the matrix R with h_i = R_ij \H_j where h are the mass eigenstates and j = u,d.
        // Then having R' such that H_j = R'_jk \Phi_k where \Phi_k are in the Higgs basis,
        // we get that h_i = R_ij R'_jk \Phi_k is the matrix taking us from the Higgs basis to the mass basis.
        // The approximate alignment limit is when ( R R')_00 ~ 1 .

        boost::numeric::ublas::matrix<double> ZHiggsToMassBasis = boost::numeric::ublas::prod(ZSusyToMassBasis,ZHiggsToSusyBasis);


        cout<<"The H_SM component of h is: " << ZHiggsToMassBasis(0,0) <<endl;

        return ZHiggsToMassBasis(0,0) > 0.9;
    }

    void get_NMSSM_spectrum_SPheno (Spectrum& spectrum)
    {
      namespace myPipe = Pipes::get_NMSSM_spectrum_SPheno;
      const SMInputs &sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      Finputs inputs;
      inputs.sminputs = sminputs;
      inputs.param = myPipe::Param;
      inputs.options = myPipe::runOptions;

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // Get the spectrum from the Backend
      myPipe::BEreq::NMSSM_spectrum(spectrum, inputs);

      // Get the SLHA struct from the spectrum object
      SLHAstruct slha = spectrum.getSLHAea(2);

      // Has the user chosen to override any pole mass values?
      // This will typically break consistency, but may be useful in some special cases
      if (myPipe::runOptions->hasKey("override_pole_masses"))
      {
        std::vector<str> particle_names = myPipe::runOptions->getNames("override_pole_masses");
        for (auto& name : particle_names)
        {
          double mass = myPipe::runOptions->getValue<double>("override_pole_masses", name);
          SLHAea_add(slha, "MASS", Models::ParticleDB().pdg_pair(name).first, mass, name, true);
        }
      }

      // Convert into a spectrum object
      spectrum = spectrum_from_SLHAea<NMSSMSimpleSpec, SLHAstruct>(slha,slha,mass_cut,mass_ratio_cut);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");

      // Only allow neutralino LSPs.
      if (not has_neutralino_LSP(spectrum)) invalid_point().raise("Neutralino is not LSP.");

      // Alignment limit check

      if (not only_alignment_limit(spectrum) and myPipe::runOptions->getValueOrDef<bool>(false,"only_alignment_limit") ) invalid_point().raise("No alignment limit but it has been requested.");

    }

    /// Put together the Higgs couplings for the NMSSM, from SPheno
    void NMSSM_higgs_couplings_SPheno(HiggsCouplingsTable &result)
    {
      namespace myPipe = Pipes::NMSSM_higgs_couplings_SPheno;

      // Retrieve spectrum contents
      const Spectrum& spec = *myPipe::Dep::NMSSM_spectrum;
      const SubSpectrum& he = spec.get_HE();
      const SMInputs &sminputs = spec.get_SMInputs();

      const DecayTable* tbl = &(*myPipe::Dep::decay_rates);

      // Set up the input structure for SPheno
      Finputs inputs;
      inputs.sminputs = sminputs;
      inputs.param = myPipe::Param;
      inputs.options = myPipe::runOptions;

      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "h0_3", "A0_1", "A0_2");

      // Set the CP of the Higgs states.  Note that this would need to be more sophisticated to deal with the complex NMSSM!
      result.CP[0] = 1.;  //h0_1
      result.CP[1] = 1.;  //h0_2
      result.CP[2] = 1.;  //h0_3
      result.CP[3] = -1.; //A0_1
      result.CP[4] = -1.; //A0_2

      // Work out which SM values correspond to which SUSY Higgs
      int SMlike_higgs = SMlike_higgs_PDG_code_NMSSM(he);

      int higgs;
      int other_higgs;
      int yet_another_higgs;
      if      (SMlike_higgs == 25) { higgs = 0; other_higgs = 1; yet_another_higgs = 2; }
      else if (SMlike_higgs == 35) { higgs = 1; other_higgs = 0; yet_another_higgs = 2; }
      else if (SMlike_higgs == 45) { higgs = 2; other_higgs = 0; yet_another_higgs = 1; }

      // Set the standard model decays
      result.set_neutral_decays_SM(higgs, sHneut[higgs], *myPipe::Dep::Reference_SM_Higgs_decay_rates);
      result.set_neutral_decays_SM(other_higgs, sHneut[other_higgs], *myPipe::Dep::Reference_SM_other_Higgs_decay_rates);
      result.set_neutral_decays_SM(yet_another_higgs, sHneut[yet_another_higgs], *myPipe::Dep::Reference_SM_h0_3_decay_rates);
      result.set_neutral_decays_SM(3, sHneut[3], *myPipe::Dep::Reference_SM_A0_decay_rates);
      result.set_neutral_decays_SM(4, sHneut[4], *myPipe::Dep::Reference_SM_A0_2_decay_rates);

      // Set the Higgs sector decays from the DecayTable
      result.set_neutral_decays(higgs, sHneut[higgs], tbl->at("h0_1"));
      result.set_neutral_decays(other_higgs, sHneut[other_higgs], tbl->at("h0_2"));
      result.set_neutral_decays(yet_another_higgs, sHneut[yet_another_higgs], tbl->at("h0_3"));
      result.set_neutral_decays(3, sHneut[3], tbl->at("A0_1"));
      result.set_neutral_decays(4, sHneut[4], tbl->at("A0_2"));
      result.set_charged_decays(0, "H+", tbl->at("H+"));

      // Add t decays since t can decay to light Higgses

      // S.B. Flavour/mass basis discrepancy
      //result.set_t_decays(tbl->at("t"));
      result.set_t_decays(tbl->at("u_3"));

      // Fill HiggsCouplingsTable object from SPheno backend
      // This fills the effective couplings (C_XX2)
      myPipe::BEreq::NMSSM_HiggsCouplingsTable(spec, result, inputs);

      // The SPheno frontend provides the invisible width for each Higgs, however this requires
      // loads of additional function calls. Just use the helper function instead.
      result.invisibles = get_invisibles(he);
    }


    template <class Contents>
    void fill_map_from_subspectrum(std::map<std::string,double>& specmap, const SubSpectrum& subspec)
    {
      /// Add everything... use spectrum contents routines to automate task
      static const Contents contents;
      static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters();

      for(std::vector<SpectrumParameter>::const_iterator it = required_parameters.begin();
           it != required_parameters.end(); ++it)
      {
         const Par::Tags        tag   = it->tag();
         const std::string      name  = it->name();
         const std::vector<int> shape = it->shape();

         /// Verification routine should have taken care of invalid shapes etc, so won't check for that here.

         // Check scalar case
         if(shape.size()==1 and shape[0]==1)
         {
           std::ostringstream label;
           label << name <<" "<< Par::toString.at(tag);
           specmap[label.str()] = subspec.get(tag,name);
         }
         // Check vector case
         else if(shape.size()==1 and shape[0]>1)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             std::ostringstream label;
             label << name <<"_"<<i<<" "<< Par::toString.at(tag);
             specmap[label.str()] = subspec.get(tag,name,i);
           }
         }
         // Check matrix case
         else if(shape.size()==2)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             for(int j = 1; j<=shape[0]; ++j) {
               std::ostringstream label;
               label << name <<"_("<<i<<","<<j<<") "<<Par::toString.at(tag);
               specmap[label.str()] = subspec.get(tag,name,i,j);
             }
           }
         }
         // Deal with all other cases
         else
         {
           // ERROR
           std::ostringstream errmsg;
           errmsg << "Error, invalid parameter received while converting SubSpectrum to map of strings! This should no be possible if the spectrum content verification routines were working correctly; they must be buggy, please report this.";
           errmsg << "Problematic parameter was: "<< tag <<", " << name << ", shape="<< shape;
           utils_error().forced_throw(LOCAL_INFO,errmsg.str());
         }
      }
    }

    void get_NMSSM_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_NMSSM_spectrum_as_map;
      const Spectrum& nmssmspec(*myPipe::Dep::NMSSM_spectrum);

      // @{ DEBUGGING
      //std::cout<<"Debugging NMSSM spectrum routines..."<<std::endl;
      //std::cout<<"Dumping SLHAea object from Spectrum object"<<std::endl;
      //std::cout<<nmssmspec.get_HE().getSLHAea(2)<<std::endl; 
      // @}

      fill_map_from_subspectrum<SpectrumContents::SM_slha>  (specmap, nmssmspec.get_LE());
      // TODO: This line doesn't work for some reason... 
      fill_map_from_subspectrum<SpectrumContents::NMSSM>(specmap, nmssmspec.get_HE());
    }

    /// @} End Gambit module functions

  } // end namespace SpecBit
} // end namespace Gambit

