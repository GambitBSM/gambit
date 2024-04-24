DIR          := models/THDM_I
MODNAME      := THDM_I
SARAH_MODEL  := THDM_I
WITH_$(MODNAME) := yes

THDM_I_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

THDM_I_MK     := \
		$(DIR)/module.mk

THDM_I_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

THDM_I_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

THDM_I_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

THDM_I_INCLUDE_MK := \
		$(THDM_I_SUSY_BETAS_MK) \
		$(THDM_I_SOFT_BETAS_MK)

THDM_I_SLHA_INPUT := \
		$(DIR)/LesHouches.in.THDM_I_generated \


THDM_I_REFERENCES := \
		$(DIR)/THDM_I_references.tex

THDM_I_GNUPLOT := \
		$(DIR)/THDM_I_plot_rgflow.gnuplot \
		$(DIR)/THDM_I_plot_spectrum.gnuplot

THDM_I_TARBALL := \
		$(MODNAME).tar.gz

LIBTHDM_I_SRC := \
		$(DIR)/THDM_I_a_muon.cpp \
		$(DIR)/THDM_I_edm.cpp \
		$(DIR)/THDM_I_effective_couplings.cpp \
		$(DIR)/THDM_I_info.cpp \
		$(DIR)/THDM_I_input_parameters.cpp \
		$(DIR)/THDM_I_mass_eigenstates.cpp \
		$(DIR)/THDM_I_observables.cpp \
		$(DIR)/THDM_I_physical.cpp \
		$(DIR)/THDM_I_slha_io.cpp \
		$(DIR)/THDM_I_soft_parameters.cpp \
		$(DIR)/THDM_I_susy_parameters.cpp \
		$(DIR)/THDM_I_utilities.cpp \
		$(DIR)/THDM_I_weinberg_angle.cpp

EXETHDM_I_SRC := \
		$(DIR)/run_THDM_I.cpp \
		$(DIR)/run_cmd_line_THDM_I.cpp \
		$(DIR)/scan_THDM_I.cpp
LLTHDM_I_LIB  :=
LLTHDM_I_OBJ  :=
LLTHDM_I_SRC  := \
		$(DIR)/THDM_I_librarylink.cpp

LLTHDM_I_MMA  := \
		$(DIR)/THDM_I_librarylink.m \
		$(DIR)/run_THDM_I.m

LIBTHDM_I_HDR := \
		$(DIR)/THDM_I_cxx_diagrams.hpp \
		$(DIR)/THDM_I_a_muon.hpp \
		$(DIR)/THDM_I_convergence_tester.hpp \
		$(DIR)/THDM_I_edm.hpp \
		$(DIR)/THDM_I_effective_couplings.hpp \
		$(DIR)/THDM_I_ewsb_solver.hpp \
		$(DIR)/THDM_I_ewsb_solver_interface.hpp \
		$(DIR)/THDM_I_high_scale_constraint.hpp \
		$(DIR)/THDM_I_info.hpp \
		$(DIR)/THDM_I_initial_guesser.hpp \
		$(DIR)/THDM_I_input_parameters.hpp \
		$(DIR)/THDM_I_low_scale_constraint.hpp \
		$(DIR)/THDM_I_mass_eigenstates.hpp \
		$(DIR)/THDM_I_model.hpp \
		$(DIR)/THDM_I_model_slha.hpp \
		$(DIR)/THDM_I_observables.hpp \
		$(DIR)/THDM_I_physical.hpp \
		$(DIR)/THDM_I_slha_io.hpp \
		$(DIR)/THDM_I_spectrum_generator.hpp \
		$(DIR)/THDM_I_spectrum_generator_interface.hpp \
		$(DIR)/THDM_I_soft_parameters.hpp \
		$(DIR)/THDM_I_susy_parameters.hpp \
		$(DIR)/THDM_I_susy_scale_constraint.hpp \
		$(DIR)/THDM_I_utilities.hpp \
		$(DIR)/THDM_I_weinberg_angle.hpp

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
-include $(THDM_I_SUSY_BETAS_MK)
-include $(THDM_I_SOFT_BETAS_MK)
-include $(THDM_I_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(THDM_I_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(THDM_I_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(THDM_I_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBTHDM_I_SRC := $(sort $(LIBTHDM_I_SRC))
EXETHDM_I_SRC := $(sort $(EXETHDM_I_SRC))

LIBTHDM_I_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBTHDM_I_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBTHDM_I_SRC)))

EXETHDM_I_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXETHDM_I_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXETHDM_I_SRC)))

EXETHDM_I_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXETHDM_I_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXETHDM_I_SRC)))

LIBTHDM_I_DEP := \
		$(LIBTHDM_I_OBJ:.o=.d)

EXETHDM_I_DEP := \
		$(EXETHDM_I_OBJ:.o=.d)

LLTHDM_I_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLTHDM_I_SRC)))

LLTHDM_I_OBJ  := $(LLTHDM_I_SRC:.cpp=.o)
LLTHDM_I_LIB  := $(LLTHDM_I_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBTHDM_I     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_THDM_I := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_THDM_I := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBTHDM_I) $(EXETHDM_I_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(THDM_I_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBTHDM_I_SRC) $(THDM_I_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBTHDM_I_HDR) $(THDM_I_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXETHDM_I_SRC) $(THDM_I_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLTHDM_I_SRC) $(THDM_I_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLTHDM_I_MMA) $(THDM_I_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(THDM_I_MK) $(THDM_I_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(THDM_I_INCLUDE_MK) $(THDM_I_INSTALL_DIR)
ifneq ($(THDM_I_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(THDM_I_SLHA_INPUT) $(THDM_I_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(THDM_I_REFERENCES) $(THDM_I_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(THDM_I_GNUPLOT) $(THDM_I_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBTHDM_I_DEP)
		-rm -f $(EXETHDM_I_DEP)
		-rm -f $(LLTHDM_I_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBTHDM_I)
		-rm -f $(LLTHDM_I_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBTHDM_I_OBJ)
		-rm -f $(EXETHDM_I_OBJ)
		-rm -f $(LLTHDM_I_OBJ)

# BEGIN: NOT EXPORTED ##########################################
clean-$(MODNAME)-src:
		-rm -f $(LIBTHDM_I_SRC)
		-rm -f $(LIBTHDM_I_HDR)
		-rm -f $(EXETHDM_I_SRC)
		-rm -f $(LLTHDM_I_SRC)
		-rm -f $(LLTHDM_I_MMA)
		-rm -f $(METACODE_STAMP_THDM_I)
		-rm -f $(THDM_I_INCLUDE_MK)
		-rm -f $(THDM_I_SLHA_INPUT)
		-rm -f $(THDM_I_REFERENCES)
		-rm -f $(THDM_I_GNUPLOT)

# the following is commented out in GAMBIT to avoid nuke-all removing the source files
# distclean-$(MODNAME): clean-$(MODNAME)-src
# END:   NOT EXPORTED ##########################################

clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXETHDM_I_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(THDM_I_TARBALL) \
		$(LIBTHDM_I_SRC) $(LIBTHDM_I_HDR) \
		$(EXETHDM_I_SRC) \
		$(LLTHDM_I_SRC) $(LLTHDM_I_MMA) \
		$(THDM_I_MK) $(THDM_I_INCLUDE_MK) \
		$(THDM_I_SLHA_INPUT) $(THDM_I_REFERENCES) \
		$(THDM_I_GNUPLOT)

$(LIBTHDM_I_SRC) $(LIBTHDM_I_HDR) $(EXETHDM_I_SRC) $(LLTHDM_I_SRC) $(LLTHDM_I_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_THDM_I)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_THDM_I): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_THDM_I)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_THDM_I)"
		@echo "Note: to regenerate THDM_I source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_THDM_I)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_THDM_I):
		@true
endif

$(LIBTHDM_I_DEP) $(EXETHDM_I_DEP) $(LLTHDM_I_DEP) $(LIBTHDM_I_OBJ) $(EXETHDM_I_OBJ) $(LLTHDM_I_OBJ) $(LLTHDM_I_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBTHDM_I_DEP) $(EXETHDM_I_DEP) $(LLTHDM_I_DEP) $(LIBTHDM_I_OBJ) $(EXETHDM_I_OBJ) $(LLTHDM_I_OBJ) $(LLTHDM_I_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLTHDM_I_OBJ) $(LLTHDM_I_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBTHDM_I): $(LIBTHDM_I_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBTHDM_I) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLTHDM_I_LIB): $(LLTHDM_I_OBJ) $(LIBTHDM_I) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBTHDM_I_DEP) $(EXETHDM_I_DEP)
ALLSRC += $(LIBTHDM_I_SRC) $(EXETHDM_I_SRC)
ALLLIB += $(LIBTHDM_I)
ALLEXE += $(EXETHDM_I_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLTHDM_I_DEP)
ALLSRC += $(LLTHDM_I_SRC)
ALLLL  += $(LLTHDM_I_LIB)
endif
