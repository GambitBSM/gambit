DIR          := models/THDM_II
MODNAME      := THDM_II
SARAH_MODEL  := THDM_II
WITH_$(MODNAME) := yes

THDM_II_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

THDM_II_MK     := \
		$(DIR)/module.mk

THDM_II_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

THDM_II_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

THDM_II_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

THDM_II_INCLUDE_MK := \
		$(THDM_II_SUSY_BETAS_MK) \
		$(THDM_II_SOFT_BETAS_MK)

THDM_II_SLHA_INPUT := \
		$(DIR)/LesHouches.in.THDM_II_generated \
		$(DIR)/LesHouches.in.THDMII

THDM_II_REFERENCES := \
		$(DIR)/THDM_II_references.tex

THDM_II_GNUPLOT := \
		$(DIR)/THDM_II_plot_rgflow.gnuplot \
		$(DIR)/THDM_II_plot_spectrum.gnuplot

THDM_II_TARBALL := \
		$(MODNAME).tar.gz

LIBTHDM_II_SRC := \
		$(DIR)/THDM_II_a_muon.cpp \
		$(DIR)/THDM_II_edm.cpp \
		$(DIR)/THDM_II_effective_couplings.cpp \
		$(DIR)/THDM_II_info.cpp \
		$(DIR)/THDM_II_input_parameters.cpp \
		$(DIR)/THDM_II_mass_eigenstates.cpp \
		$(DIR)/THDM_II_observables.cpp \
		$(DIR)/THDM_II_physical.cpp \
		$(DIR)/THDM_II_slha_io.cpp \
		$(DIR)/THDM_II_soft_parameters.cpp \
		$(DIR)/THDM_II_susy_parameters.cpp \
		$(DIR)/THDM_II_utilities.cpp \
		$(DIR)/THDM_II_weinberg_angle.cpp

EXETHDM_II_SRC := \
		$(DIR)/run_THDM_II.cpp \
		$(DIR)/run_cmd_line_THDM_II.cpp \
		$(DIR)/scan_THDM_II.cpp
LLTHDM_II_LIB  :=
LLTHDM_II_OBJ  :=
LLTHDM_II_SRC  := \
		$(DIR)/THDM_II_librarylink.cpp

LLTHDM_II_MMA  := \
		$(DIR)/THDM_II_librarylink.m \
		$(DIR)/run_THDM_II.m

LIBTHDM_II_HDR := \
		$(DIR)/THDM_II_cxx_diagrams.hpp \
		$(DIR)/THDM_II_a_muon.hpp \
		$(DIR)/THDM_II_convergence_tester.hpp \
		$(DIR)/THDM_II_edm.hpp \
		$(DIR)/THDM_II_effective_couplings.hpp \
		$(DIR)/THDM_II_ewsb_solver.hpp \
		$(DIR)/THDM_II_ewsb_solver_interface.hpp \
		$(DIR)/THDM_II_high_scale_constraint.hpp \
		$(DIR)/THDM_II_info.hpp \
		$(DIR)/THDM_II_initial_guesser.hpp \
		$(DIR)/THDM_II_input_parameters.hpp \
		$(DIR)/THDM_II_low_scale_constraint.hpp \
		$(DIR)/THDM_II_mass_eigenstates.hpp \
		$(DIR)/THDM_II_model.hpp \
		$(DIR)/THDM_II_model_slha.hpp \
		$(DIR)/THDM_II_observables.hpp \
		$(DIR)/THDM_II_physical.hpp \
		$(DIR)/THDM_II_slha_io.hpp \
		$(DIR)/THDM_II_spectrum_generator.hpp \
		$(DIR)/THDM_II_spectrum_generator_interface.hpp \
		$(DIR)/THDM_II_soft_parameters.hpp \
		$(DIR)/THDM_II_susy_parameters.hpp \
		$(DIR)/THDM_II_susy_scale_constraint.hpp \
		$(DIR)/THDM_II_utilities.hpp \
		$(DIR)/THDM_II_weinberg_angle.hpp

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
-include $(THDM_II_SUSY_BETAS_MK)
-include $(THDM_II_SOFT_BETAS_MK)
-include $(THDM_II_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(THDM_II_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(THDM_II_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(THDM_II_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBTHDM_II_SRC := $(sort $(LIBTHDM_II_SRC))
EXETHDM_II_SRC := $(sort $(EXETHDM_II_SRC))

LIBTHDM_II_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBTHDM_II_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBTHDM_II_SRC)))

EXETHDM_II_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXETHDM_II_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXETHDM_II_SRC)))

EXETHDM_II_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXETHDM_II_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXETHDM_II_SRC)))

LIBTHDM_II_DEP := \
		$(LIBTHDM_II_OBJ:.o=.d)

EXETHDM_II_DEP := \
		$(EXETHDM_II_OBJ:.o=.d)

LLTHDM_II_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLTHDM_II_SRC)))

LLTHDM_II_OBJ  := $(LLTHDM_II_SRC:.cpp=.o)
LLTHDM_II_LIB  := $(LLTHDM_II_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBTHDM_II     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_THDM_II := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_THDM_II := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBTHDM_II) $(EXETHDM_II_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(THDM_II_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBTHDM_II_SRC) $(THDM_II_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBTHDM_II_HDR) $(THDM_II_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXETHDM_II_SRC) $(THDM_II_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLTHDM_II_SRC) $(THDM_II_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLTHDM_II_MMA) $(THDM_II_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(THDM_II_MK) $(THDM_II_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(THDM_II_INCLUDE_MK) $(THDM_II_INSTALL_DIR)
ifneq ($(THDM_II_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(THDM_II_SLHA_INPUT) $(THDM_II_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(THDM_II_REFERENCES) $(THDM_II_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(THDM_II_GNUPLOT) $(THDM_II_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBTHDM_II_DEP)
		-rm -f $(EXETHDM_II_DEP)
		-rm -f $(LLTHDM_II_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBTHDM_II)
		-rm -f $(LLTHDM_II_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBTHDM_II_OBJ)
		-rm -f $(EXETHDM_II_OBJ)
		-rm -f $(LLTHDM_II_OBJ)

# BEGIN: NOT EXPORTED ##########################################
clean-$(MODNAME)-src:
		-rm -f $(LIBTHDM_II_SRC)
		-rm -f $(LIBTHDM_II_HDR)
		-rm -f $(EXETHDM_II_SRC)
		-rm -f $(LLTHDM_II_SRC)
		-rm -f $(LLTHDM_II_MMA)
		-rm -f $(METACODE_STAMP_THDM_II)
		-rm -f $(THDM_II_INCLUDE_MK)
		-rm -f $(THDM_II_SLHA_INPUT)
		-rm -f $(THDM_II_REFERENCES)
		-rm -f $(THDM_II_GNUPLOT)

# the following is commented out in GAMBIT to avoid nuke-all removing the source files
# distclean-$(MODNAME): clean-$(MODNAME)-src
# END:   NOT EXPORTED ##########################################

clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXETHDM_II_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(THDM_II_TARBALL) \
		$(LIBTHDM_II_SRC) $(LIBTHDM_II_HDR) \
		$(EXETHDM_II_SRC) \
		$(LLTHDM_II_SRC) $(LLTHDM_II_MMA) \
		$(THDM_II_MK) $(THDM_II_INCLUDE_MK) \
		$(THDM_II_SLHA_INPUT) $(THDM_II_REFERENCES) \
		$(THDM_II_GNUPLOT)

$(LIBTHDM_II_SRC) $(LIBTHDM_II_HDR) $(EXETHDM_II_SRC) $(LLTHDM_II_SRC) $(LLTHDM_II_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_THDM_II)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_THDM_II): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_THDM_II)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_THDM_II)"
		@echo "Note: to regenerate THDM_II source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_THDM_II)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_THDM_II):
		@true
endif

$(LIBTHDM_II_DEP) $(EXETHDM_II_DEP) $(LLTHDM_II_DEP) $(LIBTHDM_II_OBJ) $(EXETHDM_II_OBJ) $(LLTHDM_II_OBJ) $(LLTHDM_II_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBTHDM_II_DEP) $(EXETHDM_II_DEP) $(LLTHDM_II_DEP) $(LIBTHDM_II_OBJ) $(EXETHDM_II_OBJ) $(LLTHDM_II_OBJ) $(LLTHDM_II_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLTHDM_II_OBJ) $(LLTHDM_II_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBTHDM_II): $(LIBTHDM_II_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBTHDM_II) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLTHDM_II_LIB): $(LLTHDM_II_OBJ) $(LIBTHDM_II) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBTHDM_II_DEP) $(EXETHDM_II_DEP)
ALLSRC += $(LIBTHDM_II_SRC) $(EXETHDM_II_SRC)
ALLLIB += $(LIBTHDM_II)
ALLEXE += $(EXETHDM_II_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLTHDM_II_DEP)
ALLSRC += $(LLTHDM_II_SRC)
ALLLL  += $(LLTHDM_II_LIB)
endif
