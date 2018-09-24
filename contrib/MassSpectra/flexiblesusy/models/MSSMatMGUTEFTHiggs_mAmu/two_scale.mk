#  ====================================================================
#  This file is part of FlexibleSUSY.
#
#  FlexibleSUSY is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published
#  by the Free Software Foundation, either version 3 of the License,
#  or (at your option) any later version.
#
#  FlexibleSUSY is distributed in the hope that it will be useful, but
#  WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with FlexibleSUSY.  If not, see
#  <http://www.gnu.org/licenses/>.
#  ====================================================================

MSSMatMGUTEFTHiggs_mAmu_INCLUDE_MK += $(DIR)/two_scale.mk

LIBMSSMatMGUTEFTHiggs_mAmu_SRC += \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_convergence_tester.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_ewsb_solver.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_high_scale_constraint.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_initial_guesser.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_low_scale_constraint.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_model.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_spectrum_generator.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_susy_scale_constraint.cpp
LIBMSSMatMGUTEFTHiggs_mAmu_HDR += \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_convergence_tester.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_ewsb_solver.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_high_scale_constraint.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_initial_guesser.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_low_scale_constraint.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_model.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_spectrum_generator.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_two_scale_susy_scale_constraint.hpp

LIBMSSMatMGUTEFTHiggs_mAmu_SRC += \
		models/MSSMatMGUTEFTHiggs_mAmu/MSSMatMGUTEFTHiggs_mAmu_standard_model_two_scale_matching.cpp

LIBMSSMatMGUTEFTHiggs_mAmu_HDR += \
		models/MSSMatMGUTEFTHiggs_mAmu/MSSMatMGUTEFTHiggs_mAmu_standard_model_two_scale_matching.hpp
