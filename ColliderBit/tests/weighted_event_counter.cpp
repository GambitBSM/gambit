// Maintainer-run unit check. This file is not part of the production analysis catalogue.
#include "gambit/ColliderBit/analyses/SignalRegionData.hpp"
#include <cmath>
#include <stdexcept>

using namespace Gambit::ColliderBit;

void close(double actual, double expected)
{
  if (std::abs(actual - expected) > 1e-12 * std::max(1.0, std::abs(expected)))
    throw std::runtime_error("Weighted EventCounter/SignalRegionData mismatch");
}

int main()
{
  HEPUtils::Event event;
  EventCounter first("SR"), second("SR");
  first.set_store_accepted_event_IDs(true);
  second.set_store_accepted_event_IDs(true);
  event.set_id(1); event.set_weight(0.5); first.add_event(event);
  event.set_id(2); event.set_weight(3.0); second.add_event(event);
  first.combine(second); // Independent thread/file accumulators.
  close(first.weight_sum(), 3.5);
  close(first.weight_sum2(), 9.25);
  SignalRegionData sr(first, 0, {0, 0});
  close(sr.n_sig_MC_stat, std::sqrt(9.25));
  close(sr.n_sig_MC_sys, 0);
  // Total input weights [0.5, 1, 3], selected [0.5, 3], L=10/fb, sigma=2 fb.
  sr.n_sig_scaled = 20.0 * 3.5 / 4.5;
  close(sr.calc_n_sig_scaled_err(), 20.0 * std::sqrt(9.25) / 4.5);
  if (sr.accepted_event_ids != std::vector<unsigned int>({1, 2}))
    throw std::runtime_error("Event provenance was lost during merge");
  EventCounter scaled("SR");
  scaled.add_event(event, 8.5, 0.2);
  SignalRegionData with_systematic(scaled, 0, {0, 0});
  close(with_systematic.n_sig_MC_stat, 8.5);
  close(with_systematic.n_sig_MC_sys, 0.2);
  EventCounter added("SR"); added += first;
  close(added.weight_sum2(), 9.25);
  first.reset(); close(first.weight_sum2(), 0); close(first.weight_sum(), 0);
  first.init("new"); close(first.weight_sum2(), 0);
}
