#ifndef __boss__classes_ExampleBackend_1_234_hpp__
#define __boss__classes_ExampleBackend_1_234_hpp__

#ifndef __classes_hpp__
#define __classes_hpp__

#include <iostream>
#include <vector>
#include <ctime>
#include <map>
typedef int* int2;
typedef int2** int3;
typedef int3& int4;
typedef int4&& int5;
typedef int Data;

#include "backend_types/ExampleBackend_1_234/abstract_Node.hpp"
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"
struct Node : public virtual Abstract_Node {
    Data d;
    struct Node* next;

  public:
    Abstract_Node* pointer_copy__BOSS();

    using Abstract_Node::pointer_assign__BOSS;
    void pointer_assign__BOSS(Abstract_Node* in);

  public:
    int& d_ref__BOSS();



};

typedef struct Node* List_2;


// A dummy class
#include "backend_types/ExampleBackend_1_234/abstract_ClassOne.hpp"
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"
class ClassOne : public virtual Abstract_ClassOne
{

public:

  int i;
  int& i_2 = i;
  double d;
  long int li;
  long li_1;
  unsigned long li_2;
  std::map<int, std::vector<unsigned long int>> testing_Var;
  
  // Decalring it as a member variable
//   std::vector<clock_t> my_vec_clock;
  
  // Constructor
  ClassOne() {}

  // Some method, defined in classes.cpp
  void some_method(int);

  // Some other method, defined right here
  void some_other_method(int i_in)
  {
    std::cout << "ClassOne::some_other_method: arg 1: i_in = " << i_in << std::endl;
  }

  // Testing methods which returns a clock instead
  clock_t return_clock_t();

  // Testing methods that return vectors

  std::vector<int> return_as_vector_with_int();

  std::vector<clock_t> return_as_vector_with_clock();


  public:
    Abstract_ClassOne* pointer_copy__BOSS();


  public:
    int& i_ref__BOSS();

    int& i_2_ref__BOSS();

    double& d_ref__BOSS();

    long int& li_ref__BOSS();

    long int& li_1_ref__BOSS();

    long unsigned int& li_2_ref__BOSS();



};



namespace SomeNamespace
{

  // Another dummy class
  } 
  #include "backend_types/ExampleBackend_1_234/abstract_ClassTwo.hpp"
  #include "gambit/Backends/abstracttypedefs.hpp"
  #include "gambit/Backends/wrappertypedefs.hpp"
  namespace SomeNamespace { 
  class ClassTwo : public virtual Abstract_ClassTwo
  {
  public:
    int j;
  
    public:
      Abstract_ClassTwo* pointer_copy__BOSS();

      using Abstract_ClassTwo::pointer_assign__BOSS;
      void pointer_assign__BOSS(Abstract_ClassTwo* in);

    public:
      int& j_ref__BOSS();



};

}


#endif
#endif /* __boss__classes_ExampleBackend_1_234_hpp__ */
