#ifndef __abstract_Spectrum_generator_settings_FlexibleSUSY_CMSSM_2_4_0_h__
#define __abstract_Spectrum_generator_settings_FlexibleSUSY_CMSSM_2_4_0_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include <string>
#include <array>
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_Spectrum_generator_settings : public virtual AbstractBase
        {
            public:
    
                virtual void reset() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Spectrum_generator_settings*) =0;
                virtual Abstract_Spectrum_generator_settings* pointer_copy__BOSS() =0;
    
            private:
                Spectrum_generator_settings* wptr;
                bool delete_wrapper;
            public:
                Spectrum_generator_settings* get_wptr() { return wptr; }
                void set_wptr(Spectrum_generator_settings* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Spectrum_generator_settings()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Spectrum_generator_settings(const Abstract_Spectrum_generator_settings&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Spectrum_generator_settings& operator=(const Abstract_Spectrum_generator_settings&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Spectrum_generator_settings* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Spectrum_generator_settings& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Spectrum_generator_settings() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Spectrum_generator_settings_FlexibleSUSY_CMSSM_2_4_0_h__ */
