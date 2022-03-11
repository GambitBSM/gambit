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

private:
  std::vector<T> stack;
  int curr_size;
};



#endif