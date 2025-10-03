#ifndef MYTOPTAGGEDJET_H
#define MYTOPTAGGEDJET_H

#include "HEPUtils/Jet.h"

namespace HEPUtils {

/**
 * A derived jet class that stores substructure variables
 * and a boolean flag for top tagging.
 */
class MyTopTaggedJet : public Jet {
public:
  // Constructor just forwards to the base Jet constructor
  MyTopTaggedJet(const P4& p4)
    : Jet(p4), _tau32(0.0), _isTopTagged(false) {}

  // Set/Get the τ32 substructure variable
  void setTau32(double t) { _tau32 = t; }
  double getTau32() const { return _tau32; }

  // Set/Get the top-tagged flag
  void setTopTagged(bool tagged) { _isTopTagged = tagged; }
  bool isTopTagged() const { return _isTopTagged; }

private:
  double _tau32;
  bool   _isTopTagged;
};

} // namespace HEPUtils

#endif
