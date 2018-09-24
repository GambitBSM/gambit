DIR          := models/MSSMatMGUTEFTHiggs_mAmu
MODNAME      := MSSMatMGUTEFTHiggs_mAmu
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes

MSSMatMGUTEFTHiggs_mAmu_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

MSSMatMGUTEFTHiggs_mAmu_MK     := \
		$(DIR)/module.mk

MSSMatMGUTEFTHiggs_mAmu_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

MSSMatMGUTEFTHiggs_mAmu_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

MSSMatMGUTEFTHiggs_mAmu_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

MSSMatMGUTEFTHiggs_mAmu_INCLUDE_MK := \
		$(MSSMatMGUTEFTHiggs_mAmu_SUSY_BETAS_MK) \
		$(MSSMatMGUTEFTHiggs_mAmu_SOFT_BETAS_MK)

MSSMatMGUTEFTHiggs_mAmu_SLHA_INPUT := \
		$(DIR)/LesHouches.in.MSSMatMGUTEFTHiggs_mAmu_generated \
		$(DIR)/LesHouches.in.MSSMEFTHiggs \
		$(DIR)/LesHouches.in.MSSMatMGUT

MSSMatMGUTEFTHiggs_mAmu_REFERENCES := \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_references.tex

MSSMatMGUTEFTHiggs_mAmu_GNUPLOT := \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_plot_rgflow.gnuplot \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_plot_spectrum.gnuplot

MSSMatMGUTEFTHiggs_mAmu_TARBALL := \
		$(MODNAME).tar.gz

LIBMSSMatMGUTEFTHiggs_mAmu_SRC := \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_a_muon.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_edm.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_effective_couplings.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_info.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_input_parameters.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_observables.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_physical.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_slha_io.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_soft_parameters.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_susy_parameters.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_utilities.cpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_weinberg_angle.cpp

EXEMSSMatMGUTEFTHiggs_mAmu_SRC := \
		$(DIR)/run_MSSMatMGUTEFTHiggs_mAmu.cpp \
		$(DIR)/run_cmd_line_MSSMatMGUTEFTHiggs_mAmu.cpp \
		$(DIR)/scan_MSSMatMGUTEFTHiggs_mAmu.cpp
LLMSSMatMGUTEFTHiggs_mAmu_LIB  :=
LLMSSMatMGUTEFTHiggs_mAmu_OBJ  :=
LLMSSMatMGUTEFTHiggs_mAmu_SRC  := \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_librarylink.cpp

LLMSSMatMGUTEFTHiggs_mAmu_MMA  := \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_librarylink.m \
		$(DIR)/run_MSSMatMGUTEFTHiggs_mAmu.m

LIBMSSMatMGUTEFTHiggs_mAmu_HDR := \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_cxx_diagrams.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_a_muon.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_convergence_tester.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_edm.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_effective_couplings.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_ewsb_solver.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_ewsb_solver_interface.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_high_scale_constraint.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_info.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_initial_guesser.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_input_parameters.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_low_scale_constraint.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_model.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_model_slha.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_observables.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_physical.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_slha_io.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_spectrum_generator.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_spectrum_generator_interface.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_soft_parameters.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_susy_parameters.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_susy_scale_constraint.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_utilities.hpp \
		$(DIR)/MSSMatMGUTEFTHiggs_mAmu_weinberg_angle.hpp

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
-include $(MSSMatMGUTEFTHiggs_mAmu_SUSY_BETAS_MK)
-include $(MSSMatMGUTEFTHiggs_mAmu_SOFT_BETAS_MK)
-include $(MSSMatMGUTEFTHiggs_mAmu_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(MSSMatMGUTEFTHiggs_mAmu_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMatMGUTEFTHiggs_mAmu_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMatMGUTEFTHiggs_mAmu_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBMSSMatMGUTEFTHiggs_mAmu_SRC := $(sort $(LIBMSSMatMGUTEFTHiggs_mAmu_SRC))
EXEMSSMatMGUTEFTHiggs_mAmu_SRC := $(sort $(EXEMSSMatMGUTEFTHiggs_mAmu_SRC))

LIBMSSMatMGUTEFTHiggs_mAmu_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBMSSMatMGUTEFTHiggs_mAmu_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBMSSMatMGUTEFTHiggs_mAmu_SRC)))

EXEMSSMatMGUTEFTHiggs_mAmu_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXEMSSMatMGUTEFTHiggs_mAmu_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXEMSSMatMGUTEFTHiggs_mAmu_SRC)))

EXEMSSMatMGUTEFTHiggs_mAmu_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXEMSSMatMGUTEFTHiggs_mAmu_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXEMSSMatMGUTEFTHiggs_mAmu_SRC)))

LIBMSSMatMGUTEFTHiggs_mAmu_DEP := \
		$(LIBMSSMatMGUTEFTHiggs_mAmu_OBJ:.o=.d)

EXEMSSMatMGUTEFTHiggs_mAmu_DEP := \
		$(EXEMSSMatMGUTEFTHiggs_mAmu_OBJ:.o=.d)

LLMSSMatMGUTEFTHiggs_mAmu_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLMSSMatMGUTEFTHiggs_mAmu_SRC)))

LLMSSMatMGUTEFTHiggs_mAmu_OBJ  := $(LLMSSMatMGUTEFTHiggs_mAmu_SRC:.cpp=.o)
LLMSSMatMGUTEFTHiggs_mAmu_LIB  := $(LLMSSMatMGUTEFTHiggs_mAmu_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBMSSMatMGUTEFTHiggs_mAmu     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_MSSMatMGUTEFTHiggs_mAmu := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_MSSMatMGUTEFTHiggs_mAmu := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBMSSMatMGUTEFTHiggs_mAmu) $(EXEMSSMatMGUTEFTHiggs_mAmu_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(MSSMatMGUTEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMatMGUTEFTHiggs_mAmu_SRC) $(MSSMatMGUTEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMatMGUTEFTHiggs_mAmu_HDR) $(MSSMatMGUTEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXEMSSMatMGUTEFTHiggs_mAmu_SRC) $(MSSMatMGUTEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMatMGUTEFTHiggs_mAmu_SRC) $(MSSMatMGUTEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMatMGUTEFTHiggs_mAmu_MMA) $(MSSMatMGUTEFTHiggs_mAmu_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(MSSMatMGUTEFTHiggs_mAmu_MK) $(MSSMatMGUTEFTHiggs_mAmu_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(MSSMatMGUTEFTHiggs_mAmu_INCLUDE_MK) $(MSSMatMGUTEFTHiggs_mAmu_INSTALL_DIR)
ifneq ($(MSSMatMGUTEFTHiggs_mAmu_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(MSSMatMGUTEFTHiggs_mAmu_SLHA_INPUT) $(MSSMatMGUTEFTHiggs_mAmu_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(MSSMatMGUTEFTHiggs_mAmu_REFERENCES) $(MSSMatMGUTEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(MSSMatMGUTEFTHiggs_mAmu_GNUPLOT) $(MSSMatMGUTEFTHiggs_mAmu_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBMSSMatMGUTEFTHiggs_mAmu_DEP)
		-rm -f $(EXEMSSMatMGUTEFTHiggs_mAmu_DEP)
		-rm -f $(LLMSSMatMGUTEFTHiggs_mAmu_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBMSSMatMGUTEFTHiggs_mAmu)
		-rm -f $(LLMSSMatMGUTEFTHiggs_mAmu_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBMSSMatMGUTEFTHiggs_mAmu_OBJ)
		-rm -f $(EXEMSSMatMGUTEFTHiggs_mAmu_OBJ)
		-rm -f $(LLMSSMatMGUTEFTHiggs_mAmu_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXEMSSMatMGUTEFTHiggs_mAmu_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(MSSMatMGUTEFTHiggs_mAmu_TARBALL) \
		$(LIBMSSMatMGUTEFTHiggs_mAmu_SRC) $(LIBMSSMatMGUTEFTHiggs_mAmu_HDR) \
		$(EXEMSSMatMGUTEFTHiggs_mAmu_SRC) \
		$(LLMSSMatMGUTEFTHiggs_mAmu_SRC) $(LLMSSMatMGUTEFTHiggs_mAmu_MMA) \
		$(MSSMatMGUTEFTHiggs_mAmu_MK) $(MSSMatMGUTEFTHiggs_mAmu_INCLUDE_MK) \
		$(MSSMatMGUTEFTHiggs_mAmu_SLHA_INPUT) $(MSSMatMGUTEFTHiggs_mAmu_REFERENCES) \
		$(MSSMatMGUTEFTHiggs_mAmu_GNUPLOT)

$(LIBMSSMatMGUTEFTHiggs_mAmu_SRC) $(LIBMSSMatMGUTEFTHiggs_mAmu_HDR) $(EXEMSSMatMGUTEFTHiggs_mAmu_SRC) $(LLMSSMatMGUTEFTHiggs_mAmu_SRC) $(LLMSSMatMGUTEFTHiggs_mAmu_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_MSSMatMGUTEFTHiggs_mAmu)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_MSSMatMGUTEFTHiggs_mAmu): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_MSSMatMGUTEFTHiggs_mAmu)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_MSSMatMGUTEFTHiggs_mAmu)"
		@echo "Note: to regenerate MSSMatMGUTEFTHiggs_mAmu source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_MSSMatMGUTEFTHiggs_mAmu)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_MSSMatMGUTEFTHiggs_mAmu):
		@true
endif

$(LIBMSSMatMGUTEFTHiggs_mAmu_DEP) $(EXEMSSMatMGUTEFTHiggs_mAmu_DEP) $(LLMSSMatMGUTEFTHiggs_mAmu_DEP) $(LIBMSSMatMGUTEFTHiggs_mAmu_OBJ) $(EXEMSSMatMGUTEFTHiggs_mAmu_OBJ) $(LLMSSMatMGUTEFTHiggs_mAmu_OBJ) $(LLMSSMatMGUTEFTHiggs_mAmu_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBMSSMatMGUTEFTHiggs_mAmu_DEP) $(EXEMSSMatMGUTEFTHiggs_mAmu_DEP) $(LLMSSMatMGUTEFTHiggs_mAmu_DEP) $(LIBMSSMatMGUTEFTHiggs_mAmu_OBJ) $(EXEMSSMatMGUTEFTHiggs_mAmu_OBJ) $(LLMSSMatMGUTEFTHiggs_mAmu_OBJ) $(LLMSSMatMGUTEFTHiggs_mAmu_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLMSSMatMGUTEFTHiggs_mAmu_OBJ) $(LLMSSMatMGUTEFTHiggs_mAmu_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBMSSMatMGUTEFTHiggs_mAmu): $(LIBMSSMatMGUTEFTHiggs_mAmu_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBMSSMatMGUTEFTHiggs_mAmu) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLMSSMatMGUTEFTHiggs_mAmu_LIB): $(LLMSSMatMGUTEFTHiggs_mAmu_OBJ) $(LIBMSSMatMGUTEFTHiggs_mAmu) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBMSSMatMGUTEFTHiggs_mAmu_DEP) $(EXEMSSMatMGUTEFTHiggs_mAmu_DEP)
ALLSRC += $(LIBMSSMatMGUTEFTHiggs_mAmu_SRC) $(EXEMSSMatMGUTEFTHiggs_mAmu_SRC)
ALLLIB += $(LIBMSSMatMGUTEFTHiggs_mAmu)
ALLEXE += $(EXEMSSMatMGUTEFTHiggs_mAmu_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLMSSMatMGUTEFTHiggs_mAmu_DEP)
ALLSRC += $(LLMSSMatMGUTEFTHiggs_mAmu_SRC)
ALLLL  += $(LLMSSMatMGUTEFTHiggs_mAmu_LIB)
endif
