//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  'Safety bucket' class definitions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///   \date 2013 Apr, Nov
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///   \date 2014 Mar, Sep
///   \date 2022 May
///
///  *********************************************

#ifndef __safety_bucket_hpp__
#define __safety_bucket_hpp__

#include <iostream>
#include <omp.h>

#include "gambit/Elements/functors.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"


namespace Gambit
{

  /// Base class for the interface classes 'dep_bucket', 'BEvariable_bucket' and 'BEfunction_bucket'.
  class safety_bucket_base
  {

    public:

      /// Master constructor
      safety_bucket_base(str myinfo) : whoami(myinfo) {}

      /// Ask whether the bucket has been initialised with a valid pointer or not,
      /// i.e. has the dependency resolver activated this dependency / backend req?
      bool active()
      {
        return _initialized;
      }

      /// Get capability name.
      str name()
      {
        if (not _initialized) dieGracefully();
        return _functor_base_ptr->name();
      }

      /// Get name of origin (module/backend).
      str origin()
      {
        if (not _initialized) dieGracefully();
        return _functor_base_ptr->origin();
      }


    protected:

      functor * _functor_base_ptr;

      bool _initialized;

      const str whoami;

      /// Failure message invoked when the user tries to access the object before it is initialized.
      void dieGracefully() const
      {
        str errmsg = "You just just tried to access the dependency or backend requirement\n"
                     + whoami + "\n"
                     "Unfortunately this does not yet point to anything, because the dependency\n"
                     "or backend requirement has not been satistified yet.  If using GAMBIT in \n"
                     "full, please check your rollcall declaration of this module function, and\n"
                     "its source code.  This error often occurs because you have written \n"
                     "  using namespace Pipes::x \n"
                     "where x is not actually the function being executed.  Don't steal pipes!!\n\n"
                     "Alternatively, if you are writing a standalone executable using some  \n"
                     "GAMBIT modules, please check that you have correctly filled this dep/req.";
        utils_error().raise(LOCAL_INFO,errmsg);
      }
  };



  /// An interface class for module dependencies.
  template <typename TYPE>
  class dep_bucket : public safety_bucket_base
  {

    public:

      /// Constructor for dep_bucket.
      dep_bucket(str mym, str myf, str me, module_functor<TYPE> * functor_ptr_in = NULL, module_functor_common* dependent_functor_ptr_in = NULL)
      : safety_bucket_base(mym+"::Pipes::"+myf+"::Dep::"+me)
      {
        initialize(functor_ptr_in, dependent_functor_ptr_in);
      }

      /// Initialize this bucket with a depedency functor pointer.
      void initialize(module_functor<TYPE> * functor_ptr_in, module_functor_common* dependent_functor_ptr_in)
      {
        _functor_ptr = functor_ptr_in;
        _functor_base_ptr = functor_ptr_in;
        _dependent_functor_ptr = dependent_functor_ptr_in;

        // Extract pointer to dependency from functor and store as a safe_ptr.
        if (functor_ptr_in == NULL)
        {
          _sptr.set(NULL);
          _initialized = false;
        }
        else
        {
          _sptr = _functor_ptr->valuePtr();
          _initialized = true;
        }
      }

      /// Get module name.
      str module()
      {
        return origin();
      }

      /// Check if the thread index needs to be used to access the functor's result
      static bool use_thread_index(module_functor<TYPE>* f1, module_functor_common* f2)
      {
        return (f1->loopManagerCapability() != "none" and
          f1->loopManagerCapability() == f2->loopManagerCapability() and
          f1->loopManagerName()       == f2->loopManagerName()       and
          f1->loopManagerOrigin()     == f2->loopManagerOrigin() );
      }

      /// Dereference the dependency pointer stored as a safe_ptr.
      const TYPE& operator *() const
      {
        if (not _initialized) dieGracefully();
        //Choose the index of the thread if the dependency and the dependent functor are running inside the same loop.  If not, just access the first element.
        int index = use_thread_index(_functor_ptr, _dependent_functor_ptr) ? omp_get_thread_num() : 0;
        return _sptr[index];
      }

      /// Access is allowed to const member functions only
      const TYPE* operator->() const
      {
        if (not _initialized) this->dieGracefully();
        //Choose the index of the thread if the dependency and the dependent functor are running inside the same loop.  If not, just choose the first element.
        int index = use_thread_index(_functor_ptr, _dependent_functor_ptr) ? omp_get_thread_num() : 0;
        return _sptr.operator->() + index;   //Call a const member function of the indexth element of the array pointed to by the safe pointer.
      }

      /// Get the safe_ptr.
      safe_ptr<TYPE>& safe_pointer()
      {
        if (not _initialized) dieGracefully();
        return _sptr;
      }


    protected:

      module_functor<TYPE> * _functor_ptr;
      safe_ptr<TYPE> _sptr;
      module_functor_common * _dependent_functor_ptr;

  };



  /// A base class for BEvariable_bucket and BEfunction_bucket.
  class BE_bucket_base : public safety_bucket_base
  {

    public:

      /// Constructor for BE_bucket_base.
      BE_bucket_base(str mym, str myf, str me)
      : safety_bucket_base(mym+"::Pipes::"+myf+"::BEreq::"+me) {}

      /// Get backend name.
      str backend()
      {
        return origin();
      }

      /// Get version information.
      str version()
      {
        if (not _initialized) dieGracefully();
        return _functor_base_ptr->version();
      }

  };


  /// An interface class for backend variables.
  template <typename TYPE>
  class BEvariable_bucket : public BE_bucket_base
  {

    protected:

      backend_functor<TYPE*(*)(),TYPE*> * _functor_ptr;
      safe_variable_ptr<TYPE> _svptr;

    public:

      /// Constructor for BEvariable_bucket.
      BEvariable_bucket(str mym, str myf, str me, backend_functor<TYPE*(*)(),TYPE*> * functor_ptr_in = NULL)
      : BE_bucket_base(mym, myf, me)
      {
        initialize(functor_ptr_in);
      }


      /// Initialize this bucket with a functor pointer.
      void initialize(backend_functor<TYPE*(*)(),TYPE*> * functor_ptr_in)
      {
        _functor_ptr      = functor_ptr_in;
        _functor_base_ptr = functor_ptr_in;

        if (functor_ptr_in == NULL)
        {
          _svptr.set(NULL);
          _initialized = false;
        }
        else
        {
          // Extract variable pointer from functor and store as a safe_variable_ptr
          _svptr.set( (*_functor_ptr)() );
          _initialized = true;
        }
      }

      /// Dereference the variable pointer stored as a safe_variable_ptr.
      TYPE& operator *()
      {
        if (not _initialized) dieGracefully();
        return *_svptr;
      }

      /// Access member functions
      TYPE* operator->()
      {
        return _svptr.operator->();
      }

      /// Get the underlying variable pointer.
      TYPE * pointer()
      {
        if (not _initialized) dieGracefully();
        return _svptr.get();
      }

      /// Get the safe_variable_ptr.
      safe_variable_ptr<TYPE>& safe_pointer()
      {
        if (not _initialized) dieGracefully();
        return _svptr;
      }

  };


  /// An interface class for backend functions.
  template <typename PTR_TYPE, typename TYPE, typename... ARGS>
  class BEfunction_bucket_common : public BE_bucket_base
  {
   public:

      /// Constructor for BEfunction_bucket_common.
      BEfunction_bucket_common(str mym, str myf, str me, backend_functor<PTR_TYPE, TYPE, ARGS...>* functor_ptr_in = NULL)
      : BE_bucket_base(mym, myf, me)
      {
        initialize(functor_ptr_in);
      }

      /// Initialize this bucket with a functor pointer.
      void initialize(backend_functor<PTR_TYPE, TYPE, ARGS...>* functor_ptr_in)
      {
        _functor_ptr      = functor_ptr_in;
        _functor_base_ptr = functor_ptr_in;

        if (functor_ptr_in == NULL)
        {
          _initialized = false;
        }
        else
        {
          _initialized = true;
        }
      }

      /// Return the underlying function pointer.
      PTR_TYPE pointer()
      {
        if (not _initialized) dieGracefully();
        return _functor_ptr->handoutFunctionPointer();
      }


    protected:

      backend_functor<PTR_TYPE, TYPE, ARGS...>* _functor_ptr;

  };


  /// The actual usable form of the interface class to backend functions
  template <typename PTR_TYPE, typename TYPE, typename... ARGS> class BEfunction_bucket;

  /// Partial specialisation for non-variadic backend functions.
  template <typename TYPE, typename... ARGS>
  class BEfunction_bucket<TYPE(*)(ARGS...),TYPE,ARGS...> : public BEfunction_bucket_common<TYPE(*)(ARGS...),TYPE,ARGS...>
  {

    public:

      /// Constructor for non-variadic BEfunction_bucket.
      BEfunction_bucket(str mym, str myf, str me, backend_functor<TYPE(*)(ARGS...), TYPE, ARGS...>* functor_ptr_in = NULL)
       : BEfunction_bucket_common<TYPE(*)(ARGS...),TYPE,ARGS...>(mym, myf, me, functor_ptr_in) {}

      /// Call backend function.
      TYPE operator ()(ARGS&& ...args)
      {
        if (not this->_initialized) this->dieGracefully();
        return (*(this->_functor_ptr))(std::forward<ARGS>(args)...);
      }

  };

  /// Partial specialisation for variadic backend functions.
  template <typename TYPE, typename... ARGS>
  class BEfunction_bucket<typename variadic_ptr<TYPE,ARGS...>::type,TYPE,ARGS...>
   : public BEfunction_bucket_common<typename variadic_ptr<TYPE,ARGS...>::type,TYPE,ARGS...>
  {

    public:

      /// Constructor for variadic BEfunction_bucket.
      BEfunction_bucket(str mym, str myf, str me, backend_functor<typename variadic_ptr<TYPE,ARGS...>::type, TYPE, ARGS...>* functor_ptr_in = NULL)
       : BEfunction_bucket_common<typename variadic_ptr<TYPE,ARGS...>::type,TYPE,ARGS...>(mym, myf, me, functor_ptr_in) {}

      /// Call backend function.
      template <typename... VARARGS>
      TYPE operator ()(VARARGS&& ...varargs)
      {
        if (not this->_initialized) this->dieGracefully();
        return (*(this->_functor_ptr))(std::forward<VARARGS>(varargs)...);
      }

  };

}

#endif // defined __safety_bucket_hpp__

