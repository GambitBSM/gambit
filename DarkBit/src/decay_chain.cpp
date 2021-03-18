//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementation of classes and functions for decay chain setup
///  Currently only accepts 2-body decays in each step,
///  and assumes that particles decay isotropically in their CM system (like
///  scalars).  Does not allow massless particles as intermediate states.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Lars A. Dal
///          (l.a.dal@fys.uio.no)
///  \date 2014 Oct, Nov, Dec
///  \date 2015 Jan
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"

//#define DARKBIT_DEBUG

namespace Gambit
{
  namespace DarkBit
  {
    namespace DecayChain
    {
      using std::ostringstream;
      using std::set;
      using std::endl;
      using std::pair;

      //  *********************************************
      //  3-vector related
      //  *********************************************

      double vec3::length() const
      {
        return sqrt(vals[0]*vals[0]+vals[1]*vals[1]+vals[2]*vals[2]);
      }
      void vec3::normalize()
      {
        double l = length();
        for(int i=0;i<3;i++)
        {
          vals[i] /= l;
        }
      }
      void vec3::normalize(const double len)
      {
        double l = length();
        for(int i=0;i<3;i++)
        {
          vals[i] *= len/l;
        }
      }
      vec3 operator* (double x, const vec3 &y)
      {
        vec3 retVec = y;
        for(int i=0;i<3;i++)
        {
          retVec[i] *= x;
        }
        return retVec;
      }
      vec3 operator* (const vec3 &y, double x)
      {
        vec3 retVec = y;
        for(int i=0;i<3;i++)
        {
          retVec[i] *= x;
        }
        return retVec;
      }
      vec3 operator/ (const vec3 &y, double x)
      {
        vec3 retVec = y;
        for(int i=0;i<3;i++)
        {
          retVec[i] /= x;
        }
        return retVec;
      }
      std::ostream& operator<<(std::ostream& os, const vec3& v)
      {
        os << v[0] << ", " << v[1]  << ", " << v[2];
        return os;
      }
      double dot(const vec3 &a, const vec3 &b)
      {
        return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
      }


      //  *********************************************
      //  4-vector related
      //  *********************************************

      vec4 operator* (double x, const vec4 &y)
      {
        vec4 retVec = y;
        for(int i=0;i<4;i++)
        {
          retVec[i] *= x;
        }
        return retVec;
      }
      vec4 operator* (const vec4 &y, double x)
      {
        vec4 retVec = y;
        for(int i=0;i<4;i++)
        {
          retVec[i] *= x;
        }
        return retVec;
      }
      vec4 operator+ (const vec4 &x, const vec4 &y)
      {
        vec4 retVec = x;
        for(int i=0;i<4;i++)
        {
          retVec[i] += y[i];
        }
        return retVec;
      }
      vec4 operator- (const vec4 &x, const vec4 &y)
      {
        vec4 retVec = x;
        for(int i=0;i<4;i++)
        {
          retVec[i] -= y[i];
        }
        return retVec;
      }
      std::ostream& operator<<(std::ostream& os, const vec4& v)
      {
        os <<
          "(" << v[0] << ", " << v[1]  << ", " << v[2] << ", " << v[3] <<")";
        return os;
      }
      double dot(const vec4 &a, const vec4 &b)
      {
        return a[0]*b[0]-a[1]*b[1]-a[2]*b[2]-a[3]*b[3];
      }
      vec4 Ep4vec(const vec3 p, double m)
      {
        double E = sqrt(dot(p,p)+m*m);
        return vec4(E,p);
      }


      //  *********************************************
      //  4x4 matrix related
      //  *********************************************

      mat4::mat4(
          double v00, double v01, double v02, double v03,
          double v10, double v11, double v12, double v13,
          double v20, double v21, double v22, double v23,
          double v30, double v31, double v32, double v33)
      {
        vals[0][0] = v00;
        vals[0][1] = v01;
        vals[0][2] = v02;
        vals[0][3] = v03;
        vals[1][0] = v10;
        vals[1][1] = v11;
        vals[1][2] = v12;
        vals[1][3] = v13;
        vals[2][0] = v20;
        vals[2][1] = v21;
        vals[2][2] = v22;
        vals[2][3] = v23;
        vals[3][0] = v30;
        vals[3][1] = v31;
        vals[3][2] = v32;
        vals[3][3] = v33;
      }
      mat4::mat4(double v)
      {
        vals[0][0] = v;
        vals[0][1] = v;
        vals[0][2] = v;
        vals[0][3] = v;
        vals[1][0] = v;
        vals[1][1] = v;
        vals[1][2] = v;
        vals[1][3] = v;
        vals[2][0] = v;
        vals[2][1] = v;
        vals[2][2] = v;
        vals[2][3] = v;
        vals[3][0] = v;
        vals[3][1] = v;
        vals[3][2] = v;
        vals[3][3] = v;
      }
      mat4 mat4::identity()
      {
        return mat4(1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1);
      }
      vec4 operator* (const mat4 &m, const vec4 &v)
      {
        vec4 out(0);
        for(int i=0;i<4;i++)
        {
          for(int j=0;j<4;j++)
          {
            out[i] += m.vals[i][j]*v[j];
          }
        }
        return out;
      }
      mat4 operator* (const mat4 &m1, const mat4 &m2)
      {
        mat4 out(0);
        for(int i=0;i<4;i++)
        {
          for(int j=0;j<4;j++)
          {
            for(int k=0; k<4; k++)
            {
              out.vals[i][j] += m1.vals[i][k]*m2.vals[k][j];
            }
          }
        }
        return out;
      }
      std::ostream& operator<<(std::ostream& os, const mat4& m)
      {
        for(int i=0;i<4;i++)
        {
          for(int j=0;j<4;j++)
          {
            os << m.vals[i][j] << ", ";
          }
          if(i!=3)
            os << endl;
        }
        return os;
      }


      //  *********************************************
      //  Utility functions
      //  *********************************************

      double rand_m1_1()
      {
        return -1.0 + 2.0 * rand_0_1();
      }
      vec3 randOnSphere()
      {
        // Marsaglia 1972 rejection method
        double r1,r2;
        do
        {
          r1 = rand_m1_1();
          r2 = rand_m1_1();
        }
        while(r1*r1+r2*r2 >=1.0);
        vec3 v;
        v[0] = 2.0*r1*sqrt(1-r1*r1-r2*r2);
        v[1] = 2.0*r2*sqrt(1-r1*r1-r2*r2);
        v[2] = 1.0-2.0*(r1*r1+r2*r2);
        return v;
      }
      void lorentzMatrix(const vec3 &beta_xyz, mat4 &mat)
      {
        double b = beta_xyz.length();
        double bm2 = b==0 ? 0 : 1.0/(b*b);
        const double &bx = beta_xyz[0];
        const double &by = beta_xyz[1];
        const double &bz = beta_xyz[2];
        double g = 1.0/sqrt(1-b*b);
        mat =  mat4(    g,      -g*bx,              -g*by,              -g*bz,
            -g*bx,  1+(g-1)*bx*bx*bm2,  (g-1)*bx*by*bm2,    (g-1)*bx*bz*bm2,
            -g*by,  (g-1)*by*bx*bm2,    1+(g-1)*by*by*bm2,  (g-1)*by*bz*bm2,
            -g*bz,  (g-1)*bz*bx*bm2,    (g-1)*bz*by*bm2,    1+(g-1)*bz*bz*bm2);
      }
      void lorentzMatrix(const vec3 &beta_xyz, mat4 &mat, double gamma)
      {
        double b = beta_xyz.length();
        double bm2 = b==0 ? 0 : 1.0/(b*b);
        const double &bx = beta_xyz[0];
        const double &by = beta_xyz[1];
        const double &bz = beta_xyz[2];
        double &g = gamma;
        mat =  mat4(    g,      -g*bx,              -g*by,              -g*bz,
            -g*bx,  1+(g-1)*bx*bx*bm2,  (g-1)*bx*by*bm2,    (g-1)*bx*bz*bm2,
            -g*by,  (g-1)*by*bx*bm2,    1+(g-1)*by*by*bm2,  (g-1)*by*bz*bm2,
            -g*bz,  (g-1)*bz*bx*bm2,    (g-1)*bz*by*bm2,    1+(g-1)*bz*bz*bm2);
      }
      vec4 lorentzBoost(const vec4 &inVec, const vec3 &beta_xyz)
      {
        mat4 lorentz;
        lorentzMatrix(beta_xyz, lorentz);
        return lorentz*inVec;
      }
      vec4 p_parentFrame(const vec4 &inVec, const vec4 &p_parent)
      {
        vec3 beta_xyz = -p_parent.xyz()/p_parent[0];
        return lorentzBoost(inVec, beta_xyz);
      }
      void boostMatrixParentFrame(mat4 &mat, vec4 &p_parent, double m)
      {
        vec3 beta_xyz = -p_parent.xyz()/p_parent[0];
        double gamma = p_parent[0]/m;
        lorentzMatrix(beta_xyz, mat,gamma);
      }
      double invariantMass(const vec4 &a, const vec4 &b)
      {
        vec4 tmp = a+b;
        return sqrt(dot(tmp,tmp));
      }


      //  *********************************************
      //  DecayTableEntry functions
      //  *********************************************

      int DecayTableEntry::findChannelIdx(double pick) const
      {
        if(!randInit)
        {
          piped_warnings.request(LOCAL_INFO,
            "Generating rand table at runtime. This should have happened\n"
            "during initialization, and might not be threadsafe here.");
          generateRandTable();
        }
        vector<double>::const_iterator pos = upper_bound(randLims.begin(),
            randLims.end(),pick);
        return pos - randLims.begin();
      }
      bool DecayTableEntry::randomDecay(const TH_Channel* &decay) const
      {
        if(!hasEnabledDecays()) return false;
        double pick = rand_0_1();
        int idx = findChannelIdx(pick);
        decay = enabledDecays[idx];
        return true;
      }
      void DecayTableEntry::generateRandTable() const
      {
        randLims.clear();
        double tmp=0;
        for(vector<const TH_Channel*>::const_iterator
            it = enabledDecays.begin(); it != enabledDecays.end(); ++it)
        {
          tmp += DecayTable::getWidth(*it)/enabledWidth;
          randLims.push_back(tmp);
        }
        randInit=true;
      }
      void DecayTableEntry::update()
      {
        totalWidth = 0;
        enabledWidth = 0;
        for(vector<const TH_Channel*>::const_iterator
            it = enabledDecays.begin(); it != enabledDecays.end(); ++it)
        {
          enabledWidth += DecayTable::getWidth(*it);
          totalWidth   += DecayTable::getWidth(*it);
        }
        for(vector<const TH_Channel*>::const_iterator
            it = disabledDecays.begin(); it != disabledDecays.end(); ++it)
        {
          totalWidth   += DecayTable::getWidth(*it);
        }
        totalWidth += invisibleWidth;
        if(randInit) generateRandTable();
      }
      bool DecayTableEntry::isEnabled(const TH_Channel *in) const
      {
        for(vector<const TH_Channel*>::const_iterator
            it = enabledDecays.begin(); it != enabledDecays.end(); ++it)
        {
          if((*it) == in) return true;
        }
        return false;
      }
      bool DecayTableEntry::isDisabled(const TH_Channel *in) const
      {
        for(vector<const TH_Channel*>::const_iterator
            it = disabledDecays.begin(); it != disabledDecays.end(); ++it)
        {
          if((*it) == in) return true;
        }
        return false;
      }
      bool DecayTableEntry::isRegistered (const TH_Channel *in) const
      {
        if(isEnabled(in)) return true;
        if(isDisabled(in)) return true;
        return false;
      }
      void DecayTableEntry::addChannel(const TH_Channel *in)
      {
        if(in->nFinalStates > 2)
        {
          piped_warnings.request(LOCAL_INFO,
            "Trying to add decay with >2 final states to DecayTableEntry.\n"
            "Channel added as disabled.");
          addDisabled(in);
          return;
        }
        enabledDecays.push_back(in);
        totalWidth   += DecayTable::getWidth(in);
        enabledWidth += DecayTable::getWidth(in);
      }
      void DecayTableEntry::addDisabled(const TH_Channel *in)
      {
        disabledDecays.push_back(in);
        totalWidth   += DecayTable::getWidth(in);
      }
      void DecayTableEntry::setInvisibleWidth(double width)
      {
        invisibleWidth = width;
        totalWidth  += width;
      }
      bool DecayTableEntry::enableDecay(const TH_Channel *in)
      {
        // N>2 body decays currently not possible.
        if(in->nFinalStates > 2)
        {
          piped_warnings.request(LOCAL_INFO,
            "Trying to enable decay with >2 final states in decay chain.\n"
            "Request ignored.");
          return false;
        }
        bool found = false;
        for(vector<const TH_Channel*>::iterator
            it = disabledDecays.begin(); it != disabledDecays.end(); ++it)
        {
          if((*it) == in)
          {
            found = true;
            disabledDecays.erase(it);
          }
        }
        if(!found) return false;
        enabledDecays.push_back(in);
        enabledWidth += DecayTable::getWidth(in);
        // Re-generate Monte Carlo table if necessary
        if(randInit) generateRandTable();
        return true;
      }
      bool DecayTableEntry::disableDecay(const TH_Channel *in)
      {
        bool found = false;
        for(vector<const TH_Channel*>::iterator it = enabledDecays.begin();
            it != enabledDecays.end(); ++it)
        {
          if((*it) == in)
          {
            found = true;
            enabledDecays.erase(it);
          }
        }
        if(!found) return false;
        disabledDecays.push_back(in);
        enabledWidth -= DecayTable::getWidth(in);
        // Re-generate Monte Carlo table if necessary
        if(randInit) generateRandTable();
        return true;
      }
      double DecayTableEntry::getEnabledBranching() const
      {
        return hasEnabledDecays() ? enabledWidth/getTotalWidth() : 0.0;
      }
      void DecayTableEntry::forceTotalWidth(bool enabled, double width)
      {
        useForcedTotalWidth = enabled;
        forcedTotalWidth = width;
      }
      double DecayTableEntry::getTotalWidth() const
      {
        return useForcedTotalWidth ? forcedTotalWidth : totalWidth;
      }
      bool DecayTableEntry::hasEnabledDecays() const
      {
        return (enabledDecays.size()>0);
      }

      //  *********************************************
      //  DecayTable functions
      //  *********************************************

      DecayTable::DecayTable(const TH_ProcessCatalog &cat,
          const SimYieldTable &tab, set<string> disabledList)
      {
#ifdef DARKBIT_DEBUG
        std::cout << "Importing CascadeMC DecayTable from process catalog..." << std::endl;
#endif
        set<string> finalStates;
        // Register all decaying particles and their decays
        for(vector<TH_Process>::const_iterator it = cat.processList.begin();
            it != cat.processList.end(); ++it)
        {
          // Only interested in decay processes
          if(it->isAnnihilation) continue;

          string pID = it->particle1ID;
          double m = cat.getParticleProperty(pID).mass;
          bool stable = ((it->channelList).size()<1);
#ifdef DARKBIT_DEBUG
          std::cout << "Importing " << pID << std::endl;
#endif
          if(disabledList.count(pID)==1) stable = true;
          // If tabulated spectra exist for decays of this particle, consider
          // it stable for the purpose of decay chain generation.
          if(tab.hasAnyChannel(pID)) stable = true;
//          if(!stable and (width <=0.0))
//          {
//             piped_warnings.request(LOCAL_INFO,
//               "Unstable particle "+pID+" with zero width in decay table. Treating it as stable in cascade decays.");
//             stable = true;
//          }
          // Create DecayTableEntry and insert decay channels
          DecayTableEntry entry(pID,m,stable);
          for(vector<TH_Channel>::const_iterator it2 = (
                it->channelList).begin(); it2 != (it->channelList).end(); ++it2)
          {
            // N>2 body decays currently not supported, but should be included
            // as disabled to get the correct total width.
            if((it2->nFinalStates) > 2)
            {
              entry.addDisabled(&(*it2));
            }
            else
            {
              entry.addChannel(&(*it2));
            }
            for(vector<string>::const_iterator
                it3 = (it2->finalStateIDs).begin();
                it3 != (it2->finalStateIDs).end(); ++it3)
            {
              finalStates.insert(*it3);
            }
          }
          entry.setInvisibleWidth(it->genRateMisc->bind()->eval());
          if(!stable and entry.enabledDecays.size() == 0)
          {
            piped_warnings.request(LOCAL_INFO,
              "Unstable particle "+pID+" has no available decay channels. Treating it as stable in cascade decays.");
            entry.stable = true;
          }
          addEntry(pID,entry);
        }
        // Flag channels where all final final states are stable as endpoints.
        // Loop over all particles
        for(unordered_map<string,DecayTableEntry>::iterator it = table.begin();
            it != table.end(); ++it)
        {
          // Loop over all decays
          for(vector<const TH_Channel*>::const_iterator
              it2 = (it->second.enabledDecays).begin();
              it2 != (it->second.enabledDecays).end(); ++it2)
          {
            bool isEndpoint = true;
            // Loop over all final states
            for(vector<string>::const_iterator
                it3 = ((*it2)->finalStateIDs).begin();
                it3 != ((*it2)->finalStateIDs).end(); ++it3)
            {
              // All (and only) decaying particles are registered so far. If
              // particle is registered, it's not stable.
              if(hasEntry(*it3))
              {
                if(!table[*it3].stable)
                {
                  isEndpoint = false;
                  break;
                }
              }
            }
            it->second.endpointFlags[*it2] = isEndpoint;
          }
          it->second.generateRandTable();
        }
        // Iterate over final states and register particles that have not
        // already been registered (because they are considered stable).
        for(set<string>::iterator it = finalStates.begin();
            it != finalStates.end(); ++it)
        {
          if(!hasEntry(*it))
          {
            double m = cat.getParticleProperty(*it).mass;
            addEntry(*it,m,true);
          }
        }
#ifdef DARKBIT_DEBUG
        std::cout << "...done" << std::endl;
#endif
      }
      bool DecayTable::hasEntry(string index) const
      {
        return table.find(index) != table.end();
      }
      void DecayTable::addEntry(string pID, double m, bool stable)
      {
        table.insert (
            pair<string,DecayTableEntry>(pID,DecayTableEntry(pID,m,stable)) );
      }
      void DecayTable::addEntry(string pID, DecayTableEntry entry)
      {
        table.insert ( pair<string,DecayTableEntry>(pID,entry) );
      }
      bool DecayTable::randomDecay(string pID, const TH_Channel* &decay) const
      {
        bool ans=false;
        try
        {
          ans=(table.at(pID)).randomDecay(decay);
        }
        catch (std::out_of_range& e)
        {
          throw(Piped_exceptions::description(LOCAL_INFO,
                "No partcile "+pID+" in decay table."));
        }
        return ans;
      }
      const DecayTableEntry& DecayTable::operator[](string i) const
      {
        const DecayTableEntry *ent = NULL;
        try
        {
          ent= &table.at(i);
        }
        catch (std::out_of_range& e)
        {
          throw(Piped_exceptions::description(LOCAL_INFO,
                "No partcile "+i+" in decay table."));
        }
        return *ent;
      }
      double DecayTable::getWidth(const TH_Channel *ch)
      {
        return ch->genRate->bind()->eval();
      }
      void DecayTable::printTable() const
      {
#ifdef DARKBIT_DEBUG
        std::cout << std::endl;
        std::cout << "***********************" << endl;
        std::cout << "CMC DecayTable printout" << endl;
        std::cout << "***********************" << endl;
        std::cout << std::endl;
        for(unordered_map<string,DecayTableEntry>::const_iterator
            it = table.begin(); it != table.end(); ++it)
        {
          std::cout << "Particle: " <<(it->first) << endl;
          std::cout << "Set stable: " << (it->second).stable << endl;
          std::cout << "Mass: " <<(it->second).m << endl;
          std::cout << "Total width: " << (it->second.getTotalWidth())<< endl;
          std::cout << "Enabled branching ratio: "
            << (it->second.getEnabledBranching()) << endl;
          std::cout << "Enabled decays:" << endl;
          for(vector<const TH_Channel*>::const_iterator
              it2 = (it->second.enabledDecays).begin();
              it2 != (it->second.enabledDecays).end(); ++it2)
          {
            std::cout << "  ";
            for(vector<string>::const_iterator
                it3 = ((*it2)->finalStateIDs).begin();
                it3 != ((*it2)->finalStateIDs).end(); ++it3)
            {
              std::cout << *it3 << ", ";
            }
            std::cout << "Width: " << getWidth(*it2) << endl;
          }
          std::cout << "Disabled decays:" << endl;
          for(vector<const TH_Channel*>::const_iterator
              it2 = (it->second.disabledDecays).begin();
              it2 != (it->second.disabledDecays).end(); ++it2)
          {
            std::cout << "  ";
            for(vector<string>::const_iterator
                it3 = ((*it2)->finalStateIDs).begin();
                it3 != ((*it2)->finalStateIDs).end(); ++it3)
            {
              std::cout << *it3 << ", ";
            }
            std::cout << "Width: " << getWidth(*it2) << endl;
          }
          std::cout << std::endl;
        }
#endif
      }


      //  *********************************************
      //  ChainParticle functions
      //  *********************************************

      ChainParticle::ChainParticle(
          vec3 ipLab, const DecayTable *dc, string pID) :
        m((*dc)[pID].m), weight(1), decayTable(dc), pID(pID),
        chainGeneration(0), abortedDecay(false), isEndpoint(false),
        nChildren(0), parent(NULL)
      {
        p_parent=Ep4vec(ipLab,m);
        boostMatrixParentFrame(boostToParentFrame,p_parent,m);
        boostToLabFrame = boostToParentFrame;
      }
      void ChainParticle::generateDecayChainMC(int maxSteps, double Emin)
      {
        if(nChildren!=0)
        {
          piped_warnings.request(LOCAL_INFO,
            "Overwriting existing decay in decay chain.");
          cutChain();
        }
        // Stable particles flagged as endpoints
        if((*decayTable)[pID].stable)
        {
          isEndpoint = true;
        }
        // Check whether or not to proceed with decay
        else if( ((maxSteps < 0) or (int(chainGeneration) < maxSteps))
            and ((Emin < 0) or (E_Lab()> Emin)) )
        {
          const TH_Channel *chn;
          bool canDecay = decayTable->randomDecay(pID, chn);
          if(!canDecay)
          {
            piped_warnings.request(LOCAL_INFO,
              "Unable to pick allowed decay for "+ pID+". Keeping particle stable.");
            abortedDecay = true;
            return;
          }
          // Only 2-body decays are currently allowed
          if((chn->nFinalStates) != 2)
          {
            string err;
            err = "Invalid decay channel in decay table.\n";
            err+= "N!=2 body decays are currently not supported in cascade decays.\n";
            throw(Piped_exceptions::description(LOCAL_INFO,err));
            return;
          }
          nChildren = 2; // chn->nFinalStates;
          // Kinematics for 2-body decays
          double m1 = (*decayTable)[(chn->finalStateIDs)[0]].m;
          double m2 = (*decayTable)[(chn->finalStateIDs)[1]].m;
          if(m1+m2>m)
          {
            ostringstream err;
            err <<
              "Kinematically impossible decay in decay chain:\n" <<
              pID << "-> " <<
              ((chn->finalStateIDs)[0]) << ", " << ((chn->finalStateIDs)[1]) << "\n" <<
              "Please check your process catalog." << endl;
            err << "Relevant particle masses: " << m << " -> " << m1 << " + " << m2;
            throw(Piped_exceptions::description(LOCAL_INFO, err.str()));
          }
          const double &Etot = m;
          double E1 = 0.5*(Etot*Etot+m1*m1-m2*m2)/Etot;
          double E2 = Etot-E1;
          double abs_p = sqrt(E1*E1-m1*m1);
          // Assume isotropic decay in CM frame (no spin correlations).
          vec3 dir = randOnSphere();
          vec4 p1(E1, abs_p*dir);
          vec4 p2(E2,-abs_p*dir);
          // Weight from not including all possible decay channels
          double wt = weight*(*decayTable)[pID].getEnabledBranching();
          children.push_back(new ChainParticle(p1, m1, wt, decayTable, this,
                chainGeneration+1, chn->finalStateIDs[0]));
          children.push_back(new ChainParticle(p2, m2, wt, decayTable, this,
                chainGeneration+1, chn->finalStateIDs[1]));
          // Reached chain endpoint. Don't attempt further decays
          if((*decayTable)[pID].endpointFlags.at(chn))
          {
            isEndpoint = true;
          }
          // Continue chain from child links.
          else
          {
            for(int i=0;i<nChildren;i++)
            {
              children[i]->generateDecayChainMC(maxSteps, Emin);
            }
          }
        }
        else
        {
          abortedDecay = true;
        }
      }
      void ChainParticle::reDrawAngles()
      {
        if(nChildren==2)
        {
          double m1 = children[0]->m;
          vec3  dir = randOnSphere();
          double E1 = children[0]->p_parent[0];
          double E2 = children[1]->p_parent[0];
          double abs_p = sqrt(E1*E1-m1*m1);
          vec4 p1(E1, abs_p*dir);
          vec4 p2(E2,-abs_p*dir);
          children[0]->update(p1);
          children[1]->update(p2);
          children[0]->reDrawAngles();
          children[1]->reDrawAngles();
        }
      }
      void ChainParticle::cutChain()
      {
        for(int i=0;i<nChildren; i++) delete children[i];
        children.clear();
        nChildren = 0;
      }
      vec4 ChainParticle::p_to_Lab(const vec4 &p) const
      {
        return boostToLabFrame*p;
      }
      vec4 ChainParticle::p_Lab() const
      {
        if(chainGeneration==0) return p_parent;
        return parent->boostToLabFrame*p_parent;
      }
      double ChainParticle::E_Lab() const
      {
        if(chainGeneration==0) return p_parent[0];
        double E = 0;
        for(int j=0;j<4;j++)
        {
          E += (parent->boostToLabFrame).vals[0][j]*p_parent[j];
        }
        return E;
      }
      void ChainParticle::collectEndpointStates(vector<const ChainParticle*>
          &endpointStates, bool includeAborted, string ipID) const
      {
        if(abortedDecay)
        {
          if(includeAborted && ((ipID=="") || (ipID==pID)))
            endpointStates.push_back(this);
        }
        else
        {
          if(nChildren!=0 and !isEndpoint)
          {
            for(vector<ChainParticle*>::const_iterator it=children.begin();
                it!=children.end(); ++it)
            {
              (*it)->collectEndpointStates(endpointStates,includeAborted,pID);
            }
          }
          else if((ipID=="") or (ipID==pID) or isEndpoint)
          {
            endpointStates.push_back(this);
          }
        }
      }
      const ChainParticle* ChainParticle::operator[](int i) const
      {
        if(i<nChildren)
          return children[i];
        else
        {
          throw(Piped_exceptions::description(LOCAL_INFO,
                "Trying to access non-existing decay chain entry."));
          return this;
        }
      }
      const ChainParticle* ChainParticle::getParent() const
      {
        return parent;
      }
      double ChainParticle::E_parentFrame() const
      {
        return p_parent[0];
      }
      void ChainParticle::printChain() const
      {
        std::cout << "*********************" << endl;
        std::cout << "Decay chain printout:" << endl;
        std::cout << "---------------------" << endl;
        std::cout << "Generation " << chainGeneration << ":" << endl;
        std::cout << "0  " << pID << ", p = " << p_Lab() <<
          ", Weight: " << weight  << endl;
        std::cout << "---------------------" << endl;
        if(nChildren>0)
        {
          bool run = false;
          int gen = chainGeneration+1;
          do
          {
            std::cout << "Generation " << gen <<":" << endl;
            run= false;
            for(int i=0;i<nChildren;i++)
            {
              vector<int> ancestry;
              ancestry.push_back(0);
              ancestry.push_back(i);
              bool more = children[i]->printChain(gen,ancestry);
              run = more || run;
            }
            gen++;
            std::cout << "---------------------" << endl;
          }
          while(run);
        }
      }
      bool ChainParticle::printChain(int generation, vector<int> ancestry) const
      {
        if(generation < chainGeneration) return false;
        if(generation > chainGeneration)
        {
          bool more = false;
          for(int i=0;i<nChildren;i++)
          {
            vector<int> ancestry2 = ancestry;
            ancestry2.push_back(i);
            if(children[i]->printChain(generation,ancestry2)) more = true;
          }
          return more;
        }
        for(vector<int>::const_iterator it=ancestry.begin();
            it!=ancestry.end(); ++it)
        {
          std::cout << *it << "  ";
        }
        std::cout << pID  << ", p = " << p_Lab() << ", Weight: " << weight  << endl;
        if(nChildren>0) return true;
        return false;
      }
      void ChainParticle::getBoost(double& gamma, double& beta) const
      {
        const mat4& b=boostToLabFrame;
        gamma = b.vals[0][0];
        beta = sqrt(b.vals[0][1]*b.vals[0][1]+b.vals[0][2]*b.vals[0][2]+
            b.vals[0][3]*b.vals[0][3])/gamma;
      }
      ChainParticle::~ChainParticle()
      {
        for(int i=0;i<nChildren; i++) delete children[i];
      }
      void ChainParticle::update(vec4 &ip_parent)
      {
        p_parent = ip_parent;
        boostMatrixParentFrame(boostToParentFrame,p_parent,m);
        boostToLabFrame = parent->boostToLabFrame*boostToParentFrame;
      }
      ChainParticle::ChainParticle(const vec4 &pp, double m, double weight,
          const DecayTable *dc, ChainParticle *parent, int chainGeneration,
          string pID) :
        m(m), weight(weight), decayTable(dc), p_parent(pp), pID(pID),
        chainGeneration(chainGeneration), abortedDecay(false),
        isEndpoint(false), nChildren(0), parent(parent)
      {
        boostMatrixParentFrame(boostToParentFrame,p_parent,m);
        boostToLabFrame = parent->boostToLabFrame*boostToParentFrame;
      }

    } // namespace DecayChain
  } // namespace DarkBit
} // namespace Gambit
