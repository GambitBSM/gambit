DIR          := models/CMSSMNoFV
MODNAME      := CMSSMNoFV
SARAH_MODEL  := MSSMNoFV
WITH_$(MODNAME) := yes

CMSSMNoFV_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

CMSSMNoFV_MK     := \
		$(DIR)/module.mk

CMSSMNoFV_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

CMSSMNoFV_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

CMSSMNoFV_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

CMSSMNoFV_INCLUDE_MK := \
		$(CMSSMNoFV_SUSY_BETAS_MK) \
		$(CMSSMNoFV_SOFT_BETAS_MK)

CMSSMNoFV_SLHA_INPUT := \
		$(DIR)/LesHouches.in.CMSSMNoFV_generated \
		$(DIR)/LesHouches.in.CMSSMNoFV

CMSSMNoFV_REFERENCES := \
		$(DIR)/CMSSMNoFV_references.tex

CMSSMNoFV_GNUPLOT := \
		$(DIR)/CMSSMNoFV_plot_rgflow.gnuplot \
		$(DIR)/CMSSMNoFV_plot_spectrum.gnuplot

CMSSMNoFV_TARBALL := \
		$(MODNAME).tar.gz

LIBCMSSMNoFV_SRC := \
		$(DIR)/CMSSMNoFV_a_muon.cpp \
		$(DIR)/CMSSMNoFV_edm.cpp \
		$(DIR)/CMSSMNoFV_effective_couplings.cpp \
		$(DIR)/CMSSMNoFV_info.cpp \
		$(DIR)/CMSSMNoFV_input_parameters.cpp \
		$(DIR)/CMSSMNoFV_mass_eigenstates.cpp \
		$(DIR)/CMSSMNoFV_observables.cpp \
		$(DIR)/CMSSMNoFV_physical.cpp \
		$(DIR)/CMSSMNoFV_slha_io.cpp \
		$(DIR)/CMSSMNoFV_soft_parameters.cpp \
		$(DIR)/CMSSMNoFV_susy_parameters.cpp \
		$(DIR)/CMSSMNoFV_utilities.cpp \
		$(DIR)/CMSSMNoFV_weinberg_angle.cpp

EXECMSSMNoFV_SRC := \
		$(DIR)/run_CMSSMNoFV.cpp \
		$(DIR)/run_cmd_line_CMSSMNoFV.cpp \
		$(DIR)/scan_CMSSMNoFV.cpp
LLCMSSMNoFV_LIB  :=
LLCMSSMNoFV_OBJ  :=
LLCMSSMNoFV_SRC  := \
		$(DIR)/CMSSMNoFV_librarylink.cpp

LLCMSSMNoFV_MMA  := \
		$(DIR)/CMSSMNoFV_librarylink.m \
		$(DIR)/run_CMSSMNoFV.m

LIBCMSSMNoFV_HDR := \
		$(DIR)/CMSSMNoFV_cxx_diagrams.hpp \
		$(DIR)/CMSSMNoFV_a_muon.hpp \
		$(DIR)/CMSSMNoFV_convergence_tester.hpp \
		$(DIR)/CMSSMNoFV_edm.hpp \
		$(DIR)/CMSSMNoFV_effective_couplings.hpp \
		$(DIR)/CMSSMNoFV_ewsb_solver.hpp \
		$(DIR)/CMSSMNoFV_ewsb_solver_interface.hpp \
		$(DIR)/CMSSMNoFV_high_scale_constraint.hpp \
		$(DIR)/CMSSMNoFV_info.hpp \
		$(DIR)/CMSSMNoFV_initial_guesser.hpp \
		$(DIR)/CMSSMNoFV_input_parameters.hpp \
		$(DIR)/CMSSMNoFV_low_scale_constraint.hpp \
		$(DIR)/CMSSMNoFV_mass_eigenstates.hpp \
		$(DIR)/CMSSMNoFV_model.hpp \
		$(DIR)/CMSSMNoFV_model_slha.hpp \
		$(DIR)/CMSSMNoFV_observables.hpp \
		$(DIR)/CMSSMNoFV_physical.hpp \
		$(DIR)/CMSSMNoFV_slha_io.hpp \
		$(DIR)/CMSSMNoFV_spectrum_generator.hpp \
		$(DIR)/CMSSMNoFV_spectrum_generator_interface.hpp \
		$(DIR)/CMSSMNoFV_soft_parameters.hpp \
		$(DIR)/CMSSMNoFV_susy_parameters.hpp \
		$(DIR)/CMSSMNoFV_susy_scale_constraint.hpp \
		$(DIR)/CMSSMNoFV_utilities.hpp \
		$(DIR)/CMSSMNoFV_weinberg_angle.hpp

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
-include $(CMSSMNoFV_SUSY_BETAS_MK)
-include $(CMSSMNoFV_SOFT_BETAS_MK)
-include $(CMSSMNoFV_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(CMSSMNoFV_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(CMSSMNoFV_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(CMSSMNoFV_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBCMSSMNoFV_SRC := $(sort $(LIBCMSSMNoFV_SRC))
EXECMSSMNoFV_SRC := $(sort $(EXECMSSMNoFV_SRC))

LIBCMSSMNoFV_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBCMSSMNoFV_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBCMSSMNoFV_SRC)))

EXECMSSMNoFV_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXECMSSMNoFV_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXECMSSMNoFV_SRC)))

EXECMSSMNoFV_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXECMSSMNoFV_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXECMSSMNoFV_SRC)))

LIBCMSSMNoFV_DEP := \
		$(LIBCMSSMNoFV_OBJ:.o=.d)

EXECMSSMNoFV_DEP := \
		$(EXECMSSMNoFV_OBJ:.o=.d)

LLCMSSMNoFV_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLCMSSMNoFV_SRC)))

LLCMSSMNoFV_OBJ  := $(LLCMSSMNoFV_SRC:.cpp=.o)
LLCMSSMNoFV_LIB  := $(LLCMSSMNoFV_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBCMSSMNoFV     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_CMSSMNoFV := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_CMSSMNoFV := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBCMSSMNoFV) $(EXECMSSMNoFV_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(CMSSMNoFV_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBCMSSMNoFV_SRC) $(CMSSMNoFV_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBCMSSMNoFV_HDR) $(CMSSMNoFV_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXECMSSMNoFV_SRC) $(CMSSMNoFV_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLCMSSMNoFV_SRC) $(CMSSMNoFV_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLCMSSMNoFV_MMA) $(CMSSMNoFV_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(CMSSMNoFV_MK) $(CMSSMNoFV_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(CMSSMNoFV_INCLUDE_MK) $(CMSSMNoFV_INSTALL_DIR)
ifneq ($(CMSSMNoFV_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(CMSSMNoFV_SLHA_INPUT) $(CMSSMNoFV_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(CMSSMNoFV_REFERENCES) $(CMSSMNoFV_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(CMSSMNoFV_GNUPLOT) $(CMSSMNoFV_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBCMSSMNoFV_DEP)
		-rm -f $(EXECMSSMNoFV_DEP)
		-rm -f $(LLCMSSMNoFV_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBCMSSMNoFV)
		-rm -f $(LLCMSSMNoFV_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBCMSSMNoFV_OBJ)
		-rm -f $(EXECMSSMNoFV_OBJ)
		-rm -f $(LLCMSSMNoFV_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXECMSSMNoFV_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(CMSSMNoFV_TARBALL) \
		$(LIBCMSSMNoFV_SRC) $(LIBCMSSMNoFV_HDR) \
		$(EXECMSSMNoFV_SRC) \
		$(LLCMSSMNoFV_SRC) $(LLCMSSMNoFV_MMA) \
		$(CMSSMNoFV_MK) $(CMSSMNoFV_INCLUDE_MK) \
		$(CMSSMNoFV_SLHA_INPUT) $(CMSSMNoFV_REFERENCES) \
		$(CMSSMNoFV_GNUPLOT)

$(LIBCMSSMNoFV_SRC) $(LIBCMSSMNoFV_HDR) $(EXECMSSMNoFV_SRC) $(LLCMSSMNoFV_SRC) $(LLCMSSMNoFV_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_CMSSMNoFV)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_CMSSMNoFV): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_CMSSMNoFV)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_CMSSMNoFV)"
		@echo "Note: to regenerate CMSSMNoFV source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_CMSSMNoFV)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_CMSSMNoFV):
		@true
endif

$(LIBCMSSMNoFV_DEP) $(EXECMSSMNoFV_DEP) $(LLCMSSMNoFV_DEP) $(LIBCMSSMNoFV_OBJ) $(EXECMSSMNoFV_OBJ) $(LLCMSSMNoFV_OBJ) $(LLCMSSMNoFV_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBCMSSMNoFV_DEP) $(EXECMSSMNoFV_DEP) $(LLCMSSMNoFV_DEP) $(LIBCMSSMNoFV_OBJ) $(EXECMSSMNoFV_OBJ) $(LLCMSSMNoFV_OBJ) $(LLCMSSMNoFV_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLCMSSMNoFV_OBJ) $(LLCMSSMNoFV_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBCMSSMNoFV): $(LIBCMSSMNoFV_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBCMSSMNoFV) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLCMSSMNoFV_LIB): $(LLCMSSMNoFV_OBJ) $(LIBCMSSMNoFV) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBCMSSMNoFV_DEP) $(EXECMSSMNoFV_DEP)
ALLSRC += $(LIBCMSSMNoFV_SRC) $(EXECMSSMNoFV_SRC)
ALLLIB += $(LIBCMSSMNoFV)
ALLEXE += $(EXECMSSMNoFV_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLCMSSMNoFV_DEP)
ALLSRC += $(LLCMSSMNoFV_SRC)
ALLLL  += $(LLCMSSMNoFV_LIB)
endif
