//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Tests to verify that Spectrum objects are
///  working correctly.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///    \date 2015 Aug
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no_)
///     \date 2016 Apr - Sep
///
///
///  *********************************************

#include <string>
#include <sstream>
#include <cmath>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"

#include "SLHAea/slhaea.h"
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>

#include "gambit/Utils/stream_overloads.hpp"

// MAtrix macros were super slow to compile, have now removed them.

namespace Gambit
{

  namespace SpecBit
  {

    using namespace std;
    using namespace LogTags;

    // Helper function to add error information to report
    void add_error(std::ostringstream& out, const std::exception& e, const std::string& msg)
    {
       out << "------------------------------" << std::endl;
       out << "TEST FAIL: " << msg << std::endl;
       out << "Exception thrown was: "<<e.what()<<std::endl;
       return;
    }

    // Test function for Matematica
    void Math_test(bool &result)
    {
      namespace myPipe = Pipes::Math_test;

      int input1 = 3, input2 = 4;

      int output= myPipe::BEreq::MathTest(input1,input2);
      cout << "Testing Mathematica" << endl;
      cout << "Result : " << output << endl;


      result = true;

    }

    void SUSYHD_test(bool &result)
    {
      using namespace Pipes::SUSYHD_test;

      const triplet<double> &mh = *Dep::prec_mh;

      cout << "mh = " << mh.central << " + "  << mh.upper << " - "  << mh.lower << endl;

      if(!mh.central) result = false;
      else result = true;

      return ;
    }

    // Testing function for SPheno
    void SPheno_MSSM_test(bool &result)
    {
      namespace myPipe = Pipes::SPheno_MSSM_test;
      const Spectrum& fullspectrum = *myPipe::Dep::unimproved_MSSM_spectrum;

      std::cout << fullspectrum.getSLHAea(2) << std::endl;

      result = 0;
    }

    /// Verify consistency of the contents of a Spectrum object of capability MSSMspectrum.
    /// (derived from old 'exampleRead' function)
    void MSSMspectrum_test (bool &result)
    {

      // Retrieve pointer to Spectrum object, delivered by dependency resolver
      // Module function asks for Spectrum* with capability unimproved_MSSM_spectrum.
      namespace myPipe = Pipes::MSSMspectrum_test;
      const Spectrum& fullspectrum = *myPipe::Dep::unimproved_MSSM_spectrum;
      const SubSpectrum& spec = fullspectrum.get_HE(); // MSSMSpec SubSpectrum object
      const SubSpectrum& SM   = fullspectrum.get_LE(); // QedQcdWrapper SubSpectrum object

      using namespace Par; // Bring parameter tags into scope

      std::ostringstream report; // Information about any problems encountered

      // Extract SLHAea object
      // This copies the data out. Could possibly change it to pass out a
      // reference instead, or have another function to do that.
      SLHAea::Coll slhaea = fullspectrum.getSLHAea(2);
      // for testing, write this to file
      std::ofstream out1;
      out1.open("SpecBit/MSSMspectrum_test.slha");
      out1 << slhaea;
      out1.close();

      // SLHAea::Coll slhaea = spec.getSLHAea(2); // The above is just a wrapper for this.

      // If this is a valid model point, return true and dump information, else false

      // SLHAea objects behave mostly like maps, but with special kinds of keys. For
      // "at" and "operator[]", it does automatic conversion, but for "find" it does
      // not, so we have to manually do it.
      SLHAea::Block spinfo = slhaea.at("SPINFO");
      //std::vector<std::string> k3(1, "3");
      std::vector<std::string> k4(1, "4");

      // See if error code entries exist
      //if(spinfo.find(k3) == spinfo.end() and spinfo.find(k4) == spinfo.end())
      if(spinfo.find(k4) == spinfo.end())
      {
         std::cout << "Good spectrum found! Inspecting contents..." << std::endl;
         std::cout << std::endl << slhaea << std::endl;

         // Write to file so we can check it
         spec.writeSLHAfile(2, "SpecBit/MSSMspectrum_test_good.slha");

         // ---------------------------------------------------------
         // BEGIN DEMO OF SPECTRUM OBJECT AND PARTICLE DATABASE
         // ---------------------------------------------------------

         #define ECHO(COMMAND)                                \
         {                                                    \
             try {                                            \
                cout << "  " << STRINGIFY(COMMAND) << " = " << COMMAND << endl;\
             }                                                \
             catch (const std::exception& e)                  \
             { add_error(report,e,STRINGIFY(COMMAND)); }      \
         }

         /* ----------Test particle database access ---------------- */
         const auto& PDB = Models::ParticleDB();

         // First check out what is actually in the database
         PDB.check_contents();

         // Demo a couple of particle name retrievals
         cout<<endl;
         cout<<"Demo retrieval of lightest neutralino info from particle database"<<endl;
         cout<<"-----------------------------------------------------------------"<<endl;
         ECHO( PDB.pdg_pair("~chi0_1")                   ) // Input long name, retrieve PDG code + context integer
         ECHO( PDB.pdg_pair("~chi0",1)                   ) // Input short name + index, retrieve PDG code + context integer
         ECHO( PDB.long_name("~chi0",1)                  ) // Input short name + index, retrieve long name
         ECHO( PDB.long_name(std::make_pair(1000022,0))  ) // Input PDG code + context integer, retrieve long name
         ECHO( PDB.long_name(1000022,0)                  ) // Input PDG code + context integer, retrieve long name
         ECHO( PDB.short_name_pair("~chi0_1")            ) // Input long name, retrieve short name + index
         ECHO( PDB.short_name_pair(std::make_pair(1000022,0)) ) // Input PDG code plus context integer, retrieve short name + index
         ECHO( PDB.short_name_pair(1000022,0)            ) // Input PDG code plus context integer, retrieve short name + index

         cout<<endl;
         cout<<"Demo retrieval of antiparticle names/codes using particle names/codes"<<endl;
         cout<<"-----------------------------------------------------------------"<<endl;
         // Check existence in various ways
         ECHO( PDB.has_antiparticle("~chi0_1")                 )
         ECHO( PDB.has_antiparticle("~chi0",1)                 )
         ECHO( PDB.has_antiparticle(std::make_pair("~chi0",1)) )
         ECHO( PDB.has_antiparticle(1000022,0)                 )
         ECHO( PDB.has_antiparticle(std::make_pair(1000022,0)) )
         ECHO( PDB.get_antiparticle("~chi0_1")                 ) // Input long name, retrieve antiparticle long name
         ECHO( PDB.get_antiparticle("~chi0",1)                 ) // Input short name + index, retrieve antiparticle short name + index
         ECHO( PDB.get_antiparticle(std::make_pair("~chi0",1)) ) // Input short name + index, retrieve antiparticle short name + index
         ECHO( PDB.get_antiparticle(1000022,0)                 ) // Input PDG code + context integet, retrieve antiparticle PDG code + context integer
         ECHO( PDB.get_antiparticle(std::make_pair(1000022,0)) ) // Input PDG code + context integet, retrieve antiparticle PDG code + context integer
         ECHO( PDB.has_antiparticle("~chi+_1")                 )
         ECHO( PDB.has_antiparticle("~chi+",1)                 )
         ECHO( PDB.has_antiparticle(std::make_pair("~chi+",1)) )
         ECHO( PDB.has_antiparticle(1000024,0)                 )
         ECHO( PDB.has_antiparticle(std::make_pair(1000024,0)) )
         ECHO( PDB.get_antiparticle("~chi+_1")                 ) // Input long name, retrieve antiparticle long name
         ECHO( PDB.get_antiparticle("~chi+",1)                 ) // Input short name + index, retrieve antiparticle short name + index
         ECHO( PDB.get_antiparticle(std::make_pair("~chi+",1)) ) // Input short name + index, retrieve antiparticle short name + index
         ECHO( PDB.get_antiparticle(1000024,0)                 ) // Input PDG code + context integet, retrieve antiparticle PDG code + context integer
         ECHO( PDB.get_antiparticle(std::make_pair(1000024,0)) ) // Input PDG code + context integet, retrieve antiparticle PDG code + context integer
         ECHO( PDB.has_antiparticle("u_1")                 )
         ECHO( PDB.has_antiparticle("u",1)                 )
         ECHO( PDB.has_antiparticle(std::make_pair("u",1)) )
         ECHO( PDB.has_antiparticle(2,0)                   )
         ECHO( PDB.has_antiparticle(std::make_pair(2,0))   )
         ECHO( PDB.get_antiparticle("u_1")                 ) // Input long name, retrieve antiparticle long name
         ECHO( PDB.get_antiparticle("u",1)                 ) // Input short name + index, retrieve antiparticle short name + index
         ECHO( PDB.get_antiparticle(std::make_pair("u",1)) ) // Input short name + index, retrieve antiparticle short name + index
         ECHO( PDB.get_antiparticle(2,0)                   ) // Input PDG code + context integet, retrieve antiparticle PDG code + context integer
         ECHO( PDB.get_antiparticle(std::make_pair(2,0))   ) // Input PDG code + context integet, retrieve antiparticle PDG code + context integer


         cout<<endl;
         cout<<"Demo retrieval when no short name exists"<<endl;
         cout<<"-----------------------------------------------------------------"<<endl;
         ECHO( PDB.pdg_pair("H+")                        )
         //ECHO( PDB.pdg_pair("H+",1)                      ) // Error!
         //ECHO( PDB.long_name("H+",1)                     ) // Error!
         ECHO( PDB.long_name(std::make_pair(37,0))       )
         ECHO( PDB.long_name(37,0)                       )
         //ECHO( PDB.short_name_pair("H+")                 ) // Error!
         //ECHO( PDB.short_name_pair(std::make_pair(37,0)) ) // Error!
         //ECHO( PDB.short_name_pair(37,0)                 ) // Error!
         //ECHO( PDB.short_name_pair(37)                   ) // Error!
         cout<<endl;
         /* ----------------- Pole masses --------------------------- */

         cout<<"Begin demo retrievals from Spectrum and SubSpectrum objects"<<endl;
         cout<<"-----------------------------------------------------------------"<<endl;
         cout<<endl;
         cout<<"First, general methods for accessing different sorts of information."<<endl;
         cout<<endl;
         // At the moment it is only pole masses which have getters overloaded to use
         // the particle database information. It is only the MASS block in the
         // spectrum generator output SLHA files which use PDG numbers anyway, so I
         // think this makes sense.
         cout<<"Lightest neutral Higgs boson pole mass:"<<endl;
         ECHO(  fullspectrum.get(Pole_Mass, PDB.short_name_pair(25,0) )   )
         ECHO(  fullspectrum.get(Pole_Mass, PDB.long_name(25,0) )         )
         ECHO(  fullspectrum.get(Pole_Mass,25,0)                          )
         ECHO(  fullspectrum.get(Pole_Mass, PDB.pdg_pair("h0",1) )        )
         ECHO(  fullspectrum.get(Pole_Mass,"h0",1)                        )
         ECHO(  fullspectrum.get(Pole_Mass,"h0_1")                        )

         ECHO(  spec.get(Pole_Mass, PDB.short_name_pair(25,0) )   )
         ECHO(  spec.get(Pole_Mass, PDB.long_name(25,0) )         )
         ECHO(  spec.get(Pole_Mass,25,0)                          )
         ECHO(  spec.get(Pole_Mass, PDB.pdg_pair("h0",1) )        )
         ECHO(  spec.get(Pole_Mass,"h0",1)                        )
         ECHO(  spec.get(Pole_Mass,"h0_1")                        )

         cout<<endl;
         cout<<"Retrieval of Spectrum object contents, with"<<endl;
         cout<<"correspondence to SLHAea object entries"<<endl;
         cout<<"-----------------------------------------------------------------"<<endl;

         // MZ was a bad first example; it is empty unless you switch on the SM pole mass
         // calculator for flexiblesusy. We do not yet pass any input value of MZ though
         // Similar issues with other gauge boson masses. So don't use these yet or
         // you'll get zero for all these masses.
         cout<<endl;
         cout<<"Gauge boson pole masses:"<<endl;
         cout<<endl;
         ECHO(  fullspectrum.get(Par::Pole_Mass,"Z0") )
         ECHO(  SM.get(Par::Pole_Mass,"Z0")           )
         ECHO(  slhaea.at("SMINPUTS").at(4).at(1)      )
         cout<<endl;
         ECHO(  fullspectrum.get(Par::Pole_Mass,"gamma")    )
         ECHO(  SM.get(Par::Pole_Mass,"gamma")    )
         cout<<"  ***Not in slha***"<<endl;
         cout<<endl;
         ECHO(  fullspectrum.get(Par::Pole_Mass,"W+")       )
         ECHO(  SM.get(Par::Pole_Mass,"W+")         )
         ECHO(  slhaea.at("MASS").at(24).at(1)    )
         cout<<endl;
         ECHO(  fullspectrum.get(Par::Pole_Mass,"g")       )
         ECHO(  SM.get(Par::Pole_Mass,"g")          )
         cout<<"  ***Not in slha***"<<endl;
         cout<<endl;
         cout<<"Quark pole masses (actually the slha entries are MSbar except the top mass):"<<endl;
         cout<<endl;
         // I'm a little unclear on what the pole masses for the lighter quarks mean, since I thought
         // that non-perturbative effects made definining them difficult... well anyway will have
         // to ask Peter what is being computed here.

         //ECHO(  spec.get(Par::Pole_Mass,"u",1)      )  // i.e. up (mass eigenstate)
         cout<<"  ***u Pole mass not well defined***"<<endl;
         ECHO(  slhaea.at("SMINPUTS").at(22).at(1)   )  // mu(2 GeV)^MS-bar, not pole mass
         cout<<endl;
         //ECHO(  spec.get(Par::Pole_Mass,"u",2)      )  // i.e. charm
         cout<<"  ***c Pole mass not well defined***"<<endl;
         ECHO(  slhaea.at("SMINPUTS").at(24).at(1)   )  // mc(mc)^MS-bar, not pole mass
         cout<<endl;
         //ECHO(  spec.get(Par::Pole_Mass,"u",3)      )  // i.e. top
         ECHO(  fullspectrum.get(Par::Pole_Mass,"t")       )
         ECHO(  SM.get(Par::Pole_Mass,"u",3)      )  // i.e. top
         ECHO(  slhaea.at("SMINPUTS").at(6).at(1)    )
         cout<<endl;
         //ECHO(  spec.get(Par::Pole_Mass,"d",1)      )  // i.e. down
         cout<<"  ***d Pole mass not well defined***"<<endl;
         ECHO(  slhaea.at("SMINPUTS").at(21).at(1)   )  // md(2 GeV)^MS-bar, not pole mass
         cout<<endl;
         //ECHO(  spec.get(Par::Pole_Mass,"d",2)      )  // i.e. strange
         cout<<"  ***s Pole mass not well defined***"<<endl;
         ECHO(  slhaea.at("SMINPUTS").at(23).at(1)   )  // ms(2 GeV)^MS-bar, not pole mass
         cout<<endl;
         //ECHO(  spec.get(Par::Pole_Mass,"d",3)      )  // i.e. bottom
         ECHO(  fullspectrum.get(Par::Pole_Mass,"b")       )
         ECHO(  SM.get(Par::Pole_Mass,"d",3)      )  // i.e. bottom
         ECHO(  slhaea.at("SMINPUTS").at(5).at(1)    )  //  mb(mb)^MS-bar, not pole mass.
         cout<<endl;
         cout<<"Charged fermions pole masses:"<<endl;
         cout<<endl;
         //ECHO(  spec.get(Par::Pole_Mass,"e-",1)     )  // i.e. electron
         ECHO(  fullspectrum.get(Par::Pole_Mass,"e-")       )
         ECHO(  SM.get(Par::Pole_Mass,"e-",1)     )  // i.e. electron
         ECHO(  slhaea.at("SMINPUTS").at(11).at(1)   )
         cout<<endl;
         //ECHO(  spec.get(Par::Pole_Mass,"e-",2)     )  // i.e. muon
         ECHO(  fullspectrum.get(Par::Pole_Mass,"mu-")       )
         ECHO(  SM.get(Par::Pole_Mass,"e-",2)     )  // i.e. muon
         ECHO(  slhaea.at("SMINPUTS").at(13).at(1)   )
         cout<<endl;
         //ECHO(  spec.get(Par::Pole_Mass,"e-",3)     )  // i.e. tau
         ECHO(  fullspectrum.get(Par::Pole_Mass,"tau-")       )
         ECHO(  SM.get(Par::Pole_Mass,"e-",3)     )  // i.e. tau
         ECHO(  slhaea.at("SMINPUTS").at(7).at(1)    )
         cout<<endl;
         cout<<"Neutrinos pole masses:"<<endl;
         cout<<endl;
         // These will produce errors because currently no neutrino mass getters are hooked up
         //ECHO(  spec.get(Par::Pole_Mass,"nu",1)     )  // Just mass ordered (if there is mixing)
         ECHO(  fullspectrum.get(Par::Pole_Mass,"nu",1)       )
         ECHO(  SM.get(Par::Pole_Mass,"nu",1)     )  // Just mass ordered (if there is mixing)
         ECHO(  slhaea.at("SMINPUTS").at(12).at(1)   )
         cout<<endl;
         //ECHO(  spec.get(Par::Pole_Mass,"nu",2)     )
         ECHO(  fullspectrum.get(Par::Pole_Mass,"nu",2)       )
         ECHO(  SM.get(Par::Pole_Mass,"nu",2)     )
         ECHO(  slhaea.at("SMINPUTS").at(14).at(1)   )
         cout<<endl;
         //ECHO(  spec.get(Par::Pole_Mass,"nu",3)     )
         ECHO(  fullspectrum.get(Par::Pole_Mass,"nu",3)       )
         ECHO(  SM.get(Par::Pole_Mass,"nu",3)     )
         ECHO(  slhaea.at("SMINPUTS").at(8).at(1)    )
         cout<<endl;
         // Now for SUSY particles
         cout<<endl;
         cout<<"MSSM Higgs sector pole masses:"<<endl;
         cout<<endl;
         ECHO(  fullspectrum.get(Par::Pole_Mass,"h0",1)       )
         ECHO(  spec.get(Par::Pole_Mass,"h0",1)     )  // Lightest neutral Higgs boson
         ECHO(  slhaea.at("MASS").at(25).at(1)       )
         cout<<endl;
         ECHO(  fullspectrum.get(Par::Pole_Mass,"h0",2)       )
         ECHO(  spec.get(Par::Pole_Mass,"h0",2)     )  // Heavy neutral Higgs boson
         ECHO(  slhaea.at("MASS").at(35).at(1)       )
         cout<<endl;
         ECHO(  fullspectrum.get(Par::Pole_Mass,"H+")       )
         ECHO(  spec.get(Par::Pole_Mass,"H+")       )  // Charged Higgs
         ECHO(  slhaea.at("MASS").at(37).at(1)       )
         cout<<endl;
         ECHO(  fullspectrum.get(Par::Pole_Mass,"A0")       )
         ECHO(  spec.get(Par::Pole_Mass,"A0")       )  // Pseudoscalar neutral Higgs
         ECHO(  slhaea.at("MASS").at(36).at(1)       )
         cout<<endl;

         // I'm going to use these nested functors to save lots of typing for the rest. It is just the
         // same as the examples above, except that the PDG codes are retrieved from the particle database.
         // The PDG code - string name correspondences are defined in 'Models/src/particle_database.cpp'

         struct get_polemass_functor
         {
           // Single mass
           void operator()(const std::string& longname)
           {
             std::ostringstream echo1, echo2, echo3;
             echo1 <<     "  fullspectrum.get(Par::Pole_Mass,"<<longname<<") = ";
             double value1 = fullspectrum.get(Par::Pole_Mass,longname);
             cout << echo1.str() << value1 << endl;
             echo2 <<     "  spec.get(Par::Pole_Mass,"<<longname<<") = ";
             double value2 = spec.get(Par::Pole_Mass,longname);
             cout << echo2.str() << value2 << endl;
             echo3 <<  "  slhaea.at(\"MASS\").at("<<PDB.pdg_pair(longname).first<<").at(1) = ";
             str value3 = slhaea.at("MASS").at( PDB.pdg_pair(longname).first ).at(1);
             cout << echo3.str() << value3 << endl;
             cout<<endl;
           }
           // Range of indexes masses
           void operator()(const std::string& longname, int from, int to)
           {
             for(int i=from; i<=to; ++i)
             {
               std::ostringstream echo1;
               std::ostringstream echo2;
               echo1 <<     "  spec.get(Par::Pole_Mass,"<<longname<<","<<i<<") = ";
               double value1 = spec.get(Par::Pole_Mass,longname,i);
               echo2 <<  "  slhaea.at(\"MASS\").at("<<PDB.pdg_pair(longname,i).first<<").at(1) = ";
               str value2 = slhaea.at("MASS").at( PDB.pdg_pair(longname,i).first ).at(1);
               cout << echo1.str() << value1 << endl;
               cout << echo2.str() << value2 << endl;
               cout<<endl;
             }
           }

           get_polemass_functor(const Spectrum& fullin, const SubSpectrum& specin, SLHAea::Coll& slhaeain)
             : fullspectrum(fullin)
             , spec(specin)
             , slhaea(slhaeain)
           {}

           private:
             const Spectrum& fullspectrum;
             const SubSpectrum& spec;
             SLHAea::Coll slhaea;
             const Models::partmap& PDB = Models::ParticleDB();
         };

         get_polemass_functor get_polemass(fullspectrum,spec,slhaea);

         cout<<endl<<"Gaugino pole masses:"<<endl<<endl;
         get_polemass("~g");
         get_polemass("~chi+",1,2);
         get_polemass("~chi0",1,4);
         cout<<endl<<"Squark pole masses:"<<endl<<endl;
         get_polemass("~d",1,6);
         get_polemass("~u",1,6);
         cout<<endl<<"Slepton pole masses:"<<endl<<endl;
         get_polemass("~e-",1,6);
         get_polemass("~nu",1,3);

         cout << endl << "Mixing matrices:" << endl << endl;

         // Note, currently we are not using a matrix object or any such thing, so you have to
         // extract the elements of each matrix one at a time. It would probably be handy to
         // add such a return type though.

         #define GET_MIX_MATRIX_EL(r, PRODUCT)                                   \
         {                                                                       \
            str label = BOOST_PP_SEQ_ELEM(0, PRODUCT);                           \
            str block = BOOST_PP_SEQ_ELEM(1, PRODUCT);                           \
            int i = BOOST_PP_SEQ_ELEM(2, PRODUCT);                               \
            int j = BOOST_PP_SEQ_ELEM(3, PRODUCT);                               \
           try{                                                                  \
            std::ostringstream echo1;                                            \
            std::ostringstream echo2;                                            \
            echo1 <<     "  spec.get(Par::Pole_Mixing,"<<label<<","<<i<<","<<j<<") = "; \
            double value1 = spec.get(Par::Pole_Mixing,label,i,j); \
            echo2 <<     "  SLHAea::to<double>( slhaea.at("<<block<<").at("<<i<<","<<j<<").at(2) ) = "; \
            double value2 = SLHAea::to<double>( slhaea.at(block).at(i,j).at(2) ); \
            cout << echo1.str() << value1 <<endl;                                \
            cout << echo2.str() << value2 <<endl;                                \
            cout << endl;                                                        \
           }                                                                     \
           catch (const std::exception& e)                                       \
           { add_error(report,e,label+": "+block); }                             \
         }

         #define GET_MIX_MATRIX(NAME,BLOCK,__IND1,__IND2) BOOST_PP_SEQ_FOR_EACH_PRODUCT(GET_MIX_MATRIX_EL, ((NAME))((BLOCK))(BOOST_PP_TUPLE_TO_SEQ(__IND1))(BOOST_PP_TUPLE_TO_SEQ(__IND2)))

         // The names here could perhaps be improved. They are not so immediately obvious to me.

         // GET_MIX_MATRIX("~chi-","UMIX",(1,2),(1,2)) cout<<endl;
         // GET_MIX_MATRIX("~chi+","VMIX",(1,2),(1,2)) cout<<endl;
         // GET_MIX_MATRIX("A0","PSEUDOSCALARMIX",(1,2),(1,2)) cout<<endl;
         // GET_MIX_MATRIX("~d","DSQMIX",(1,2,3,4,5,6),(1,2,3,4,5,6)) cout<<endl;
         // GET_MIX_MATRIX("~e-","SELMIX",(1,2,3,4,5,6),(1,2,3,4,5,6)) cout<<endl;
         // GET_MIX_MATRIX("h0","SCALARMIX",(1,2),(1,2)) cout<<endl;
         // GET_MIX_MATRIX("~chi0","NMIX",(1,2,3,4),(1,2,3,4)) cout<<endl;
         // GET_MIX_MATRIX("H+","CHARGEMIX",(1,2),(1,2)) cout<<endl;
         // GET_MIX_MATRIX("~u","USQMIX",(1,2,3,4,5,6),(1,2,3,4,5,6)) cout<<endl;
         // GET_MIX_MATRIX("~nu","SNUMIX",(1,2,3),(1,2,3)) cout<<endl;

         cout<<endl;
         cout << "Next up: running parameters" << endl;
         cout << "These are all given in the DRbar scheme, at least when running FlexibleSUSY or SoftSUSY. ";
         cout << "There may be some switching or converting once other spectrum generator are added." << endl;
         cout<<endl;
         cout << "Spectrum object running parameters are currently defined at scale Q="
              << spec.GetScale() << " [GeV]" << endl << endl;
         cout<<endl;
         cout << "-- Dimensionless parameters --" <<endl;
         cout << endl << "Gauge couplings:" << endl << endl;
         ECHO(  spec.get(Par::dimensionless,"g1")  )  // U_Y(1) gauge coupling in SU(5) normalisation
         ECHO(  slhaea.at("GAUGE").at(1).at(1)  ) // This is in the Standard Model normalisation as per SLHA conventions
         cout << "Note: " << spec.get(Par::dimensionless,"g1") << " * sqrt(3/5) = "
                          << spec.get(Par::dimensionless,"g1")*sqrt(3./5.) << endl;
         cout<<endl;
         ECHO(  spec.get(Par::dimensionless,"g2")  )  // SU(2) gauge coupling
         ECHO(  slhaea.at("GAUGE").at(2).at(1)  )
         cout<<endl;
         ECHO(  spec.get(Par::dimensionless,"g3")  )  // SU(3) gauge coupling
         ECHO(  slhaea.at("GAUGE").at(3).at(1)  )
         cout<<endl;

         cout << endl << "Yukawa matrices:" << endl << endl;

         // Note, currently we are not using a matrix object or any such thing, so you have to
         // extract the elements of the matrix one at a time. It would probably be handy to
         // add such a return type though.

         #define GET_MATRIX_EL(r, PRODUCT)                                       \
         {                                                                       \
            str label = BOOST_PP_SEQ_ELEM(0, PRODUCT);                           \
            str block = BOOST_PP_SEQ_ELEM(1, PRODUCT);                           \
            int i = BOOST_PP_SEQ_ELEM(2, PRODUCT);                               \
            int j = BOOST_PP_SEQ_ELEM(3, PRODUCT);                               \
           try{                                                                  \
            std::ostringstream echo1;                                            \
            std::ostringstream echo2;                                            \
            echo1 <<     "  spec.get(Par::dimensionless,"<<label<<","<<i<<","<<j<<") = "; \
            double value1 = spec.get(Par::dimensionless,label,i,j); \
            echo2 <<     "  SLHAea::to<double>( slhaea.at("<<block<<").at("<<i<<","<<j<<").at(2) ) = "; \
            double value2 = SLHAea::to<double>( slhaea.at(block).at(i,j).at(2) ); \
            cout << echo1.str() << value1 <<endl;                                \
            cout << echo2.str() << value2 <<endl;                                \
            cout << endl;                                                        \
           } catch (const std::exception& e)                                       \
           { add_error(report,e,label+": "+block); }                             \
         }

         #define GET_MATRIX(NAME,BLOCK,__IND1,__IND2) BOOST_PP_SEQ_FOR_EACH_PRODUCT(GET_MATRIX_EL, ((NAME))((BLOCK))(BOOST_PP_TUPLE_TO_SEQ(__IND1))(BOOST_PP_TUPLE_TO_SEQ(__IND2)))

         // GET_MATRIX("Yu","YU",(1,2,3),(1,2,3)) cout << endl;
         // GET_MATRIX("Yd","YD",(1,2,3),(1,2,3)) cout << endl;
         // GET_MATRIX("Ye","YE",(1,2,3),(1,2,3)) cout << endl;

         // Mass dimension 1 parameters

         cout<<endl;
         cout<<"MSSM mass dimension 1 running parameters"<<endl;
         cout<<endl;
         ECHO(  spec.get(Par::mass1,"M1")    )  // Gaugino mass parameter "MassB"
         ECHO(  slhaea.at("MSOFT").at(1).at(1)                )
         cout<<endl;
         ECHO(  spec.get(Par::mass1,"M2")    )  // Gaugino mass parameter "MassWB"
         ECHO(  slhaea.at("MSOFT").at(2).at(1)                )
         cout<<endl;
         ECHO(  spec.get(Par::mass1,"M3")    )  // Gaugino mass parameter "MassG"
         ECHO(  slhaea.at("MSOFT").at(3).at(1)                )
         cout<<endl;
         ECHO(  spec.get(Par::mass1,"Mu")    )  // Superpotential mu parameter
         ECHO(  slhaea.at("HMIX").at(1).at(1)                 )
         cout<<endl;
         ECHO(  spec.get(Par::mass1,"vd")    )  // Down-type Higgs vev
         ECHO(  slhaea.at("HMIX").at(102).at(1)               )
         cout<<endl;
         ECHO(  spec.get(Par::mass1,"vu")    )  // Up-type Higgs vev
         ECHO(  slhaea.at("HMIX").at(103).at(1)               )
         cout<<endl;

         // Matrices

         #define GET_M1_MATRIX_EL(r, PRODUCT)                                    \
         {                                                                       \
            str label = BOOST_PP_SEQ_ELEM(0, PRODUCT);                           \
            str block = BOOST_PP_SEQ_ELEM(1, PRODUCT);                           \
            int i = BOOST_PP_SEQ_ELEM(2, PRODUCT);                               \
            int j = BOOST_PP_SEQ_ELEM(3, PRODUCT);                               \
           try{                                                                  \
            std::ostringstream echo1;                                            \
            std::ostringstream echo2;                                            \
            echo1 <<     "  spec.get(Par::mass1,"<<label<<","<<i<<","<<j<<") = "; \
            double value1 = spec.get(Par::mass1,label,i,j); \
            echo2 <<     "  SLHAea::to<double>( slhaea.at("<<block<<").at("<<i<<","<<j<<").at(2) ) = "; \
            double value2 = SLHAea::to<double>( slhaea.at(block).at(i,j).at(2) ); \
            cout << echo1.str() << value1 <<endl;                                \
            cout << echo2.str() << value2 <<endl;                                \
            cout << endl;                                                        \
           } catch (const std::exception& e)                                       \
           { add_error(report,e,label+": "+block); }                             \
         }

         #define GET_M1_MATRIX(NAME,BLOCK,__IND1,__IND2) BOOST_PP_SEQ_FOR_EACH_PRODUCT(GET_M1_MATRIX_EL, ((NAME))((BLOCK))(BOOST_PP_TUPLE_TO_SEQ(__IND1))(BOOST_PP_TUPLE_TO_SEQ(__IND2)))

         cout << endl << "Triliner coupling matrices? SLHA says these blocks should be called AU,AD,AE, not TU,TD,TE though, so I'm not sure. Need to check with Peter." << endl << endl;

         // Seem to be the trilinears, and TYu and au etc. seem to be equal. Ask Peter...

         // GET_M1_MATRIX("TYu","TU",(1,2,3),(1,2,3)) cout << endl;
         // GET_M1_MATRIX("TYd","TD",(1,2,3),(1,2,3)) cout << endl;
         // GET_M1_MATRIX("TYe","TE",(1,2,3),(1,2,3)) cout << endl;
         // cout << endl;
         // GET_M1_MATRIX("au","TU",(1,2,3),(1,2,3)) cout << endl;
         // GET_M1_MATRIX("ad","TD",(1,2,3),(1,2,3)) cout << endl;
         // GET_M1_MATRIX("ae","TE",(1,2,3),(1,2,3)) cout << endl;

         // Mass dimension 2 parameters

         cout<<endl;
         cout<<"MSSM mass dimension 2 running parameters"<<endl;
         cout<<endl;
         ECHO(  spec.get(Par::mass2,"mHd2")  )  // Down-type Higgs soft mass
         ECHO(  slhaea.at("MSOFT").at(21).at(1)               )
         cout<<endl;
         ECHO(  spec.get(Par::mass2,"mHu2")  )  // Up-type Higgs soft mass
         ECHO(  slhaea.at("MSOFT").at(22).at(1)               )
         cout<<endl;
         ECHO(  spec.get(Par::mass2,"BMu")   )  // Higgs bilinear soft parameter
         ECHO(  slhaea.at("HMIX").at(101).at(1)               )
         cout<<endl;

         // Matrices

         #define GET_M2_MATRIX_EL(r, PRODUCT)                                    \
         {                                                                       \
            str label = BOOST_PP_SEQ_ELEM(0, PRODUCT);                           \
            str block = BOOST_PP_SEQ_ELEM(1, PRODUCT);                           \
            int i = BOOST_PP_SEQ_ELEM(2, PRODUCT);                               \
            int j = BOOST_PP_SEQ_ELEM(3, PRODUCT);                               \
            std::ostringstream echo1;                                            \
           try {                                                                 \
            std::ostringstream echo2;                                            \
            echo1 <<     "  spec.get(Par::mass2,"<<label<<","<<i<<","<<j<<") = "; \
            double value1 = spec.get(Par::mass2,label,i,j); \
            echo2 <<     "  SLHAea::to<double>( slhaea.at("<<block<<").at("<<i<<","<<j<<").at(2) ) = "; \
            double value2 = SLHAea::to<double>( slhaea.at(block).at(i,j).at(2) ); \
            cout << echo1.str() << value1 <<endl;                                \
            cout << echo2.str() << value2 <<endl;                                \
            cout << endl;                                                        \
           } catch (const std::exception& e)                                       \
           { add_error(report,e,label+": "+block); }                             \
        }

         #define GET_M2_MATRIX(NAME,BLOCK,__IND1,__IND2) BOOST_PP_SEQ_FOR_EACH_PRODUCT(GET_M2_MATRIX_EL, ((NAME))((BLOCK))(BOOST_PP_TUPLE_TO_SEQ(__IND1))(BOOST_PP_TUPLE_TO_SEQ(__IND2)))

         cout << endl << "Mass matrices:" << endl << endl;

         // GET_M2_MATRIX("mq2","MSQ2",(1,2,3),(1,2,3)) cout << endl;
         // GET_M2_MATRIX("mu2","MSU2",(1,2,3),(1,2,3)) cout << endl;
         // GET_M2_MATRIX("md2","MSD2",(1,2,3),(1,2,3)) cout << endl;
         // GET_M2_MATRIX("me2","MSE2",(1,2,3),(1,2,3)) cout << endl;
         // GET_M2_MATRIX("ml2","MSL2",(1,2,3),(1,2,3)) cout << endl;

         cout << endl;

         /// NEW! Tests of override setters
         /// These cannot be run on a const spectrum object, so we need to clone it first
         std::unique_ptr<SubSpectrum> clonedspec = spec.clone();

         cout << "Testing set_override functions" << endl;

         cout << "Original M1:" << clonedspec->get(Par::mass1,"M1") << endl;
         clonedspec->set_override(Par::mass1,-666,"M1");
         cout << "Override M1:" << clonedspec->get(Par::mass1,"M1") << endl;
          // Check that original can still be accessed using special optional argument
         cout << "Original M1 via no_overrides:" << clonedspec->get(Par::mass1,"M1",ignore_overrides) << endl;

         cout << "Original ~e-(1):" << clonedspec->get(Par::Pole_Mass,"~e-",1) << endl;
         clonedspec->set_override(Par::Pole_Mass,-667,"~e-",1);
         cout << "Override ~e-(1):" << clonedspec->get(Par::Pole_Mass,"~e-",1) << endl;
         cout << "Original ~e-(1) via no_overrides:" << clonedspec->get(Par::Pole_Mass,"~e-",1,ignore_overrides) << endl;

         // Make sure that we can set overrides via long name strings properly
         cout << "Original ~e-(2):" << clonedspec->get(Par::Pole_Mass,"~e-",2) << endl;
         clonedspec->set_override(Par::Pole_Mass,-345,"~e-_2");
         cout << "Override ~e-(2):" << clonedspec->get(Par::Pole_Mass,"~e-",2) << endl;
         cout << "Original ~e-(2) via no_overrides:" << clonedspec->get(Par::Pole_Mass,"~e-",2,ignore_overrides) << endl;
         clonedspec->set_override(Par::Pole_Mass,-347,"~e-",2);
         cout << "Override ~e-(2) (second time):" << clonedspec->get(Par::Pole_Mass,"~e-",2) << endl;
         cout << "Original ~e-(2) via no_overrides (second time):" << clonedspec->get(Par::Pole_Mass,"~e-",2,ignore_overrides) << endl;



         cout << "Original ml2(1,1):" << clonedspec->get(Par::mass2,"ml2",1,1) << endl;
         clonedspec->set_override(Par::mass2,-668,"ml2",1,1);
         cout << "Override ml2(1,1):" << clonedspec->get(Par::mass2,"ml2",1,1) << endl;
         cout << "Original ml2(1,1) via no_overrides:" << clonedspec->get(Par::mass2,"ml2",1,1,ignore_overrides) << endl;


         /// Now add some entry that didn't exist before
         cout << "has 'new_entry'? " << clonedspec->has(Par::mass1,"new_entry") << endl;
         cout << "..." << endl;
         /// Note: if we try to do it like this, it should fail:
         //clonedspec->set_override(Par::mass2,-1234,"new_entry"); // incorrect: "allow_new" false by default
         clonedspec->set_override(Par::mass1,-1234,"new_entry",true); // correct: "allow_new" = true
         cout << "has 'new_entry'? " << clonedspec->has(Par::mass1,"new_entry") << endl;
         cout << "new_entry = " << clonedspec->get(Par::mass1,"new_entry") << endl;
         cout << endl;

         /// TODO: Tests of ordinary 'setter' functions (these actually replace data in the wrapped object)


         /// Tests of spectrum/particle database antiparticle getters/setters interaction
         cout << "Test retrieval of antiparticle entries" << endl;

         cout << "has '~e+' pole mass? " << clonedspec->has(Par::Pole_Mass,"~e+",1) << endl;
         cout << "'~e+' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e+",1) << endl;
         cout << "'~e-' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e-",1) << endl;
         cout << "Setting new ~e+ pole mass value" << endl;
         clonedspec->set(Par::Pole_Mass,-666,"~e+",1);
         cout << "'~e+' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e+",1) << endl;
         cout << "'~e-' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e-",1) << endl;
         cout << "Setting override ~e+ pole mass value" << endl;
         // Need to turn on the "allow_new" check for this, because no explicit entry for
         // ~e+_1 exists yet, and need to turn on the "decouple" option to prevent conversion
         // to the antiparticle string name. This action will decouple the ~e-_1 and ~e+_1 masses from
         // here onwards.
         clonedspec->set_override(Par::Pole_Mass,-999,"~e+",1,true,true); // "allow_new" + "decouple" = true
         cout << "'~e+' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e+",1) << endl;
         cout << "'~e-' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e-",1) << endl;
         cout << "Set ~e+ pole mass via PDG code" << endl;
         // Can leave safety check on this time, because now an explicit entry for
         // ~e+_1 DOES exist (i.e. the previous override entry)
         clonedspec->set_override(Par::Pole_Mass,-111,std::make_pair(-1000011,0));
         cout << "'(-1000011,0)' pole mass = " << clonedspec->get(Par::Pole_Mass,std::make_pair(-1000011,0)) << endl;
         cout << "'~e+' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e+",1) << endl;
         cout << "'~e-' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e-",1) << endl;
         cout << "Setting new ~e+ pole mass value (will be hidden by override!)" << endl;
         // This should also throw a warning explaining that the newly set value is not retrievable by
         // the getters, due to being hidden by an override value.
         clonedspec->set(Par::Pole_Mass,-96969,"~e+",1);
         cout << "'~e+' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e+",1) << endl;
         cout << "'~e-' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e-",1) << endl;
         cout << endl;

         cout << "has '~e+,2' pole mass? " << clonedspec->has(Par::Pole_Mass,"~e+",2) << endl;
         cout << "'~e+,2' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e+",2) << endl;
         cout << "'~e-,2' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e-",2) << endl;
         cout << "Setting new ~e+,2 pole mass value" << endl;
         clonedspec->set(Par::Pole_Mass,-666,"~e+",2);
         cout << "'~e+,2' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e+",2) << endl;
         cout << "'~e-,2' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e-",2) << endl;
         cout << "Setting override ~e+,2 pole mass value" << endl;
         clonedspec->set_override(Par::Pole_Mass,-999,"~e+",2,true);
         cout << "'~e+,2' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e+",2) << endl;
         cout << "'~e-,2' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e-",2) << endl;
         cout << "Set ~e+,2 pole mass via PDG code" << endl;
         clonedspec->set_override(Par::Pole_Mass,-111,std::make_pair(-1000013,0));
         cout << "'(-1000013,0)' pole mass = " << clonedspec->get(Par::Pole_Mass,std::make_pair(-1000013,0)) << endl;
         cout << "'~e+,2' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e+",2) << endl;
         cout << "'~e-,2' pole mass = " << clonedspec->get(Par::Pole_Mass,"~e-",2) << endl;


         cout << "Test report:" << std::endl << report.str();

         /// Turn SpecBit warnings to 'fatal' in order to trigger stop after this function runs.
         SpecBit_warning().raise(LOCAL_INFO,"\n *** Finished examining spectrum contents ***");
         result = 0;
      }
    }

    // Test that output of Standard Model wrapper (e.g. QedQcdWrapper) matches
    // SMINPUTS sufficiently accurately
    // Set flag SLHAonly=1 if SMskeleton and/or MSSMskeleton are being used.
    void light_quark_test(bool&)
    {
       namespace myPipe = Pipes::light_quark_test;
       const SubSpectrum& qedqcd = **myPipe::Dep::qedqcd_subspectrum;

       // Check light quark mass ratios
       logger() << "Checking light quark mass ratios:" << EOM;

       /// Generate data for a plot of quark mass
       double Qs[] = {
       1.00000000e-02,   1.25892541e-02,   1.58489319e-02,
       1.99526231e-02,   2.51188643e-02,   3.16227766e-02,
       3.98107171e-02,   5.01187234e-02,   6.30957344e-02,
       7.94328235e-02,   1.00000000e-01,   1.25892541e-01,
       1.58489319e-01,   1.99526231e-01,   2.51188643e-01,
       3.16227766e-01,   3.98107171e-01,   5.01187234e-01,
       6.30957344e-01,   7.94328235e-01,   1.00000000e+00,
       1.25892541e+00,   1.58489319e+00,   1.99526231e+00,
       2.51188643e+00,   3.16227766e+00,   3.98107171e+00,
       5.01187234e+00,   6.30957344e+00,   7.94328235e+00,
       1.00000000e+01,   1.25892541e+01,   1.58489319e+01,
       1.99526231e+01,   2.51188643e+01,   3.16227766e+01,
       3.98107171e+01,   5.01187234e+01,   6.30957344e+01,
       7.94328235e+01,   1.00000000e+02,   1.25892541e+02,
       1.58489319e+02,   1.99526231e+02,   2.51188643e+02,
       3.16227766e+02,   3.98107171e+02,   5.01187234e+02,
       6.30957344e+02,   7.94328235e+02,   1.00000000e+03,
       1.25892541e+03,   1.58489319e+03,   1.99526231e+03,
       2.51188643e+03,   3.16227766e+03,   3.98107171e+03,
       5.01187234e+03,   6.30957344e+03,   7.94328235e+03,
       1.00000000e+04,   1.25892541e+04,   1.58489319e+04,
       1.99526231e+04,   2.51188643e+04,   3.16227766e+04,
       3.98107171e+04,   5.01187234e+04,   6.30957344e+04,
       7.94328235e+04
       };

       std::vector<double> Qvec(Qs, Utils::endA(Qs));

       std::ofstream Qout;
       Qout.open("SpecBit/light_quark_txt");

       Qout <<std::setw(12)<<"Qin"
            <<std::setw(12)<<"Qreal"
            <<std::setw(12)<<"alphaS"
            <<std::setw(12)<<"md"
            <<std::setw(12)<<"mu"
            <<std::setw(12)<<"ms"
            <<std::setw(12)<<"mu/md"
            <<std::setw(12)<<"ms/md"
            <<std::endl;
       for(std::vector<double>::iterator it = Qvec.begin(); it != Qvec.end(); ++it)
       {
          // Clone to avoid buildup of errors
          std::unique_ptr<SubSpectrum> SMloop = qedqcd.clone();

          SMloop->RunToScale(*it);
          double Q = SMloop->GetScale();
          double mu = SMloop->get(Par::mass1,"u");
          double md = SMloop->get(Par::mass1,"d");
          double ms = SMloop->get(Par::mass1,"s");
          double alphas = SMloop->get(Par::dimensionless,"alphaS");
          // Write to file
          Qout <<std::setw(12)<<*it
               <<std::setw(12)<<Q
               <<std::setw(12)<<alphas
               <<std::setw(12)<<md
               <<std::setw(12)<<mu
               <<std::setw(12)<<ms
               <<std::setw(12)<<mu/md
               <<std::setw(12)<<ms/md
               <<std::endl;
       }

       Qout.close();

       std::cout << " light quark test finished, bailing out!" << std::endl;
       exit(0);
    }
  }

}

#undef PDB
