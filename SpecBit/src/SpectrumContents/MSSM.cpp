//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class defining the parameters that SubSpectrum
///  objects providing MSSM spectrum data must provide
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Ben Farmer
///          (benjamin.farmer@imperial.ac.uk)
///  \date 2016 Feb, 2019 June, Oct
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Oct
///
///  *********************************************

#ifndef __mssmcontents_hpp__
#define __mssmcontents_hpp__

#include "gambit/Elements/slhaea_helpers.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/SpecBit/RegisteredSpectra.hpp"
#include "gambit/Logs/logger.hpp"
#include "SLHAea/slhaea.h"

namespace Gambit {

  /// Helper function for sorting int, double pairs according to the double
  bool orderer (std::pair<int, double> a, std::pair<int, double> b) { return a.second < b.second; }

  /// @{ Helper functions to do extra error checking for SLHAea object contents
  /// Used to be in SLHASimpleSpec wrapper. Needed for SLHA1->2 translation routines
  
  /// One index
  double getdata(const std::string& local_info, const SLHAstruct& data, const std::string& block, int index)
  {
     double output = 0.0;
     try
     {
       output = SLHAea::to<double>(data.at(block).at(index).at(1));
     }
     catch (const std::out_of_range& e)
     {
       std::ostringstream errmsg;
       errmsg << "Error accessing data at index "<<index<<" of block "<<block<<". Please check that the input SLHAea object was properly filled." << std::endl;
       errmsg << "Dumping received SLHAea object to file 'scratch/slhaea_access_debug.slha'" << std::endl;
       errmsg  << "(Received out_of_range error from SLHAea class with message: " << e.what() << ")";
       std::ofstream ofs("scratch/slhaea_access_debug.slha");
       ofs << data;
       ofs.close();
       utils_error().raise(local_info,errmsg.str());
     }
     return output;
  }

  /// Two indices
  double getdata(const std::string& local_info, const SLHAstruct& data, const std::string& block, int i, int j)
  {
     double output = 0.0;
     try
     {
       output = SLHAea::to<double>(data.at(block).at(i,j).at(2));
     }
     catch (const std::out_of_range& e)
     {
       std::ostringstream errmsg;
       errmsg << "Error accessing data at index "<<i<<","<<j<<" of block "<<block<<". Please check that the SLHAea object was properly filled." << std::endl;
       errmsg << "Dumping received SLHAea object to file 'scratch/slhaea_access_debug.slha'" << std::endl;
       errmsg  << "(Received out_of_range error from SLHAea class with message: " << e.what() << ")";
       std::ofstream ofs("scratch/slhaea_access_debug.slha");
       ofs << data;
       ofs.close();
       utils_error().raise(local_info,errmsg.str());
     }
     return output;
  }

  /// @}
 
  /// Contents defined via constructor
  SpectrumContents::MSSM::MSSM()
   : Contents("MSSM")
  {
     addAllFrom(SM_slha()); 

     // shape prototypes
     std::vector<int> scalar; // Empty vector, i.e. no indices, i.e.. get(Par::Tag, "name")
     std::vector<int> v2     = initVector(2);   // i.e. get(Par::Tag, "name", i)
     std::vector<int> v3     = initVector(3);   // "
     std::vector<int> v4     = initVector(4);   // "
     std::vector<int> v6     = initVector(6);   // "
     std::vector<int> m2x2   = initVector(2,2); // i.e. get(Par::Tag, "name", i, j)
     std::vector<int> m3x3   = initVector(3,3); // "
     std::vector<int> m4x4   = initVector(4,4); // "
     std::vector<int> m6x6   = initVector(6,6); // "

     /// Set transformation functions for SLHA input/output
     setInputTransform(&MSSM::transformInputSLHAea);
     setOutputTransform(&MSSM::generateOutputSLHAea);

     //           tag,        name,   shape
     addParameter(Par::mass2, "BMu" , scalar, "BMu", 1); // TODO: Made this up// PA: I believe BMu is not in  the output SLHA file, instead mADRbar^2 = BMu / s_\beta c_\beta is in HMIX block.  How do we handle this?
     addParameter(Par::mass2, "mHd2", scalar, "MSOFT", 21);
     addParameter(Par::mass2, "mHu2", scalar, "MSOFT", 22);

     addParameter(Par::mass2, "mq2", m3x3, "MSQ2"); 
     addParameter(Par::mass2, "ml2", m3x3, "MSL2");
     addParameter(Par::mass2, "md2", m3x3, "MSD2");
     addParameter(Par::mass2, "mu2", m3x3, "MSU2");
     addParameter(Par::mass2, "me2", m3x3, "MSE2");

     addParameter(Par::mass1, "M1", scalar, "MSOFT", 1);
     addParameter(Par::mass1, "M2", scalar, "MSOFT", 2);
     addParameter(Par::mass1, "M3", scalar, "MSOFT", 3);
     addParameter(Par::mass1, "Mu", scalar, "HMIX", 1); // mu(Q) DRbar, I think
     addParameter(Par::mass1, "vev",scalar, "HMIX", 3);
     addParameter(Par::mass1, "vu", scalar, "VEVS", 1); 
     addParameter(Par::mass1, "vd", scalar, "VEVS", 2);

     // trilinears T_{ij} = Y_{ij} A_{ij} (no sum on i,j)
     addParameter(Par::mass1, "TYd", m3x3, "TD"); 
     addParameter(Par::mass1, "TYe", m3x3, "TE");
     addParameter(Par::mass1, "TYu", m3x3, "TU");

     // EXTRAS! Kind of logical to always include these, without forcing users to calculate them themselves
     addParameter(Par::dimensionless, "tanbeta", scalar, "HMIX", 2); // DRBAR tanbeta
     //addParameter(Par::dimensionless, "tanbeta(mZ)", scalar); // i.e. the SLHA MINPAR value of tanbeta(mZ). Not yet a strict requirement, but highly recommended for wrappers to add it via override setters. TODO: Make this compulsory?
     addParameter(Par::mass2, "mA2" , scalar, "HMIX", 4);
     //

     addParameter(Par::dimensionless, "g1", scalar, "GAUGE", 4); // TODO: I forget if our g1,g2,g3 definitions are g',g,g3 like in SLHA. Check this.
                                                                 // I'm pretty sure no. See below for conversion. Will put converted value in entry 4 rather than 1. 
     addParameter(Par::dimensionless, "g2", scalar, "GAUGE", 2);
     addParameter(Par::dimensionless, "g3", scalar, "GAUGE", 3);

     addParameter(Par::dimensionless, "sinW2", scalar, "SINTHETAW", 1); // TODO: No SLHA definition for this, just make up somewhere for it

     addParameter(Par::dimensionless, "Yd", m3x3, "YD");
     addParameter(Par::dimensionless, "Yu", m3x3, "YU");
     addParameter(Par::dimensionless, "Ye", m3x3, "YE");

     addParameter(Par::Pole_Mass, "~g", scalar, "MASS");
     addParameter(Par::Pole_Mass, "~d",     v6, "MASS");
     addParameter(Par::Pole_Mass, "~u",     v6, "MASS");
     addParameter(Par::Pole_Mass, "~e-",    v6, "MASS");
     addParameter(Par::Pole_Mass, "~nu",    v3, "MASS");
     addParameter(Par::Pole_Mass, "~chi+",  v2, "MASS");
     addParameter(Par::Pole_Mass, "~chi0",  v4, "MASS");
     addParameter(Par::Pole_Mass, "h0",     v2, "MASS");
     addParameter(Par::Pole_Mass, "A0", scalar, "MASS");
     addParameter(Par::Pole_Mass, "H+", scalar, "MASS");
     addParameter(Par::Pole_Mass, "W+", scalar, "MASS");
     addParameter(Par::Pole_Mass, "~g", scalar, "MASS");

     addParameter(Par::Pole_Mixing, "~d",    m6x6, "DSQMIX");
     addParameter(Par::Pole_Mixing, "~u",    m6x6, "USQMIX");
     addParameter(Par::Pole_Mixing, "~e-",   m6x6, "SELMIX");
     addParameter(Par::Pole_Mixing, "~nu",   m3x3, "SNUMIX");
     addParameter(Par::Pole_Mixing, "~chi0", m4x4, "NMIX");
     addParameter(Par::Pole_Mixing, "~chi-", m2x2, "UMIX"); // TODO: Does this naming really make the most sense?
     addParameter(Par::Pole_Mixing, "~chi+", m2x2, "VMIX"); 
     addParameter(Par::Pole_Mixing, "h0",    m2x2, "SCALARMIX"); // Non-SLHA: going with the FlexibleSUSY naming. Use these to compute ALPHA and other such SLHA variables when writing SLHA files.
     addParameter(Par::Pole_Mixing, "A0",    m2x2, "PSEUDOSCALARMIX");
     addParameter(Par::Pole_Mixing, "H+",    m2x2, "CHARGEMIX");
  }

  /// For the MSSM we need to transform our internal structure back into SLHA-compliant format for output
  SLHAstruct SpectrumContents::MSSM::generateOutputSLHAea(const Spectrum& spec, const int slha_version)
  {
      SLHAstruct raw = spec.getRawSLHAea();
      SLHAstruct output;
      std::ostringstream comment;

      // Copy some of the blocks verbatim
      // TODO: check case sensitiviy, do these in nicer order
      // TODO: should we copy these over and ensure backend always creates them
      // TODO: use something like slha(sminputs.getSLHAea) here or do that eralier and pass to backends
      output["SMINPUTS"] = raw["SMINPUTS"];
      output["VCKMIN"] = raw["VCKMIN"];
      output["UPMNSIN"] = raw["UPMNSIN"];

      output["DMASS"]    = raw["DMASS"]; // Not part of SLHA, but convenient to keep
      // PA: adding SPINFO to blocks copied over for now as FeynHiggs front end needs it
      // TODO: see below where Tomas wanted to construct it, so maybe adding it loke this is not the best approach. Indeed if we modify the spectrum contents, e.g, add precise Higgs mass calculation, we should really edit the SPINFO  Also this was always missing from GAMBIT slha files, not sure why FeynHiggs now needs it.
      output["SPINFO"] = raw["SPINFO"];
      // TODO: check replacing adding this ourselves is OK
      // and understand why that was missing tangbeta(mZ) parameter
      output["MINPAR"] = raw["MINPAR"];
      //std::stringstream ss; // Need to go via stringstream, no direct stream operator between
      //ss << raw["SMINPUTS"];
      //output << ss.str();

      // TODO: Would be good to have this, but currently the information about where the spectrum came from is lost.
      // Would need to add some member variable to the Spectrum object to store this information.
      // SPINFO block
      //if(not SLHAea_block_exists(output, "SPINFO"))
      //{
      //   SLHAea_add_block(output, "SPINFO");
      //   SLHAea_add(output, "SPINFO", 1, "GAMBIT, using "+backend_name);
      //   SLHAea_add(output, "SPINFO", 2, gambit_version()+" (GAMBIT); "+backend_version+" ("+backend_name+")");
      //}

      // All other MSSM blocks
      slhahelp::add_MSSM_spectrum_to_SLHAea(spec, output, slha_version);
      return output;
   }

   /// For the MSSM we also need to transform SLHA-compliant input files into our internal format
   /// EXCEPTION: We do not add the DMASS (mass uncertainty) block automatically! This is to force people
   /// to set uncertainties for the pole masses when they create Spectrum objects.
   SLHAstruct SpectrumContents::MSSM::transformInputSLHAea(const SLHAstruct& input)
   {
      // This is copy/pasted from the old MSSMSimpleSpec constructor
      SLHAstruct data = input;
      std::map<int, int> slha1to2; // PDG_translation_map;
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
        std::cout << "Input SLHA for setting up simple spectrum is SLHA1.  You old dog." << std::endl;

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
          for (int i = 0; i < lengths[j]; i++) masses[j].push_back(std::pair<int, double>(pdg[j][i], getdata(LOCAL_INFO,data,"MASS",pdg[j][i])));

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
                datum = getdata(LOCAL_INFO,data, gen3mix[j], family_index, (k+1)/3);
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
              entry = getdata(LOCAL_INFO,data, "MSOFT",30+3*k+i+(k>1?4:0)); // black magic to get correct index in MSOFT matching diagonal elements
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
          SLHAea_check_block(data, T[k].first); // TODO: should delete superceded slha1 "A" blocks? Edit: Probably yes. Not required by MSSM contents anymore
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
                  Yentry = getdata(LOCAL_INFO,data, Y[k].first,i,j);
                }
                else
                {
                  Yentry = 0;
                }

                if(SLHAea_check_block(data,A[k].first,i,j))
                {
                  Aentry = getdata(LOCAL_INFO,data, A[k].first,i,j);
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
      else logger() << "Input SLHA data for setting up MSSM spectrum is SLHA2.  *living in the future*" << EOM;
 
      // TODO: The above just takes care of SLHA1->2 conversions.
      // We still need to add a bunch of data that was previously computed "on the fly" by the SimpleSpectrum getter functions

      // SLHA2 defines Yukawa and trilinear couplings in super-CKM/PMNS basis, so they are diagonal.
      // But we still allow access to off-diagonal elements (should just return zero)
      // So we need to fill these in the wrapped SLHAea object (not necessarily provided)
      std::vector<std::string> diagblocks = {"YU","YD","YE","TU","TD","TE"};
      for(auto block: diagblocks) {
        for(int i=1;i<=3;i++) {
          for(int j=1;j<=3;j++) {
            if(i!=j) SLHAea_add(data, block, i, j, 0, "", false); // Comment not really necessary
          }
        }
      } 

      // gY -> g1
      // GAUGE block entry 1 is gY, not g1 as the Spectrum getters have been defined to return.
      double g1 = getdata(LOCAL_INFO,data,"GAUGE",1) / sqrt(3./5.);
      SLHAea_add(data,"GAUGE",4,g1,"g1 = gY/sqrt(3/5)",true);

      // BMu
      double tb = getdata(LOCAL_INFO,data,"HMIX",2); // tan beta(Q) DRbar ( = vu/vd)
      double cb = cos(atan(tb));
      double sb = sin(atan(tb));
      double mA2 = getdata(LOCAL_INFO,data,"HMIX",4); // m^2_A=[m3^2/cosBsinB](Q) DRbar, tree 
      double BMu = mA2 * (sb * cb);
      SLHAea_add(data,"BMu",1,BMu,"BMu",true); // TODO: Just sticking it in a made-up block for now

      // vd, vu
      double v = getdata(LOCAL_INFO,data,"HMIX",3); // v = sqrt(vd^2 + vu^2) DRbar
      double vd = sqrt(abs( v*v / ( tb*tb + 1 ) ));
      double itb = 1./tb; 
      double vu = sqrt(abs( v*v / ( itb*itb + 1 ) )); 
      SLHAea_add(data,"VEVS",1,vu,"vu",true); // TODO: Just sticking it in a made-up block for now
      SLHAea_add(data,"VEVS",2,vd,"vd",true);
  
      // sin(\theta_W) (DRbar)
      double sg1 = 0.6 * Utils::sqr(g1);
      double g2 = getdata(LOCAL_INFO,data,"GAUGE",2);
      double sintw = sg1 / (sg1 + Utils::sqr(g2));
      SLHAea_add(data,"SINTHETAW",1,sintw,"sin(theta_W) (DRbar)",true);

      // Neutrino and massless gauge boson masses
      SLHAea_add(data,"MASS",21,0,"gluon",false); // No overwrite allowed, use input value if one was provided
      SLHAea_add(data,"MASS",22,0,"photon",false);
      SLHAea_add(data,"SMINPUTS",12,0,"nu_1",false); // Neutrinos massless by default 
      SLHAea_add(data,"SMINPUTS",14,0,"nu_2",false); 
      SLHAea_add(data,"SMINPUTS",8 ,0,"nu_3",false);

      // TODO: Need to deal with SCALARMIX, PSEUDOSCALARMIX, etc also. FlexibleSUSY gives us these, and we need them internally, but they are not SLHA standard. So we cannot assume they exist. Need to calculate them from SLHA information (though we won't overwrite them if given)
      //BLOCK PSEUDOSCALARMIX   Q=  0.000000000000000e+00
      //    1   1  -9.999000000000000e+03   # A0 mixing matrix (1,1)
      //    1   2  -9.999000000000000e+03   # A0 mixing matrix (1,2)
      //    2   1  -9.999000000000000e+03   # A0 mixing matrix (2,1)
      //    2   2  -9.999000000000000e+03   # A0 mixing matrix (2,2)
      //BLOCK SCALARMIX     Q=  0.000000000000000e+00
      //    1   1  -9.999000000000000e+03   # h0 mixing matrix (1,1)
      //    1   2  -9.999000000000000e+03   # h0 mixing matrix (1,2)
      //    2   1  -9.999000000000000e+03   # h0 mixing matrix (2,1)
      //    2   2  -9.999000000000000e+03   # h0 mixing matrix (2,2)
      //BLOCK CHARGEMIX     Q=  0.000000000000000e+00
      //    1   1  -9.999000000000000e+03   # H+ mixing matrix (1,1)
      //    1   2  -9.999000000000000e+03   # H+ mixing matrix (1,2)
      //    2   1  -9.999000000000000e+03   # H+ mixing matrix (2,1)
      //    2   2  -9.999000000000000e+03   # H+ mixing matrix (2,2)
      // TODO: JUST ADDING AS ZERO FOR NOW!!!!! NEED TO ADD THIS CALCULATION!
      std::vector<std::string> non_slha_mix_blocks = {"PSEUDOSCALARMIX","SCALARMIX","CHARGEMIX"};
      for(auto block: non_slha_mix_blocks) {
          for(int i=1; i<=2; i++) {
              for(int j=1; j<=2; j++) {
                  SLHAea_add(data,block,i,j,0,"",false);
              }
          }
      }

      return data;
   }
 
}
#endif
