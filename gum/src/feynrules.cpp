//   GUM: GAMBIT Universal Model Machine
//   ************************************
///  \file
///
///  Definitions of Feynrules class
///
///  **********************************
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2018, 2019, 2020
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 July
///
///  ***********************************

#include <set>
#include <algorithm>
#include <cstring>
#include <fstream>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "feynrules.hpp"

namespace GUM
{

  // Feynrules constructor, loads Feynrules and model
  FeynRules::FeynRules(std::string model, std::string base_model) : Math_Package(model)
  {
    // Math_Package constructor already creates the WSTP link
    
    try
    {
      // Load Feynrules
      load_feynrules();

      // Load model
      load_model(model, base_model);
    }
    catch(...) { throw; }
  }

  // Load Feynrules
  void FeynRules::load_feynrules()
  {

    std::cout << "Loading FeynRules... ";
    std::cout.flush();

    std::string input = "$FeynRulesPath = SetDirectory[\"" + std::string(FEYNRULES_PATH) + "\"]";

    send_to_math(input);

    const char* out;
    if (!WSGetString(link, &out))
    {
        throw std::runtime_error("Error loading FeynRules. Please check that Mathematica\n"
                                 "is working and that FeynRules actually lives where CMake put it, in:\n"
                                 "  " + std::string(FEYNRULES_PATH) + "\n"
                                 "Please try rebuilding.");
    }
    else
    {
        std::cout << "FeynRules loaded from " << out << "." << std::endl;
    }

    // Need to run FR serially, as it bugs out in parallel
    input = "FR$Parallel=False;";
    send_to_math(input);

    input = "<<FeynRules`";
    send_to_math(input);


  }

  void FeynRules::load_model(std::string model, std::string base_model)
  {

    std::cout << "Loading model " + model + " in FeynRules";
    std::cout.flush();
    if (not base_model.empty()) { std::cout << ", piggybacking off of " << base_model; }
    std::cout << "... " << std::endl;

    std::string modelpath;
    
    // Check to see if the model is in the FeynRules directory
    modelpath = std::string(FEYNRULES_PATH) + "/Models/" + model + "/" + model + ".fr";
    std::ifstream modelpath1(modelpath.c_str());

    // If it's not in the FeynRules directory, try the gum Models dir...
    if (!modelpath1.good())
    {
        modelpath = std::string(GUM_DIR) + "/Models/" + model + "/" + model + ".fr";
        std::ifstream modelpath2(modelpath.c_str());
        if (!modelpath2.good())
        {
            throw std::runtime_error("GUM Error: Unable to find the model " + model + " in either the "
                                     "FeynRules model directory, or the GUM model directory!");
        }
    }

    // Same process for the base_model
    if (!base_model.empty())
    {
        std::string basepath = std::string(FEYNRULES_PATH) + "/Models/" + base_model + "/" + base_model + ".fr";

        std::ifstream basepath1(basepath.c_str());
        if (!basepath1.good())
        {
            basepath = std::string(GUM_DIR) + "/Models/" + base_model + "/" + base_model + ".fr";
            std::ifstream basepath2(basepath.c_str());
            if (!basepath2.good())
            {
            throw std::runtime_error("GUM Error: Unable to find the base model " + base_model + " in either"
                                     " the FeynRules model directory, or the GUM model directory!");
            }
        }
        // Fire off the LoadModel command with the model and the base model.
        std::string command = "LoadModel[\"" + basepath + "\",\"" + modelpath + "\"]";
        send_to_math(command);
    }
    else
    {
        // Fire off the LoadModel command with just the model.
        std::string command = "LoadModel[\"" + modelpath + "\"]";
        send_to_math(command);
    }

    // Check the model has been loaded by querying the model name. If it has changed from the default then we're set.
    // TODO: need to check for duplicate definitions of gauge groups, field contents etc - this makes gum freeze 
    std::string modelname = get_modelname();

    std::string tomatch = "Models" + model + model;
    if (modelname == tomatch)
        throw std::runtime_error("FeynRules Error: Could not load model " + model + ". Please check your FeynRules file.");
    else if ((modelname == "Standard Model") and (base_model.empty()))
        throw std::runtime_error("FeynRules Error: GUM is for BSM physics, yo!");
    else if ((modelname == "Standard Model") and (not base_model.empty()))
        throw std::runtime_error("FeynRules Error: GUM tried to import something on top of the Standard Model, but your model file did not import properly. Please check it.");
    else if ((modelname == "M$ModelName"))
        throw std::runtime_error("FeynRules Error: models not loaded correctly, given as 'M$ModelName'. Please check your FeynRules files.");
    // All good. else {
    std::cout << "Model " + model + " loaded successfully, with model name " << modelname << "." << std::endl;
    //}
  }

  // The model may have a different "internal" name than what's on the package.
  // Need this info for output files, etc.
  std::string FeynRules::get_modelname()
  {
    std::string command = "M$ModelName";
    send_to_math(command);

    std::string modelname;
    get_from_math(modelname);
    return modelname;
  }

  /// Load a restriction file up. Firstly tries to find it in the model directory,
  /// then the base_model directory.
  void FeynRules::load_restriction(std::string model, std::string base_model, std::string rst)
  {
   
    std::cout << "Attempting to load restriction " + rst + "... " << std::endl;

    std::string respath;
    respath = std::string(FEYNRULES_PATH) + "/Models/" + model + "/" + rst + ".rst";
    std::ifstream path1(respath.c_str());

    // If it's not in the FeynRules directory, try the gum Models dir...
    if (!path1.good())
    {
        respath = std::string(GUM_DIR) + "/Models/" + model + "/" + rst + ".rst";
        std::ifstream path2(respath.c_str());

        // If it's not in the model directory, try the base_model...
        if (!path2.good())
        {  
            if (!base_model.empty())
            {
                respath = std::string(FEYNRULES_PATH) + "/Models/" + base_model + "/" + rst + ".rst";
        
                std::ifstream path3(respath.c_str());
                if (!path3.good())
                {
                    respath = std::string(GUM_DIR) + "/Models/" + base_model + "/" + rst + ".rst";
                    std::ifstream path4(respath.c_str());
                    if (!path4.good())
                    {
                    throw std::runtime_error("GUM Error: Unable to find the restriction " + rst + " in either\n"
                                             "the FeynRules model directory, or the GUM model directory,"
                                             "for both the model *and* the base_model!");
                    }
                }
            }
            else
            {
                throw std::runtime_error("GUM Error: Unable to find the restriction " + rst + " in either\n"
                                         "the FeynRules model directory, or the GUM model directory!");
            }
        }
    }

    std::cout << "Found restriction file at " << respath << std::endl;

    // LoadRestriction command.
    std::string command = "LoadRestriction[\"" + respath + "\"]";
    send_to_math(command);

    // Check restrictions are ok
    command = "Length[M$Restrictions]";
    send_to_math(command);

    int out;
    get_from_math(out);
    if (out == 0)
        throw std::runtime_error("FeynRules Error: No restrictions loaded. Please check "
                                 "your .gum file and \nthat your .rst files are in the "
                                 "correct place.");

    std::cout << "Restriction " + rst + " loaded successfully." << std::endl;
  }

  // Check to see the Lagrangian returns something sensible
  void FeynRules::check_lagrangian(std::string LTot)
  {
    std::cout << "Checking the Lagrangian... you have specified the following: ";
    std::cout << LTot << std::endl; 

    std::string command = "Head@("+LTot+") // ToString";
    send_to_math(command);

    std::string entry;
    get_from_math(entry);
    if (entry == "Symbol")
    {
        command = LTot + "// ToString";
        send_to_math(command);
        get_from_math(entry);
        if (entry == LTot)
        {
            std::stringstream ss;
            ss << "Lagrangian has not been loaded successfully." << std::endl;
            ss << "Please check your .gum file and .fr file(s)." << std::endl;
            throw std::runtime_error(ss.str());
        }
    }

    std::cout << "Lagrangian seems OK..." << std::endl;
  }

  // Check a model is Hermitian (it should be...)
  // Also check for correct normalisation
  void FeynRules::check_herm(std::string LTot)
  {

    std::cout << "Checking the model is Hermitian... ";
    std::cout.flush();

    std::string command = "ch = CheckHermiticity[" + LTot + "]";
    send_to_math(command);

    command = "Length[ch]";
    send_to_math(command);

    int lench;
    get_from_math(lench);

    if (lench == 0)
    {
        std::cout << "Your Lagrangian is Hermitian." << std::endl;
    }
    else
    {
        std::stringstream ss;
        ss << "Your Lagrangian is not Hermitian." << std::endl;
        ss << "FeynRules found " + std::to_string(lench) + " vertices in L-HC[L]." << std::endl;
        ss << "Please check your FeynRules file." << std::endl;
        throw std::runtime_error(ss.str());
    }

    std::cout << "Checking kinetic and mass terms are properly diagonalised..." << std::endl;

    // Check for kinetic term diagonalisation...
    std::string isnorm;
    command = "CheckDiagonalKineticTerms[" + LTot + "]";
    send_to_math(command);

    get_from_math(isnorm);
    if (isnorm != "True")
    {
        std::stringstream ss;
        ss << "Your Lagrangian has kinetic terms that are not correctly diagonalised!" << std::endl;
        ss << "Please check your FeynRules file and the FeynRules manual." << std::endl;
        throw std::runtime_error(ss.str());
    }

    std::cout << "Kinetic terms are diagonal... ";
    std::cout.flush();

    // Check for mass term diagonalisation...
    command = "CheckDiagonalMassTerms[" + LTot + "]";
    send_to_math(command);

    get_from_math(isnorm);
    if (isnorm != "True")
    {
        std::stringstream ss;
        ss << "Your Lagrangian has mass terms that are not correctly diagonalised!" << std::endl;
        ss << "Please check your FeynRules file and the FeynRules manual." << std::endl;
        throw std::runtime_error(ss.str());
    }

    std::cout << "Mass terms are diagonal... ";
    std::cout.flush();

    // Kinetic term normalisation. 
    // We ignore the SM neutrinos because they don't have a kinetic term under the SM.
    command = "CheckKineticTermNormalisation[" + LTot + ", Free -> {ve,vm,vt}] == Null // ToString";
    send_to_math(command);

    get_from_math(isnorm);
    if (isnorm == "True")
    {
        std::stringstream ss;
        ss << "Your Lagrangian is not correctly normalised!" << std::endl;
        ss << "Please check your FeynRules file and the FeynRules manual." << std::endl;
        throw std::runtime_error(ss.str());
    }

    std::cout << "All good." << std::endl;

  }

  // Gets the 'PartList' -- this contains all particles in the model.
  void FeynRules::get_partlist(std::vector<Particle> &partlist)
  {

    std::cout << "Extracting particles from FeynRules model." << std::endl;

    // Command to get a list of lists of lists of lists(!) with particle info.
    std::string command = "pl = PartList;";
    send_to_math(command);

    // Find out how many particles we have to get.
    command = "Length[pl]";
    send_to_math(command);

    std::stringstream ss;

    int lenpl;
    get_from_math(lenpl);
    std::cout << "Found " << lenpl << " particle sets." << std::endl;

    // Get to parsing this monster.
    for (int i=0; i<lenpl; i++)
    {

        // First things first, check to see if we are dealing with multiplets.
        // e.g., l = (e, mu, tau).
        int numelements;
        command = "Length[pl[[" + std::to_string(i+1) + ",2]]]";
        send_to_math(command);
        get_from_math(numelements);

        for (int j=0; j<numelements; j++)
        {

            // Initialise all properties we wish to find out about a particle.
            std::string name;
            std::string antiname;
            std::string spin;
            std::string fullname;
            std::string eaten;
            std::string mass;
            // Needs to initialise these to suppress compiler warnings.
            int color = 1;
            int chargeX3 = 0;
            int spinX2 = 0;   
            int pdg;
            bool SM;

            // Firstly, find the name
            command = "pl[[" + std::to_string(i+1) + ",2," + std::to_string(j+1) + ",1]]";
            send_to_math(command);
            get_from_math(name);

            // Then, the antiparticle name
            command = "pl[[" + std::to_string(i+1) + ",2," + std::to_string(j+1) + ",2]]";
            send_to_math(command);
            get_from_math(antiname);

            // Next, find out the spin.
            command = "pl[[" + std::to_string(i+1) + ",2," + std::to_string(j+1) + ",3]]";
            send_to_math(command);
            get_from_math(spin);
            if (spin == "V")
            {
                spinX2 = 2;
            }
            else if (spin == "F")
            {
                spinX2 = 1;
            }
            else if (spin == "S")
            {
                spinX2 = 0;
            }
            else if (spin == "T")
            {
                spinX2 = 4;
            }
            // Don't try and parse ghosts; it'll give us an error. We also
            // don't care about them from a pheno (GUM) standpoint.
            else if (spin == "U")
            {
                continue;
            }

            // PDG code.
            command = "pl[[" + std::to_string(i+1) + ",2," + std::to_string(j+1) + ",9]]";
            send_to_math(command);
            get_from_math(pdg);

            // "Full name"
            command = "pl[[" + std::to_string(i+1) + ",2," + std::to_string(j+1) + ",10]]";
            send_to_math(command);
            get_from_math(fullname);

            // Name of the mass parameter.
            command = "pl[[" + std::to_string(i+1) + ",2," + std::to_string(j+1) + ",5]]";
            send_to_math(command);
            get_from_math(mass);

            // Check it doesn't get eaten - this isn't a physical particle.
            command = "pl[[" + std::to_string(i+1) + ",2," + std::to_string(j+1) + ",13]]";
            send_to_math(command);
            get_from_math(eaten);
            if (eaten != "NoGS")
            {
                continue;
            }

            // Color representation
            command = "pl[[" + std::to_string(i+1) + ",2," + std::to_string(j+1) + ",7]]";
            send_to_math(command);

            std::string colorstr;
            get_from_math(colorstr);
            if (colorstr == "S")
            {
                color = 1;
            }
            else if (colorstr == "T")
            {
                color = 3;
            }
            else if (colorstr == "O")
            {
                color = 8;
            }

            // Charge

            // Firsly, need to get the name of the Class in FeynRules (in case there's
            // multiple entries -- they will all have the same QNUMBERS.)
            std::string classname;
            command = "pl[[" + std::to_string(i+1) + ",1,2]]";
            send_to_math(command);
            get_from_math(classname);
            
            // Now see if there is a charge entry
            float charge = 0.;

            command = "N[Q[" + classname + "]]";
            send_to_math(command);
            get_from_math(charge);

            chargeX3 = int(round(charge * 3));

            // If we've got this far, our particle is physical.
            // One last thing... check if it's a SM particle or not.
            std::set<int> SM_pdgs = {1, 2, 3, 4, 5, 6, 11, 12, 13, 14, 15, 16, 21, 22, 23, 24};
            if (SM_pdgs.count(abs(pdg)))
            {
                SM = true;
            }
            else
            {
                SM = false;
            }

            // Add the particle to the list.
            Particle particle(pdg, std::string(name), spinX2, chargeX3, color, SM, mass, std::string(antiname), std::string(fullname));
            partlist.push_back(particle);
        }

     }

  }

  // Gets the 'ParamList' -- this contains all particles in the model.
  void FeynRules::get_paramlist(std::vector<Parameter> &paramlist)
  {
    std::cout << "Extracting external parameters from FeynRules model." << std::endl;

    std::string command = "epl = EParamList;";
    send_to_math(command);

    // Find out how many parameters we have to get.
    command = "Length[epl]";
    send_to_math(command);

    std::stringstream ss;

    int lenepl;
    get_from_math(lenepl);

    std::cout << "Found " << lenepl << " parameter blocks." << std::endl;

    std::string block;

    for (int i=0; i<lenepl; i++)
    {
        command = "epl[[" + std::to_string(i+1) + ",1]]";
        send_to_math(command);
        get_from_math(block);

        // First things first, check how many elements are in each block.
        // e.g., SMINPUTS = (aEWM1, Gf, alphaS).
        int numelements;
        command = "Length[epl[[" + std::to_string(i+1) + ",2]]]";
        send_to_math(command);
        get_from_math(numelements);

        for (int j=0; j<numelements; j++)
        {

            std::string paramname;

            command = "epl[[" + std::to_string(i+1) + ",2," + std::to_string(j+1) + ",2,1]]";
            send_to_math(command);
            get_from_math(paramname);

            Parameter parameter(paramname, block, int(j+1));
            paramlist.push_back(parameter);
        }
    }
  }

  // Set the gauge -- accepts either 'feynman' or 'unitary'
  void FeynRules::set_gauge(std::string gauge)
  {
    if ((gauge != "feynman") && (gauge != "unitary"))
    {
        std::stringstream ss;
        ss << "set_gauge() called with an incorrect option, "
                  << gauge << ".\n Allowed options: 'feynman' or 'unitary'."
                  << std::endl;
        throw std::runtime_error(ss.str());
    }
    std::string command;
    if (gauge == "feynman")
    {
        command = "FeynmanGauge = True;";
        std::cout << "Setting Feynman Gauge." << std::endl;
    }
    else if (gauge == "unitary")
    {
        command = "FeynmanGauge = False;";
        std::cout << "Setting Unitary Gauge." << std::endl;
    }
    send_to_math(command);
  }

  // Write CalcHEP output.
  void FeynRules::write_ch_output(std::string LTot)
  {
    std::cout << "Writing CalcHEP output." << std::endl;

    // CalcHEP is faster in Feynman Gauge.
    std::string gauge = "feynman";
    set_gauge(gauge);

    // Check to see if FR catches any 4-fermion vertices.
    bool fourF = false;
    int nfourF = 0;

    // Redirect output to catch them after writing CH files
    send_to_math("streams = AppendTo[$Output, OpenWrite[]];");

    // Write output.
    std::string command = "WriteCHOutput[" + LTot + ", CHAutoWidths -> False];";
    send_to_math(command);

    // Close the output stream and restore to stdout
    command = "Close@Last@streams; $Output = Most@streams; output = ReadList@First@Last@streams;";
    send_to_math(command);

    // Process the output to find out if there are any 4-fermion interactions.
    int noutput;
    send_to_math("Length[output]");
    get_from_math(noutput);

    for(int i=1; i<=noutput; i++)
    {
      std::string output;
      send_to_math("ToString[output[[" + std::to_string(i) + "]]]");
      get_from_math(output);

      // If we find a 4-fermion vertex, take a note of it
      size_t pos = output.find("4 fermion");
      if(pos != std::string::npos)
      {
        fourF = true;
        nfourF++;
      }
    }

    // 4-fermion vertices result in a fatal error in GUM v1.
    if(fourF)
    {
      std::stringstream ss;
      ss << "GUM caught " + std::to_string(nfourF) + " 4-fermion vertices in your Lagrangian." << std::endl;
      ss << "This is a fatal error in the current release of GUM." << std::endl;
      ss << "Dealing with 4-fermion vertices is planned for future releases." << std::endl;
      throw std::runtime_error(ss.str());
    }
    std::cout << "CalcHEP files written." << std::endl;

  }

  // Write MadGraph output.
  void FeynRules::write_mg_output(std::string LTot)
  {
    std::cout << "Writing MadGraph (UFO) output for Pythia/MadDM." << std::endl;

    // Write output.
    std::string command = "WriteUFO[" + LTot + "];";
    send_to_math(command);

    std::cout << "MadGraph files written." << std::endl;
  }

  // Performs all FeynRules output.
  void all_feynrules(Options opts, std::vector<Particle> &partlist, std::vector<Parameter> &paramlist, 
                     Outputs &outputs, std::vector<std::string> &backends, Error &error)
  {
    try
    {
      std::cout << "Calling FeynRules with model " << opts.model() << "..." << std::endl;

      // Create FeynRules object, open link to Mathematica, load Feynrules and the model
      FeynRules model(opts.model(), opts.base_model());

      // Load restrictions - if there are any.
      if (not opts.restriction().empty())
      {
        // Split the list of restrictions
        std::stringstream RST(opts.restriction());
        std::string rst;
        while (getline(RST,rst,','))
        {
          model.load_restriction(opts.model(), opts.base_model(), rst);
        }
      }

      // Check the Lagrangian seems to exist.
      model.check_lagrangian(opts.lagrangian());

      // Diagnositics -- check it is hermitian
      model.check_herm(opts.lagrangian());

      // Get all of the particles
      model.get_partlist(partlist);

      // And all parameters
      model.get_paramlist(paramlist);

      // Get the "actual" model name
      std::string fr_model_name = model.get_modelname();

      // Output directory
      std::string output = std::string(FEYNRULES_PATH) + "/" + fr_model_name;

      /// Write CalcHEP output
      if (std::find(backends.begin(), backends.end(), "calchep") != backends.end() ||
          std::find(backends.begin(), backends.end(), "micromegas") != backends.end() )
      {
        model.write_ch_output(opts.lagrangian());

        // Location of CalcHEP files
        std::string chdir = output + "-CH";
        std::replace(chdir.begin(), chdir.end(), ' ', '-');
        outputs.set_ch(chdir);
      }

      /// Same for MadGraph->Pythia
      if (std::find(backends.begin(), backends.end(), "pythia") != backends.end() ||
          std::find(backends.begin(), backends.end(), "ufo") != backends.end() )
      {
        model.write_mg_output(opts.lagrangian());

        // Location of MadGraph (UFO) files
        std::string mgdir = output + "_UFO";
        std::replace(mgdir.begin(), mgdir.end(), ' ', '_');
        outputs.set_mg(mgdir);
      }
    }
    catch(std::exception &e)
    {
      error.raise("FeynRules Error: " + std::string(e.what()));
    }
  }

} // namespace GUM

// Now all the grizzly stuff, so Python can call C++ (which can call Mathematica...)
BOOST_PYTHON_MODULE(libfr)
{
  using namespace boost::python;

  class_<Particle>("FRParticle", init<int, std::string, int, int, int, bool, std::string, std::string, std::string>())
    .def("pdg",      &Particle::pdg)
    .def("name",     &Particle::name)
    .def("SM",       &Particle::SM)
    .def("spinX2",   &Particle::spinX2)
    .def("chargeX3", &Particle::chargeX3)
    .def("color",    &Particle::color)
    .def("mass",     &Particle::mass)
    .def("SC",       &Particle::SC)
    .def("antiname", &Particle::antiname)
    ;

  class_<Parameter>("FRParameter", init<std::string, std::string, int>())
    .def("name",  &Parameter::name)
    .def("block", &Parameter::block)
    .def("index", &Parameter::index)
    ;

  class_<Options>("FROptions", init<std::string, std::string, std::string, std::string, std::string>())
    .def("package",     &Options::package)
    .def("model",       &Options::model)
    .def("base_model",  &Options::base_model)
    .def("restriction", &Options::restriction)
    .def("lagrangian",  &Options::lagrangian)
    ;

  class_<Outputs>("FROutputs", init<>())
    .def("get_ch",  &Outputs::get_ch)
    .def("get_mg",  &Outputs::get_mg)
    .def("set_ch",  &Outputs::set_ch)
    .def("set_mg",  &Outputs::set_mg)
    ;

  class_<Error>("FRError", init<>())
    .def("is_error", &Error::is_error)
    .def("what", &Error::what)
    ;

  class_< std::vector<Particle> >("FRVectorOfParticles")
    .def(vector_indexing_suite< std::vector<Particle> >() )
    ;

  class_< std::vector<Parameter> >("FRVectorOfParameters")
    .def(vector_indexing_suite< std::vector<Parameter> >() )
    ;

  class_< std::vector<std::string> >("FRBackends")
    .def(vector_indexing_suite< std::vector<std::string> >() )
    ;


  def("all_feynrules", GUM::all_feynrules);

}
