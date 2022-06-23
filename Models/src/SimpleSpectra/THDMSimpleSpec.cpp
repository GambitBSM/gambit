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
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///
///  *********************************************

#include "gambit/Models/SimpleSpectra/THDMSimpleSpec.hpp"
#include "gambit/Elements/thdm_slhahelp.hpp"
#include "gambit/Utils/util_functions.hpp"

using namespace SLHAea;

namespace Gambit
{

    /// @{ Member functions for SLHAeaModel class

    /// Default Constructor
    THDMea::THDMea()
      : SLHAeaModel()
    {}

    /// Constructor via SLHAea object
    THDMea::THDMea(const SLHAea::Coll& slhainput)
      : SLHAeaModel(slhainput)
    {}

    /// @{ Getters for SM information

    // Model type
    double THDMea::get_model_type()   const { return getdata("FMODSEL",1) - 30; }

    /// Pole masses
    double THDMea::get_MZ_pole()        const { return getdata("SMINPUTS",4); }
    double THDMea::get_Mtop_pole()      const { return getdata("SMINPUTS",6); }

    // Note, these are actually MSbar masses mb(mb) and mc(mc)
    // However, since this wrapper is very simple, it isn't possible to return
    // these at the same scale as the other running parameters. They can be
    // be considered as approximately pole masses though, so I have allowed
    // to be accessed here. Use as pole masses at own risk.
    double THDMea::get_MbMb()           const { return getdata("SMINPUTS",5); }
    double THDMea::get_McMc()           const { return getdata("SMINPUTS",24); }

    double THDMea::get_Mtau_pole()      const { return getdata("SMINPUTS",7); }
    double THDMea::get_Mmuon_pole()     const { return getdata("SMINPUTS",13); }
    double THDMea::get_Melectron_pole() const { return getdata("SMINPUTS",11); }

    double THDMea::get_Mnu1_pole()      const { return getdata("SMINPUTS",12); }
    double THDMea::get_Mnu2_pole()      const { return getdata("SMINPUTS",14); }
    double THDMea::get_Mnu3_pole()      const { return getdata("SMINPUTS",8); }

    double THDMea::get_MPhoton_pole()   const { return 0.; }
    double THDMea::get_MGluon_pole()    const { return 0.; }

    // In SLHA the W mass is an output, though some spectrum generator authors
    // allow it as a non-standard entry in SMINPUTS. Here we will stick to
    // SLHA.
    double THDMea::get_MW_pole()        const { return getdata("MASS",24); }
    double THDMea::get_MW_unc()         const { return 0.0; }

    double THDMea::get_sinthW2_pole()   const { return (1.0 - Utils::sqr(get_MW_pole()) / Utils::sqr(get_MZ_pole())); }

    /// Running masses
    //  Only available for light quarks
    double THDMea::get_md() const { return getdata("SMINPUTS",21); }
    double THDMea::get_mu() const { return getdata("SMINPUTS",22); }
    double THDMea::get_ms() const { return getdata("SMINPUTS",23); }

    double THDMea::get_vev()   const { return getdata("HMIX",3);  }
    double THDMea::get_tanb()  const { return getdata("MINPAR",3); }
    double THDMea::get_beta()  const { return atan(get_tanb()); }
    double THDMea::get_alpha() const { return getdata("ALPHA",0); }

    double THDMea::get_v1()    const { return sqrt(pow(get_vev(),2)*pow(get_tanb(),2)/(1+pow(get_tanb(),2)));  }
    double THDMea::get_v2()    const { return sqrt(pow(get_vev(),2)/(1+pow(get_tanb(),2))); }

    double THDMea::get_g1()    const { return getdata("GAUGE",1); }
    double THDMea::get_g2()    const { return getdata("GAUGE",2); }
    double THDMea::get_g3()    const { return getdata("GAUGE",3); }
    //double THDMea::get_sinW2() const { return (0.5 - pow( 0.25 - (1.0/getdata("SMINPUTS",1) * M_PI / (getdata("SMINPUTS",2) * pow(2,0.5)))/pow(getdata("SMINPUTS",4),2) , 0.5)); }
    double THDMea::get_sinW2() const { return getdata("HMIX",23); }


    double THDMea::get_Yd1(int i, int j) const { return getdata("Yd1",i,j); }
    double THDMea::get_Yu1(int i, int j) const { return getdata("Yu1",i,j); }
    double THDMea::get_Ye1(int i, int j) const { return getdata("Ye1",i,j); }

    double THDMea::get_ImYd1(int i, int j) const { return getdata("ImYd1",i,j); }
    double THDMea::get_ImYu1(int i, int j) const { return getdata("ImYu1",i,j); }
    double THDMea::get_ImYe1(int i, int j) const { return getdata("ImYe1",i,j); }

    double THDMea::get_Yd2(int i, int j) const { return getdata("Yd2",i,j); }
    double THDMea::get_Yu2(int i, int j) const { return getdata("Yu2",i,j); }
    double THDMea::get_Ye2(int i, int j) const { return getdata("Ye2",i,j); }

    double THDMea::get_ImYd2(int i, int j) const { return getdata("ImYd2",i,j); }
    double THDMea::get_ImYu2(int i, int j) const { return getdata("ImYu2",i,j); }
    double THDMea::get_ImYe2(int i, int j) const { return getdata("ImYe2",i,j); }

    // Pole masses
    double THDMea::get_mh0_pole(int i) const
    {
      if      (i==1){ return getdata("MASS",25); } // Neutral Higgs(1)
      else if (i==2){ return getdata("MASS",35); } // Neutral Higgs(2)
      else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_mh0! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
    }

    double THDMea::get_mA0_pole() const { return getdata("MASS",36); }
    double THDMea::get_mC_pole()  const { return getdata("MASS",37); }
    double THDMea::get_mG0() const { return 0.0; }
    double THDMea::get_mGC() const { return 0.0; }

    // Running masses, same to pole masses on simple spectra
    double THDMea::get_mh0(int i) const
    {
      if      (i==1){ return getdata("MASS",25); } // Neutral Higgs(1)
      else if (i==2){ return getdata("MASS",35); } // Neutral Higgs(2)
      else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_mh0! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
    }

    double THDMea::get_mA0() const { return getdata("MASS",36); }
    double THDMea::get_mC()  const { return getdata("MASS",37); }
    double THDMea::get_MW()  const { return getdata("MASS",24); }

    double THDMea::get_lambda1() const { return getdata("MINPAR",11); }
    double THDMea::get_lambda2() const { return getdata("MINPAR",12); }
    double THDMea::get_lambda3() const { return getdata("MINPAR",13); }
    double THDMea::get_lambda4() const { return getdata("MINPAR",14); }
    double THDMea::get_lambda5() const { return getdata("MINPAR",15); }
    double THDMea::get_lambda6() const { return getdata("MINPAR",16); }
    double THDMea::get_lambda7() const { return getdata("MINPAR",17); }

    double THDMea::get_Lambda1() const
    {
      double b = get_beta(), sb = sin(b), cb = cos(b), s2b = sin(2.*b);
      double lam1 = get_lambda1(), lam2 = get_lambda2(), lam345 = get_lambda3() + get_lambda4() + get_lambda5(), lam6 = get_lambda6(), lam7 = get_lambda7();
      return lam1*pow(cb,4) + lam2*pow(sb,4) + 0.5*lam345*pow(s2b,2) + 2.*s2b*(pow(cb,2)*lam6+pow(sb,2)*lam7);
    }
    double THDMea::get_Lambda2() const
    {
      double b = get_beta(), sb = sin(b), cb = cos(b), s2b = sin(2.*b);
      double lam1 = get_lambda1(), lam2 = get_lambda2(), lam345 = get_lambda3() + get_lambda4() + get_lambda5(), lam6 = get_lambda6(), lam7 = get_lambda7();
      return lam1*pow(sb,4) + lam2*pow(cb,4) + 0.5*lam345*pow(s2b,2) - 2.*s2b*(pow(sb,2)*lam6+pow(cb,2)*lam7);
    }
    double THDMea::get_Lambda3() const
    {
      double b = get_beta(), s2b = sin(2.*b), c2b = cos(2.*b);
      double lam1 = get_lambda1(), lam2 = get_lambda2(), lam3 = get_lambda3(), lam345 = get_lambda3() + get_lambda4() + get_lambda5(), lam6 = get_lambda6(), lam7 = get_lambda7();
      return 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam3 - s2b*c2b*(lam6-lam7);
    }
    double THDMea::get_Lambda4() const
    {
      double b = get_beta(), s2b = sin(2.*b), c2b = cos(2.*b);
      double lam1 = get_lambda1(), lam2 = get_lambda2(), lam4 = get_lambda4(), lam345 = get_lambda3() + get_lambda4() + get_lambda5(), lam6 = get_lambda6(), lam7 = get_lambda7();
      return 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam4 - s2b*c2b*(lam6-lam7);
    }
    double THDMea::get_Lambda5() const
    {
      double b = get_beta(), s2b = sin(2.*b), c2b = cos(2.*b);
      double lam1 = get_lambda1(), lam2 = get_lambda2(), lam345 = get_lambda3() + get_lambda4() + get_lambda5(), lam5 = get_lambda5(), lam6 = get_lambda6(), lam7 = get_lambda7();
      return 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam5 - s2b*c2b*(lam6-lam7);
    }
    double THDMea::get_Lambda6() const
    {
      double b = get_beta(), sb = sin(b), cb = cos(b), s2b = sin(2.*b), c2b = cos(2.*b);
      double lam1 = get_lambda1(), lam2 = get_lambda2(), lam345 = get_lambda3() + get_lambda4() + get_lambda5(), lam6 = get_lambda6(), lam7 = get_lambda7();
      return -0.5*s2b*(lam1*pow(cb,2)-lam2*pow(sb,2)-lam345*c2b) + cb*cos(3.*b)*lam6 + sb*sin(3.*b)*lam7;
    }
    double THDMea::get_Lambda7() const
    {
      double b = get_beta(), sb = sin(b), cb = cos(b), s2b = sin(2.*b), c2b = cos(2.*b);
      double lam1 = get_lambda1(), lam2 = get_lambda2(), lam345 = get_lambda3() + get_lambda4() + get_lambda5(), lam6 = get_lambda6(), lam7 = get_lambda7();
      return -0.5*s2b*(lam1*pow(sb,2)-lam2*pow(cb,2)+lam345*c2b) + sb*sin(3.*b)*lam6 + cb*cos(3.*b)*lam7;
    }

    double THDMea::get_m12_2() const { return getdata("MINPAR",18); }

    double THDMea::get_m11_2() const
    {
      double m12_2 = get_m12_2(), b = get_beta(), cb = cos(b), sb = sin(b), vev = get_vev();
      double lam1 = get_lambda1(), lam345 = get_lambda3() + get_lambda4() + get_lambda5(), lam6 = get_lambda6(), lam7 = get_lambda7();
      return m12_2*tan(b) - 0.5*pow(vev,2) * (lam1*cb*cb + lam345*sb*sb + 3.0*lam6*sb*cb + lam7*sb*sb*tan(b));
    }
    double THDMea::get_m22_2() const
    {
      double m12_2 = get_m12_2(), b = get_beta(), cb = cos(b), sb = sin(b), vev = get_vev();
      double lam2 = get_lambda2(), lam345 = get_lambda3() + get_lambda4() + get_lambda5(), lam6 = get_lambda6(), lam7 = get_lambda7();
      return m12_2/tan(b) - 0.5*pow(vev,2) * (lam2*sb*sb + lam345*cb*cb + lam6*cb*cb/tan(b) + 3.0*lam7*sb*cb);
    }

    double THDMea::get_M12_2() const
    {
      double  b = get_tanb(), s2b = sin(2.*b), c2b = cos(2.*b);
      double m11_2 = get_m11_2(), m12_2 = get_m12_2(), m22_2 = get_m22_2();
      return (m11_2-m22_2)*s2b + m12_2*c2b;
    }

    double THDMea::get_M11_2() const
    {
      double  b = get_tanb(), cb = cos(b), sb = sin(b), s2b = sin(2.*b);
      double m11_2 = get_m11_2(), m12_2 = get_m12_2(), m22_2 = get_m22_2();
      return m11_2*pow(cb,2) + m22_2*pow(sb,2) - m12_2*s2b;
    }

    double THDMea::get_M22_2() const
    {
      double  b = get_tanb(), cb = cos(b), sb = sin(b), s2b = sin(2.*b);
      double m11_2 = get_m11_2(), m12_2 = get_m12_2(), m22_2 = get_m22_2();
      return m11_2*pow(sb,2) + m22_2*pow(cb,2) + m12_2*s2b;
    }

    /// @}


    /// @{ Member functions for THDMSimpleSpec class

    /// @{ Constructors

    /// Default Constructor
    THDMSimpleSpec::THDMSimpleSpec()
    {}

    /// Construct via SLHAea object
    THDMSimpleSpec::THDMSimpleSpec(const SLHAea::Coll& slhainput)
      : SLHASimpleSpec(slhainput)
    {}

    // Construct with THDMModel struct
    THDMSimpleSpec::THDMSimpleSpec(const Models::THDMModel& p, const SMInputs &sminputs)
      : params(p)
    {
      std::map<str,double> scalars = {{"h0_1", p.mh0}, {"h0_2", p.mH0}, {"A0", p.mA0},
                                      {"H+", p.mC}, {"W+", p.mW},
                                      {"lambda1",p.lambda1}, {"lambda2",p.lambda2}, {"lambda3",p.lambda3},
                                      {"lambda4",p.lambda4}, {"lambda5",p.lambda5}, {"lambda6",p.lambda6},
                                      {"lambda7",p.lambda7}, {"tanb",p.tanb}, {"alpha",p.alpha},
                                      {"m11_2",p.m11_2}, {"m12_2",p.m12_2}, {"m22_22",p.m22_2},
                                      {"vev",p.vev}, {"g1",p.g1}, {"g2",p.g2}, {"g3",p.g3}, {"sinW2",p.sinW2}};

      SLHAea::Coll slha;

      SLHAea_add(slha, "FMODSEL", 1, 30 + p.model_type, "THDM");

      sminputs.add_to_SLHAea(slha);

      const std::vector<SpectrumParameter> contents = Contents().all_parameters();

      for(auto scalar = scalars.begin(); scalar != scalars.end(); scalar++)
        for(auto param = contents.begin(); param != contents.end(); param++)
        {
          if(param->name() == scalar->first)
          {
            SLHAea_add(slha, param->blockname(), param->blockindex(), scalar->second, "# "+scalar->first, true);
          }
        }

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          SLHAea_add(slha, "Yu1", i+1, j+1, p.Yu1[i][j], "# Yu1("+std::to_string(i+1)+","+std::to_string(j+1)+")", true);
          SLHAea_add(slha, "Yd1", i+1, j+1, p.Yd1[i][j], "# Yd1("+std::to_string(i+1)+","+std::to_string(j+1)+")", true);
          SLHAea_add(slha, "Ye1", i+1, j+1, p.Ye1[i][j], "# Ye1("+std::to_string(i+1)+","+std::to_string(j+1)+")", true);
          SLHAea_add(slha, "Yu2", i+1, j+1, p.Yu2[i][j], "# Yu2("+std::to_string(i+1)+","+std::to_string(j+1)+")", true);
          SLHAea_add(slha, "Yd2", i+1, j+1, p.Yd2[i][j], "# Yd2("+std::to_string(i+1)+","+std::to_string(j+1)+")", true);
          SLHAea_add(slha, "Ye2", i+1, j+1, p.Ye2[i][j], "# Ye2("+std::to_string(i+1)+","+std::to_string(j+1)+")", true);
          SLHAea_add(slha, "ImYu1", i+1, j+1, p.ImYu1[i][j], "# ImYu1("+std::to_string(i+1)+","+std::to_string(j+1)+")", true);
          SLHAea_add(slha, "ImYd1", i+1, j+1, p.ImYd1[i][j], "# ImYd1("+std::to_string(i+1)+","+std::to_string(j+1)+")", true);
          SLHAea_add(slha, "ImYe1", i+1, j+1, p.ImYe1[i][j], "# ImYe1("+std::to_string(i+1)+","+std::to_string(j+1)+")", true);
          SLHAea_add(slha, "ImYu2", i+1, j+1, p.ImYu2[i][j], "# ImYu2("+std::to_string(i+1)+","+std::to_string(j+1)+")", true);
          SLHAea_add(slha, "ImYd2", i+1, j+1, p.ImYd2[i][j], "# ImYd2("+std::to_string(i+1)+","+std::to_string(j+1)+")", true);
          SLHAea_add(slha, "ImYe2", i+1, j+1, p.ImYe2[i][j], "# ImYe2("+std::to_string(i+1)+","+std::to_string(j+1)+")", true);
        }

      slhawrap = slha;

    }

    /// Copy constructor: needed by clone function.
    THDMSimpleSpec::THDMSimpleSpec(const THDMSimpleSpec& other)
      : SLHASimpleSpec(other)
    {}

    /// @}

    /// Hardcoded to return SLHA2 defined scale of light quark MSbar masses in SMINPUTS block (2 GeV)
    double THDMSimpleSpec::GetScale() const { return 2; }

    /// @}

    // Map fillers

    THDMSimpleSpec::GetterMaps THDMSimpleSpec::fill_getter_maps()
    {

        GetterMaps map_collection;

        typedef MTget::FInfo1 FInfo1;
        typedef MTget::FInfo2 FInfo2;

        static const int i12v[] = {1,2};
        static const std::set<int> i12(i12v, Utils::endA(i12v));

        static const int i123v[] = {1,2,3};
        static const std::set<int> i123(i123v, Utils::endA(i123v));

        /// Fill for mass1 map
        {
            MTget::fmap0 tmp_map;

            tmp_map["u_1"]  = &THDMea::get_mu; // u
            tmp_map["d_1"]  = &THDMea::get_md; // d
            tmp_map["d_2"]  = &THDMea::get_ms; // s

            // Nearest flavour 'aliases' for the THDM mass eigenstates
            tmp_map["u"]  = &THDMea::get_mu; // u
            tmp_map["d"]  = &THDMea::get_md; // d
            tmp_map["s"]  = &THDMea::get_ms; // s

            // vev
            tmp_map["vev"]  = &THDMea::get_vev;
            tmp_map["v1"]  = &THDMea::get_v1;
            tmp_map["v2"]  = &THDMea::get_v2;

            // coupling basis potential parameters
            tmp_map["m12_2"]  = &THDMea::get_m12_2;
            tmp_map["m11_2"]  = &THDMea::get_m11_2;
            tmp_map["m22_2"]  = &THDMea::get_m22_2;

            // higgs basis potential parameters
            tmp_map["M12_2"]  = &THDMea::get_M12_2;
            tmp_map["M11_2"]  = &THDMea::get_M11_2;
            tmp_map["M22_2"]  = &THDMea::get_M22_2;

            // Running masses
            tmp_map["A0"] = &THDMea::get_mA0;
            tmp_map["H+"] = &THDMea::get_mC;
            tmp_map["H-"] = &THDMea::get_mC;
            tmp_map["W+"] = &THDMea::get_MW;

            map_collection[Par::mass1].map0 = tmp_map;
        }

        /// THDM Scalar Higgs Running Mass
        {
            MTget::fmap1 tmp_map;
            tmp_map["h0"]   = FInfo1( &THDMea::get_mh0, i12 );

            map_collection[Par::mass1].map1 = tmp_map;
        }

        /// Fill Pole_mass map (from Model object)
        {
            MTget::fmap0 tmp_map;

            tmp_map["Z0"]  = &THDMea::get_MZ_pole;
            tmp_map["W+"]  = &THDMea::get_MW_pole;
            tmp_map["gamma"] = &THDMea::get_MPhoton_pole;
            tmp_map["g"]     = &THDMea::get_MGluon_pole;

            tmp_map["d_3"] = &THDMea::get_MbMb; // b
            tmp_map["u_2"] = &THDMea::get_McMc; // c
            tmp_map["u_3"] = &THDMea::get_Mtop_pole; //t
            tmp_map["e-_3"]= &THDMea::get_Mtau_pole; // tau
            tmp_map["e-_2"]= &THDMea::get_Mmuon_pole; // mu
            tmp_map["e-_1"]= &THDMea::get_Melectron_pole;
            tmp_map["nu_1"]= &THDMea::get_Mnu1_pole;
            tmp_map["nu_2"]= &THDMea::get_Mnu2_pole;
            tmp_map["nu_3"]= &THDMea::get_Mnu3_pole;

            // Nearest flavour 'aliases' for the THDM mass eigenstates
            tmp_map["b"]   = &THDMea::get_MbMb; // b
            tmp_map["c"]   = &THDMea::get_McMc; // c
            tmp_map["t"]   = &THDMea::get_Mtop_pole; //t
            tmp_map["tau-"]= &THDMea::get_Mtau_pole; // tau
            tmp_map["mu-"] = &THDMea::get_Mmuon_pole; // mu
            tmp_map["e-"]  = &THDMea::get_Melectron_pole;

            // THDM Extra Scalar Pole Masses
            tmp_map["A0"]= &THDMea::get_mA0_pole;
            tmp_map["H+"] = &THDMea::get_mC_pole;
            tmp_map["H-"]  = &THDMea::get_mC_pole;
            tmp_map["G+"]  = &THDMea::get_mGC;
            tmp_map["G-"]  = &THDMea::get_mGC;
            tmp_map["G0"]  = &THDMea::get_mG0;

            map_collection[Par::Pole_Mass].map0 = tmp_map;
        }

        // THDM Scalar Higgs Pole Mass
        {
            MTget::fmap1 tmp_map;
            tmp_map["h0"]   = FInfo1( &THDMea::get_mh0_pole, i12 );

            map_collection[Par::Pole_Mass].map1 = tmp_map;
        }

        // fill W mass uncertainties
        {
            MTget::fmap0 tmp_map;
            tmp_map["W+"] = &THDMea::get_MW_unc;
            map_collection[Par::Pole_Mass_1srd_high].map0 = tmp_map;
        }

        {
           MTget::fmap0 tmp_map;
           tmp_map["W+"] = &THDMea::get_MW_unc;
           map_collection[Par::Pole_Mass_1srd_low].map0 = tmp_map;
        }


        // Dimensionless block
        {
            MTget::fmap0 tmp_map;

            tmp_map["model_type"] = &THDMea::get_model_type;

            tmp_map["g1"]   = &THDMea::get_g1;
            tmp_map["g2"]   = &THDMea::get_g2;
            tmp_map["g3"]   = &THDMea::get_g3;

            tmp_map["sinW2"] = &THDMea::get_sinW2;

            tmp_map["tanb"]  = &THDMea::get_tanb;
            tmp_map["beta"]  = &THDMea::get_beta;
            tmp_map["alpha"] = &THDMea::get_alpha;

            tmp_map["lambda1"]  = &THDMea::get_lambda1;
            tmp_map["lambda2"]  = &THDMea::get_lambda2;
            tmp_map["lambda3"]  = &THDMea::get_lambda3;
            tmp_map["lambda4"]  = &THDMea::get_lambda4;
            tmp_map["lambda5"]  = &THDMea::get_lambda5;
            tmp_map["lambda6"]  = &THDMea::get_lambda6;
            tmp_map["lambda7"]  = &THDMea::get_lambda7;

            tmp_map["Lambda1"]  = &THDMea::get_Lambda1;
            tmp_map["Lambda2"]  = &THDMea::get_Lambda2;
            tmp_map["Lambda3"]  = &THDMea::get_Lambda3;
            tmp_map["Lambda4"]  = &THDMea::get_Lambda4;
            tmp_map["Lambda5"]  = &THDMea::get_Lambda5;
            tmp_map["Lambda6"]  = &THDMea::get_Lambda6;
            tmp_map["Lambda7"]  = &THDMea::get_Lambda7;

            map_collection[Par::dimensionless].map0 = tmp_map;
        }

        // Yukawas block
        {
            MTget::fmap2 tmp_map;

            tmp_map["Yu1"]   = FInfo2( &THDMea::get_Yu1, i123, i123);
            tmp_map["Yd1"]   = FInfo2( &THDMea::get_Yd1, i123, i123);
            tmp_map["Ye1"]   = FInfo2( &THDMea::get_Ye1, i123, i123);

            tmp_map["ImYu1"] = FInfo2( &THDMea::get_ImYu1, i123, i123);
            tmp_map["ImYd1"] = FInfo2( &THDMea::get_ImYd1, i123, i123);
            tmp_map["ImYe1"] = FInfo2( &THDMea::get_ImYe1, i123, i123);

            tmp_map["Yu2"]   = FInfo2( &THDMea::get_Yu2, i123, i123);
            tmp_map["Yd2"]   = FInfo2( &THDMea::get_Yd2, i123, i123);
            tmp_map["Ye2"]   = FInfo2( &THDMea::get_Ye2, i123, i123);

            tmp_map["ImYu2"] = FInfo2( &THDMea::get_ImYu2, i123, i123);
            tmp_map["ImYd2"] = FInfo2( &THDMea::get_ImYd2, i123, i123);
            tmp_map["ImYe2"] = FInfo2( &THDMea::get_ImYe2, i123, i123);

            map_collection[Par::dimensionless].map2 = tmp_map;
        }


        return map_collection;
    }

} // end Gambit namespace


