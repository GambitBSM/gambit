#ifndef __boss__classes_ExampleBackend_1_234_hpp__
#define __boss__classes_ExampleBackend_1_234_hpp__

#ifndef __classes_hpp__
#define __classes_hpp__

#include <iostream>
#include <vector>
#include <ctime>
#include <map> 



#include "backend_types/ExampleBackend_1_234/abstract_ClassThree.hpp"
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"
template <typename T>         
class ClassThree : public virtual Abstract_ClassThree<T> {
public:
  T pop();
  void push(T item);
  int size();

private:
  std::vector<T> stack;
  int curr_size;

  public:
    Abstract_ClassThree* pointer_copy__BOSS();

    using Abstract_ClassThree::pointer_assign__BOSS;
    void pointer_assign__BOSS(Abstract_ClassThree* in);


};

// Instantiate a <double> specialization of ClassThree:
#include "backend_types/ExampleBackend_1_234/abstract_Dummy.hpp"
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"
class Dummy : public virtual Abstract_Dummy {
  ClassThree<double> var;

  public:
    Abstract_Dummy* pointer_copy__BOSS();

    using Abstract_Dummy::pointer_assign__BOSS;
    void pointer_assign__BOSS(Abstract_Dummy* in);


};

#endif
#endif /* __boss__classes_ExampleBackend_1_234_hpp__ */
