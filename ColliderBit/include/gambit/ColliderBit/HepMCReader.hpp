// Common HepMC2/3 ASCII input, including gzip-compressed files.
#pragma once

#include "HepMC3/Reader.h"

#include <memory>
#include <string>

namespace Gambit
{
  namespace ColliderBit
  {
    /// Detect the HepMC text format through a transparent decompression stream.
    /// The returned reader owns its input stream for the full event loop.
    std::unique_ptr<HepMC3::Reader> make_hepmc_reader(const std::string& filename);
  }
}
