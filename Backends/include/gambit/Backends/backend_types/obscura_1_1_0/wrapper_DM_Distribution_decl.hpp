#ifndef __wrapper_DM_Distribution_decl_obscura_1_1_0_hpp__
#define __wrapper_DM_Distribution_decl_obscura_1_1_0_hpp__

#include <cstddef>
#include <string>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_DM_Distribution.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        class DM_Distribution : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_DM_Distribution* (*__factory0)();
                static Abstract_DM_Distribution* (*__factory1)(std::string, double, double, double);
        
                // -- Other member variables: 
            public:
                double& DM_density;
                bool& DD_use_eta_function;
        
                // Member functions: 
            public:
                double Minimum_DM_Speed() const;
        
                double Maximum_DM_Speed() const;
        
                double PDF_Speed(double v);
        
                double CDF_Speed(double v);
        
                double PDF_Norm();
        
                double Differential_DM_Flux(double v, double mDM);
        
                double Total_DM_Flux(double mDM);
        
                double Average_Speed(double vMin);
        
                double Average_Speed();
        
                double Eta_Function(double vMin);
        
                void Print_Summary(int mpi_rank);
        
                void Print_Summary();
        
                void Export_PDF_Speed(std::string file_path, int v_points, bool log_scale);
        
                void Export_PDF_Speed(std::string file_path, int v_points);
        
                void Export_PDF_Speed(std::string file_path);
        
                void Export_Eta_Function(std::string file_path, int v_points, bool log_scale);
        
                void Export_Eta_Function(std::string file_path, int v_points);
        
                void Export_Eta_Function(std::string file_path);
        
        
                // Wrappers for original constructors: 
            public:
                DM_Distribution();
                DM_Distribution(std::string label, double rhoDM, double vMin, double vMax);
        
                // Special pointer-based constructor: 
                DM_Distribution(Abstract_DM_Distribution* in);
        
                // Copy constructor: 
                DM_Distribution(const DM_Distribution& in);
        
                // Assignment operator: 
                DM_Distribution& operator=(const DM_Distribution& in);
        
                // Destructor: 
                ~DM_Distribution();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_DM_Distribution* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Distribution_decl_obscura_1_1_0_hpp__ */
