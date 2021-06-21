//   GUM: GAMBIT Universal Model Machine
//   ************************************
///  \file
///
///  Definitions of mother class for
///  Mathematica packages.
///
///  **********************************
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
//   \date 2019 July, Aug
///
///  ***********************************


#include <iostream>
#include <fstream>

#include "math_package.hpp"

namespace GUM
{

  // Constructor, set the model and start the link
  Math_Package::Math_Package(std::string modelname)
  {
    // Set the model name
    name = modelname;

    // Establish WSTP link
    create_wstp_link();

  }

  // Destructor, close the link
  Math_Package::~Math_Package()
  {
    close_wstp_link();
  }
    
  // Set model name
  void Math_Package::set_name(std::string modelname)
  {
    name = modelname;
  }
   
  // Create the link to WSTP
  void Math_Package::create_wstp_link()
  {
    int WSerrno;
    WSENV WSenv = WSInitialize(0);
      
    if(WSenv == (WSENV)0)
    {
      std::cout << "Unable to initialize WSTP environment" << std::endl;
    }
    else
    {
      std::cout << "The environment is initialized successfully..." << std::endl;
    }
      
    std::stringstream WSTPflags;
      
    // This opens a WSTP connection
    WSTPflags << "-linkname " << MATHEMATICA_KERNEL << " -mathlink";
      
    link = (WSLINK)WSOpenString(WSenv, WSTPflags.str().c_str(), &WSerrno);
      
    if(link == (WSLINK)0 || WSerrno != WSEOK)
    {
      std::cout << "Unable to create link to the Kernel!" << std::endl;
      std::cout << "Something went wrong with the Mathematica Kernel, make sure you have a working Mathematica installation." << std::endl;
      WSNewPacket(link);
      throw std::runtime_error("WSTP Error: Unable to create link to Kernel");
    }
    else
    {
      std::cout << "WSTP link started" << std::endl;
    }
  }
    
  // Close link to WSTP
  void Math_Package::close_wstp_link()
  {
    std::string command = "Quit[];";
    send_to_math(command);
    WSClose(link);
    std::cout << "WSTP link closed successfully." << std::endl;
  }
    
  // Wait to receive a packet from the kernel
  void Math_Package::wait_for_packet()
  {
    int pkt;
    while( (pkt = WSNextPacket(link), pkt) && pkt != RETURNPKT)
    {
      WSNewPacket(link);
      if (WSError(link))
      {
        std::cout << "Error reading packet from WSTP" << std::endl;
      }
    }
  }
    
  // Send a string to be evaluated in Mathematica via WSTP
  void Math_Package::send_to_math(std::string input)
  {
    WSNewPacket(link);
    WSPutFunction(link, "ToExpression", 1);
    WSPutString(link, input.c_str());

    wait_for_packet();
    input = "";
  }

  // Get a character variable from Mathematica via WSTP
  void Math_Package::get_from_math(char &val)
  {
    const char *val2;
    if(!WSGetString(link, &val2))
      throw std::runtime_error("WSTP Error: Failed to retrieve a character");
    val = val2[0];
  }

  // Get a string variable from Mathematica via WSTP
  void Math_Package::get_from_math(std::string &val)
  {
    const char *val2;
    if(!WSGetString(link, &val2))
      throw std::runtime_error("WSTP Error: Failed to retrieve a string");
    val = std::string(val2);
  }

  // Get an integer variable from Mathematica via WSTP
  void Math_Package::get_from_math(int &val)
  {
    if(!WSGetInteger(link, &val))
      throw std::runtime_error("WSTP Error: Failed to retrieve an integer");
  }
  
  // Get a float variable from Mathematica via WSTP
  void Math_Package::get_from_math(float &val)
  {
    if(!WSGetReal32(link, &val))
      throw std::runtime_error("WSTP Error: Failed to retrieve a float");
  }

  // Get a double variable from Mathematica via WSTP
  void Math_Package::get_from_math(double &val)
  {
    if(!WSGetReal64(link, &val))
      throw std::runtime_error("WSTP Error: Failed to retrieve a double");
  }

  // Get a bool variable from Mathematica via WSTP
  void Math_Package::get_from_math(bool &val)
  {
    const char *val2;
    if(!WSGetString(link, &val2))
      throw std::runtime_error("WSTP Error: Failed to retrieve a bool");
    val = (std::string(val2) == "True");
  }

  // Load package
  void Math_Package::load_package()
  {
     // Dummy, overload
  }

  // Load model
  void Math_Package::load_model(std::string)
  {
     // Dummy, overload
  }

  // Model checks
  void Math_Package::check_model()
  {
     // Dummy, overload
  }

  // Get model name
  std::string Math_Package::get_modelname()
  {
    return name;  
  }

  void Math_Package::get_partlist(std::vector<Particle>&)
  {
    // Dummy, overload
  }

  // Parameters list
  void Math_Package::get_paramlist(std::vector<Parameter>&)
  {
    // Dummy, overload
  }

  // Flags (boolean only)
  void Math_Package::get_flags(std::map<std::string, bool>& flags)
  {   
    try
    {
      for (auto it = flags.begin(); it != flags.end(); it++)
      {
        std::string flag_label = it->first;
        send_to_math(flag_label);
        get_from_math(it->second);
      }
    }
    catch (...) { throw; }
      
  }

} // namespace GUM
