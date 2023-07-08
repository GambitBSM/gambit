#ifndef __wrapper_LHdecayTable_decl_Pythia_8_212_h__
#define __wrapper_LHdecayTable_decl_Pythia_8_212_h__

#include <cstddef>
#include <vector>
#include <string>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_LHdecayTable.h"
#include "wrapper_LHdecayChannel_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class LHdecayTable : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_LHdecayTable* (*__factory0)();
                static Abstract_LHdecayTable* (*__factory1)(int);
                static Abstract_LHdecayTable* (*__factory2)(int, double);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                int getId();
        
                double getWidth();
        
                void setId(int idIn);
        
                void setWidth(double widthIn);
        
                void reset(double widthIn);
        
                void reset();
        
                void addChannel(Pythia8::LHdecayChannel channelIn);
        
                void addChannel(double bratIn, int nDaIn, std::vector<int> idDaIn, std::string cIn);
        
                void addChannel(double bratIn, int nDaIn, std::vector<int> idDaIn);
        
                int size();
        
                double getBrat(int iChannel);
        
                ::std::vector<int> getIdDa(int iChannel);
        
                Pythia8::LHdecayChannel getChannel(int iChannel);
        
        
                // Wrappers for original constructors: 
            public:
                LHdecayTable();
                LHdecayTable(int idIn);
                LHdecayTable(int idIn, double widthIn);
        
                // Special pointer-based constructor: 
                LHdecayTable(Abstract_LHdecayTable* in);
        
                // Copy constructor: 
                LHdecayTable(const LHdecayTable& in);
        
                // Assignment operator: 
                LHdecayTable& operator=(const LHdecayTable& in);
        
                // Destructor: 
                ~LHdecayTable();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_LHdecayTable* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_LHdecayTable_decl_Pythia_8_212_h__ */
