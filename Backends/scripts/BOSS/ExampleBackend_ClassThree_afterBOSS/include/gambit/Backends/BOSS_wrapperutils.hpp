#ifndef __BOSS_wrapperutils_ExampleBackend_1_234_hpp__
#define __BOSS_wrapperutils_ExampleBackend_1_234_hpp__

#include "backend_types/ExampleBackend_1_234/wrapper_ClassThree.hpp"
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"

template<typename T>
Wrapper_ClassThree<T>* wrapper_creator(Abstract_ClassThree<T>*);

template<typename T>
void wrapper_deleter(Wrapper_ClassThree<T>*);

template<typename T>
void set_delete_BEptr(Wrapper_ClassThree<T>*, bool);

#endif /* __BOSS_wrapperutils_ExampleBackend_1_234_hpp__ */
