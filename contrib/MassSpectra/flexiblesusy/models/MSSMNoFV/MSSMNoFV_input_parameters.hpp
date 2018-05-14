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

// File generated at Thu 10 May 2018 14:59:12

#ifndef MSSMNoFV_INPUT_PARAMETERS_H
#define MSSMNoFV_INPUT_PARAMETERS_H

#include <complex>
#include <Eigen/Core>

namespace flexiblesusy {

struct MSSMNoFV_input_parameters {
   double TanBeta{};
   int SignMu{1};
   double Qin{};
   double M1{};
   double M2{};
   double M3{};
   double AtIN{};
   double AbIN{};
   double AtauIN{};
   double AcIN{};
   double AsIN{};
   double AmuonIN{};
   double AuIN{};
   double AdIN{};
   double AeIN{};
   double mHd2IN{};
   double mHu2IN{};
   double ml11IN{};
   double ml22IN{};
   double ml33IN{};
   double me11IN{};
   double me22IN{};
   double me33IN{};
   double mq11IN{};
   double mq22IN{};
   double mq33IN{};
   double mu11IN{};
   double mu22IN{};
   double mu33IN{};
   double md11IN{};
   double md22IN{};
   double md33IN{};


   Eigen::ArrayXd get() const;
   void set(const Eigen::ArrayXd&);
};

std::ostream& operator<<(std::ostream&, const MSSMNoFV_input_parameters&);

} // namespace flexiblesusy

#endif
