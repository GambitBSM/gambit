#ifndef __wrapper_DM_Distribution_def_obscura_1_1_0_hpp__
#define __wrapper_DM_Distribution_def_obscura_1_1_0_hpp__

#include <string>
#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        // Member functions: 
        inline double DM_Distribution::Minimum_DM_Speed() const
        {
            return get_BEptr()->Minimum_DM_Speed();
        }
        
        inline double DM_Distribution::Maximum_DM_Speed() const
        {
            return get_BEptr()->Maximum_DM_Speed();
        }
        
        inline double DM_Distribution::PDF_Speed(double v)
        {
            return get_BEptr()->PDF_Speed(v);
        }
        
        inline double DM_Distribution::CDF_Speed(double v)
        {
            return get_BEptr()->CDF_Speed(v);
        }
        
        inline double DM_Distribution::PDF_Norm()
        {
            return get_BEptr()->PDF_Norm();
        }
        
        inline double DM_Distribution::Differential_DM_Flux(double v, double mDM)
        {
            return get_BEptr()->Differential_DM_Flux(v, mDM);
        }
        
        inline double DM_Distribution::Total_DM_Flux(double mDM)
        {
            return get_BEptr()->Total_DM_Flux(mDM);
        }
        
        inline double DM_Distribution::Average_Speed(double vMin)
        {
            return get_BEptr()->Average_Speed(vMin);
        }
        
        inline double DM_Distribution::Average_Speed()
        {
            return get_BEptr()->Average_Speed__BOSS();
        }
        
        inline double DM_Distribution::Eta_Function(double vMin)
        {
            return get_BEptr()->Eta_Function(vMin);
        }
        
        inline void DM_Distribution::Print_Summary(int mpi_rank)
        {
            get_BEptr()->Print_Summary(mpi_rank);
        }
        
        inline void DM_Distribution::Print_Summary()
        {
            get_BEptr()->Print_Summary__BOSS();
        }
        
        inline void DM_Distribution::Export_PDF_Speed(std::string file_path, int v_points, bool log_scale)
        {
            get_BEptr()->Export_PDF_Speed(file_path, v_points, log_scale);
        }
        
        inline void DM_Distribution::Export_PDF_Speed(std::string file_path, int v_points)
        {
            get_BEptr()->Export_PDF_Speed__BOSS(file_path, v_points);
        }
        
        inline void DM_Distribution::Export_PDF_Speed(std::string file_path)
        {
            get_BEptr()->Export_PDF_Speed__BOSS(file_path);
        }
        
        inline void DM_Distribution::Export_Eta_Function(std::string file_path, int v_points, bool log_scale)
        {
            get_BEptr()->Export_Eta_Function(file_path, v_points, log_scale);
        }
        
        inline void DM_Distribution::Export_Eta_Function(std::string file_path, int v_points)
        {
            get_BEptr()->Export_Eta_Function__BOSS(file_path, v_points);
        }
        
        inline void DM_Distribution::Export_Eta_Function(std::string file_path)
        {
            get_BEptr()->Export_Eta_Function__BOSS(file_path);
        }
        
        
        // Wrappers for original constructors: 
        inline DM_Distribution::DM_Distribution() :
            WrapperBase(__factory0()),
            DM_density( get_BEptr()->DM_density_ref__BOSS()),
            DD_use_eta_function( get_BEptr()->DD_use_eta_function_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Distribution::DM_Distribution(std::string label, double rhoDM, double vMin, double vMax) :
            WrapperBase(__factory1(label, rhoDM, vMin, vMax)),
            DM_density( get_BEptr()->DM_density_ref__BOSS()),
            DD_use_eta_function( get_BEptr()->DD_use_eta_function_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline DM_Distribution::DM_Distribution(Abstract_DM_Distribution* in) :
            WrapperBase(in),
            DM_density( get_BEptr()->DM_density_ref__BOSS()),
            DD_use_eta_function( get_BEptr()->DD_use_eta_function_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline DM_Distribution::DM_Distribution(const DM_Distribution& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
            DM_density( get_BEptr()->DM_density_ref__BOSS()),
            DD_use_eta_function( get_BEptr()->DD_use_eta_function_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline DM_Distribution& DM_Distribution::operator=(const DM_Distribution& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline DM_Distribution::~DM_Distribution()
        {
            if (get_BEptr() != 0)
            {
                get_BEptr()->set_delete_wrapper(false);
                if (can_delete_BEptr())
                {
                    delete BEptr;
                    BEptr = 0;
                }
            }
            set_delete_BEptr(false);
        }
        
        // Returns correctly casted pointer to Abstract class: 
        inline Abstract_DM_Distribution* obscura::DM_Distribution::get_BEptr() const
        {
            return dynamic_cast<Abstract_DM_Distribution*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Distribution_def_obscura_1_1_0_hpp__ */
