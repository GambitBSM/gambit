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



int ClassSix::pop2()
{
  int top = stack2.back();
  stack2.pop_back();
  return top;
}


void ClassSix::push2(int item)
{
  stack2.push_back(item);
}


int ClassSix::size2()
{
  return stack2.size();
}



template <typename T>
T ClassSeven<T>::pop2()
{
  T top = stack2.back();
  stack2.pop_back();
  return top;
}


template <typename T>
void ClassSeven<T>::push2(T item)
{
  stack2.push_back(item);
}


template <typename T>
int ClassSeven<T>::size2()
{
  return stack2.size();
}


