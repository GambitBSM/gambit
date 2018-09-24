DIR          := models/MSSMEFTHiggs_mAmu
MODNAME      := MSSMEFTHiggs_mAmu
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes

MSSMEFTHiggs_mAmu_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

MSSMEFTHiggs_mAmu_MK     := \
		$(DIR)/module.mk

MSSMEFTHiggs_mAmu_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

MSSMEFTHiggs_mAmu_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

MSSMEFTHiggs_mAmu_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

MSSMEFTHiggs_mAmu_INCLUDE_MK := \
		$(MSSMEFTHiggs_mAmu_SUSY_BETAS_MK) \
		$(MSSMEFTHiggs_mAmu_SOFT_BETAS_MK)

MSSMEFTHiggs_mAmu_SLHA_INPUT := \
		$(DIR)/LesHouches.in.MSSMEFTHiggs_mAmu_generated \
		$(DIR)/LesHouches.in.MSSMEFTHiggs

MSSMEFTHiggs_mAmu_REFERENCES := \
		$(DIR)/MSSMEFTHiggs_mAmu_references.tex

MSSMEFTHiggs_mAmu_GNUPLOT := \
		$(DIR)/MSSMEFTHiggs_mAmu_plot_rgflow.gnuplot \
		$(DIR)/MSSMEFTHiggs_mAmu_plot_spectrum.gnuplot

MSSMEFTHiggs_mAmu_TARBALL := \
		$(MODNAME).tar.gz

LIBMSSMEFTHiggs_mAmu_SRC := \
		$(DIR)/MSSMEFTHiggs_mAmu_a_muon.cpp \
		$(DIR)/MSSMEFTHiggs_mAmu_edm.cpp \
		$(DIR)/MSSMEFTHiggs_mAmu_effective_couplings.cpp \
		$(DIR)/MSSMEFTHiggs_mAmu_info.cpp \
		$(DIR)/MSSMEFTHiggs_mAmu_input_parameters.cpp \
		$(DIR)/MSSMEFTHiggs_mAmu_mass_eigenstates.cpp \
		$(DIR)/MSSMEFTHiggs_mAmu_observables.cpp \
		$(DIR)/MSSMEFTHiggs_mAmu_physical.cpp \
		$(DIR)/MSSMEFTHiggs_mAmu_slha_io.cpp \
		$(DIR)/MSSMEFTHiggs_mAmu_soft_parameters.cpp \
		$(DIR)/MSSMEFTHiggs_mAmu_susy_parameters.cpp \
		$(DIR)/MSSMEFTHiggs_mAmu_utilities.cpp \
		$(DIR)/MSSMEFTHiggs_mAmu_weinberg_angle.cpp

EXEMSSMEFTHiggs_mAmu_SRC := \
		$(DIR)/run_MSSMEFTHiggs_mAmu.cpp \
		$(DIR)/run_cmd_line_MSSMEFTHiggs_mAmu.cpp \
		$(DIR)/scan_MSSMEFTHiggs_mAmu.cpp
LLMSSMEFTHiggs_mAmu_LIB  :=
LLMSSMEFTHiggs_mAmu_OBJ  :=
LLMSSMEFTHiggs_mAmu_SRC  := \
		$(DIR)/MSSMEFTHiggs_mAmu_librarylink.cpp

LLMSSMEFTHiggs_mAmu_MMA  := \
		$(DIR)/MSSMEFTHiggs_mAmu_librarylink.m \
		$(DIR)/run_MSSMEFTHiggs_mAmu.m

LIBMSSMEFTHiggs_mAmu_HDR := \
		$(DIR)/MSSMEFTHiggs_mAmu_cxx_diagrams.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_a_muon.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_convergence_tester.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_edm.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_effective_couplings.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_ewsb_solver.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_ewsb_solver_interface.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_high_scale_constraint.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_info.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_initial_guesser.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_input_parameters.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_low_scale_constraint.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_mass_eigenstates.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_model.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_model_slha.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_observables.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_physical.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_slha_io.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_spectrum_generator.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_spectrum_generator_interface.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_soft_parameters.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_susy_parameters.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_susy_scale_constraint.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_utilities.hpp \
		$(DIR)/MSSMEFTHiggs_mAmu_weinberg_angle.hpp

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
-include $(MSSMEFTHiggs_mAmu_SUSY_BETAS_MK)
-include $(MSSMEFTHiggs_mAmu_SOFT_BETAS_MK)
-include $(MSSMEFTHiggs_mAmu_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(MSSMEFTHiggs_mAmu_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMEFTHiggs_mAmu_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMEFTHiggs_mAmu_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBMSSMEFTHiggs_mAmu_SRC := $(sort $(LIBMSSMEFTHiggs_mAmu_SRC))
EXEMSSMEFTHiggs_mAmu_SRC := $(sort $(EXEMSSMEFTHiggs_mAmu_SRC))

LIBMSSMEFTHiggs_mAmu_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBMSSMEFTHiggs_mAmu_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBMSSMEFTHiggs_mAmu_SRC)))

EXEMSSMEFTHiggs_mAmu_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXEMSSMEFTHiggs_mAmu_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXEMSSMEFTHiggs_mAmu_SRC)))

EXEMSSMEFTHiggs_mAmu_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXEMSSMEFTHiggs_mAmu_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXEMSSMEFTHiggs_mAmu_SRC)))

LIBMSSMEFTHiggs_mAmu_DEP := \
		$(LIBMSSMEFTHiggs_mAmu_OBJ:.o=.d)

EXEMSSMEFTHiggs_mAmu_DEP := \
		$(EXEMSSMEFTHiggs_mAmu_OBJ:.o=.d)

LLMSSMEFTHiggs_mAmu_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLMSSMEFTHiggs_mAmu_SRC)))

LLMSSMEFTHiggs_mAmu_OBJ  := $(LLMSSMEFTHiggs_mAmu_SRC:.cpp=.o)
LLMSSMEFTHiggs_mAmu_LIB  := $(LLMSSMEFTHiggs_mAmu_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBMSSMEFTHiggs_mAmu     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_MSSMEFTHiggs_mAmu := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_MSSMEFTHiggs_mAmu := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBMSSMEFTHiggs_mAmu) $(EXEMSSMEFTHiggs_mAmu_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(MSSMEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMEFTHiggs_mAmu_SRC) $(MSSMEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMEFTHiggs_mAmu_HDR) $(MSSMEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXEMSSMEFTHiggs_mAmu_SRC) $(MSSMEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMEFTHiggs_mAmu_SRC) $(MSSMEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMEFTHiggs_mAmu_MMA) $(MSSMEFTHiggs_mAmu_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(MSSMEFTHiggs_mAmu_MK) $(MSSMEFTHiggs_mAmu_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(MSSMEFTHiggs_mAmu_INCLUDE_MK) $(MSSMEFTHiggs_mAmu_INSTALL_DIR)
ifneq ($(MSSMEFTHiggs_mAmu_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(MSSMEFTHiggs_mAmu_SLHA_INPUT) $(MSSMEFTHiggs_mAmu_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(MSSMEFTHiggs_mAmu_REFERENCES) $(MSSMEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(MSSMEFTHiggs_mAmu_GNUPLOT) $(MSSMEFTHiggs_mAmu_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBMSSMEFTHiggs_mAmu_DEP)
		-rm -f $(EXEMSSMEFTHiggs_mAmu_DEP)
		-rm -f $(LLMSSMEFTHiggs_mAmu_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBMSSMEFTHiggs_mAmu)
		-rm -f $(LLMSSMEFTHiggs_mAmu_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBMSSMEFTHiggs_mAmu_OBJ)
		-rm -f $(EXEMSSMEFTHiggs_mAmu_OBJ)
		-rm -f $(LLMSSMEFTHiggs_mAmu_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXEMSSMEFTHiggs_mAmu_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(MSSMEFTHiggs_mAmu_TARBALL) \
		$(LIBMSSMEFTHiggs_mAmu_SRC) $(LIBMSSMEFTHiggs_mAmu_HDR) \
		$(EXEMSSMEFTHiggs_mAmu_SRC) \
		$(LLMSSMEFTHiggs_mAmu_SRC) $(LLMSSMEFTHiggs_mAmu_MMA) \
		$(MSSMEFTHiggs_mAmu_MK) $(MSSMEFTHiggs_mAmu_INCLUDE_MK) \
		$(MSSMEFTHiggs_mAmu_SLHA_INPUT) $(MSSMEFTHiggs_mAmu_REFERENCES) \
		$(MSSMEFTHiggs_mAmu_GNUPLOT)

$(LIBMSSMEFTHiggs_mAmu_SRC) $(LIBMSSMEFTHiggs_mAmu_HDR) $(EXEMSSMEFTHiggs_mAmu_SRC) $(LLMSSMEFTHiggs_mAmu_SRC) $(LLMSSMEFTHiggs_mAmu_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_MSSMEFTHiggs_mAmu)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_MSSMEFTHiggs_mAmu): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_MSSMEFTHiggs_mAmu)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_MSSMEFTHiggs_mAmu)"
		@echo "Note: to regenerate MSSMEFTHiggs_mAmu source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_MSSMEFTHiggs_mAmu)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_MSSMEFTHiggs_mAmu):
		@true
endif

$(LIBMSSMEFTHiggs_mAmu_DEP) $(EXEMSSMEFTHiggs_mAmu_DEP) $(LLMSSMEFTHiggs_mAmu_DEP) $(LIBMSSMEFTHiggs_mAmu_OBJ) $(EXEMSSMEFTHiggs_mAmu_OBJ) $(LLMSSMEFTHiggs_mAmu_OBJ) $(LLMSSMEFTHiggs_mAmu_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBMSSMEFTHiggs_mAmu_DEP) $(EXEMSSMEFTHiggs_mAmu_DEP) $(LLMSSMEFTHiggs_mAmu_DEP) $(LIBMSSMEFTHiggs_mAmu_OBJ) $(EXEMSSMEFTHiggs_mAmu_OBJ) $(LLMSSMEFTHiggs_mAmu_OBJ) $(LLMSSMEFTHiggs_mAmu_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLMSSMEFTHiggs_mAmu_OBJ) $(LLMSSMEFTHiggs_mAmu_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBMSSMEFTHiggs_mAmu): $(LIBMSSMEFTHiggs_mAmu_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBMSSMEFTHiggs_mAmu) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLMSSMEFTHiggs_mAmu_LIB): $(LLMSSMEFTHiggs_mAmu_OBJ) $(LIBMSSMEFTHiggs_mAmu) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBMSSMEFTHiggs_mAmu_DEP) $(EXEMSSMEFTHiggs_mAmu_DEP)
ALLSRC += $(LIBMSSMEFTHiggs_mAmu_SRC) $(EXEMSSMEFTHiggs_mAmu_SRC)
ALLLIB += $(LIBMSSMEFTHiggs_mAmu)
ALLEXE += $(EXEMSSMEFTHiggs_mAmu_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLMSSMEFTHiggs_mAmu_DEP)
ALLSRC += $(LLMSSMEFTHiggs_mAmu_SRC)
ALLLL  += $(LLMSSMEFTHiggs_mAmu_LIB)
endif
