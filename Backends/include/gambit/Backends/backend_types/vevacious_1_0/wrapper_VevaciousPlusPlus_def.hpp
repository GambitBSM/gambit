#ifndef __wrapper_VevaciousPlusPlus_def_vevacious_1_0_hpp__
#define __wrapper_VevaciousPlusPlus_def_vevacious_1_0_hpp__

#include <string>
#include <utility>
#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace VevaciousPlusPlus
    {
        
        // Member functions: 
        inline void VevaciousPlusPlus::RunPoint(const std::string& newInput)
        {
            get_BEptr()->RunPoint(newInput);
        }
        
        inline ::std::pair<std::vector<double>, std::vector<double>> VevaciousPlusPlus::GetPanicVacua()
        {
            return get_BEptr()->GetPanicVacua();
        }
        
        inline ::std::pair<std::vector<double>, std::vector<double>> VevaciousPlusPlus::RunVacua(const std::string& newInput)
        {
            return get_BEptr()->RunVacua(newInput);
        }
        
        inline void VevaciousPlusPlus::ReadLhaBlock(const std::string& uppercaseBlockName, const double scale, const std::vector<std::pair<int, double>>& parameters, const int dimension)
        {
            get_BEptr()->ReadLhaBlock(uppercaseBlockName, scale, parameters, dimension);
        }
        
        inline void VevaciousPlusPlus::WriteResultsAsXmlFile(const std::string& xmlFilename)
        {
            get_BEptr()->WriteResultsAsXmlFile(xmlFilename);
        }
        
        inline ::std::string VevaciousPlusPlus::GetResultsAsString()
        {
            return get_BEptr()->GetResultsAsString();
        }
        
        inline double VevaciousPlusPlus::GetLifetimeInSeconds()
        {
            return get_BEptr()->GetLifetimeInSeconds();
        }
        
        inline double VevaciousPlusPlus::GetThermalProbability()
        {
            return get_BEptr()->GetThermalProbability();
        }
        
        inline double VevaciousPlusPlus::GetThermalDecayWidth()
        {
            return get_BEptr()->GetThermalDecayWidth();
        }
        
        inline ::std::vector<double> VevaciousPlusPlus::GetThresholdAndActions()
        {
            return get_BEptr()->GetThresholdAndActions();
        }
        
        inline ::std::vector<double> VevaciousPlusPlus::GetThermalThresholdAndActions()
        {
            return get_BEptr()->GetThermalThresholdAndActions();
        }
        
        inline void VevaciousPlusPlus::AppendResultsToLhaFile(const std::string& lhaFilename, const bool writeWarnings)
        {
            get_BEptr()->AppendResultsToLhaFile(lhaFilename, writeWarnings);
        }
        
        inline void VevaciousPlusPlus::AppendResultsToLhaFile(const std::string& lhaFilename)
        {
            get_BEptr()->AppendResultsToLhaFile__BOSS(lhaFilename);
        }
        
        
        // Wrappers for original constructors: 
        inline VevaciousPlusPlus::VevaciousPlusPlus(const std::string& initializationFileName) :
            WrapperBase(__factory0(initializationFileName))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline VevaciousPlusPlus::VevaciousPlusPlus(Abstract_VevaciousPlusPlus* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Destructor: 
        inline VevaciousPlusPlus::~VevaciousPlusPlus()
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
        inline Abstract_VevaciousPlusPlus* VevaciousPlusPlus::VevaciousPlusPlus::get_BEptr() const
        {
            return dynamic_cast<Abstract_VevaciousPlusPlus*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_VevaciousPlusPlus_def_vevacious_1_0_hpp__ */
