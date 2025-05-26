#ifndef __wrapper_Standard_Halo_Model_decl_obscura_1_1_0_hpp__
#define __wrapper_Standard_Halo_Model_decl_obscura_1_1_0_hpp__

#include <cstddef>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Standard_Halo_Model.hpp"
#include "wrapper_DM_Distribution_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        class Standard_Halo_Model : public DM_Distribution
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Standard_Halo_Model* (*__factory0)();
                static Abstract_Standard_Halo_Model* (*__factory1)(double, double, double, double);
                static Abstract_Standard_Halo_Model* (*__factory2)(double, double, double);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void Set_Speed_Dispersion(double v0);
        
                void Set_Escape_Velocity(double vesc);
        
                void Set_Observer_Velocity(int day, int month, int year, int hour, int minute);
        
                void Set_Observer_Velocity(int day, int month, int year, int hour);
        
                void Set_Observer_Velocity(int day, int month, int year);
        
                double PDF_Speed(double v);
        
                double CDF_Speed(double v);
        
                double Eta_Function(double vMin);
        
                void Print_Summary(int mpi_rank);
        
                void Print_Summary();
        
        
                // Wrappers for original constructors: 
            public:
                Standard_Halo_Model();
                Standard_Halo_Model(double rho, double v0, double vobs, double vesc);
                Standard_Halo_Model(double rho, double v0, double vobs);
        
                // Special pointer-based constructor: 
                Standard_Halo_Model(Abstract_Standard_Halo_Model* in);
        
                // Copy constructor: 
                Standard_Halo_Model(const Standard_Halo_Model& in);
        
                // Assignment operator: 
                Standard_Halo_Model& operator=(const Standard_Halo_Model& in);
        
                // Destructor: 
                ~Standard_Halo_Model();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Standard_Halo_Model* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Standard_Halo_Model_decl_obscura_1_1_0_hpp__ */
