// Common HepMC2/3 ASCII input, including gzip-compressed files.
#pragma once

#include "HepMC3/Reader.h"
#include "HepMC3/GenEvent.h"

#include <memory>
#include <string>

namespace Gambit
{
  namespace ColliderBit
  {
    /// Detect the HepMC text format through a transparent decompression stream.
    /// The returned reader owns its input stream for the full event loop.
    std::unique_ptr<HepMC3::Reader> make_hepmc_reader(const std::string& filename);
    /// Validate the physical listing terminator and count ASCII event records.
    long long validate_hepmc_listing(const std::string& filename);

    /// Resolve by name on each event, never by a cached multiweight index.
    /// Empty requested name selects a unique conventional nominal name or a
    /// single unnamed weight. Negative weights need a signed-event model.
    double nominal_hepmc_weight(const HepMC3::GenEvent& event,
                               const std::string& requested_name,
                               const std::string& filename,
                               std::string* resolved_name = nullptr,
                               int* resolved_index = nullptr);
  }
}
