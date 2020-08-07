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
///          (patscott@physics.mcgill.ca)
///  \date 2013 Oct
///  \date 2014 Jan, Apr
///  \date 2015 Mar
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
#include "gambit/cmake/cmake_variables.hpp"

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <gsl/gsl_integration.h>

namespace Gambit
{
  namespace DarkBit
  {
    
    /// General annihilation/decay channel for sim yield tables
    SimYieldChannel::SimYieldChannel(daFunk::Funk dNdE, std::string p1, std::string p2, std::string finalState, double Ecm_min, double Ecm_max)
    : dNdE(dNdE)
    , p1(p1)
    , p2(p2)
    , finalState(finalState)
    , Ecm_min(Ecm_min)
    , Ecm_max(Ecm_max)
    {
      std::ostringstream msg;
      msg << "SimYieldChannel for " << p1 << " " << p2 <<
       " final state(s): Requested center-of-mass energy out of range (";
      msg << Ecm_min << "-" << Ecm_max << " GeV).";
      auto error = daFunk::raiseInvalidPoint(msg.str());
      auto Ecm = daFunk::var("Ecm");
      this->dNdE = daFunk::ifelse(Ecm - Ecm_min, daFunk::ifelse(Ecm_max - Ecm, dNdE, error), error);
      dNdE_bound = this->dNdE->bind("E", "Ecm");
    }
    
    /// Sim yield table dummy constructor
    SimYieldTable::SimYieldTable() : dummy_channel(daFunk::zero("E", "Ecm"), "", "", "", 0.0, 0.0) {}
    
    void SimYieldTable::addChannel(daFunk::Funk dNdE, std::string p1, std::string p2, std::string finalState, double Ecm_min, double Ecm_max)
    {
      if ( hasChannel(p1, p2) )
      {
        DarkBit_warning().raise(LOCAL_INFO, "addChanel: Channel already exists --> ignoring new one.");
        return;
      }
      channel_list.push_back(SimYieldChannel(dNdE, p1, p2, finalState, Ecm_min, Ecm_max));
    }
    
    void SimYieldTable::addChannel(daFunk::Funk dNdE, std::string p1, std::string finalState, double Ecm_min, double Ecm_max)
    {
      addChannel(dNdE, p1, "", finalState, Ecm_min, Ecm_max);
    }
    
    bool SimYieldTable::hasChannel(std::string p1, std::string p2, std::string finalState) const
    {
      return ( findChannel(p1, p2, finalState) != -1 );
    }
    
    bool SimYieldTable::hasChannel(std::string p1, std::string finalState) const
    {
      return hasChannel(p1, "", finalState);
    }
    
    bool SimYieldTable::hasAnyChannel(std::string p1) const
    {
      return hasAnyChannel(p1, "");
    }
    
    bool SimYieldTable::hasAnyChannel(std::string p1, std::string p2) const
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
    
    const SimYieldChannel& SimYieldTable::getChannel(std::string p1, std::string p2, std::string finalState) const
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
    daFunk::Funk SimYieldTable::operator()(std::string p1, std::string p2, std::string finalState, double Ecm) const
    {
      return this->operator()(p1, p2, finalState)->set("Ecm", Ecm);
    }
    
    /// Retrieve simyield table entries at given center of mass energy (GeV)
    daFunk::Funk SimYieldTable::operator()(std::string p1, std::string finalState, double Ecm) const
    {
      return this->operator()(p1,finalState)->set("Ecm", Ecm);
    }
    
    /// Retrieve simyield table entries at given center of mass energy (GeV)
    daFunk::Funk SimYieldTable::operator()(std::string p1, std::string p2, std::string finalState) const
    {
      int index = findChannel(p1, p2, finalState);
      if ( index == -1 )
      {
          DarkBit_warning().raise(LOCAL_INFO, "SimYieldTable(): Channel not known, returning zero spectrum.");
          return daFunk::zero("E", "Ecm");
      }
      return channel_list[index].dNdE;
    }
    
    daFunk::Funk SimYieldTable::operator()(std::string p1, std::string finalState) const
    {
      return this->operator()(p1, "", finalState);
    }
    
    int SimYieldTable::findChannel(std::string p1, std::string p2, std::string finalState) const
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

  }
}
