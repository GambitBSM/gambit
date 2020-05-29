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
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Apr
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2016 Oct
///
///  *********************************************

#include "gambit/Models/SimpleSpectra/MSSMSimpleSpec.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/variadic_functions.hpp"
#include "gambit/Logs/logger.hpp"

#include <math.h>
#include <boost/lexical_cast.hpp>

using namespace SLHAea;

namespace Gambit
{

      /// Helper function for sorting int, double pairs according to the double
      bool orderer (std::pair<int, double> a, std::pair<int, double> b) { return a.second < b.second; }

      /// @{ Member functions for SLHAeaModel class

      /// Default Constructor
      MSSMea::MSSMea()
        : SLHAeaModel()
      {}

      /// Constructor via SLHAea object
      MSSMea::MSSMea(const SLHAea::Coll& input)
        : SLHAeaModel(input)
      {
        std::map<int, int>& slha1to2 = PDG_translation_map;
        str blocks[4] = {"DSQMIX", "USQMIX", "SELMIX", "SNUMIX"};
        str gen3mix[3] = {"SBOTMIX", "STOPMIX", "STAUMIX"};
        logger() << LogTags::utils;

        // Work out if this SLHAea object is SLHA1 or SLHA2
        if (data.find(blocks[0]) == data.end() or
            data.find(blocks[1]) == data.end() or
            data.find(blocks[2]) == data.end() or
            data.find(blocks[3]) == data.end() )
        {
          if (data.find(gen3mix[0]) == data.end() or
              data.find(gen3mix[1]) == data.end() or
              data.find(gen3mix[2]) == data.end() )
          {
            utils_error().raise(LOCAL_INFO, "Input SLHA data appears to be neither SLHA1 nor SLHA2.");
          }
          logger() << "Input SLHA for setting up simple spectrum is SLHA1.  You old dog." << EOM;

          // Get scale, needed for specifying SLHA2 blocks
          /// TODO: Currently assumes all blocks at same scale. Should check if this
          /// is true.
          double scale = 0.0;
          try
          {
            scale = SLHAea::to<double>(data.at("GAUGE").find_block_def()->at(3));
          }
          catch (const std::out_of_range& e)
          {
            std::ostringstream errmsg;
            errmsg << "Could not find block \"GAUGE\" in SLHAea object (required to retrieve scale Q). Received out_of_range error with message: " << e.what();
            utils_error().raise(LOCAL_INFO,errmsg.str());
          }

          //Looks like it is SLHA1, so convert it to SLHA2.
          int lengths[4] = {6, 6, 6, 3};
          str names[4] = {"~d_", "~u_", "~l_", "~nu_"};
          std::vector<int> pdg[4];
          std::vector< std::pair<int, double> > masses[4];
          pdg[0] = initVector<int>(1000001, 1000003, 1000005, 2000001, 2000003, 2000005); // d-type squarks
          pdg[1] = initVector<int>(1000002, 1000004, 1000006, 2000002, 2000004, 2000006); // u-type squarks
          pdg[2] = initVector<int>(1000011, 1000013, 1000015, 2000011, 2000013, 2000015); // sleptons
          pdg[3] = initVector<int>(1000012, 1000014, 1000016);                            // sneutrinos
          for (int j = 0; j < 4; j++)
          {
            // Get the masses
            for (int i = 0; i < lengths[j]; i++) masses[j].push_back(std::pair<int, double>(pdg[j][i], getdata("MASS",pdg[j][i])));

            // Sort them
            std::sort(masses[j].begin(), masses[j].end(), orderer);

            // Rewrite them in correct order, and populate the pdg-pdg maps
            for (int i = 0; i < lengths[j]; i++)
            {
              //data["MASS"][pdg[j][i]][1] = boost::lexical_cast<str>(masses[j][i].second);
              //data["MASS"][pdg[j][i]][2] = "# "+names[j]+boost::lexical_cast<str>(i+1);
              str masspdg = boost::lexical_cast<str>(masses[j][i].second);
              str comment = "# "+names[j]+boost::lexical_cast<str>(i+1);
              SLHAea_add(data, "MASS", pdg[j][i], masspdg, comment, true);
              slha1to2[masses[j][i].first] = pdg[j][i];
            }

            // Write the mixing block.  i is the SLHA2 index, k is the SLHA1 index.
            //data[blocks[j]][""] << "BLOCK" << blocks[j];
            SLHAea_check_block(data, blocks[j]);
            for (int i = 0; i < lengths[j]; i++) for (int k = 0; k < lengths[j]; k++)
            {
              double datum;
              if (lengths[j] == 3 or (k != 2 and k != 5)) // first or second generation (or neutrinos)
              {
                datum = (slha1to2.at(pdg[j][k]) == pdg[j][i]) ? 1.0 : 0.0;
              }
              else // third generation => need to use the 2x2 SLHA1 mixing matrices.
              {
                double family_index = 0;
                if (k == 2)
                {
                  if (slha1to2.at(pdg[j][k]) == pdg[j][i]) family_index = 1;
                  else if (slha1to2.at(pdg[j][5]) == pdg[j][i]) family_index = 2;
                }
                else if (k == 5)
                {
                  if (slha1to2.at(pdg[j][k]) == pdg[j][i]) family_index = 2;
                  else if (slha1to2.at(pdg[j][2]) == pdg[j][i]) family_index = 1;
                }
                if (family_index > 0)
                {
                  datum = getdata(gen3mix[j], family_index, (k+1)/3);
                }
                else datum = 0.0;
              }
              //data[blocks[j]][""] << i+1 << k+1 << datum << "# "+blocks[j]+boost::lexical_cast<str>(i*10+k+11);
              SLHAea_add(data, blocks[j], i+1, k+1, datum, "# "+blocks[j]+boost::lexical_cast<str>(i*10+k+11), true);
            }

          }
          // Now deal with MSOFT --> SLHA2 soft mass matrix blocks
          // (inverse of retrieval code in add_MSSM_spectrum_to_SLHAea) 
          sspair M[5] = {sspair("MSL2","ml2"), sspair("MSE2","me2"), sspair("MSQ2","mq2"), sspair("MSU2","mu2"), sspair("MSD2","md2")};
          for (int k=0;k<5;k++)
          {
            std::string block(M[k].first);
            if(not SLHAea_block_exists(data, block)) SLHAea_add_block(data, block, scale); //TODO: maybe just always delete and replace
            for(int i=1;i<4;i++) for(int j=1;j<4;j++)
            {
              std::ostringstream comment;
              comment << block << "(" << i << "," << j << ")";
              double entry;
              if(i==j)
              {
                entry = getdata("MSOFT",30+3*k+i+(k>1?4:0)); // black magic to get correct index in MSOFT matching diagonal elements
              }
              else
              {
                // Everything off-diagonal is zero in SLHA1
                entry = 0;
              }
              //data[block][""] << i << j << entry*entry << "# "+comment.str();
              SLHAea_add(data, block, i, j, entry*entry, "# "+comment.str(), true);
            }
          }

          // Yukawa and trilinear blocks.  YU, YD and YE, plus [YU, YD and YE; SLHA1 only], or [TU, TD and TE; SLHA2 only].
          sspair A[3] = {sspair("AU","Au"), sspair("AD","Ad"), sspair("AE","Ae")};
          sspair Y[3] = {sspair("YU","Yu"), sspair("YD","Yd"), sspair("YE","Ye")};
          sspair T[3] = {sspair("TU","TYu"), sspair("TD","TYd"), sspair("TE","TYe")};
          for (int k=0;k<3;k++)
          {
            SLHAea_check_block(data, A[k].first);
            SLHAea_check_block(data, Y[k].first);
            SLHAea_check_block(data, T[k].first); // TODO: should delete superceded slha1 "A" blocks?
            for(int i=1;i<4;i++)
            {
              for(int j=1;j<4;j++)
              {
                std::ostringstream comment;
                comment << "(" << i << "," << j << ")";
                // SLHA1 has only diagonal elements in Y and A. We should fill them out fully.
                // Assume missing diagonal elements are also zero.
                double Yentry;
                double Aentry;
                if(i==j)
                {
                  if(SLHAea_check_block(data,Y[k].first,i,j))
                  {
                    Yentry = getdata(Y[k].first,i,j);
                  }
                  else
                  {
                    Yentry = 0;
                  }

                  if(SLHAea_check_block(data,A[k].first,i,j))
                  {
                    Aentry = getdata(A[k].first,i,j);
                  }
                  else
                  {
                    Aentry = 0;
                  }
                }
                else
                {
                  Yentry = 0;
                  Aentry = 0;
                }
              
                double Tentry = Aentry * Yentry;
                SLHAea_add(data, Y[k].first, i, j, Yentry, "# "+Y[k].first+"_"+comment.str(), true);
                SLHAea_add(data, A[k].first, i, j, Aentry, "# "+A[k].first+"_"+comment.str(), true);
                SLHAea_add(data, T[k].first, i, j, Tentry, "# "+T[k].first+"_"+comment.str(), true);
              }
            }
          }


        }

        else logger() << "Input SLHA data for setting up simple spectrum is SLHA2.  *living in the future*" << EOM;
        // In the end, we should always have converted to SLHA2 by now, so set this as the internally-tracked version.
        wrapped_slha_version = 2;
      }

      /// @{ Getters for MSSM information
      double MSSMea::get_Mu()      const{ return getdata("HMIX",1); } // mu(Q) DRbar
      double MSSMea::get_tanbeta() const{ return getdata("HMIX",2); } // tan beta(Q) DRbar ( = vu/vd)
      double MSSMea::get_tanbeta_mZ() const{ return getdata("MINPAR",3); } // tan beta(mZ) DRbar
      double MSSMea::get_v()       const{ return getdata("HMIX",3); } // v = sqrt(vd^2 + vu^2) DRbar
      double MSSMea::get_mA2()     const{ return getdata("HMIX",4); } // m^2_A=[m3^2/cosBsinB](Q) DRbar, tree
      ////// THESE ARE NOT SLHA! Therefore cannot rely on them being in the SLHAea object.
      ////// But we can compute them instead.
      // double MSSMea::get_BMu()     const { return getdata("HMIX",101); }
      // double MSSMea::get_vd()      const { return getdata("HMIX",102); }
      // double MSSMea::get_vu()      const { return getdata("HMIX",103); }
      ///////
      double MSSMea::get_BMu() const 
      {
        double tb = get_tanbeta();
        double cb = cos(atan(tb));
        double sb = sin(atan(tb));
        return get_mA2() * (sb * cb);
      }
      double MSSMea::get_vd() const 
      {
        double v = get_v();
        double tb = get_tanbeta();
        return sqrt(abs( v*v / ( tb*tb + 1 ) ));
      }
      double MSSMea::get_vu() const
      {
        double v = get_v();
        double itb = 1./get_tanbeta();
        return sqrt(abs( v*v / ( itb*itb + 1 ) )); 
      }

      double MSSMea::get_MassB () const { return getdata("MSOFT",1); }
      double MSSMea::get_MassWB() const { return getdata("MSOFT",2); }
      double MSSMea::get_MassG () const { return getdata("MSOFT",3); }
      double MSSMea::get_mHd2() const { return getdata("MSOFT",21); }
      double MSSMea::get_mHu2() const { return getdata("MSOFT",22); }

      double MSSMea::get_mq2(int i, int j) const { return getdata("MSQ2",i,j); }
      double MSSMea::get_ml2(int i, int j) const { return getdata("MSL2",i,j); }
      double MSSMea::get_md2(int i, int j) const { return getdata("MSD2",i,j); }
      double MSSMea::get_mu2(int i, int j) const { return getdata("MSU2",i,j); }
      double MSSMea::get_me2(int i, int j) const { return getdata("MSE2",i,j); }

      double MSSMea::get_TYd(int i, int j) const { return getdata("Td",i,j); }
      double MSSMea::get_TYu(int i, int j) const { return getdata("Tu",i,j); }
      double MSSMea::get_TYe(int i, int j) const { return getdata("Te",i,j); }

      double MSSMea::get_ad(int i, int j) const { return getdata("Ad",i,j); }
      double MSSMea::get_au(int i, int j) const { return getdata("Au",i,j); }
      double MSSMea::get_ae(int i, int j) const { return getdata("Ae",i,j); }

      double MSSMea::get_Yd(int i, int j) const { return getdata("Yd",i,j); }
      double MSSMea::get_Yu(int i, int j) const { return getdata("Yu",i,j); }
      double MSSMea::get_Ye(int i, int j) const { return getdata("Ye",i,j); }

      double MSSMea::get_g1() const { return getdata("GAUGE",1)/sqrt(3./5.); } // Convert from gy (in SLHAea object) to g1
      double MSSMea::get_g2() const { return getdata("GAUGE",2); }
      double MSSMea::get_g3() const { return getdata("GAUGE",3); }
      double MSSMea::get_sinthW2_DRbar() const
      {
        double sg1 = 0.6 * Utils::sqr(get_g1());
        return sg1 / (sg1 + Utils::sqr(get_g2()));
      }

      double MSSMea::get_MGlu_pole() const { return getdata("MASS",1000021); }

      double MSSMea::get_Mhh_pole_slha(int i) const
      {
         if      (i==1){ return getdata("MASS",25); } // Neutral Higgs(1)
         else if (i==2){ return getdata("MASS",35); } // Neutral Higgs(2)
         else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_Mhh_pole_slha! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
      }
      double MSSMea::get_MAh_pole () const { return getdata("MASS",36); }
      double MSSMea::get_MHpm_pole() const { return getdata("MASS",37); }
      double MSSMea::get_MW_pole()    const { return getdata("MASS",24); } // REQUIRED output of MSSM-compatible subspectrum

      double MSSMea::get_MCha_pole_slha(int i) const
      {
         if      (i==1){ return getdata("MASS",1000024); } // Chargino(1)
         else if (i==2){ return getdata("MASS",1000037); } // Chargino(2)
         else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_MCha_pole_slha! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
      }
      double MSSMea::get_MSd_pole_slha(int i) const
      {
         static std::map<int,int> match;

         if      (i==1){ return getdata("MASS",1000001); } // d-type squark(1)
         else if (i==2){ return getdata("MASS",1000003); } // d-type squark(2)
         else if (i==3){ return getdata("MASS",1000005); } // d-type squark(3)
         else if (i==4){ return getdata("MASS",2000001); } // d-type squark(4)
         else if (i==5){ return getdata("MASS",2000003); } // d-type squark(5)
         else if (i==6){ return getdata("MASS",2000005); } // d-type squark(6)
         else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_MSd_pole_slha! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
      }
      double MSSMea::get_MSu_pole_slha(int i) const
      {
         if      (i==1){ return getdata("MASS",1000002); } // u-type squark(1)
         else if (i==2){ return getdata("MASS",1000004); } // u-type squark(2)
         else if (i==3){ return getdata("MASS",1000006); } // u-type squark(3)
         else if (i==4){ return getdata("MASS",2000002); } // u-type squark(4)
         else if (i==5){ return getdata("MASS",2000004); } // u-type squark(5)
         else if (i==6){ return getdata("MASS",2000006); } // u-type squark(6)
         else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_MSd_pole_slha! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
      }
      double MSSMea::get_MSe_pole_slha(int i) const
      {
         if      (i==1){ return getdata("MASS",1000011); } // charged slepton(1)
         else if (i==2){ return getdata("MASS",1000013); } // charged slepton(2)
         else if (i==3){ return getdata("MASS",1000015); } // charged slepton(3)
         else if (i==4){ return getdata("MASS",2000011); } // charged slepton(4)
         else if (i==5){ return getdata("MASS",2000013); } // charged slepton(5)
         else if (i==6){ return getdata("MASS",2000015); } // charged slepton(6)
         else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_MSd_pole_slha! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
      }
      double MSSMea::get_MSv_pole_slha(int i) const
      {
         if      (i==1){ return getdata("MASS",1000012); } // Sneutrino(1)
         else if (i==2){ return getdata("MASS",1000014); } // Sneutrino(2)
         else if (i==3){ return getdata("MASS",1000016); } // Sneutrino(3)
         else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_MSd_pole_slha! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
      }
      double MSSMea::get_MChi_pole_slha(int i) const
      {
         if      (i==1){ return getdata("MASS",1000022); } // Neutralino(1)
         else if (i==2){ return getdata("MASS",1000023); } // Neutralino(2)
         else if (i==3){ return getdata("MASS",1000025); } // Neutralino(3)
         else if (i==4){ return getdata("MASS",1000035); } // Neutralino(4)
         else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_MChi_pole_slha! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
      }

      // Pole Mixings
      double MSSMea::get_ZD_pole_slha(int i, int j) const { return getdata("DSQMIX",i,j); }
      double MSSMea::get_ZU_pole_slha(int i, int j) const { return getdata("USQMIX",i,j); }

      double MSSMea::get_ZV_pole_slha(int i, int j) const { return getdata("SNUMIX",i,j); }
      double MSSMea::get_ZE_pole_slha(int i, int j) const { return getdata("SELMIX",i,j); }

      double MSSMea::get_ZH_pole_slha(int i, int j) const { return getdata("SCALARMIX",i,j); }
      double MSSMea::get_ZA_pole_slha(int i, int j) const { return getdata("PSEUDOSCALARMIX",i,j); }

      double MSSMea::get_ZP_pole_slha(int i, int j) const { return getdata("CHARGEMIX",i,j); }
      double MSSMea::get_ZN_pole_slha(int i, int j) const { return getdata("NMIX",i,j); }

      double MSSMea::get_UM_pole_slha(int i, int j) const { return getdata("UMIX",i,j); }
      double MSSMea::get_UP_pole_slha(int i, int j) const { return getdata("VMIX",i,j); }

      /// @}


      /// @{ Member functions for MSSMSimpleSpec class

      /// @{ Constructors

      /// Default Constructor
      MSSMSimpleSpec::MSSMSimpleSpec(double uncert)
      {
        set_pole_mass_uncertainties(uncert);
      }

      /// Constructor via SLHAea object
      MSSMSimpleSpec::MSSMSimpleSpec(const SLHAea::Coll& input, double uncert)
        : SLHASimpleSpec(input)
      {
        set_pole_mass_uncertainties(uncert);
      }

      /// Copy constructor: needed by clone function.
      MSSMSimpleSpec::MSSMSimpleSpec(const MSSMSimpleSpec& other, double uncert)
        : SLHASimpleSpec(other)
      {
        set_pole_mass_uncertainties(uncert);
      }

      /// @}

      /// Ofset from user-input indices (user assumes 1,2,3 indexed, e.g. use offset=-1 for zero-indexing)
      int MSSMSimpleSpec::get_index_offset() const {return 0.;} // we use indices starting from 1 in this file, matching user assumptions. (because Peter is god, he knows user assumptions before they do.)

      /// Retrieve SLHAea object 
      // NOTE! No need to write this function, SubSpectrum base class can handle it if add_to_SLHAea exists.
      //SLHAea::Coll MSSMSimpleSpec::getSLHAea(int slha_version) const 

      /// Add SLHAea object to another
      void MSSMSimpleSpec::add_to_SLHAea(int slha_version, SLHAea::Coll& slha) const
      {
        // Add SPINFO data if not already present
        SLHAea_add_GAMBIT_SPINFO(slha);

        // All MSSM blocks
        slhahelp::add_MSSM_spectrum_to_SLHAea(*this, slha, slha_version);
      }

      /// Retrieve the PDG translation map
      const std::map<int, int>& MSSMSimpleSpec::PDG_translator() const { return slhawrap.PDG_translator(); }

      /// Set pole mass uncertainties
      void MSSMSimpleSpec::set_pole_mass_uncertainties(double uncert)
      {
        const std::vector<int> i12        = initVector(1,2);
        const std::vector<int> i123       = initVector(1,2,3);
        const std::vector<int> i1234      = initVector(1,2,3,4);
        const std::vector<int> i123456    = initVector(1,2,3,4,5,6);
        const std::vector<str> sbosons1   = initVector<str>("~g","A0","H+","H-","W+","W-");
        const std::vector<str> sbosons2   = initVector<str>("~chi+","~chi-","h0");
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
        set_override_vector(Par::Pole_Mass_1srd_high, uncert, "~chi0", i1234, true);
        set_override_vector(Par::Pole_Mass_1srd_low,  uncert, "~chi0", i1234, true);
      }

      // Map fillers

      MSSMSimpleSpec::GetterMaps MSSMSimpleSpec::fill_getter_maps()
      {
         GetterMaps map_collection;

         typedef MTget::FInfo1 FInfo1;
         typedef MTget::FInfo2 FInfo2;

         // Can't use c++11 initialiser lists, se have to initialise the index sets like this.
         static const int i12v[] = {1,2};
         static const std::set<int> i12(i12v, Utils::endA(i12v));

         static const int i123v[] = {1,2,3};
         static const std::set<int> i123(i123v, Utils::endA(i123v));

         static const int i1234v[] = {1,2,3,4};
         static const std::set<int> i1234(i1234v, Utils::endA(i1234v));

         static const int i123456v[] = {1,2,3,4,5,6};
         static const std::set<int> i123456(i123456v, Utils::endA(i123456v));

         // Running parameters
         {
            MTget::fmap0 tmp_map;
            tmp_map["BMu"] = &Model::get_BMu;
            tmp_map["mA2"] = &Model::get_mA2;
            tmp_map["mHd2"] = &Model::get_mHd2;
            tmp_map["mHu2"] = &Model::get_mHu2;
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
            map_collection[Par::mass1].map0 = tmp_map;
         }
         {
            MTget::fmap2 tmp_map;
            tmp_map["TYd"]= FInfo2( &Model::get_TYd, i123, i123);
            tmp_map["TYe"]= FInfo2( &Model::get_TYe, i123, i123);
            tmp_map["TYu"]= FInfo2( &Model::get_TYu, i123, i123);
            tmp_map["ad"] = FInfo2( &Model::get_ad, i123, i123);
            tmp_map["ae"] = FInfo2( &Model::get_ae, i123, i123);
            tmp_map["au"] = FInfo2( &Model::get_au, i123, i123);
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
            tmp_map["A0"] = &Model::get_MAh_pole;
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
            tmp_map["h0"] =    FInfo1( &Model::get_Mhh_pole_slha, i12 );
            tmp_map["~chi+"] = FInfo1( &Model::get_MCha_pole_slha, i12 );
            tmp_map["~chi0"] = FInfo1( &Model::get_MChi_pole_slha, i1234 );

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
            tmp_map["h0"] =    FInfo2( &Model::get_ZH_pole_slha, i12, i12);
            tmp_map["A0"] =    FInfo2( &Model::get_ZA_pole_slha, i12, i12);
            tmp_map["H+"] =    FInfo2( &Model::get_ZP_pole_slha, i12, i12);
            tmp_map["~chi0"] = FInfo2( &Model::get_ZN_pole_slha, i1234, i1234);
            tmp_map["~chi-"] = FInfo2( &Model::get_UM_pole_slha, i12, i12);
            tmp_map["~chi+"] = FInfo2( &Model::get_UP_pole_slha, i12, i12);
            map_collection[Par::Pole_Mixing].map2 = tmp_map;
         }

         return map_collection;
      }


} // end Gambit namespace


