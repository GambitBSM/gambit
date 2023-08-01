#ifndef __abstract_EPhysicalProblem_gm2calc_1_3_0_hpp__
#define __abstract_EPhysicalProblem_gm2calc_1_3_0_hpp__

#include <cstddef>
#include <iostream>
#include <string>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_Error_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   namespace gm2calc
   {
      class Abstract_EPhysicalProblem : virtual public gm2calc::Abstract_Error
      {
         public:
   
            virtual ::std::string what() const =0;
   
         public:
            using gm2calc::Abstract_Error::pointer_assign__BOSS;
            virtual void pointer_assign__BOSS(Abstract_EPhysicalProblem*) =0;
            virtual Abstract_EPhysicalProblem* pointer_copy__BOSS() =0;
   
         private:
            EPhysicalProblem* wptr;
            bool delete_wrapper;
         public:
            EPhysicalProblem* get_wptr() { return wptr; }
            void set_wptr(EPhysicalProblem* wptr_in) { wptr = wptr_in; }
            bool get_delete_wrapper() { return delete_wrapper; }
            void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
   
         public:
            Abstract_EPhysicalProblem()
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_EPhysicalProblem(const Abstract_EPhysicalProblem& in) : 
               gm2calc::Abstract_Error(in)
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_EPhysicalProblem& operator=(const Abstract_EPhysicalProblem&) { return *this; }
   
            virtual void init_wrapper() =0;
   
            EPhysicalProblem* get_init_wptr()
            {
               init_wrapper();
               return wptr;
            }
   
            EPhysicalProblem& get_init_wref()
            {
               init_wrapper();
               return *wptr;
            }
   
            virtual ~Abstract_EPhysicalProblem() =0;
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_EPhysicalProblem_gm2calc_1_3_0_hpp__ */
