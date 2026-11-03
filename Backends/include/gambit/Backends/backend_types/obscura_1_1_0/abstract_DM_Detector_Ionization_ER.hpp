#ifndef __abstract_DM_Detector_Ionization_ER_obscura_1_1_0_hpp__
#define __abstract_DM_Detector_Ionization_ER_obscura_1_1_0_hpp__

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_DM_Particle_decl.hpp"
#include "wrapper_DM_Distribution_decl.hpp"
#include "wrapper_DM_Detector_Ionization_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace obscura
    {
        class Abstract_DM_Detector_Ionization_ER : virtual public obscura::Abstract_DM_Detector_Ionization
        {
            public:
    
            public:
                using obscura::Abstract_DM_Detector_Ionization::pointer_assign__BOSS;
                virtual void pointer_assign__BOSS(Abstract_DM_Detector_Ionization_ER*) =0;
                virtual Abstract_DM_Detector_Ionization_ER* pointer_copy__BOSS() =0;
    
            private:
                DM_Detector_Ionization_ER* wptr;
                bool delete_wrapper;
            public:
                DM_Detector_Ionization_ER* get_wptr() { return wptr; }
                void set_wptr(DM_Detector_Ionization_ER* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_DM_Detector_Ionization_ER()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_DM_Detector_Ionization_ER(const Abstract_DM_Detector_Ionization_ER& in) : 
                    obscura::Abstract_DM_Detector(in), obscura::Abstract_DM_Detector_Ionization(in)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_DM_Detector_Ionization_ER& operator=(const Abstract_DM_Detector_Ionization_ER&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                DM_Detector_Ionization_ER* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                DM_Detector_Ionization_ER& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_DM_Detector_Ionization_ER() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_DM_Detector_Ionization_ER_obscura_1_1_0_hpp__ */
