DIR          := models/SSM
MODNAME      := SSM
SARAH_MODEL  := SSM
WITH_$(MODNAME) := yes

SSM_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

SSM_MK     := \
		$(DIR)/module.mk

SSM_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

SSM_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

SSM_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

SSM_INCLUDE_MK := \
		$(SSM_SUSY_BETAS_MK) \
		$(SSM_SOFT_BETAS_MK)

SSM_SLHA_INPUT := \
		$(DIR)/LesHouches.in.SSM_generated \
		$(DIR)/LesHouches.in.SSM

SSM_REFERENCES := \
		$(DIR)/SSM_references.tex

SSM_GNUPLOT := \
		$(DIR)/SSM_plot_rgflow.gnuplot \
		$(DIR)/SSM_plot_spectrum.gnuplot

SSM_TARBALL := \
		$(MODNAME).tar.gz

LIBSSM_SRC := \
		$(DIR)/SSM_a_muon.cpp \
		$(DIR)/SSM_edm.cpp \
		$(DIR)/SSM_effective_couplings.cpp \
		$(DIR)/SSM_info.cpp \
		$(DIR)/SSM_input_parameters.cpp \
		$(DIR)/SSM_mass_eigenstates.cpp \
		$(DIR)/SSM_observables.cpp \
		$(DIR)/SSM_physical.cpp \
		$(DIR)/SSM_slha_io.cpp \
		$(DIR)/SSM_soft_parameters.cpp \
		$(DIR)/SSM_susy_parameters.cpp \
		$(DIR)/SSM_utilities.cpp \
		$(DIR)/SSM_weinberg_angle.cpp

EXESSM_SRC := \
		$(DIR)/run_SSM.cpp \
		$(DIR)/run_cmd_line_SSM.cpp \
		$(DIR)/scan_SSM.cpp
LLSSM_LIB  :=
LLSSM_OBJ  :=
LLSSM_SRC  := \
		$(DIR)/SSM_librarylink.cpp

LLSSM_MMA  := \
		$(DIR)/SSM_librarylink.m \
		$(DIR)/run_SSM.m

LIBSSM_HDR := \
		$(DIR)/SSM_cxx_diagrams.hpp \
		$(DIR)/SSM_a_muon.hpp \
		$(DIR)/SSM_convergence_tester.hpp \
		$(DIR)/SSM_edm.hpp \
		$(DIR)/SSM_effective_couplings.hpp \
		$(DIR)/SSM_ewsb_solver.hpp \
		$(DIR)/SSM_ewsb_solver_interface.hpp \
		$(DIR)/SSM_high_scale_constraint.hpp \
		$(DIR)/SSM_info.hpp \
		$(DIR)/SSM_initial_guesser.hpp \
		$(DIR)/SSM_input_parameters.hpp \
		$(DIR)/SSM_low_scale_constraint.hpp \
		$(DIR)/SSM_mass_eigenstates.hpp \
		$(DIR)/SSM_model.hpp \
		$(DIR)/SSM_model_slha.hpp \
		$(DIR)/SSM_observables.hpp \
		$(DIR)/SSM_physical.hpp \
		$(DIR)/SSM_slha_io.hpp \
		$(DIR)/SSM_spectrum_generator.hpp \
		$(DIR)/SSM_spectrum_generator_interface.hpp \
		$(DIR)/SSM_soft_parameters.hpp \
		$(DIR)/SSM_susy_parameters.hpp \
		$(DIR)/SSM_susy_scale_constraint.hpp \
		$(DIR)/SSM_utilities.hpp \
		$(DIR)/SSM_weinberg_angle.hpp

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
-include $(SSM_SUSY_BETAS_MK)
-include $(SSM_SOFT_BETAS_MK)
-include $(SSM_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(SSM_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(SSM_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(SSM_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBSSM_SRC := $(sort $(LIBSSM_SRC))
EXESSM_SRC := $(sort $(EXESSM_SRC))

LIBSSM_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBSSM_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBSSM_SRC)))

EXESSM_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXESSM_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXESSM_SRC)))

EXESSM_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXESSM_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXESSM_SRC)))

LIBSSM_DEP := \
		$(LIBSSM_OBJ:.o=.d)

EXESSM_DEP := \
		$(EXESSM_OBJ:.o=.d)

LLSSM_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLSSM_SRC)))

LLSSM_OBJ  := $(LLSSM_SRC:.cpp=.o)
LLSSM_LIB  := $(LLSSM_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBSSM     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_SSM := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_SSM := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBSSM) $(EXESSM_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(SSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBSSM_SRC) $(SSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBSSM_HDR) $(SSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXESSM_SRC) $(SSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLSSM_SRC) $(SSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLSSM_MMA) $(SSM_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(SSM_MK) $(SSM_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(SSM_INCLUDE_MK) $(SSM_INSTALL_DIR)
ifneq ($(SSM_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(SSM_SLHA_INPUT) $(SSM_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(SSM_REFERENCES) $(SSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(SSM_GNUPLOT) $(SSM_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBSSM_DEP)
		-rm -f $(EXESSM_DEP)
		-rm -f $(LLSSM_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBSSM)
		-rm -f $(LLSSM_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBSSM_OBJ)
		-rm -f $(EXESSM_OBJ)
		-rm -f $(LLSSM_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXESSM_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(SSM_TARBALL) \
		$(LIBSSM_SRC) $(LIBSSM_HDR) \
		$(EXESSM_SRC) \
		$(LLSSM_SRC) $(LLSSM_MMA) \
		$(SSM_MK) $(SSM_INCLUDE_MK) \
		$(SSM_SLHA_INPUT) $(SSM_REFERENCES) \
		$(SSM_GNUPLOT)

$(LIBSSM_SRC) $(LIBSSM_HDR) $(EXESSM_SRC) $(LLSSM_SRC) $(LLSSM_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_SSM)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_SSM): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_SSM)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_SSM)"
		@echo "Note: to regenerate SSM source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_SSM)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_SSM):
		@true
endif

$(LIBSSM_DEP) $(EXESSM_DEP) $(LLSSM_DEP) $(LIBSSM_OBJ) $(EXESSM_OBJ) $(LLSSM_OBJ) $(LLSSM_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBSSM_DEP) $(EXESSM_DEP) $(LLSSM_DEP) $(LIBSSM_OBJ) $(EXESSM_OBJ) $(LLSSM_OBJ) $(LLSSM_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLSSM_OBJ) $(LLSSM_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBSSM): $(LIBSSM_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBSSM) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLSSM_LIB): $(LLSSM_OBJ) $(LIBSSM) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBSSM_DEP) $(EXESSM_DEP)
ALLSRC += $(LIBSSM_SRC) $(EXESSM_SRC)
ALLLIB += $(LIBSSM)
ALLEXE += $(EXESSM_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLSSM_DEP)
ALLSRC += $(LLSSM_SRC)
ALLLL  += $(LLSSM_LIB)
endif
