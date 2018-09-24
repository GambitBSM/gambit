DIR          := models/NUHMSSM
MODNAME      := NUHMSSM
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes

NUHMSSM_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

NUHMSSM_MK     := \
		$(DIR)/module.mk

NUHMSSM_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

NUHMSSM_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

NUHMSSM_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

NUHMSSM_INCLUDE_MK := \
		$(NUHMSSM_SUSY_BETAS_MK) \
		$(NUHMSSM_SOFT_BETAS_MK)

NUHMSSM_SLHA_INPUT := \
		$(DIR)/LesHouches.in.NUHMSSM_generated \
		$(DIR)/LesHouches.in.NUHMSSM

NUHMSSM_REFERENCES := \
		$(DIR)/NUHMSSM_references.tex

NUHMSSM_GNUPLOT := \
		$(DIR)/NUHMSSM_plot_rgflow.gnuplot \
		$(DIR)/NUHMSSM_plot_spectrum.gnuplot

NUHMSSM_TARBALL := \
		$(MODNAME).tar.gz

LIBNUHMSSM_SRC := \
		$(DIR)/NUHMSSM_a_muon.cpp \
		$(DIR)/NUHMSSM_edm.cpp \
		$(DIR)/NUHMSSM_effective_couplings.cpp \
		$(DIR)/NUHMSSM_info.cpp \
		$(DIR)/NUHMSSM_input_parameters.cpp \
		$(DIR)/NUHMSSM_mass_eigenstates.cpp \
		$(DIR)/NUHMSSM_observables.cpp \
		$(DIR)/NUHMSSM_physical.cpp \
		$(DIR)/NUHMSSM_slha_io.cpp \
		$(DIR)/NUHMSSM_soft_parameters.cpp \
		$(DIR)/NUHMSSM_susy_parameters.cpp \
		$(DIR)/NUHMSSM_utilities.cpp \
		$(DIR)/NUHMSSM_weinberg_angle.cpp

EXENUHMSSM_SRC := \
		$(DIR)/run_NUHMSSM.cpp \
		$(DIR)/run_cmd_line_NUHMSSM.cpp \
		$(DIR)/scan_NUHMSSM.cpp
LLNUHMSSM_LIB  :=
LLNUHMSSM_OBJ  :=
LLNUHMSSM_SRC  := \
		$(DIR)/NUHMSSM_librarylink.cpp

LLNUHMSSM_MMA  := \
		$(DIR)/NUHMSSM_librarylink.m \
		$(DIR)/run_NUHMSSM.m

LIBNUHMSSM_HDR := \
		$(DIR)/NUHMSSM_cxx_diagrams.hpp \
		$(DIR)/NUHMSSM_a_muon.hpp \
		$(DIR)/NUHMSSM_convergence_tester.hpp \
		$(DIR)/NUHMSSM_edm.hpp \
		$(DIR)/NUHMSSM_effective_couplings.hpp \
		$(DIR)/NUHMSSM_ewsb_solver.hpp \
		$(DIR)/NUHMSSM_ewsb_solver_interface.hpp \
		$(DIR)/NUHMSSM_high_scale_constraint.hpp \
		$(DIR)/NUHMSSM_info.hpp \
		$(DIR)/NUHMSSM_initial_guesser.hpp \
		$(DIR)/NUHMSSM_input_parameters.hpp \
		$(DIR)/NUHMSSM_low_scale_constraint.hpp \
		$(DIR)/NUHMSSM_mass_eigenstates.hpp \
		$(DIR)/NUHMSSM_model.hpp \
		$(DIR)/NUHMSSM_model_slha.hpp \
		$(DIR)/NUHMSSM_observables.hpp \
		$(DIR)/NUHMSSM_physical.hpp \
		$(DIR)/NUHMSSM_slha_io.hpp \
		$(DIR)/NUHMSSM_spectrum_generator.hpp \
		$(DIR)/NUHMSSM_spectrum_generator_interface.hpp \
		$(DIR)/NUHMSSM_soft_parameters.hpp \
		$(DIR)/NUHMSSM_susy_parameters.hpp \
		$(DIR)/NUHMSSM_susy_scale_constraint.hpp \
		$(DIR)/NUHMSSM_utilities.hpp \
		$(DIR)/NUHMSSM_weinberg_angle.hpp

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
-include $(NUHMSSM_SUSY_BETAS_MK)
-include $(NUHMSSM_SOFT_BETAS_MK)
-include $(NUHMSSM_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(NUHMSSM_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(NUHMSSM_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(NUHMSSM_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBNUHMSSM_SRC := $(sort $(LIBNUHMSSM_SRC))
EXENUHMSSM_SRC := $(sort $(EXENUHMSSM_SRC))

LIBNUHMSSM_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBNUHMSSM_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBNUHMSSM_SRC)))

EXENUHMSSM_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXENUHMSSM_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXENUHMSSM_SRC)))

EXENUHMSSM_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXENUHMSSM_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXENUHMSSM_SRC)))

LIBNUHMSSM_DEP := \
		$(LIBNUHMSSM_OBJ:.o=.d)

EXENUHMSSM_DEP := \
		$(EXENUHMSSM_OBJ:.o=.d)

LLNUHMSSM_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLNUHMSSM_SRC)))

LLNUHMSSM_OBJ  := $(LLNUHMSSM_SRC:.cpp=.o)
LLNUHMSSM_LIB  := $(LLNUHMSSM_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBNUHMSSM     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_NUHMSSM := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_NUHMSSM := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBNUHMSSM) $(EXENUHMSSM_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(NUHMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBNUHMSSM_SRC) $(NUHMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBNUHMSSM_HDR) $(NUHMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXENUHMSSM_SRC) $(NUHMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLNUHMSSM_SRC) $(NUHMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLNUHMSSM_MMA) $(NUHMSSM_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(NUHMSSM_MK) $(NUHMSSM_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(NUHMSSM_INCLUDE_MK) $(NUHMSSM_INSTALL_DIR)
ifneq ($(NUHMSSM_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(NUHMSSM_SLHA_INPUT) $(NUHMSSM_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(NUHMSSM_REFERENCES) $(NUHMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(NUHMSSM_GNUPLOT) $(NUHMSSM_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBNUHMSSM_DEP)
		-rm -f $(EXENUHMSSM_DEP)
		-rm -f $(LLNUHMSSM_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBNUHMSSM)
		-rm -f $(LLNUHMSSM_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBNUHMSSM_OBJ)
		-rm -f $(EXENUHMSSM_OBJ)
		-rm -f $(LLNUHMSSM_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXENUHMSSM_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(NUHMSSM_TARBALL) \
		$(LIBNUHMSSM_SRC) $(LIBNUHMSSM_HDR) \
		$(EXENUHMSSM_SRC) \
		$(LLNUHMSSM_SRC) $(LLNUHMSSM_MMA) \
		$(NUHMSSM_MK) $(NUHMSSM_INCLUDE_MK) \
		$(NUHMSSM_SLHA_INPUT) $(NUHMSSM_REFERENCES) \
		$(NUHMSSM_GNUPLOT)

$(LIBNUHMSSM_SRC) $(LIBNUHMSSM_HDR) $(EXENUHMSSM_SRC) $(LLNUHMSSM_SRC) $(LLNUHMSSM_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_NUHMSSM)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_NUHMSSM): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_NUHMSSM)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_NUHMSSM)"
		@echo "Note: to regenerate NUHMSSM source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_NUHMSSM)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_NUHMSSM):
		@true
endif

$(LIBNUHMSSM_DEP) $(EXENUHMSSM_DEP) $(LLNUHMSSM_DEP) $(LIBNUHMSSM_OBJ) $(EXENUHMSSM_OBJ) $(LLNUHMSSM_OBJ) $(LLNUHMSSM_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBNUHMSSM_DEP) $(EXENUHMSSM_DEP) $(LLNUHMSSM_DEP) $(LIBNUHMSSM_OBJ) $(EXENUHMSSM_OBJ) $(LLNUHMSSM_OBJ) $(LLNUHMSSM_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLNUHMSSM_OBJ) $(LLNUHMSSM_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBNUHMSSM): $(LIBNUHMSSM_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBNUHMSSM) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLNUHMSSM_LIB): $(LLNUHMSSM_OBJ) $(LIBNUHMSSM) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBNUHMSSM_DEP) $(EXENUHMSSM_DEP)
ALLSRC += $(LIBNUHMSSM_SRC) $(EXENUHMSSM_SRC)
ALLLIB += $(LIBNUHMSSM)
ALLEXE += $(EXENUHMSSM_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLNUHMSSM_DEP)
ALLSRC += $(LLNUHMSSM_SRC)
ALLLL  += $(LLNUHMSSM_LIB)
endif
