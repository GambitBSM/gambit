//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Source code for types for module DarkBit.
///  For instructions on adding new types, see
///  the corresponding header.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2012 Mar, 2014 Jan
///
///  \author Torsten Bringmann
///          (torsten.bringmann@fys.uio.no)
///  \date 2013 Jun
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2013 Oct
///  \date 2014 Jan, Apr
///  \date 2015 Mar
///  \date 2020 Dec
///
///  \author Lars A. Dal
///          (l.a.dal@fys.uio.no)
///  \date 2014 Mar, Jul, Sep, Oct, Dec
///  \date 2015 Jan
///
///  \author Christopher Savage
///          (chris@savage.name)
///  \date 2015 Jan
///
///  \author Jonathan Cornell
///          (jcornell@ucsc.edu)
///  \date 2014
///
///  \author Sebastian Wild
///          (sebastian.wild@ph.tum.de)
///  \date 2016 Aug
///
///  \author Ben Farmer
///          (benjamin.farmer@imperial.ac.uk)
///  \date 2019 Jul
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 Sep
///
///  *********************************************


#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <cmath>
#include <sstream>

#include "gambit/Backends/backend_types/nulike.hpp"
#include "gambit/DarkBit/DarkBit_types.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/cmake/cmake_variables.hpp"

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <gsl/gsl_integration.h>

namespace Gambit
{
  namespace DarkBit
  {

    namespace
    {
      /// Helper function to convert a "finalState" in the SimYield channel to its conjugated state.
      std::string get_conjugated_finalState(const std::string& finalState)
      {
        if (finalState=="e+_1") return "e-_1";
        if (finalState=="pbar") return "p";
        if (finalState=="Dbar") return "D";

        // All other cases ("gamma","nu_e + nu_ebar",...) are self conjugate
        return finalState;
      }
    }

    /// Helper function to get the mass of a given final state particle
    double get_finalState_mass(const std::string& finalState)
    {
      // Current "massive" final states that can occur in SimYieldTables.
      if (finalState=="e+_1" || finalState=="e-_1") return m_electron;
      if (finalState=="pbar" || finalState=="p"   ) return m_proton;
      if (finalState=="Dbar" || finalState=="D"   ) return m_deuteron;

      // All other final states are ("gamma","nu_e + nu_ebar",...) are massless.
      return 0.0;
    }

    /// General annihilation/decay channel for sim yield tables
    SimYieldChannel::SimYieldChannel(daFunk::Funk dNdE, const std::string& p1, const std::string& p2, const std::string& finalState, double Ecm_min, double Ecm_max, safe_ptr<Options> runOptions)
    : dNdE(dNdE)
    , p1(p1)
    , p2(p2)
    , finalState(finalState)
    , finalStateMass(get_finalState_mass(finalState))
    , Ecm_min(Ecm_min)
    , Ecm_max(Ecm_max)
    {
      // If dNdE is given w.r.t 'Ekin', write it as a function w.r.t. 'E' (total energy)
      // in order to conform with the rest of the code.
      // For E < m, we return zero.
      if (dNdE->hasArg("Ekin"))
      {
        auto E = daFunk::var("E");
        double m = this->finalStateMass;
        dNdE = daFunk::ifelse(E-m, dNdE->set("Ekin", E -m), daFunk::zero("E","Ecm"));
      }

      std::ostringstream msg, msg2;
      msg << "SimYieldChannel for " << p1 << " " << p2 <<
       " final state(s): Requested center-of-mass energy out of range (";
      msg << Ecm_min << "-" << Ecm_max << " GeV).";
      daFunk::Funk error;
      bool invalidate = runOptions.isNull() ? false : runOptions->getValueOrDef<bool>(false, "out_of_range_invalidate");
      bool zero = runOptions.isNull() ? false : runOptions->getValueOrDef<bool>(false, "out_of_range_zero_yield");
      if(invalidate and zero)
      {
        msg2 << std::endl << "The following selected options are incompatible: " << std::endl
            << "  out_of_range_invalidate: true" << std::endl
            << "  out_of_range_zero_yield: true" << std::endl
            << "Please modify your YAML file to correct that." << std::endl;
        DarkBit_error().raise(LOCAL_INFO,msg2.str());
      }
      else if(invalidate)
      {
        error = daFunk::raiseInvalidPoint(msg.str());
      }
      else if(zero)
      {
        error = daFunk::zero("E", "Ecm");
      }
      else
      {
        msg << std::endl << "To circumvent this error you can add one"
            << " of the following two options to the Rules section of your YAML file:" << std::endl
            << " - out_of_range_invalidate:  invalidate points that have"
            << " c.o.m. energy out of range of yield tables." << std::endl
            << " - out_of_range_zero_yield:  set to zero the yields out"
            << " of range of the yield tables." << std::endl
            << " You can add either (but not both) options as module-wide rules like this:" << std::endl << std::endl
            << "  - module: DarkBit" << std::endl
            << "    options:" << std::endl
            << "      out_of_range_zero_yield: true" << std::endl << std::endl
            << "Note that this choice has important physical implications on"
            << " your result, so choose wisely." << std::endl;
        error = daFunk::throwError(msg.str());
      }
      auto Ecm = daFunk::var("Ecm");
      this->dNdE = daFunk::ifelse(Ecm - Ecm_min, daFunk::ifelse(Ecm_max - Ecm, dNdE, error), error);
      dNdE_bound = this->dNdE->bind("E", "Ecm");
    }

    /// Sim yield table dummy constructor
    SimYieldTable::SimYieldTable() : dummy_channel(daFunk::zero("E", "Ecm"), "", "", "", 0.0, 0.0, safe_ptr<Options>()) {}

    void SimYieldTable::addChannel(daFunk::Funk dNdE, const std::string& p1, const std::string& p2, const std::string& finalState, double Ecm_min, double Ecm_max, safe_ptr<Options> runOptions)
    {
      if (checkChannel(p1, p2, finalState) == SimYieldChannelCheck::success)
        channel_list.push_back(SimYieldChannel(dNdE, p1, p2, finalState, Ecm_min, Ecm_max, runOptions));
    }

    void SimYieldTable::addChannel(daFunk::Funk dNdE, const std::string& p1, const std::string& finalState, double Ecm_min, double Ecm_max, safe_ptr<Options> runOptions)
    {
      addChannel(dNdE, p1, "", finalState, Ecm_min, Ecm_max, runOptions);
    }

    void SimYieldTable::addChannel(SimYieldChannel channel)
    {
      if (checkChannel(channel.p1, channel.p2, channel.finalState) == SimYieldChannelCheck::success)
        channel_list.push_back(channel);
    }

    void SimYieldTable::replaceFinalState(const std::string& oldFinalState, const std::string& newFinalState)
    {
      for (auto& channel : channel_list)
      {
        if (channel.finalState == oldFinalState) channel.finalState = newFinalState;
      }
    }

    void SimYieldTable::donateChannels(SimYieldTable& receiver) const
    {
      for (const auto& channel : channel_list) receiver.addChannel(channel);
    }

    bool SimYieldTable::hasChannel(const std::string& p1, const std::string& p2, const std::string& finalState) const
    {
      return ( findChannel(p1, p2, finalState) != -1 );
    }

    bool SimYieldTable::hasChannel(const std::string& p1, const std::string& finalState) const
    {
      return hasChannel(p1, "", finalState);
    }

    bool SimYieldTable::hasAnyChannel(const std::string& p1) const
    {
      return hasAnyChannel(p1, "");
    }

    bool SimYieldTable::hasAnyChannel(const std::string& p1, const std::string& p2) const
    {
      const std::vector<SimYieldChannel> &cl = channel_list;
      for ( unsigned int i = 0; i < channel_list.size(); i++ )
      {
        if ((p1==cl[i].p1 and p2==cl[i].p2) or (p1==cl[i].p2 and p2==cl[i].p1) )
        {
          return true;
        }
      }
      return false;
    }

    const SimYieldChannel& SimYieldTable::getChannel(const std::string& p1, const std::string& p2, const std::string& finalState) const
    {
      int index = findChannel(p1, p2, finalState);
      if ( index == -1 )
      {
        DarkBit_warning().raise(LOCAL_INFO, "getChannel: Channel unknown, returning dummy.");
        return dummy_channel;
      }
      return channel_list[index];
    }

    /// Retrieve simyield table entries at given center of mass energy (GeV)
    daFunk::Funk SimYieldTable::operator()(const std::string& p1, const std::string& p2, const std::string& finalState, double Ecm) const
    {
      return this->operator()(p1, p2, finalState)->set("Ecm", Ecm);
    }

    /// Retrieve simyield table entries at given center of mass energy (GeV)
    daFunk::Funk SimYieldTable::operator()(const std::string& p1, const std::string& finalState, double Ecm) const
    {
      return this->operator()(p1,finalState)->set("Ecm", Ecm);
    }

    /// Retrieve simyield table entries at given center of mass energy (GeV)
    daFunk::Funk SimYieldTable::operator()(const std::string& p1, const std::string& p2, const std::string& finalState) const
    {
      int index = findChannel(p1, p2, finalState);
      if ( index == -1 )
      {
          DarkBit_warning().raise(LOCAL_INFO, "SimYieldTable(): Channel not known, returning zero spectrum.");
          return daFunk::zero("E", "Ecm");
      }
      return channel_list[index].dNdE;
    }

    daFunk::Funk SimYieldTable::operator()(const std::string& p1, const std::string& finalState) const
    {
      return this->operator()(p1, "", finalState);
    }

    int SimYieldTable::findChannel(const std::string& p1, const std::string& p2, const std::string& finalState) const
    {
      const std::vector<SimYieldChannel> &cl = channel_list;
      for ( unsigned int i = 0; i < channel_list.size(); i++ )
      {
        if ((p1==cl[i].p1 and p2==cl[i].p2 and finalState==cl[i].finalState) or (p1==cl[i].p2 and p2==cl[i].p1 and finalState==cl[i].finalState) )
        {
          return i;
        }
      }
      return -1;
    }

    SimYieldChannelCheck SimYieldTable::checkChannel(const std::string& p1, const std::string& p2, const std::string& finalState) const
    {
      // Skip if the channel is already in the table
      if ( hasChannel(p1, p2, finalState) )
      {
        DarkBit_warning().raise(LOCAL_INFO, "addChanel: Channel already exists --> ignoring new one.");
        return SimYieldChannelCheck::duplication;
      }

      // Skip when either p1 or p2 are equal to finalState.
      // Also skip if finalState is the conjugated state in the single particle case (p2=="")
      // Such channels are monochromatic lines that are handled separately
      // in "getYield()" of IndirectDetectionYields.cpp
      if (p1 == finalState || p2 == finalState || (p2 == "" && p1 == get_conjugated_finalState(finalState)))
      {
        std::ostringstream warn;
        warn << "addChanel: The channel (p1 = " <<p1<<", p2 = "<<p2<<", finalState = "<<finalState<<") appears to be a monochromatic line.\n";
        warn << "Such lines are handled within \"getYield()\" in DarkBit/src/IndirectDetectionYield.cpp";
        warn << " --> This channel will be ingnored in the SimYieldTable";
        DarkBit_warning().raise(LOCAL_INFO, warn.str());
        return SimYieldChannelCheck::monochromatic_line;
      }

      // If everything went fine, return success
      return SimYieldChannelCheck::success;
    }

  }
}
