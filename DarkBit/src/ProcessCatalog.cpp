//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementation file for DarkBit Process
///  Catalog constituents types.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Mar
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/DarkBit/ProcessCatalog.hpp"

//#define DARKBIT_DEBUG

namespace Gambit {
  namespace DarkBit {


    // TH_ParticleProperty definitions

    TH_ParticleProperty::TH_ParticleProperty(double mass, unsigned int spin2)
      : mass(mass), spin2(spin2)
    {}


    // TH_Channel definitions

    /// Constructor
    TH_Channel::TH_Channel(std::vector<str> finalStateIDs, daFunk::Funk genRate)
      :  finalStateIDs(finalStateIDs), nFinalStates(finalStateIDs.size()),
      genRate(genRate)
    {
      if ( nFinalStates < 2 )
      {
        DarkBit_error().raise(LOCAL_INFO, "Need at least two final state particles.");
      }
    }

    /// Print information about this channel.
    void TH_Channel::printChannel() const
    {
      logger() << "Channel: ";
      for ( auto it = finalStateIDs.begin(); it != finalStateIDs.end(); it++ )
      {
        logger() << *it << " ";
      }
      logger() << EOM;
    }

    /*! \brief Indicate whether or not the final states of this channel contain
     * a specific particle.
     */
    bool TH_Channel::channelContains(str p) const
    {
      return std::find(finalStateIDs.begin(),
          finalStateIDs.end(), p) != finalStateIDs.end();
    }

    /*! \brief Indicate whether or not this channel is the one defined by some
     * specific final states.  Particle name version.
     */
    bool TH_Channel::isChannel(str p0, str p1, str p2, str p3) const
    {
      str vals[] = {p0, p1};
      std::vector<str> inIDs(std::begin(vals), std::end(vals));
      if (p2 != "") inIDs.push_back(p2);
      if (p3 != "") inIDs.push_back(p3);
      return isChannel(inIDs);
    }

    /*! \brief Indicate whether or not this channel is the one defined by some
     * specific final states.  Particle vector version.
     */
    bool TH_Channel::isChannel(std::vector<str> particles) const
    {
      if (particles.size() != finalStateIDs.size()) return false;
      return std::is_permutation(
          finalStateIDs.begin(), finalStateIDs.end(), particles.begin());
    }


    // TH_Process definitions

    /// Constructor for decay process
    TH_Process::TH_Process(const str & particle1ID)
      : isAnnihilation (false),
      particle1ID    (particle1ID),
      particle2ID    (""),
      genRateMisc    (daFunk::zero())
    {}

    /// Constructor for annihilation process
    TH_Process::TH_Process(const str & particle1ID, const str & particle2ID)
      : isAnnihilation (true),
      particle1ID(particle1ID),
      particle2ID(particle2ID),
      genRateMisc(daFunk::zero("v"))
    {
      if (particle1ID.compare(particle2ID) > 0)
      {
        DarkBit_error().raise(LOCAL_INFO,
            "Particle identifiers should be in alphabetical order.");
      }
    }

    /// Compare initial states
    bool TH_Process::isProcess(const str & p1, const str & p2) const
    {
      sspair candidate_process(p1, p2);
      sspair this_process(this->particle1ID, this->particle2ID);
      return candidate_process == this_process;
    }

    /// Check for given channel.  Return a pointer to it if found, NULL if not.
    const TH_Channel* TH_Process::find(std::vector<str> final_states) const
    {
      for (auto it = channelList.begin(); it != channelList.end(); ++it)
      {
        if (it->isChannel(final_states)) return &(*it);
      }
      return NULL;
    }


    // TH_ProcessCatalog definitions

    /// Retrieve a specific process from the catalog
    TH_Process TH_ProcessCatalog::getProcess(str id1, str id2) const
    {
      const TH_Process* temp = find(id1, id2);
      if (temp == NULL)
      {
        DarkBit_error().raise(LOCAL_INFO,
            "Process with initial states " + id1 + " " + id2 + " missing.");
      }
      return *temp;
    }

    /// Check for a specific process in the catalog
    const TH_Process* TH_ProcessCatalog::find(str id1, str id2) const
    {
      for (std::vector<TH_Process>::const_iterator it = processList.begin();
          it != processList.end(); ++it)
      {
        if ( it -> isProcess(id1, id2) ) return &(*it);
      }
      return NULL;
    }

    /*! \brief Retrieve properties of a given particle involved in one or more
     * processes in this catalog
     */
    TH_ParticleProperty TH_ProcessCatalog::getParticleProperty(str id) const
    {
      auto it = particleProperties.find(id);
      if ( it == particleProperties.end() )
      {
        DarkBit_error().raise(LOCAL_INFO,
            "Cannot find entry for " + id +
            " in particleProperties of TH_ProcessCatalog.");
      }
      return it->second;
    }

    bool TH_ProcessCatalog::hasParticleProperty(str id) const
    {
      auto it = particleProperties.find(id);
      return (it != particleProperties.end());
    }


    void TH_ProcessCatalog::validate()
    {
#ifdef DARKBIG_DEBUG
      std::cout << std::endl;
      std::cout << "********************************" << std::endl;
      std::cout << "*** Validate Process catalog ***" << std::endl;
      std::cout << "********************************" << std::endl;
      std::cout << std::endl;
#endif

      for (auto it = processList.begin(); it != processList.end(); it++)
      {
        if (it->isAnnihilation) // Annihilation
        {
          std::string p1ID = it->particle1ID;
          std::string p2ID = it->particle2ID;
          double m1 = getParticleProperty(p1ID).mass;
          double m2 = getParticleProperty(p2ID).mass;
          double E_in = m1 + m2;
#ifdef DARKBIT_DEBUG
          std::cout << "Annihilation process for: " << p1ID << " " << p2ID << std::endl;
          std::cout << "  Masses (GeV): " << m1 << " " << m2 << std::endl;
#endif

          if ((it->genRateMisc->getNArgs() != 1) or not(it->genRateMisc->hasArg("v")))
            DarkBit_error().raise(LOCAL_INFO,
                "Invalid TH_ProcessCatalog annihilation entry for " + it->particle1ID + " " + it->particle2ID + "\n"
                "  genRateMisc must have relative velocity v as only argument.");

#ifdef DARKBIT_DEBUG
          std::cout << "  genRateMisc(v=0) = " << it->genRateMisc->bind("v")->eval(0) << std::endl;
#endif

          for (auto it2 = it->channelList.begin(); it2 != it->channelList.end(); it2++)
          {
            double E_out = 0;
            std::string outstring = "";
            for (size_t i = 0; i < it2->finalStateIDs.size(); i++)
            {
              E_out += getParticleProperty(it2->finalStateIDs[i]).mass;
              outstring += it2->finalStateIDs[i] + " ";
            }
#ifdef DARKBIT_DEBUG
            std::cout << "  Channel: " << outstring << std::endl;
            std::cout << "    Total mass: " << E_out << std::endl;
#endif
            if (it2->nFinalStates != it2->finalStateIDs.size())
              DarkBit_error().raise(LOCAL_INFO,
                  "Invalid TH_ProcessCatalog annihilation entry for " + it->particle1ID + " " + it->particle2ID + "\n"
                  "  inconsistent nFinalStates entry for final states " + outstring);
            if ((it2->finalStateIDs.size() < 2) or (it2->finalStateIDs.size() > 3))
              DarkBit_error().raise(LOCAL_INFO,
                "Invalid TH_ProcessCatalog annihilation entry for " + it->particle1ID + " " + it->particle2ID + "\n"
                "  number of final states not supported for annihilation into " + outstring);
            if (it2->finalStateIDs.size() == 2)
              if ((it2->genRate->getNArgs() != 1) or not it2->genRate->hasArg("v"))
                DarkBit_error().raise(LOCAL_INFO,
                  "Invalid TH_ProcessCatalog annihilation entry for " + it->particle1ID + " " + it->particle2ID + "\n"
                  "  genRate must have relative velocity v as only argument for annihilation into " + outstring);
            if (it2->finalStateIDs.size() == 3)
              if (it2->genRate->getNArgs() != 3 or not it2->genRate->hasArg("E") or not it2->genRate->hasArg("E1") or not it2->genRate->hasArg("v"))
                DarkBit_error().raise(LOCAL_INFO,
                  "Invalid TH_ProcessCatalog annihilation entry for " + it->particle1ID + " " + it->particle2ID + "\n"
                  "  genRate must have three arguments (v, E and E1) for annihilation into " + outstring);
            if ((it2->finalStateIDs.size() == 3) and E_out > E_in)
            {
              // TODO: This could be defined more generally (allowing three-body final states that are closed for v=0)
              DarkBit_error().raise(LOCAL_INFO,
                "Invalid TH_ProcessCatalog annihilation entry for " + it->particle1ID + " " + it->particle2ID + "\n"
                "  three-body final states kinematically not allowed for v=0 for annihilation into " + outstring);
            }
            // Test whether channels kinematically closed for v=0 are indeed closed
            if ((it2->finalStateIDs.size() == 2) and (E_out > E_in))
            {
              double v_min = sqrt(1-1/pow(E_out/E_in,2));
              if ( it2->genRate->bind("v")->eval(v_min*0.999) != 0 )
                DarkBit_error().raise(LOCAL_INFO,
                  "Invalid TH_ProcessCatalog annihilation entry for " + it->particle1ID + " " + it->particle2ID + "\n"
                  "  genRate must be zero for values of v that are below kinematic threshold for annihilation into " + outstring);
            }
#ifdef DARKBIT_DEBUG
            if (it2->finalStateIDs.size() == 2)
              std::cout << "    genRate(v=0) = " << it2->genRate->bind("v")->eval() << std::endl;
            else
              std::cout << "    genRate(v=0) = f(E, E1)" << std::endl;
#endif
          }
        }
        else // Decay
        {
          double E_in = getParticleProperty(it->particle1ID).mass;

#ifdef DARKBIT_DEBUG
          std::cout << "Decay process for: " << it->particle1ID << std::endl;
          std::cout << "  Mass (GeV): " << E_in << std::endl;
          std::cout << "  genRateMisc = " << it->genRateMisc->bind()->eval() << std::endl;
#endif

          if (it->genRateMisc->getNArgs() != 0)
            DarkBit_error().raise(LOCAL_INFO,
                "Invalid TH_ProcessCatalog decay entry for " + it->particle1ID + "\n"
                "  genRateMisc must have zero arguments.");
          for (auto it2 = it->channelList.begin(); it2 != it->channelList.end(); it2++)
          {
            double E_out = 0;
            std::string outstring = "";
            for (size_t i = 0; i < it2->finalStateIDs.size(); i++)
            {
              E_out += getParticleProperty(it2->finalStateIDs[i]).mass;
              outstring += it2->finalStateIDs[i] + " ";
            }
#ifdef DARKBIT_DEBUG
            std::cout << "  Channel: " << outstring << std::endl;
            std::cout << "    Total mass: " << E_out << std::endl;
#endif
            if (it2->nFinalStates != it2->finalStateIDs.size())
              DarkBit_error().raise(LOCAL_INFO,
                  "Invalid TH_ProcessCatalog decay entry for " + it->particle1ID + "\n"
                  "  inconsistent nFinalStates entry for final states " + outstring);
            if ((it2->finalStateIDs.size() < 2) or (it2->finalStateIDs.size() > 3))
              DarkBit_error().raise(LOCAL_INFO,
                "Invalid TH_ProcessCatalog decay entry for " + it->particle1ID + "\n"
                "  number of final states not supported for decay into " + outstring);
            if (it2->finalStateIDs.size() == 2)
              if (it2->genRate->getNArgs() != 0)
                DarkBit_error().raise(LOCAL_INFO,
                  "Invalid TH_ProcessCatalog decay entry for " + it->particle1ID + "\n"
                  "  genRate must have zero arguments for decay into " + outstring);
            if (it2->finalStateIDs.size() == 3)
              if (it2->genRate->getNArgs() != 2 or not it2->genRate->hasArg("E") or not it2->genRate->hasArg("E1"))
                DarkBit_error().raise(LOCAL_INFO,
                  "Invalid TH_ProcessCatalog decay entry for " + it->particle1ID + "\n"
                  "  genRate must have two arguments (E and E1) for decay into " + outstring);
            if (E_out > E_in)
              DarkBit_error().raise(LOCAL_INFO,
                "Invalid TH_ProcessCatalog decay entry for " + it->particle1ID + "\n"
                "  kinematically forbidden decay into " + outstring);
#ifdef DARKBIT_DEBUG
            if (it2->finalStateIDs.size() == 2)
              std::cout << "    genRate = " << it2->genRate->bind()->eval() << std::endl;
            else
              std::cout << "    genRate = f(E, E1)" << std::endl;
#endif
          }
        }
      }
#ifdef DARKBIT_DEBUG
      std::cout << std::endl;
      std::cout << "*****************" << std::endl;
      std::cout << "*** Validated ***" << std::endl;
      std::cout << "*****************" << std::endl;
      std::cout << std::endl;
#endif
    }
  } // namespace DarkBit
} // namespace Gambit

#undef DARKBIT_DEBUG
