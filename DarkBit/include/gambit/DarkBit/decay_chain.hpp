//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Type definition and function declaration header for decay chain setup.
///
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Lars A. Dal
///          (l.a.dal@fys.uio.no)
///  \date 2014 Oct, Nov, Dec
///  \date 2015 Jan
///  *********************************************

#ifndef __decay_chain_hpp__
#define __decay_chain_hpp__

#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <boost/shared_ptr.hpp>
#include "gambit/Utils/threadsafe_rng.hpp"

namespace Gambit
{
    namespace DarkBit
    {
        struct TH_Channel;
        struct TH_ProcessCatalog;
        class SimYieldTable;
        namespace DecayChain
        {
            using std::vector;
            using std::ofstream;
            using std::ostream;
            using std::string;
            using boost::shared_ptr;
            using std::unordered_map;
            using std::set;

            //  *********************************************
            //  Generic 3-vector class
            //  *********************************************
            class vec3
            {
                public:
                    double vals[3];
                    // Constructors
                    vec3(){}
                    vec3(double v0, double v1, double v2) {vals[0]=v0;vals[1]=v1;vals[2]=v2;}
                    vec3(double v0){vals[0]=v0;vals[1]=v0;vals[2]=v0;}
                    // Get the length of the vector
                    double length() const;
                    // Normalize vector to unit length
                    void normalize();
                    // Normalize vector to length len
                    void normalize(const double len);
                    // Operators
                    double& operator[](int i){ return vals[i];}
                    double operator[](int i)const{ return vals[i];}
                    vec3 operator-()const{return vec3(-vals[0],-vals[1],-vals[2]);	}
            };
            vec3 operator* (double x, const vec3 &y);
            vec3 operator* (const vec3 &y, double x);
            vec3 operator/ (const vec3 &y, double x);
            ostream& operator<<(ostream& os, const vec3& v);
            double dot(const vec3 &a, const vec3 &b);


            //  *********************************************
            //  Generic 4-vector class
            //  *********************************************
            class vec4
            {
                public:
                    double vals[4];
                    // Constructors
                    vec4(){}
                    vec4(double v0, double v1, double v2, double v3){vals[0]=v0;vals[1]=v1;vals[2]=v2;vals[3]=v3;}
                    vec4(double v0){vals[0]=v0;vals[1]=v0;vals[2]=v0;vals[3]=v0;}
                    vec4(double v0, vec3 v){vals[0]=v0;vals[1]=v[0];vals[2]=v[1];vals[3]=v[2];}
                    // Returns vec3 containting elements 1,2,3
                    vec3 xyz() const{return vec3(vals[1],vals[2],vals[3]);}
                    // Operators
                    double& operator[](int i){ return vals[i];}
                    double operator[](int i)const{ return vals[i];}
                    vec4 operator-(){return vec4(-vals[0],-vals[1],-vals[2],-vals[3]);}
            };
            vec4 operator* (double x, const vec4 &y);
            vec4 operator* (const vec4 &y, double x);
            vec4 operator+ (const vec4 &x, const vec4 &y);
            vec4 operator- (const vec4 &x, const vec4 &y);
            ostream& operator<<(ostream& os, const vec4& v);
            double dot(const vec4 &a, const vec4 &b);
            // Construct an energy-momentum 4-vector from the given 3-momentum and mass
            vec4 Ep4vec(const vec3 p, double m);


            //  *********************************************
            //  Generic 4x4 class
            //  *********************************************
            class mat4
            {
                public:
                    double vals[4][4];
                    mat4(){};
                    mat4(   double v00, double v01, double v02, double v03,
                            double v10, double v11, double v12, double v13,
                            double v20, double v21, double v22, double v23,
                            double v30, double v31, double v32, double v33);
                    mat4(double v);
                    // Identity matrix
                    static mat4 identity();
            };
            vec4 operator* (const mat4 &m, const vec4 &v);
            mat4 operator* (const mat4 &m1, const mat4 &m2);
            ostream& operator<<(ostream& os, const mat4& m);


            //  *********************************************
            //  Utility functions
            //  *********************************************
            // Generate a random number between -1 and 1
            double rand_m1_1();
            // Generate a random number between 0 and 1
            inline double rand_0_1(){return Random::draw();}
            // Generate a 3-vector to a random point on the unit sphere
            vec3 randOnSphere();
            // Calculate Lorentz boost matrix corresponding to beta_xyz.
            // Always calculate gamma=E/m and use the second version when possible, as this is far more numerically stable.
            void lorentzMatrix(const vec3 &beta_xyz, mat4 &mat);
            void lorentzMatrix(const vec3 &beta_xyz, mat4 &mat, double gamma);
            // Boost inVec according to beta_xyz.
            vec4 lorentzBoost(const vec4 &inVec, const vec3 &beta_xyz);
            // Boost inVec to the frame where a particle at rest (in this frame) would have 4-momentum p_parent
            vec4 p_parentFrame(const vec4 &inVec, const vec4 &p_parent);
            // Get Lorentz matrix for boosting to parent frame
            void boostMatrixParentFrame(mat4 &mat, vec4 &p_parent);
            // Calculate the invariant mass of the given 4-vector pair
            double invariantMass(const vec4 &a, const vec4 &b);


            //  *********************************************
            //  Class containing all the allowed decay channels of a single particle,
            //  as well as the particle mass.
            //  Contains functonality for picking random decays according to their decay widths
            //  *********************************************
            class DecayTableEntry
            {
                friend class DecayTable;
                public:
                    // Particle mass
                    const double m;
                    // Is the particle stable in the context of the decay chain?
                    bool stable;
                    // Flags indicating whether or not the various decay states are endpoints
                    unordered_map<const TH_Channel*, bool> endpointFlags;
                    // Constructor
                    DecayTableEntry(string pID, double m, bool stable) :
                        m(m), stable(stable), enabledWidth(0),
                        totalWidth(0), invisibleWidth(0), useForcedTotalWidth(false), forcedTotalWidth(0), pID(pID), randInit(false){}
                    // Dummy constructor (for the DecayTable map)
                    DecayTableEntry() :
                        m(0), stable(false), enabledWidth(0),
                        totalWidth(0), invisibleWidth(0), useForcedTotalWidth(false), forcedTotalWidth(0), pID(""),  randInit(false){}
                    // Pick a random decay channel
                    bool randomDecay(const TH_Channel* &decay) const;
                    // Update decay widths and if necessary Monte Carlo table
                    void update();
                    // Functions for checking if a decay exists in the decay tables
                    bool isEnabled(const TH_Channel *in) const;
                    bool isDisabled(const TH_Channel *in) const;
                    bool isRegistered(const TH_Channel *in) const;
                    // Add decay channel as enabled or disabled
                    void addChannel(const TH_Channel *in);
                    void addDisabled(const TH_Channel *in);
                    void setInvisibleWidth(double width);
                    // Functions for enabling/disabling (registered) decays.
                    // Returns false if decay is in the list of disabled/enabled decays
                    bool enableDecay(const TH_Channel *in);
                    bool disableDecay(const TH_Channel *in);
                    // Get branching ratio of enabled decays
                    double getEnabledBranching() const;
                    // Set total decay width to a fixed value
                    void forceTotalWidth(bool enabled, double width);
                    // Get total decay width
                    double getTotalWidth() const;
                    bool hasEnabledDecays() const;
                private:
                    // Lists of decays
                    vector<const TH_Channel*> enabledDecays;
                    vector<const TH_Channel*> disabledDecays;
                    // Table used for picking random decays
                    mutable vector<double> randLims;
                    // Decay widths of enabled channels and all channels
                    double enabledWidth;
                    double totalWidth;
                    double invisibleWidth;
                    bool useForcedTotalWidth;
                    double forcedTotalWidth;
                    // String particle identifier
                    string pID;
                    // Initialization status of Monte Carlo table
                    mutable bool randInit;
                    // Function used in picking a random decay
                    int findChannelIdx(double pick) const;
                    // Generate table for picking a random decay in Monte Carlo decay chains
                    void generateRandTable() const;
            };

            //  *********************************************
            //  Table of all particles and their decay channels.
            //  Uses particle PID as array index
            //  *********************************************
            class DecayTable
            {
                public:
                    DecayTable(const TH_ProcessCatalog &cat, const SimYieldTable &tab, set<string> disabledList);
                    DecayTable(){};
                    bool hasEntry(string) const;
                    // Add particle to decay table, specifying particle ID, mass and whether or not it should be decayed in decay chains
                    void addEntry(string pID, double m, bool stable);
                    void addEntry(string pID, DecayTableEntry entry);
                    bool randomDecay(string pID, const TH_Channel* &decay) const;
                    const DecayTableEntry& operator[](string i) const;
                    // Retrieve width of decay channel
                    static double getWidth(const TH_Channel *ch);
                    // Print the decay table (to cout)
                    void printTable() const;
                private:
                    unordered_map<string,DecayTableEntry> table;
            };


            //  *********************************************
            //  The main decay chain class.
            //  Each link (particle) in the decay chain is an instance of this class,
            //  with pointers to its parent and child links.
            //  *********************************************
            class ChainParticle
            {
                public:
                    // Invariant (rest) mass
                    const double m;
                    // Constructor for the base node (top particle in the decay chain).
                    ChainParticle(vec3 ipLab, const DecayTable *dc, string pID);
                    // Iteratively add random links to the decay chain by Monte Carlo to a maximum length of maxSteps or minimum energy of Emin.
                    // Use negative numbers to turn off limits
                    void generateDecayChainMC(int maxSteps, double Emin);
                    // Draw new angles for the decay products in this and all subsequent links of the decay chain
                    void reDrawAngles();
                    // Remove all subsequent links in the decay chain
                    void cutChain();
                    // Boost a given 4-momentum from this frame to the lab frame.
                    vec4 p_to_Lab(const vec4 &p) const;
                    // Calculate 4-momentum of this particle in the lab frame.
                    vec4 p_Lab() const;
                    // Calculate the energy of this particle in the lab frame. Faster than calculating the full 4-momentum.
                    double E_Lab() const;
                    // Iteratively collect decay chain endpoint states. Optional argument to only collect particles of certain types.
                    // Note that this function will not collect decay products of endpoint states. These must be extracted manually.
                    void collectEndpointStates(vector<const ChainParticle*> &endpointStates, bool includeAborted, string ipID="") const;
                    // Get number of child particles
                    int getnChildren() const {return nChildren;}
                    // Get child particle
                    const ChainParticle* operator[](int i) const;
                    // Get parent particle
                    const ChainParticle* getParent() const;
                    // Get energy in parent frame
                    double E_parentFrame() const;
                    // Get particle ID
                    string getpID() const {return pID;}
                    // Print the decay chain (to cout)
                    void printChain() const;
                    // Get weight factor (see description of the weight variable)
                    double getWeight() const {return weight;}
                    // Get boost between lab frame and CoM frame of this particle
                    void getBoost(double& gamma, double& beta) const;
                    // Get pointer to decay table
                    const DecayTable* getDecayTable() const {return decayTable;}
                    // Destructor
                    ~ChainParticle();
                private:
                    // Helper function for printChain()
                    bool printChain(int generation, vector<int> ancestry) const;
                    // How much the decay chain (to this point) should be weighted down due to
                    // missing/disabled decay channels. Only relevant for Monte Carlo generated chains.
                    double weight;
                    // Pointer to decay table
                    const DecayTable *decayTable;
                    // Lorentz matrices
                    mat4 boostToParentFrame;
                    mat4 boostToLabFrame;
                    // 4-momentum in parent's rest frame
                    vec4 p_parent;
                    // Particle identifier
                    string pID;
                    // How many ancestors do I have?
                    int chainGeneration;
                    // Has this particle been kept from decaying by an energy or chain length cut?
                    bool abortedDecay;
                    // Is this particle stable, or has it decayed to a final state consisting entirely of stable particles?
                    // If so, this particle is considered a final state, and any children must be extracted manually after collecting the final states.
                    // This is to avoid having final states that can't be treated as free particles (such as quarks).
                    bool isEndpoint;
                    // Number of child particles
                    int nChildren;
                    // Pointers to parent and child particles
                    ChainParticle *parent;
                    vector<ChainParticle*> children;
                    // Function for updating the Lorentz boost matrices according to a new 4-momentum.
                    void update(vec4 &ip_parent);
                    // Constructor used by member functions during chain generation.
                    ChainParticle(const vec4 &pp, double m, double weight, const DecayTable *dc, ChainParticle *parent, int chainGeneration, string pID);
                    // Disable copy constructor and assignment operator. These would cause mayhem.
                    ChainParticle(const ChainParticle&);
                    ChainParticle & operator=(const ChainParticle&);
            };
            typedef std::vector<const Gambit::DarkBit::DecayChain::ChainParticle*> ChainParticleVector;

            // Container for passing around ChainParticle objects.
            struct ChainContainer
            {
                ChainContainer(){}
                ChainContainer(shared_ptr<ChainParticle> ch) : chain(ch) {}
                shared_ptr<const ChainParticle> chain;
            };

        }
    }
}

#endif // defined __decay_chain_hpp__
