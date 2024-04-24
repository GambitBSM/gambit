// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

// File generated at Wed 29 Mar 2017 15:37:11

#ifndef THDM_II_SPECTRUM_GENERATOR_INTERFACE_H
#define THDM_II_SPECTRUM_GENERATOR_INTERFACE_H

#include "THDM_II_two_scale_model.hpp"
#include "THDM_II_utilities.hpp"

#include "spectrum_generator_settings.hpp"
#include "coupling_monitor.hpp"
#include "two_loop_corrections.hpp"
#include "error.hpp"
#include "logger.hpp"

namespace softsusy {
   class QedQcd;
}

namespace flexiblesusy {

struct THDM_II_input_parameters;

template <class T>
class THDM_II_spectrum_generator_interface {
public:
   THDM_II_spectrum_generator_interface()
      : model()
      , settings()
      , parameter_output_scale(0.)
      , reached_precision(std::numeric_limits<double>::infinity())
   {}
   virtual ~THDM_II_spectrum_generator_interface() {}

   const THDM_II<T>& get_model() const { return model; }
   THDM_II<T>& get_model() { return model; }
   const Problems<THDM_II_info::NUMBER_OF_PARTICLES>& get_problems() const {
      return model.get_problems();
   }
   int get_exit_code() const { return get_problems().have_problem(); }
   double get_reached_precision() const { return reached_precision; }
   const Spectrum_generator_settings& get_settings() const { return settings; }
   void set_parameter_output_scale(double s) { parameter_output_scale = s; }
   void set_precision_goal(double precision_goal_) {
      settings.set(Spectrum_generator_settings::precision, precision_goal_);
   }
   void set_pole_mass_loop_order(unsigned l) {
      settings.set(Spectrum_generator_settings::pole_mass_loop_order, l);
      model.set_pole_mass_loop_order(l);
   }
   void set_pole_scale(double q) {
      settings.set(Spectrum_generator_settings::pole_mass_scale, q);
   }
   void set_ewsb_loop_order(unsigned l) {
      settings.set(Spectrum_generator_settings::ewsb_loop_order, l);
      model.set_ewsb_loop_order(l);
   }
   void set_beta_loop_order(unsigned l) {
      settings.set(Spectrum_generator_settings::beta_loop_order, l);
   }
   void set_beta_zero_threshold(double t) {
      settings.set(Spectrum_generator_settings::beta_zero_threshold, t);
   }
   void set_max_iterations(unsigned n) {
      settings.set(Spectrum_generator_settings::max_iterations, n);
   }
   void set_calculate_sm_masses(bool flag) {
      settings.set(Spectrum_generator_settings::calculate_sm_masses, flag);
   }
   void set_force_output(bool flag) {
      settings.set(Spectrum_generator_settings::force_output, flag);
   }
   void set_threshold_corrections_loop_order(unsigned t) {
      settings.set(Spectrum_generator_settings::threshold_corrections_loop_order, t);
   }
   void set_two_loop_corrections(const Two_loop_corrections& c) {
      settings.set_two_loop_corrections(c);
      model.set_two_loop_corrections(c);
   }
   void set_settings(const Spectrum_generator_settings&);

   virtual void run(const softsusy::QedQcd&, const THDM_II_input_parameters&) = 0;
   void write_running_couplings(const std::string& filename, double, double) const;
   void write_spectrum(const std::string& filename = "THDM_II_spectrum.dat") const;

protected:
   THDM_II<T> model;
   Spectrum_generator_settings settings;
   double parameter_output_scale; ///< output scale for running parameters
   double reached_precision; ///< the precision that was reached
};

/**
 * Setup spectrum generator from a Spectrum_generator_settings object.
 *
 * @param settings spectrum generator settings
 */
template <class T>
void THDM_II_spectrum_generator_interface<T>::set_settings(
   const Spectrum_generator_settings& settings_)
{
   settings = settings_;
   model.set_pole_mass_loop_order(settings.get(Spectrum_generator_settings::pole_mass_loop_order));
   model.set_ewsb_loop_order(settings.get(Spectrum_generator_settings::ewsb_loop_order));
   model.set_two_loop_corrections(settings.get_two_loop_corrections());
}

/**
 * Create a text file which contains the values of all model
 * parameters at all scales between the low-scale and the high-scale.
 *
 * @param filename name of output file
 * @param start lowest scale
 * @param stop highest scale
 */
template <class T>
void THDM_II_spectrum_generator_interface<T>::write_running_couplings(
   const std::string& filename,
   double start, double stop) const
{
   THDM_II_mass_eigenstates tmp_model(model);
   try {
      tmp_model.run_to(start);
   } catch (const Error& error) {
      ERROR("write_running_couplings: running to scale "
            << start << " failed: " << error.what());
      return;
   }

   THDM_II_parameter_getter parameter_getter;
   Coupling_monitor<THDM_II_mass_eigenstates, THDM_II_parameter_getter>
      coupling_monitor(tmp_model, parameter_getter);

   coupling_monitor.run(start, stop, 100, true);
   coupling_monitor.write_to_file(filename);
}

/**
 * Write spectrum (pole masses) to a text file
 *
 * @param filename output file name
 */
template <class T>
void THDM_II_spectrum_generator_interface<T>::write_spectrum(const std::string& filename) const
{
   THDM_II_spectrum_plotter plotter;
   plotter.extract_spectrum(model);
   plotter.write_to_file(filename);
}

} // namespace flexiblesusy

#endif
