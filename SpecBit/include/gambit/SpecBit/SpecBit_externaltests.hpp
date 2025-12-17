//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Test functions for Spectrum object
///
///  These functions test various aspects of the
///  Spectrum class and related classes. They are
///  not dependent on any other parts of Gambit,
///  so that Spectrum object test code can be
///  compiled and run seperately from Gambit, but
///  but also be run from inside Gambit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///    \date 2014 Dec, 2015 Jan - Mar
///
///  *********************************************

#ifndef __SpecBit_tests_hpp__
#define __SpecBit_tests_hpp__

#include "gambit/SpecBit/MSSMSpec.hpp"
#include "gambit/SpecBit/model_files_and_boxes.hpp"

// Flexible SUSY stuff (should not be needed by the rest of gambit)
#include "flexiblesusy/src/ew_input.hpp"
#include "flexiblesusy/src/numerics2.hpp"
#include "flexiblesusy/src/wrappers.hpp"

// Switch test output depending on where this is being compiled
#ifdef IN_SPECBIT
  #define OUTPUT logger()
  #define TAGerr LogTags::err
  #define TAGfatal LogTags::fatal
  #define TAGeom EOM
#else
  #define OUTPUT std::cerr
  #define TAGerr ""
  #define TAGfatal ""
  #define TAGeom ""
#endif



namespace Gambit
{

   namespace SpecBit
   {

      bool print_error(bool pass, std::string get_type, std::string data,
                       double sting_get_out, double data_member,
                       int i = -1, int j = -1)
      {
         OUTPUT << " returning fail on test for: " << std::endl;
         if (i > -1) OUTPUT << "with first index = " << i << std::endl;
         if (j > -1) OUTPUT << "with second index = " << j << std::endl;
         OUTPUT << get_type << " with " << data << " string arg."  <<std::endl;
         OUTPUT << "string getter gives = "
                <<sting_get_out  << std::endl;
         OUTPUT << "data member is = "
                << data_member  << std::endl;
         OUTPUT << TAGerr << TAGfatal << TAGeom;
         return pass;

      }

      void print_error(std::string get_type, std::string name,
                       double sting_get_out, double data_member,
                       int i = -1, int j = -1)
      {
         OUTPUT << " returning fail on test for: " << std::endl;
         if (i > -1) OUTPUT << "with first index = " << i << std::endl;
         if (j > -1) OUTPUT << "with second index = " << j << std::endl;
         OUTPUT << get_type << " with " << name << " string arg."
                <<std::endl;
         OUTPUT << "string getter gives = " <<sting_get_out  << std::endl;
         OUTPUT << "data member is = "
                << data_member  << std::endl;
         OUTPUT << TAGerr << TAGfatal << TAGeom;
      }

      bool test_getters(std::string get_type,
                        std::string name, double getter_output,
                        double data_member, int i = -1, int j = -1)
      {
         bool pass = flexiblesusy::is_equal(getter_output,data_member);
         // if(pass == false) return pass;
         if(pass == false)
            print_error(get_type, name, getter_output, data_member,i,j);
         return pass;
      }


      /// Module convenience functions
      // These are not known to Gambit

      template <class M>
      bool TestMssmParMass2_0(SubSpectrum * spec, M FSmssm,
                              bool immediate_exit = true)
      {
         bool pass = false;
         //do all in loop

         // Ben: No initializer lists allowed; changing all these.
         //std::set<std::pair<std::string,double>> name_value = {
         //   {"BMu", FSmssm.get_BMu()},
         //   {"mHd2", FSmssm.get_mHd2()},
         //   {"mHu2", FSmssm.get_mHu2()}
         //};

         std::set<std::pair<std::string,double>> name_value;
         name_value.insert(std::make_pair( "BMu" , FSmssm.get_BMu()  ));
         name_value.insert(std::make_pair( "mHd2", FSmssm.get_mHd2() ));
         name_value.insert(std::make_pair( "mHu2", FSmssm.get_mHu2() ));

         std::set<std::pair<std::string, double>>::iterator iter;
         for(iter=name_value.begin(); iter != name_value.end(); ++iter)
            {
               pass = test_getters("get_mass2_parameter", iter->first,
                                   spec->
                                   get_mass2_parameter(iter->first),
                                   iter->second);
               if(immediate_exit == true && pass == false) return pass;
            }

         return pass;
      }


      template <class MI>
      bool TestMssmParMass2_0(MSSMSpec<MI>& mssm, typename MI::Model& FSmssm,
                              bool immediate_exit = true)
      {
         bool pass = false;
         //do all in loop
         std::set<std::pair<std::string,double>> name_value;
         name_value.insert(std::make_pair( "BMu" , FSmssm.get_BMu()  ));
         name_value.insert(std::make_pair( "mHd2", FSmssm.get_mHd2() ));
         name_value.insert(std::make_pair( "mHu2", FSmssm.get_mHu2() ));

         std::set<std::pair<std::string, double>>::iterator iter;
         for(iter=name_value.begin(); iter != name_value.end(); ++iter)
            {
               pass = test_getters("get_mass2_parameter", iter->first,
                                   mssm.
                                   get_mass2_parameter(iter->first),
                                   iter->second);
               if(immediate_exit == true && pass == false) return pass;
            }

         return pass;
      }




    template <class M>
    bool TestMssmParMass2_2(SubSpectrum * spec, M FSmssm,
                            bool immediate_exit=true)
    {
       bool pass = false;

       for(int i=1; i<=3; i++){
          for(int j=1; j<=3; j++){
             //Would be smarter to take these out of for loop and
             // use function pointers, but I won't.
             std::set<std::pair<std::string,double>> name_value;
             name_value.insert(std::make_pair( "mq2", FSmssm.get_mq2(i-1,j-1) ));
             name_value.insert(std::make_pair( "mu2", FSmssm.get_mu2(i-1,j-1) ));
             name_value.insert(std::make_pair( "md2", FSmssm.get_md2(i-1,j-1) ));
             name_value.insert(std::make_pair( "ml2", FSmssm.get_ml2(i-1,j-1) ));
             name_value.insert(std::make_pair( "me2", FSmssm.get_me2(i-1,j-1) ));

             std::set<std::pair<std::string, double>>::iterator iter;
             for(iter=name_value.begin(); iter != name_value.end(); ++iter)
                {
                   pass = test_getters("get_mass2_parameter", iter->first,
                                       spec->
                                       get_mass2_parameter(iter->first,i,j),
                                       iter->second, i, j);
                   if(immediate_exit == true && pass == false) return pass;
                }
          }
       }
       return pass;
    }


      template <class MI>
    bool TestMssmParMass2_2(MSSMSpec<MI>& mssm, typename MI::Model& FSmssm,
                            bool immediate_exit=true)
    {
       bool pass = false;

       for(int i=1; i<=3; i++){
          for(int j=1; j<=3; j++){
             //Would be smarter to take these out of for loop and
             // use function pointers, but I won't.
             std::set<std::pair<std::string,double>> name_value;
             name_value.insert(std::make_pair( "mq2", FSmssm.get_mq2(i-1,j-1) ));
             name_value.insert(std::make_pair( "mu2", FSmssm.get_mu2(i-1,j-1) ));
             name_value.insert(std::make_pair( "md2", FSmssm.get_md2(i-1,j-1) ));
             name_value.insert(std::make_pair( "ml2", FSmssm.get_ml2(i-1,j-1) ));
             name_value.insert(std::make_pair( "me2", FSmssm.get_me2(i-1,j-1) ));

             std::set<std::pair<std::string, double>>::iterator iter;
             for(iter=name_value.begin(); iter != name_value.end(); ++iter)
                {
                   pass = test_getters("get_mass2_parameter", iter->first,
                                       mssm.
                                       get_mass2_parameter(iter->first,i,j),
                                       iter->second, i, j);
                   if(immediate_exit == true && pass == false) return pass;
                }
          }
       }
       return pass;
    }


      template <class M>
      bool TestMssmParMass1_0(SubSpectrum * spec, M FSmssm,
                              bool immediate_exit=true)
      {
         bool pass = false;

         std::set<std::pair<std::string,double>> name_value;
         name_value.insert(std::make_pair( "M1", FSmssm.get_MassB()  ));
         name_value.insert(std::make_pair( "M2", FSmssm.get_MassWB() ));
         name_value.insert(std::make_pair( "M3", FSmssm.get_MassG()  ));
         name_value.insert(std::make_pair( "vu", FSmssm.get_vu()     ));
         name_value.insert(std::make_pair( "vd", FSmssm.get_vd()     ));

         std::set<std::pair<std::string, double>>::iterator iter;
         for(iter=name_value.begin(); iter != name_value.end(); ++iter)
            {
               pass = test_getters("get_mass_parameter", iter->first,
                                   spec->
                                   get_mass_parameter(iter->first),
                                   iter->second);
               if(immediate_exit == true && pass == false) return pass;
            }

         return pass;
      }

      template <class MI>
      bool TestMssmParMass1_0(MSSMSpec<MI>& mssm, typename MI::Model& FSmssm,
                              bool immediate_exit=true)
      {
         bool pass = false;

         std::set<std::pair<std::string,double>> name_value;
         name_value.insert(std::make_pair( "M1", FSmssm.get_MassB()  ));
         name_value.insert(std::make_pair( "M2", FSmssm.get_MassWB() ));
         name_value.insert(std::make_pair( "M3", FSmssm.get_MassG()  ));
         name_value.insert(std::make_pair( "vu", FSmssm.get_vu()     ));
         name_value.insert(std::make_pair( "vd", FSmssm.get_vd()     ));

         std::set<std::pair<std::string, double>>::iterator iter;
         for(iter=name_value.begin(); iter != name_value.end(); ++iter)
            {
               pass = test_getters("get_mass_parameter", iter->first,
                                   mssm.
                                   get_mass_parameter(iter->first),
                                   iter->second);
               if(immediate_exit == true && pass == false) return pass;
            }

         return pass;
      }



      template <class M>
      bool TestMssmParMass1_2(SubSpectrum * spec, M FSmssm,
                              bool immediate_exit =true)
      {
         bool pass = false;
         for(int i=1; i<=3; i++){
            for(int j=1; j<=3; j++){
                std::set<std::pair<std::string,double>> name_value;
                name_value.insert(std::make_pair( "TYd", FSmssm.get_TYd(i-1,j-1) ));
                name_value.insert(std::make_pair( "TYu", FSmssm.get_TYu(i-1,j-1) ));
                name_value.insert(std::make_pair( "TYe", FSmssm.get_TYe(i-1,j-1) ));

                std::set<std::pair<std::string, double>>::iterator iter;
                for(iter=name_value.begin(); iter != name_value.end(); ++iter)
                {
                   pass = test_getters("get_mass_parameter", iter->first,
                                       spec->
                                       get_mass_parameter(iter->first,i,j),
                                       iter->second, i, j);
                   if(immediate_exit == true && pass == false) return pass;
                }
             }
          }
          return pass;
       }


      template <class MI>
      bool TestMssmParMass1_2(MSSMSpec<MI>& mssm, typename MI::Model& FSmssm,
                              bool immediate_exit =true)
      {
         bool pass = false;
         for(int i=1; i<=3; i++){
            for(int j=1; j<=3; j++){
                std::set<std::pair<std::string,double>> name_value;
                name_value.insert(std::make_pair( "TYd", FSmssm.get_TYd(i-1,j-1) ));
                name_value.insert(std::make_pair( "TYu", FSmssm.get_TYu(i-1,j-1) ));
                name_value.insert(std::make_pair( "TYe", FSmssm.get_TYe(i-1,j-1) ));

                std::set<std::pair<std::string, double>>::iterator iter;
                for(iter=name_value.begin(); iter != name_value.end(); ++iter)
                {
                   pass = test_getters("get_mass_parameter", iter->first,
                                       mssm.
                                       get_mass_parameter(iter->first,i,j),
                                       iter->second, i, j);
                   if(immediate_exit == true && pass == false) return pass;
                }
            }
         }
         return pass;
      }

    template <class M>
    bool TestMssmParMass0_0(SubSpectrum * spec, M FSmssm,
                            bool immediate_exit =true )
    {
       bool pass = false;
       std::set<std::pair<std::string,double>> name_value;
       name_value.insert(std::make_pair( "g1", FSmssm.get_g1() ));
       name_value.insert(std::make_pair( "g2", FSmssm.get_g2() ));
       name_value.insert(std::make_pair( "g3", FSmssm.get_g3() ));

       std::set<std::pair<std::string, double>>::iterator iter;
       for(iter=name_value.begin(); iter != name_value.end(); ++iter)
       {
          pass = test_getters("get_dimensionless_parameter", iter->first,
                              spec->
                              get_dimensionless_parameter(iter->first),
                              iter->second);
          if(immediate_exit == true && pass == false) return pass;
       }

       return pass;
    }


    template <class MI>
    bool TestMssmParMass0_0(MSSMSpec<MI>& mssm, typename MI::Model& FSmssm,
                               bool immediate_exit =true )
    {
       bool pass = false;
       std::set<std::pair<std::string,double>> name_value;
       name_value.insert(std::make_pair( "g1", FSmssm.get_g1() ));
       name_value.insert(std::make_pair( "g2", FSmssm.get_g2() ));
       name_value.insert(std::make_pair( "g3", FSmssm.get_g3() ));

       std::set<std::pair<std::string, double>>::iterator iter;
       for(iter=name_value.begin(); iter != name_value.end(); ++iter)
       {
          pass = test_getters("get_dimensionless_parameter", iter->first,
                              mssm.
                              get_dimensionless_parameter(iter->first),
                              iter->second);
          if(immediate_exit == true && pass == false) return pass;
       }

       return pass;
    }

    template <class M>
    bool TestMssmParMass0_2(SubSpectrum * spec, M FSmssm,
                               bool immediate_exit = true)
    {
       bool pass = false;
       for(int i=1; i<=3; i++){
          for(int j=1; j<=3; j++){

             std::set<std::pair<std::string,double>> name_value;
             name_value.insert(std::make_pair( "Yd", FSmssm.get_Yd(i-1,j-1) ));
             name_value.insert(std::make_pair( "Yu", FSmssm.get_Yu(i-1,j-1) ));
             name_value.insert(std::make_pair( "Ye", FSmssm.get_Ye(i-1,j-1) ));

             std::set<std::pair<std::string, double>>::iterator iter;
             for(iter=name_value.begin(); iter != name_value.end(); ++iter)
             {
                pass = test_getters("get_dimensionless_parameter",
                                    iter->first,
                                    spec->
                                    get_dimensionless_parameter(iter->first,
                                                                i,j),
                                    iter->second, i, j);
                if(immediate_exit == true && pass == false) return pass;
             }
          }
       }
       return pass;
    }


      template <class MI>
      bool TestMssmParMass0_2(MSSMSpec<MI>& mssm, typename MI::Model& FSmssm,
                               bool immediate_exit = true)
      {
       bool pass = false;
       for(int i=1; i<=3; i++){
          for(int j=1; j<=3; j++){

             std::set<std::pair<std::string,double>> name_value;
             name_value.insert(std::make_pair( "Yd", FSmssm.get_Yd(i-1,j-1) ));
             name_value.insert(std::make_pair( "Yu", FSmssm.get_Yu(i-1,j-1) ));
             name_value.insert(std::make_pair( "Ye", FSmssm.get_Ye(i-1,j-1) ));

             std::set<std::pair<std::string, double>>::iterator iter;
             for(iter=name_value.begin(); iter != name_value.end(); ++iter)
             {
                pass = test_getters("get_dimensionless_parameter",
                                    iter->first,
                                    mssm.
                                    get_dimensionless_parameter(iter->first,
                                                                i,j),
                                    iter->second, i, j);
                if(immediate_exit == true && pass == false) return pass;
             }
          }
       }
       return pass;
    }

    template <class M>
    bool TestMssmPoleGets0(SubSpectrum * spec, M FSmssm,
                           bool immediate_exit = true)
    {
       bool pass = false;
       //do all in loop
       std::set<std::pair<std::string,double>> name_value;
       name_value.insert(std::make_pair( "MZ", FSmssm.get_physical().MVZ       ));
       name_value.insert(std::make_pair( "MW", FSmssm.get_physical().MVWm      ));
       name_value.insert(std::make_pair( "MGluino", FSmssm.get_physical().MGlu ));
       name_value.insert(std::make_pair( "MGluon", FSmssm.get_physical().MVG   ));
       name_value.insert(std::make_pair( "MPhoton", FSmssm.get_physical().MVP  ));

       std::set<std::pair<std::string, double>>::iterator iter;
       for(iter=name_value.begin(); iter != name_value.end(); ++iter)
       {
          pass = test_getters("get_Pole_Mass", iter->first,
                              spec->get_Pole_Mass(iter->first),
                              iter->second);
          if(immediate_exit == true && pass == false) return pass;
       }
       return pass;
    }


    template <class MI>
    bool TestMssmPoleGets0(MSSMSpec<MI>& mssm, typename MI::Model& FSmssm,
                           bool immediate_exit = true)
    {
       bool pass = false;
       //do all in loop
       std::set<std::pair<std::string,double>> name_value;
       name_value.insert(std::make_pair( "MZ", FSmssm.get_physical().MVZ       ));
       name_value.insert(std::make_pair( "MW", FSmssm.get_physical().MVWm      ));
       name_value.insert(std::make_pair( "MGluino", FSmssm.get_physical().MGlu ));
       name_value.insert(std::make_pair( "MGluon", FSmssm.get_physical().MVG   ));
       name_value.insert(std::make_pair( "MPhoton", FSmssm.get_physical().MVP  ));

       std::set<std::pair<std::string, double>>::iterator iter;
       for(iter=name_value.begin(); iter != name_value.end(); ++iter)
       {
          pass = test_getters("get_Pole_Mass", iter->first,
                              mssm.get_Pole_Mass(iter->first),
                              iter->second);
          if(immediate_exit == true && pass == false) return pass;
       }
       return pass;
    }


    template <class M>
    bool TestMssmPoleGets1(SubSpectrum * spec, M FSmssm,
                           bool immediate_exit = true)
    {
       bool pass = false;

       for(int i=1; i<=6; i++){
         std::set<std::pair<std::string,double>> name_value;
         name_value.insert(std::make_pair( "MSd", FSmssm.get_physical().MSd(i-1) ));
         name_value.insert(std::make_pair( "MSu", FSmssm.get_physical().MSu(i-1) ));
         name_value.insert(std::make_pair( "MSe", FSmssm.get_physical().MSe(i-1) ));


         std::set<std::pair<std::string, double>>::iterator iter;
         for(iter=name_value.begin(); iter != name_value.end(); ++iter)
         {
            pass = test_getters("get_Pole_Mass", iter->first,
                                spec->get_Pole_Mass(iter->first,i),
                                iter->second, i);
            if(immediate_exit == true && pass == false) return pass;
         }

       }
       for(int i=1; i<=3; i++){

          std::set<std::pair<std::string,double>> name_value;
          name_value.insert(std::make_pair( "MSv", FSmssm.get_physical().MSv(i-1) ));
          name_value.insert(std::make_pair( "MFd", FSmssm.get_physical().MFd(i-1) ));
          name_value.insert(std::make_pair( "MFu", FSmssm.get_physical().MFu(i-1) ));
          name_value.insert(std::make_pair( "MFe", FSmssm.get_physical().MFe(i-1) ));

          std::set<std::pair<std::string, double>>::iterator iter;
          for(iter=name_value.begin(); iter != name_value.end(); ++iter)
          {
             pass = test_getters("get_Pole_Mass", iter->first,
                                 spec->get_Pole_Mass(iter->first,i),
                                 iter->second, i);
             if(immediate_exit == true && pass == false) return pass;
          }

       }
       for(int i=1; i<=2; i++){
          std::string name = "Mh0";
          pass = test_getters("get_Pole_Mass", name,
                                      spec->get_Pole_Mass(name,i),
                                      FSmssm.get_physical().Mhh(i-1), i);
          if(immediate_exit == true && pass == false) return pass;
          name = "MCha";
          pass = test_getters("get_Pole_Mass", name,
                              spec->get_Pole_Mass(name,i),
                              FSmssm.get_physical_slha().MCha(i-1), i);
          if(immediate_exit == true && pass == false) return pass;
       }
       // In the neutralino and chargino tests I compare against
       // value in physical_slha struct since the value in
       // physical may differ by a sign since it stores positive masses
       // and a complex mixing matrix.
       for(int i=1; i<=4; i++){
          std::string name = "MChi";
          pass = test_getters("get_Pole_Mass", name,
                              spec->get_Pole_Mass(name,i),
                              FSmssm.get_physical_slha().MChi(i-1), i);
          if(immediate_exit == true && pass == false) return pass;
       }
       return pass;
    }


     template <class MI>
    bool TestMssmPoleGets1(MSSMSpec<MI>& mssm, typename MI::Model& FSmssm,
                           bool immediate_exit = true)
    {
       bool pass = false;

       for(int i=1; i<=6; i++){
         std::set<std::pair<std::string,double>> name_value;
         name_value.insert(std::make_pair( "MSd", FSmssm.get_physical().MSd(i-1) ));
         name_value.insert(std::make_pair( "MSu", FSmssm.get_physical().MSu(i-1) ));
         name_value.insert(std::make_pair( "MSe", FSmssm.get_physical().MSe(i-1) ));

         std::set<std::pair<std::string, double>>::iterator iter;
         for(iter=name_value.begin(); iter != name_value.end(); ++iter)
         {
            pass = test_getters("get_Pole_Mass", iter->first,
                                mssm.get_Pole_Mass(iter->first,i),
                                iter->second, i);
            if(immediate_exit == true && pass == false) return pass;
         }

       }
       for(int i=1; i<=3; i++){

          std::set<std::pair<std::string,double>> name_value;
          name_value.insert(std::make_pair( "MSv", FSmssm.get_physical().MSv(i-1) ));
          name_value.insert(std::make_pair( "MFd", FSmssm.get_physical().MFd(i-1) ));
          name_value.insert(std::make_pair( "MFu", FSmssm.get_physical().MFu(i-1) ));
          name_value.insert(std::make_pair( "MFe", FSmssm.get_physical().MFe(i-1) ));

          std::set<std::pair<std::string, double>>::iterator iter;
          for(iter=name_value.begin(); iter != name_value.end(); ++iter)
          {
             pass = test_getters("get_Pole_Mass", iter->first,
                                 mssm.get_Pole_Mass(iter->first,i),
                                 iter->second, i);
             if(immediate_exit == true && pass == false) return pass;
          }

       }
       for(int i=1; i<=2; i++){
          std::string name = "Mh0";
          pass = test_getters("get_Pole_Mass", name,
                                      mssm.get_Pole_Mass(name,i),
                                      FSmssm.get_physical().Mhh(i-1), i);
          if(immediate_exit == true && pass == false) return pass;
          name = "MCha";
          pass = test_getters("get_Pole_Mass", name,
                              mssm.get_Pole_Mass(name,i),
                              FSmssm.get_physical_slha().MCha(i-1), i);
          if(immediate_exit == true && pass == false) return pass;
       }
       // In the neutralino and chargino tests I compare against
       // value in physical_slha struct since the value in
       // physical may differ by a sign since it stores positive masses
       // and a complex mixing matrix.
       for(int i=1; i<=4; i++){
          std::string name = "MChi";
          pass = test_getters("get_Pole_Mass", name,
                              mssm.get_Pole_Mass(name,i),
                              FSmssm.get_physical_slha().MChi(i-1), i);
          if(immediate_exit == true && pass == false) return pass;
       }
       return pass;
    }


     template <class M>
     bool TestMssmPoleMixingGets2(SubSpectrum * spec, M FSmssm,
                                  bool immediate_exit = true)
     {
        bool pass = false;
        for(int i=1; i<=6; i++){
           for(int j=1; j<=6; j++){
              std::set<std::pair<std::string,double>> name_value;
              name_value.insert(std::make_pair( "~d", FSmssm.get_physical_slha().ZD(i-1,j-1) ));
              name_value.insert(std::make_pair( "~u", FSmssm.get_physical_slha().ZU(i-1,j-1) ));
              name_value.insert(std::make_pair( "~e-", FSmssm.get_physical_slha().ZE(i-1,j-1) ));

              std::set<std::pair<std::string, double>>::iterator iter;
              for(iter=name_value.begin(); iter != name_value.end(); ++iter)
              {
                 pass = test_getters("get_Pole_Mixing", iter->first,
                                     spec->
                                     get_Pole_Mixing(iter->first,i,j),
                                     iter->second, i, j);
                 if(immediate_exit == true && pass == false) return pass;
              }
           }
        }


        for(int i=1; i<=3; i++){
           for(int j=1; j<=3; j++){
              string name = "~nu";
              pass = test_getters("get_Pole_Mixing", name,
                                  spec->get_Pole_Mixing(name,i,j),
                                  FSmssm.get_physical_slha().ZV(i-1, j-1), i,j);
              if(immediate_exit == true && pass == false) return pass;

              }
           }


        for(int i=1; i<=2; i++){
           for(int j=1; j<=2; j++){
              std::set<std::pair<std::string,double>> name_value;
              name_value.insert(std::make_pair( "h0",   FSmssm.get_physical_slha().ZH(i-1,j-1) ));
              name_value.insert(std::make_pair( "A0",   FSmssm.get_physical_slha().ZA(i-1,j-1) ));
              name_value.insert(std::make_pair( "H+", FSmssm.get_physical_slha().ZP(i-1,j-1) ));
              name_value.insert(std::make_pair( "~chi-", flexiblesusy::Re(FSmssm.get_physical_slha()
                                     .UM(i-1,j-1)) ));
              name_value.insert(std::make_pair( "~chi+", flexiblesusy::Re(FSmssm.get_physical_slha()
                                     .UP(i-1,j-1)) ));


              std::set<std::pair<std::string, double>>::iterator iter;
              for(iter=name_value.begin(); iter != name_value.end(); ++iter)
              {
                 pass = test_getters("get_Pole_Mixing", iter->first,
                                     spec->
                                     get_Pole_Mixing(iter->first,i,j),
                                     iter->second, i, j);
                 if(immediate_exit == true && pass == false) return pass;
              }
           }
       }

        return pass;
    }


       template <class MI>
     bool TestMssmPoleMixingGets2(MSSMSpec<MI>& mssm, typename MI::Model& FSmssm,
                                  bool immediate_exit = true)
     {
        bool pass = false;
        for(int i=1; i<=6; i++){
           for(int j=1; j<=6; j++){
              std::set<std::pair<std::string,double>> name_value;
              name_value.insert(std::make_pair( "~d", FSmssm.get_physical_slha().ZD(i-1,j-1) ));
              name_value.insert(std::make_pair( "~u", FSmssm.get_physical_slha().ZU(i-1,j-1) ));
              name_value.insert(std::make_pair( "~e-", FSmssm.get_physical_slha().ZE(i-1,j-1) ));

              std::set<std::pair<std::string, double>>::iterator iter;
              for(iter=name_value.begin(); iter != name_value.end(); ++iter)
              {
                 pass = test_getters("get_Pole_Mixing", iter->first,
                                     mssm.
                                     get_Pole_Mixing(iter->first,i,j),
                                     iter->second, i, j);
                 if(immediate_exit == true && pass == false) return pass;
              }
           }
        }


        for(int i=1; i<=3; i++){
           for(int j=1; j<=3; j++){
              string name = "~nu";
              pass = test_getters("get_Pole_Mixing", name,
                                  mssm.get_Pole_Mixing(name,i,j),
                                  FSmssm.get_physical_slha().ZV(i-1, j-1), i,j);
              if(immediate_exit == true && pass == false) return pass;

              }
           }


        for(int i=1; i<=2; i++){
           for(int j=1; j<=2; j++){
              std::set<std::pair<std::string,double>> name_value;
              name_value.insert(std::make_pair( "h0",   FSmssm.get_physical_slha().ZH(i-1,j-1) ));
              name_value.insert(std::make_pair( "A0",   FSmssm.get_physical_slha().ZA(i-1,j-1) ));
              name_value.insert(std::make_pair( "H+", FSmssm.get_physical_slha().ZP(i-1,j-1) ));
              name_value.insert(std::make_pair( "~chi-", flexiblesusy::Re(FSmssm.get_physical_slha()
                                     .UM(i-1,j-1)) ));
              name_value.insert(std::make_pair( "~chi+", flexiblesusy::Re(FSmssm.get_physical_slha()
                                     .UP(i-1,j-1)) ));

              std::set<std::pair<std::string, double>>::iterator iter;
              for(iter=name_value.begin(); iter != name_value.end(); ++iter)
              {
                 pass = test_getters("get_Pole_Mixing", iter->first,
                                     mssm.
                                     get_Pole_Mixing(iter->first,i,j),
                                     iter->second, i, j);
                 if(immediate_exit == true && pass == false) return pass;
              }
           }
       }

       return pass;
    }


    template <class M>
    bool TestMssmPoleGets(SubSpectrum * spec, M FSmssm)
    {
       bool pass = false;
       pass = TestMssmPoleGets0(spec,FSmssm);
       if(pass == false) return pass;
        pass = TestMssmPoleGets1(spec,FSmssm);
       if(pass == false) return pass;
       pass = TestMssmPoleMixingGets2(spec,FSmssm);
       if(pass == false) return pass;
       return pass;
    }

    template <class MI>
    bool TestMssmPoleGets(MSSMSpec<MI>& mssm, typename MI::Model& FSmssm)
    {
       bool pass = false;
       pass = TestMssmPoleGets0(mssm,FSmssm);
       if(pass == false) return pass;
        pass = TestMssmPoleGets1(mssm,FSmssm);
       if(pass == false) return pass;
       pass = TestMssmPoleMixingGets2(mssm,FSmssm);
       if(pass == false) return pass;
       return pass;
    }

    template <class M>
    bool TestMssmParGets(SubSpectrum * spec, M FSmssm)
    {
       bool pass = false;
       pass = TestMssmParMass2_0(spec,FSmssm);
       if(pass == false) return pass;
       pass = TestMssmParMass2_2(spec,FSmssm);
       if(pass == false) return pass;
       pass = TestMssmParMass1_0(spec,FSmssm);
       if(pass == false) return pass;
       pass = TestMssmParMass1_2(spec,FSmssm);
       if(pass == false) return pass;
       pass = TestMssmParMass0_0(spec,FSmssm);
       if(pass == false) return pass;
       pass = TestMssmParMass0_2(spec,FSmssm);
       if(pass == false) return pass;

       return pass;

    }

     template <class MI>
    bool TestMssmParGets(MSSMSpec<MI>& mssm, typename MI::Model& FSmssm)
    {
       bool pass = false;
       pass = TestMssmParMass2_0(mssm,FSmssm);
       if(pass == false) return pass;
       pass = TestMssmParMass2_2(mssm,FSmssm);
       if(pass == false) return pass;
       pass = TestMssmParMass1_0(mssm,FSmssm);
       if(pass == false) return pass;
       pass = TestMssmParMass1_2(mssm,FSmssm);
       if(pass == false) return pass;
       pass = TestMssmParMass0_0(mssm,FSmssm);
       if(pass == false) return pass;
       pass = TestMssmParMass0_2(mssm,FSmssm);
       if(pass == false) return pass;

       return pass;

    }

    template <class Model>
    void setup(Model& mssm)
    {
       Eigen::Matrix<double,3,3> Yu;
       Eigen::Matrix<double,3,3> Yd;
       Eigen::Matrix<double,3,3> Ye;
       double Mu;
       double g1;
       double g2;
       double g3;
       double vd;
       double vu;
       Eigen::Matrix<double,3,3> TYu;
       Eigen::Matrix<double,3,3> TYd;
       Eigen::Matrix<double,3,3> TYe;
       double BMu;
       Eigen::Matrix<double,3,3> mq2;
       Eigen::Matrix<double,3,3> ml2;
       double mHd2;
       double mHu2;
       Eigen::Matrix<double,3,3> md2;
       Eigen::Matrix<double,3,3> mu2;
       Eigen::Matrix<double,3,3> me2;
       double MassB;
       double MassWB;
       double MassG;

       // susy parameters
       Yu << 1.26136e-05, 0, 0,
                       0, 0.00667469, 0,
                       0, 0, 0.857849;

       Yd << 0.000242026, 0, 0,
                       0, 0.00529911, 0,
                       0, 0, 0.193602;

       Ye << 2.84161e-05, 0, 0,
                       0, 0.00587557, 0,
                       0, 0, 0.10199;

       Mu = 627.164;
       g1 = 0.468171;
       g2 = 0.642353;
       g3 = 1.06459;
       vd = 25.0944;
       vu = 242.968;

       // soft parameters
       TYu << -0.0144387, 0, 0,
                       0, -7.64037, 0,
                       0, 0, -759.305;

       TYd << -0.336207, 0, 0,
                      0, -7.36109, 0,
                      0, 0, -250.124;

       TYe << -0.00825134, 0, 0,
                        0, -1.70609, 0,
                        0, 0, -29.4466;

       BMu = 52140.8;

       mq2 << 1.03883e+06, 0, 0,
                        0, 1.03881e+06, 0,
                        0, 0, 879135;

       ml2 << 124856, 0, 0,
                   0, 124853, 0,
                   0, 0, 124142;

       mHd2 = 92436.9;
       mHu2 = -380337;

       md2 << 954454, 0, 0,
                   0, 954439, 0,
                   0, 0, 934727;

       mu2 << 963422, 0, 0,
                   0, 963400, 0,
                   0, 0, 656621;

       me2 << 49215.8, 0, 0,
                    0, 49210.9, 0,
                    0, 0, 47759.2;

       MassB = 210.328;
       MassWB = 389.189;
       MassG = 1114.45;

       // set parameters
       mssm.set_scale(flexiblesusy::Electroweak_constants::MZ);
       mssm.set_Yu(Yu);
       mssm.set_Yd(Yd);
       mssm.set_Ye(Ye);
       mssm.set_Mu(Mu);
       mssm.set_g1(g1);
       mssm.set_g2(g2);
       mssm.set_g3(g3);
       mssm.set_vd(vd);
       mssm.set_vu(vu);
       mssm.set_TYu(TYu);
       mssm.set_TYd(TYd);
       mssm.set_TYe(TYe);
       mssm.set_BMu(BMu);
       mssm.set_mq2(mq2);
       mssm.set_ml2(ml2);
       mssm.set_mHd2(mHd2);
       mssm.set_mHu2(mHu2);
       mssm.set_md2(md2);
       mssm.set_mu2(mu2);
       mssm.set_me2(me2);
       mssm.set_MassB(MassB);
       mssm.set_MassWB(MassWB);
       mssm.set_MassG(MassG);
    }


      template <class MI>
      bool test_exact(MSSMSpec<MI>& mssm, typename MI::Model& FS_model_slha)
      {
         bool pass = TestMssmParGets(mssm,FS_model_slha);
         if(pass == false)
            {
               OUTPUT << "TestMssmParGets failing."  <<std::endl;
               return pass;
            }
         pass = TestMssmPoleGets(mssm,FS_model_slha);
         if(pass == false)
            {
               OUTPUT << "TestMssmParGets failing."  <<std::endl;
               return pass;
            }


         return pass;
      }

      template <class M>
      double test_exact(SubSpectrum * spec, M FS_model_slha)
      {
         bool pass = TestMssmParGets(spec,FS_model_slha);
         if(pass == false)
            {
               OUTPUT << "TestMssmParGets failing."  <<std::endl;
               return pass;
            }
         pass = TestMssmPoleGets(spec,FS_model_slha);
         if(pass == false)
            {
               OUTPUT << "TestMssmParGets failing."  <<std::endl;
               return pass;
            }

         return pass;

      }
      //This gives identical results after running up, so don't need messy
      // Test_close
      template <class MI>
       bool running_test(MSSMSpec<MI> & mssm, typename MI::Model & FS_model_slha, double tol)
      {
         double highscale = 1e+16;
         double lowscale = mssm.GetScale();
         double lowscale2 = FS_model_slha.get_scale();
         bool pass = flexiblesusy::is_equal(lowscale,lowscale2);
         if(!pass) {
            OUTPUT << "test fail: "
                   << "objects not at same scale at start of runtest."
                   << std::endl;
            return pass;
         }

         mssm.RunToScale(highscale);
         FS_model_slha.run_to(highscale);
         pass = test_exact(mssm, FS_model_slha);
          if(!pass) {
            OUTPUT << "test fail: "
                   << "objects not the same after running to MGUT."
                   << std::endl;
            return pass;
         }
         mssm.RunToScale(lowscale);
         FS_model_slha.run_to(lowscale);
         pass = test_exact(mssm, FS_model_slha);
          if(!pass) {
            OUTPUT << "test fail: "
                   << "objects not the same after running to lowscale."
                   << std::endl;
            return pass;
         }


         return pass;
      }

      template <class Model>
      bool running_test(SubSpectrum * spec, Model & FS_model_slha,
                   double tol)
      {
         double highscale = 1e+16;
         double lowscale = spec->GetScale();
         double lowscale2 = FS_model_slha.get_scale();
         bool pass = flexiblesusy::is_equal(lowscale,lowscale2);
         if(!pass) {
            OUTPUT << "test fail: "
                   << "objects not at same scale at start of runtest."
                   << std::endl;
            return pass;
         }

         spec->RunToScale(highscale);
         FS_model_slha.run_to(highscale);
         pass = test_exact(spec, FS_model_slha);
          if(!pass) {
            OUTPUT << "test fail: "
                   << "objects not the same after running to MGUT."
                   << std::endl;
            return pass;
         }
         spec->RunToScale(lowscale);
         FS_model_slha.run_to(lowscale);
         pass = test_exact(spec, FS_model_slha);
          if(!pass) {
            OUTPUT << "test fail: "
                   << "objects not the same after running to lowscale."
                   << std::endl;
            return pass;
         }

         return pass;
      }

      // Helper function for tests in Spectrum_test
      bool test_within_tol(double a, double b, double tol, std::string label)
      {
         // Tol is considered as a fraction of a
         bool pass = std::abs(a - b) <= std::abs(a*tol);  // pass == true
         OUTPUT << "TESTING: " << label << std::endl;
         if(!pass)
         {
            OUTPUT << "  ******FAIL******" << std::endl
                   << "  Inputs do not match within requested relative tolerance (" << tol << ")"
                   << std::endl
                   << "  a = " << a << std::endl
                   << "  b = " << b << std::endl
                   << "  |(a - b)/a| = " << std::abs((a-b)/a) << " (greater than tol = " << tol << ")"
                   << std::endl;
         }
         else
         {
            OUTPUT << "  Pass: (a="<<a<<", b="<<b<<")" << std::endl
                   << "  |(a - b)/a| = " << std::abs((a-b)/a) << " (less than tol = " << tol << ")"
                   << std::endl;
         }
         return pass;
      }

      // Test that output of Standard Model wrapper (e.g. QedQcdWrapper) matches
      // SMINPUTS sufficiently accurately
      // Set flag SLHAonly=1 if SMskeleton and/or MSSMskeleton are being used.
      void Spectrum_test(Spectrum matched_spectra, const SubSpectrum* smin, bool SLHAonly=0)
      {
         // Extract pieces of Spectrum to make it clear what they are supposed to be
         SMInputs sminputs = matched_spectra->get_SMInputs();
         std::unique_ptr<SubSpectrum> SM = matched_spectra->clone_LE(); // COPIES Spectrum object
         // const SubSpectrum* SM = matched_spectra->get_LE(); // Cannot do running on original object.

         double tol     = 1e-9; // Demanding matching to 1 part in a billion (pole masses, things that don't change)
         double tolg    = 1e-4; // Seem to get about this level of precision recovering running couplings from QedQcd object.
         double tolm    = 1e-3; //      "         "              "             "                masses     "        "

         // // SLHA1
         // double alphainv;  // 1: Inverse electromagnetic coupling at the Z pole in the MSbar scheme (with 5 active flavours)
         // double GF;        // 2: Fermi constant (in units of GeV^-2)
         // double alphaS;    // 3: Strong coupling at the Z pole in the MSbar scheme (with 5 active flavours).
         // double mZ;        // 4: Z pole mass
         // double mBmB;      // 5: b quark running mass in the MSbar scheme (at mB)
         // double mT;        // 6: Top quark pole mass
         // double mTau;      // 7: Tau pole mass

         // // SLHA2
         // double mNu3;      // 8: Heaviest neutrino pole mass

         // double mE;        // 11: Electron pole mass
         // double mNu1;      // 12: Lightest neutrino pole mass
         // double mMu;       // 13: Muon pole mass
         // double mNu2;      // 14: Second lightest neutrino pole mass

         // double mD;        // 21: d quark running mass in the MSbar scheme at 2 GeV
         // double mU;        // 21: u quark running mass in the MSbar scheme at 2 GeV
         // double mS;        // 21: s quark running mass in the MSbar scheme at 2 GeV
         // double mC;        // 21: c quark running mass in the MSbar scheme at mC

         // First check pole masses
         test_within_tol( sminputs.mZ,   SM->get_Pole_Mass("Z"), tol, "Z pole" );
         //test_within_tol( sminputs.mW,   SM->get_Pole_Mass("W"), tol, "W pole" ); // Whoops, no mW in sminputs.
         test_within_tol( sminputs.mT,   SM->get_Pole_Mass("t"), tol, "top pole" );
         test_within_tol( sminputs.mTau, SM->get_Pole_Mass("tau"), tol, "tau pole" );
         test_within_tol( sminputs.mMu,  SM->get_Pole_Mass("mu"), tol, "mu pole" );
         test_within_tol( sminputs.mE,   SM->get_Pole_Mass("e"), tol, "e pole" );
         //test_within_tol( sminputs.mNu3, SM->get_Pole_Mass(""), tol );
         //test_within_tol( sminputs.mNu2, SM->get_Pole_Mass(""), tol );
         //test_within_tol( sminputs.mNu1, SM->get_Pole_Mass(""), tol );

         // Next check running quantities evaluated at Z pole
         // Note, numerical errors might creep in depending on how we do the running
         // back and forth. Might need to consider some method to "reset" object back
         // to original condition (keep a copy of itself inside?)
         //SM->RunToScale(sminputs.mZ);
         OUTPUT << "Current scale: " << SM->GetScale() << std::endl;
         OUTPUT << "Z pole mass  : " << SM->get_Pole_Mass("Z") << std::endl;
         if(not SLHAonly) test_within_tol( sminputs.alphainv, 1./ SM->get_dimensionless_parameter("alpha"), tol, "1/alpha(mZ)" );
         if(not SLHAonly) test_within_tol( sminputs.alphaS,       SM->get_dimensionless_parameter("alphaS"), tol, "alphaS(mZ)" );

         // Check running quantities evaluated at 2 GeV
         if(not SLHAonly) SM->RunToScale(2);
         OUTPUT << "Current scale: " << SM->GetScale() << std::endl;
         test_within_tol( sminputs.mU, SM->get_mass_parameter("u"), tolm, "mu(2)" );
         test_within_tol( sminputs.mD, SM->get_mass_parameter("d"), tolm, "md(2)" );
         test_within_tol( sminputs.mS, SM->get_mass_parameter("s"), tolm, "ms(2)" );

         // Check mC(mC) and mB(mB)
         if(not SLHAonly){
           SM->RunToScale(sminputs.mCmC);
           OUTPUT << "Current scale: " << SM->GetScale() << std::endl;
           OUTPUT << "mC (MSbar)   : " << SM->get_mass_parameter("c") << std::endl;
           test_within_tol( sminputs.mCmC, SM->get_mass_parameter("c"), tolm, "mc(mc)" );
           SM->RunToScale(sminputs.mBmB);
           OUTPUT << "Current scale: " << SM->GetScale() << std::endl;
           OUTPUT << "mB (MSbar)   : " << SM->get_mass_parameter("b") << std::endl;
           test_within_tol( sminputs.mBmB, SM->get_mass_parameter("b"), tolm, "mb(mb)" );
           OUTPUT << EOM;
         }

         // Check that pre-extracted SM SubSpectrum* and the one from Spectrum object match
         if(not SLHAonly) SM->RunToScale(sminputs.mZ);
         if(not SLHAonly) smin->RunToScale(sminputs.mZ);
         OUTPUT << "Checking match between SM SubSpectrum* retrieved in different ways..." << std::endl;
         test_within_tol(SM->get_Pole_Mass("Z"),
                         smin->get_Pole_Mass("Z"),                          tol, "Z pole" );
         test_within_tol(SM->get_Pole_Mass("W"),
                         smin->get_Pole_Mass("W"),                          tol, "W pole" );
         test_within_tol(SM->get_Pole_Mass("t"),
                         smin->get_Pole_Mass("t"),                          tol, "top pole" );
         test_within_tol(SM->get_Pole_Mass("tau"),
                         smin->get_Pole_Mass("tau"),                        tol, "tau pole" );
         test_within_tol(SM->get_Pole_Mass("mu"),
                         smin->get_Pole_Mass("mu"),                         tol, "mu pole" );
         test_within_tol(SM->get_Pole_Mass("e"),
                         smin->get_Pole_Mass("e"),                          tol, "e pole" );
         if(not SLHAonly) test_within_tol(SM->get_dimensionless_parameter("alpha"),
                         smin->get_dimensionless_parameter("alpha"), tol, "1/alpha(mZ)" );
         if(not SLHAonly) test_within_tol(SM->get_dimensionless_parameter("alphaS"),
                         smin->get_dimensionless_parameter("alphaS"),tol, "alphaS(mZ)" );
         test_within_tol(SM->get_mass_parameter("u"),
                         smin->get_mass_parameter("u"),              tolm, "mu(2)" );
         test_within_tol(SM->get_mass_parameter("d"),
                         smin->get_mass_parameter("d"),              tolm, "md(2)" );
         test_within_tol(SM->get_mass_parameter("s"),
                         smin->get_mass_parameter("s"),              tolm, "ms(2)" );
         if(not SLHAonly) test_within_tol(SM->get_mass_parameter("c"),
                         smin->get_mass_parameter("c"),              tolm, "mc(mc)" );
         if(not SLHAonly) test_within_tol(SM->get_mass_parameter("b"),
                         smin->get_mass_parameter("b"),              tolm, "mb(mb)" );


         // Check light quark mass ratios
         OUTPUT << "Checking light quark mass ratios:" << std::endl;

         std::vector<double> scales;
         scales.push_back(10);
         if(not SLHAonly) scales.push_back(2);
         if(not SLHAonly) scales.push_back(1);
         if(not SLHAonly) scales.push_back(0.5);
         if(not SLHAonly) scales.push_back(0.1);

         for(std::vector<double>::iterator it = scales.begin(); it != scales.end(); ++it)
         {
            if(not SLHAonly) SM->RunToScale(*it);
            double Q = SM->GetScale();
            double mu = SM->get_mass_parameter("u");
            double md = SM->get_mass_parameter("d");
            double ms = SM->get_mass_parameter("s");

            OUTPUT << "---------------------------------" << std::endl;
            OUTPUT << "Current scale: " << Q << std::endl;
            OUTPUT << "mu("<<Q<<") = " << mu << std::endl;
            OUTPUT << "md("<<Q<<") = " << md << std::endl;
            OUTPUT << "ms("<<Q<<") = " << ms << std::endl;
            OUTPUT << "mu/md = " << mu/md << std::endl;
            OUTPUT << "ms/md = " << ms/md << std::endl;
         }
         OUTPUT << EOM;

         /// Generate data for a plot of quark mass
         if(not SLHAonly) {

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

         for(std::vector<double>::iterator it = Qvec.begin(); it != Qvec.end(); ++it)
         {
            // Clone to avoid buildup of errors
            std::unique_ptr<SubSpectrum> SMloop = matched_spectra->clone_LE();

            SMloop->RunToScale(*it);
            double Q = SMloop->GetScale();
            double mu = SMloop->get_mass_parameter("u");
            double md = SMloop->get_mass_parameter("d");
            double ms = SMloop->get_mass_parameter("s");

            // Write to file
            Qout << Q << ", " << md << ", " << mu << ", " << ms << std::endl;
         }

         Qout.close();

         } // endif

         /// Testing copyability of Spectrum;
         // Copy to object to clone the hosted SubSpectrum objects.
         // i.e. all copies are deep copies.
         Spectrum nonconst_spectra(*matched_spectra);

         // Try to access non-const member functions
         OUTPUT << std::endl;
         OUTPUT << "Testing non-const access to Spectrum object:" << std::endl;
         if(not SLHAonly) nonconst_spectra.RunBothToScale(sminputs.mT); // This is the only non-const function atm.
         OUTPUT << "Current SM SubSpectrum* scale: " << nonconst_spectra.get_LE()->GetScale() << std::endl;
         OUTPUT << "Current UV SubSpectrum* scale: " << nonconst_spectra.get_UV()->GetScale() << std::endl;
         // Make sure nothing happened to the original objects
         OUTPUT << "Old SM SubSpectrum* scale: " << matched_spectra->get_LE()->GetScale() << std::endl;
         OUTPUT << "Old UV SubSpectrum* scale: " << matched_spectra->get_UV()->GetScale() << std::endl;
         // Check some other numbers
         OUTPUT << "Current SM SubSpectrum* mu :" << nonconst_spectra.get_LE()->get_mass_parameter("u") << std::endl;
         OUTPUT << "Current SM Spectrum* md :" << nonconst_spectra.get_LE()->get_mass_parameter("d") << std::endl;
         OUTPUT << "Current SM Spectrum* ms :" << nonconst_spectra.get_LE()->get_mass_parameter("s") << std::endl;
         OUTPUT << "Old SM Spectrum* mu :" << matched_spectra->get_LE()->get_mass_parameter("u") << std::endl;
         OUTPUT << "Old SM Spectrum* md :" << matched_spectra->get_LE()->get_mass_parameter("d") << std::endl;
         OUTPUT << "Old SM Spectrum* ms :" << matched_spectra->get_LE()->get_mass_parameter("s") << std::endl;
         OUTPUT << EOM;

         // Check running beyond soft and hard limits (assumes QedQcdWrapper for SM)
         // behave = 0  -- If running beyond soft limit requested, halt at soft limit
         //                (assumes hard limits outside of soft limits; but this is not enforced)
         // behave = 1  -- If running beyond soft limit requested, throw warning
         //                  "           "   hard limit     "    , throw error
         // behave = anything else -- Ignore limits and attempt running to requested scale
         if(not SLHAonly) {
           OUTPUT << "Testing QedQcdWrapper running limits:" << std::endl;
           // behave=0 (default)
           // Running halted at soft limit
           OUTPUT << "behave=0" << std::endl;
           SM->RunToScale(sminputs.mT);   // Soft limit (and hard limit)
           OUTPUT << "Current scale: " << SM->GetScale() << std::endl;
           SM->RunToScale(1.5*sminputs.mT);
           OUTPUT << "Current scale: " << SM->GetScale() << std::endl;
           OUTPUT << EOM;

           // behave=2
           // Should be no errors, just potentially inaccurate running
           // EDIT: Whoops, so QedQcd object itself will throw an error if you try
           // to run above mT. Remove comments to observe this behaviour.
           OUTPUT << "behave=2" << std::endl;
           SM->RunToScale(sminputs.mT,2);   // Soft limit (and hard limit)
           OUTPUT << "Current scale: " << SM->GetScale() << std::endl;
           //SM->RunToScale(1.5*sminputs.mT,2);
           //OUTPUT << "Current scale: " << SM->GetScale() << std::endl;
           OUTPUT << EOM;

           // behave=1
           OUTPUT << "behave=1" << std::endl;
           SM->RunToScale(sminputs.mT,1);   // Soft limit (and hard limit)
           OUTPUT << "Current scale: " << SM->GetScale() << std::endl;
           SM->RunToScale(1.5*sminputs.mT,1); // Beyond hard limit (error)
           OUTPUT << "Current scale: " << SM->GetScale() << std::endl;
           OUTPUT << EOM;
         }
      }

   }  // end namespace SpecBit
}  // end namespace Gambit

#endif
