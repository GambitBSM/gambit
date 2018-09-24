DIR          := models/MSSMatMGUTEFTHiggs
MODNAME      := MSSMatMGUTEFTHiggs
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes

MSSMatMGUTEFTHiggs_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

MSSMatMGUTEFTHiggs_MK     := \
		$(DIR)/module.mk

MSSMatMGUTEFTHiggs_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

MSSMatMGUTEFTHiggs_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

MSSMatMGUTEFTHiggs_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

MSSMatMGUTEFTHiggs_INCLUDE_MK := \
		$(MSSMatMGUTEFTHiggs_SUSY_BETAS_MK) \
		$(MSSMatMGUTEFTHiggs_SOFT_BETAS_MK)

MSSMatMGUTEFTHiggs_SLHA_INPUT := \
		$(DIR)/LesHouches.in.MSSMatMGUTEFTHiggs_generated \
		$(DIR)/LesHouches.in.MSSMEFTHiggs

MSSMatMGUTEFTHiggs_REFERENCES := \
		$(DIR)/MSSMatMGUTEFTHiggs_references.tex

MSSMatMGUTEFTHiggs_GNUPLOT := \
		$(DIR)/MSSMatMGUTEFTHiggs_plot_rgflow.gnuplot \
		$(DIR)/MSSMatMGUTEFTHiggs_plot_spectrum.gnuplot

MSSMatMGUTEFTHiggs_TARBALL := \
		$(MODNAME).tar.gz

LIBMSSMatMGUTEFTHiggs_SRC := \
		$(DIR)/MSSMatMGUTEFTHiggs_a_muon.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_edm.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_effective_couplings.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_info.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_input_parameters.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mass_eigenstates.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_observables.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_physical.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_slha_io.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_soft_parameters.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_susy_parameters.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_utilities.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_weinberg_angle.cpp

EXEMSSMatMGUTEFTHiggs_SRC := \
		$(DIR)/run_MSSMatMGUTEFTHiggs.cpp \
		$(DIR)/run_cmd_line_MSSMatMGUTEFTHiggs.cpp \
		$(DIR)/scan_MSSMatMGUTEFTHiggs.cpp
LLMSSMatMGUTEFTHiggs_LIB  :=
LLMSSMatMGUTEFTHiggs_OBJ  :=
LLMSSMatMGUTEFTHiggs_SRC  := \
		$(DIR)/MSSMatMGUTEFTHiggs_librarylink.cpp

LLMSSMatMGUTEFTHiggs_MMA  := \
		$(DIR)/MSSMatMGUTEFTHiggs_librarylink.m \
		$(DIR)/run_MSSMatMGUTEFTHiggs.m

LIBMSSMatMGUTEFTHiggs_HDR := \
		$(DIR)/MSSMatMGUTEFTHiggs_cxx_diagrams.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_a_muon.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_convergence_tester.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_edm.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_effective_couplings.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_ewsb_solver.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_ewsb_solver_interface.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_high_scale_constraint.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_info.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_initial_guesser.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_input_parameters.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_low_scale_constraint.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mass_eigenstates.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_model.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_model_slha.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_observables.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_physical.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_slha_io.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_spectrum_generator.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_spectrum_generator_interface.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_soft_parameters.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_susy_parameters.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_susy_scale_constraint.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_utilities.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_weinberg_angle.hpp

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
-include $(MSSMatMGUTEFTHiggs_SUSY_BETAS_MK)
-include $(MSSMatMGUTEFTHiggs_SOFT_BETAS_MK)
-include $(MSSMatMGUTEFTHiggs_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(MSSMatMGUTEFTHiggs_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMatMGUTEFTHiggs_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMatMGUTEFTHiggs_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBMSSMatMGUTEFTHiggs_SRC := $(sort $(LIBMSSMatMGUTEFTHiggs_SRC))
EXEMSSMatMGUTEFTHiggs_SRC := $(sort $(EXEMSSMatMGUTEFTHiggs_SRC))

LIBMSSMatMGUTEFTHiggs_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBMSSMatMGUTEFTHiggs_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBMSSMatMGUTEFTHiggs_SRC)))

EXEMSSMatMGUTEFTHiggs_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXEMSSMatMGUTEFTHiggs_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXEMSSMatMGUTEFTHiggs_SRC)))

EXEMSSMatMGUTEFTHiggs_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXEMSSMatMGUTEFTHiggs_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXEMSSMatMGUTEFTHiggs_SRC)))

LIBMSSMatMGUTEFTHiggs_DEP := \
		$(LIBMSSMatMGUTEFTHiggs_OBJ:.o=.d)

EXEMSSMatMGUTEFTHiggs_DEP := \
		$(EXEMSSMatMGUTEFTHiggs_OBJ:.o=.d)

LLMSSMatMGUTEFTHiggs_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLMSSMatMGUTEFTHiggs_SRC)))

LLMSSMatMGUTEFTHiggs_OBJ  := $(LLMSSMatMGUTEFTHiggs_SRC:.cpp=.o)
LLMSSMatMGUTEFTHiggs_LIB  := $(LLMSSMatMGUTEFTHiggs_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBMSSMatMGUTEFTHiggs     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_MSSMatMGUTEFTHiggs := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_MSSMatMGUTEFTHiggs := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBMSSMatMGUTEFTHiggs) $(EXEMSSMatMGUTEFTHiggs_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(MSSMatMGUTEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMatMGUTEFTHiggs_SRC) $(MSSMatMGUTEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMatMGUTEFTHiggs_HDR) $(MSSMatMGUTEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXEMSSMatMGUTEFTHiggs_SRC) $(MSSMatMGUTEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMatMGUTEFTHiggs_SRC) $(MSSMatMGUTEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMatMGUTEFTHiggs_MMA) $(MSSMatMGUTEFTHiggs_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(MSSMatMGUTEFTHiggs_MK) $(MSSMatMGUTEFTHiggs_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(MSSMatMGUTEFTHiggs_INCLUDE_MK) $(MSSMatMGUTEFTHiggs_INSTALL_DIR)
ifneq ($(MSSMatMGUTEFTHiggs_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(MSSMatMGUTEFTHiggs_SLHA_INPUT) $(MSSMatMGUTEFTHiggs_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(MSSMatMGUTEFTHiggs_REFERENCES) $(MSSMatMGUTEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(MSSMatMGUTEFTHiggs_GNUPLOT) $(MSSMatMGUTEFTHiggs_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBMSSMatMGUTEFTHiggs_DEP)
		-rm -f $(EXEMSSMatMGUTEFTHiggs_DEP)
		-rm -f $(LLMSSMatMGUTEFTHiggs_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBMSSMatMGUTEFTHiggs)
		-rm -f $(LLMSSMatMGUTEFTHiggs_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBMSSMatMGUTEFTHiggs_OBJ)
		-rm -f $(EXEMSSMatMGUTEFTHiggs_OBJ)
		-rm -f $(LLMSSMatMGUTEFTHiggs_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXEMSSMatMGUTEFTHiggs_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(MSSMatMGUTEFTHiggs_TARBALL) \
		$(LIBMSSMatMGUTEFTHiggs_SRC) $(LIBMSSMatMGUTEFTHiggs_HDR) \
		$(EXEMSSMatMGUTEFTHiggs_SRC) \
		$(LLMSSMatMGUTEFTHiggs_SRC) $(LLMSSMatMGUTEFTHiggs_MMA) \
		$(MSSMatMGUTEFTHiggs_MK) $(MSSMatMGUTEFTHiggs_INCLUDE_MK) \
		$(MSSMatMGUTEFTHiggs_SLHA_INPUT) $(MSSMatMGUTEFTHiggs_REFERENCES) \
		$(MSSMatMGUTEFTHiggs_GNUPLOT)

$(LIBMSSMatMGUTEFTHiggs_SRC) $(LIBMSSMatMGUTEFTHiggs_HDR) $(EXEMSSMatMGUTEFTHiggs_SRC) $(LLMSSMatMGUTEFTHiggs_SRC) $(LLMSSMatMGUTEFTHiggs_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_MSSMatMGUTEFTHiggs)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_MSSMatMGUTEFTHiggs): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_MSSMatMGUTEFTHiggs)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_MSSMatMGUTEFTHiggs)"
		@echo "Note: to regenerate MSSMatMGUTEFTHiggs source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_MSSMatMGUTEFTHiggs)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_MSSMatMGUTEFTHiggs):
		@true
endif

$(LIBMSSMatMGUTEFTHiggs_DEP) $(EXEMSSMatMGUTEFTHiggs_DEP) $(LLMSSMatMGUTEFTHiggs_DEP) $(LIBMSSMatMGUTEFTHiggs_OBJ) $(EXEMSSMatMGUTEFTHiggs_OBJ) $(LLMSSMatMGUTEFTHiggs_OBJ) $(LLMSSMatMGUTEFTHiggs_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBMSSMatMGUTEFTHiggs_DEP) $(EXEMSSMatMGUTEFTHiggs_DEP) $(LLMSSMatMGUTEFTHiggs_DEP) $(LIBMSSMatMGUTEFTHiggs_OBJ) $(EXEMSSMatMGUTEFTHiggs_OBJ) $(LLMSSMatMGUTEFTHiggs_OBJ) $(LLMSSMatMGUTEFTHiggs_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLMSSMatMGUTEFTHiggs_OBJ) $(LLMSSMatMGUTEFTHiggs_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBMSSMatMGUTEFTHiggs): $(LIBMSSMatMGUTEFTHiggs_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBMSSMatMGUTEFTHiggs) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLMSSMatMGUTEFTHiggs_LIB): $(LLMSSMatMGUTEFTHiggs_OBJ) $(LIBMSSMatMGUTEFTHiggs) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBMSSMatMGUTEFTHiggs_DEP) $(EXEMSSMatMGUTEFTHiggs_DEP)
ALLSRC += $(LIBMSSMatMGUTEFTHiggs_SRC) $(EXEMSSMatMGUTEFTHiggs_SRC)
ALLLIB += $(LIBMSSMatMGUTEFTHiggs)
ALLEXE += $(EXEMSSMatMGUTEFTHiggs_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLMSSMatMGUTEFTHiggs_DEP)
ALLSRC += $(LLMSSMatMGUTEFTHiggs_SRC)
ALLLL  += $(LLMSSMatMGUTEFTHiggs_LIB)
endif
