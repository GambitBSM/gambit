DIR          := models/lowMSSM
MODNAME      := lowMSSM
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes

lowMSSM_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

lowMSSM_MK     := \
		$(DIR)/module.mk

lowMSSM_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

lowMSSM_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

lowMSSM_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

lowMSSM_INCLUDE_MK := \
		$(lowMSSM_SUSY_BETAS_MK) \
		$(lowMSSM_SOFT_BETAS_MK)

lowMSSM_SLHA_INPUT := \
		$(DIR)/LesHouches.in.lowMSSM_generated \
		$(DIR)/LesHouches.in.lowMSSM

lowMSSM_REFERENCES := \
		$(DIR)/lowMSSM_references.tex

lowMSSM_GNUPLOT := \
		$(DIR)/lowMSSM_plot_rgflow.gnuplot \
		$(DIR)/lowMSSM_plot_spectrum.gnuplot

lowMSSM_TARBALL := \
		$(MODNAME).tar.gz

LIBlowMSSM_SRC := \
		$(DIR)/lowMSSM_a_muon.cpp \
		$(DIR)/lowMSSM_edm.cpp \
		$(DIR)/lowMSSM_effective_couplings.cpp \
		$(DIR)/lowMSSM_info.cpp \
		$(DIR)/lowMSSM_input_parameters.cpp \
		$(DIR)/lowMSSM_mass_eigenstates.cpp \
		$(DIR)/lowMSSM_observables.cpp \
		$(DIR)/lowMSSM_physical.cpp \
		$(DIR)/lowMSSM_slha_io.cpp \
		$(DIR)/lowMSSM_soft_parameters.cpp \
		$(DIR)/lowMSSM_susy_parameters.cpp \
		$(DIR)/lowMSSM_utilities.cpp \
		$(DIR)/lowMSSM_weinberg_angle.cpp

EXElowMSSM_SRC := \
		$(DIR)/run_lowMSSM.cpp \
		$(DIR)/run_cmd_line_lowMSSM.cpp \
		$(DIR)/scan_lowMSSM.cpp
LLlowMSSM_LIB  :=
LLlowMSSM_OBJ  :=
LLlowMSSM_SRC  := \
		$(DIR)/lowMSSM_librarylink.cpp

LLlowMSSM_MMA  := \
		$(DIR)/lowMSSM_librarylink.m \
		$(DIR)/run_lowMSSM.m

LIBlowMSSM_HDR := \
		$(DIR)/lowMSSM_cxx_diagrams.hpp \
		$(DIR)/lowMSSM_a_muon.hpp \
		$(DIR)/lowMSSM_convergence_tester.hpp \
		$(DIR)/lowMSSM_edm.hpp \
		$(DIR)/lowMSSM_effective_couplings.hpp \
		$(DIR)/lowMSSM_ewsb_solver.hpp \
		$(DIR)/lowMSSM_ewsb_solver_interface.hpp \
		$(DIR)/lowMSSM_high_scale_constraint.hpp \
		$(DIR)/lowMSSM_info.hpp \
		$(DIR)/lowMSSM_initial_guesser.hpp \
		$(DIR)/lowMSSM_input_parameters.hpp \
		$(DIR)/lowMSSM_low_scale_constraint.hpp \
		$(DIR)/lowMSSM_mass_eigenstates.hpp \
		$(DIR)/lowMSSM_model.hpp \
		$(DIR)/lowMSSM_model_slha.hpp \
		$(DIR)/lowMSSM_observables.hpp \
		$(DIR)/lowMSSM_physical.hpp \
		$(DIR)/lowMSSM_slha_io.hpp \
		$(DIR)/lowMSSM_spectrum_generator.hpp \
		$(DIR)/lowMSSM_spectrum_generator_interface.hpp \
		$(DIR)/lowMSSM_soft_parameters.hpp \
		$(DIR)/lowMSSM_susy_parameters.hpp \
		$(DIR)/lowMSSM_susy_scale_constraint.hpp \
		$(DIR)/lowMSSM_utilities.hpp \
		$(DIR)/lowMSSM_weinberg_angle.hpp

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
-include $(lowMSSM_SUSY_BETAS_MK)
-include $(lowMSSM_SOFT_BETAS_MK)
-include $(lowMSSM_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(lowMSSM_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(lowMSSM_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(lowMSSM_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBlowMSSM_SRC := $(sort $(LIBlowMSSM_SRC))
EXElowMSSM_SRC := $(sort $(EXElowMSSM_SRC))

LIBlowMSSM_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBlowMSSM_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBlowMSSM_SRC)))

EXElowMSSM_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXElowMSSM_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXElowMSSM_SRC)))

EXElowMSSM_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXElowMSSM_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXElowMSSM_SRC)))

LIBlowMSSM_DEP := \
		$(LIBlowMSSM_OBJ:.o=.d)

EXElowMSSM_DEP := \
		$(EXElowMSSM_OBJ:.o=.d)

LLlowMSSM_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLlowMSSM_SRC)))

LLlowMSSM_OBJ  := $(LLlowMSSM_SRC:.cpp=.o)
LLlowMSSM_LIB  := $(LLlowMSSM_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBlowMSSM     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_lowMSSM := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_lowMSSM := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBlowMSSM) $(EXElowMSSM_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(lowMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBlowMSSM_SRC) $(lowMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBlowMSSM_HDR) $(lowMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXElowMSSM_SRC) $(lowMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLlowMSSM_SRC) $(lowMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLlowMSSM_MMA) $(lowMSSM_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(lowMSSM_MK) $(lowMSSM_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(lowMSSM_INCLUDE_MK) $(lowMSSM_INSTALL_DIR)
ifneq ($(lowMSSM_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(lowMSSM_SLHA_INPUT) $(lowMSSM_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(lowMSSM_REFERENCES) $(lowMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(lowMSSM_GNUPLOT) $(lowMSSM_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBlowMSSM_DEP)
		-rm -f $(EXElowMSSM_DEP)
		-rm -f $(LLlowMSSM_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBlowMSSM)
		-rm -f $(LLlowMSSM_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBlowMSSM_OBJ)
		-rm -f $(EXElowMSSM_OBJ)
		-rm -f $(LLlowMSSM_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXElowMSSM_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(lowMSSM_TARBALL) \
		$(LIBlowMSSM_SRC) $(LIBlowMSSM_HDR) \
		$(EXElowMSSM_SRC) \
		$(LLlowMSSM_SRC) $(LLlowMSSM_MMA) \
		$(lowMSSM_MK) $(lowMSSM_INCLUDE_MK) \
		$(lowMSSM_SLHA_INPUT) $(lowMSSM_REFERENCES) \
		$(lowMSSM_GNUPLOT)

$(LIBlowMSSM_SRC) $(LIBlowMSSM_HDR) $(EXElowMSSM_SRC) $(LLlowMSSM_SRC) $(LLlowMSSM_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_lowMSSM)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_lowMSSM): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_lowMSSM)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_lowMSSM)"
		@echo "Note: to regenerate lowMSSM source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_lowMSSM)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_lowMSSM):
		@true
endif

$(LIBlowMSSM_DEP) $(EXElowMSSM_DEP) $(LLlowMSSM_DEP) $(LIBlowMSSM_OBJ) $(EXElowMSSM_OBJ) $(LLlowMSSM_OBJ) $(LLlowMSSM_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBlowMSSM_DEP) $(EXElowMSSM_DEP) $(LLlowMSSM_DEP) $(LIBlowMSSM_OBJ) $(EXElowMSSM_OBJ) $(LLlowMSSM_OBJ) $(LLlowMSSM_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLlowMSSM_OBJ) $(LLlowMSSM_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBlowMSSM): $(LIBlowMSSM_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBlowMSSM) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLlowMSSM_LIB): $(LLlowMSSM_OBJ) $(LIBlowMSSM) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBlowMSSM_DEP) $(EXElowMSSM_DEP)
ALLSRC += $(LIBlowMSSM_SRC) $(EXElowMSSM_SRC)
ALLLIB += $(LIBlowMSSM)
ALLEXE += $(EXElowMSSM_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLlowMSSM_DEP)
ALLSRC += $(LLlowMSSM_SRC)
ALLLL  += $(LLlowMSSM_LIB)
endif
