DIR          := models/THDM_flipped
MODNAME      := THDM_flipped
SARAH_MODEL  := THDM_flipped
WITH_$(MODNAME) := yes

THDM_flipped_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

THDM_flipped_MK     := \
		$(DIR)/module.mk

THDM_flipped_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

THDM_flipped_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

THDM_flipped_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

THDM_flipped_INCLUDE_MK := \
		$(THDM_flipped_SUSY_BETAS_MK) \
		$(THDM_flipped_SOFT_BETAS_MK)

THDM_flipped_SLHA_INPUT := \
		$(DIR)/LesHouches.in.THDM_flipped_generated \


THDM_flipped_REFERENCES := \
		$(DIR)/THDM_flipped_references.tex

THDM_flipped_GNUPLOT := \
		$(DIR)/THDM_flipped_plot_rgflow.gnuplot \
		$(DIR)/THDM_flipped_plot_spectrum.gnuplot

THDM_flipped_TARBALL := \
		$(MODNAME).tar.gz

LIBTHDM_flipped_SRC := \
		$(DIR)/THDM_flipped_a_muon.cpp \
		$(DIR)/THDM_flipped_edm.cpp \
		$(DIR)/THDM_flipped_effective_couplings.cpp \
		$(DIR)/THDM_flipped_info.cpp \
		$(DIR)/THDM_flipped_input_parameters.cpp \
		$(DIR)/THDM_flipped_mass_eigenstates.cpp \
		$(DIR)/THDM_flipped_observables.cpp \
		$(DIR)/THDM_flipped_physical.cpp \
		$(DIR)/THDM_flipped_slha_io.cpp \
		$(DIR)/THDM_flipped_soft_parameters.cpp \
		$(DIR)/THDM_flipped_susy_parameters.cpp \
		$(DIR)/THDM_flipped_utilities.cpp \
		$(DIR)/THDM_flipped_weinberg_angle.cpp

EXETHDM_flipped_SRC := \
		$(DIR)/run_THDM_flipped.cpp \
		$(DIR)/run_cmd_line_THDM_flipped.cpp \
		$(DIR)/scan_THDM_flipped.cpp
LLTHDM_flipped_LIB  :=
LLTHDM_flipped_OBJ  :=
LLTHDM_flipped_SRC  := \
		$(DIR)/THDM_flipped_librarylink.cpp

LLTHDM_flipped_MMA  := \
		$(DIR)/THDM_flipped_librarylink.m \
		$(DIR)/run_THDM_flipped.m

LIBTHDM_flipped_HDR := \
		$(DIR)/THDM_flipped_cxx_diagrams.hpp \
		$(DIR)/THDM_flipped_a_muon.hpp \
		$(DIR)/THDM_flipped_convergence_tester.hpp \
		$(DIR)/THDM_flipped_edm.hpp \
		$(DIR)/THDM_flipped_effective_couplings.hpp \
		$(DIR)/THDM_flipped_ewsb_solver.hpp \
		$(DIR)/THDM_flipped_ewsb_solver_interface.hpp \
		$(DIR)/THDM_flipped_high_scale_constraint.hpp \
		$(DIR)/THDM_flipped_info.hpp \
		$(DIR)/THDM_flipped_initial_guesser.hpp \
		$(DIR)/THDM_flipped_input_parameters.hpp \
		$(DIR)/THDM_flipped_low_scale_constraint.hpp \
		$(DIR)/THDM_flipped_mass_eigenstates.hpp \
		$(DIR)/THDM_flipped_model.hpp \
		$(DIR)/THDM_flipped_model_slha.hpp \
		$(DIR)/THDM_flipped_observables.hpp \
		$(DIR)/THDM_flipped_physical.hpp \
		$(DIR)/THDM_flipped_slha_io.hpp \
		$(DIR)/THDM_flipped_spectrum_generator.hpp \
		$(DIR)/THDM_flipped_spectrum_generator_interface.hpp \
		$(DIR)/THDM_flipped_soft_parameters.hpp \
		$(DIR)/THDM_flipped_susy_parameters.hpp \
		$(DIR)/THDM_flipped_susy_scale_constraint.hpp \
		$(DIR)/THDM_flipped_utilities.hpp \
		$(DIR)/THDM_flipped_weinberg_angle.hpp

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
-include $(THDM_flipped_SUSY_BETAS_MK)
-include $(THDM_flipped_SOFT_BETAS_MK)
-include $(THDM_flipped_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(THDM_flipped_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(THDM_flipped_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(THDM_flipped_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBTHDM_flipped_SRC := $(sort $(LIBTHDM_flipped_SRC))
EXETHDM_flipped_SRC := $(sort $(EXETHDM_flipped_SRC))

LIBTHDM_flipped_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBTHDM_flipped_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBTHDM_flipped_SRC)))

EXETHDM_flipped_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXETHDM_flipped_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXETHDM_flipped_SRC)))

EXETHDM_flipped_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXETHDM_flipped_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXETHDM_flipped_SRC)))

LIBTHDM_flipped_DEP := \
		$(LIBTHDM_flipped_OBJ:.o=.d)

EXETHDM_flipped_DEP := \
		$(EXETHDM_flipped_OBJ:.o=.d)

LLTHDM_flipped_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLTHDM_flipped_SRC)))

LLTHDM_flipped_OBJ  := $(LLTHDM_flipped_SRC:.cpp=.o)
LLTHDM_flipped_LIB  := $(LLTHDM_flipped_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBTHDM_flipped     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_THDM_flipped := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_THDM_flipped := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBTHDM_flipped) $(EXETHDM_flipped_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(THDM_flipped_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBTHDM_flipped_SRC) $(THDM_flipped_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBTHDM_flipped_HDR) $(THDM_flipped_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXETHDM_flipped_SRC) $(THDM_flipped_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLTHDM_flipped_SRC) $(THDM_flipped_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLTHDM_flipped_MMA) $(THDM_flipped_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(THDM_flipped_MK) $(THDM_flipped_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(THDM_flipped_INCLUDE_MK) $(THDM_flipped_INSTALL_DIR)
ifneq ($(THDM_flipped_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(THDM_flipped_SLHA_INPUT) $(THDM_flipped_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(THDM_flipped_REFERENCES) $(THDM_flipped_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(THDM_flipped_GNUPLOT) $(THDM_flipped_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBTHDM_flipped_DEP)
		-rm -f $(EXETHDM_flipped_DEP)
		-rm -f $(LLTHDM_flipped_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBTHDM_flipped)
		-rm -f $(LLTHDM_flipped_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBTHDM_flipped_OBJ)
		-rm -f $(EXETHDM_flipped_OBJ)
		-rm -f $(LLTHDM_flipped_OBJ)

# BEGIN: NOT EXPORTED ##########################################
clean-$(MODNAME)-src:
		-rm -f $(LIBTHDM_flipped_SRC)
		-rm -f $(LIBTHDM_flipped_HDR)
		-rm -f $(EXETHDM_flipped_SRC)
		-rm -f $(LLTHDM_flipped_SRC)
		-rm -f $(LLTHDM_flipped_MMA)
		-rm -f $(METACODE_STAMP_THDM_flipped)
		-rm -f $(THDM_flipped_INCLUDE_MK)
		-rm -f $(THDM_flipped_SLHA_INPUT)
		-rm -f $(THDM_flipped_REFERENCES)
		-rm -f $(THDM_flipped_GNUPLOT)

# the following is commented out in GAMBIT to avoid nuke-all removing the source files
# distclean-$(MODNAME): clean-$(MODNAME)-src
# END:   NOT EXPORTED ##########################################

clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXETHDM_flipped_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(THDM_flipped_TARBALL) \
		$(LIBTHDM_flipped_SRC) $(LIBTHDM_flipped_HDR) \
		$(EXETHDM_flipped_SRC) \
		$(LLTHDM_flipped_SRC) $(LLTHDM_flipped_MMA) \
		$(THDM_flipped_MK) $(THDM_flipped_INCLUDE_MK) \
		$(THDM_flipped_SLHA_INPUT) $(THDM_flipped_REFERENCES) \
		$(THDM_flipped_GNUPLOT)

$(LIBTHDM_flipped_SRC) $(LIBTHDM_flipped_HDR) $(EXETHDM_flipped_SRC) $(LLTHDM_flipped_SRC) $(LLTHDM_flipped_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_THDM_flipped)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_THDM_flipped): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_THDM_flipped)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_THDM_flipped)"
		@echo "Note: to regenerate THDM_flipped source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_THDM_flipped)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_THDM_flipped):
		@true
endif

$(LIBTHDM_flipped_DEP) $(EXETHDM_flipped_DEP) $(LLTHDM_flipped_DEP) $(LIBTHDM_flipped_OBJ) $(EXETHDM_flipped_OBJ) $(LLTHDM_flipped_OBJ) $(LLTHDM_flipped_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBTHDM_flipped_DEP) $(EXETHDM_flipped_DEP) $(LLTHDM_flipped_DEP) $(LIBTHDM_flipped_OBJ) $(EXETHDM_flipped_OBJ) $(LLTHDM_flipped_OBJ) $(LLTHDM_flipped_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLTHDM_flipped_OBJ) $(LLTHDM_flipped_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBTHDM_flipped): $(LIBTHDM_flipped_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBTHDM_flipped) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLTHDM_flipped_LIB): $(LLTHDM_flipped_OBJ) $(LIBTHDM_flipped) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBTHDM_flipped_DEP) $(EXETHDM_flipped_DEP)
ALLSRC += $(LIBTHDM_flipped_SRC) $(EXETHDM_flipped_SRC)
ALLLIB += $(LIBTHDM_flipped)
ALLEXE += $(EXETHDM_flipped_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLTHDM_flipped_DEP)
ALLSRC += $(LLTHDM_flipped_SRC)
ALLLL  += $(LLTHDM_flipped_LIB)
endif
