#include <iostream>
#include "classes.hpp"




template <typename T>
T ClassThree<T>::pop()
{
  T top = stack.back();
  stack.pop_back();
  return top;
}


template <typename T>
void ClassThree<T>::push(T item)
{
  stack.push_back(item);
}


template <typename T>
int ClassThree<T>::size()
{
  return stack.size();
}

double ClassFour::pop()
{
  double top = stack.back();
  stack.pop_back();
  return top;
}


void ClassFour::push(double item)
{
  stack.push_back(item);
}


int ClassFour::size()
{
  return stack.size();
}
