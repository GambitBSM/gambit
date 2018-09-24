DIR          := models/MSSMNoFV
MODNAME      := MSSMNoFV
SARAH_MODEL  := MSSMNoFV
WITH_$(MODNAME) := yes

MSSMNoFV_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

MSSMNoFV_MK     := \
		$(DIR)/module.mk

MSSMNoFV_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

MSSMNoFV_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

MSSMNoFV_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

MSSMNoFV_INCLUDE_MK := \
		$(MSSMNoFV_SUSY_BETAS_MK) \
		$(MSSMNoFV_SOFT_BETAS_MK)

MSSMNoFV_SLHA_INPUT := \
		$(DIR)/LesHouches.in.MSSMNoFV_generated \
		$(DIR)/LesHouches.in.MSSMNoFV

MSSMNoFV_REFERENCES := \
		$(DIR)/MSSMNoFV_references.tex

MSSMNoFV_GNUPLOT := \
		$(DIR)/MSSMNoFV_plot_rgflow.gnuplot \
		$(DIR)/MSSMNoFV_plot_spectrum.gnuplot

MSSMNoFV_TARBALL := \
		$(MODNAME).tar.gz

LIBMSSMNoFV_SRC := \
		$(DIR)/MSSMNoFV_a_muon.cpp \
		$(DIR)/MSSMNoFV_edm.cpp \
		$(DIR)/MSSMNoFV_effective_couplings.cpp \
		$(DIR)/MSSMNoFV_info.cpp \
		$(DIR)/MSSMNoFV_input_parameters.cpp \
		$(DIR)/MSSMNoFV_mass_eigenstates.cpp \
		$(DIR)/MSSMNoFV_observables.cpp \
		$(DIR)/MSSMNoFV_physical.cpp \
		$(DIR)/MSSMNoFV_slha_io.cpp \
		$(DIR)/MSSMNoFV_soft_parameters.cpp \
		$(DIR)/MSSMNoFV_susy_parameters.cpp \
		$(DIR)/MSSMNoFV_utilities.cpp \
		$(DIR)/MSSMNoFV_weinberg_angle.cpp

EXEMSSMNoFV_SRC := \
		$(DIR)/run_MSSMNoFV.cpp \
		$(DIR)/run_cmd_line_MSSMNoFV.cpp \
		$(DIR)/scan_MSSMNoFV.cpp
LLMSSMNoFV_LIB  :=
LLMSSMNoFV_OBJ  :=
LLMSSMNoFV_SRC  := \
		$(DIR)/MSSMNoFV_librarylink.cpp

LLMSSMNoFV_MMA  := \
		$(DIR)/MSSMNoFV_librarylink.m \
		$(DIR)/run_MSSMNoFV.m

LIBMSSMNoFV_HDR := \
		$(DIR)/MSSMNoFV_cxx_diagrams.hpp \
		$(DIR)/MSSMNoFV_a_muon.hpp \
		$(DIR)/MSSMNoFV_convergence_tester.hpp \
		$(DIR)/MSSMNoFV_edm.hpp \
		$(DIR)/MSSMNoFV_effective_couplings.hpp \
		$(DIR)/MSSMNoFV_ewsb_solver.hpp \
		$(DIR)/MSSMNoFV_ewsb_solver_interface.hpp \
		$(DIR)/MSSMNoFV_high_scale_constraint.hpp \
		$(DIR)/MSSMNoFV_info.hpp \
		$(DIR)/MSSMNoFV_initial_guesser.hpp \
		$(DIR)/MSSMNoFV_input_parameters.hpp \
		$(DIR)/MSSMNoFV_low_scale_constraint.hpp \
		$(DIR)/MSSMNoFV_mass_eigenstates.hpp \
		$(DIR)/MSSMNoFV_model.hpp \
		$(DIR)/MSSMNoFV_model_slha.hpp \
		$(DIR)/MSSMNoFV_observables.hpp \
		$(DIR)/MSSMNoFV_physical.hpp \
		$(DIR)/MSSMNoFV_slha_io.hpp \
		$(DIR)/MSSMNoFV_spectrum_generator.hpp \
		$(DIR)/MSSMNoFV_spectrum_generator_interface.hpp \
		$(DIR)/MSSMNoFV_soft_parameters.hpp \
		$(DIR)/MSSMNoFV_susy_parameters.hpp \
		$(DIR)/MSSMNoFV_susy_scale_constraint.hpp \
		$(DIR)/MSSMNoFV_utilities.hpp \
		$(DIR)/MSSMNoFV_weinberg_angle.hpp

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
-include $(MSSMNoFV_SUSY_BETAS_MK)
-include $(MSSMNoFV_SOFT_BETAS_MK)
-include $(MSSMNoFV_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(MSSMNoFV_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMNoFV_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMNoFV_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBMSSMNoFV_SRC := $(sort $(LIBMSSMNoFV_SRC))
EXEMSSMNoFV_SRC := $(sort $(EXEMSSMNoFV_SRC))

LIBMSSMNoFV_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBMSSMNoFV_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBMSSMNoFV_SRC)))

EXEMSSMNoFV_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXEMSSMNoFV_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXEMSSMNoFV_SRC)))

EXEMSSMNoFV_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXEMSSMNoFV_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXEMSSMNoFV_SRC)))

LIBMSSMNoFV_DEP := \
		$(LIBMSSMNoFV_OBJ:.o=.d)

EXEMSSMNoFV_DEP := \
		$(EXEMSSMNoFV_OBJ:.o=.d)

LLMSSMNoFV_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLMSSMNoFV_SRC)))

LLMSSMNoFV_OBJ  := $(LLMSSMNoFV_SRC:.cpp=.o)
LLMSSMNoFV_LIB  := $(LLMSSMNoFV_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBMSSMNoFV     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_MSSMNoFV := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_MSSMNoFV := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBMSSMNoFV) $(EXEMSSMNoFV_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(MSSMNoFV_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMNoFV_SRC) $(MSSMNoFV_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMNoFV_HDR) $(MSSMNoFV_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXEMSSMNoFV_SRC) $(MSSMNoFV_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMNoFV_SRC) $(MSSMNoFV_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMNoFV_MMA) $(MSSMNoFV_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(MSSMNoFV_MK) $(MSSMNoFV_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(MSSMNoFV_INCLUDE_MK) $(MSSMNoFV_INSTALL_DIR)
ifneq ($(MSSMNoFV_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(MSSMNoFV_SLHA_INPUT) $(MSSMNoFV_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(MSSMNoFV_REFERENCES) $(MSSMNoFV_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(MSSMNoFV_GNUPLOT) $(MSSMNoFV_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBMSSMNoFV_DEP)
		-rm -f $(EXEMSSMNoFV_DEP)
		-rm -f $(LLMSSMNoFV_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBMSSMNoFV)
		-rm -f $(LLMSSMNoFV_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBMSSMNoFV_OBJ)
		-rm -f $(EXEMSSMNoFV_OBJ)
		-rm -f $(LLMSSMNoFV_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXEMSSMNoFV_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(MSSMNoFV_TARBALL) \
		$(LIBMSSMNoFV_SRC) $(LIBMSSMNoFV_HDR) \
		$(EXEMSSMNoFV_SRC) \
		$(LLMSSMNoFV_SRC) $(LLMSSMNoFV_MMA) \
		$(MSSMNoFV_MK) $(MSSMNoFV_INCLUDE_MK) \
		$(MSSMNoFV_SLHA_INPUT) $(MSSMNoFV_REFERENCES) \
		$(MSSMNoFV_GNUPLOT)

$(LIBMSSMNoFV_SRC) $(LIBMSSMNoFV_HDR) $(EXEMSSMNoFV_SRC) $(LLMSSMNoFV_SRC) $(LLMSSMNoFV_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_MSSMNoFV)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_MSSMNoFV): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_MSSMNoFV)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_MSSMNoFV)"
		@echo "Note: to regenerate MSSMNoFV source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_MSSMNoFV)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_MSSMNoFV):
		@true
endif

$(LIBMSSMNoFV_DEP) $(EXEMSSMNoFV_DEP) $(LLMSSMNoFV_DEP) $(LIBMSSMNoFV_OBJ) $(EXEMSSMNoFV_OBJ) $(LLMSSMNoFV_OBJ) $(LLMSSMNoFV_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBMSSMNoFV_DEP) $(EXEMSSMNoFV_DEP) $(LLMSSMNoFV_DEP) $(LIBMSSMNoFV_OBJ) $(EXEMSSMNoFV_OBJ) $(LLMSSMNoFV_OBJ) $(LLMSSMNoFV_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLMSSMNoFV_OBJ) $(LLMSSMNoFV_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBMSSMNoFV): $(LIBMSSMNoFV_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBMSSMNoFV) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLMSSMNoFV_LIB): $(LLMSSMNoFV_OBJ) $(LIBMSSMNoFV) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBMSSMNoFV_DEP) $(EXEMSSMNoFV_DEP)
ALLSRC += $(LIBMSSMNoFV_SRC) $(EXEMSSMNoFV_SRC)
ALLLIB += $(LIBMSSMNoFV)
ALLEXE += $(EXEMSSMNoFV_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLMSSMNoFV_DEP)
ALLSRC += $(LLMSSMNoFV_SRC)
ALLLL  += $(LLMSSMNoFV_LIB)
endif
