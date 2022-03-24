#include "gambit/Backends/BOSS_wrapperutils.hpp"

template<typename T>
Wrapper_ClassThree<T>* wrapper_creator(Abstract_ClassThree<T>* abs_ptr)
{
  return new Wrapper_ClassThree<T>(abs_ptr);
}

template<typename T>
void wrapper_deleter(Wrapper_ClassThree<T>* wptr)
{
  wptr->set_delete_BEptr(false);
  delete wptr;
}

template<typename T>
void set_delete_BEptr(Wrapper_ClassThree<T>* wptr, bool setting)
{
  wptr->set_delete_BEptr(setting);
}

Wrapper_ClassFour* wrapper_creator(Abstract_ClassFour* abs_ptr)
{
  return new Wrapper_ClassFour(abs_ptr);
}

void wrapper_deleter(Wrapper_ClassFour* wptr)
{
  wptr->set_delete_BEptr(false);
  delete wptr;
}

void set_delete_BEptr(Wrapper_ClassFour* wptr, bool setting)
{
  wptr->set_delete_BEptr(setting);
