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

template <typename T>
bool ClassThree<T>::equal(T item1, T item2)
{
  return item1 == item2;
}

template <typename T>
ClassThree<T> ClassThree<T>::operator+(ClassThree<T> & other)
{
  ClassThree<T> result;
  for(int i=0; i<curr_size; ++i)
    result.push(pop() + other.pop());

  return result;
}

// Instantiate a <double> specialization of ClassThree:
template class ClassThree<double>;




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

ClassFour ClassFour::operator+(ClassFour &other)
{
  ClassFour result;
  for(int i=0; i<curr_size; ++i)
    result.push(pop() + other.pop());

  return result;
}


ClassFour ClassFive<ClassFour>::pop()
{
  ClassFour top = stack.back();
  stack.pop_back();
  return top;
}


void ClassFive<ClassFour>::push(ClassFour item)
{
  stack.push_back(item);
}


int ClassFive<ClassFour>::size()
{
  return stack.size();
}
