#ifndef __BOSS_wrapperutils_ExampleBackend_1_234_hpp__
#define __BOSS_wrapperutils_ExampleBackend_1_234_hpp__

#include "backend_types/ExampleBackend_1_234/wrapper_ClassTwo.hpp"
#include "backend_types/ExampleBackend_1_234/wrapper_ClassOne.hpp"
#include "backend_types/ExampleBackend_1_234/wrapper_Node.hpp"
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"

Wrapper_Node* wrapper_creator(Abstract_Node*);

void wrapper_deleter(Wrapper_Node*);

void set_delete_BEptr(Wrapper_Node*, bool);

Wrapper_ClassOne* wrapper_creator(Abstract_ClassOne*);

void wrapper_deleter(Wrapper_ClassOne*);

void set_delete_BEptr(Wrapper_ClassOne*, bool);

SomeNamespace::Wrapper_ClassTwo* wrapper_creator(SomeNamespace::Abstract_ClassTwo*);

void wrapper_deleter(SomeNamespace::Wrapper_ClassTwo*);

void set_delete_BEptr(SomeNamespace::Wrapper_ClassTwo*, bool);

#endif /* __BOSS_wrapperutils_ExampleBackend_1_234_hpp__ */
