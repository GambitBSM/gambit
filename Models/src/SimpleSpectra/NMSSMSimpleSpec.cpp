//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
//
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2018 Oct
///
///  *********************************************

#include "gambit/Models/SimpleSpectra/NMSSMSimpleSpec.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/variadic_functions.hpp"
#include "gambit/Logs/logger.hpp"

#include <math.h>
#include <boost/lexical_cast.hpp>

using namespace SLHAea;

namespace Gambit
{

      /// @{ Member functions for SLHAeaModel class

      /// Default Constructor
      NMSSMea::NMSSMea()
        : MSSMea()
      {}

      /// Constructor via SLHAea object
      NMSSMea::NMSSMea(const SLHAea::Coll& input)
        : MSSMea(input)
      {
        // Nothing to do here, conversion from SLHA1 - SLHA2 is done by the MSSMEa constructor
      }

      /// @{ Getters for NMSSM-only information
      double NMSSMea::get_lambda()  const{ return getdata("NMSSMRUN",1); } // lam
      double NMSSMea::get_kappa()   const{ return getdata("NMSSMRUN",2); } // kap
      double NMSSMea::get_Tlambda() const{ return getdata("NMSSMRUN",3); } // Tlam
      double NMSSMea::get_Tkappa()  const{ return getdata("NMSSMRUN",4); } // Tk
      double NMSSMea::get_vS()      const{ return getdata("NMSSMRUN",5); } // vS 
      double NMSSMea::get_ms2()      const{ return getdata("NMSSMRUN",10); } // ms2


      double NMSSMea::get_Mhh_pole_slha(int i) const
      {
         if      (i==1){ return getdata("MASS",25); } // Neutral Higgs(1)
         else if (i==2){ return getdata("MASS",35); } // Neutral Higgs(2)
         else if (i==3){ return getdata("MASS",45); } // Neutral Higgs(3)
         else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_Mhh_pole_slha! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
      }

      double NMSSMea::get_MAh_pole_slha (int i) const
      {
         if      (i==1){ return getdata("MASS",36); } // CP-odd Neutral Higgs(1)
         else if (i==2){ return getdata("MASS",46); } // CP-odd Neutral Higgs(2)
         else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_Ahh_pole_slha! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
      }

      double NMSSMea::get_MChi_pole_slha(int i) const
      {
         if      (i==1){ return getdata("MASS",1000022); } // Neutralino(1)
         else if (i==2){ return getdata("MASS",1000023); } // Neutralino(2)
         else if (i==3){ return getdata("MASS",1000025); } // Neutralino(3)
         else if (i==4){ return getdata("MASS",1000035); } // Neutralino(4)
         else if (i==5){ return getdata("MASS",1000045); } // Neutralino(5)
         else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_MChi_pole_slha! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
      }

      /// @}


      /// @{ Member functions for MSSMSimpleSpec class

      /// @{ Constructors

      /// Default Constructor
      NMSSMSimpleSpec::NMSSMSimpleSpec(double uncert)
      {
        set_pole_mass_uncertainties(uncert);
      }

      /// Constructor via SLHAea object
      NMSSMSimpleSpec::NMSSMSimpleSpec(const SLHAea::Coll& input, double uncert)
        : SLHASimpleSpec(input)
      {
        set_pole_mass_uncertainties(uncert);
      }

      /// Copy constructor: needed by clone function.
      NMSSMSimpleSpec::NMSSMSimpleSpec(const NMSSMSimpleSpec& other, double uncert)
        : SLHASimpleSpec(other)
      {
        set_pole_mass_uncertainties(uncert);
      }

      /// @}

      /// Offset from user-input indices (user assumes 1,2,3 indexed, e.g. use offset=-1 for zero-indexing)
      int NMSSMSimpleSpec::get_index_offset() const {return 0.;} // we use indices starting from 1 in this file, matching user assumptions. (because Peter is god, he knows user assumptions before they do.)

      /// Add SLHAea object to another
      void NMSSMSimpleSpec::add_to_SLHAea(int slha_version, SLHAea::Coll& slha) const
      {
        // Add SPINFO data if not already present
        SLHAea_add_GAMBIT_SPINFO(slha);

        // All NMSSM blocks
        slhahelp::add_MSSM_spectrum_to_SLHAea(*this, slha, slha_version);

        // Add NMSSM specific blocks and entries

        // Block NMSSMRUN
        SLHAea_add_block(slha, "NMSSMRUN", GetScale());
        slha["NMSSMRUN"][""] << 1 << get(Par::dimensionless, "lambda") << "# lam";
        slha["NMSSMRUN"][""] << 2 << get(Par::dimensionless, "kappa")  << "# kap";
        slha["NMSSMRUN"][""] << 3 << get(Par::mass1, "Tlambda")  << "# Tlam";
        slha["NMSSMRUN"][""] << 4 << get(Par::mass1, "Tkappa")  << "# Tk";
        slha["NMSSMRUN"][""] << 5 << get(Par::mass1, "vS")  << "# vS";
        slha["NMSSMRUN"][""] << 10 << get(Par::mass2, "ms2")  << "# ms2";

        // Missing masses and couplings for the extra neutralino and higgses
        slha["MASS"][""] << 45 << get(Par::Pole_Mass, "h0", 3) << "# hh_3";
        slha["MASS"][""] << 46 << get(Par::Pole_Mass, "A0", 2) << "# Ah_2";
        slha["MASS"][""] << 1000045 << get(Par::Pole_Mass, "~chi0", 5) << "# Chi_5";
        for(int i=1; i<5; i++)
        {
          slha["NMIX"][""] << i << 5 << get(Par::Pole_Mixing, "~chi0", i, 5) << "~chi0 mixing matrix (" << i << ",5)";
          slha["NMIX"][""] << 5 << i << get(Par::Pole_Mixing, "~chi0", 5, i) << "~chi0 mixing matrix (5," << i << ")";
        }
        slha["NMIX"][""] << 5 << 5 << get(Par::Pole_Mixing, "~chi0", 5, 5) << "~chi0 mixing matrix (5,5)";

      }

      /// Retrieve the PDG translation map
      const std::map<int, int>& NMSSMSimpleSpec::PDG_translator() const { return slhawrap.PDG_translator(); }

      /// Set pole mass uncertainties
      void NMSSMSimpleSpec::set_pole_mass_uncertainties(double uncert)
      {
        const std::vector<int> i12        = initVector(1,2);
        const std::vector<int> i123       = initVector(1,2,3);
        const std::vector<int> i12345     = initVector(1,2,3,4,5);
        const std::vector<int> i123456    = initVector(1,2,3,4,5,6);
        const std::vector<str> sbosons1   = initVector<str>("~g","H+","H-","W+","W-");
        const std::vector<str> sbosons2   = initVector<str>("~chi+","~chi-","A0");
        const std::vector<str> sfermions1 = initVector<str>("~u","~d","~e-","~ubar","~dbar","~e+");
        const std::vector<str> sfermions2 = initVector<str>("~nu","~nubar");
        set_override_vector(Par::Pole_Mass_1srd_high, uncert, sfermions1, i123456, true);
        set_override_vector(Par::Pole_Mass_1srd_low,  uncert, sfermions1, i123456, true);
        set_override_vector(Par::Pole_Mass_1srd_high, uncert, sfermions2, i123, true);
        set_override_vector(Par::Pole_Mass_1srd_low,  uncert, sfermions2, i123, true);
        set_override_vector(Par::Pole_Mass_1srd_high, uncert, sbosons1, true);
        set_override_vector(Par::Pole_Mass_1srd_low,  uncert, sbosons1, true);
        set_override_vector(Par::Pole_Mass_1srd_high, uncert, sbosons2, i12, true);
        set_override_vector(Par::Pole_Mass_1srd_low,  uncert, sbosons2, i12, true);
        set_override_vector(Par::Pole_Mass_1srd_high, uncert, "h0", i123, true);
        set_override_vector(Par::Pole_Mass_1srd_low,  uncert, "h0", i123, true); 
        set_override_vector(Par::Pole_Mass_1srd_high, uncert, "~chi0", i12345, true);
        set_override_vector(Par::Pole_Mass_1srd_low,  uncert, "~chi0", i12345, true);
      }

      // Map fillers

      NMSSMSimpleSpec::GetterMaps NMSSMSimpleSpec::fill_getter_maps()
      {
         GetterMaps map_collection;

         typedef MTget::FInfo1 FInfo1;
         typedef MTget::FInfo2 FInfo2;

         // Can't use c++11 initialiser lists, se have to initialise the index sets like this.
         static const int i12v[] = {1,2};
         static const std::set<int> i12(i12v, Utils::endA(i12v));

         static const int i123v[] = {1,2,3};
         static const std::set<int> i123(i123v, Utils::endA(i123v));

         static const int i12345v[] = {1,2,3,4,5};
         static const std::set<int> i12345(i12345v, Utils::endA(i12345v));

         static const int i123456v[] = {1,2,3,4,5,6};
         static const std::set<int> i123456(i123456v, Utils::endA(i123456v));

         // Running parameters
         {
            MTget::fmap0 tmp_map;
            tmp_map["mHd2"] = &Model::get_mHd2;
            tmp_map["mHu2"] = &Model::get_mHu2;
            tmp_map["ms2"]  = &Model::get_ms2;
            map_collection[Par::mass2].map0 = tmp_map;
         }
         {
            MTget::fmap2 tmp_map;
            tmp_map["mq2"] = FInfo2( &Model::get_mq2, i123, i123);
            tmp_map["ml2"] = FInfo2( &Model::get_ml2, i123, i123);
            tmp_map["md2"] = FInfo2( &Model::get_md2, i123, i123);
            tmp_map["mu2"] = FInfo2( &Model::get_mu2, i123, i123);
            tmp_map["me2"] = FInfo2( &Model::get_me2, i123, i123);
            map_collection[Par::mass2].map2 = tmp_map;
         }
         {
            MTget::fmap0 tmp_map;
            tmp_map["M1"]= &Model::get_MassB;
            tmp_map["M2"]= &Model::get_MassWB;
            tmp_map["M3"]= &Model::get_MassG;
            tmp_map["Mu"]= &Model::get_Mu;
            tmp_map["vu"]= &Model::get_vu;
            tmp_map["vd"]= &Model::get_vd;
            tmp_map["vS"]= &Model::get_vS;
            tmp_map["Tlambda"] = &Model::get_Tlambda;
            tmp_map["Tkappa"]  = &Model::get_Tkappa;
            map_collection[Par::mass1].map0 = tmp_map;
         }
         {
            MTget::fmap2 tmp_map;
            tmp_map["TYd"]= FInfo2( &Model::get_TYd, i123, i123);
            tmp_map["TYe"]= FInfo2( &Model::get_TYe, i123, i123);
            tmp_map["TYu"]= FInfo2( &Model::get_TYu, i123, i123);
            tmp_map["ad"] = FInfo2( &Model::get_TYd, i123, i123);
            tmp_map["ae"] = FInfo2( &Model::get_TYe, i123, i123);
            tmp_map["au"] = FInfo2( &Model::get_TYu, i123, i123);
            map_collection[Par::mass1].map2 = tmp_map;
         }
         {
            MTget::fmap0 tmp_map;
            tmp_map["g1"]= &Model::get_g1;
            tmp_map["g2"]= &Model::get_g2;
            tmp_map["g3"]= &Model::get_g3;
            tmp_map["tanbeta"]= &Model::get_tanbeta;
            tmp_map["tanbeta(mZ)"]= &Model::get_tanbeta_mZ; // Special entry for reproducing MINPAR entry in SLHA
            tmp_map["sinW2"]= &Model::get_sinthW2_DRbar;
            tmp_map["lambda"]   = &Model::get_lambda;
            tmp_map["kappa"]   = &Model::get_kappa;
            map_collection[Par::dimensionless].map0 = tmp_map;
         }
         {
            MTget::fmap2 tmp_map;
            tmp_map["Yd"]= FInfo2( &Model::get_Yd, i123, i123);
            tmp_map["Yu"]= FInfo2( &Model::get_Yu, i123, i123);
            tmp_map["Ye"]= FInfo2( &Model::get_Ye, i123, i123);
            map_collection[Par::dimensionless].map2 = tmp_map;
         }

         // "Physical" parameters
         {
            MTget::fmap0 tmp_map;
            tmp_map["~g"] = &Model::get_MGlu_pole;
            tmp_map["H+"] = &Model::get_MHpm_pole;
            // Antiparticle label
            tmp_map["H-"] = &Model::get_MHpm_pole;
            tmp_map["W+"] = &Model::get_MW_pole;
            map_collection[Par::Pole_Mass].map0 = tmp_map;
         }
         {
            MTget::fmap1 tmp_map;
            tmp_map["~d"] =    FInfo1( &Model::get_MSd_pole_slha, i123456 );
            tmp_map["~u"] =    FInfo1( &Model::get_MSu_pole_slha, i123456 );
            tmp_map["~e-"] =   FInfo1( &Model::get_MSe_pole_slha, i123456 );
            tmp_map["~nu"] =   FInfo1( &Model::get_MSv_pole_slha, i123 );
            tmp_map["A0"] =    FInfo1( &Model::get_MAh_pole_slha, i12 );
            tmp_map["h0"] =    FInfo1( &Model::get_Mhh_pole_slha, i123 );
            tmp_map["~chi+"] = FInfo1( &Model::get_MCha_pole_slha, i12 );
            tmp_map["~chi0"] = FInfo1( &Model::get_MChi_pole_slha, i12345 );

            // Antiparticles (same getters, just different string name)
            tmp_map["~dbar"] = FInfo1( &Model::get_MSd_pole_slha, i123456 );
            tmp_map["~ubar"] = FInfo1( &Model::get_MSu_pole_slha, i123456 );
            tmp_map["~e+"]   = FInfo1( &Model::get_MSe_pole_slha, i123456 );
            tmp_map["~nubar"]= FInfo1( &Model::get_MSv_pole_slha, i123 );
            tmp_map["~chi-"] = FInfo1( &Model::get_MCha_pole_slha, i12 );
            map_collection[Par::Pole_Mass].map1 = tmp_map;
         }
         {
            MTget::fmap2 tmp_map;
            tmp_map["~d"] =    FInfo2( &Model::get_ZD_pole_slha, i123456, i123456);
            tmp_map["~nu"] =   FInfo2( &Model::get_ZV_pole_slha, i123, i123);
            tmp_map["~u"] =    FInfo2( &Model::get_ZU_pole_slha, i123456, i123456);
            tmp_map["~e-"]=    FInfo2( &Model::get_ZE_pole_slha, i123456, i123456);
            tmp_map["h0"] =    FInfo2( &Model::get_ZH_pole_slha, i123, i123);
            tmp_map["A0"] =    FInfo2( &Model::get_ZA_pole_slha, i123, i123);
            tmp_map["H+"] =    FInfo2( &Model::get_ZP_pole_slha, i12, i12);
            tmp_map["~chi0"] = FInfo2( &Model::get_ZN_pole_slha, i12345, i12345);
            tmp_map["~chi-"] = FInfo2( &Model::get_UM_pole_slha, i12, i12);
            tmp_map["~chi+"] = FInfo2( &Model::get_UP_pole_slha, i12, i12);
            map_collection[Par::Pole_Mixing].map2 = tmp_map;
         }

         return map_collection;
      }


} // end Gambit namespace


