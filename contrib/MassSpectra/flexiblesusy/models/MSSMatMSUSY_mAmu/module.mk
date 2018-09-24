DIR          := models/MSSMatMSUSY_mAmu
MODNAME      := MSSMatMSUSY_mAmu
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes

MSSMatMSUSY_mAmu_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

MSSMatMSUSY_mAmu_MK     := \
		$(DIR)/module.mk

MSSMatMSUSY_mAmu_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

MSSMatMSUSY_mAmu_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

MSSMatMSUSY_mAmu_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

MSSMatMSUSY_mAmu_INCLUDE_MK := \
		$(MSSMatMSUSY_mAmu_SUSY_BETAS_MK) \
		$(MSSMatMSUSY_mAmu_SOFT_BETAS_MK)

MSSMatMSUSY_mAmu_SLHA_INPUT := \
		$(DIR)/LesHouches.in.MSSMatMSUSY_mAmu_generated \
		$(DIR)/LesHouches.in.lowMSSM

MSSMatMSUSY_mAmu_REFERENCES := \
		$(DIR)/MSSMatMSUSY_mAmu_references.tex

MSSMatMSUSY_mAmu_GNUPLOT := \
		$(DIR)/MSSMatMSUSY_mAmu_plot_rgflow.gnuplot \
		$(DIR)/MSSMatMSUSY_mAmu_plot_spectrum.gnuplot

MSSMatMSUSY_mAmu_TARBALL := \
		$(MODNAME).tar.gz

LIBMSSMatMSUSY_mAmu_SRC := \
		$(DIR)/MSSMatMSUSY_mAmu_a_muon.cpp \
		$(DIR)/MSSMatMSUSY_mAmu_edm.cpp \
		$(DIR)/MSSMatMSUSY_mAmu_effective_couplings.cpp \
		$(DIR)/MSSMatMSUSY_mAmu_info.cpp \
		$(DIR)/MSSMatMSUSY_mAmu_input_parameters.cpp \
		$(DIR)/MSSMatMSUSY_mAmu_mass_eigenstates.cpp \
		$(DIR)/MSSMatMSUSY_mAmu_observables.cpp \
		$(DIR)/MSSMatMSUSY_mAmu_physical.cpp \
		$(DIR)/MSSMatMSUSY_mAmu_slha_io.cpp \
		$(DIR)/MSSMatMSUSY_mAmu_soft_parameters.cpp \
		$(DIR)/MSSMatMSUSY_mAmu_susy_parameters.cpp \
		$(DIR)/MSSMatMSUSY_mAmu_utilities.cpp \
		$(DIR)/MSSMatMSUSY_mAmu_weinberg_angle.cpp

EXEMSSMatMSUSY_mAmu_SRC := \
		$(DIR)/run_MSSMatMSUSY_mAmu.cpp \
		$(DIR)/run_cmd_line_MSSMatMSUSY_mAmu.cpp \
		$(DIR)/scan_MSSMatMSUSY_mAmu.cpp
LLMSSMatMSUSY_mAmu_LIB  :=
LLMSSMatMSUSY_mAmu_OBJ  :=
LLMSSMatMSUSY_mAmu_SRC  := \
		$(DIR)/MSSMatMSUSY_mAmu_librarylink.cpp

LLMSSMatMSUSY_mAmu_MMA  := \
		$(DIR)/MSSMatMSUSY_mAmu_librarylink.m \
		$(DIR)/run_MSSMatMSUSY_mAmu.m

LIBMSSMatMSUSY_mAmu_HDR := \
		$(DIR)/MSSMatMSUSY_mAmu_cxx_diagrams.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_a_muon.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_convergence_tester.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_edm.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_effective_couplings.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_ewsb_solver.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_ewsb_solver_interface.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_high_scale_constraint.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_info.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_initial_guesser.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_input_parameters.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_low_scale_constraint.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_mass_eigenstates.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_model.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_model_slha.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_observables.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_physical.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_slha_io.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_spectrum_generator.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_spectrum_generator_interface.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_soft_parameters.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_susy_parameters.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_susy_scale_constraint.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_utilities.hpp \
		$(DIR)/MSSMatMSUSY_mAmu_weinberg_angle.hpp

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
-include $(MSSMatMSUSY_mAmu_SUSY_BETAS_MK)
-include $(MSSMatMSUSY_mAmu_SOFT_BETAS_MK)
-include $(MSSMatMSUSY_mAmu_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(MSSMatMSUSY_mAmu_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMatMSUSY_mAmu_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMatMSUSY_mAmu_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBMSSMatMSUSY_mAmu_SRC := $(sort $(LIBMSSMatMSUSY_mAmu_SRC))
EXEMSSMatMSUSY_mAmu_SRC := $(sort $(EXEMSSMatMSUSY_mAmu_SRC))

LIBMSSMatMSUSY_mAmu_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBMSSMatMSUSY_mAmu_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBMSSMatMSUSY_mAmu_SRC)))

EXEMSSMatMSUSY_mAmu_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXEMSSMatMSUSY_mAmu_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXEMSSMatMSUSY_mAmu_SRC)))

EXEMSSMatMSUSY_mAmu_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXEMSSMatMSUSY_mAmu_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXEMSSMatMSUSY_mAmu_SRC)))

LIBMSSMatMSUSY_mAmu_DEP := \
		$(LIBMSSMatMSUSY_mAmu_OBJ:.o=.d)

EXEMSSMatMSUSY_mAmu_DEP := \
		$(EXEMSSMatMSUSY_mAmu_OBJ:.o=.d)

LLMSSMatMSUSY_mAmu_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLMSSMatMSUSY_mAmu_SRC)))

LLMSSMatMSUSY_mAmu_OBJ  := $(LLMSSMatMSUSY_mAmu_SRC:.cpp=.o)
LLMSSMatMSUSY_mAmu_LIB  := $(LLMSSMatMSUSY_mAmu_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBMSSMatMSUSY_mAmu     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_MSSMatMSUSY_mAmu := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_MSSMatMSUSY_mAmu := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBMSSMatMSUSY_mAmu) $(EXEMSSMatMSUSY_mAmu_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(MSSMatMSUSY_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMatMSUSY_mAmu_SRC) $(MSSMatMSUSY_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMatMSUSY_mAmu_HDR) $(MSSMatMSUSY_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXEMSSMatMSUSY_mAmu_SRC) $(MSSMatMSUSY_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMatMSUSY_mAmu_SRC) $(MSSMatMSUSY_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMatMSUSY_mAmu_MMA) $(MSSMatMSUSY_mAmu_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(MSSMatMSUSY_mAmu_MK) $(MSSMatMSUSY_mAmu_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(MSSMatMSUSY_mAmu_INCLUDE_MK) $(MSSMatMSUSY_mAmu_INSTALL_DIR)
ifneq ($(MSSMatMSUSY_mAmu_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(MSSMatMSUSY_mAmu_SLHA_INPUT) $(MSSMatMSUSY_mAmu_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(MSSMatMSUSY_mAmu_REFERENCES) $(MSSMatMSUSY_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(MSSMatMSUSY_mAmu_GNUPLOT) $(MSSMatMSUSY_mAmu_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBMSSMatMSUSY_mAmu_DEP)
		-rm -f $(EXEMSSMatMSUSY_mAmu_DEP)
		-rm -f $(LLMSSMatMSUSY_mAmu_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBMSSMatMSUSY_mAmu)
		-rm -f $(LLMSSMatMSUSY_mAmu_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBMSSMatMSUSY_mAmu_OBJ)
		-rm -f $(EXEMSSMatMSUSY_mAmu_OBJ)
		-rm -f $(LLMSSMatMSUSY_mAmu_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXEMSSMatMSUSY_mAmu_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(MSSMatMSUSY_mAmu_TARBALL) \
		$(LIBMSSMatMSUSY_mAmu_SRC) $(LIBMSSMatMSUSY_mAmu_HDR) \
		$(EXEMSSMatMSUSY_mAmu_SRC) \
		$(LLMSSMatMSUSY_mAmu_SRC) $(LLMSSMatMSUSY_mAmu_MMA) \
		$(MSSMatMSUSY_mAmu_MK) $(MSSMatMSUSY_mAmu_INCLUDE_MK) \
		$(MSSMatMSUSY_mAmu_SLHA_INPUT) $(MSSMatMSUSY_mAmu_REFERENCES) \
		$(MSSMatMSUSY_mAmu_GNUPLOT)

$(LIBMSSMatMSUSY_mAmu_SRC) $(LIBMSSMatMSUSY_mAmu_HDR) $(EXEMSSMatMSUSY_mAmu_SRC) $(LLMSSMatMSUSY_mAmu_SRC) $(LLMSSMatMSUSY_mAmu_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_MSSMatMSUSY_mAmu)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_MSSMatMSUSY_mAmu): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_MSSMatMSUSY_mAmu)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_MSSMatMSUSY_mAmu)"
		@echo "Note: to regenerate MSSMatMSUSY_mAmu source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_MSSMatMSUSY_mAmu)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_MSSMatMSUSY_mAmu):
		@true
endif

$(LIBMSSMatMSUSY_mAmu_DEP) $(EXEMSSMatMSUSY_mAmu_DEP) $(LLMSSMatMSUSY_mAmu_DEP) $(LIBMSSMatMSUSY_mAmu_OBJ) $(EXEMSSMatMSUSY_mAmu_OBJ) $(LLMSSMatMSUSY_mAmu_OBJ) $(LLMSSMatMSUSY_mAmu_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBMSSMatMSUSY_mAmu_DEP) $(EXEMSSMatMSUSY_mAmu_DEP) $(LLMSSMatMSUSY_mAmu_DEP) $(LIBMSSMatMSUSY_mAmu_OBJ) $(EXEMSSMatMSUSY_mAmu_OBJ) $(LLMSSMatMSUSY_mAmu_OBJ) $(LLMSSMatMSUSY_mAmu_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLMSSMatMSUSY_mAmu_OBJ) $(LLMSSMatMSUSY_mAmu_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBMSSMatMSUSY_mAmu): $(LIBMSSMatMSUSY_mAmu_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBMSSMatMSUSY_mAmu) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLMSSMatMSUSY_mAmu_LIB): $(LLMSSMatMSUSY_mAmu_OBJ) $(LIBMSSMatMSUSY_mAmu) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBMSSMatMSUSY_mAmu_DEP) $(EXEMSSMatMSUSY_mAmu_DEP)
ALLSRC += $(LIBMSSMatMSUSY_mAmu_SRC) $(EXEMSSMatMSUSY_mAmu_SRC)
ALLLIB += $(LIBMSSMatMSUSY_mAmu)
ALLEXE += $(EXEMSSMatMSUSY_mAmu_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLMSSMatMSUSY_mAmu_DEP)
ALLSRC += $(LLMSSMatMSUSY_mAmu_SRC)
ALLLL  += $(LLMSSMatMSUSY_mAmu_LIB)
endif
