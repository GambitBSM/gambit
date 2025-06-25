#ifndef __wrapper_Standard_Halo_Model_def_obscura_1_1_0_hpp__
#define __wrapper_Standard_Halo_Model_def_obscura_1_1_0_hpp__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        // Member functions: 
        inline void Standard_Halo_Model::Set_Speed_Dispersion(double v0)
        {
            get_BEptr()->Set_Speed_Dispersion(v0);
        }
        
        inline void Standard_Halo_Model::Set_Escape_Velocity(double vesc)
        {
            get_BEptr()->Set_Escape_Velocity(vesc);
        }
        
        inline void Standard_Halo_Model::Set_Observer_Velocity(int day, int month, int year, int hour, int minute)
        {
            get_BEptr()->Set_Observer_Velocity(day, month, year, hour, minute);
        }
        
        inline void Standard_Halo_Model::Set_Observer_Velocity(int day, int month, int year, int hour)
        {
            get_BEptr()->Set_Observer_Velocity__BOSS(day, month, year, hour);
        }
        
        inline void Standard_Halo_Model::Set_Observer_Velocity(int day, int month, int year)
        {
            get_BEptr()->Set_Observer_Velocity__BOSS(day, month, year);
        }
        
        inline double Standard_Halo_Model::PDF_Speed(double v)
        {
            return get_BEptr()->PDF_Speed(v);
        }
        
        inline double Standard_Halo_Model::CDF_Speed(double v)
        {
            return get_BEptr()->CDF_Speed(v);
        }
        
        inline double Standard_Halo_Model::Eta_Function(double vMin)
        {
            return get_BEptr()->Eta_Function(vMin);
        }
        
        inline void Standard_Halo_Model::Print_Summary(int mpi_rank)
        {
            get_BEptr()->Print_Summary(mpi_rank);
        }
        
        inline void Standard_Halo_Model::Print_Summary()
        {
            get_BEptr()->Print_Summary__BOSS();
        }
        
        
        // Wrappers for original constructors: 
        inline Standard_Halo_Model::Standard_Halo_Model() :
            DM_Distribution(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Standard_Halo_Model::Standard_Halo_Model(double rho, double v0, double vobs, double vesc) :
            DM_Distribution(__factory1(rho, v0, vobs, vesc))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Standard_Halo_Model::Standard_Halo_Model(double rho, double v0, double vobs) :
            DM_Distribution(__factory2(rho, v0, vobs))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Standard_Halo_Model::Standard_Halo_Model(Abstract_Standard_Halo_Model* in) :
            DM_Distribution(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Standard_Halo_Model::Standard_Halo_Model(const Standard_Halo_Model& in) :
            DM_Distribution(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Standard_Halo_Model& Standard_Halo_Model::operator=(const Standard_Halo_Model& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Standard_Halo_Model::~Standard_Halo_Model()
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
        inline Abstract_Standard_Halo_Model* obscura::Standard_Halo_Model::get_BEptr() const
        {
            return dynamic_cast<Abstract_Standard_Halo_Model*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Standard_Halo_Model_def_obscura_1_1_0_hpp__ */
