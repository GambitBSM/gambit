#ifndef __wrapper_VevaciousPlusPlus_decl_vevacious_1_0_hpp__
#define __wrapper_VevaciousPlusPlus_decl_vevacious_1_0_hpp__

#include <cstddef>
#include <string>
#include <utility>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_VevaciousPlusPlus.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace VevaciousPlusPlus
    {
        
        class VevaciousPlusPlus : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_VevaciousPlusPlus* (*__factory0)(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >&);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void RunPoint(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& newInput);
        
                ::std::pair<std::vector<double, std::allocator<double> >, std::vector<double, std::allocator<double> > > GetPanicVacua();
        
                ::std::pair<std::vector<double, std::allocator<double> >, std::vector<double, std::allocator<double> > > RunVacua(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& newInput);
        
                void ReadLhaBlock(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& uppercaseBlockName, const double scale, const ::std::vector<std::pair<int, double>, std::allocator<std::pair<int, double> > >& parameters, const int dimension);
        
                void WriteResultsAsXmlFile(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& xmlFilename);
        
                ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > GetResultsAsString();
        
                double GetLifetimeInSeconds();
        
                double GetThermalProbability();
        
                double GetThermalDecayWidth();
        
                ::std::vector<double, std::allocator<double> > GetThresholdAndActions();
        
                ::std::vector<double, std::allocator<double> > GetThermalThresholdAndActions();
        
                void AppendResultsToLhaFile(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& lhaFilename, const bool writeWarnings);
        
                void AppendResultsToLhaFile(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& lhaFilename);
        
        
                // Wrappers for original constructors: 
            public:
                VevaciousPlusPlus(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& initializationFileName);
        
                // Special pointer-based constructor: 
                VevaciousPlusPlus(Abstract_VevaciousPlusPlus* in);
        
                // Destructor: 
                ~VevaciousPlusPlus();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_VevaciousPlusPlus* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_VevaciousPlusPlus_decl_vevacious_1_0_hpp__ */
