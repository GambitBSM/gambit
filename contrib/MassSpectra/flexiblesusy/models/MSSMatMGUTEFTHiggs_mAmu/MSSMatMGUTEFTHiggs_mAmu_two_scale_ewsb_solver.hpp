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

// File generated at Thu 10 May 2018 14:34:56

/**
 * @file MSSMatMGUTEFTHiggs_mAmu_two_scale_ewsb_solver.hpp
 *
 * @brief contains class for solving EWSB when two-scale algorithm is used
 *
 * This file was generated at Thu 10 May 2018 14:34:56 with FlexibleSUSY
 * 2.0.1 (git commit: unknown) and SARAH 4.12.2 .
 */

#ifndef MSSMatMGUTEFTHiggs_mAmu_TWO_SCALE_EWSB_SOLVER_H
#define MSSMatMGUTEFTHiggs_mAmu_TWO_SCALE_EWSB_SOLVER_H

#include "MSSMatMGUTEFTHiggs_mAmu_ewsb_solver.hpp"
#include "MSSMatMGUTEFTHiggs_mAmu_ewsb_solver_interface.hpp"
#include "error.hpp"

#include <Eigen/Core>

namespace flexiblesusy {

class EWSB_solver;
class Two_scale;

class MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates;

template<>
class MSSMatMGUTEFTHiggs_mAmu_ewsb_solver<Two_scale> : public MSSMatMGUTEFTHiggs_mAmu_ewsb_solver_interface {
public:
   MSSMatMGUTEFTHiggs_mAmu_ewsb_solver() = default;
   MSSMatMGUTEFTHiggs_mAmu_ewsb_solver(const MSSMatMGUTEFTHiggs_mAmu_ewsb_solver&) = default;
   MSSMatMGUTEFTHiggs_mAmu_ewsb_solver(MSSMatMGUTEFTHiggs_mAmu_ewsb_solver&&) = default;
   virtual ~MSSMatMGUTEFTHiggs_mAmu_ewsb_solver() {}
   MSSMatMGUTEFTHiggs_mAmu_ewsb_solver& operator=(const MSSMatMGUTEFTHiggs_mAmu_ewsb_solver&) = default;
   MSSMatMGUTEFTHiggs_mAmu_ewsb_solver& operator=(MSSMatMGUTEFTHiggs_mAmu_ewsb_solver&&) = default;

   virtual void set_loop_order(int l) override { loop_order = l; }
   virtual void set_number_of_iterations(int n) override { number_of_iterations = n; }
   virtual void set_precision(double p) override { precision = p; }

   virtual int get_loop_order() const override { return loop_order; }
   virtual int get_number_of_iterations() const override { return number_of_iterations; }
   virtual double get_precision() const override { return precision; }

   virtual int solve(MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates&) override;
private:
   static const int number_of_ewsb_equations = 2;
   using EWSB_vector_t = Eigen::Matrix<double,number_of_ewsb_equations,1>;

   class EEWSBStepFailed : public Error {
   public:
      virtual ~EEWSBStepFailed() {}
      virtual std::string what() const { return "Could not perform EWSB step."; }
   };

   int number_of_iterations{100}; ///< maximum number of iterations
   int loop_order{2};             ///< loop order to solve EWSB at
   double precision{1.e-5};       ///< precision goal

   void set_ewsb_solution(MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates&, const EWSB_solver*);
   template <typename It> void set_best_ewsb_solution(MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates&, It, It);

   int solve_tree_level(MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates&);
   int solve_iteratively(MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates&);
   int solve_iteratively_at(MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates&, int);
   int solve_iteratively_with(MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates&, EWSB_solver*, const EWSB_vector_t&);

   EWSB_vector_t initial_guess(const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates&) const;
   EWSB_vector_t tadpole_equations(const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates&) const;
   EWSB_vector_t ewsb_step(const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates&) const;
};

} // namespace flexiblesusy

#endif
