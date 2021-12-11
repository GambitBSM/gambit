#include <dlfcn.h>
#include <string>
#include <iostream>


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
