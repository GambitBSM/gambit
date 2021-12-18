#include <dlfcn.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>


// 
// Various useful definitions
// 

// A simple macro for throwing a runtime_error with the line number
#define RUNTIME_ERROR throw std::runtime_error(std::string("Error thrown on line ") + std::to_string(__LINE__));

// Dummy definitions of some GAMBIT macros that the BOSSed code expects should exist
#define ALREADY_LOADED(BE) 0
#define SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BACKENDNAME, SAFE_VERSION, DEFAULT)  This code will never be generated when ALREADY_LOADED is 0

// Hack to suppress warnings about casting between void pointers and function pointers.
// "Necessary" as long as dlsym has no separate functionality for retrieving function pointers.
union voidptr_voidfptr
{
  void *ptr;      // Use this for objects
  void(*fptr)();  // Use this for functions
};



//
// Include the BOSS-generated headers
//

#include "gambit/Backends/backend_types/ExampleBackend_1_234/loaded_types.hpp"

// Let's simplfy things a bit
using namespace ExampleBackend_1_234;


// 
// Main program
// 

int main()
{

  // 
  // First we need to load the shared library using dlopen
  // 

  // Path to shared lib
  const std::string path = "../ExampleBackend/libexamplebackend.so";

  // Try loading it with dlopen
  std::cout << "Trying to load library at " << path << std::endl;
  void* phandle = dlopen(path.c_str(), RTLD_LAZY);

  // Did it work?
  if (phandle)
  {
    std::cout << "All good. phandle = " << phandle << " should now be pointing to " << path << std::endl;
  }
  else
  {
    std::string error_msg = dlerror();
    std::cout << "No good. dlerror() says: " << error_msg << std::endl; 
    RUNTIME_ERROR
  }


  // 
  // Now let's do some runtime classloading "by hand". What we need to do is
  // 
  //   1. Create a void pointer / void function pointer "psym"
  // 
  //   2. Use our phandle and the function dlsym to connect psym to the symbol "Factory_ClassOne_0__BOSS_1" 
  //      in libexamplebackend.so using dlsym. 
  // 
  //      Factory_ClassOne_0__BOSS_1 is the factory function that BOSS has generated in ../ExampleBackend/src/BOSS_factory_ClassOne.cpp.
  //      This function creates a new instance of the original ClassOne, and returns its pointer as a base class (Abstract_ClassOne) pointer. 
  // 
  //   3. Recast the function pointer to a function pointer of type Abstract_ClassOne*(*)()
  // 
  //   4. Call the factory function and receive the returned pointer as a Abstract_ClassOne*.
  // 
  // When we now call the methods of Abstract_ClassOne on this pointer, we are in fact calling
  // the correponding methods of the underlying (original) ClassOne instance.
  // 
  // (We can't access the member variables directly yet. For that we'll need to expand this example to use the "wrapper class".)
  // 


  // 1) Create a void (function) pointer
  voidptr_voidfptr psym;

  // 2) Connect it to the correct library symbol
  const std::string library_symbol = "Factory_ClassOne_0__BOSS_1";

  std::cout << "Trying to connect to the library symbol " << library_symbol << std::endl;

  psym.ptr = dlsym(phandle, library_symbol.c_str());

  if (psym.ptr)
  {
    std::cout << "All good. psym.ptr = " << psym.ptr << " is should now point to the library symbol " << library_symbol << std::endl;
  }
  else
  {
    std::cout << "No good. psym.ptr is NULL." << std::endl; 
    RUNTIME_ERROR
  }

  // 3) Recast to a function pointer "fptr" of type Abstract_ClassOne*(*)()
  Abstract_ClassOne*(*factory_fptr)();
  factory_fptr = reinterpret_cast< Abstract_ClassOne*(*)() >(psym.fptr);


  // 4) Call the factory function and receive the returned pointer as a Abstract_ClassOne*.
  Abstract_ClassOne* myptr = factory_fptr();
  std::cout << "myptr = " << myptr << " should now point to a OneClass instance. Let's try to use it..." << std::endl;


  myptr->some_method(10);
  myptr->some_other_method(20);

  return 0;
}

