// Maintainer-run regression test: link with the configured ColliderBit/Utils
// objects and dependencies. This is not a registered physics analysis.
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisContainer.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include <cmath>
#include <memory>
#include <stdexcept>

using namespace Gambit::ColliderBit;
using Gambit::str;

void require(bool condition, const char* message)
{
  if (!condition) throw std::runtime_error(message);
}

class CutflowProbe : public Analysis
{
public:
  CutflowProbe()
  {
    set_analysis_name("CutflowProbe");
    set_luminosity(1);
    defineSignalRegion("SR", "cut");
  }

  const Cutflows& booked() const { return _cutflows; }
  const EventCounter& counter() const { return _counters.at("SR"); }
  void forget_diagnostics() { _cutflows = Cutflows(); }
  void throw_integer_on_next_event() { legacy_integer = true; }
  void disabled_logging_families(const HEPUtils::Event* event)
  {
    const std::vector<bool> cuts = {true};
    LOG_CUTS(cuts, "missing")
    LOG_CUT_N("missing-", 2)
    LOG_CUTS_N(cuts, "missing-", 2)
  }

private:
  bool legacy_integer = false;
  void run(const HEPUtils::Event* event) override
  {
    if (legacy_integer) throw 23;
    BEGIN_PRESELECTION
    END_PRESELECTION
    LOG_CUT("SR")
    FILL_SIGNAL_REGION("SR");
  }
  void collect_results() override { add_result(SignalRegionData(_counters.at("SR"), 0, {0, 0})); }
  void analysis_specific_reset() override {}
};

void check_photon_variants()
{
  // Use the real factories: a synthetic probe alone misses constructor-order
  // bugs in derived analyses. No event generation or detector RNG is needed.
  const std::vector<std::pair<str, std::size_t>> variants = {
    {"ATLAS_SUSY_2016_27", 7},
    {"ATLAS_SUSY_2016_27_1Photon", 3},
    {"ATLAS_SUSY_2016_27_2Photon", 4}
  };
  for (bool enabled : {false, true})
  {
    Cutflow::set_check_cutflow(enabled);
    for (const auto& variant : variants)
    {
      std::unique_ptr<Analysis> analysis(mkAnalysis(variant.first));
      for (int point = 0; point < 2; ++point)
      {
        if (point) analysis->reset();
        const auto& result = analysis->get_results();
        require(result.size() == variant.second, "Photon variant changed its signal-region selection");
        require(result.cutflows.cfs.size() == 1,
                "Photon regression needs a CHECK_CUTFLOW build with one booked cutflow per variant");
        // This lookup reproduced the reported missing ..._2Photon error before
        // the constructor fix, even with diagnostic filling switched off.
        const auto& cutflow = result.cutflows[analysis->analysis_name()];
        require(cutflow.counts == std::vector<double>(52, 0.0),
                "Photon variant lost or duplicated its cutflow on construction/reset");
      }
    }
  }
}

int main()
{
  check_photon_variants();
  HEPUtils::Event event;
  event.set_weight(2);
  event.set_id(17);
  Cutflow::set_check_cutflow(true);
  CutflowProbe probe;
  probe.analyze(event);
  require(probe.counter().sum() == 1, "Signal counter did not fill");
  require(probe.booked()["SR"].counts == std::vector<double>({2, 2, 2, 2}), "Weighted cutflow incorrect");
  const auto labels = probe.booked()["SR"].cuts;
  probe.reset();
  require(probe.booked().cfs.size() == 1 && probe.booked()["SR"].cuts == labels,
          "Analysis reset discarded booked cutflows");
  require(probe.booked()["SR"].counts == std::vector<double>({0, 0, 0, 0}), "Cutflow statistics survived reset");
  probe.analyze(event);
  require(probe.counter().sum() == 1 && probe.counter().weight_sum2() == 4,
          "Reset mixed different points or lost weighted signal statistics");

  // Disabled diagnostics must not evaluate even a missing named lookup.
  Cutflow::set_check_cutflow(false);
  CutflowProbe disabled;
  disabled.forget_diagnostics();
  disabled.analyze(event);
  disabled.disabled_logging_families(&event);
  require(disabled.counter().weight_sum() == 2 && disabled.counter().weight_sum2() == 4,
          "Disabling cutflow disabled physics counters");
  require(disabled.booked().cfs.empty(), "Disabled diagnostics created implicit cutflows");

  // Enabled diagnostics still report a real configuration mistake explicitly.
  Cutflow::set_check_cutflow(true);
  bool caught = false;
  try { disabled.analyze(event); }
  catch (const std::out_of_range& error)
  {
    const std::string message = error.what();
    caught = message.find("CutflowProbe") != std::string::npos
          && message.find("SR") != std::string::npos
          && message.find("17") != std::string::npos;
  }
  require(caught, "Missing cutflow lost its analysis/event/name diagnostic");

  // Both const and mutable lookup overloads must use typed exceptions.
  Cutflows empty;
  const Cutflows& constant = empty;
  caught = false;
  try { constant["unknown"]; }
  catch (const std::out_of_range&) { caught = true; }
  require(caught, "Const cutflow lookup did not throw a typed error");

  CutflowProbe legacy;
  legacy.throw_integer_on_next_event();
  caught = false;
  try { legacy.analyze(event); }
  catch (const std::runtime_error& error)
  {
    const std::string message = error.what();
    caught = message.find("CutflowProbe") != std::string::npos
          && message.find("17") != std::string::npos
          && message.find("23") != std::string::npos;
  }
  require(caught, "A legacy integer exception escaped without analysis/event context");
}
