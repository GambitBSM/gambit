DIR          := models/ScalarSingletDM_Z3
MODNAME      := ScalarSingletDM_Z3
SARAH_MODEL  := ScalarSingletDM_Z3
WITH_$(MODNAME) := yes

ScalarSingletDM_Z3_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

ScalarSingletDM_Z3_MK     := \
		$(DIR)/module.mk

ScalarSingletDM_Z3_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

ScalarSingletDM_Z3_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

ScalarSingletDM_Z3_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

ScalarSingletDM_Z3_INCLUDE_MK := \
		$(ScalarSingletDM_Z3_SUSY_BETAS_MK) \
		$(ScalarSingletDM_Z3_SOFT_BETAS_MK)

ScalarSingletDM_Z3_SLHA_INPUT := \
		$(DIR)/LesHouches.in.ScalarSingletDM_Z3_generated \
		$(DIR)/LesHouches.in.ScalarSingletDM_Z3

ScalarSingletDM_Z3_REFERENCES := \
		$(DIR)/ScalarSingletDM_Z3_references.tex

ScalarSingletDM_Z3_GNUPLOT := \
		$(DIR)/ScalarSingletDM_Z3_plot_rgflow.gnuplot \
		$(DIR)/ScalarSingletDM_Z3_plot_spectrum.gnuplot

ScalarSingletDM_Z3_TARBALL := \
		$(MODNAME).tar.gz

LIBScalarSingletDM_Z3_SRC := \
		$(DIR)/ScalarSingletDM_Z3_a_muon.cpp \
		$(DIR)/ScalarSingletDM_Z3_edm.cpp \
		$(DIR)/ScalarSingletDM_Z3_effective_couplings.cpp \
		$(DIR)/ScalarSingletDM_Z3_info.cpp \
		$(DIR)/ScalarSingletDM_Z3_input_parameters.cpp \
		$(DIR)/ScalarSingletDM_Z3_mass_eigenstates.cpp \
		$(DIR)/ScalarSingletDM_Z3_observables.cpp \
		$(DIR)/ScalarSingletDM_Z3_physical.cpp \
		$(DIR)/ScalarSingletDM_Z3_slha_io.cpp \
		$(DIR)/ScalarSingletDM_Z3_soft_parameters.cpp \
		$(DIR)/ScalarSingletDM_Z3_susy_parameters.cpp \
		$(DIR)/ScalarSingletDM_Z3_utilities.cpp \
		$(DIR)/ScalarSingletDM_Z3_weinberg_angle.cpp

EXEScalarSingletDM_Z3_SRC := \
		$(DIR)/run_ScalarSingletDM_Z3.cpp \
		$(DIR)/run_cmd_line_ScalarSingletDM_Z3.cpp \
		$(DIR)/scan_ScalarSingletDM_Z3.cpp
LLScalarSingletDM_Z3_LIB  :=
LLScalarSingletDM_Z3_OBJ  :=
LLScalarSingletDM_Z3_SRC  := \
		$(DIR)/ScalarSingletDM_Z3_librarylink.cpp

LLScalarSingletDM_Z3_MMA  := \
		$(DIR)/ScalarSingletDM_Z3_librarylink.m \
		$(DIR)/run_ScalarSingletDM_Z3.m

LIBScalarSingletDM_Z3_HDR := \
		$(DIR)/ScalarSingletDM_Z3_cxx_diagrams.hpp \
		$(DIR)/ScalarSingletDM_Z3_a_muon.hpp \
		$(DIR)/ScalarSingletDM_Z3_convergence_tester.hpp \
		$(DIR)/ScalarSingletDM_Z3_edm.hpp \
		$(DIR)/ScalarSingletDM_Z3_effective_couplings.hpp \
		$(DIR)/ScalarSingletDM_Z3_ewsb_solver.hpp \
		$(DIR)/ScalarSingletDM_Z3_ewsb_solver_interface.hpp \
		$(DIR)/ScalarSingletDM_Z3_high_scale_constraint.hpp \
		$(DIR)/ScalarSingletDM_Z3_info.hpp \
		$(DIR)/ScalarSingletDM_Z3_initial_guesser.hpp \
		$(DIR)/ScalarSingletDM_Z3_input_parameters.hpp \
		$(DIR)/ScalarSingletDM_Z3_low_scale_constraint.hpp \
		$(DIR)/ScalarSingletDM_Z3_mass_eigenstates.hpp \
		$(DIR)/ScalarSingletDM_Z3_model.hpp \
		$(DIR)/ScalarSingletDM_Z3_model_slha.hpp \
		$(DIR)/ScalarSingletDM_Z3_observables.hpp \
		$(DIR)/ScalarSingletDM_Z3_physical.hpp \
		$(DIR)/ScalarSingletDM_Z3_slha_io.hpp \
		$(DIR)/ScalarSingletDM_Z3_spectrum_generator.hpp \
		$(DIR)/ScalarSingletDM_Z3_spectrum_generator_interface.hpp \
		$(DIR)/ScalarSingletDM_Z3_soft_parameters.hpp \
		$(DIR)/ScalarSingletDM_Z3_susy_parameters.hpp \
		$(DIR)/ScalarSingletDM_Z3_susy_scale_constraint.hpp \
		$(DIR)/ScalarSingletDM_Z3_utilities.hpp \
		$(DIR)/ScalarSingletDM_Z3_weinberg_angle.hpp

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
-include $(ScalarSingletDM_Z3_SUSY_BETAS_MK)
-include $(ScalarSingletDM_Z3_SOFT_BETAS_MK)
-include $(ScalarSingletDM_Z3_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(ScalarSingletDM_Z3_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(ScalarSingletDM_Z3_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(ScalarSingletDM_Z3_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBScalarSingletDM_Z3_SRC := $(sort $(LIBScalarSingletDM_Z3_SRC))
EXEScalarSingletDM_Z3_SRC := $(sort $(EXEScalarSingletDM_Z3_SRC))

LIBScalarSingletDM_Z3_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBScalarSingletDM_Z3_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBScalarSingletDM_Z3_SRC)))

EXEScalarSingletDM_Z3_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXEScalarSingletDM_Z3_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXEScalarSingletDM_Z3_SRC)))

EXEScalarSingletDM_Z3_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXEScalarSingletDM_Z3_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXEScalarSingletDM_Z3_SRC)))

LIBScalarSingletDM_Z3_DEP := \
		$(LIBScalarSingletDM_Z3_OBJ:.o=.d)

EXEScalarSingletDM_Z3_DEP := \
		$(EXEScalarSingletDM_Z3_OBJ:.o=.d)

LLScalarSingletDM_Z3_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLScalarSingletDM_Z3_SRC)))

LLScalarSingletDM_Z3_OBJ  := $(LLScalarSingletDM_Z3_SRC:.cpp=.o)
LLScalarSingletDM_Z3_LIB  := $(LLScalarSingletDM_Z3_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBScalarSingletDM_Z3     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_ScalarSingletDM_Z3 := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_ScalarSingletDM_Z3 := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBScalarSingletDM_Z3) $(EXEScalarSingletDM_Z3_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(ScalarSingletDM_Z3_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBScalarSingletDM_Z3_SRC) $(ScalarSingletDM_Z3_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBScalarSingletDM_Z3_HDR) $(ScalarSingletDM_Z3_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXEScalarSingletDM_Z3_SRC) $(ScalarSingletDM_Z3_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLScalarSingletDM_Z3_SRC) $(ScalarSingletDM_Z3_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLScalarSingletDM_Z3_MMA) $(ScalarSingletDM_Z3_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(ScalarSingletDM_Z3_MK) $(ScalarSingletDM_Z3_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(ScalarSingletDM_Z3_INCLUDE_MK) $(ScalarSingletDM_Z3_INSTALL_DIR)
ifneq ($(ScalarSingletDM_Z3_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(ScalarSingletDM_Z3_SLHA_INPUT) $(ScalarSingletDM_Z3_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(ScalarSingletDM_Z3_REFERENCES) $(ScalarSingletDM_Z3_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(ScalarSingletDM_Z3_GNUPLOT) $(ScalarSingletDM_Z3_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBScalarSingletDM_Z3_DEP)
		-rm -f $(EXEScalarSingletDM_Z3_DEP)
		-rm -f $(LLScalarSingletDM_Z3_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBScalarSingletDM_Z3)
		-rm -f $(LLScalarSingletDM_Z3_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBScalarSingletDM_Z3_OBJ)
		-rm -f $(EXEScalarSingletDM_Z3_OBJ)
		-rm -f $(LLScalarSingletDM_Z3_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXEScalarSingletDM_Z3_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(ScalarSingletDM_Z3_TARBALL) \
		$(LIBScalarSingletDM_Z3_SRC) $(LIBScalarSingletDM_Z3_HDR) \
		$(EXEScalarSingletDM_Z3_SRC) \
		$(LLScalarSingletDM_Z3_SRC) $(LLScalarSingletDM_Z3_MMA) \
		$(ScalarSingletDM_Z3_MK) $(ScalarSingletDM_Z3_INCLUDE_MK) \
		$(ScalarSingletDM_Z3_SLHA_INPUT) $(ScalarSingletDM_Z3_REFERENCES) \
		$(ScalarSingletDM_Z3_GNUPLOT)

$(LIBScalarSingletDM_Z3_SRC) $(LIBScalarSingletDM_Z3_HDR) $(EXEScalarSingletDM_Z3_SRC) $(LLScalarSingletDM_Z3_SRC) $(LLScalarSingletDM_Z3_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_ScalarSingletDM_Z3)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_ScalarSingletDM_Z3): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_ScalarSingletDM_Z3)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_ScalarSingletDM_Z3)"
		@echo "Note: to regenerate ScalarSingletDM_Z3 source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_ScalarSingletDM_Z3)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_ScalarSingletDM_Z3):
		@true
endif

$(LIBScalarSingletDM_Z3_DEP) $(EXEScalarSingletDM_Z3_DEP) $(LLScalarSingletDM_Z3_DEP) $(LIBScalarSingletDM_Z3_OBJ) $(EXEScalarSingletDM_Z3_OBJ) $(LLScalarSingletDM_Z3_OBJ) $(LLScalarSingletDM_Z3_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBScalarSingletDM_Z3_DEP) $(EXEScalarSingletDM_Z3_DEP) $(LLScalarSingletDM_Z3_DEP) $(LIBScalarSingletDM_Z3_OBJ) $(EXEScalarSingletDM_Z3_OBJ) $(LLScalarSingletDM_Z3_OBJ) $(LLScalarSingletDM_Z3_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLScalarSingletDM_Z3_OBJ) $(LLScalarSingletDM_Z3_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBScalarSingletDM_Z3): $(LIBScalarSingletDM_Z3_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBScalarSingletDM_Z3) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLScalarSingletDM_Z3_LIB): $(LLScalarSingletDM_Z3_OBJ) $(LIBScalarSingletDM_Z3) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBScalarSingletDM_Z3_DEP) $(EXEScalarSingletDM_Z3_DEP)
ALLSRC += $(LIBScalarSingletDM_Z3_SRC) $(EXEScalarSingletDM_Z3_SRC)
ALLLIB += $(LIBScalarSingletDM_Z3)
ALLEXE += $(EXEScalarSingletDM_Z3_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLScalarSingletDM_Z3_DEP)
ALLSRC += $(LLScalarSingletDM_Z3_SRC)
ALLLL  += $(LLScalarSingletDM_Z3_LIB)
endif
