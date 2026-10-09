//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
/// Shared accepted-event CSV export for ColliderBit and CBS.
#pragma once

#include <map>
#include <string>
#include <vector>

namespace Gambit
{
  namespace ColliderBit
  {
    struct AnalysisData;

    /// Append completed-event acceptance rows, grouped by collider and detector.
    /// Existing files must have the same SR columns in the same order.
    /// CSVs contain unweighted 0/1 acceptance; local event IDs are not exported.
    void export_accepted_events(
      const std::vector<AnalysisData*>& analyses,
      const std::map<std::string, std::vector<unsigned int>>& completed_event_ids);
  }
}
