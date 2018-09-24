DIR          := models/MSSMatMGUT_mAmu
MODNAME      := MSSMatMGUT_mAmu
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes

MSSMatMGUT_mAmu_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

MSSMatMGUT_mAmu_MK     := \
		$(DIR)/module.mk

MSSMatMGUT_mAmu_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

MSSMatMGUT_mAmu_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

MSSMatMGUT_mAmu_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

MSSMatMGUT_mAmu_INCLUDE_MK := \
		$(MSSMatMGUT_mAmu_SUSY_BETAS_MK) \
		$(MSSMatMGUT_mAmu_SOFT_BETAS_MK)

MSSMatMGUT_mAmu_SLHA_INPUT := \
		$(DIR)/LesHouches.in.MSSMatMGUT_mAmu_generated \
		$(DIR)/LesHouches.in.MSSMatMGUT

MSSMatMGUT_mAmu_REFERENCES := \
		$(DIR)/MSSMatMGUT_mAmu_references.tex

MSSMatMGUT_mAmu_GNUPLOT := \
		$(DIR)/MSSMatMGUT_mAmu_plot_rgflow.gnuplot \
		$(DIR)/MSSMatMGUT_mAmu_plot_spectrum.gnuplot

MSSMatMGUT_mAmu_TARBALL := \
		$(MODNAME).tar.gz

LIBMSSMatMGUT_mAmu_SRC := \
		$(DIR)/MSSMatMGUT_mAmu_a_muon.cpp \
		$(DIR)/MSSMatMGUT_mAmu_edm.cpp \
		$(DIR)/MSSMatMGUT_mAmu_effective_couplings.cpp \
		$(DIR)/MSSMatMGUT_mAmu_info.cpp \
		$(DIR)/MSSMatMGUT_mAmu_input_parameters.cpp \
		$(DIR)/MSSMatMGUT_mAmu_mass_eigenstates.cpp \
		$(DIR)/MSSMatMGUT_mAmu_observables.cpp \
		$(DIR)/MSSMatMGUT_mAmu_physical.cpp \
		$(DIR)/MSSMatMGUT_mAmu_slha_io.cpp \
		$(DIR)/MSSMatMGUT_mAmu_soft_parameters.cpp \
		$(DIR)/MSSMatMGUT_mAmu_susy_parameters.cpp \
		$(DIR)/MSSMatMGUT_mAmu_utilities.cpp \
		$(DIR)/MSSMatMGUT_mAmu_weinberg_angle.cpp

EXEMSSMatMGUT_mAmu_SRC := \
		$(DIR)/run_MSSMatMGUT_mAmu.cpp \
		$(DIR)/run_cmd_line_MSSMatMGUT_mAmu.cpp \
		$(DIR)/scan_MSSMatMGUT_mAmu.cpp
LLMSSMatMGUT_mAmu_LIB  :=
LLMSSMatMGUT_mAmu_OBJ  :=
LLMSSMatMGUT_mAmu_SRC  := \
		$(DIR)/MSSMatMGUT_mAmu_librarylink.cpp

LLMSSMatMGUT_mAmu_MMA  := \
		$(DIR)/MSSMatMGUT_mAmu_librarylink.m \
		$(DIR)/run_MSSMatMGUT_mAmu.m

LIBMSSMatMGUT_mAmu_HDR := \
		$(DIR)/MSSMatMGUT_mAmu_cxx_diagrams.hpp \
		$(DIR)/MSSMatMGUT_mAmu_a_muon.hpp \
		$(DIR)/MSSMatMGUT_mAmu_convergence_tester.hpp \
		$(DIR)/MSSMatMGUT_mAmu_edm.hpp \
		$(DIR)/MSSMatMGUT_mAmu_effective_couplings.hpp \
		$(DIR)/MSSMatMGUT_mAmu_ewsb_solver.hpp \
		$(DIR)/MSSMatMGUT_mAmu_ewsb_solver_interface.hpp \
		$(DIR)/MSSMatMGUT_mAmu_high_scale_constraint.hpp \
		$(DIR)/MSSMatMGUT_mAmu_info.hpp \
		$(DIR)/MSSMatMGUT_mAmu_initial_guesser.hpp \
		$(DIR)/MSSMatMGUT_mAmu_input_parameters.hpp \
		$(DIR)/MSSMatMGUT_mAmu_low_scale_constraint.hpp \
		$(DIR)/MSSMatMGUT_mAmu_mass_eigenstates.hpp \
		$(DIR)/MSSMatMGUT_mAmu_model.hpp \
		$(DIR)/MSSMatMGUT_mAmu_model_slha.hpp \
		$(DIR)/MSSMatMGUT_mAmu_observables.hpp \
		$(DIR)/MSSMatMGUT_mAmu_physical.hpp \
		$(DIR)/MSSMatMGUT_mAmu_slha_io.hpp \
		$(DIR)/MSSMatMGUT_mAmu_spectrum_generator.hpp \
		$(DIR)/MSSMatMGUT_mAmu_spectrum_generator_interface.hpp \
		$(DIR)/MSSMatMGUT_mAmu_soft_parameters.hpp \
		$(DIR)/MSSMatMGUT_mAmu_susy_parameters.hpp \
		$(DIR)/MSSMatMGUT_mAmu_susy_scale_constraint.hpp \
		$(DIR)/MSSMatMGUT_mAmu_utilities.hpp \
		$(DIR)/MSSMatMGUT_mAmu_weinberg_angle.hpp

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
-include $(MSSMatMGUT_mAmu_SUSY_BETAS_MK)
-include $(MSSMatMGUT_mAmu_SOFT_BETAS_MK)
-include $(MSSMatMGUT_mAmu_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(MSSMatMGUT_mAmu_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMatMGUT_mAmu_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMatMGUT_mAmu_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBMSSMatMGUT_mAmu_SRC := $(sort $(LIBMSSMatMGUT_mAmu_SRC))
EXEMSSMatMGUT_mAmu_SRC := $(sort $(EXEMSSMatMGUT_mAmu_SRC))

LIBMSSMatMGUT_mAmu_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBMSSMatMGUT_mAmu_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBMSSMatMGUT_mAmu_SRC)))

EXEMSSMatMGUT_mAmu_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXEMSSMatMGUT_mAmu_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXEMSSMatMGUT_mAmu_SRC)))

EXEMSSMatMGUT_mAmu_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXEMSSMatMGUT_mAmu_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXEMSSMatMGUT_mAmu_SRC)))

LIBMSSMatMGUT_mAmu_DEP := \
		$(LIBMSSMatMGUT_mAmu_OBJ:.o=.d)

EXEMSSMatMGUT_mAmu_DEP := \
		$(EXEMSSMatMGUT_mAmu_OBJ:.o=.d)

LLMSSMatMGUT_mAmu_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLMSSMatMGUT_mAmu_SRC)))

LLMSSMatMGUT_mAmu_OBJ  := $(LLMSSMatMGUT_mAmu_SRC:.cpp=.o)
LLMSSMatMGUT_mAmu_LIB  := $(LLMSSMatMGUT_mAmu_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBMSSMatMGUT_mAmu     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_MSSMatMGUT_mAmu := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_MSSMatMGUT_mAmu := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBMSSMatMGUT_mAmu) $(EXEMSSMatMGUT_mAmu_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(MSSMatMGUT_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMatMGUT_mAmu_SRC) $(MSSMatMGUT_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMatMGUT_mAmu_HDR) $(MSSMatMGUT_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXEMSSMatMGUT_mAmu_SRC) $(MSSMatMGUT_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMatMGUT_mAmu_SRC) $(MSSMatMGUT_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMatMGUT_mAmu_MMA) $(MSSMatMGUT_mAmu_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(MSSMatMGUT_mAmu_MK) $(MSSMatMGUT_mAmu_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(MSSMatMGUT_mAmu_INCLUDE_MK) $(MSSMatMGUT_mAmu_INSTALL_DIR)
ifneq ($(MSSMatMGUT_mAmu_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(MSSMatMGUT_mAmu_SLHA_INPUT) $(MSSMatMGUT_mAmu_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(MSSMatMGUT_mAmu_REFERENCES) $(MSSMatMGUT_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(MSSMatMGUT_mAmu_GNUPLOT) $(MSSMatMGUT_mAmu_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBMSSMatMGUT_mAmu_DEP)
		-rm -f $(EXEMSSMatMGUT_mAmu_DEP)
		-rm -f $(LLMSSMatMGUT_mAmu_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBMSSMatMGUT_mAmu)
		-rm -f $(LLMSSMatMGUT_mAmu_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBMSSMatMGUT_mAmu_OBJ)
		-rm -f $(EXEMSSMatMGUT_mAmu_OBJ)
		-rm -f $(LLMSSMatMGUT_mAmu_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXEMSSMatMGUT_mAmu_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(MSSMatMGUT_mAmu_TARBALL) \
		$(LIBMSSMatMGUT_mAmu_SRC) $(LIBMSSMatMGUT_mAmu_HDR) \
		$(EXEMSSMatMGUT_mAmu_SRC) \
		$(LLMSSMatMGUT_mAmu_SRC) $(LLMSSMatMGUT_mAmu_MMA) \
		$(MSSMatMGUT_mAmu_MK) $(MSSMatMGUT_mAmu_INCLUDE_MK) \
		$(MSSMatMGUT_mAmu_SLHA_INPUT) $(MSSMatMGUT_mAmu_REFERENCES) \
		$(MSSMatMGUT_mAmu_GNUPLOT)

$(LIBMSSMatMGUT_mAmu_SRC) $(LIBMSSMatMGUT_mAmu_HDR) $(EXEMSSMatMGUT_mAmu_SRC) $(LLMSSMatMGUT_mAmu_SRC) $(LLMSSMatMGUT_mAmu_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_MSSMatMGUT_mAmu)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_MSSMatMGUT_mAmu): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_MSSMatMGUT_mAmu)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_MSSMatMGUT_mAmu)"
		@echo "Note: to regenerate MSSMatMGUT_mAmu source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_MSSMatMGUT_mAmu)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_MSSMatMGUT_mAmu):
		@true
endif

$(LIBMSSMatMGUT_mAmu_DEP) $(EXEMSSMatMGUT_mAmu_DEP) $(LLMSSMatMGUT_mAmu_DEP) $(LIBMSSMatMGUT_mAmu_OBJ) $(EXEMSSMatMGUT_mAmu_OBJ) $(LLMSSMatMGUT_mAmu_OBJ) $(LLMSSMatMGUT_mAmu_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBMSSMatMGUT_mAmu_DEP) $(EXEMSSMatMGUT_mAmu_DEP) $(LLMSSMatMGUT_mAmu_DEP) $(LIBMSSMatMGUT_mAmu_OBJ) $(EXEMSSMatMGUT_mAmu_OBJ) $(LLMSSMatMGUT_mAmu_OBJ) $(LLMSSMatMGUT_mAmu_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLMSSMatMGUT_mAmu_OBJ) $(LLMSSMatMGUT_mAmu_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBMSSMatMGUT_mAmu): $(LIBMSSMatMGUT_mAmu_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBMSSMatMGUT_mAmu) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLMSSMatMGUT_mAmu_LIB): $(LLMSSMatMGUT_mAmu_OBJ) $(LIBMSSMatMGUT_mAmu) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBMSSMatMGUT_mAmu_DEP) $(EXEMSSMatMGUT_mAmu_DEP)
ALLSRC += $(LIBMSSMatMGUT_mAmu_SRC) $(EXEMSSMatMGUT_mAmu_SRC)
ALLLIB += $(LIBMSSMatMGUT_mAmu)
ALLEXE += $(EXEMSSMatMGUT_mAmu_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLMSSMatMGUT_mAmu_DEP)
ALLSRC += $(LLMSSMatMGUT_mAmu_SRC)
ALLLL  += $(LLMSSMatMGUT_mAmu_LIB)
endif
