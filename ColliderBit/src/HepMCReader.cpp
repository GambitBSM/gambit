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
#include "HepMC3/GenRunInfo.h"

#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <set>
#include <array>
#include <zlib.h>

namespace Gambit
{
  namespace ColliderBit
  {
    long long validate_hepmc_listing(const std::string& filename)
    {
      // gzread is transparent for plain text and verifies gzip CRC/trailers.
      // HepMC3's bxz stream otherwise accepts some truncated gzip footers as EOF.
      std::unique_ptr<gzFile_s, int(*)(gzFile)> input(gzopen(filename.c_str(), "rb"), gzclose);
      if (!input) throw std::runtime_error("Could not open HepMC input " + filename);
      std::array<char, 65536> buffer;
      std::string line, last;
      long long events = 0;
      auto inspect_line = [&]() {
        if (line.find_first_not_of(" \t\r") != std::string::npos)
        {
          last = line;
          if (line.compare(0, 2, "E ") == 0) ++events;
        }
        line.clear();
      };
      int count;
      while ((count = gzread(input.get(), buffer.data(), buffer.size())) > 0)
        for (int i = 0; i < count; ++i)
          if (buffer[i] == '\n') inspect_line(); else line += buffer[i];
      int status;
      const std::string error = gzerror(input.get(), &status);
      if (count < 0 || status != Z_OK)
        throw std::runtime_error("Damaged or truncated gzip input " + filename + ": " + error);
      inspect_line();
      last.erase(last.find_last_not_of(" \t\r") + 1);
      if (events == 0 || (last != "HepMC::IO_GenEvent-END_EVENT_LISTING"
                          && last != "HepMC::Asciiv3-END_EVENT_LISTING"))
        throw std::runtime_error("Incomplete, empty or damaged HepMC listing in " + filename);
      return events;
    }

    double nominal_hepmc_weight(const HepMC3::GenEvent& event,
                               const std::string& requested_name,
                               const std::string& filename,
                               std::string* resolved_name, int* resolved_index)
    {
      const auto& weights = event.weights();
      std::vector<std::string> names;
      if (event.run_info()) names = event.run_info()->weight_names();
      if (!names.empty() && names.size() != weights.size())
        throw std::runtime_error("Weight names and values differ in " + filename);
      if (std::set<std::string>(names.begin(), names.end()).size() != names.size())
        throw std::runtime_error("Duplicate HepMC weight names in " + filename);
      int index = -1;
      if (!requested_name.empty())
      {
        const auto it = std::find(names.begin(), names.end(), requested_name);
        if (it == names.end())
          throw std::runtime_error("Nominal weight '" + requested_name + "' is missing in " + filename);
        index = static_cast<int>(it - names.begin());
      }
      else
      {
        for (std::size_t i = 0; i < names.size(); ++i)
        {
          std::string name = names[i];
          std::transform(name.begin(), name.end(), name.begin(),
                         [](unsigned char c) { return std::tolower(c); });
          if (name.empty() || name == "weight" || name == "nominal" || name == "default" || name == "0")
          {
            if (index >= 0) throw std::runtime_error("Ambiguous nominal HepMC weight in " + filename
                                                  + "; specify nominal_weight_name.");
            index = static_cast<int>(i);
          }
        }
        if (index < 0 && weights.size() <= 1) index = 0;
        if (index < 0)
          throw std::runtime_error("No unique nominal HepMC weight in " + filename
                                   + "; specify nominal_weight_name.");
      }
      const double weight = weights.empty() ? 1.0 : weights.at(index);
      if (!std::isfinite(weight) || weight < 0.0)
        throw std::runtime_error("Non-finite or negative nominal weight in " + filename
                                 + "; CBS currently supports independent positive-weight events.");
      if (resolved_name) *resolved_name = names.empty() ? "<single>" : names.at(index);
      if (resolved_index) *resolved_index = index;
      return weight;
    }

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
