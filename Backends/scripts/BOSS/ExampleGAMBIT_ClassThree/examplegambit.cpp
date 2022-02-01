#include <dlfcn.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
// #include "../ExampleBackend/include/classes.hpp"

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


// A small helper function that returns a voidptr_voidfptr to a library symbol,
// given a library pointer and symbol name as input
voidptr_voidfptr get_vptr(void* phandle, std::string library_symbol)
{
  voidptr_voidfptr psym;

  std::cout << "get_vptr: Trying to connect to the library symbol " << library_symbol << std::endl;
  psym.ptr = dlsym(phandle, library_symbol.c_str());

  if (psym.ptr)
  {
    std::cout << "get_vptr: All good. The returned pointer " << psym.ptr << " should point to the library symbol " << library_symbol << std::endl;
  }
  else
  {
    std::cout << "get_vptr: No good. Got a NULL pointer." << std::endl; 
    RUNTIME_ERROR
  }

  return psym;
}


  void foo(int Z) {
    for (int i = 0; i < Z; i++) {
        std::cout << "Thread using function"
               " pointer as callable\n";
    }
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
  }

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
  const std::string path = "../ExampleBackend_ClassThree_afterBOSS/libexamplebackend.so";

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


  // Steps 1) and 2) are taken care of by the helper function get_vptr
  voidptr_voidfptr psym = get_vptr(phandle, "Factory_ClassThree_0_double__BOSS_1");

  // 3) Recast to a function pointer "fptr" of type Abstract_ClassThree<double>*(*)()
  Abstract_ClassThree<double>*(*factory_fptr)();
  factory_fptr = reinterpret_cast< Abstract_ClassThree<double>*(*)() >(psym.fptr);

  // 4) Call the factory function and receive the returned pointer as a Abstract_ClassOne*.
  Abstract_ClassThree<double>* myptr = factory_fptr();
  std::cout << "myptr = " << myptr << " should now point to a ClassThree<double> instance. Let's try to use it..." << std::endl;

  std::cout << "myptr->size(): " << myptr->size() << std::endl;
  std::cout << "Adding 1.0, 2.0 and 3.0 using myptr->push(...)" << std::endl;
  myptr->push(1.);
  myptr->push(2.);
  myptr->push(3.);
  std::cout << "myptr->size(): " << myptr->size() << std::endl;
  
  std::cout << "myptr->pop(): " << myptr->pop() << std::endl;
  std::cout << "myptr->pop(): " << myptr->pop() << std::endl;
  std::cout << "myptr->pop(): " << myptr->pop() << std::endl;

  // All done
  return 0;

}

