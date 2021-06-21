//   GUM: GAMBIT Universal Model Machine
//   ************************************
///  \file
///
///  Definitions of SARAH class
///
///  **********************************
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2018, 2019
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 July, Aug
///
///  ***********************************

#include <set>
#include <algorithm>
#include <cstring>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/raw_function.hpp>

#include <boost/filesystem.hpp>

#include "sarah.hpp"

namespace GUM
{

  // SARAH constructor, loads SARAH and the model
  SARAH::SARAH(std::string model) : Math_Package(model)
  {
    // Math_Package constructor already creates the WSTP link

    try
    {
      // Load SARAH
      load_sarah();

      // Load model
      load_model(model);
    }
    catch(...) { throw; }
    
  }
   
  // Load SARAH
  void SARAH::load_sarah()
  {

    std::cout << "Loading SARAH... ";
    std::cout.flush();

    std::string input;
    input+= "SetDirectory[\"" + std::string(SARAH_PATH) + "\"]";
    send_to_math(input);

    const char* out;
    if (!WSGetString(link, &out))
    {
        throw std::runtime_error("SARAH Error: Error loading SARAH. Please check that Mathematica\n" 
                                 "is working and that SARAH actually lives where CMake put it, in:\n"
                                 "  " + std::string(SARAH_PATH) + "\n" 
                                 "Please try rebuilding.");
    }
    else
    {
        std::cout << "SARAH loaded from " << out << "." << std::endl;
    }

    input = "<<SARAH`";
    send_to_math(input);

  }

  void SARAH::load_model(std::string model)
  {
    try
    {
      std::cout << "Loading model " + model + " in SARAH... " << std::endl;

      // Check if model is in SARAH's or GUM's list of models
      if(!model_exists(model))
      {
        throw std::runtime_error("SARAH Error: Could not load model " + model + ". Model is not recognised by SARAH or GUM.");
      }

      // Load it up.
      std::string command = "Start[\"" + model + "\"];";
      send_to_math(command);

      // Check the model has been loaded by querying the model name. If it has changed from the default then we're set.
      std::string modelname = get_modelname();

      // ...Assuming someone hasn't set the model name to 'ModelName' which would be unbelievably annoying and vastly silly.
      if (modelname == "ModelName")
        throw std::runtime_error("SARAH Error: Could not load model " + model + ". Please check your SARAH file.");

      // All good.
      std::cout << "Model " + model + " loaded successfully, with model name " << modelname << "." << std::endl;
    } catch(...) { throw; }
  }

  void SARAH::check_model(std::string model, std::vector<std::string> &backends)
  {
    try
    {
      std::cout << "Checking your model... " << std::endl;

      // Check whether CalcHEP or MicrOmegas have been requested as backend
      bool need_ch = false;
      if (std::find(backends.begin(), backends.end(), "calchep") != backends.end()   ||
          std::find(backends.begin(), backends.end(), "micromegas") != backends.end() )
        need_ch = true;
      
      // Redirect output to catch them after checking model
      send_to_math("streams = AppendTo[$Output, OpenWrite[]];");
   
      send_to_math("CheckModel[]; messages = $MessageList;");

      // Close the output stream and restore to stdout
      std::string command = "Close@Last@streams;"\
                "$Output = Most@streams;"\
                "output = ReadList@First@Last@streams;";
      send_to_math(command);

      // Process the output to find anomaly warnings
      int noutput;
      send_to_math("Length[output]");
      get_from_math(noutput);
      for(int i=1; i<=noutput; i++)
      {
        std::string output;
        send_to_math("ToString[output[[" + std::to_string(i) + "]]]");
        get_from_math(output);

        size_t pos = output.find("WARNING");
        if(pos != std::string::npos)
          std::cout << output.substr(pos) << std::endl;
      }

      // Get the messages and processes them
      int nmessages;
      send_to_math("Length[messages]");
      get_from_math(nmessages);
      for(int i=1; i<=nmessages; i++)
      {
        std::string error, message;
        send_to_math("ToString[messages[[" + std::to_string(i) + "]]]");
        get_from_math(error);

        // If the error is a Mathematica error rather than a SARAH error (e.g. Part::partw) skip
        if(error == "Part::partw" or error == "Part::pkspec1") continue;

        // Else, carry on analysing the error
        send_to_math("ToString[ReleaseHold[messages[[" + std::to_string(i) + "]]]]");
        get_from_math(message);

        //CheckAnomalies
        // This is handled above as it does not produce error messages, only prints

        //CheckChargeConservation;
        if(error == "ChargeConservation::NoSUN")
          std::cout << "Warning! " << message << std::endl;
        else if(error == "Superpotential::ChargeViolation")
          throw std::runtime_error("SARAH Error: Model violates charge conservation. Please fix your superpotential");
        else if(error == "Superpotential::MaybeChargeViolation")
          std::cout << "Warning! The superpotential may violate charge conservation." << std::endl;
        else if(error == "Superpotential::ViolationGlobal")
          throw std::runtime_error("SARAH Error: Model violates global symmetry. Please fix your superpotential");

        //CheckPossibleTermsSuperPotential, CheckPossibleTermsPotential
        else if(error == "Lagrange:ChargeViolation")
          throw std::runtime_error("SARAH Error: Model violates charge conservation. Please fix your Lagrangian");
        else if(error == "Lagrange::MaybeChargeViolation")
          std::cout << "Warning! The Lagrangian may violate charge conservation." << std::endl;
        else if(error == "PossibleTerms::IncludeGlobal")
          std::cout << "Warning! The superpotential does not include all possible terms." << std::endl;
        else if(error == "PossibleTerms::NonSUSY")
          std::cout << "Warning! The Lagrangian does not include all possible terms. Note that this functionality does not work perfectly for non-susy models, so check your Lagrangian" << std::endl;


        //CheckParticleMixingAndVEVs
        else if(error == "Mixing::DifferentQN")
          throw std::runtime_error("SARAH Error: " + message + ". Please fix your model file.");
        else if(error == "VEV::UnbrokenSymmetries")
          throw std::runtime_error("SARAH Error: " + message + ". Please fix your model file.");

        //CheckMassMatrices
        else if(error == "MassMatrix::OnlyZero")
          std::cout << "Warning! " << message << "." << std::endl;
        else if(error == "MassMatrix::Reducible")
          std::cout << "Warning! " << message << "." << std::endl;

        //CheckMissingMixing
        else if(error == "Lagrangian::PossibleMixing")
          std::cout << "Warning! Possible mixing between fields has been found." << std::endl;    


        //CheckDiracSpinors
        else if(error == "DiracSpinor::missing")
          std::cout << "Warning! Missing Dirac spinor definitions for some Weyl spinors." << std::endl;

        //CheckParameterDefinitionsFinal
        else if(error == "CheckModelFiles::MissingParameter")
          throw std::runtime_error("SARAH Error: " + message + ". Please fix your parameters file.");
        else if(error == "CheckModelFiles::MissingLH")
          throw std::runtime_error("SARAH Error: " + message + ". Please fix your parameters file.");
        else if(error == "CheckModelFiles::MissingOutputNameParameter")
          throw std::runtime_error("SARAH Error: " + message + ". Please fix your parameters file.");
        else if(error == "ParameterNames::TooLong")
          if(need_ch)
            throw std::runtime_error("SARAH Error: Some parameter OutputName is too long for a valid CalcHEP output.");
          else
            std::cout << "Warning! The OutputNames of some parameters are too long for CalcHEP output. If using CalcHEP please reduce their length." << std::endl;
        else if(error == "ParameterNames::DefinedTwice")
          throw std::runtime_error("SARAH Error: " + message + ". Please fix your parameters file.");

        //CheckParticleDefinitionsFinal
        else if(error == "CheckModelFiles::MissingParticle")
          std::cout << "Warning! Some particle definitions are missing from the particles file." << std::endl;
          //throw std::runtime_error("SARAH Error: " + message + ". Please fix your particles file.");
        else if(error == "CheckModelFiles::MissingOutputName")
          std::cout << "Warning! Some particle are missing a definition of OutputName in the particles file." << std::endl;
          //throw std::runtime_error("SARAH Error: " + message + ". Please fix your particles file.");
        else if(error == "CheckModelFiles::MissingRParity")
          throw std::runtime_error("SARAH Error: " + message + ". Please fix your particles file.");
        else if(error == "CheckModelFiles::WrongPDG")
          throw std::runtime_error("SARAH Error: " + message + ". Please fix your particles file.");
        else if(error == "CheckModelFiles::ElectricCharge")
          throw std::runtime_error("SARAH Error: " + message + ". Please fix your particles file.");
        else if(error == "ParticleNames::TooLong")
          if(need_ch)
            throw std::runtime_error("SARAH Error: Some particle OutputName is too long for a valid CalcHEP output.");
          else
            std::cout << "Warning! The OutputNames of some particles are too long for CalcHEP output. If using CalcHEP please reduce their length." << std::endl;
        else if(error == "ParticleNames::DefinedTwice")
          std::cout << "Warning! Some particle OutputNames are defined twice." << std::endl;
          //throw std::runtime_error("SARAH Error: " + message + ". Please fix your particles file.");
        else if(error == "FeynArts::NN")
          std::cout << "Warning! " << message << ". If using FeynArts please add missing numbers." << std::endl;
        else if(error == "FeynArts::NumberDefinedTwiceF")
          std::cout << "Warning! " << message << ". If using FeynArts please change duplicated numbers." << std::endl;
        else if(error == "FeynArts::NumberDefinedTwiceS")
          std::cout << "Warning! " << message << ". If using FeynArts please change duplicated numbers." << std::endl;
        else if(error == "FeynArts::NumberDefinedTwiceV")
          std::cout << "Warning! " << message << ". If using FeynArts please change duplicated numbers." << std::endl;
        else if(error == "FeynArts::NumberDefinedTwiceG")
          std::cout << "Warning! " << message << ". If using FeynArts please change duplicated numbers." << std::endl;
        else if(error == "Model::NoEC")
          throw std::runtime_error("SARAH Error: " + message + ". Please fix your particles file.");

        // This seems to be a recurring bug in SARAH, so ignore it
        else if(error == "Transpose::nmtx")
        {
          // Do nothing
        }

        // Ignore messages about suppression of messages
        else if(error == "General::stop")
        {
          // Do nothing
        }

        // If error is unknown throw exception
        else
          throw std::runtime_error("SARAH Error: " + error + " : " + message);
      }

      // All good.
      std::cout << "Model " + model + " successfully passed SARAH's checks. Please address any warnings issued." << std::endl;
    } catch(...) { throw; }
  }



  // The model may have a different "internal" name than what's on the package.
  // Need this info for output files, etc.
  std::string SARAH::get_modelname()
  {

    std::string command = "ModelName";
    send_to_math(command);

    const char* out;
    if (!WSGetString(link, &out))
        throw std::runtime_error("SARAH Error: Error getting Model name.");

    return std::string(out);
  }

  // Check if model is SARAH's database or in GUM's
  bool SARAH::model_exists(std::string modelname)
  {
    try
    {
      // Check if the model is in the SARAH database
      std::string command = "MemberQ[ShowModels[[1]],\"" + modelname + "\"]";
      send_to_math(command);
      
      // Get the boolean result
      bool is_SARAH_model;
      get_from_math(is_SARAH_model);
      if(is_SARAH_model)
      {
        return true;
      }

      // If not check if it's in the GUM model database
      std::string modelpath = std::string(GUM_DIR) + "/Models/" + modelname + "/" + modelname + ".m";

      // If it exists, then copy the folder to the SARAH model dir
      if (!boost::filesystem::exists(modelpath))
      {
        std::cout << "Copying SARAH files from GUM directory to SARAH directory..." << std::endl;
        std::string dest = std::string(SARAH_PATH) + "/Models/" + modelname;
        std::string src = std::string(GUM_DIR) + "/Models/" + modelname;

        // Create the folder in SARAH...
        if (!boost::filesystem::create_directory(dest))
        {
            throw std::runtime_error("Unable to create new model folder in SARAH: " + dest + ".");
        }
        // Copy all files from the GUM dir to the SARAH dir
        for (boost::filesystem::directory_iterator file(src); file != boost::filesystem::directory_iterator();
             ++ file)
        {
            try
            {
                boost::filesystem::path current(file->path());
                // Leave folders behind
                if(boost::filesystem::is_directory(current)) {  continue; }
                else
                {
                    boost::filesystem::copy_file(current, dest / current.filename());
                }
            }
            catch(boost::filesystem::filesystem_error const & e)
            {
                throw std::runtime_error( e.what() );
            }
        }
      }

      // Let's try that again.
      get_from_math(is_SARAH_model);
      if(is_SARAH_model)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    catch(...) { throw; }
  }

  // Computes the vertices at EWSB
  void SARAH::calculate_vertices()
  {
    std::cout << "Calculating vertices..." << std::endl;

    std::string command = "";

    try
    {
      command = "MakeVertexList[EWSB];";
      send_to_math(command);
    }
    catch (std::runtime_error &e)
    {
      std::stringstream ss;
      ss << e.what() << ": Last command: " << command;
      throw std::runtime_error(ss.str());
    }
  }

  // Get particles list
  void SARAH::get_partlist(std::vector<Particle> &partlist)
  {

    std::cout << "Extracting particles from SARAH model." << std::endl;

    std::string command = "";

    try
    {

      // Command to get a list with (most) particle info.
      command = "plgum = ParticleDefinitions[EWSB];";
      send_to_math(command);

      // Find out how many particles we have to get.
      command = "Length[plgum]";
      send_to_math(command);

      int lenpl;
      get_from_math(lenpl);

      // Save some stuff for in a minute.

      // Fermions
      std::vector<std::string> dFs;
      command = "PART[F][[All,1]]";
      // command = "diracFermions[ALL]";
      send_to_math(command);
      get_from_math(dFs);

      // Scalar
      std::vector<std::string> scs;
      command = "PART[S][[All,1]]";
      send_to_math(command);
      get_from_math(scs);
      
      // Vector
      std::vector<std::string> vecs;
      command = "PART[V][[All,1]]";
      send_to_math(command);
      get_from_math(scs);
      
      std::cout << "Found " << lenpl << " particle sets." << std::endl;

      // Get to parsing this monster.
      for (int i=0; i<lenpl; i++)
      {
      
        // First things first, check to see if we are dealing with multiplets.
        // e.g., l = (e, mu, tau).
        int numelements;
        command = "Length[getPDG[plgum[[" + std::to_string(i+1) + ", 1]]]]";
        send_to_math(command);
        get_from_math(numelements);

        // If there's no associated PDG code.
        if (numelements == 0)
        {
            continue;
        }

        for (int j=0; j<numelements; j++)
        {
            // Initialise all properties we wish to find out about a particle.
            std::string name;
            std::string alt_name;
            std::string outputname;
            std::string antiname;
            std::string antioutputname;
            std::string mass;
            std::string colorrep;
            int spinX2 = -1; // Set to -1 for error catching
            int chargeX3 = 0;
            int color = 0;
            int pdg;
            int num;
            bool SM;
            bool capitalise = false;

            // Assume a particle is SC unless we spot it.
            bool self_conjugate = true;

            // Get SARAH name of the particle
            send_to_math("plgum[[" + std::to_string(i+1) + ", 1]]");
            get_from_math(alt_name);

            // Use this to get the spin of the particle

            // Get the PDG
            command = "Part[getPDG[plgum[[" + std::to_string(i+1) + ", 1]]], " + std::to_string(j+1) + "]";
            send_to_math(command);
            get_from_math(pdg);

            // If it's got a PDG of 0 it's not a physical particle. Don't care about it.
            if (pdg == 0) { continue; }

            command = "Length[getOutputName[plgum[[" + std::to_string(i+1) + ", 1]]]]";
            send_to_math(command);
            get_from_math(num);

            if (num == 2)
            {
                self_conjugate = false;
                command = "Part[getOutputName[plgum[[" + std::to_string(i+1) + ", 1]]], 1]";
                send_to_math(command);
                get_from_math(name);

                command = "Part[getOutputName[plgum[[" + std::to_string(i+1) + ", 1]]], 2]";
                send_to_math(command);
                get_from_math(antiname);
            }
            else if (num == 0)
            {
                command = "getOutputName[plgum[[" + std::to_string(i+1) + ", 1]]]";
                send_to_math(command);
                get_from_math(name);

                // Probe to see if it is self-conjugate
                command = "TrueQ[plgum[[" + std::to_string(i+1) + ", 1]] == conj[plgum[[" + std::to_string(i+1) + ", 1]]]]";
                send_to_math(command);
                bool is_sc;
                get_from_math(is_sc);
                if (not is_sc)
                {
                    self_conjugate = false;
                    capitalise = true;
                    antiname = name; // This will get changed in a minute
                }
            }
            else
            {
                std::stringstream err;
                err << "More than 2 particles here; "
                    << "what weird symmetries have you got???" 
                    << std::endl;
                throw std::runtime_error(err.str());
            }

            if (numelements > 1)
            {
                outputname = name + std::to_string(j+1);
                alt_name = alt_name + std::to_string(j+1);
            }
            else
            {
                outputname = name;
                antioutputname = antiname;
            }

            if (not self_conjugate && capitalise)
            {
                antioutputname = outputname;
                if (isupper(antioutputname[0])) { antioutputname = tolower(antioutputname[0]); }
                else { antioutputname[0] = toupper(antioutputname[0]); }
            }
            else if (not self_conjugate && not capitalise)
            {
                antioutputname = antiname;
            }
            else { antioutputname = outputname; }

            mass = "M" + outputname;

            // Get the color rep
            command = "getColorRep[plgum[["+std::to_string(i+1)+",1]]] // ToString";
            send_to_math(command);
            get_from_math(colorrep);

            // Translate this to a color that GAMBIT particle DB can use
            if (colorrep == "S") color = 1;
            else if(colorrep == "T") color = 3;
            else if(colorrep == "O") color = 8;
            else if(colorrep == "Six") color = 6;
            else throw std::runtime_error("Unrecognised color - " + colorrep + " - found.");

            // Electric charge
            command = "getElectricCharge[plgum[["+std::to_string(i+1)+",1]]] * 3";
            send_to_math(command);
            get_from_math(chargeX3);

            // Spin
            std::string spinentry;
            command = "getType[plgum[["+std::to_string(i+1)+",1]]]";
            send_to_math(command);
            get_from_math(spinentry);

            if (spinentry == "S") spinX2 = 0;
            else if(spinentry == "F") spinX2 = 1;
            else if(spinentry == "V") spinX2 = 2;
            // Get Spinformation for EWSB particles that come from mixings in either
            // matter/gauge sectors or are from VEVs
            else if(spinentry == "NoField") 
            {
              // Strip any trailing digits first
              size_t last_index = alt_name.find_last_not_of("0123456789");
              std::string strippedname = alt_name.substr(0, last_index + 1);

              // Check to see if it's in the list of fermions we have
              if (std::find(dFs.begin(), dFs.end(), strippedname) != dFs.end())
                spinX2 = 1;
              // If not - how about a scalar?
              else if (std::find(scs.begin(), scs.end(), strippedname) != scs.end())
                spinX2 = 0;
              // Or a vector?
              else if (std::find(vecs.begin(), vecs.end(), strippedname) != vecs.end())
                spinX2 = 2;
            }
            else throw std::runtime_error("Unrecognised spin - " + spinentry + " - found.");

            // If we haven't found a spin...
            if (spinX2 == -1)
              throw std::runtime_error("Unable to extract spin for particle: " + alt_name + ".");

            std::set<int> SM_pdgs = {1, 2, 3, 4, 5, 6, 11, 12, 13, 14, 15, 16, 21, 22, 23, 24};
            if (SM_pdgs.count(abs(pdg)))
            {
                SM = true;
            }
            else
            {
                SM = false;
            }

            // If it's not SM, get the tree-level mass relation
            std::string treelevelmass = "";

            if (not SM)
            {
              // If there are multiplets, the tree-level masses cannot give the mixings or the EWSB conditions
              // In these cases one should use a spectrum generator
              // Hence, flag the tree level mass as not valid so an error can be thrown later if there's no spec gen
              if (numelements > 1)
              {
                treelevelmass = "NotValid";
              }
              else
              {
                // Use Mathematica's terrible CForm output, amend this in GUM -- string replacement is nicer in Python :-)
                command = "TreeMass[" + alt_name + ",EWSB] // CForm // ToString";
                send_to_math(command);
                get_from_math(treelevelmass);
              }
            }

            // Add the particle to the list.
            Particle particle(pdg, outputname, spinX2, chargeX3, color, 
                              SM, mass, antioutputname, alt_name, "", treelevelmass);  // Blank space is for SPheno mass (alt_mass)
            partlist.push_back(particle);

        }

      }

      std::cout << "Done." << std::endl;

    }
    catch (std::runtime_error &e)
    {
      std::stringstream ss;
      ss << e.what() << ": Last command: " << command;
      throw std::runtime_error(ss.str());
    }
  }

  // Get parameters list
  void SARAH::get_paramlist(std::vector<Parameter> &paramlist, std::vector<Parameter> &sphenodependences)
  {

    std::cout << "Extracting parameters from SARAH model." << std::endl;

    std::string command = "";

    try
    {

      // Get list of parameters
      command = "pdgum = ParameterDefinitions;";
      send_to_math(command);

      // Here's another parameter list which has, crucically,
      // the size of mixing matrices.
      command = "pgum = parameters;";
      send_to_math(command);

      // Find out how many parameters we have to get.
      command = "Length[pdgum]";
      send_to_math(command);

      int lenpl;
      get_from_math(lenpl);

      std::cout << "Found " << lenpl << " parameter sets." << std::endl;

      for (int i=0; i<lenpl; i++)
      {
        std::string block;
        std::string paramname;
        std::string alt_paramname;
        bool real = false; // Assume it's complex unless we figure out that it's not.
        int index = 1;
        bool sphenodeps = false; // Do we want to save this as a SPheno dep?

        // Whether we've found an LH block
        bool LHblock = false;

        // Whether the LHblock is a mixing matrix [of some size]
        bool ismixing = false;

        command = "pdgum[[" + std::to_string(i+1) + ",1]]//ToString";
        send_to_math(command);

        // Get the parameter name as it is known in SARAH. This
        // might change later.
        get_from_math(paramname);

        command = "Length[pdgum[[" + std::to_string(i+1) + ",2]]]";
        send_to_math(command);

        // Each entry will be some sort of descriptor for
        // a particle. Discard things like LaTeX entries, 
        // descriptions in prose, etc.
        std::string entry;

        // Here are the useful things we want to query:
        // - blockname & index
        // - parameter name
        // - dependences
        // - if a parameter is *definitely* real

        command = "Real /. pdgum[[" + std::to_string(i+1) + ", 2]] // ToString";
        send_to_math(command);
        get_from_math(entry);

        // If it's definitely a real parameter, store this information
        if (entry == "True") real = true;

        // With DependenceSPheno -- flag it, so we can save it for later; we'll want it
        command = "DependenceSPheno /. pdgum[[" + std::to_string(i+1) + ",2]] // ToString";
        send_to_math(command);
        get_from_math(entry);
        if (entry != "DependenceSPheno" and entry != "None") 
        {
          sphenodeps = true;
        }

        // Otherwise -- if we don't want to save it: 
        // If it has a dependence -- not interested. Bin it.

        // Numerical dependence?
        // Parameters with DependenceNum are acutally needed, so keep these
        
        // Same with just Dependence
        command = "Dependence /. pdgum[[" + std::to_string(i+1) + ",2]] // ToString";
        send_to_math(command); 
        get_from_math(entry);
        if (entry != "Dependence" and entry != "None" and sphenodeps != true) continue;

        // Get block name
        command = "Head[LesHouches /. pdgum[[" + std::to_string(i+1) + ",2]]]";
        send_to_math(command);
        get_from_math(entry);

        // If we have a list, then there's a blockname and an index.
        if (entry == "List") 
        { 
            command = "LesHouches /. pdgum[[" + std::to_string(i+1) + ",2]]";
            send_to_math(command);
            std::vector<std::string> leshouches;
            get_from_math(leshouches);

            // blockname
            block = leshouches[0];
            // index
            index = std::stoi(leshouches[1]);
            LHblock = true;

            // If blockname is PHASES then it's effectively a mixing
            if (block == "phases" or block == "Phases")
              ismixing = true;
        }
        // If not a list, but a symbol, then we've got a mixing block
        else if(entry == "Symbol") 
        {
            // Get the blockname
            command = "LesHouches /. pdgum[[" + std::to_string(i+1) + ",2]]";
            send_to_math(command);
            get_from_math(block);

            if(block != "None")
            {
              ismixing = true;
              LHblock = true;
            }
        }
        else
        {
          throw std::runtime_error("Error in LesHouches block for the entry "
                                   + paramname + " in SARAH -- please check "
                                   "your SARAH model file.");
        }

        // Does the parameter have a different external
        // name than the internal SARAH name? If so, use it.
        command = "OutputName /. pdgum[[" + std::to_string(i+1) + ",2]] // ToString";
        send_to_math(command);
        get_from_math(entry);

        // If it has a different output name to 
        // internal, we'd better use it, seeing as GAMBIT
        // is... output, I guess.
        if (entry != "OutputName") 
        { 
            alt_paramname = paramname;
            paramname = entry;
        }

        // If it's a fundamental parameter of our theory, 
        // add it to the list (if it has an LH block!)
        if (LHblock && !ismixing && !sphenodeps)
        {
            Parameter parameter(paramname, block, index, alt_paramname, real);
            paramlist.push_back(parameter);
        }
        // If it's a mixing block then save it as as such 
        else if (LHblock && ismixing && !sphenodeps)
        {
            std::string shape;
            std::vector<std::string> shapesize;

            // Get the position of the mixing block in the other param list
            command = "pos = Position[pgum, " + alt_paramname + "]";
            send_to_math(command);

            // Extract the size of the matrix
            command = "Extract[pgum, pos[[1,1]]][[3]]";
            send_to_math(command);
            get_from_math(shapesize);

            // If it's a phase, then it's a scalar
            if(shapesize.size())
              shape = "m" + shapesize[0] + "x" + shapesize[1];
            else
              shape = "scalar";
            
            // Add to the paramlist -- but only as an *output* parameter, 
            // and with the shape of the matrix
            bool is_output = true;

            Parameter parameter(paramname, block, index, alt_paramname, 
                                real, shape, is_output);
            paramlist.push_back(parameter);
        }
        // Save to the SPheno dependencies
        else if (LHblock && sphenodeps)
        {
          // If there's a SPheno dep., use Mathematica's terrible CForm output.
          // We'll amend this in GUM -- string replacement is nicer in Python :-)
          command = "DependenceSPheno /. pdgum[[" + std::to_string(i+1) + ",2]] // CForm // ToString";
          send_to_math(command);
          get_from_math(entry);
          // Here we are storing the alt_paramname as the definition. Be careful!
          Parameter sphenodep(paramname, block, index, entry, real);
          sphenodependences.push_back(sphenodep);
        }

      }
    }
    catch (std::runtime_error &e)
    {
      std::stringstream ss;
      ss << e.what() << ": Last command: " << command;
      throw std::runtime_error(ss.str());
    }
  }

  // Get minpar and extpar parameters and add them to the parameter list
  void SARAH::get_minpar_extpar(std::vector<Parameter> &parameters)
  {
    std::cout << "Extracting MINPAR and EXTPAR parameters from SPheno" << std::endl;

    std::vector<std::vector<std::string> > minpar;
    std::vector<std::vector<std::string> > extpar;

    std::string defaultlist;
    std::string command = "";

    try
    {
      

      // Check if MINPAR is a list
      bool is_list;
      command = "Head[MINPAR]===List";
      send_to_math(command);
      get_from_math(is_list);

      // Find out how many parameters we have...
      command = "Length[pdgum]";
      send_to_math(command);
      int lenpl;
      get_from_math(lenpl);

      // Get default parameters
      bool default_is_list;
      command = "Head[DefaultInputValues]===List";
      send_to_math(command);
      get_from_math(default_is_list);

      // If there's no 'DefaultInputValues' list, try 
      // DefaultInputValues[1] -- sometimes models have
      // different benchmark points. 
      if(default_is_list)
      {
        defaultlist = "DefaultInputValues";
      }
      else
      {
        bool please_be_list;
        command = "Head[DefaultInputValues[1]]===List";
        send_to_math(command);
        get_from_math(please_be_list);
        if(please_be_list)
        {
          defaultlist = "DefaultInputValues[1]";
        }
        else
        {
          defaultlist = "NONE";
        }
      }

      if(is_list)
      {
        // Get the MINPAR list
        command = "MINPAR";
        send_to_math(command);
        get_from_math(minpar);

        // Add MINPAR parameters to the parameter list
        for(std::vector<std::string> par : minpar)
        {
          // Query the parameter list, as the MINPAR entry may end up being a BC already,
          // such as TanBeta. Then we should find out if it's real or not.
          std::string paramname;
          bool real = false;
          for (int i=0; i<lenpl; i++)
          {
            command = "pdgum[[" + std::to_string(i+1) + ",1]] // ToString";
            send_to_math(command);
            get_from_math(paramname);

            if(par[1] == paramname)
            {
              command = "Real /. pdgum[[" + std::to_string(i+1) + ", 2]] // ToString";
              send_to_math(command);
              std::string entry;
              get_from_math(entry);
              if(entry == "True") real = true;
            }
          }
          
          Parameter param(par[1], "MINPAR", std::stoi(par[0]), par[1], real);
 
          // Get default values (if there are any)
          if (defaultlist != "NONE")
          {
            std::string value;
            command = par[1] + "/." + defaultlist;
            send_to_math(command);
            get_from_math(value);
            if(value != par[1])
              param.set_default(std::stod(value));
          }

          parameters.push_back(param);
        }
      }

      // Check if EXTPAR is a list
      command = "Head[EXTPAR]===List";
      send_to_math(command);
      get_from_math(is_list);

      if(is_list)
      {
        // Get the EXTPAR list
        command = "EXTPAR";
        send_to_math(command);
        get_from_math(extpar);

        // Add EXTPAR parameters to the parameter list
        for(std::vector<std::string> par : extpar)
        {
          // Query the parameter list, as the EXTPAR entry may end up being a BC already,
          // such as TanBeta. Then we should find out if it's real or not.
          std::string paramname;
          bool real = false;
          for (int i=0; i<lenpl; i++)
          {
            command = "pdgum[[" + std::to_string(i+1) + ",1]] // ToString";
            send_to_math(command);
            get_from_math(paramname);

            if(par[1] == paramname)
            {
              command = "Real /. pdgum[[" + std::to_string(i+1) + ", 2]] // ToString";
              std::cout << command << std::endl;
              send_to_math(command);
              std::string entry;
              get_from_math(entry);
              if(entry == "True") real = true;
            }
          }
          Parameter param(par[1], "EXTPAR", std::stoi(par[0]), par[1], real);

          // Get default values (if there are any)
          if (defaultlist != "NONE")
          {
            std::string value;
            command = par[1] + "/." + defaultlist;
            send_to_math(command);
            get_from_math(value);
            if(value != par[1])
              param.set_default(std::stod(value));
          }

          parameters.push_back(param);
        }
      }

    }
    catch (std::runtime_error &e)
    {
      std::stringstream ss;
      ss << e.what() << ": Last command: " << command;
      throw std::runtime_error(ss.str());
    }

  }

  // Get the blocks, entries and parameter names of the in-out blocks
  void SARAH::get_inout_blocks(std::vector<Parameter> &parameters)
  {
    std::cout << "Extracting in-out blocks from SPheno" << std::endl;

    std::string command = "";

    try
    {

      // Get the length of the CombindedBlock, as the shape is not a vector<string>
      int length;
      command = "Length[CombindedBlock]";
      send_to_math(command);
      get_from_math(length);

      for(int i=1; i<=length; i++)
      {
        // Get the name of the block
        std::string blockname;
        command = "CombindedBlock[["+std::to_string(i)+",1]]";
        send_to_math(command);
        get_from_math(blockname);
        blockname = blockname + "IN";

        // Now get the parameters in the block
        int block_length;
        command = "Length[CombindedBlock[["+std::to_string(i)+"]]]";
        send_to_math(command);
        get_from_math(block_length);

        for(int j=2; j<=block_length; j++)
        {

          std::string parname;
          command = "CombindedBlock[["+std::to_string(i)+","+std::to_string(j)+",1]] // ToString";
          send_to_math(command);
          get_from_math(parname);

          std::string parindex;
          command = "CombindedBlock[["+std::to_string(i)+","+std::to_string(j)+",2]]";
          send_to_math(command);
          get_from_math(parindex);

          // Get the output name and remove params that have dependencies
          int pdlength;
          command = "Length[pdgum]";
          send_to_math(command);
          get_from_math(pdlength);

          for(int j=1; j<=pdlength; j++)
          {
            std::string name;
            command = "pdgum[["+std::to_string(j)+",1]]//ToString";
            send_to_math(command);
            get_from_math(name);

            if(name == parname)
            {
              std::string entry;

              command = "DependenceNum /. pdgum[[" + std::to_string(j) + ",2]] // ToString";
              send_to_math(command);
              get_from_math(entry);
              if (entry != "DependenceNum" and entry != "None") continue;

              command = "DependenceSPheno /. pdgum[[" + std::to_string(j) + ",2]] // ToString";
              send_to_math(command);
              get_from_math(entry);
              if (entry != "DependenceSPheno" and entry != "None") continue;

              command = "Dependence /. pdgum[[" + std::to_string(j) + ",2]] // ToString";
              send_to_math(command);
              get_from_math(entry);
              if (entry != "Dependence" and entry != "None") continue;

              std::string outputname;
              command = "OutputName /. pdgum[[" + std::to_string(j) + ",2]] // ToString";
              send_to_math(command);
              get_from_math(outputname);
              if(outputname == "OutputName") outputname = parname;

              bool real = false;
              command = "Real /. pdgum[[" + std::to_string(j) + ", 2]] // ToString";
              send_to_math(command);
              get_from_math(entry);
              if(entry == "True") real = true;

              parameters.push_back(Parameter(outputname, blockname, std::stoi(parindex), outputname, real));

            }
          }
        }

      }
    }
    catch (std::runtime_error &e)
    {
      std::stringstream ss;
      ss << e.what() << ": Last command: " << command;
      throw std::runtime_error(ss.str());
    }
  }

  // Get the boundary conditions for all parameters in the parameter list
  void SARAH::get_boundary_conditions(std::map<std::string, std::string> &bcs, 
                                      std::vector<Parameter> parameters)
  {
    std::cout << "Getting boundary conditions" << std::endl;

    std::string command = "";

    try
    {
      // TODO: Expand this for other types of boundary conditions 
      int bc_len;
      command = "Length[BoundaryLowScaleInput]";
      send_to_math(command);
      get_from_math(bc_len);
      for(int i=1; i<=bc_len; i++)
      {
        std::string bc_name;
        command = "BoundaryLowScaleInput[["+std::to_string(i)+",1]] // ToString";
        send_to_math(command);
        get_from_math(bc_name);

        std::string bc;
        command = "BoundaryLowScaleInput[["+std::to_string(i)+",2]] // ToString";
        send_to_math(command);
        get_from_math(bc);

        for(auto param = parameters.begin(); param != parameters.end(); param++)
        {
          if (param->name() == bc_name or param->alt_name() == bc_name)
          {
              bcs[bc] = param->name();
          }
        }
      }
    }
    catch (std::runtime_error &e)
    {
      std::stringstream ss;
      ss << e.what() << ": Last command: " << command;
      throw std::runtime_error(ss.str());
    }
  }

  // Extract parameters used to solve tadpoles and mark them as output
  void SARAH::get_tadpoles(std::vector<Parameter> &parameters)
  {
    std::cout << "Extracting parameters to solve tadpoles" << std::endl;

    std::string command = "";

    try
    {
      bool is_list; 
      command = "Head[ParametersToSolveTadpoles]===List";
      send_to_math(command);
      get_from_math(is_list);
      if(is_list)
      {
        std::vector<std::string> tadpoles;
        command = "ParametersToSolveTadpoles";
        send_to_math(command);
        get_from_math(tadpoles);

        for(auto param = parameters.begin(); param != parameters.end(); param++)
          for(auto tp : tadpoles)
            if (param->name() == tp or param->alt_name() == tp)
            {
              param->set_output(true);
            }
      }
    }
    catch (std::runtime_error &e)
    {
      std::stringstream ss;
      ss << e.what() << ": Last command: " << command;
      throw std::runtime_error(ss.str());
    }
  }

  // Add the names of spheno masses to all particles
  void SARAH::add_SPheno_mass_names(std::vector<Particle> &particles)
  {
    std::cout << "Adding SPheno masses" << std::endl;

    std::string command = "";

    try
    {
      std::vector<Particle> newParticles;
      for (auto part = particles.begin(); part != particles.end(); part++)
      {
        std::string sarah_mass;

        command = "SPhenoMass[" + part->alt_name() + "]";
        send_to_math(command);
        get_from_math(sarah_mass);

        newParticles.push_back(Particle(part->pdg(), part->name(), part->spinX2(), part->chargeX3(), part->color(), part->SM(), part->mass(), part->antiname(), part->alt_name(), sarah_mass, part->tree_mass()));
      }
      particles = newParticles;
    }
    catch (std::runtime_error &e)
    {
      std::stringstream ss;
      ss << e.what() << ": Last command: " << command;
      throw std::runtime_error(ss.str());
    }
  }

  // Leave only the parameters that SPheno uses
  void SARAH::SPheno_parameters(std::vector<Parameter> &parameters)
  {
    std::cout << "Getting SPheno parameters" << std::endl;

    std::string command;

    try
    {
      bool is_list;
      std::vector<std::string> SPhenoparams;
      std::vector<std::string> SPhenomassparams;
      std::vector<std::string> MCparams;
      std::vector<std::string> MCvars;

      // Get the list of parameters and vevs used by SPheno
      command = "Head[listAllParametersAndVEVs]===List";
      send_to_math(command);
      get_from_math(is_list);
      if(is_list)
      {
        command = "SPhenoForm/@listAllParametersAndVEVs";
        send_to_math(command);
        get_from_math(SPhenoparams);

      }

      // Get the mixing parameters
      command = "Head[NewMassParameters]===List";
      send_to_math(command);
      get_from_math(is_list);
      if(is_list)
      {
        command = "SPhenoForm/@NewMassParameters";
        send_to_math(command);
        get_from_math(SPhenomassparams);
      }

      // Check if any of the parameters have a matching condition
      command = "mcgum = DEFINITION[MatchingConditions]";
      send_to_math(command);
 
      int size = 0;
      command = "Length[mcgum]";
      send_to_math(command);
      get_from_math(size);
      for(int i=1; i<=size; i++)
      {
        std::string par;
        command = "mcgum[[" + std::to_string(i) + ",1]]";
        send_to_math(command);
        get_from_math(par);
        MCparams.push_back(par);

        std::vector<std::string> vars;
        command = "Variables[mcgum[[" + std::to_string(i) + ",2]]]";
        send_to_math(command);
        get_from_math(vars);
        MCvars.insert(MCvars.end(),vars.begin(), vars.end());
      }

      std::vector<Parameter> newParameters;
      for(auto param : parameters)
      {

        for(auto mcv: MCvars)
        {
          if(param.name() == mcv or param.alt_name() == mcv)
          {
            if(std::find(SPhenoparams.begin(), SPhenoparams.end(), param.name()) == SPhenoparams.end() and
               std::find(SPhenoparams.begin(), SPhenoparams.end(), param.alt_name()) == SPhenoparams.end())
            {
              // If the param is in the matching conditions, we always want the name in the matching conditions
              SPhenoparams.push_back(mcv);
            }
          }
        }

        for(auto SPhenoparam :  SPhenoparams)
        {
          if(param.name() == SPhenoparam or param.alt_name() == SPhenoparam)
          {
            bool is_output = param.is_output();
            if(std::find(MCparams.begin(), MCparams.end(), param.name()) != MCparams.end() or
               std::find(MCparams.begin(), MCparams.end(), param.alt_name()) != MCparams.end())
              is_output = true;
            newParameters.push_back(Parameter(SPhenoparam, param.block(), param.index(), param.alt_name(), param.is_real(), param.shape(), is_output, param.bcs()));
          }
        }

        for(auto SPhenomassparam :  SPhenomassparams)
        {
          if(param.name() == SPhenomassparam or param.alt_name() == SPhenomassparam)
          {
            newParameters.push_back(Parameter(SPhenomassparam, param.block(), param.index(), param.alt_name(), param.is_real(), param.shape(), param.is_output(), param.bcs()));
          }
        }
      }

      parameters = newParameters;
    }
    catch (std::runtime_error &e)
    {
      std::stringstream ss;
      ss << e.what() << ": Last command: " << command;
      throw std::runtime_error(ss.str());
    }
  }

  // Returns the eigenstate & mixing matrix after EWSB 
  void SARAH::get_mixing_matrices(std::map<std::string, std::string> &mixings)
  {
    std::cout << "Getting mixing matrices from SARAH..." << std::endl;

    std::string command = "";

    try
    {
      command = "dgum = DEFINITION[EWSB][MatterSector];";
      send_to_math(command);

      // Find out how many (sets of) mixing matrices there are...
      int len;
      command = "Length[dgum]";
      send_to_math(command);
      get_from_math(len);
  
      for(int i=1; i<=len; i++)
      {
        std::vector<std::string> eigenpairs;
        // Make this one list, easier to parse
        command = "agum = Flatten[dgum[[" + std::to_string(i) + ",2]]]";
        send_to_math(command);
        get_from_math(eigenpairs);

        // Check we haven't got additional entries
        int size = eigenpairs.size();

        if(size % 2)
          throw std::runtime_error("Not an even number of matrix-eigenstate pairs! Check your SARAH file.");

        // List should look like: {<EIGENSTATE_1>, <MIXING_MATRIX_1>, <EIGENSTATE_2>, <MIXING_MATRIX_2>, ...}
        for(int i=0; i<size; i++)
        {
          std::string eigenstate = eigenpairs[i];
          std::string mixingmat = eigenpairs[i+1];
 
          int len2;

          // Check to see if the particle name is a Weyl fermion
          bool is_weyl;
          command = "MemberQ[WeylFermionAndIndermediate[[;;,1]],"+eigenstate+"]";
          send_to_math(command);
          get_from_math(is_weyl);

          // If it's a Weyl fermion, get the Dirac fermion
          if(is_weyl)
          {
            command = "Select[DEFINITION[EWSB][DiracSpinors], MemberQ[#[[2]],"+eigenstate+", 2] &][[1,1]]";
            send_to_math(command);
            get_from_math(eigenstate);
          }

          // Check to see if the mixing matrix has a different OutputName
          command = "Length[pdgum]";
          send_to_math(command);
          get_from_math(len2);
          
          for(int j=0; j<len2; j++)
          {
            std::string pname;
            command = "pdgum[[" + std::to_string(j+1) + ",1]] // ToString";
            send_to_math(command);
            get_from_math(pname);

            if(pname == mixingmat)
            {
              std::string oname;
              command = "OutputName /. pdgum[[" + std::to_string(j+1) + ",2]] // ToString";
              send_to_math(command);
              get_from_math(oname);

              if(oname == "OutputName")
              {
                mixings[mixingmat] = eigenstate;
              }
              else
              {
               mixings[oname] = eigenstate;
              }
              continue;
            }
          }
          // Increment again; need to do +2 each iteration.
          i++;
        }
      }
    }
    catch (std::runtime_error &e)
    {
      std::stringstream ss;
      ss << e.what() << ": Last command: " << command;
      throw std::runtime_error(ss.str());
    }
  }

  // Write CalcHEP output.
  void SARAH::write_ch_output()
  {
    std::cout << "Writing CalcHEP output." << std::endl;

    // Options for the CH output.
    std::string options;
    // This is currently hard-coded, because GAMBIT needs to interface with CalcHEP 
    // in a specific way.
    /* do not read from SLHA file |  let alphaS run  |  all masses computed externally */
    options = "SLHAinput -> False, UseRunningCoupling -> True, CalculateMasses -> False";

    // Write output.
    std::string command = "MakeCHep[" + options + "];";
    send_to_math(command);

    std::cout << "CalcHEP files written." << std::endl;
  }

  // Write MadGraph output.
  void SARAH::write_madgraph_output()
  {
    std::cout << "Writing MadGraph (UFO) output for Pythia/MadDM." << std::endl;

    // Write output.
    std::string command = "MakeUFO[];";
    send_to_math(command);

    std::cout << "MadGraph files written." << std::endl;
  }

  // Write SPheno output.
  void SARAH::write_spheno_output(std::map<std::string,std::string> options)
  {
      std::cout << "Writing SPheno output." << std::endl;
      std::cout << "Strap in tight -- this might take a while..." << std::endl;
      
      // Options for SPheno output.
      std::string SPhenoOptions = "";
      // - InputFile (default $MODEL/SPheno.m)
      // - StandardCompiler -> <COMPILER> (default gfortran) // TG: This should be handled by GM cmake system, so no need
      // - IncludeLoopDecays (default True)
      // - ReadLists (default False) 
      // - IncludeFlavourKit (default True but we set it to False cause FlavourKit will be a different backend)
      //options = "IncludeLoopDecays->False, IncludeFlavorKit->False, ReadLists->True";
      for(auto it = options.begin(); it != options.end(); it++)
      {
        SPhenoOptions += it->first + "->" + it->second + ", ";
      }
      SPhenoOptions += "IncludeFlavorKit->False";

      std::cout << "Options for SPheno given as: " << SPhenoOptions << std::endl;

      // Write output.
      std::string command = "MakeSPheno[" + SPhenoOptions + "];";
      send_to_math(command);

      std::cout << "SPheno files written." << std::endl;
  }

  // Write Vevacious output.
  void SARAH::write_vevacious_output()
  {
      std::cout << "Writing Vevacious output." << std::endl;  

      // Options for Vevacious output.
      std::string options;
      options = "Version->\"++\", ReadLists->True";

      // Write output.
      std::string command = "MakeVevacious[" + options + "];";
      send_to_math(command);  

      std::cout << "Vevacious files written." << std::endl;
  }

  // Do all operations with SARAH
  void all_sarah(Options opts, std::vector<Particle> &partlist, std::vector<Parameter> &paramlist,
                 Outputs &outputs, std::vector<std::string> &backends,
                 std::map<std::string,bool> &flags, std::map<std::string, std::string> &mixings,
                 std::map<std::string, std::string> &bcs,
                 std::vector<Parameter> &sphenodependences, Error &error)
  {

    try
    {
      std::cout << "Calling SARAH with model " << opts.model() << "..." << std::endl;

      // Create SARAH object, open link to Mathematica, load SARAH and the model
      SARAH model(opts.model());

      // Get the options to pass to backends
      std::map<std::string, std::map<std::string, std::string> > BEoptions = opts.options();

      // Check the model using SARAH's CheckModel function
      // Note: this is necessary, as it initilizes some variables used later, do not remove
      model.check_model(opts.model(), backends);

      // Get all of the particles
      model.get_partlist(partlist);

      // And all parameters
      model.get_paramlist(paramlist, sphenodependences);

      // And mixings
      model.get_mixing_matrices(mixings);

      // Where the outputs all live
      std::string outputdir = std::string(SARAH_PATH) + "/Output/" + opts.model() + "/EWSB/";

      /// Write CalcHEP output (for MicrOmegas also)
      if (std::find(backends.begin(), backends.end(), "calchep") != backends.end()   ||
          std::find(backends.begin(), backends.end(), "micromegas") != backends.end() )
      {
        model.write_ch_output();

        // Location of CalcHEP files
        std::string chdir = outputdir + "CHep";
        std::replace(chdir.begin(), chdir.end(), ' ', '-');
        outputs.set_ch(chdir);
      }
 
      /// Write MadGraph output
      if (std::find(backends.begin(), backends.end(), "pythia") != backends.end() ||
          std::find(backends.begin(), backends.end(), "ufo") != backends.end() )
      {
        model.write_madgraph_output();

        // Location of MadGraph (UFO) files
        std::string mgdir = outputdir + "UFO";
        std::replace(mgdir.begin(), mgdir.end(), ' ', '-');
        outputs.set_mg(mgdir);
      }

      /// Write SPheno output
      if (std::find(backends.begin(), backends.end(), "spheno") != backends.end() )
      {
       
        std::map<std::string, std::string> sphenoopts;

        // If there's SPheno options in the map, pass them over...
        if ( BEoptions.find("spheno") != BEoptions.end() ) 
        {
          sphenoopts = BEoptions.at("spheno");
        }

        model.write_spheno_output(sphenoopts);

        // Leave only the parameters that SPheno uses
        model.SPheno_parameters(paramlist);
 
        // Get minpar and extpar parameters
        model.get_minpar_extpar(paramlist);

        // Get useful SPheno flags, default to False
        flags = {
          {"SupersymmetricModel",false}, 
          {"OnlyLowEnergySPheno", false},
          {"UseHiggs2LoopMSSM", false},
          {"SA`AddOneLoopDecay", false}
        };
        model.get_flags(flags);

        // Get the boundary conditions for the parameters
        model.get_boundary_conditions(bcs, paramlist);

        // Get the parameters used to solve tadpoles and remove them from the list
        model.get_tadpoles(paramlist);

        // Get in-out blocks
        model.get_inout_blocks(paramlist);

        // Add SPheno mass names for all particles
        model.add_SPheno_mass_names(partlist);

        // Location of SPheno files
        std::string sphdir = outputdir + "SPheno";
        std::replace(sphdir.begin(), sphdir.end(), ' ', '-');
        outputs.set_sph(sphdir);
      }


      /// Write Vevacious output
      if (std::find(backends.begin(), backends.end(), "vevacious") != backends.end() )
      {
        model.write_vevacious_output();        

        // Location of Vevacious (.vin + .xml) files
        // Note these do not live in the same place the other output files do.
        std::string vevdir = std::string(SARAH_PATH) + "/Output/" + opts.model() + "/Vevacious";
        std::replace(vevdir.begin(), vevdir.end(), ' ', '-');
        outputs.set_vev(vevdir);
      }

    }
    catch(std::exception &e)
    {
      error.raise("SARAH Error: " + std::string(e.what()));
    }
  }

   
} // namespace GUM

// Now all the grizzly stuff, so Python can call C++ (which can call Mathematica...)
using namespace boost::python;

// Nasty function to translate python dictionaries to maps
object setOptions(tuple args, dict kwargs)
{
    Options& self = extract<Options&>(args[0]);

    list keys = kwargs.keys();

    std::map<std::string,std::map<std::string,std::string> > outMap;
    for(int i = 0; i < len(keys); ++i)
    {
        dict secondLayer = extract<dict>(kwargs[keys[i]]);
        list keys2 = secondLayer.keys();

        std::map<std::string,std::string> tempMap;
        for(int j=0; j < len(keys2); ++j)
        {
          std::string value = extract<std::string>(str(secondLayer[keys2[j]]));
          tempMap[extract<std::string>(keys2[j])] = value;
        }
        outMap[extract<std::string>(keys[i])] = tempMap;
    }
    self.setOptions(outMap);

    return object();
}

BOOST_PYTHON_MODULE(libsarah)
{

  class_<Particle>("SARAHParticle", init<int, std::string, int, int, int, bool, std::string, std::string, std::string, std::string, std::string>())
    .def("pdg",      &Particle::pdg)
    .def("name",     &Particle::name)
    .def("SM",       &Particle::SM)
    .def("spinX2",   &Particle::spinX2)
    .def("chargeX3", &Particle::chargeX3)
    .def("color",    &Particle::color)
    .def("mass",     &Particle::mass)
    .def("SC",       &Particle::SC)
    .def("antiname", &Particle::antiname)
    .def("alt_name", &Particle::alt_name)
    .def("alt_mass", &Particle::alt_mass)
    .def("tree_mass", &Particle::tree_mass)
    ;

  class_<Parameter>("SARAHParameter", init<std::string, std::string, int, std::string, bool, std::string, bool, std::string>())
    .def("name",      &Parameter::name)
    .def("block",     &Parameter::block)
    .def("index",     &Parameter::index)
    .def("alt_name",  &Parameter::alt_name)
    .def("is_real",   &Parameter::is_real)
    .def("shape",     &Parameter::shape)
    .def("is_output", &Parameter::is_output)
    .def("bcs",       &Parameter::bcs)
    .def("defvalue",  &Parameter::defvalue)
    ;

  class_<Options>("SARAHOptions", init<std::string, std::string>())
    .def("package",     &Options::package)
    .def("model",       &Options::model)
    .def("setOptions",  raw_function(&setOptions,1))
    ;

  class_<Outputs>("SARAHOutputs", init<>())
    .def("get_ch",   &Outputs::get_ch)
    .def("get_mg",   &Outputs::get_mg)
    .def("get_sph",  &Outputs::get_sph)
    .def("get_vev",  &Outputs::get_vev)    
    .def("set_ch",   &Outputs::set_ch)
    .def("set_mg",   &Outputs::set_mg)
    .def("set_sph",  &Outputs::set_sph)
    .def("set_vev",  &Outputs::set_vev)
    ;

  class_<Error>("SARAHError", init<>())
    .def("is_error", &Error::is_error)
    .def("what", &Error::what)
    ;

  class_< std::vector<Particle> >("SARAHVectorOfParticles")
    .def(vector_indexing_suite< std::vector<Particle> >() )
    ;

  class_< std::vector<Parameter> >("SARAHVectorOfParameters")
    .def(vector_indexing_suite< std::vector<Parameter> >() )
    ;

  class_< std::map<std::string,bool> >("SARAHMapStrBool")
    .def(map_indexing_suite< std::map<std::string,bool> >() )
    ;

  class_< std::vector<std::string> >("SARAHBackends")
    .def(vector_indexing_suite< std::vector<std::string> >() )
    ;

  class_< std::map<std::string, std::string> >("SARAHMapStrStr")
    .def(map_indexing_suite< std::map<std::string, std::string>, true>() )
    ;

  def("all_sarah", GUM::all_sarah);

}
