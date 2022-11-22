//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for CalcHEP Backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2017 May, Oct
///        2018 Sep
///
///  *****************************************

#include <fstream>
#include <boost/algorithm/string/replace.hpp>

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Models/partmap.hpp"
#include "gambit/Backends/frontends/CalcHEP_3_6_27.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"
#include "gambit/Elements/decay_table.hpp"

#include "gambit/Utils/mpiwrapper.hpp"

#include <unistd.h>

BE_INI_FUNCTION
{

  // Scan-level.
  static bool scan_level = true;

  if (scan_level)
  {
    // Declare backend path variables
    str BEpath;
    const char *path;
    char *modeltoset;
    std::string model;

    // All decays and xsecs added to a new model
    std::map< str, std::vector< std::vector<str> > > decays;
    std::map< std::vector<str>, std::vector< std::vector<str> > > xsecs;

    if (ModelInUse("ScalarSingletDM_Z2"))
    {
      // Set model within CalcHEP
      BEpath = backendDir + "/../models/ScalarSingletDM_Z2";
      path = BEpath.c_str();
      modeltoset = (char*)malloc(strlen(path)+11);
      sprintf(modeltoset, "%s", path);

      decays["h"] = std::vector< std::vector<str> >{ {"~S","~S"} };
      xsecs[std::vector<str>{"~S","~S"}] = std::vector< std::vector<str> >{ {"d'", "D'"}, {"u", "U"}, {"B", "b"}, {"h", "h"}, {"e", "E"}, {"Z", "Z"}, {"c", "C"}, {"s'", "S'"}, {"m", "M"}, {"t", "T"}, {"W+", "W-"}, {"ta+", "ta-"} };
      model = "ScalarSingletDM_Z2";
    }

    if (ModelInUse("DMEFT"))
    {
      BEpath = backendDir + "/../models/DMEFT";
      path = BEpath.c_str();
      modeltoset = (char*)malloc(strlen(path)+11);
      sprintf(modeltoset, "%s", path);
    }

    // CH is not threadsafe so make critical sections everywhere
    #pragma omp critical
    if (ModelInUse("DMsimpVectorMedDiracDM"))
    {
      BEpath = backendDir + "/../models/DMsimpVectorMedDiracDM";
      path = BEpath.c_str();
      modeltoset = (char*)malloc(strlen(path)+11);
      sprintf(modeltoset, "%s", path);
      decays["Y1"] = std::vector< std::vector<str> >{ {"b~","b"}, {"c~","c"}, {"d~","d"}, {"s~","s"}, {"t~","t"}, {"u~","u"}, {"Xd~","Xd"} };
      xsecs[std::vector<str>{"Xd", "Xd~"}] = std::vector< std::vector<str> >{ {"c~","c"}, {"d~","d"}, {"s~","s"}, {"t~","t"}, {"b~","b"}, {"u~","u"}, {"Y1","Y1"} };
      model = "DMsimpVectorMedDiracDM";
    }
    
    if (ModelInUse("DMsimpVectorMedMajoranaDM"))
    {
      BEpath = backendDir + "/../models/DMsimpVectorMedMajoranaDM";
      path = BEpath.c_str();
      modeltoset = (char*)malloc(strlen(path)+11);
      sprintf(modeltoset, "%s", path);
      decays["Y1"] = std::vector< std::vector<str> >{ {"b~","b"}, {"c~","c"}, {"d~","d"}, {"s~","s"}, {"t~","t"}, {"u~","u"}, {"Xm","Xm"} };
      xsecs[std::vector<str>{"Xm", "Xm"}] = std::vector< std::vector<str> >{ {"c~","c"}, {"d~","d"}, {"s~","s"}, {"t~","t"}, {"b~","b"}, {"u~","u"}, {"Y1","Y1"} };
      model = "DMsimpVectorMedMajoranaDM";
    }
    
    if (ModelInUse("DMsimpVectorMedScalarDM"))
    {
      BEpath = backendDir + "/../models/DMsimpVectorMedScalarDM";
      path = BEpath.c_str();
      modeltoset = (char*)malloc(strlen(path)+11);
      sprintf(modeltoset, "%s", path);
      decays["Y1"] = std::vector< std::vector<str> >{ {"Xc","Xc~"}, {"b~","b"}, {"c~","c"}, {"d~","d"}, {"s~","s"}, {"t~","t"}, {"u~","u"} };
      xsecs[std::vector<str>{"Xc", "Xc~"}] = std::vector< std::vector<str> >{ {"c~","c"}, {"d~","d"}, {"s~","s"}, {"t~","t"}, {"b~","b"}, {"u~","u"}, {"Y1","Y1"} };
      model = "DMsimpVectorMedScalarDM";
    }
    
    {
      int error = setModel(modeltoset, 1);
      if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set model" + std::string(modeltoset) +
            " in CalcHEP. CalcHEP error code: " + std::to_string(error) + ". Please check your model files.\n");
    }

    // Get the MPI rank, only let the first rank make the processes...
    int rank = 0;
    #ifdef WITH_MPI
      rank = GMPI::Comm().Get_rank();
    #endif

    // rank 0 can create all the libraries
    if (rank == 0)
    {
      // Decays first
      for (auto d : decays)
        for (auto fs : d.second)
          generate_decay_code(model, d.first, fs);

      // And two to twos
      for (auto x : xsecs)
        for (auto fs : x.second)
          generate_xsec_code(model, x.first, fs);
    }
    #ifdef WITH_MPI
      // Wait here until the first rank has generated all matrix elements.
      GMPI::Comm().Barrier();
    #endif

    free(modeltoset);
  }

  // Point-level.
  scan_level = false;

  if (ModelInUse("ScalarSingletDM_Z2"))
  {
    // Obtain model contents
    static const SpectrumContents::ScalarSingletDM_Z2 ScalarSingletDM_Z2_contents;

    // Obtain list of all parameters within model
    static const std::vector<SpectrumParameter> ScalarSingletDM_Z2_params = ScalarSingletDM_Z2_contents.all_parameters();

    // Obtain spectrum information to pass to CalcHEP
    const Spectrum& spec = *Dep::ScalarSingletDM_Z2_spectrum;

    Assign_All_Values(spec, ScalarSingletDM_Z2_params);
  }

  if (ModelInUse("DMEFT"))
  {
   // Obtain model contents
   static const SpectrumContents::DMEFT DMEFT_contents;

   // Obtain list of all parameters within model
   static const std::vector<SpectrumParameter> DMEFT_params = DMEFT_contents.all_parameters();

   // Obtain spectrum information to pass to CalcHEP
   const Spectrum& spec = *Dep::DMEFT_spectrum;

   Assign_All_Values(spec, DMEFT_params);
  }

  if (ModelInUse("DMsimpVectorMedDiracDM"))
  {
    // Obtain spectrum information to pass to CalcHEP
    const Spectrum& spec = *Dep::DMsimpVectorMedDiracDM_spectrum;
    
    // Obtain model contents
    static const SpectrumContents::DMsimpVectorMedDiracDM DMsimpVectorMedDiracDM_contents;
    
    // Obtain list of all parameters within model
    static const std::vector<SpectrumParameter> DMsimpVectorMedDiracDM_params = DMsimpVectorMedDiracDM_contents.all_parameters();
    
    Assign_All_Values(spec, DMsimpVectorMedDiracDM_params);
  }
  
  if (ModelInUse("DMsimpVectorMedMajoranaDM"))
  {
    // Obtain spectrum information to pass to CalcHEP
    const Spectrum& spec = *Dep::DMsimpVectorMedMajoranaDM_spectrum;
    
    // Obtain model contents
    static const SpectrumContents::DMsimpVectorMedMajoranaDM DMsimpVectorMedMajoranaDM_contents;
    
    // Obtain list of all parameters within model
    static const std::vector<SpectrumParameter> DMsimpVectorMedMajoranaDM_params = DMsimpVectorMedMajoranaDM_contents.all_parameters();
    
    Assign_All_Values(spec, DMsimpVectorMedMajoranaDM_params);
  }
  
  if (ModelInUse("DMsimpVectorMedScalarDM"))
  {
    // Obtain spectrum information to pass to CalcHEP
    const Spectrum& spec = *Dep::DMsimpVectorMedScalarDM_spectrum;
    
    // Obtain model contents
    static const SpectrumContents::DMsimpVectorMedScalarDM DMsimpVectorMedScalarDM_contents;
    
    // Obtain list of all parameters within model
    static const std::vector<SpectrumParameter> DMsimpVectorMedScalarDM_params = DMsimpVectorMedScalarDM_contents.all_parameters();
    
    Assign_All_Values(spec, DMsimpVectorMedScalarDM_params);
  }
  
}
END_BE_INI_FUNCTION

BE_NAMESPACE
{
  /// Create matrix element code for a decay
  numout* generate_decay_code(str model, str in, std::vector<str> out)
  {
    // Generate process from in and out states
    char *process = new char[(in + " -> " + out[0] + "," + out[1]).length() + 1];
    strcpy(process, (in + " -> " + out[0] + "," + out[1]).c_str());

    std::string incpy = in;
    std::string out0cpy = out[0];
    std::string out1cpy = out[1];

    // Replace any instance of a tilde with "bar"
    boost::replace_all(incpy, "~", "bar");
    boost::replace_all(out0cpy, "~", "bar");
    boost::replace_all(out1cpy, "~", "bar");

    // Remove all non-alpha numeric characters from the library names
    incpy.resize(std::remove_if(incpy.begin(), incpy.end(), [](char x) {return !isalnum(x) && !isspace(x);})-incpy.begin());
    out0cpy.resize(std::remove_if(out0cpy.begin(), out0cpy.end(), [](char x) {return !isalnum(x) && !isspace(x);})-out0cpy.begin());
    out1cpy.resize(std::remove_if(out1cpy.begin(), out1cpy.end(), [](char x) {return !isalnum(x) && !isspace(x);})-out1cpy.begin());

    // Generate libname from model and process name
    char *libname = new char[(model + "_" + incpy + "_to_" + out0cpy + out1cpy).length() + 1];
    strcpy(libname, (model + "_" + incpy + "_to_" + out0cpy + out1cpy).c_str());

    char *excludeVirtual = NULL; // Exclude any internal particles
    char *excludeOut = NULL;     // Exclude any products
    int twidth = 0;              // T-channel propagator width
    int UG = 0;                  // Unitary gauge

    // Generates shared object file based on libName - unless it already exists.
    numout* cc = getMEcode(twidth, UG, process, excludeVirtual, excludeOut, libname);

    // Release all memory allocated by "new" before returning
    delete[] process;
    delete[] libname;

    return cc;
  }

  /// For cross-sections, just wrap the decay code
  numout* generate_xsec_code(str model, std::vector<str> in, std::vector<str> out)
  {
    str newin = in[0] + "," + in[1];
    return generate_decay_code(model, newin, out);
  }

  /// Assigns gambit value to parameter, with error-checking.
  void Assign_Value(char *parameter, double value)
  {
    int error;
    error = assignVal(parameter, value);
    if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set " + std::string(parameter) +
          " in CalcHEP. CalcHEP error code: " + std::to_string(error) + ". Please check your model files.\n");
  }

  /// Assigns gambit value to parameter, with error-checking, for parameters that may
  /// have two different names in CalcHEP, such as alphainv : aEWM1 (FeynRules) / aEWinv (SARAH)
  void Assign_Value(char *parameter1, char *parameter2, double value)
  {
    int error;
    error = assignVal(parameter1, value);
    // If name 1 is successful, awesome.
    if (error == 0) return;
    // If not, then try the second one
    error = assignVal(parameter2, value);
    // If that doesn't work, we can throw an error, eh.
    if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set " + std::string(parameter1) +
          " or " + std::string(parameter2) + " in CalcHEP. " +
          " CalcHEP error code: " + std::to_string(error) + ". Please check your model files.\n");
  }

  /// Takes all parameters in a model, and assigns them by
  /// value to the appropriate CalcHEP parameter names.
  void Assign_All_Values(const Spectrum& spec, std::vector<SpectrumParameter> params)
  {
    // Iterate through the expected spectrum parameters of the model. Pass the value of pole masses
    // to CalcHEP from the spectrum, by PDG code.
    for (auto it = params.begin(); it != params.end(); ++it)
    {
      // Don't add the SM vev, Gauge couplings, Yukawas,
      // as CalcHEP computes these internally.
      std::list<std::string> doNotAssign = {"g1", "g2", "g3", "v", "Yu", "Ye", "Yd", "sinW2", "vev"};

      // Fetch the iterator of element with the parameter name
      std::list<std::string>::iterator it2 = std::find(doNotAssign.begin(), doNotAssign.end(), it->name());

      // If we find the parameter in the "do not assign" list, then don't try and assign it,
      // or this will throw an error.
      if (it2 != doNotAssign.end())
      {
        continue;
      }

      // Pole masses
      if (it->tag() == Par::Pole_Mass)
      {
        // Scalar case
        if (it->shape()[0] == 1)
        {
          std::pair<int,int> PDG_code = Models::ParticleDB().partmap::pdg_pair(it->name());
          Assign_Value(pdg2mass(PDG_code.first), spec.get(Par::Pole_Mass, PDG_code.first, PDG_code.second));
        }
        // Vector case
        else
        {
          for (int i=0; i<it->shape()[0]; ++i)
          {
            str long_name = it->name() + "_" + std::to_string(i+1);
            std::pair<int,int> PDG_code = Models::ParticleDB().partmap::pdg_pair(long_name);
            Assign_Value(pdg2mass(PDG_code.first), spec.get(Par::Pole_Mass, PDG_code.first, PDG_code.second));
          }
        }
        // Ignore any matrix cases, as Par::Pole_Mass should only be scalars or vectors
      }
      // Otherwise, should all have the right names
      else
      {
        const SubSpectrum& HE = spec.get_HE();

        // Scalar case
        if (it->shape().size()==1 and it->shape()[0] == 1)
        {
          str name = it->name();
          char *chepname = const_cast<char*> ( name.c_str() );
          Assign_Value(chepname, HE.get(it->tag(), it->name()));
        }
        // Vector case
        else if (it->shape().size()==1 and it->shape()[0] > 1)
        {
          for (int i=0; i<it->shape()[0]; ++i)
          {
            str long_name = it->name() + std::to_string(i+1);
            char *chepname = const_cast<char*> ( long_name.c_str() );
            Assign_Value(chepname, HE.get(it->tag(), it->name(), i+1));
          }
        }
        // Matrix
        else if(it->shape().size()==2)
        {
          for (int i=0; i<it->shape()[0]; ++i)
          {
            for (int j=0; j<it->shape()[0]; ++j)
            {
              str long_name = it->name() + std::to_string(i+1) + "x" + std::to_string(j+1);
              char *chepname = const_cast<char*> ( long_name.c_str() );
              Assign_Value(chepname, HE.get(it->tag(), it->name(), i+1, j+1));
            }
          }
        }
      }
    }

    // Now go through the input parameters of the model. **NOTE**: this structure will only work for the case
    // where we want to scan over fundamental Lagrangian parameters. This will change post-SpecBit redesign.

    // Create SMInputs struct from spectrum
    const SMInputs& sminputs = spec.get_SMInputs();

    // Assign SMInputs
    Assign_Value((char*)"Gf", (char*)"GF", sminputs.GF);                    // Fermi
    Assign_Value((char*)"aS", sminputs.alphaS);                             // Strong coupling (unspecified scale if SARAH)
    Assign_Value((char*)"alfSMZ", (char*)"aS", sminputs.alphaS);            // Strong coupling (mZ) for both.
    Assign_Value((char*)"aEWM1", (char*)"aEWinv", sminputs.alphainv);       // Inverse EM coupling

    // Then, SM particle masses (by PDG code)
    Assign_Value(pdg2mass(1), sminputs.mD);                        // Down
    Assign_Value(pdg2mass(2), sminputs.mU);                        // Up
    Assign_Value(pdg2mass(3), sminputs.mS);                        // Strange
    Assign_Value(pdg2mass(4), sminputs.mCmC);                      // Charm (mC) MSbar
    Assign_Value(pdg2mass(11), spec.get(Par::Pole_Mass, "e-"));    // Electron
    Assign_Value(pdg2mass(13), spec.get(Par::Pole_Mass, "mu-"));   // Muon
    Assign_Value(pdg2mass(15), spec.get(Par::Pole_Mass, "tau-"));  // Tau
    Assign_Value(pdg2mass(23), spec.get(Par::Pole_Mass, "Z0"));    // Z
    Assign_Value(pdg2mass(5), spec.get(Par::Pole_Mass, "d_3"));    // mB(mB) MSbar
    Assign_Value(pdg2mass(6), spec.get(Par::Pole_Mass, "u_3"));    // mT(mT) MSbar
  }

  /// Passes the width of each BSM particle in the model, from DecayTable to CalcHEP.
  /// Don't set the widths of anything SM, except the top, which can get BSM contributions.
  void Assign_Widths(const DecayTable& tbl)
  {
    // Obtain all generic pdg codes. We can't set these widths..
    const std::vector<std::pair<int, int>> generic_particles = Models::ParticleDB().partmap::get_generic_particles();
    const std::vector<std::pair<int, int>> SM_particles = Models::ParticleDB().partmap::get_SM_particles();

    // Iterate through DecayTable. If it is not in the generic particles, or the SM, then go for it.
    for (std::map<std::pair<int, int>, Gambit::DecayTable::Entry>::const_iterator it = tbl.particles.begin();
          it != tbl.particles.end(); ++it)
    {
      if (std::find(generic_particles.begin(), generic_particles.end(), it->first) != generic_particles.end())
      {
        continue;
      }
      if (std::find(SM_particles.begin(), SM_particles.end(), it->first) != SM_particles.end())
      {
        continue;
      }
      Assign_Value(pdg2width(it->first.first), tbl.at(it->first).width_in_GeV);
    }
    // Assign the top separately as they can have BSM contributions e.g. decaying to charged higgses
    Assign_Value(pdg2width(6), tbl.at("t").width_in_GeV);
  }

  /// Provides spin-averaged decay width for 2 body decay process in CM frame at tree-level.
  // TODO: remove dependence on g3 (for alphaS(mZ)).
  double CH_Decay_Width(str& model, str& in, std::vector<str>& out)
  {
    // Check size of in and out states;
    if (out.size() != 2) backend_error().raise(LOCAL_INFO, "Output vector"
                        " must have only 2 entries for a 1 to 2 process.");

    // Calculates and updates all PUBLIC (model-dependent) parameters. These come from $CALCHEP/aux/VandP.c, generated by setModel() in the INI_FUNCTION.
    int err = calcMainFunc();

    if(err != 0) backend_error().raise(LOCAL_INFO, "Unable to calculate parameter " + std::string(varNames[err]) +
          " in CalcHEP. Please check your model files.\n");

    // Check if channel is kinematically open before doing anything. No need to compile processes that are not relevant.
    char *inbound = new char[(in).length() + 1];
    strcpy(inbound, (in).c_str());

    char *outbound_1 = new char[(out[0]).length() + 1];
    strcpy(outbound_1, (out[0]).c_str());

    char *outbound_2 = new char[(out[1]).length() + 1];
    strcpy(outbound_2, (out[1]).c_str());

    // Obtain mass of decaying particle
    double M =  pMass(inbound);
    double m1 = pMass(outbound_1);
    double m2 = pMass(outbound_2);

    // If channel is kinematically closed, return 0.
    if (m1 + m2 > M) { return 0; }

    // Generate process from in and out states
    char *process = new char[(in + " -> " + out[0] + "," + out[1]).length() + 1];
    strcpy(process, (in + " -> " + out[0] + "," + out[1]).c_str());

    std::string incpy = in;
    std::string out0cpy = out[0];
    std::string out1cpy = out[1];

    // Replace any instance of a tilde with "bar"
    boost::replace_all(incpy, "~", "bar");
    boost::replace_all(out0cpy, "~", "bar");
    boost::replace_all(out1cpy, "~", "bar");

    // Remove all non-alpha numeric characters from the library names
    incpy.resize(std::remove_if(incpy.begin(), incpy.end(), [](char x) {return !isalnum(x) && !isspace(x);})-incpy.begin());
    out0cpy.resize(std::remove_if(out0cpy.begin(), out0cpy.end(), [](char x) {return !isalnum(x) && !isspace(x);})-out0cpy.begin());
    out1cpy.resize(std::remove_if(out1cpy.begin(), out1cpy.end(), [](char x) {return !isalnum(x) && !isspace(x);})-out1cpy.begin());


    // Generate libname from model and process name
    char *libname = new char[(model + "_" + incpy + "_to_" + out0cpy + out1cpy).length() + 1];
    strcpy(libname, (model + "_" + incpy + "_to_" + out0cpy + out1cpy).c_str());

    char *excludeVirtual = NULL; // Exclude any internal particles
    char *excludeOut = NULL;     // Exclude any products
    int twidth = 0;              // T-channel propagator width
    int UG = 0;                  // Unitary gauge

    // Generates shared object file based on libName - unless it already exists.
    numout* cc = getMEcode(twidth, UG, process, excludeVirtual, excludeOut, libname);

    // Export numerical values of parameters to link to dynamical code
    err=passParameters(cc);

    if(err != 0) backend_error().raise(LOCAL_INFO, "Unable to calculate parameter " + std::string(varNames[err]) +
          " in CalcHEP. Please check your model files.\n");

    // Kinematic factors.
    double m_plus = m1+m2;
    double m_minus = m1-m2;
    double Msquared = M*M;
    double p = sqrt((Msquared - m_plus*m_plus)*(Msquared - m_minus*m_minus))/(2*M); // Magnitude of momentum in CM frame
    double E_1 = (Msquared + m1*m1 - m2*m2)/(2*M);                                  // Energy of first particle

    // Momentum vector for decay. This is 3 4-vectors, for the decaying particle and the products, respectively. 1 <--- M ---> 2
    double pvect[12] = {M, 0, 0, 0, E_1, 0, 0, p, (M-E_1), 0, 0, -p};

    // Compute squared matrix element
    double matElement = cc -> interface -> sqme(1, 0, pvect, NULL, &err);

    if(err != 0) backend_error().raise(LOCAL_INFO, "Unable to calculate matrix element associated with " + std::string(process) +
          " in CalcHEP. Please check your model files.\n");

    // Compute kinematic prefactor for X -> Y, Z decay
    double prefactor = p/(8*pi*Msquared);

    // Release all memory allocated by "new" before returning
    delete[] libname;
    delete[] inbound;
    delete[] outbound_1;
    delete[] outbound_2;

    // Return partial width
    return prefactor*matElement;
  }

  /// Computes annihilation cross-section for 2->2 process, DM+DMbar -> X + Y at tree level.
  /// Coannihilations not currently supported; we require the mass of both in states are equal.
  double CH_Sigma_V(str& model, std::vector<str>& in, std::vector<str>& out, double& v_rel, const DecayTable& decays)
  {
    // Check size of in and out states;
    if (in.size() != 2 or out.size() != 2) backend_error().raise(LOCAL_INFO, "Input and output vectors"
                        " must have only 2 entries for a 2 to 2 process.");

    // Calculates and updates all PUBLIC (model-dependent) parameters. These come from $CALCHEP/aux/VandP.c, generated by setModel() in the INI_FUNCTION.
    int err = calcMainFunc();

    if(err != 0) backend_error().raise(LOCAL_INFO, "Unable to calculate parameter " + std::string(varNames[err]) +
          " in CalcHEP. Please check your model files.\n");

    // Check if channel is kinematically open before doing anything. No need to compile processes that are not relevant.
    char *inbound_1 = new char[(in[0]).length() + 1];
    strcpy(inbound_1, (in[0]).c_str());

    char *inbound_2 = new char[(in[1]).length() + 1];
    strcpy(inbound_2, (in[1]).c_str());

    char *outbound_1 = new char[(out[0]).length() + 1];
    strcpy(outbound_1, (out[0]).c_str());

    char *outbound_2 = new char[(out[1]).length() + 1];
    strcpy(outbound_2, (out[1]).c_str());

    // Obtain mass of in & out states
    double m_DM = pMass(inbound_1);
    if (pMass(inbound_2) != m_DM) backend_error().raise(LOCAL_INFO, "Mass for both in states must be identical for CH_Sigma_V. "
                                  "Coannihilations not currently supported.");
    double m3 = pMass(outbound_1);
    double m4 = pMass(outbound_2);

    // Kinematics (in states)
    double s = 16*m_DM*m_DM/(4-v_rel*v_rel);
    double E_cm = sqrt(s);
    double E_1 = E_cm/2;
    double E_2 = E_1;
    double p_in = m_DM*v_rel/(sqrt(4-v_rel*v_rel));

    // Not enough energy for the process. Closed.
    if (m3+m4 > E_cm) { return 0; }

    // Pass particle widths - for propagators.
    Assign_Widths(decays);

    // Generate process from in and out states
    char *process = new char[(in[0]+ "," + in[1] + " -> " + out[0] + "," + out[1]).length() + 1];
    strcpy(process, (in[0] + "," + in[1] + " -> " + out[0] + "," + out[1]).c_str());

    str DM = in[0]; // Create copy of the string, as we are about to manipulate.
    str DMbar = in[1];

    // Remove all non-alpha numeric characters from the library names
    DM.resize(std::remove_if(DM.begin(), DM.end(), [](char x) {return !isalnum(x) && !isspace(x);})-DM.begin());
    DMbar.resize(std::remove_if(DMbar.begin(), DMbar.end(), [](char x) {return !isalnum(x) && !isspace(x);})-DMbar.begin());
    out[0].resize(std::remove_if(out[0].begin(), out[0].end(), [](char x) {return !isalnum(x) && !isspace(x);})-out[0].begin());
    out[1].resize(std::remove_if(out[1].begin(), out[1].end(), [](char x) {return !isalnum(x) && !isspace(x);})-out[1].begin());

    // Generate libname from model and process name
    char *libname = new char[(model + "_" + DM + DMbar + "_to_" + out[0] + out[1]).length() + 1];
    strcpy(libname, (model + "_" + DM + DMbar + "_to_" + out[0] + out[1]).c_str());

    /// TODO: are these options for the function..?
    char *excludeVirtual = NULL; // Exclude any internal particles
    char *excludeOut = NULL;     // Exclude any products
    int twidth = 0;              // T-channel propagator width
    int UG = 0;                  // Unitary gauge

    // Generates shared object file based on libName - unless it already exists.
    numout* cc = getMEcode(twidth, UG, process, excludeVirtual, excludeOut, libname);

    // Release all memory allocated by "new" before returning
    delete[] libname;
    delete[] inbound_1;
    delete[] inbound_2;
    delete[] outbound_1;
    delete[] outbound_2;

    // Export numerical values of parameters to link to dynamical code
    err=passParameters(cc);

    if(err != 0) backend_error().raise(LOCAL_INFO, "Unable to calculate parameter " + std::string(varNames[err]) +
          " in CalcHEP. Please check your model files.\n");

    // Kinematic factors (out states)
    double E_3 = (s - (m4*m4) + (m3*m3))/(2*E_cm);
    double E_4 = E_cm - E_3;
    double m_out_plus = m3+m4;
    double m_out_minus = m3-m4;
    double p_out = sqrt((s - m_out_plus*m_out_plus)*(s - m_out_minus*m_out_minus))/(2*E_cm); // Magnitude of outbound momentum in CM frame

    // Momentum vector for 2->2. This is 4 4-vectors, for particles 1->4 respectively.
    double pvect[16] = {E_1, 0, 0, p_in, E_2, 0, 0, -p_in, E_3, 0, 0, p_out, E_4, 0, 0, -p_out};

    // Kinematic prefactor
    double prefactor = p_out/(32*pi*m_DM*s/sqrt(4-v_rel*v_rel));

    // Squared matrix element - f(p(theta)) - to be integrated over.
    double M_squared = 0.0;

    int numsteps = 200;
    // Integrate between -1 < cos(theta) < 1
    for (int i=0; i < numsteps; i++)
    {
      double dcos = 2. / numsteps;
      double cosT = -1 + dcos*i;
      double sinT = sqrt(1-cosT*cosT);
      pvect[9] = p_out*sinT;
      pvect[11] = p_out*cosT;
      pvect[13] = -pvect[9];
      pvect[15] = -pvect[11];
      M_squared += dcos*(cc -> interface -> sqme(1, 0, pvect, NULL, &err)); // dcos * dM_squared/dcos
    }

    // If we get a negative ME (or a NaN), and the relative velocity is zero, then try
    // putting in an arbitrarily small value for the velocity.
    if ((M_squared < 0 or std::isnan(M_squared)) and v_rel == 0.)
    {
      // Choose velocity to be non-zero (but effectively zero) to avoid
      // potential unphysical values for p-wave suppressed xsecs.
      double newvel = 1e-6;

      logger() << "Square matrix element returned a negative value, but velocity is zero." << std::endl;
      logger() << "Trying with v = 1e-6 for final states " << out[0] << " " << out[1] << std::endl;

      // Compute new values for the kinematics
      s = 16*m_DM*m_DM/(4-newvel*newvel);
      E_cm = sqrt(s);
      E_1 = E_cm/2;
      E_2 = E_1;
      p_in = m_DM*newvel/(sqrt(4-newvel*newvel));
      E_3 = (s - (m4*m4) + (m3*m3))/(2*E_cm);
      E_4 = E_cm - E_3;
      p_out = sqrt((s - m_out_plus*m_out_plus)*(s - m_out_minus*m_out_minus))/(2*E_cm);
      pvect[0] = E_1;
      pvect[3] = p_in;
      pvect[4] = E_2;
      pvect[7] = -p_in;
      pvect[8] = E_3;
      pvect[9] = p_out;
      pvect[12] = E_4;
      pvect[15] = -p_out;
      prefactor = p_out/(32*pi*m_DM*s/sqrt(4-newvel*newvel));

      M_squared = 0.0;

      // Integrate again.
      for (int i=0; i < numsteps; i++)
      {
        double dcos = 2. / numsteps;
        double cosT = -1 + dcos*i;
        double sinT = sqrt(1-cosT*cosT);
        pvect[9] = p_out*sinT;
        pvect[11] = p_out*cosT;
        pvect[13] = -pvect[9];
        pvect[15] = -pvect[11];
        M_squared += dcos*(cc -> interface -> sqme(1, 0, pvect, NULL, &err)); // dcos * dM_squared/dcos

      }
    }
    // If it's a NaN, throw an error
    else if (std::isnan(M_squared))
    {
      std::ostringstream err;
      err << "ERROR: CalcHEP returned a NaN matrix element for the process "
          << in[0]  << " " << in[1]  << " to "
          << out[0] << " " << out[1] << " for relative velocity " << v_rel << ".";
      backend_error().raise(LOCAL_INFO, err.str());
    }

    // If it's negative, just return 0. We'll conservatively assume it's just numerical noise.
    else if (M_squared < 0)
    {
      logger() << "Squared matrix element has returned a negative value from CalcHEP." << std::endl;
      logger() << "Final states are " << out[0] << " " << out[1] << " for relative velocity " << v_rel << std::endl;
      logger() << "Returning 0 instead, assuming it's numerical noise from the crude integration." << EOM;
      return 0.;
    }

    // Total sigma_v
    return prefactor*M_squared;
  }
}
END_BE_NAMESPACE
