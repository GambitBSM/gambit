#ifndef __abstract_DM_Distribution_obscura_1_1_0_hpp__
#define __abstract_DM_Distribution_obscura_1_1_0_hpp__

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace obscura
    {
        class Abstract_DM_Distribution : public virtual AbstractBase
        {
            public:
    
                virtual double& DM_density_ref__BOSS() =0;
    
                virtual bool& DD_use_eta_function_ref__BOSS() =0;
    
                virtual double Minimum_DM_Speed() const =0;
    
                virtual double Maximum_DM_Speed() const =0;
    
                virtual double PDF_Speed(double) =0;
    
                virtual double CDF_Speed(double) =0;
    
                virtual double PDF_Norm() =0;
    
                virtual double Differential_DM_Flux(double, double) =0;
    
                virtual double Total_DM_Flux(double) =0;
    
                virtual double Average_Speed(double) =0;
    
                virtual double Average_Speed__BOSS() =0;
    
                virtual double Eta_Function(double) =0;
    
                virtual void Print_Summary(int) =0;
    
                virtual void Print_Summary__BOSS() =0;
    
                virtual void Export_PDF_Speed(std::string, int, bool) =0;
    
                virtual void Export_PDF_Speed__BOSS(std::string, int) =0;
    
                virtual void Export_PDF_Speed__BOSS(std::string) =0;
    
                virtual void Export_Eta_Function(std::string, int, bool) =0;
    
                virtual void Export_Eta_Function__BOSS(std::string, int) =0;
    
                virtual void Export_Eta_Function__BOSS(std::string) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_DM_Distribution*) =0;
                virtual Abstract_DM_Distribution* pointer_copy__BOSS() =0;
    
            private:
                DM_Distribution* wptr;
                bool delete_wrapper;
            public:
                DM_Distribution* get_wptr() { return wptr; }
                void set_wptr(DM_Distribution* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_DM_Distribution()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_DM_Distribution(const Abstract_DM_Distribution&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_DM_Distribution& operator=(const Abstract_DM_Distribution&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                DM_Distribution* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                DM_Distribution& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_DM_Distribution() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_DM_Distribution_obscura_1_1_0_hpp__ */
