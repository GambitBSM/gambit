DIR          := models/THDM_lepton
MODNAME      := THDM_lepton
SARAH_MODEL  := THDM_lepton
WITH_$(MODNAME) := yes

THDM_lepton_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

THDM_lepton_MK     := \
		$(DIR)/module.mk

THDM_lepton_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

THDM_lepton_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

THDM_lepton_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

THDM_lepton_INCLUDE_MK := \
		$(THDM_lepton_SUSY_BETAS_MK) \
		$(THDM_lepton_SOFT_BETAS_MK)

THDM_lepton_SLHA_INPUT := \
		$(DIR)/LesHouches.in.THDM_lepton_generated \


THDM_lepton_REFERENCES := \
		$(DIR)/THDM_lepton_references.tex

THDM_lepton_GNUPLOT := \
		$(DIR)/THDM_lepton_plot_rgflow.gnuplot \
		$(DIR)/THDM_lepton_plot_spectrum.gnuplot

THDM_lepton_TARBALL := \
		$(MODNAME).tar.gz

LIBTHDM_lepton_SRC := \
		$(DIR)/THDM_lepton_a_muon.cpp \
		$(DIR)/THDM_lepton_edm.cpp \
		$(DIR)/THDM_lepton_effective_couplings.cpp \
		$(DIR)/THDM_lepton_info.cpp \
		$(DIR)/THDM_lepton_input_parameters.cpp \
		$(DIR)/THDM_lepton_mass_eigenstates.cpp \
		$(DIR)/THDM_lepton_observables.cpp \
		$(DIR)/THDM_lepton_physical.cpp \
		$(DIR)/THDM_lepton_slha_io.cpp \
		$(DIR)/THDM_lepton_soft_parameters.cpp \
		$(DIR)/THDM_lepton_susy_parameters.cpp \
		$(DIR)/THDM_lepton_utilities.cpp \
		$(DIR)/THDM_lepton_weinberg_angle.cpp

EXETHDM_lepton_SRC := \
		$(DIR)/run_THDM_lepton.cpp \
		$(DIR)/run_cmd_line_THDM_lepton.cpp \
		$(DIR)/scan_THDM_lepton.cpp
LLTHDM_lepton_LIB  :=
LLTHDM_lepton_OBJ  :=
LLTHDM_lepton_SRC  := \
		$(DIR)/THDM_lepton_librarylink.cpp

LLTHDM_lepton_MMA  := \
		$(DIR)/THDM_lepton_librarylink.m \
		$(DIR)/run_THDM_lepton.m

LIBTHDM_lepton_HDR := \
		$(DIR)/THDM_lepton_cxx_diagrams.hpp \
		$(DIR)/THDM_lepton_a_muon.hpp \
		$(DIR)/THDM_lepton_convergence_tester.hpp \
		$(DIR)/THDM_lepton_edm.hpp \
		$(DIR)/THDM_lepton_effective_couplings.hpp \
		$(DIR)/THDM_lepton_ewsb_solver.hpp \
		$(DIR)/THDM_lepton_ewsb_solver_interface.hpp \
		$(DIR)/THDM_lepton_high_scale_constraint.hpp \
		$(DIR)/THDM_lepton_info.hpp \
		$(DIR)/THDM_lepton_initial_guesser.hpp \
		$(DIR)/THDM_lepton_input_parameters.hpp \
		$(DIR)/THDM_lepton_low_scale_constraint.hpp \
		$(DIR)/THDM_lepton_mass_eigenstates.hpp \
		$(DIR)/THDM_lepton_model.hpp \
		$(DIR)/THDM_lepton_model_slha.hpp \
		$(DIR)/THDM_lepton_observables.hpp \
		$(DIR)/THDM_lepton_physical.hpp \
		$(DIR)/THDM_lepton_slha_io.hpp \
		$(DIR)/THDM_lepton_spectrum_generator.hpp \
		$(DIR)/THDM_lepton_spectrum_generator_interface.hpp \
		$(DIR)/THDM_lepton_soft_parameters.hpp \
		$(DIR)/THDM_lepton_susy_parameters.hpp \
		$(DIR)/THDM_lepton_susy_scale_constraint.hpp \
		$(DIR)/THDM_lepton_utilities.hpp \
		$(DIR)/THDM_lepton_weinberg_angle.hpp

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
-include $(THDM_lepton_SUSY_BETAS_MK)
-include $(THDM_lepton_SOFT_BETAS_MK)
-include $(THDM_lepton_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(THDM_lepton_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(THDM_lepton_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(THDM_lepton_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBTHDM_lepton_SRC := $(sort $(LIBTHDM_lepton_SRC))
EXETHDM_lepton_SRC := $(sort $(EXETHDM_lepton_SRC))

LIBTHDM_lepton_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBTHDM_lepton_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBTHDM_lepton_SRC)))

EXETHDM_lepton_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXETHDM_lepton_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXETHDM_lepton_SRC)))

EXETHDM_lepton_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXETHDM_lepton_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXETHDM_lepton_SRC)))

LIBTHDM_lepton_DEP := \
		$(LIBTHDM_lepton_OBJ:.o=.d)

EXETHDM_lepton_DEP := \
		$(EXETHDM_lepton_OBJ:.o=.d)

LLTHDM_lepton_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLTHDM_lepton_SRC)))

LLTHDM_lepton_OBJ  := $(LLTHDM_lepton_SRC:.cpp=.o)
LLTHDM_lepton_LIB  := $(LLTHDM_lepton_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBTHDM_lepton     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_THDM_lepton := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_THDM_lepton := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBTHDM_lepton) $(EXETHDM_lepton_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(THDM_lepton_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBTHDM_lepton_SRC) $(THDM_lepton_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBTHDM_lepton_HDR) $(THDM_lepton_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXETHDM_lepton_SRC) $(THDM_lepton_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLTHDM_lepton_SRC) $(THDM_lepton_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLTHDM_lepton_MMA) $(THDM_lepton_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(THDM_lepton_MK) $(THDM_lepton_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(THDM_lepton_INCLUDE_MK) $(THDM_lepton_INSTALL_DIR)
ifneq ($(THDM_lepton_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(THDM_lepton_SLHA_INPUT) $(THDM_lepton_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(THDM_lepton_REFERENCES) $(THDM_lepton_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(THDM_lepton_GNUPLOT) $(THDM_lepton_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBTHDM_lepton_DEP)
		-rm -f $(EXETHDM_lepton_DEP)
		-rm -f $(LLTHDM_lepton_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBTHDM_lepton)
		-rm -f $(LLTHDM_lepton_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBTHDM_lepton_OBJ)
		-rm -f $(EXETHDM_lepton_OBJ)
		-rm -f $(LLTHDM_lepton_OBJ)

# BEGIN: NOT EXPORTED ##########################################
clean-$(MODNAME)-src:
		-rm -f $(LIBTHDM_lepton_SRC)
		-rm -f $(LIBTHDM_lepton_HDR)
		-rm -f $(EXETHDM_lepton_SRC)
		-rm -f $(LLTHDM_lepton_SRC)
		-rm -f $(LLTHDM_lepton_MMA)
		-rm -f $(METACODE_STAMP_THDM_lepton)
		-rm -f $(THDM_lepton_INCLUDE_MK)
		-rm -f $(THDM_lepton_SLHA_INPUT)
		-rm -f $(THDM_lepton_REFERENCES)
		-rm -f $(THDM_lepton_GNUPLOT)

distclean-$(MODNAME): clean-$(MODNAME)-src
# END:   NOT EXPORTED ##########################################

clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXETHDM_lepton_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(THDM_lepton_TARBALL) \
		$(LIBTHDM_lepton_SRC) $(LIBTHDM_lepton_HDR) \
		$(EXETHDM_lepton_SRC) \
		$(LLTHDM_lepton_SRC) $(LLTHDM_lepton_MMA) \
		$(THDM_lepton_MK) $(THDM_lepton_INCLUDE_MK) \
		$(THDM_lepton_SLHA_INPUT) $(THDM_lepton_REFERENCES) \
		$(THDM_lepton_GNUPLOT)

$(LIBTHDM_lepton_SRC) $(LIBTHDM_lepton_HDR) $(EXETHDM_lepton_SRC) $(LLTHDM_lepton_SRC) $(LLTHDM_lepton_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_THDM_lepton)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_THDM_lepton): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_THDM_lepton)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_THDM_lepton)"
		@echo "Note: to regenerate THDM_lepton source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_THDM_lepton)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_THDM_lepton):
		@true
endif

$(LIBTHDM_lepton_DEP) $(EXETHDM_lepton_DEP) $(LLTHDM_lepton_DEP) $(LIBTHDM_lepton_OBJ) $(EXETHDM_lepton_OBJ) $(LLTHDM_lepton_OBJ) $(LLTHDM_lepton_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBTHDM_lepton_DEP) $(EXETHDM_lepton_DEP) $(LLTHDM_lepton_DEP) $(LIBTHDM_lepton_OBJ) $(EXETHDM_lepton_OBJ) $(LLTHDM_lepton_OBJ) $(LLTHDM_lepton_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLTHDM_lepton_OBJ) $(LLTHDM_lepton_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBTHDM_lepton): $(LIBTHDM_lepton_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBTHDM_lepton) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLTHDM_lepton_LIB): $(LLTHDM_lepton_OBJ) $(LIBTHDM_lepton) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBTHDM_lepton_DEP) $(EXETHDM_lepton_DEP)
ALLSRC += $(LIBTHDM_lepton_SRC) $(EXETHDM_lepton_SRC)
ALLLIB += $(LIBTHDM_lepton)
ALLEXE += $(EXETHDM_lepton_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLTHDM_lepton_DEP)
ALLSRC += $(LLTHDM_lepton_SRC)
ALLLL  += $(LLTHDM_lepton_LIB)
endif
