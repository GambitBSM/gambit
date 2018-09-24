DIR          := models/SingletDM
MODNAME      := SingletDM
SARAH_MODEL  := SingletDM
WITH_$(MODNAME) := yes

SingletDM_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

SingletDM_MK     := \
		$(DIR)/module.mk

SingletDM_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

SingletDM_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

SingletDM_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

SingletDM_INCLUDE_MK := \
		$(SingletDM_SUSY_BETAS_MK) \
		$(SingletDM_SOFT_BETAS_MK)

SingletDM_SLHA_INPUT := \
		$(DIR)/LesHouches.in.SingletDM_generated \
		$(DIR)/LesHouches.in.SingletDM

SingletDM_REFERENCES := \
		$(DIR)/SingletDM_references.tex

SingletDM_GNUPLOT := \
		$(DIR)/SingletDM_plot_rgflow.gnuplot \
		$(DIR)/SingletDM_plot_spectrum.gnuplot

SingletDM_TARBALL := \
		$(MODNAME).tar.gz

LIBSingletDM_SRC := \
		$(DIR)/SingletDM_a_muon.cpp \
		$(DIR)/SingletDM_edm.cpp \
		$(DIR)/SingletDM_effective_couplings.cpp \
		$(DIR)/SingletDM_info.cpp \
		$(DIR)/SingletDM_input_parameters.cpp \
		$(DIR)/SingletDM_mass_eigenstates.cpp \
		$(DIR)/SingletDM_observables.cpp \
		$(DIR)/SingletDM_physical.cpp \
		$(DIR)/SingletDM_slha_io.cpp \
		$(DIR)/SingletDM_soft_parameters.cpp \
		$(DIR)/SingletDM_susy_parameters.cpp \
		$(DIR)/SingletDM_utilities.cpp \
		$(DIR)/SingletDM_weinberg_angle.cpp

EXESingletDM_SRC := \
		$(DIR)/run_SingletDM.cpp \
		$(DIR)/run_cmd_line_SingletDM.cpp \
		$(DIR)/scan_SingletDM.cpp
LLSingletDM_LIB  :=
LLSingletDM_OBJ  :=
LLSingletDM_SRC  := \
		$(DIR)/SingletDM_librarylink.cpp

LLSingletDM_MMA  := \
		$(DIR)/SingletDM_librarylink.m \
		$(DIR)/run_SingletDM.m

LIBSingletDM_HDR := \
		$(DIR)/SingletDM_cxx_diagrams.hpp \
		$(DIR)/SingletDM_a_muon.hpp \
		$(DIR)/SingletDM_convergence_tester.hpp \
		$(DIR)/SingletDM_edm.hpp \
		$(DIR)/SingletDM_effective_couplings.hpp \
		$(DIR)/SingletDM_ewsb_solver.hpp \
		$(DIR)/SingletDM_ewsb_solver_interface.hpp \
		$(DIR)/SingletDM_high_scale_constraint.hpp \
		$(DIR)/SingletDM_info.hpp \
		$(DIR)/SingletDM_initial_guesser.hpp \
		$(DIR)/SingletDM_input_parameters.hpp \
		$(DIR)/SingletDM_low_scale_constraint.hpp \
		$(DIR)/SingletDM_mass_eigenstates.hpp \
		$(DIR)/SingletDM_model.hpp \
		$(DIR)/SingletDM_model_slha.hpp \
		$(DIR)/SingletDM_observables.hpp \
		$(DIR)/SingletDM_physical.hpp \
		$(DIR)/SingletDM_slha_io.hpp \
		$(DIR)/SingletDM_spectrum_generator.hpp \
		$(DIR)/SingletDM_spectrum_generator_interface.hpp \
		$(DIR)/SingletDM_soft_parameters.hpp \
		$(DIR)/SingletDM_susy_parameters.hpp \
		$(DIR)/SingletDM_susy_scale_constraint.hpp \
		$(DIR)/SingletDM_utilities.hpp \
		$(DIR)/SingletDM_weinberg_angle.hpp

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
-include $(SingletDM_SUSY_BETAS_MK)
-include $(SingletDM_SOFT_BETAS_MK)
-include $(SingletDM_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(SingletDM_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(SingletDM_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(SingletDM_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBSingletDM_SRC := $(sort $(LIBSingletDM_SRC))
EXESingletDM_SRC := $(sort $(EXESingletDM_SRC))

LIBSingletDM_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBSingletDM_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBSingletDM_SRC)))

EXESingletDM_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXESingletDM_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXESingletDM_SRC)))

EXESingletDM_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXESingletDM_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXESingletDM_SRC)))

LIBSingletDM_DEP := \
		$(LIBSingletDM_OBJ:.o=.d)

EXESingletDM_DEP := \
		$(EXESingletDM_OBJ:.o=.d)

LLSingletDM_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLSingletDM_SRC)))

LLSingletDM_OBJ  := $(LLSingletDM_SRC:.cpp=.o)
LLSingletDM_LIB  := $(LLSingletDM_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBSingletDM     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_SingletDM := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_SingletDM := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBSingletDM) $(EXESingletDM_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(SingletDM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBSingletDM_SRC) $(SingletDM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBSingletDM_HDR) $(SingletDM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXESingletDM_SRC) $(SingletDM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLSingletDM_SRC) $(SingletDM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLSingletDM_MMA) $(SingletDM_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(SingletDM_MK) $(SingletDM_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(SingletDM_INCLUDE_MK) $(SingletDM_INSTALL_DIR)
ifneq ($(SingletDM_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(SingletDM_SLHA_INPUT) $(SingletDM_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(SingletDM_REFERENCES) $(SingletDM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(SingletDM_GNUPLOT) $(SingletDM_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBSingletDM_DEP)
		-rm -f $(EXESingletDM_DEP)
		-rm -f $(LLSingletDM_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBSingletDM)
		-rm -f $(LLSingletDM_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBSingletDM_OBJ)
		-rm -f $(EXESingletDM_OBJ)
		-rm -f $(LLSingletDM_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXESingletDM_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(SingletDM_TARBALL) \
		$(LIBSingletDM_SRC) $(LIBSingletDM_HDR) \
		$(EXESingletDM_SRC) \
		$(LLSingletDM_SRC) $(LLSingletDM_MMA) \
		$(SingletDM_MK) $(SingletDM_INCLUDE_MK) \
		$(SingletDM_SLHA_INPUT) $(SingletDM_REFERENCES) \
		$(SingletDM_GNUPLOT)

$(LIBSingletDM_SRC) $(LIBSingletDM_HDR) $(EXESingletDM_SRC) $(LLSingletDM_SRC) $(LLSingletDM_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_SingletDM)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_SingletDM): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_SingletDM)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_SingletDM)"
		@echo "Note: to regenerate SingletDM source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_SingletDM)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_SingletDM):
		@true
endif

$(LIBSingletDM_DEP) $(EXESingletDM_DEP) $(LLSingletDM_DEP) $(LIBSingletDM_OBJ) $(EXESingletDM_OBJ) $(LLSingletDM_OBJ) $(LLSingletDM_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBSingletDM_DEP) $(EXESingletDM_DEP) $(LLSingletDM_DEP) $(LIBSingletDM_OBJ) $(EXESingletDM_OBJ) $(LLSingletDM_OBJ) $(LLSingletDM_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLSingletDM_OBJ) $(LLSingletDM_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBSingletDM): $(LIBSingletDM_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBSingletDM) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLSingletDM_LIB): $(LLSingletDM_OBJ) $(LIBSingletDM) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBSingletDM_DEP) $(EXESingletDM_DEP)
ALLSRC += $(LIBSingletDM_SRC) $(EXESingletDM_SRC)
ALLLIB += $(LIBSingletDM)
ALLEXE += $(EXESingletDM_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLSingletDM_DEP)
ALLSRC += $(LLSingletDM_SRC)
ALLLL  += $(LLSingletDM_LIB)
endif
