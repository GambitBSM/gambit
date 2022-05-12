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

  ClassThree<T> operator+(ClassThree<T>& other);

  T test;

private:
  std::vector<T> stack;
  int curr_size;
};

static ClassThree<double> __BOSS_dummy_ClassThree_double_instance__;
static ClassThree<int> _BOSS_dummy_ClassThree_int_instance__;


class ClassFour {
public:
  double pop();
  void push(double item);
  int size();

  ClassFour operator+(ClassFour& other);

private:
  std::vector<double> stack;
  int curr_size;
};

static ClassThree<ClassFour> _BOSS_dummy_ClassThree_ClassFour_instance__;


template <typename T>
class ClassFive;

template<>
class ClassFive<ClassFour>
{
public:
  ClassFour pop();
  void push(ClassFour item);
  int size();

private:
  std::vector<ClassFour> stack;
  int curr_size;

};


class ClassSix : public ClassFive<ClassFour>
{
public:
  int pop2();
  void push2(int item);
  int size2();

private:
  std::vector<int> stack2;
  int curr_size2;
};


template <typename T>
class ClassSeven : public ClassThree<T>
{
public:
  T pop2();
  void push2(T item);
  int size2();
  void get_stack(std::vector<ClassFour>&);

private:
  std::vector<T> stack2;
  int curr_size2;
  std::vector<ClassFour> stack3;
};

static ClassSeven<double> __BOSS_dummy_ClassSeven_double_instance__;
static ClassSeven<int> __BOSS_dummy_ClassSeven_int_instance__;

#endif
