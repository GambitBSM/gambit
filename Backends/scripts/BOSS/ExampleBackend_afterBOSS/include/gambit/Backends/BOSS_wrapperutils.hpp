#ifndef __BOSS_wrapperutils_ExampleBackend_1_234_hpp__
#define __BOSS_wrapperutils_ExampleBackend_1_234_hpp__

#include "backend_types/ExampleBackend_1_234/wrapper_ClassFive.hpp"
#include "backend_types/ExampleBackend_1_234/wrapper_ClassFour.hpp"
#include "backend_types/ExampleBackend_1_234/wrapper_ClassThree.hpp"
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"

template<typename T>
Wrapper_ClassThree<T>* wrapper_creator(Abstract_ClassThree<T>*);

template<typename T>
void wrapper_deleter(Wrapper_ClassThree<T>*);

template<typename T>
void set_delete_BEptr(Wrapper_ClassThree<T>*, bool);

Wrapper_ClassFour* wrapper_creator(Abstract_ClassFour*);

void wrapper_deleter(Wrapper_ClassFour*);

void set_delete_BEptr(Wrapper_ClassFour*, bool);

template <typename T1>
Wrapper_ClassFive<T1>* wrapper_creator(Abstract_ClassFive<T1>*);

template <typename T1>
void wrapper_deleter(Wrapper_ClassFive<T1>*);

template <typename T1>
void set_delete_BEptr(Wrapper_ClassFive<T1>*, bool);

#endif /* __BOSS_wrapperutils_ExampleBackend_1_234_hpp__ */
