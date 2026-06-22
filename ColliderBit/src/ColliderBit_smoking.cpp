//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit module functions for the smoking backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher Chang
///  \date 2026 Apr
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/Backends/backend_types/smoking.hpp"
#include "gambit/ColliderBit/complete_process_PID_pair_multimaps.hpp"

#include "gambit/Utils/slhaea_helpers.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    /// Run the smoking NLO+NLL cross-section calculation using the SLHAea object
    /// already constructed by ColliderBit (normally passed to Pythia).
    void PerformInitialCrossSection_smoking(initialxsec_container& result)
    {
      using namespace Pipes::PerformInitialCrossSection_smoking;

      SLHAstruct slhaea = *Dep::SpectrumAndDecaysForPythia;

      // Add MODSEL block if it is missing
      if(slhaea.find("MODSEL") == slhaea.end())                                             \
      {                                                                                     \
        SLHAea::Block block("MODSEL");                                                      \
        block.push_back("BLOCK MODSEL              # Model selection");                     \
        SLHAea::Line line;                                                                  \
        line << 1 << 0 << "# Tell smoking that this is a SUSY model.";                       \
        block.push_back(line);                                                              \
	SLHAea::Line line2;                                                                  \
        line2 << 6 << 3 << "# There is Flavour violations in squark and slepton sectors";    \
        block.push_back(line2);                                                              \
        slhaea.push_front(block);                                                           \
      }

      smoking_variables vars;
      vars.slhaea = slhaea;

      BEreq::smoking_init(vars);
      std::vector<Result> res = BEreq::smoking_calc(vars); // TODO: This needs to be renamed in smoking, as Result is far too generic a term
      BEreq::smoking_finalise();

      std::cout << "LO xsec from smoking: " << res[0].cross_section.central << std::endl;

      // Forming the output...
      // Calculating the total cross-section as the sum of the process cross sections
      std::string collider = runOptions->getValueOrDef<std::string>("LHC_13TeV", "Collider"); // TODO: Support multiple Colliders (just loop through a list)
      map_str_xsec_container TotalXsecContainer;
      map_int_process_xsec int_proc_xsec_map;
      map_str_map_int_process_xsec ProcessXsecContainer;
      xsec total_xsec;
      for (size_t i = 0; i < vars.pid1.size(); i++)
      {
        xsec cross_section = res[i].cross_section;
        total_xsec = total_xsec + cross_section;
        double process_xsec = cross_section.central;
        double process_xsecErr = cross_section.upper - cross_section.central;

        // Look up all Pythia process codes for this (pid1, pid2) pair.
        // PID_pair sorts its arguments so ordering in smoking's output doesn't matter.
        PID_pair pp(vars.pid1[i], vars.pid2[i]);
        auto range = all_PID_pairs_to_process_codes().equal_range(pp);

        if (range.first == range.second)
        {
          ColliderBit_warning().raise(LOCAL_INFO,
            "smoking returned a cross-section for PID pair (" +
            std::to_string(vars.pid1[i]) + ", " + std::to_string(vars.pid2[i]) +
            ") that has no entry in all_PID_pairs_to_process_codes. Skipping.");
          continue;
        }

        std::vector<int> codes_for_pair;
        for (auto it = range.first; it != range.second; ++it)
          codes_for_pair.push_back(it->second);

        // Register all Pythia codes for this PID pair, noting codes that share the xsec.
        for (int code : codes_for_pair)
        {
          process_xsec_container newprocess;
          newprocess.set_xsec(process_xsec, process_xsecErr);
          newprocess.set_process_code(code);
          for (int other : codes_for_pair)
            if (other != code) newprocess.register_process_sharing_xsec(other);
          int_proc_xsec_map[code] = newprocess;
        }
      }
      ProcessXsecContainer[collider] = int_proc_xsec_map;
      xsec_container xsContainer;
      xsContainer.set_xsec(total_xsec.central, total_xsec.upper - total_xsec.central); // NOTE: Assuming symmetric uncertainty, but smoking can in theory return assymetric uncertainty
      TotalXsecContainer[collider] = xsContainer;


      result = initialxsec_container();
      result.first = TotalXsecContainer;
      result.second = ProcessXsecContainer;
    }


  }
}
