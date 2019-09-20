#ifndef __wrapper_Event_decl_Pythia_EM_8_212_h__
#define __wrapper_Event_decl_Pythia_EM_8_212_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Event.h"
#include <string>
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Particle_decl.h"
#include "wrapper_Vec4_decl.h"
#include <ostream>
#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class Event : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Pythia8::Abstract_Event* (*__factory0)(int);
                static Pythia8::Abstract_Event* (*__factory1)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void init(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > headerIn, Pythia8::ParticleData* particleDataPtrIn, int startColTagIn);
        
                void init(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > headerIn, Pythia8::ParticleData* particleDataPtrIn);
        
                void init(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > headerIn);
        
                void init();
        
                void clear();
        
                void reset();
        
                Pythia8::Particle& operator[](int i);
        
                const Pythia8::Particle& operator[](int i) const;
        
                Pythia8::Particle& front();
        
                Pythia8::Particle& at(int i);
        
                Pythia8::Particle& back();
        
                int size() const;
        
                int append(Pythia8::Particle entryIn);
        
                int append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, double px, double py, double pz, double e, double m, double scaleIn, double polIn);
        
                int append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, double px, double py, double pz, double e, double m, double scaleIn);
        
                int append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, double px, double py, double pz, double e, double m);
        
                int append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, double px, double py, double pz, double e);
        
                int append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, Pythia8::Vec4 p, double m, double scaleIn, double polIn);
        
                int append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, Pythia8::Vec4 p, double m, double scaleIn);
        
                int append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, Pythia8::Vec4 p, double m);
        
                int append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, Pythia8::Vec4 p);
        
                int append(int id, int status, int col, int acol, double px, double py, double pz, double e, double m, double scaleIn, double polIn);
        
                int append(int id, int status, int col, int acol, double px, double py, double pz, double e, double m, double scaleIn);
        
                int append(int id, int status, int col, int acol, double px, double py, double pz, double e, double m);
        
                int append(int id, int status, int col, int acol, double px, double py, double pz, double e);
        
                int append(int id, int status, int col, int acol, Pythia8::Vec4 p, double m, double scaleIn, double polIn);
        
                int append(int id, int status, int col, int acol, Pythia8::Vec4 p, double m, double scaleIn);
        
                int append(int id, int status, int col, int acol, Pythia8::Vec4 p, double m);
        
                int append(int id, int status, int col, int acol, Pythia8::Vec4 p);
        
                void setEvtPtr(int iSet);
        
                void setEvtPtr();
        
                int copy(int iCopy, int newStatus);
        
                int copy(int iCopy);
        
                void list(int precision) const;
        
                void list() const;
        
                void list(::std::basic_ostream<char, std::char_traits<char> >& os, int precision) const;
        
                void list(::std::basic_ostream<char, std::char_traits<char> >& os) const;
        
                void list(bool showScaleAndVertex, bool showMothersAndDaughters, int precision) const;
        
                void list(bool showScaleAndVertex, bool showMothersAndDaughters) const;
        
                void list(bool showScaleAndVertex) const;
        
                void list(bool showScaleAndVertex, bool showMothersAndDaughters, ::std::basic_ostream<char, std::char_traits<char> >& os, int precision) const;
        
                void list(bool showScaleAndVertex, bool showMothersAndDaughters, ::std::basic_ostream<char, std::char_traits<char> >& os) const;
        
                void popBack(int nRemove);
        
                void popBack();
        
                void remove(int iFirst, int iLast);
        
                void restorePtrs();
        
                void saveSize();
        
                void restoreSize();
        
                int savedSizeValue();
        
                void initColTag(int colTag);
        
                void initColTag();
        
                int lastColTag() const;
        
                int nextColTag();
        
                void scale(double scaleIn);
        
                double scale() const;
        
                void scaleSecond(double scaleSecondIn);
        
                double scaleSecond() const;
        
                ::std::vector<int, std::allocator<int> > daughterList(int i) const;
        
                void rot(double theta, double phi);
        
                void bst(double betaX, double betaY, double betaZ);
        
                void bst(double betaX, double betaY, double betaZ, double gamma);
        
                void bst(const Pythia8::Vec4& vec);
        
                void clearJunctions();
        
                int appendJunction(int kind, int col0, int col1, int col2);
        
                int sizeJunction() const;
        
                bool remainsJunction(int i) const;
        
                void remainsJunction(int i, bool remainsIn);
        
                int kindJunction(int i) const;
        
                int colJunction(int i, int j) const;
        
                void colJunction(int i, int j, int colIn);
        
                int endColJunction(int i, int j) const;
        
                void endColJunction(int i, int j, int endColIn);
        
                int statusJunction(int i, int j) const;
        
                void statusJunction(int i, int j, int statusIn);
        
                void eraseJunction(int i);
        
                void saveJunctionSize();
        
                void restoreJunctionSize();
        
                void listJunctions(::std::basic_ostream<char, std::char_traits<char> >& os) const;
        
                void listJunctions() const;
        
                void savePartonLevelSize();
        
                Pythia8::Event& operator+=(const Pythia8::Event& addEvent);
        
        
                // Wrappers for original constructors: 
            public:
                Event(int capacity);
                Event();
        
                // Special pointer-based constructor: 
                Event(Pythia8::Abstract_Event* in);
        
                // Copy constructor: 
                Event(const Event& in);
        
                // Assignment operator: 
                Event& operator=(const Event& in);
        
                // Destructor: 
                ~Event();
        
                // Returns correctly casted pointer to Abstract class: 
                Pythia8::Abstract_Event* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Event_decl_Pythia_EM_8_212_h__ */
