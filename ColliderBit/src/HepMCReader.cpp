// Common HepMC2/3 ASCII input, including gzip-compressed files.
#include "gambit/cmake/cmake_variables.hpp"

#ifndef EXCLUDE_HEPMC

#include "gambit/ColliderBit/HepMCReader.hpp"

// HepMC3 3.2.5 provides compressed streams as an opt-in header interface.
// Keep it in this translation unit so all callers use the same reader setup.
#define HEPMC3_USE_COMPRESSION 1
#define HEPMC3_Z_SUPPORT 1
#include "HepMC3/ReaderAscii.h"
#include "HepMC3/ReaderAsciiHepMC2.h"
#include "HepMC3/ReaderGZ.h"

#include <stdexcept>

namespace Gambit
{
  namespace ColliderBit
  {
    std::unique_ptr<HepMC3::Reader> make_hepmc_reader(const std::string& filename)
    {
      // HepMC's stream detects gzip by its magic bytes and reads plain text
      // transparently. Only a small header is decompressed for this check.
      HepMC3::ifstream input(filename);
      if (!input)
        throw std::runtime_error("Could not open HepMC input " + filename + ".");

      std::string line;
      while (std::getline(input, line))
      {
        if (line.empty()) continue;
        const std::string version = line.substr(0, 16);
        if (version == "HepMC::Version 2")
          return std::make_unique<HepMC3::ReaderGZ<HepMC3::ReaderAsciiHepMC2>>(filename);

        if (version == "HepMC::Version 3" && std::getline(input, line))
        {
          const std::string format = line.substr(0, 14);
          if (format == "HepMC::Asciiv3")
            return std::make_unique<HepMC3::ReaderGZ<HepMC3::ReaderAscii>>(filename);
          if (format == "HepMC::IO_GenE")
            return std::make_unique<HepMC3::ReaderGZ<HepMC3::ReaderAsciiHepMC2>>(filename);
        }
        throw std::runtime_error("Unrecognised HepMC2/3 ASCII header in " + filename + ".");
      }
      throw std::runtime_error("HepMC input " + filename + " is empty.");
    }
  }
}

#endif
