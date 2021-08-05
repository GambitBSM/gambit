#ifndef __wrapper_DecayTableTHDM_decl_THDMC_1_8_0_h__
#define __wrapper_DecayTableTHDM_decl_THDMC_1_8_0_h__

#include <cstddef>
#include <complex>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_DecayTableTHDM.h"
#include "wrapper_THDM_decl.h"
#include "wrapper_SM_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    class DecayTableTHDM : public WrapperBase
    {
            // Member variables: 
        public:
            // -- Static factory pointers: 
            static Abstract_DecayTableTHDM* (*__factory0)(THDM*);
    
            // -- Other member variables: 
    
            // Member functions: 
        public:
            void set_model(THDM* model);
    
            THDM* get_model();
    
            double get_gamma_huu(int h, int u1, int u2);
    
            double get_gamma_hdd(int h, int d1, int d2);
    
            double get_gamma_hll(int h, int l1, int l2);
    
            double get_gamma_hdu(int h, int d, int u);
    
            double get_gamma_hln(int h, int l, int n);
    
            double get_gamma_hhh(int h, int h1, int h2);
    
            double get_gamma_hvv(int h, int v);
    
            double get_gamma_hvh(int H, int V, int h);
    
            double get_gamma_hgg(int h);
    
            double get_gamma_hgaga(int h);
    
            double get_gamma_hZga(int h);
    
            double get_gammatot_h(int h);
    
            double get_gammatot_v(int v);
    
            double get_gammatot_top();
    
            double get_gamma_uhd(int u, int h, int d);
    
            double get_gamma_uhd_flipped(int u, int h, int d);
    
            double get_gamma_uhu(int u1, int h, int u2);
    
            double get_gamma_uhu_flipped(int u1, int h, int u2);
    
            void print_decays(int h);
    
            void print_width(int h);
    
            void print_top_decays();
    
            void set_qcd(bool set);
    
            double DHp(double ui, double uj, double xi, double xj, double sqL);
    
            double DHm(double ui, double uj, double xi, double xj, double sqL);
    
            double BHp(double ui, double uj, double xi, double xj, double sqL);
    
    
            // Wrappers for original constructors: 
        public:
            DecayTableTHDM(THDM* mod);
    
            // Special pointer-based constructor: 
            DecayTableTHDM(Abstract_DecayTableTHDM* in);
    
            // Copy constructor: 
            DecayTableTHDM(const DecayTableTHDM& in);
    
            // Assignment operator: 
            DecayTableTHDM& operator=(const DecayTableTHDM& in);
    
            // Destructor: 
            ~DecayTableTHDM();
    
            // Returns correctly casted pointer to Abstract class: 
            Abstract_DecayTableTHDM* get_BEptr() const;
    
    };
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DecayTableTHDM_decl_THDMC_1_8_0_h__ */
