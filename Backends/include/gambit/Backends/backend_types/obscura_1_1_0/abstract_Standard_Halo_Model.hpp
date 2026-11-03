#ifndef __abstract_Standard_Halo_Model_obscura_1_1_0_hpp__
#define __abstract_Standard_Halo_Model_obscura_1_1_0_hpp__

#include <cstddef>
#include <iostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_DM_Distribution_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace obscura
    {
        class Abstract_Standard_Halo_Model : virtual public obscura::Abstract_DM_Distribution
        {
            public:
    
                virtual void Set_Speed_Dispersion(double) =0;
    
                virtual void Set_Escape_Velocity(double) =0;
    
                virtual void Set_Observer_Velocity(int, int, int, int, int) =0;
    
                virtual void Set_Observer_Velocity__BOSS(int, int, int, int) =0;
    
                virtual void Set_Observer_Velocity__BOSS(int, int, int) =0;
    
                virtual double PDF_Speed(double) =0;
    
                virtual double CDF_Speed(double) =0;
    
                virtual double Eta_Function(double) =0;
    
                virtual void Print_Summary(int) =0;
    
                virtual void Print_Summary__BOSS() =0;
    
            public:
                using obscura::Abstract_DM_Distribution::pointer_assign__BOSS;
                virtual void pointer_assign__BOSS(Abstract_Standard_Halo_Model*) =0;
                virtual Abstract_Standard_Halo_Model* pointer_copy__BOSS() =0;
    
            private:
                Standard_Halo_Model* wptr;
                bool delete_wrapper;
            public:
                Standard_Halo_Model* get_wptr() { return wptr; }
                void set_wptr(Standard_Halo_Model* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Standard_Halo_Model()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Standard_Halo_Model(const Abstract_Standard_Halo_Model& in) : 
                    obscura::Abstract_DM_Distribution(in)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Standard_Halo_Model& operator=(const Abstract_Standard_Halo_Model&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Standard_Halo_Model* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Standard_Halo_Model& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Standard_Halo_Model() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Standard_Halo_Model_obscura_1_1_0_hpp__ */
