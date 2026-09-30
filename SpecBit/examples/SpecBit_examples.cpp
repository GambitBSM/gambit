//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Example retrieval of data from Spectrum
///  object.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///    \date 2014 Dec
///
///  *********************************************

#include <string>
#include <sstream>
#include <cmath>

#include "gambit/Utils/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"

#include "SLHAea/slhaea.h"
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>

// For the demo output only
#include "gambit/Utils/stream_overloads.hpp"

namespace Gambit
{

  namespace SpecBit
  {

    using namespace LogTags;

    // Helper function to add error information to report
    void add_error(std::ostringstream& out, const std::exception& e, const std::string& msg)
    {
       out << "------------------------------" << std::endl;
       out << "TEST FAIL: " << msg << std::endl;
       out << "Exception thrown was: "<<e.what()<<std::endl;
       return;
    }

    // Example showing reading of SLHA information from Spectrum object, using
    // both SLHAea objects and direct Spectrum getter functions.
    void exampleRead (bool &result)
    {

      // Retrieve pointer to Spectrum object, delivered by dependency resolver
      // Module function asks for Spectrum* with capability MSSM_spectrum.
      // i.e. has DEPENDENCY(MSSM_spectrum, Spectrum*)
      namespace myPipe = Pipes::exampleRead;
      /*TAG*/ Spectrum fullspectrum = *myPipe::Dep::MSSM_spectrum;
      const SubSpectrum* spec = fullspectrum->get_HE(); // MSSMSpec SubSpectrum object
      const SubSpectrum* SM   = fullspectrum->get_LE(); // QedQcdWrapper SubSpectrum object

      std::ostringstream report; // Information about any problems encountered

      // Extract SLHAea object
      // This copies the data out. Could possible change it to pass out a
      // reference instead, or have another function to do that.
      SLHAea::Coll slhaea = fullspectrum->getSLHAea(2);
      // for testing, write this to file
      std::ofstream out1;
      out1.open("SpecBit/exampleRead_test.slha");
      out1 << slhaea;
      out1.close();

      // SLHAea::Coll slhaea = spec->getSLHAea(2); // The above is just a wrapper for this.

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
         std::string filename(myPipe::runOptions->getValue<std::string>("output_slha_filename"));
         spec->writeSLHAfile(2,filename);

         // ---------------------------------------------------------
         // BEGIN DEMO OF SPECTRUM OBJECT AND PARTICLE DATABASE
         // ---------------------------------------------------------

         //#define ECHO(COMMAND) cout << "  " << STRINGIFY(COMMAND) << " = " << COMMAND << endl;
         //Replacing with a version that deals with SLHAea access errors
         #define ECHO(COMMAND)                                \
         {                                                    \
             try {                                            \
                cout << "  " << STRINGIFY(COMMAND) << " = " << COMMAND << endl;\
             }                                                \
             catch (const std::exception& e)                  \
             { add_error(report,e,STRINGIFY(COMMAND)); }      \
         }

         /* ----------Test particle database access ---------------- */
         #define PDB Models::ParticleDB()

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
         ECHO(  fullspectrum->get_Pole_Mass( PDB.short_name_pair(25,0) )   )
         ECHO(  fullspectrum->get_Pole_Mass( PDB.long_name(25,0) )         )
         ECHO(  fullspectrum->get_Pole_Mass(25,0)                          )
         ECHO(  fullspectrum->get_Pole_Mass( PDB.pdg_pair("h0",1) )        )
         ECHO(  fullspectrum->get_Pole_Mass("h0",1)                        )
         ECHO(  fullspectrum->get_Pole_Mass("h0_1")                        )

         ECHO(  spec->get_Pole_Mass( PDB.short_name_pair(25,0) )   )
         ECHO(  spec->get_Pole_Mass( PDB.long_name(25,0) )         )
         ECHO(  spec->get_Pole_Mass(25,0)                          )
         ECHO(  spec->get_Pole_Mass( PDB.pdg_pair("h0",1) )        )
         ECHO(  spec->get_Pole_Mass("h0",1)                        )
         ECHO(  spec->get_Pole_Mass("h0_1")                        )

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
         ECHO(  fullspectrum->get_Pole_Mass("Z0") )
         ECHO(  SM->get_Pole_Mass("Z0")           )
         ECHO(  slhaea.at("SMINPUTS").at(4).at(1)      )
         cout<<endl;
         ECHO(  fullspectrum->get_Pole_Mass("gamma")    )
         ECHO(  SM->get_Pole_Mass("gamma")    )
         cout<<"  ***Not in slha***"<<endl;
         cout<<endl;
         ECHO(  fullspectrum->get_Pole_Mass("W+")       )
         ECHO(  SM->get_Pole_Mass("W+")         )
         ECHO(  slhaea.at("MASS").at(24).at(1)    )
         cout<<endl;
         ECHO(  fullspectrum->get_Pole_Mass("g")       )
         ECHO(  SM->get_Pole_Mass("g")          )
         cout<<"  ***Not in slha***"<<endl;
         cout<<endl;
         cout<<"Quark pole masses (actually the slha entries are MSbar except the top mass):"<<endl;
         cout<<endl;
         // I'm a little unclear on what the pole masses for the lighter quarks mean, since I thought
         // that non-perturbative effects made definining them difficult... well anyway will have
         // to ask Peter what is being computed here.

         //ECHO(  spec->get_Pole_Mass("u",1)      )  // i.e. up (mass eigenstate)
         cout<<"  ***u Pole mass not well defined***"<<endl;
         ECHO(  slhaea.at("SMINPUTS").at(22).at(1)   )  // mu(2 GeV)^MS-bar, not pole mass
         cout<<endl;
         //ECHO(  spec->get_Pole_Mass("u",2)      )  // i.e. charm
         cout<<"  ***c Pole mass not well defined***"<<endl;
         ECHO(  slhaea.at("SMINPUTS").at(24).at(1)   )  // mc(mc)^MS-bar, not pole mass
         cout<<endl;
         //ECHO(  spec->get_Pole_Mass("u",3)      )  // i.e. top
         ECHO(  fullspectrum->get_Pole_Mass("t")       )
         ECHO(  SM->get_Pole_Mass("u",3)      )  // i.e. top
         ECHO(  slhaea.at("SMINPUTS").at(6).at(1)    )
         cout<<endl;
         //ECHO(  spec->get_Pole_Mass("d",1)      )  // i.e. down
         cout<<"  ***d Pole mass not well defined***"<<endl;
         ECHO(  slhaea.at("SMINPUTS").at(21).at(1)   )  // md(2 GeV)^MS-bar, not pole mass
         cout<<endl;
         //ECHO(  spec->get_Pole_Mass("d",2)      )  // i.e. strange
         cout<<"  ***s Pole mass not well defined***"<<endl;
         ECHO(  slhaea.at("SMINPUTS").at(23).at(1)   )  // ms(2 GeV)^MS-bar, not pole mass
         cout<<endl;
         //ECHO(  spec->get_Pole_Mass("d",3)      )  // i.e. bottom
         ECHO(  fullspectrum->get_Pole_Mass("b")       )
         ECHO(  SM->get_Pole_Mass("d",3)      )  // i.e. bottom
         ECHO(  slhaea.at("SMINPUTS").at(5).at(1)    )  //  mb(mb)^MS-bar, not pole mass.
         cout<<endl;
         cout<<"Charged fermions pole masses:"<<endl;
         cout<<endl;
         //ECHO(  spec->get_Pole_Mass("e-",1)     )  // i.e. electron
         ECHO(  fullspectrum->get_Pole_Mass("e-")       )
         ECHO(  SM->get_Pole_Mass("e-",1)     )  // i.e. electron
         ECHO(  slhaea.at("SMINPUTS").at(11).at(1)   )
         cout<<endl;
         //ECHO(  spec->get_Pole_Mass("e-",2)     )  // i.e. muon
         ECHO(  fullspectrum->get_Pole_Mass("mu-")       )
         ECHO(  SM->get_Pole_Mass("e-",2)     )  // i.e. muon
         ECHO(  slhaea.at("SMINPUTS").at(13).at(1)   )
         cout<<endl;
         //ECHO(  spec->get_Pole_Mass("e-",3)     )  // i.e. tau
         ECHO(  fullspectrum->get_Pole_Mass("tau-")       )
         ECHO(  SM->get_Pole_Mass("e-",3)     )  // i.e. tau
         ECHO(  slhaea.at("SMINPUTS").at(7).at(1)    )
         cout<<endl;
         cout<<"Neutrinos pole masses:"<<endl;
         cout<<endl;
         // These will produce errors because currently no neutrino mass getters are hooked up
         //ECHO(  spec->get_Pole_Mass("nu",1)     )  // Just mass ordered (if there is mixing)
         ECHO(  fullspectrum->get_Pole_Mass("nu",1)       )
         ECHO(  SM->get_Pole_Mass("nu",1)     )  // Just mass ordered (if there is mixing)
         ECHO(  slhaea.at("SMINPUTS").at(12).at(1)   )
         cout<<endl;
         //ECHO(  spec->get_Pole_Mass("nu",2)     )
         ECHO(  fullspectrum->get_Pole_Mass("nu",2)       )
         ECHO(  SM->get_Pole_Mass("nu",2)     )
         ECHO(  slhaea.at("SMINPUTS").at(14).at(1)   )
         cout<<endl;
         //ECHO(  spec->get_Pole_Mass("nu",3)     )
         ECHO(  fullspectrum->get_Pole_Mass("nu",3)       )
         ECHO(  SM->get_Pole_Mass("nu",3)     )
         ECHO(  slhaea.at("SMINPUTS").at(8).at(1)    )
         cout<<endl;
         // Now for SUSY particles
         cout<<endl;
         cout<<"MSSM Higgs sector pole masses:"<<endl;
         cout<<endl;
         ECHO(  fullspectrum->get_Pole_Mass("h0",1)       )
         ECHO(  spec->get_Pole_Mass("h0",1)     )  // Lightest neutral Higgs boson
         ECHO(  slhaea.at("MASS").at(25).at(1)       )
         cout<<endl;
         ECHO(  fullspectrum->get_Pole_Mass("h0",2)       )
         ECHO(  spec->get_Pole_Mass("h0",2)     )  // Heavy neutral Higgs boson
         ECHO(  slhaea.at("MASS").at(35).at(1)       )
         cout<<endl;
         ECHO(  fullspectrum->get_Pole_Mass("H+")       )
         ECHO(  spec->get_Pole_Mass("H+")       )  // Charged Higgs
         ECHO(  slhaea.at("MASS").at(37).at(1)       )
         cout<<endl;
         ECHO(  fullspectrum->get_Pole_Mass("A0")       )
         ECHO(  spec->get_Pole_Mass("A0")       )  // Pseudoscalar neutral Higgs
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
             echo1 <<     "  fullspectrum->get_Pole_Mass("<<longname<<") = ";
             double value1 = fullspectrum->get_Pole_Mass(longname);
             echo2 <<     "  spec->get_Pole_Mass("<<longname<<") = ";
             double value2 = spec->get_Pole_Mass(longname);
             echo3 <<  "  slhaea.at(\"MASS\").at("<<PDB.pdg_pair(longname).first<<").at(1) = ";
             str value3 = slhaea.at("MASS").at( PDB.pdg_pair(longname).first ).at(1);
             cout << echo1.str() << value1 << endl;
             cout << echo2.str() << value2 << endl;
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
               echo1 <<     "  spec->get_Pole_Mass("<<longname<<","<<i<<") = ";
               double value1 = spec->get_Pole_Mass(longname,i);
               echo2 <<  "  slhaea.at(\"MASS\").at("<<PDB.pdg_pair(longname,i).first<<").at(1) = ";
               str value2 = slhaea.at("MASS").at( PDB.pdg_pair(longname,i).first ).at(1);
               cout << echo1.str() << value1 << endl;
               cout << echo2.str() << value2 << endl;
               cout<<endl;
             }
           }

           get_polemass_functor(std::ostringstream& report, /*TAG*/ Spectrum fullin, const SubSpectrum* specin, SLHAea::Coll& slhaeain)
             : report(report)
             , fullspectrum(fullin)
             , spec(specin)
             , slhaea(slhaeain)
           {}

           private:
             std::ostringstream& report;
             /*TAG*/ Spectrum fullspectrum;
             const SubSpectrum* spec;
             SLHAea::Coll slhaea;
         };

         get_polemass_functor get_polemass(report,fullspectrum,spec,slhaea);

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
            echo1 <<     "  spec->get_Pole_Mixing("<<label<<","<<i<<","<<j<<") = "; \
            double value1 = spec->get_Pole_Mixing(label,i,j); \
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

         GET_MIX_MATRIX("~chi-","UMIX",(1,2),(1,2)) cout<<endl;
         GET_MIX_MATRIX("~chi+","VMIX",(1,2),(1,2)) cout<<endl;
         GET_MIX_MATRIX("A0","PSEUDOSCALARMIX",(1,2),(1,2)) cout<<endl;
         GET_MIX_MATRIX("~d","DSQMIX",(1,2,3,4,5,6),(1,2,3,4,5,6)) cout<<endl;
         GET_MIX_MATRIX("~e-","SELMIX",(1,2,3,4,5,6),(1,2,3,4,5,6)) cout<<endl;
         GET_MIX_MATRIX("h0","SCALARMIX",(1,2),(1,2)) cout<<endl;
         GET_MIX_MATRIX("~chi0","NMIX",(1,2,3,4),(1,2,3,4)) cout<<endl;
         GET_MIX_MATRIX("H+","CHARGEMIX",(1,2),(1,2)) cout<<endl;
         GET_MIX_MATRIX("~u","USQMIX",(1,2,3,4,5,6),(1,2,3,4,5,6)) cout<<endl;
         GET_MIX_MATRIX("~nu","SNUMIX",(1,2,3),(1,2,3)) cout<<endl;

         cout<<endl;
         cout << "Next up: running parameters" << endl;
         cout << "These are all given in the DRbar scheme, at least when running FlexibleSUSY or SoftSUSY. ";
         cout << "There may be some switching or converting once other spectrum generator are added." << endl;
         cout<<endl;
         cout << "Spectrum object running parameters are currently defined at scale Q="
              << spec->GetScale() << " [GeV]" << endl << endl;
         cout<<endl;
         cout << "-- Dimensionless parameters --" <<endl;
         cout << endl << "Gauge couplings:" << endl << endl;
         ECHO(  spec->get_dimensionless_parameter("g1")  )  // U_Y(1) gauge coupling in SU(5) normalisation
         ECHO(  slhaea.at("GAUGE").at(1).at(1)  ) // This is in the Standard Model normalisation as per SLHA conventions
         cout << "Note: " << spec->get_dimensionless_parameter("g1") << " * sqrt(3/5) = "
                          << spec->get_dimensionless_parameter("g1")*sqrt(3./5.) << endl;
         cout<<endl;
         ECHO(  spec->get_dimensionless_parameter("g2")  )  // SU(2) gauge coupling
         ECHO(  slhaea.at("GAUGE").at(2).at(1)  )
         cout<<endl;
         ECHO(  spec->get_dimensionless_parameter("g3")  )  // SU(3) gauge coupling
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
            echo1 <<     "  spec->get_dimensionless_parameter("<<label<<","<<i<<","<<j<<") = "; \
            double value1 = spec->get_dimensionless_parameter(label,i,j); \
            echo2 <<     "  SLHAea::to<double>( slhaea.at("<<block<<").at("<<i<<","<<j<<").at(2) ) = "; \
            double value2 = SLHAea::to<double>( slhaea.at(block).at(i,j).at(2) ); \
            cout << echo1.str() << value1 <<endl;                                \
            cout << echo2.str() << value2 <<endl;                                \
            cout << endl;                                                        \
           } catch (const std::exception& e)                                       \
           { add_error(report,e,label+": "+block); }                             \
         }

         #define GET_MATRIX(NAME,BLOCK,__IND1,__IND2) BOOST_PP_SEQ_FOR_EACH_PRODUCT(GET_MATRIX_EL, ((NAME))((BLOCK))(BOOST_PP_TUPLE_TO_SEQ(__IND1))(BOOST_PP_TUPLE_TO_SEQ(__IND2)))

         GET_MATRIX("Yu","YU",(1,2,3),(1,2,3)) cout << endl;
         GET_MATRIX("Yd","YD",(1,2,3),(1,2,3)) cout << endl;
         GET_MATRIX("Ye","YE",(1,2,3),(1,2,3)) cout << endl;

         // Mass dimension 1 parameters

         cout<<endl;
         cout<<"MSSM mass dimension 1 running parameters"<<endl;
         cout<<endl;
         ECHO(  spec->get_mass_parameter("M1")    )  // Gaugino mass parameter "MassB"
         ECHO(  slhaea.at("MSOFT").at(1).at(1)                )
         cout<<endl;
         ECHO(  spec->get_mass_parameter("M2")    )  // Gaugino mass parameter "MassWB"
         ECHO(  slhaea.at("MSOFT").at(2).at(1)                )
         cout<<endl;
         ECHO(  spec->get_mass_parameter("M3")    )  // Gaugino mass parameter "MassG"
         ECHO(  slhaea.at("MSOFT").at(3).at(1)                )
         cout<<endl;
         ECHO(  spec->get_mass_parameter("Mu")    )  // Superpotential mu parameter
         ECHO(  slhaea.at("HMIX").at(1).at(1)                 )
         cout<<endl;
         ECHO(  spec->get_mass_parameter("vd")    )  // Down-type Higgs vev
         ECHO(  slhaea.at("HMIX").at(102).at(1)               )
         cout<<endl;
         ECHO(  spec->get_mass_parameter("vu")    )  // Up-type Higgs vev
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
            echo1 <<     "  spec->get_mass_parameter("<<label<<","<<i<<","<<j<<") = "; \
            double value1 = spec->get_mass_parameter(label,i,j); \
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

         GET_M1_MATRIX("TYu","TU",(1,2,3),(1,2,3)) cout << endl;
         GET_M1_MATRIX("TYd","TD",(1,2,3),(1,2,3)) cout << endl;
         GET_M1_MATRIX("TYe","TE",(1,2,3),(1,2,3)) cout << endl;
         cout << endl;
         GET_M1_MATRIX("au","TU",(1,2,3),(1,2,3)) cout << endl;
         GET_M1_MATRIX("ad","TD",(1,2,3),(1,2,3)) cout << endl;
         GET_M1_MATRIX("ae","TE",(1,2,3),(1,2,3)) cout << endl;

         // Mass dimension 2 parameters

         cout<<endl;
         cout<<"MSSM mass dimension 2 running parameters"<<endl;
         cout<<endl;
         ECHO(  spec->get_mass2_parameter("mHd2")  )  // Down-type Higgs soft mass
         ECHO(  slhaea.at("MSOFT").at(21).at(1)               )
         cout<<endl;
         ECHO(  spec->get_mass2_parameter("mHu2")  )  // Up-type Higgs soft mass
         ECHO(  slhaea.at("MSOFT").at(22).at(1)               )
         cout<<endl;
         ECHO(  spec->get_mass2_parameter("BMu")   )  // Higgs bilinear soft parameter
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
            echo1 <<     "  spec->get_mass2_parameter("<<label<<","<<i<<","<<j<<") = "; \
            double value1 = spec->get_mass2_parameter(label,i,j); \
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

         GET_M2_MATRIX("mq2","MSQ2",(1,2,3),(1,2,3)) cout << endl;
         GET_M2_MATRIX("mu2","MSU2",(1,2,3),(1,2,3)) cout << endl;
         GET_M2_MATRIX("md2","MSD2",(1,2,3),(1,2,3)) cout << endl;
         GET_M2_MATRIX("me2","MSE2",(1,2,3),(1,2,3)) cout << endl;
         GET_M2_MATRIX("ml2","MSL2",(1,2,3),(1,2,3)) cout << endl;

         cout << endl;

         /// NEW! Tests of override setters

         cout << "Testing set_override functions" << endl;

         cout << "Original M1:" << spec->get_mass_parameter("M1") << endl;
         spec->set_override_mass_parameter(-666,"M1");
         cout << "Override M1:" << spec->get_mass_parameter("M1") << endl;

         cout << "Original ~e-(1):" << spec->get_Pole_Mass("~e-",1) << endl;
         spec->set_override_Pole_Mass(-667,"~e-",1);
         cout << "Override ~e-(1):" << spec->get_Pole_Mass("~e-",1) << endl;

         cout << "Original ml2(1,1):" << spec->get_mass2_parameter("ml2",1,1) << endl;
         spec->set_override_mass2_parameter(-668,"ml2",1,1);
         cout << "Override ml2(1,1):" << spec->get_mass2_parameter("ml2",1,1) << endl;

         /// Now add some entry that didn't exist before
         cout << "has 'new_entry'? " << spec->has_mass_parameter("new_entry") << endl;
         cout << "..." << endl;
         /// Note: if we try to do it like this, it should fail:
         //spec->set_override_mass2_parameter(-1234,"new_entry"); // incorrect: safety still on
         spec->set_override_mass_parameter(-1234,"new_entry",false); // correct: safety check turned off
         cout << "has 'new_entry'? " << spec->has_mass_parameter("new_entry") << endl;
         cout << "new_entry = " << spec->get_mass_parameter("new_entry") << endl;
         cout << endl;


         // Things left to add to demo:
         // - Tree-level masses
         // - Standard Model mixings (need to be added to MSSMSpec as well)
         // - some extra stuff to do regarding organising Standard Model input
         //   parameters (and computing/transferring the pole masses)

         cout << "Test report:" << std::endl << report.str();

         SpecBit_warning().raise(LOCAL_INFO,"\n *** Stopped on purpose to examine spectrum contents ***");
         result = 0;
      }
      //else if(spinfo.find(k3) != spinfo.end())
      //{
      //   std::cout << "Bad spectrum: " << spinfo.at(3) << std::endl;
      //   result = 1;
      //}
      else if(spinfo.find(k4) != spinfo.end())
      {
         std::cout << "Bad spectrum: " << spinfo.at(4) << std::endl;
         result = 1;
      }
      else
      {
         SpecBit_error().raise(LOCAL_INFO,"Bug in exampleRead 'if' logic");
      }
   }

  }
}













