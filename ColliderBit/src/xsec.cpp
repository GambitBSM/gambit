//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit (production) cross-section class.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2019 Feb
///
///  *********************************************

#include <cmath>
#include <omp.h>
#include "gambit/ColliderBit/xsec.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    /// Constructor
    xsec::xsec() : _ntot(0)
                 , _xsec(0)
                 , _xsecerr(0)
    {}

    /// Public method to reset this instance for reuse, avoiding the need for "new" or "delete".
    void xsec::reset()
    {
      _ntot = 0;
      _xsec = 0;
      _xsecerr = 0;

      // Add this instance to the instances map if it's not there already.
      int thread = omp_get_thread_num();
      if (instances_map.count(thread) == 0)
      {
        #pragma omp critical
        {
          instances_map[thread] = this;
        }
      }
    }

    /// Increment the number of events seen so far
    void xsec::log_event() { _ntot += 1; }

    /// Return the total number of events seen so far.
    double xsec::num_events() const { return _ntot; }

    /// Return the cross-section (in pb).
    double xsec::operator()() const { return _xsec; }

    /// Return the cross-section error (in pb).
    double xsec::xsec_err() const { return _xsecerr; }

    /// Return the cross-section relative error.
    double xsec::xsec_relerr() const { return _xsec > 0 ? _xsecerr/_xsec : 0; }

    /// Return the cross-section per event seen (in pb).
    double xsec::xsec_per_event() const { return (_xsec >= 0 && _ntot > 0) ? _xsec/_ntot : 0; }

    /// Set the cross-section and its error (in pb).
    void xsec::set_xsec(double xs, double xserr) { _xsec = xs; _xsecerr = xserr; }

    /// Average cross-sections and combine errors.
    void xsec::average_xsec(double other_xsec, double other_xsecerr, int other_ntot)
    {
      if (other_xsec > 0)
      {
        if (_xsec <= 0)
        {
          set_xsec(other_xsec, other_xsecerr);
        }
        else
        {
          _ntot += other_ntot;
          double w = 1./(_xsecerr*_xsecerr);
          double other_w = 1./(other_xsecerr*other_xsecerr);
          _xsec = (w * _xsec + other_w * other_xsec) / (w + other_w);
          _xsecerr = 1./sqrt(w + other_w);
        }
      }
    }

    /// Collect xsec predictions from other threads and do a weighted combination.
    void xsec::gather_xsecs()
    {
      int this_thread = omp_get_thread_num();
      for (auto& thread_xsec_pair : instances_map)
      {
        if (thread_xsec_pair.first == this_thread) continue;
        const xsec& other_xsec = (*thread_xsec_pair.second);
        average_xsec(other_xsec(), other_xsec.xsec_err(), other_xsec.num_events());
      }
    }

    /// A map with pointers to all instances of this class. The key is the thread number.
    std::map<int, const xsec*> xsec::instances_map;

  }
}
