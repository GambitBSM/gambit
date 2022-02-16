#ifndef __classes_hpp__
#define __classes_hpp__

#include <iostream>
#include <vector>
#include <ctime>
#include <map> 



template <typename T>         
class ClassThree {
public:
  T pop();
  void push(T item);
  int size();
  T var;
  T min(T,T,T);
  ClassThree(T second): var{second} {}
  ClassThree(int first): curr_size{first} {}


private:
  std::vector<T> stack;
  int curr_size;
};


// Instantiate a <double> specialization of ClassThree:
class Dummy {
  ClassThree<double> var;
};

#endif