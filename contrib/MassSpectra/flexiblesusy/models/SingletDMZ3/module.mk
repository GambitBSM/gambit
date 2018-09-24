DIR          := models/SingletDMZ3
MODNAME      := SingletDMZ3
SARAH_MODEL  := SingletDMZ3
WITH_$(MODNAME) := yes

SingletDMZ3_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

SingletDMZ3_MK     := \
		$(DIR)/module.mk

SingletDMZ3_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

SingletDMZ3_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

SingletDMZ3_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

SingletDMZ3_INCLUDE_MK := \
		$(SingletDMZ3_SUSY_BETAS_MK) \
		$(SingletDMZ3_SOFT_BETAS_MK)

SingletDMZ3_SLHA_INPUT := \
		$(DIR)/LesHouches.in.SingletDMZ3_generated \
		$(DIR)/LesHouches.in.SingletDMZ3

SingletDMZ3_REFERENCES := \
		$(DIR)/SingletDMZ3_references.tex

SingletDMZ3_GNUPLOT := \
		$(DIR)/SingletDMZ3_plot_rgflow.gnuplot \
		$(DIR)/SingletDMZ3_plot_spectrum.gnuplot

SingletDMZ3_TARBALL := \
		$(MODNAME).tar.gz

LIBSingletDMZ3_SRC := \
		$(DIR)/SingletDMZ3_a_muon.cpp \
		$(DIR)/SingletDMZ3_edm.cpp \
		$(DIR)/SingletDMZ3_effective_couplings.cpp \
		$(DIR)/SingletDMZ3_info.cpp \
		$(DIR)/SingletDMZ3_input_parameters.cpp \
		$(DIR)/SingletDMZ3_mass_eigenstates.cpp \
		$(DIR)/SingletDMZ3_observables.cpp \
		$(DIR)/SingletDMZ3_physical.cpp \
		$(DIR)/SingletDMZ3_slha_io.cpp \
		$(DIR)/SingletDMZ3_soft_parameters.cpp \
		$(DIR)/SingletDMZ3_susy_parameters.cpp \
		$(DIR)/SingletDMZ3_utilities.cpp \
		$(DIR)/SingletDMZ3_weinberg_angle.cpp

EXESingletDMZ3_SRC := \
		$(DIR)/run_SingletDMZ3.cpp \
		$(DIR)/run_cmd_line_SingletDMZ3.cpp \
		$(DIR)/scan_SingletDMZ3.cpp
LLSingletDMZ3_LIB  :=
LLSingletDMZ3_OBJ  :=
LLSingletDMZ3_SRC  := \
		$(DIR)/SingletDMZ3_librarylink.cpp

LLSingletDMZ3_MMA  := \
		$(DIR)/SingletDMZ3_librarylink.m \
		$(DIR)/run_SingletDMZ3.m

LIBSingletDMZ3_HDR := \
		$(DIR)/SingletDMZ3_cxx_diagrams.hpp \
		$(DIR)/SingletDMZ3_a_muon.hpp \
		$(DIR)/SingletDMZ3_convergence_tester.hpp \
		$(DIR)/SingletDMZ3_edm.hpp \
		$(DIR)/SingletDMZ3_effective_couplings.hpp \
		$(DIR)/SingletDMZ3_ewsb_solver.hpp \
		$(DIR)/SingletDMZ3_ewsb_solver_interface.hpp \
		$(DIR)/SingletDMZ3_high_scale_constraint.hpp \
		$(DIR)/SingletDMZ3_info.hpp \
		$(DIR)/SingletDMZ3_initial_guesser.hpp \
		$(DIR)/SingletDMZ3_input_parameters.hpp \
		$(DIR)/SingletDMZ3_low_scale_constraint.hpp \
		$(DIR)/SingletDMZ3_mass_eigenstates.hpp \
		$(DIR)/SingletDMZ3_model.hpp \
		$(DIR)/SingletDMZ3_model_slha.hpp \
		$(DIR)/SingletDMZ3_observables.hpp \
		$(DIR)/SingletDMZ3_physical.hpp \
		$(DIR)/SingletDMZ3_slha_io.hpp \
		$(DIR)/SingletDMZ3_spectrum_generator.hpp \
		$(DIR)/SingletDMZ3_spectrum_generator_interface.hpp \
		$(DIR)/SingletDMZ3_soft_parameters.hpp \
		$(DIR)/SingletDMZ3_susy_parameters.hpp \
		$(DIR)/SingletDMZ3_susy_scale_constraint.hpp \
		$(DIR)/SingletDMZ3_utilities.hpp \
		$(DIR)/SingletDMZ3_weinberg_angle.hpp

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
-include $(SingletDMZ3_SUSY_BETAS_MK)
-include $(SingletDMZ3_SOFT_BETAS_MK)
-include $(SingletDMZ3_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(SingletDMZ3_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(SingletDMZ3_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(SingletDMZ3_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBSingletDMZ3_SRC := $(sort $(LIBSingletDMZ3_SRC))
EXESingletDMZ3_SRC := $(sort $(EXESingletDMZ3_SRC))

LIBSingletDMZ3_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBSingletDMZ3_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBSingletDMZ3_SRC)))

EXESingletDMZ3_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXESingletDMZ3_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXESingletDMZ3_SRC)))

EXESingletDMZ3_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXESingletDMZ3_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXESingletDMZ3_SRC)))

LIBSingletDMZ3_DEP := \
		$(LIBSingletDMZ3_OBJ:.o=.d)

EXESingletDMZ3_DEP := \
		$(EXESingletDMZ3_OBJ:.o=.d)

LLSingletDMZ3_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLSingletDMZ3_SRC)))

LLSingletDMZ3_OBJ  := $(LLSingletDMZ3_SRC:.cpp=.o)
LLSingletDMZ3_LIB  := $(LLSingletDMZ3_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBSingletDMZ3     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_SingletDMZ3 := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_SingletDMZ3 := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBSingletDMZ3) $(EXESingletDMZ3_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(SingletDMZ3_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBSingletDMZ3_SRC) $(SingletDMZ3_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBSingletDMZ3_HDR) $(SingletDMZ3_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXESingletDMZ3_SRC) $(SingletDMZ3_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLSingletDMZ3_SRC) $(SingletDMZ3_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLSingletDMZ3_MMA) $(SingletDMZ3_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(SingletDMZ3_MK) $(SingletDMZ3_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(SingletDMZ3_INCLUDE_MK) $(SingletDMZ3_INSTALL_DIR)
ifneq ($(SingletDMZ3_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(SingletDMZ3_SLHA_INPUT) $(SingletDMZ3_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(SingletDMZ3_REFERENCES) $(SingletDMZ3_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(SingletDMZ3_GNUPLOT) $(SingletDMZ3_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBSingletDMZ3_DEP)
		-rm -f $(EXESingletDMZ3_DEP)
		-rm -f $(LLSingletDMZ3_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBSingletDMZ3)
		-rm -f $(LLSingletDMZ3_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBSingletDMZ3_OBJ)
		-rm -f $(EXESingletDMZ3_OBJ)
		-rm -f $(LLSingletDMZ3_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXESingletDMZ3_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(SingletDMZ3_TARBALL) \
		$(LIBSingletDMZ3_SRC) $(LIBSingletDMZ3_HDR) \
		$(EXESingletDMZ3_SRC) \
		$(LLSingletDMZ3_SRC) $(LLSingletDMZ3_MMA) \
		$(SingletDMZ3_MK) $(SingletDMZ3_INCLUDE_MK) \
		$(SingletDMZ3_SLHA_INPUT) $(SingletDMZ3_REFERENCES) \
		$(SingletDMZ3_GNUPLOT)

$(LIBSingletDMZ3_SRC) $(LIBSingletDMZ3_HDR) $(EXESingletDMZ3_SRC) $(LLSingletDMZ3_SRC) $(LLSingletDMZ3_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_SingletDMZ3)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_SingletDMZ3): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_SingletDMZ3)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_SingletDMZ3)"
		@echo "Note: to regenerate SingletDMZ3 source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_SingletDMZ3)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_SingletDMZ3):
		@true
endif

$(LIBSingletDMZ3_DEP) $(EXESingletDMZ3_DEP) $(LLSingletDMZ3_DEP) $(LIBSingletDMZ3_OBJ) $(EXESingletDMZ3_OBJ) $(LLSingletDMZ3_OBJ) $(LLSingletDMZ3_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBSingletDMZ3_DEP) $(EXESingletDMZ3_DEP) $(LLSingletDMZ3_DEP) $(LIBSingletDMZ3_OBJ) $(EXESingletDMZ3_OBJ) $(LLSingletDMZ3_OBJ) $(LLSingletDMZ3_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLSingletDMZ3_OBJ) $(LLSingletDMZ3_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBSingletDMZ3): $(LIBSingletDMZ3_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBSingletDMZ3) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLSingletDMZ3_LIB): $(LLSingletDMZ3_OBJ) $(LIBSingletDMZ3) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBSingletDMZ3_DEP) $(EXESingletDMZ3_DEP)
ALLSRC += $(LIBSingletDMZ3_SRC) $(EXESingletDMZ3_SRC)
ALLLIB += $(LIBSingletDMZ3)
ALLEXE += $(EXESingletDMZ3_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLSingletDMZ3_DEP)
ALLSRC += $(LLSingletDMZ3_SRC)
ALLLL  += $(LLSingletDMZ3_LIB)
endif
