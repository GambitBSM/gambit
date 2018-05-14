DIR          := models/MSSMatMSUSYEFTHiggs
MODNAME      := MSSMatMSUSYEFTHiggs
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes

MSSMatMSUSYEFTHiggs_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

MSSMatMSUSYEFTHiggs_MK     := \
		$(DIR)/module.mk

MSSMatMSUSYEFTHiggs_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

MSSMatMSUSYEFTHiggs_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

MSSMatMSUSYEFTHiggs_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

MSSMatMSUSYEFTHiggs_INCLUDE_MK := \
		$(MSSMatMSUSYEFTHiggs_SUSY_BETAS_MK) \
		$(MSSMatMSUSYEFTHiggs_SOFT_BETAS_MK)

MSSMatMSUSYEFTHiggs_SLHA_INPUT := \
		$(DIR)/LesHouches.in.MSSMatMSUSYEFTHiggs_generated \
		$(DIR)/LesHouches.in.MSSMEFTHiggs

MSSMatMSUSYEFTHiggs_REFERENCES := \
		$(DIR)/MSSMatMSUSYEFTHiggs_references.tex

MSSMatMSUSYEFTHiggs_GNUPLOT := \
		$(DIR)/MSSMatMSUSYEFTHiggs_plot_rgflow.gnuplot \
		$(DIR)/MSSMatMSUSYEFTHiggs_plot_spectrum.gnuplot

MSSMatMSUSYEFTHiggs_TARBALL := \
		$(MODNAME).tar.gz

LIBMSSMatMSUSYEFTHiggs_SRC := \
		$(DIR)/MSSMatMSUSYEFTHiggs_a_muon.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_edm.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_effective_couplings.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_info.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_input_parameters.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mass_eigenstates.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_observables.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_physical.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_slha_io.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_soft_parameters.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_susy_parameters.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_utilities.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_weinberg_angle.cpp

EXEMSSMatMSUSYEFTHiggs_SRC := \
		$(DIR)/run_MSSMatMSUSYEFTHiggs.cpp \
		$(DIR)/run_cmd_line_MSSMatMSUSYEFTHiggs.cpp \
		$(DIR)/scan_MSSMatMSUSYEFTHiggs.cpp
LLMSSMatMSUSYEFTHiggs_LIB  :=
LLMSSMatMSUSYEFTHiggs_OBJ  :=
LLMSSMatMSUSYEFTHiggs_SRC  := \
		$(DIR)/MSSMatMSUSYEFTHiggs_librarylink.cpp

LLMSSMatMSUSYEFTHiggs_MMA  := \
		$(DIR)/MSSMatMSUSYEFTHiggs_librarylink.m \
		$(DIR)/run_MSSMatMSUSYEFTHiggs.m

LIBMSSMatMSUSYEFTHiggs_HDR := \
		$(DIR)/MSSMatMSUSYEFTHiggs_cxx_diagrams.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_a_muon.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_convergence_tester.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_edm.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_effective_couplings.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_ewsb_solver.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_ewsb_solver_interface.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_high_scale_constraint.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_info.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_initial_guesser.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_input_parameters.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_low_scale_constraint.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mass_eigenstates.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_model.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_model_slha.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_observables.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_physical.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_slha_io.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_spectrum_generator.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_spectrum_generator_interface.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_soft_parameters.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_susy_parameters.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_susy_scale_constraint.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_utilities.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_weinberg_angle.hpp

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
-include $(MSSMatMSUSYEFTHiggs_SUSY_BETAS_MK)
-include $(MSSMatMSUSYEFTHiggs_SOFT_BETAS_MK)
-include $(MSSMatMSUSYEFTHiggs_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(MSSMatMSUSYEFTHiggs_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMatMSUSYEFTHiggs_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMatMSUSYEFTHiggs_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBMSSMatMSUSYEFTHiggs_SRC := $(sort $(LIBMSSMatMSUSYEFTHiggs_SRC))
EXEMSSMatMSUSYEFTHiggs_SRC := $(sort $(EXEMSSMatMSUSYEFTHiggs_SRC))

LIBMSSMatMSUSYEFTHiggs_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBMSSMatMSUSYEFTHiggs_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBMSSMatMSUSYEFTHiggs_SRC)))

EXEMSSMatMSUSYEFTHiggs_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXEMSSMatMSUSYEFTHiggs_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXEMSSMatMSUSYEFTHiggs_SRC)))

EXEMSSMatMSUSYEFTHiggs_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXEMSSMatMSUSYEFTHiggs_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXEMSSMatMSUSYEFTHiggs_SRC)))

LIBMSSMatMSUSYEFTHiggs_DEP := \
		$(LIBMSSMatMSUSYEFTHiggs_OBJ:.o=.d)

EXEMSSMatMSUSYEFTHiggs_DEP := \
		$(EXEMSSMatMSUSYEFTHiggs_OBJ:.o=.d)

LLMSSMatMSUSYEFTHiggs_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLMSSMatMSUSYEFTHiggs_SRC)))

LLMSSMatMSUSYEFTHiggs_OBJ  := $(LLMSSMatMSUSYEFTHiggs_SRC:.cpp=.o)
LLMSSMatMSUSYEFTHiggs_LIB  := $(LLMSSMatMSUSYEFTHiggs_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBMSSMatMSUSYEFTHiggs     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_MSSMatMSUSYEFTHiggs := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_MSSMatMSUSYEFTHiggs := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBMSSMatMSUSYEFTHiggs) $(EXEMSSMatMSUSYEFTHiggs_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(MSSMatMSUSYEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMatMSUSYEFTHiggs_SRC) $(MSSMatMSUSYEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMatMSUSYEFTHiggs_HDR) $(MSSMatMSUSYEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXEMSSMatMSUSYEFTHiggs_SRC) $(MSSMatMSUSYEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMatMSUSYEFTHiggs_SRC) $(MSSMatMSUSYEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMatMSUSYEFTHiggs_MMA) $(MSSMatMSUSYEFTHiggs_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(MSSMatMSUSYEFTHiggs_MK) $(MSSMatMSUSYEFTHiggs_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(MSSMatMSUSYEFTHiggs_INCLUDE_MK) $(MSSMatMSUSYEFTHiggs_INSTALL_DIR)
ifneq ($(MSSMatMSUSYEFTHiggs_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(MSSMatMSUSYEFTHiggs_SLHA_INPUT) $(MSSMatMSUSYEFTHiggs_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(MSSMatMSUSYEFTHiggs_REFERENCES) $(MSSMatMSUSYEFTHiggs_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(MSSMatMSUSYEFTHiggs_GNUPLOT) $(MSSMatMSUSYEFTHiggs_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBMSSMatMSUSYEFTHiggs_DEP)
		-rm -f $(EXEMSSMatMSUSYEFTHiggs_DEP)
		-rm -f $(LLMSSMatMSUSYEFTHiggs_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBMSSMatMSUSYEFTHiggs)
		-rm -f $(LLMSSMatMSUSYEFTHiggs_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBMSSMatMSUSYEFTHiggs_OBJ)
		-rm -f $(EXEMSSMatMSUSYEFTHiggs_OBJ)
		-rm -f $(LLMSSMatMSUSYEFTHiggs_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXEMSSMatMSUSYEFTHiggs_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(MSSMatMSUSYEFTHiggs_TARBALL) \
		$(LIBMSSMatMSUSYEFTHiggs_SRC) $(LIBMSSMatMSUSYEFTHiggs_HDR) \
		$(EXEMSSMatMSUSYEFTHiggs_SRC) \
		$(LLMSSMatMSUSYEFTHiggs_SRC) $(LLMSSMatMSUSYEFTHiggs_MMA) \
		$(MSSMatMSUSYEFTHiggs_MK) $(MSSMatMSUSYEFTHiggs_INCLUDE_MK) \
		$(MSSMatMSUSYEFTHiggs_SLHA_INPUT) $(MSSMatMSUSYEFTHiggs_REFERENCES) \
		$(MSSMatMSUSYEFTHiggs_GNUPLOT)

$(LIBMSSMatMSUSYEFTHiggs_SRC) $(LIBMSSMatMSUSYEFTHiggs_HDR) $(EXEMSSMatMSUSYEFTHiggs_SRC) $(LLMSSMatMSUSYEFTHiggs_SRC) $(LLMSSMatMSUSYEFTHiggs_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_MSSMatMSUSYEFTHiggs)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_MSSMatMSUSYEFTHiggs): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_MSSMatMSUSYEFTHiggs)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_MSSMatMSUSYEFTHiggs)"
		@echo "Note: to regenerate MSSMatMSUSYEFTHiggs source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_MSSMatMSUSYEFTHiggs)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_MSSMatMSUSYEFTHiggs):
		@true
endif

$(LIBMSSMatMSUSYEFTHiggs_DEP) $(EXEMSSMatMSUSYEFTHiggs_DEP) $(LLMSSMatMSUSYEFTHiggs_DEP) $(LIBMSSMatMSUSYEFTHiggs_OBJ) $(EXEMSSMatMSUSYEFTHiggs_OBJ) $(LLMSSMatMSUSYEFTHiggs_OBJ) $(LLMSSMatMSUSYEFTHiggs_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBMSSMatMSUSYEFTHiggs_DEP) $(EXEMSSMatMSUSYEFTHiggs_DEP) $(LLMSSMatMSUSYEFTHiggs_DEP) $(LIBMSSMatMSUSYEFTHiggs_OBJ) $(EXEMSSMatMSUSYEFTHiggs_OBJ) $(LLMSSMatMSUSYEFTHiggs_OBJ) $(LLMSSMatMSUSYEFTHiggs_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLMSSMatMSUSYEFTHiggs_OBJ) $(LLMSSMatMSUSYEFTHiggs_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBMSSMatMSUSYEFTHiggs): $(LIBMSSMatMSUSYEFTHiggs_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBMSSMatMSUSYEFTHiggs) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLMSSMatMSUSYEFTHiggs_LIB): $(LLMSSMatMSUSYEFTHiggs_OBJ) $(LIBMSSMatMSUSYEFTHiggs) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBMSSMatMSUSYEFTHiggs_DEP) $(EXEMSSMatMSUSYEFTHiggs_DEP)
ALLSRC += $(LIBMSSMatMSUSYEFTHiggs_SRC) $(EXEMSSMatMSUSYEFTHiggs_SRC)
ALLLIB += $(LIBMSSMatMSUSYEFTHiggs)
ALLEXE += $(EXEMSSMatMSUSYEFTHiggs_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLMSSMatMSUSYEFTHiggs_DEP)
ALLSRC += $(LLMSSMatMSUSYEFTHiggs_SRC)
ALLLL  += $(LLMSSMatMSUSYEFTHiggs_LIB)
endif
