DIR          := models/THDM_LS
MODNAME      := THDM_LS
SARAH_MODEL  := THDM_LS
WITH_$(MODNAME) := yes

THDM_LS_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

THDM_LS_MK     := \
		$(DIR)/module.mk

THDM_LS_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

THDM_LS_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

THDM_LS_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

THDM_LS_INCLUDE_MK := \
		$(THDM_LS_SUSY_BETAS_MK) \
		$(THDM_LS_SOFT_BETAS_MK)

THDM_LS_SLHA_INPUT := \
		$(DIR)/LesHouches.in.THDM_LS_generated \


THDM_LS_REFERENCES := \
		$(DIR)/THDM_LS_references.tex

THDM_LS_GNUPLOT := \
		$(DIR)/THDM_LS_plot_rgflow.gnuplot \
		$(DIR)/THDM_LS_plot_spectrum.gnuplot

THDM_LS_TARBALL := \
		$(MODNAME).tar.gz

LIBTHDM_LS_SRC := \
		$(DIR)/THDM_LS_a_muon.cpp \
		$(DIR)/THDM_LS_edm.cpp \
		$(DIR)/THDM_LS_effective_couplings.cpp \
		$(DIR)/THDM_LS_info.cpp \
		$(DIR)/THDM_LS_input_parameters.cpp \
		$(DIR)/THDM_LS_mass_eigenstates.cpp \
		$(DIR)/THDM_LS_observables.cpp \
		$(DIR)/THDM_LS_physical.cpp \
		$(DIR)/THDM_LS_slha_io.cpp \
		$(DIR)/THDM_LS_soft_parameters.cpp \
		$(DIR)/THDM_LS_susy_parameters.cpp \
		$(DIR)/THDM_LS_utilities.cpp \
		$(DIR)/THDM_LS_weinberg_angle.cpp

EXETHDM_LS_SRC := \
		$(DIR)/run_THDM_LS.cpp \
		$(DIR)/run_cmd_line_THDM_LS.cpp \
		$(DIR)/scan_THDM_LS.cpp
LLTHDM_LS_LIB  :=
LLTHDM_LS_OBJ  :=
LLTHDM_LS_SRC  := \
		$(DIR)/THDM_LS_librarylink.cpp

LLTHDM_LS_MMA  := \
		$(DIR)/THDM_LS_librarylink.m \
		$(DIR)/run_THDM_LS.m

LIBTHDM_LS_HDR := \
		$(DIR)/THDM_LS_cxx_diagrams.hpp \
		$(DIR)/THDM_LS_a_muon.hpp \
		$(DIR)/THDM_LS_convergence_tester.hpp \
		$(DIR)/THDM_LS_edm.hpp \
		$(DIR)/THDM_LS_effective_couplings.hpp \
		$(DIR)/THDM_LS_ewsb_solver.hpp \
		$(DIR)/THDM_LS_ewsb_solver_interface.hpp \
		$(DIR)/THDM_LS_high_scale_constraint.hpp \
		$(DIR)/THDM_LS_info.hpp \
		$(DIR)/THDM_LS_initial_guesser.hpp \
		$(DIR)/THDM_LS_input_parameters.hpp \
		$(DIR)/THDM_LS_low_scale_constraint.hpp \
		$(DIR)/THDM_LS_mass_eigenstates.hpp \
		$(DIR)/THDM_LS_model.hpp \
		$(DIR)/THDM_LS_model_slha.hpp \
		$(DIR)/THDM_LS_observables.hpp \
		$(DIR)/THDM_LS_physical.hpp \
		$(DIR)/THDM_LS_slha_io.hpp \
		$(DIR)/THDM_LS_spectrum_generator.hpp \
		$(DIR)/THDM_LS_spectrum_generator_interface.hpp \
		$(DIR)/THDM_LS_soft_parameters.hpp \
		$(DIR)/THDM_LS_susy_parameters.hpp \
		$(DIR)/THDM_LS_susy_scale_constraint.hpp \
		$(DIR)/THDM_LS_utilities.hpp \
		$(DIR)/THDM_LS_weinberg_angle.hpp

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
-include $(THDM_LS_SUSY_BETAS_MK)
-include $(THDM_LS_SOFT_BETAS_MK)
-include $(THDM_LS_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(THDM_LS_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(THDM_LS_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(THDM_LS_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBTHDM_LS_SRC := $(sort $(LIBTHDM_LS_SRC))
EXETHDM_LS_SRC := $(sort $(EXETHDM_LS_SRC))

LIBTHDM_LS_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBTHDM_LS_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBTHDM_LS_SRC)))

EXETHDM_LS_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXETHDM_LS_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXETHDM_LS_SRC)))

EXETHDM_LS_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXETHDM_LS_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXETHDM_LS_SRC)))

LIBTHDM_LS_DEP := \
		$(LIBTHDM_LS_OBJ:.o=.d)

EXETHDM_LS_DEP := \
		$(EXETHDM_LS_OBJ:.o=.d)

LLTHDM_LS_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLTHDM_LS_SRC)))

LLTHDM_LS_OBJ  := $(LLTHDM_LS_SRC:.cpp=.o)
LLTHDM_LS_LIB  := $(LLTHDM_LS_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBTHDM_LS     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_THDM_LS := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_THDM_LS := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBTHDM_LS) $(EXETHDM_LS_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(THDM_LS_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBTHDM_LS_SRC) $(THDM_LS_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBTHDM_LS_HDR) $(THDM_LS_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXETHDM_LS_SRC) $(THDM_LS_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLTHDM_LS_SRC) $(THDM_LS_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLTHDM_LS_MMA) $(THDM_LS_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(THDM_LS_MK) $(THDM_LS_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(THDM_LS_INCLUDE_MK) $(THDM_LS_INSTALL_DIR)
ifneq ($(THDM_LS_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(THDM_LS_SLHA_INPUT) $(THDM_LS_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(THDM_LS_REFERENCES) $(THDM_LS_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(THDM_LS_GNUPLOT) $(THDM_LS_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBTHDM_LS_DEP)
		-rm -f $(EXETHDM_LS_DEP)
		-rm -f $(LLTHDM_LS_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBTHDM_LS)
		-rm -f $(LLTHDM_LS_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBTHDM_LS_OBJ)
		-rm -f $(EXETHDM_LS_OBJ)
		-rm -f $(LLTHDM_LS_OBJ)

# BEGIN: NOT EXPORTED ##########################################
clean-$(MODNAME)-src:
		-rm -f $(LIBTHDM_LS_SRC)
		-rm -f $(LIBTHDM_LS_HDR)
		-rm -f $(EXETHDM_LS_SRC)
		-rm -f $(LLTHDM_LS_SRC)
		-rm -f $(LLTHDM_LS_MMA)
		-rm -f $(METACODE_STAMP_THDM_LS)
		-rm -f $(THDM_LS_INCLUDE_MK)
		-rm -f $(THDM_LS_SLHA_INPUT)
		-rm -f $(THDM_LS_REFERENCES)
		-rm -f $(THDM_LS_GNUPLOT)

# the following is commented out in GAMBIT to avoid nuke-all removing the source files
# distclean-$(MODNAME): clean-$(MODNAME)-src
# END:   NOT EXPORTED ##########################################

clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXETHDM_LS_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(THDM_LS_TARBALL) \
		$(LIBTHDM_LS_SRC) $(LIBTHDM_LS_HDR) \
		$(EXETHDM_LS_SRC) \
		$(LLTHDM_LS_SRC) $(LLTHDM_LS_MMA) \
		$(THDM_LS_MK) $(THDM_LS_INCLUDE_MK) \
		$(THDM_LS_SLHA_INPUT) $(THDM_LS_REFERENCES) \
		$(THDM_LS_GNUPLOT)

$(LIBTHDM_LS_SRC) $(LIBTHDM_LS_HDR) $(EXETHDM_LS_SRC) $(LLTHDM_LS_SRC) $(LLTHDM_LS_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_THDM_LS)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_THDM_LS): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_THDM_LS)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_THDM_LS)"
		@echo "Note: to regenerate THDM_LS source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_THDM_LS)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_THDM_LS):
		@true
endif

$(LIBTHDM_LS_DEP) $(EXETHDM_LS_DEP) $(LLTHDM_LS_DEP) $(LIBTHDM_LS_OBJ) $(EXETHDM_LS_OBJ) $(LLTHDM_LS_OBJ) $(LLTHDM_LS_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBTHDM_LS_DEP) $(EXETHDM_LS_DEP) $(LLTHDM_LS_DEP) $(LIBTHDM_LS_OBJ) $(EXETHDM_LS_OBJ) $(LLTHDM_LS_OBJ) $(LLTHDM_LS_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLTHDM_LS_OBJ) $(LLTHDM_LS_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBTHDM_LS): $(LIBTHDM_LS_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBTHDM_LS) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLTHDM_LS_LIB): $(LLTHDM_LS_OBJ) $(LIBTHDM_LS) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBTHDM_LS_DEP) $(EXETHDM_LS_DEP)
ALLSRC += $(LIBTHDM_LS_SRC) $(EXETHDM_LS_SRC)
ALLLIB += $(LIBTHDM_LS)
ALLEXE += $(EXETHDM_LS_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLTHDM_LS_DEP)
ALLSRC += $(LLTHDM_LS_SRC)
ALLLL  += $(LLTHDM_LS_LIB)
endif
