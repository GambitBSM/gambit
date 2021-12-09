DIR          := models/CMSSM
MODNAME      := CMSSM
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes
MODCMSSM_MOD := SM MSSM_higgs
MODCMSSM_DEP := $(patsubst %,model_specific/%,$(MODCMSSM_MOD))
MODCMSSM_INC := $(patsubst %,-Imodel_specific/%,$(MODCMSSM_MOD))
MODCMSSM_LIB := $(foreach M,$(MODCMSSM_MOD),model_specific/$M/libmodel_specific_$M$(MODULE_LIBEXT))

MODCMSSM_SUBMOD  := $(DIR)/cxx_qft
MODCMSSM_SUBMOD_INC := $(patsubst %,-I%,$(MODCMSSM_SUBMOD))

CMSSM_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)
CMSSM_INSTALL_CXXQFT_DIR := \
		$(CMSSM_INSTALL_DIR)/cxx_qft

CMSSM_MK     := \
		$(DIR)/module.mk

CMSSM_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

CMSSM_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

CMSSM_CXX_QFT_VERTICES_MK := \
		$(DIR)/cxx_qft/vertices.mk

CMSSM_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

CMSSM_INCLUDE_MK := \
		$(CMSSM_SUSY_BETAS_MK) \
		$(CMSSM_SOFT_BETAS_MK) \
		$(CMSSM_CXX_QFT_VERTICES_MK)

CMSSM_SLHA_INPUT := \
		$(DIR)/LesHouches.in.CMSSM_generated \
		$(DIR)/LesHouches.in.CMSSM

CMSSM_REFERENCES := \
		$(DIR)/CMSSM_references.tex

CMSSM_GNUPLOT := \
		$(DIR)/CMSSM_plot_rgflow.gnuplot \
		$(DIR)/CMSSM_plot_spectrum.gnuplot

CMSSM_TARBALL := \
		$(MODNAME).tar.gz

LIBCMSSM_SRC := \
		$(DIR)/CMSSM_a_muon.cpp \
		$(DIR)/CMSSM_edm.cpp \
		$(DIR)/CMSSM_FFV_form_factors.cpp \
		$(DIR)/CMSSM_l_to_lgamma.cpp \
		$(DIR)/CMSSM_effective_couplings.cpp \
		$(DIR)/CMSSM_info.cpp \
		$(DIR)/CMSSM_input_parameters.cpp \
		$(DIR)/CMSSM_mass_eigenstates.cpp \
		$(DIR)/CMSSM_observables.cpp \
		$(DIR)/CMSSM_physical.cpp \
		$(DIR)/CMSSM_slha_io.cpp \
		$(DIR)/CMSSM_soft_parameters.cpp \
		$(DIR)/CMSSM_susy_parameters.cpp \
		$(DIR)/CMSSM_utilities.cpp \
		$(DIR)/CMSSM_weinberg_angle.cpp

EXECMSSM_SRC := \
		$(DIR)/run_CMSSM.cpp \
		$(DIR)/run_cmd_line_CMSSM.cpp \
		$(DIR)/scan_CMSSM.cpp
LLCMSSM_LIB  :=
LLCMSSM_OBJ  :=
LLCMSSM_SRC  := \
		$(DIR)/CMSSM_librarylink.cpp

LLCMSSM_MMA  := \
		$(DIR)/CMSSM_librarylink.m \
		$(DIR)/run_CMSSM.m

LIBCMSSM_HDR := \
		$(DIR)/CMSSM_a_muon.hpp \
		$(DIR)/CMSSM_convergence_tester.hpp \
		$(DIR)/CMSSM_edm.hpp \
		$(DIR)/CMSSM_FFV_form_factors.hpp \
		$(DIR)/CMSSM_l_to_lgamma.hpp \
		$(DIR)/CMSSM_effective_couplings.hpp \
		$(DIR)/CMSSM_ewsb_solver.hpp \
		$(DIR)/CMSSM_ewsb_solver_interface.hpp \
		$(DIR)/CMSSM_high_scale_constraint.hpp \
		$(DIR)/CMSSM_info.hpp \
		$(DIR)/CMSSM_initial_guesser.hpp \
		$(DIR)/CMSSM_input_parameters.hpp \
		$(DIR)/CMSSM_low_scale_constraint.hpp \
		$(DIR)/CMSSM_mass_eigenstates.hpp \
		$(DIR)/CMSSM_model.hpp \
		$(DIR)/CMSSM_model_slha.hpp \
		$(DIR)/CMSSM_observables.hpp \
		$(DIR)/CMSSM_physical.hpp \
		$(DIR)/CMSSM_slha_io.hpp \
		$(DIR)/CMSSM_spectrum_generator.hpp \
		$(DIR)/CMSSM_spectrum_generator_interface.hpp \
		$(DIR)/CMSSM_soft_parameters.hpp \
		$(DIR)/CMSSM_susy_parameters.hpp \
		$(DIR)/CMSSM_susy_scale_constraint.hpp \
		$(DIR)/CMSSM_utilities.hpp \
		$(DIR)/CMSSM_weinberg_angle.hpp

LIBCMSSM_CXXQFT_HDR := \
		$(DIR)/cxx_qft/CMSSM_qft.hpp \
		$(DIR)/cxx_qft/CMSSM_fields.hpp \
		$(DIR)/cxx_qft/CMSSM_vertices.hpp \
		$(DIR)/cxx_qft/CMSSM_context_base.hpp \
		$(DIR)/cxx_qft/CMSSM_npointfunctions.hpp

ifneq ($(findstring two_scale,$(SOLVERS)),)
-include $(DIR)/two_scale.mk
endif
ifneq ($(findstring lattice,$(SOLVERS)),)
-include $(DIR)/lattice.mk
endif
ifneq ($(findstring semi_analytic,$(SOLVERS)),)
-include $(DIR)/semi_analytic.mk
endif

ifneq ($(MAKECMDGOALS),showbuild)
ifneq ($(MAKECMDGOALS),tag)
ifneq ($(MAKECMDGOALS),release)
ifneq ($(MAKECMDGOALS),doc)
-include $(CMSSM_SUSY_BETAS_MK)
-include $(CMSSM_SOFT_BETAS_MK)
-include $(CMSSM_CXX_QFT_VERTICES_MK)
-include $(CMSSM_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(CMSSM_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(CMSSM_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(CMSSM_CXX_QFT_VERTICES_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(CMSSM_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif

# remove duplicates in case all solvers are used
LIBCMSSM_SRC := $(sort $(LIBCMSSM_SRC))
EXECMSSM_SRC := $(sort $(EXECMSSM_SRC))

LIBCMSSM_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBCMSSM_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBCMSSM_SRC)))

EXECMSSM_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXECMSSM_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXECMSSM_SRC)))

EXECMSSM_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXECMSSM_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXECMSSM_SRC)))

LIBCMSSM_DEP := \
		$(LIBCMSSM_OBJ:.o=.d)

EXECMSSM_DEP := \
		$(EXECMSSM_OBJ:.o=.d)

LLCMSSM_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLCMSSM_SRC)))

LLCMSSM_OBJ  := $(LLCMSSM_SRC:.cpp=.o)
LLCMSSM_LIB  := $(LLCMSSM_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBCMSSM     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_CMSSM := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_CMSSM := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL_DIR) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBCMSSM) $(EXECMSSM_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		$(Q)install -d $(CMSSM_INSTALL_DIR)
		$(Q)install -d $(CMSSM_INSTALL_CXXQFT_DIR)
		$(Q)install -m u=rw,g=r,o=r $(LIBCMSSM_SRC) $(CMSSM_INSTALL_DIR)
		$(Q)install -m u=rw,g=r,o=r $(LIBCMSSM_HDR) $(CMSSM_INSTALL_DIR)
		$(Q)install -m u=rw,g=r,o=r $(LIBCMSSM_CXXQFT_HDR) $(CMSSM_INSTALL_CXXQFT_DIR)
		$(Q)install -m u=rw,g=r,o=r $(EXECMSSM_SRC) $(CMSSM_INSTALL_DIR)
		$(Q)install -m u=rw,g=r,o=r $(LLCMSSM_SRC) $(CMSSM_INSTALL_DIR)
		$(Q)install -m u=rw,g=r,o=r $(LLCMSSM_MMA) $(CMSSM_INSTALL_DIR)
		$(Q)$(INSTALL_STRIPPED) $(CMSSM_MK) $(CMSSM_INSTALL_DIR) -m u=rw,g=r,o=r
		$(Q)install -m u=rw,g=r,o=r $(CMSSM_INCLUDE_MK) $(CMSSM_INSTALL_DIR)
ifneq ($(CMSSM_SLHA_INPUT),)
		$(Q)install -m u=rw,g=r,o=r $(CMSSM_SLHA_INPUT) $(CMSSM_INSTALL_DIR)
endif
		$(Q)install -m u=rw,g=r,o=r $(CMSSM_REFERENCES) $(CMSSM_INSTALL_DIR)
		$(Q)install -m u=rw,g=r,o=r $(CMSSM_GNUPLOT) $(CMSSM_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		$(Q)-rm -f $(LIBCMSSM_DEP)
		$(Q)-rm -f $(EXECMSSM_DEP)
		$(Q)-rm -f $(LLCMSSM_DEP)

clean-$(MODNAME)-lib:
		$(Q)-rm -f $(LIBCMSSM)
		$(Q)-rm -f $(LLCMSSM_LIB)

clean-$(MODNAME)-obj:
		$(Q)-rm -f $(LIBCMSSM_OBJ)
		$(Q)-rm -f $(EXECMSSM_OBJ)
		$(Q)-rm -f $(LLCMSSM_OBJ)

# BEGIN: NOT EXPORTED ##########################################
clean-$(MODNAME)-src:
		$(Q)-rm -f $(LIBCMSSM_SRC)
		$(Q)-rm -f $(LIBCMSSM_HDR)
		$(Q)-rm -f $(LIBCMSSM_CXXQFT_HDR)
		$(Q)-rm -f $(EXECMSSM_SRC)
		$(Q)-rm -f $(LLCMSSM_SRC)
		$(Q)-rm -f $(LLCMSSM_MMA)
		$(Q)-rm -f $(METACODE_STAMP_CMSSM)
		$(Q)-rm -f $(CMSSM_INCLUDE_MK)
		$(Q)-rm -f $(CMSSM_SLHA_INPUT)
		$(Q)-rm -f $(CMSSM_REFERENCES)
		$(Q)-rm -f $(CMSSM_GNUPLOT)

distclean-$(MODNAME): clean-$(MODNAME)-src
# END:   NOT EXPORTED ##########################################

clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		$(Q)-rm -f $(EXECMSSM_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		$(Q)tar -czf $(CMSSM_TARBALL) \
		$(LIBCMSSM_SRC) $(LIBCMSSM_HDR) $(LIBCMSSM_CXXQFT_HDR) \
		$(EXECMSSM_SRC) \
		$(LLCMSSM_SRC) $(LLCMSSM_MMA) \
		$(CMSSM_MK) $(CMSSM_INCLUDE_MK) \
		$(CMSSM_SLHA_INPUT) $(CMSSM_REFERENCES) \
		$(CMSSM_GNUPLOT)

$(LIBCMSSM_SRC) $(LIBCMSSM_HDR) $(LIBCMSSM_CXXQFT_HDR) $(EXECMSSM_SRC) $(LLCMSSM_SRC) $(LLCMSSM_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_CMSSM)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_CMSSM): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_CMSSM)
		@$(MSG)
		$(Q)"$(MATH)" -run "Get[\"$<\"]; Quit[]" || (echo "Error: The code generation failed!"; exit 1)
		@touch "$(METACODE_STAMP_CMSSM)"
		@echo "Note: to regenerate CMSSM source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_CMSSM)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_CMSSM):
		@true
endif

$(LIBCMSSM_DEP) $(EXECMSSM_DEP) $(LLCMSSM_DEP) $(LIBCMSSM_OBJ) $(EXECMSSM_OBJ) $(LLCMSSM_OBJ) $(LLCMSSM_LIB): \
	CPPFLAGS += $(MODCMSSM_SUBMOD_INC) $(MODCMSSM_INC) $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBCMSSM_DEP) $(EXECMSSM_DEP) $(LLCMSSM_DEP) $(LIBCMSSM_OBJ) $(EXECMSSM_OBJ) $(LLCMSSM_OBJ) $(LLCMSSM_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLCMSSM_OBJ) $(LLCMSSM_LIB): \
	CPPFLAGS += $(LLFLAGS)

$(LIBCMSSM): $(LIBCMSSM_OBJ)
		@$(MSG)
		$(Q)$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBCMSSM) $(MODCMSSM_LIB) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		@$(MSG)
		$(Q)$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLCMSSM_LIB): $(LLCMSSM_OBJ) $(LIBCMSSM) $(MODCMSSM_LIB) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		@$(MSG)
		$(Q)$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS) $(LLLIBS)

ALLDEP += $(LIBCMSSM_DEP) $(EXECMSSM_DEP)
ALLSRC += $(LIBCMSSM_SRC) $(EXECMSSM_SRC)
ALLLIB += $(LIBCMSSM)
ALLEXE += $(EXECMSSM_EXE)
ALLMODDEP += $(MODCMSSM_DEP)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLCMSSM_DEP)
ALLSRC += $(LLCMSSM_SRC)
ALLLL  += $(LLCMSSM_LIB)
endif
