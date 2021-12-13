#include <dlfcn.h>
#include <string>
#include <iostream>


// Dummy definitions of some GAMBIT macros that the BOSSed code expects should exist
#define ALREADY_LOADED(BE) 0
#define SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BACKENDNAME, SAFE_VERSION, DEFAULT)  This code will never be generated when ALREADY_LOADED is 0

// Include the BOSS-generated headers
#include "gambit/Backends/backend_types/ExampleBackend_1_234/loaded_types.hpp"


// Main program
int main()
{

  // Path to shared lib
  const std::string path = "../ExampleBackend/libexamplebackend.so";

  // Try loading it with dlopen
  std::cout << "Trying to load library at " << path << std::endl;
  void* pHandle = dlopen(path.c_str(), RTLD_LAZY);

  // Did it work?
  if (pHandle)
  {
    std::cout << "All good so far! pHandle = " << pHandle << " should now be pointing to " << path << std::endl;
  }
  else
  {
    std::string error_msg = dlerror();
    std::cout << "No good. dlerror() says: " << error_msg << std::endl; 
  }

  return 0;
}
