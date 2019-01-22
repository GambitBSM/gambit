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

    // SB: todo
    /// Put together the Higgs couplings for the NMSSM, from partial widths only
    void NMSSM_higgs_couplings_pwid(HiggsCouplingsTable &result)
    {
      using namespace Pipes::NMSSM_higgs_couplings_pwid;

      // Retrieve spectrum contents
      const SubSpectrum& spec = Dep::NMSSM_spectrum->get_HE();

      // Get DecayTable object
      const DecayTable* tbl = &(*Dep::decay_rates);

      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "h0_3", "A0_1", "A0_2");

      // Set the CP of the Higgs states.  Note that this would need to be more sophisticated to deal with the complex NMSSM!
      result.CP[0] = 1.;  //h0_1
      result.CP[1] = 1.;  //h0_2
      result.CP[2] = 1.;  //h0_3
      result.CP[3] = -1.; //A0_1
      result.CP[4] = -1.; //A0_2

      // Work out which SM values correspond to which SUSY Higgs
      //int higgs = (SMlike_higgs_PDG_code_NMSSM(spec) == 25 ? 0 : 1);
      int SMlike_higgs = SMlike_higgs_PDG_code_NMSSM(spec);
      std::cout << "Most SM-like higgs = " << SMlike_higgs << std::endl;

      int higgs;
      int other_higgs;
      int yet_another_higgs;
      if      (SMlike_higgs == 25) { higgs = 0; other_higgs = 1; yet_another_higgs = 2; }
      else if (SMlike_higgs == 35) { higgs = 1; other_higgs = 0; yet_another_higgs = 2; }
      else if (SMlike_higgs == 45) { higgs = 2; other_higgs = 0; yet_another_higgs = 1; }

      // Set the decays
      result.set_neutral_decays_SM(higgs, sHneut[higgs], *Dep::Reference_SM_Higgs_decay_rates);
      result.set_neutral_decays_SM(other_higgs, sHneut[other_higgs], *Dep::Reference_SM_other_Higgs_decay_rates);
      result.set_neutral_decays_SM(yet_another_higgs, sHneut[yet_another_higgs], *Dep::Reference_SM_h0_3_decay_rates);
      result.set_neutral_decays_SM(3, sHneut[3], *Dep::Reference_SM_A0_decay_rates);
      result.set_neutral_decays_SM(4, sHneut[4], *Dep::Reference_SM_A0_2_decay_rates);

      try { const DecayTable::Entry& Higgs_decays = tbl->at("h0_1"); result.set_neutral_decays(0, "h0_1", Higgs_decays); }
      catch (std::exception& e) { SpecBit_error().raise(LOCAL_INFO, "h0_1 decays not provided by DecayTable."); }

      try { const DecayTable::Entry& h0_2_decays = tbl->at("h0_2"); result.set_neutral_decays(1, "h0_2", h0_2_decays); }
      catch (std::exception& e) { SpecBit_error().raise(LOCAL_INFO, "h0_2 decays not provided by DecayTable."); }

      try { const DecayTable::Entry& h0_3_decays = tbl->at("h0_3"); result.set_neutral_decays(2, "h0_3", h0_3_decays); }
      catch (std::exception& e) { SpecBit_error().raise(LOCAL_INFO, "h0_3 decays not provided by DecayTable."); }

      try { const DecayTable::Entry& A0_1_decays = tbl->at("A0_1"); result.set_neutral_decays(3, "A0_1", A0_1_decays); }
      catch (std::exception& e) { SpecBit_error().raise(LOCAL_INFO, "A0_1 decays not provided by DecayTable."); }

      try { const DecayTable::Entry& A0_2_decays = tbl->at("A0_2"); result.set_neutral_decays(4, "A0_2", A0_2_decays); }
      catch (std::exception& e) { SpecBit_error().raise(LOCAL_INFO, "A0_2 decays not provided by DecayTable."); }

      try { const DecayTable::Entry& H_plus_decays = tbl->at("H+"); result.set_charged_decays(0, "H+", H_plus_decays); }
      catch (std::exception& e) { SpecBit_error().raise(LOCAL_INFO, "H+ decays not provided by DecayTable."); }

      //result.set_neutral_decays_SM(higgs, sHneut[higgs], *Dep::Reference_SM_Higgs_decay_rates);
      //result.set_neutral_decays_SM(other_higgs, sHneut[other_higgs], *Dep::Reference_SM_other_Higgs_decay_rates);
      //result.set_neutral_decays_SM(yet_another_higgs, sHneut[yet_another_higgs], *Dep::Reference_SM_other_Higgs_decay_rates);
      //result.set_neutral_decays_SM(4, sHneut[4], *Dep::Reference_SM_A0_decay_rates);
      //result.set_neutral_decays_SM(5, sHneut[5], *Dep::Reference_SM_A0_2_decay_rates);
      //result.set_neutral_decays(0, sHneut[0],  *Dep::Higgs_decay_rates);
      //result.set_neutral_decays(1, sHneut[1], *Dep::h0_2_decay_rates);
      //result.set_neutral_decays(2, sHneut[2], *Dep::h0_3_decay_rates);
      //result.set_neutral_decays(3, sHneut[3], *Dep::A0_decay_rates);
      //result.set_neutral_decays(4, sHneut[4], *Dep::A0_2_decay_rates);
      //result.set_charged_decays(0, "H+", *Dep::H_plus_decay_rates);
      //result.set_t_decays(*Dep::t_decay_rates);


      // Currently no t decays from SPheno. In fact no SM decays... 
      /*
      try { const DecayTable::Entry& t_decays = tbl->at("t"); result.set_t_decays(t_decays); }
      catch (std::exception& e) { SpecBit_error().raise(LOCAL_INFO, "top decays not provided by DecayTable."); }
      */
      result.set_t_decays(*Dep::t_decay_rates);

      // // Use them to compute effective couplings for all neutral higgses, except for hhZ.
      // for (int i = 0; i < 5; i++)
      // {
      //   result.C_WW2[i] = result.compute_effective_coupling(i, std::pair<int,int>(24, 0), std::pair<int,int>(-24, 0));
      //   result.C_ZZ2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(23, 0));
      //   result.C_tt2[i] = result.compute_effective_coupling(i, std::pair<int,int>(6, 1), std::pair<int,int>(-6, 1));
      //   result.C_bb2[i] = result.compute_effective_coupling(i, std::pair<int,int>(5, 1), std::pair<int,int>(-5, 1));
      //   result.C_cc2[i] = result.compute_effective_coupling(i, std::pair<int,int>(4, 1), std::pair<int,int>(-4, 1));
      //   result.C_tautau2[i] = result.compute_effective_coupling(i, std::pair<int,int>(15, 1), std::pair<int,int>(-15, 1));
      //   result.C_gaga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(22, 0), std::pair<int,int>(22, 0));
      //   result.C_gg2[i] = result.compute_effective_coupling(i, std::pair<int,int>(21, 0), std::pair<int,int>(21, 0));
      //   result.C_mumu2[i] = result.compute_effective_coupling(i, std::pair<int,int>(13, 1), std::pair<int,int>(-13, 1));
      //   result.C_Zga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(21, 0));
      //   result.C_ss2[i] = result.compute_effective_coupling(i, std::pair<int,int>(3, 1), std::pair<int,int>(-3, 1));
      // }

      // Using mass eigenstate context pairs, not flavour
      for (int i = 0; i < 5; i++)
      {
        result.C_WW2[i] = result.compute_effective_coupling(i, std::pair<int,int>(24, 0), std::pair<int,int>(-24, 0));
        result.C_ZZ2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(23, 0));
        result.C_tt2[i] = result.compute_effective_coupling(i, std::pair<int,int>(6, 0), std::pair<int,int>(-6, 0));
        result.C_bb2[i] = result.compute_effective_coupling(i, std::pair<int,int>(5, 0), std::pair<int,int>(-5, 0));
        result.C_cc2[i] = result.compute_effective_coupling(i, std::pair<int,int>(4, 0), std::pair<int,int>(-4, 0));
        result.C_tautau2[i] = result.compute_effective_coupling(i, std::pair<int,int>(15, 0), std::pair<int,int>(-15, 0));
        result.C_gaga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(22, 0), std::pair<int,int>(22, 0));
        result.C_gg2[i] = result.compute_effective_coupling(i, std::pair<int,int>(21, 0), std::pair<int,int>(21, 0));
        result.C_mumu2[i] = result.compute_effective_coupling(i, std::pair<int,int>(13, 0), std::pair<int,int>(-13, 0));
        //result.C_Zga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(21, 0));
        // S.B. PDG code 22 for gamma? If so this is wrong in SpecBit_MSSM (this is Z+g which is Lorentz violating..?)
        result.C_Zga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(22, 0));
        result.C_ss2[i] = result.compute_effective_coupling(i, std::pair<int,int>(3, 0), std::pair<int,int>(-3, 0));
      }


      // Calculate hhZ effective couplings.  Here we scale out the kinematic prefactor
      // of the decay width, assuming we are well above threshold if the channel is open.
      // If not, we simply assume SM couplings.
      const double mZ = Dep::NMSSM_spectrum->get(Par::Pole_Mass,23,0);
      const double scaling = 8.*sqrt(2.)*pi/Dep::NMSSM_spectrum->get_SMInputs().GF;
      for(int i = 0; i < 5; i++)
      for(int j = 0; j < 5; j++)
      {
        double mhi = spec.get(Par::Pole_Mass, sHneut[i]);
        double mhj = spec.get(Par::Pole_Mass, sHneut[j]);
        if (mhi > mhj + mZ and result.get_neutral_decays(i).has_channel(sHneut[j], "Z0"))
        {
          double gamma = result.get_neutral_decays(i).width_in_GeV*result.get_neutral_decays(i).BF(sHneut[j], "Z0");
          double k[2] = {(mhj + mZ)/mhi, (mhj - mZ)/mhi};
          for (int l = 0; l < 2; l++) k[l] = (1.0 - k[l]) * (1.0 + k[l]);
          double K = mhi*sqrt(k[0]*k[1]);
          result.C_hiZ2[i][j] = scaling / (K*K*K) * gamma;
        }
        else // If the channel is missing from the decays or kinematically disallowed, just return the SM result.
        {
          result.C_hiZ2[i][j] = 1.;
        }
      }

      const HiggsCouplingsTable::h0_decay_array_type& h0_widths = result.get_neutral_decays_array(5);

      for (int i=0; i < 5; i++) 
      {
        for (auto it = h0_widths[i]->channels.begin(); it != h0_widths[i]->channels.end(); ++it)
        {
          std::multiset< std::pair<int,int> > ch = it->first;
          for (auto it2 = ch.begin(); it2 != ch.end(); ++it2) 
          {
            std::cout << Models::ParticleDB().partmap::long_name(*it2) << " ";
          }
          std::cout << std::endl;
        } std::cout << std::endl;

      }

      // Higgs BFs are to the SM mass eigenstates, not gauge eigenstates...
      for(int i = 0; i < 5; i++)
      {
        std::cout << "Higgs number: " << i+1 << std::endl << std::endl;
        std::cout << h0_widths[i]->width_in_GeV << std::endl;
        //std::cout << h0_widths[i]->BF("s", "sbar") << std::endl;
        // Only h0_1 seems to have any decays to s+sbar // c+cbar // W+W- ...
        //std::cout << h0_widths[i]->BF("d_2", "dbar_2") << std::endl;
        //std::cout << h0_widths[i]->BF("c", "cbar") << std::endl;
        //std::cout << h0_widths[i]->BF("u_2", "ubar_2") << std::endl;
        //std::cout << h0_widths[i]->BF("b", "bbar") << std::endl;
        std::cout << h0_widths[i]->BF("d_3", "dbar_3") << std::endl;
        //std::cout << h0_widths[i]->BF("mu+", "mu-") << std::endl;
        std::cout << h0_widths[i]->BF("e+_2", "e-_2") << std::endl;
        //std::cout << h0_widths[i]->BF("tau+", "tau-") << std::endl;
        std::cout << h0_widths[i]->BF("e+_3", "e-_3") << std::endl;
        std::cout << h0_widths[i]->BF("W+", "W-") << std::endl;
        std::cout << h0_widths[i]->BF("Z0", "Z0") << std::endl;
        // Z gamma doesn't seem to be there...?
        //std::cout << h0_widths[i]->BF("gamma", "Z0") << std::endl;
        std::cout << h0_widths[i]->BF("gamma", "gamma") << std::endl;
        std::cout << h0_widths[i]->BF("g", "g") << std::endl;
      }

      // todo
      // Work out which invisible decays are possible
      //result.invisibles = get_invisibles(spec);
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

