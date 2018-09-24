DIR          := models/MSSMEFTHiggs
MODNAME      := MSSMEFTHiggs
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes

MSSMEFTHiggs_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

MSSMEFTHiggs_MK     := \
		$(DIR)/module.mk

MSSMEFTHiggs_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

MSSMEFTHiggs_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

MSSMEFTHiggs_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

MSSMEFTHiggs_INCLUDE_MK := \
		$(MSSMEFTHiggs_SUSY_BETAS_MK) \
		$(MSSMEFTHiggs_SOFT_BETAS_MK)

MSSMEFTHiggs_SLHA_INPUT := \
		$(DIR)/LesHouches.in.MSSMEFTHiggs_generated \
		$(DIR)/LesHouches.in.MSSMEFTHiggs

MSSMEFTHiggs_REFERENCES := \
		$(DIR)/MSSMEFTHiggs_references.tex

MSSMEFTHiggs_GNUPLOT := \
		$(DIR)/MSSMEFTHiggs_plot_rgflow.gnuplot \
		$(DIR)/MSSMEFTHiggs_plot_spectrum.gnuplot

MSSMEFTHiggs_TARBALL := \
		$(MODNAME).tar.gz

LIBMSSMEFTHiggs_SRC := \
		$(DIR)/MSSMEFTHiggs_a_muon.cpp \
		$(DIR)/MSSMEFTHiggs_edm.cpp \
		$(DIR)/MSSMEFTHiggs_effective_couplings.cpp \
		$(DIR)/MSSMEFTHiggs_info.cpp \
		$(DIR)/MSSMEFTHiggs_input_parameters.cpp \
		$(DIR)/MSSMEFTHiggs_mass_eigenstates.cpp \
		$(DIR)/MSSMEFTHiggs_observables.cpp \
		$(DIR)/MSSMEFTHiggs_physical.cpp \
		$(DIR)/MSSMEFTHiggs_slha_io.cpp \
		$(DIR)/MSSMEFTHiggs_soft_parameters.cpp \
		$(DIR)/MSSMEFTHiggs_susy_parameters.cpp \
		$(DIR)/MSSMEFTHiggs_utilities.cpp \
		$(DIR)/MSSMEFTHiggs_weinberg_angle.cpp

EXEMSSMEFTHiggs_SRC := \
		$(DIR)/run_MSSMEFTHiggs.cpp \
		$(DIR)/run_cmd_line_MSSMEFTHiggs.cpp \
		$(DIR)/scan_MSSMEFTHiggs.cpp
LLMSSMEFTHiggs_LIB  :=
LLMSSMEFTHiggs_OBJ  :=
LLMSSMEFTHiggs_SRC  := \
		$(DIR)/MSSMEFTHiggs_librarylink.cpp

LLMSSMEFTHiggs_MMA  := \
		$(DIR)/MSSMEFTHiggs_librarylink.m \
		$(DIR)/run_MSSMEFTHiggs.m

LIBMSSMEFTHiggs_HDR := \
		$(DIR)/MSSMEFTHiggs_cxx_diagrams.hpp \
		$(DIR)/MSSMEFTHiggs_a_muon.hpp \
		$(DIR)/MSSMEFTHiggs_convergence_tester.hpp \
		$(DIR)/MSSMEFTHiggs_edm.hpp \
		$(DIR)/MSSMEFTHiggs_effective_couplings.hpp \
		$(DIR)/MSSMEFTHiggs_ewsb_solver.hpp \
		$(DIR)/MSSMEFTHiggs_ewsb_solver_interface.hpp \
		$(DIR)/MSSMEFTHiggs_high_scale_constraint.hpp \
		$(DIR)/MSSMEFTHiggs_info.hpp \
		$(DIR)/MSSMEFTHiggs_initial_guesser.hpp \
		$(DIR)/MSSMEFTHiggs_input_parameters.hpp \
		$(DIR)/MSSMEFTHiggs_low_scale_constraint.hpp \
		$(DIR)/MSSMEFTHiggs_mass_eigenstates.hpp \
		$(DIR)/MSSMEFTHiggs_model.hpp \
		$(DIR)/MSSMEFTHiggs_model_slha.hpp \
		$(DIR)/MSSMEFTHiggs_observables.hpp \
		$(DIR)/MSSMEFTHiggs_physical.hpp \
		$(DIR)/MSSMEFTHiggs_slha_io.hpp \
		$(DIR)/MSSMEFTHiggs_spectrum_generator.hpp \
		$(DIR)/MSSMEFTHiggs_spectrum_generator_interface.hpp \
		$(DIR)/MSSMEFTHiggs_soft_parameters.hpp \
		$(DIR)/MSSMEFTHiggs_susy_parameters.hpp \
		$(DIR)/MSSMEFTHiggs_susy_scale_constraint.hpp \
		$(DIR)/MSSMEFTHiggs_utilities.hpp \
		$(DIR)/MSSMEFTHiggs_weinberg_angle.hpp

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
-include $(MSSMEFTHiggs_SUSY_BETAS_MK)
-include $(MSSMEFTHiggs_SOFT_BETAS_MK)
-include $(MSSMEFTHiggs_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(MSSMEFTHiggs_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMEFTHiggs_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMEFTHiggs_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBMSSMEFTHiggs_SRC := $(sort $(LIBMSSMEFTHiggs_SRC))
EXEMSSMEFTHiggs_SRC := $(sort $(EXEMSSMEFTHiggs_SRC))

LIBMSSMEFTHiggs_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBMSSMEFTHiggs_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBMSSMEFTHiggs_SRC)))

EXEMSSMEFTHiggs_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXEMSSMEFTHiggs_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXEMSSMEFTHiggs_SRC)))

EXEMSSMEFTHiggs_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXEMSSMEFTHiggs_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXEMSSMEFTHiggs_SRC)))

LIBMSSMEFTHiggs_DEP := \
		$(LIBMSSMEFTHiggs_OBJ:.o=.d)

EXEMSSMEFTHiggs_DEP := \
		$(EXEMSSMEFTHiggs_OBJ:.o=.d)

LLMSSMEFTHiggs_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLMSSMEFTHiggs_SRC)))

LLMSSMEFTHiggs_OBJ  := $(LLMSSMEFTHiggs_SRC:.cpp=.o)
LLMSSMEFTHiggs_LIB  := $(LLMSSMEFTHiggs_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBMSSMEFTHiggs     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_MSSMEFTHiggs := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_MSSMEFTHiggs := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBMSSMEFTHiggs) $(EXEMSSMEFTHiggs_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(MSSMEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMEFTHiggs_SRC) $(MSSMEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMEFTHiggs_HDR) $(MSSMEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXEMSSMEFTHiggs_SRC) $(MSSMEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMEFTHiggs_SRC) $(MSSMEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMEFTHiggs_MMA) $(MSSMEFTHiggs_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(MSSMEFTHiggs_MK) $(MSSMEFTHiggs_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(MSSMEFTHiggs_INCLUDE_MK) $(MSSMEFTHiggs_INSTALL_DIR)
ifneq ($(MSSMEFTHiggs_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(MSSMEFTHiggs_SLHA_INPUT) $(MSSMEFTHiggs_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(MSSMEFTHiggs_REFERENCES) $(MSSMEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(MSSMEFTHiggs_GNUPLOT) $(MSSMEFTHiggs_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBMSSMEFTHiggs_DEP)
		-rm -f $(EXEMSSMEFTHiggs_DEP)
		-rm -f $(LLMSSMEFTHiggs_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBMSSMEFTHiggs)
		-rm -f $(LLMSSMEFTHiggs_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBMSSMEFTHiggs_OBJ)
		-rm -f $(EXEMSSMEFTHiggs_OBJ)
		-rm -f $(LLMSSMEFTHiggs_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXEMSSMEFTHiggs_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(MSSMEFTHiggs_TARBALL) \
		$(LIBMSSMEFTHiggs_SRC) $(LIBMSSMEFTHiggs_HDR) \
		$(EXEMSSMEFTHiggs_SRC) \
		$(LLMSSMEFTHiggs_SRC) $(LLMSSMEFTHiggs_MMA) \
		$(MSSMEFTHiggs_MK) $(MSSMEFTHiggs_INCLUDE_MK) \
		$(MSSMEFTHiggs_SLHA_INPUT) $(MSSMEFTHiggs_REFERENCES) \
		$(MSSMEFTHiggs_GNUPLOT)

$(LIBMSSMEFTHiggs_SRC) $(LIBMSSMEFTHiggs_HDR) $(EXEMSSMEFTHiggs_SRC) $(LLMSSMEFTHiggs_SRC) $(LLMSSMEFTHiggs_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_MSSMEFTHiggs)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_MSSMEFTHiggs): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_MSSMEFTHiggs)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_MSSMEFTHiggs)"
		@echo "Note: to regenerate MSSMEFTHiggs source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_MSSMEFTHiggs)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_MSSMEFTHiggs):
		@true
endif

$(LIBMSSMEFTHiggs_DEP) $(EXEMSSMEFTHiggs_DEP) $(LLMSSMEFTHiggs_DEP) $(LIBMSSMEFTHiggs_OBJ) $(EXEMSSMEFTHiggs_OBJ) $(LLMSSMEFTHiggs_OBJ) $(LLMSSMEFTHiggs_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBMSSMEFTHiggs_DEP) $(EXEMSSMEFTHiggs_DEP) $(LLMSSMEFTHiggs_DEP) $(LIBMSSMEFTHiggs_OBJ) $(EXEMSSMEFTHiggs_OBJ) $(LLMSSMEFTHiggs_OBJ) $(LLMSSMEFTHiggs_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLMSSMEFTHiggs_OBJ) $(LLMSSMEFTHiggs_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBMSSMEFTHiggs): $(LIBMSSMEFTHiggs_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBMSSMEFTHiggs) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLMSSMEFTHiggs_LIB): $(LLMSSMEFTHiggs_OBJ) $(LIBMSSMEFTHiggs) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBMSSMEFTHiggs_DEP) $(EXEMSSMEFTHiggs_DEP)
ALLSRC += $(LIBMSSMEFTHiggs_SRC) $(EXEMSSMEFTHiggs_SRC)
ALLLIB += $(LIBMSSMEFTHiggs)
ALLEXE += $(EXEMSSMEFTHiggs_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLMSSMEFTHiggs_DEP)
ALLSRC += $(LLMSSMEFTHiggs_SRC)
ALLLL  += $(LLMSSMEFTHiggs_LIB)
endif
