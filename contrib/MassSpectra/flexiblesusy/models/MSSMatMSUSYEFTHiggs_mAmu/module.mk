DIR          := models/MSSMatMSUSYEFTHiggs_mAmu
MODNAME      := MSSMatMSUSYEFTHiggs_mAmu
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes

MSSMatMSUSYEFTHiggs_mAmu_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

MSSMatMSUSYEFTHiggs_mAmu_MK     := \
		$(DIR)/module.mk

MSSMatMSUSYEFTHiggs_mAmu_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

MSSMatMSUSYEFTHiggs_mAmu_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

MSSMatMSUSYEFTHiggs_mAmu_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

MSSMatMSUSYEFTHiggs_mAmu_INCLUDE_MK := \
		$(MSSMatMSUSYEFTHiggs_mAmu_SUSY_BETAS_MK) \
		$(MSSMatMSUSYEFTHiggs_mAmu_SOFT_BETAS_MK)

MSSMatMSUSYEFTHiggs_mAmu_SLHA_INPUT := \
		$(DIR)/LesHouches.in.MSSMatMSUSYEFTHiggs_mAmu_generated \
		$(DIR)/LesHouches.in.MSSMEFTHiggs

MSSMatMSUSYEFTHiggs_mAmu_REFERENCES := \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_references.tex

MSSMatMSUSYEFTHiggs_mAmu_GNUPLOT := \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_plot_rgflow.gnuplot \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_plot_spectrum.gnuplot

MSSMatMSUSYEFTHiggs_mAmu_TARBALL := \
		$(MODNAME).tar.gz

LIBMSSMatMSUSYEFTHiggs_mAmu_SRC := \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_a_muon.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_edm.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_effective_couplings.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_info.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_input_parameters.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_mass_eigenstates.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_observables.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_physical.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_slha_io.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_soft_parameters.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_susy_parameters.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_utilities.cpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_weinberg_angle.cpp

EXEMSSMatMSUSYEFTHiggs_mAmu_SRC := \
		$(DIR)/run_MSSMatMSUSYEFTHiggs_mAmu.cpp \
		$(DIR)/run_cmd_line_MSSMatMSUSYEFTHiggs_mAmu.cpp \
		$(DIR)/scan_MSSMatMSUSYEFTHiggs_mAmu.cpp
LLMSSMatMSUSYEFTHiggs_mAmu_LIB  :=
LLMSSMatMSUSYEFTHiggs_mAmu_OBJ  :=
LLMSSMatMSUSYEFTHiggs_mAmu_SRC  := \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_librarylink.cpp

LLMSSMatMSUSYEFTHiggs_mAmu_MMA  := \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_librarylink.m \
		$(DIR)/run_MSSMatMSUSYEFTHiggs_mAmu.m

LIBMSSMatMSUSYEFTHiggs_mAmu_HDR := \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_cxx_diagrams.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_a_muon.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_convergence_tester.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_edm.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_effective_couplings.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_ewsb_solver.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_ewsb_solver_interface.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_high_scale_constraint.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_info.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_initial_guesser.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_input_parameters.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_low_scale_constraint.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_mass_eigenstates.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_model.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_model_slha.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_observables.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_physical.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_slha_io.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_spectrum_generator.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_spectrum_generator_interface.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_soft_parameters.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_susy_parameters.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_susy_scale_constraint.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_utilities.hpp \
		$(DIR)/MSSMatMSUSYEFTHiggs_mAmu_weinberg_angle.hpp

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
-include $(MSSMatMSUSYEFTHiggs_mAmu_SUSY_BETAS_MK)
-include $(MSSMatMSUSYEFTHiggs_mAmu_SOFT_BETAS_MK)
-include $(MSSMatMSUSYEFTHiggs_mAmu_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(MSSMatMSUSYEFTHiggs_mAmu_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMatMSUSYEFTHiggs_mAmu_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSMatMSUSYEFTHiggs_mAmu_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBMSSMatMSUSYEFTHiggs_mAmu_SRC := $(sort $(LIBMSSMatMSUSYEFTHiggs_mAmu_SRC))
EXEMSSMatMSUSYEFTHiggs_mAmu_SRC := $(sort $(EXEMSSMatMSUSYEFTHiggs_mAmu_SRC))

LIBMSSMatMSUSYEFTHiggs_mAmu_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBMSSMatMSUSYEFTHiggs_mAmu_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBMSSMatMSUSYEFTHiggs_mAmu_SRC)))

EXEMSSMatMSUSYEFTHiggs_mAmu_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXEMSSMatMSUSYEFTHiggs_mAmu_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXEMSSMatMSUSYEFTHiggs_mAmu_SRC)))

EXEMSSMatMSUSYEFTHiggs_mAmu_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXEMSSMatMSUSYEFTHiggs_mAmu_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXEMSSMatMSUSYEFTHiggs_mAmu_SRC)))

LIBMSSMatMSUSYEFTHiggs_mAmu_DEP := \
		$(LIBMSSMatMSUSYEFTHiggs_mAmu_OBJ:.o=.d)

EXEMSSMatMSUSYEFTHiggs_mAmu_DEP := \
		$(EXEMSSMatMSUSYEFTHiggs_mAmu_OBJ:.o=.d)

LLMSSMatMSUSYEFTHiggs_mAmu_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLMSSMatMSUSYEFTHiggs_mAmu_SRC)))

LLMSSMatMSUSYEFTHiggs_mAmu_OBJ  := $(LLMSSMatMSUSYEFTHiggs_mAmu_SRC:.cpp=.o)
LLMSSMatMSUSYEFTHiggs_mAmu_LIB  := $(LLMSSMatMSUSYEFTHiggs_mAmu_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBMSSMatMSUSYEFTHiggs_mAmu     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_MSSMatMSUSYEFTHiggs_mAmu := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_MSSMatMSUSYEFTHiggs_mAmu := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBMSSMatMSUSYEFTHiggs_mAmu) $(EXEMSSMatMSUSYEFTHiggs_mAmu_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(MSSMatMSUSYEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMatMSUSYEFTHiggs_mAmu_SRC) $(MSSMatMSUSYEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSMatMSUSYEFTHiggs_mAmu_HDR) $(MSSMatMSUSYEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXEMSSMatMSUSYEFTHiggs_mAmu_SRC) $(MSSMatMSUSYEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMatMSUSYEFTHiggs_mAmu_SRC) $(MSSMatMSUSYEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSMatMSUSYEFTHiggs_mAmu_MMA) $(MSSMatMSUSYEFTHiggs_mAmu_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(MSSMatMSUSYEFTHiggs_mAmu_MK) $(MSSMatMSUSYEFTHiggs_mAmu_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(MSSMatMSUSYEFTHiggs_mAmu_INCLUDE_MK) $(MSSMatMSUSYEFTHiggs_mAmu_INSTALL_DIR)
ifneq ($(MSSMatMSUSYEFTHiggs_mAmu_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(MSSMatMSUSYEFTHiggs_mAmu_SLHA_INPUT) $(MSSMatMSUSYEFTHiggs_mAmu_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(MSSMatMSUSYEFTHiggs_mAmu_REFERENCES) $(MSSMatMSUSYEFTHiggs_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(MSSMatMSUSYEFTHiggs_mAmu_GNUPLOT) $(MSSMatMSUSYEFTHiggs_mAmu_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBMSSMatMSUSYEFTHiggs_mAmu_DEP)
		-rm -f $(EXEMSSMatMSUSYEFTHiggs_mAmu_DEP)
		-rm -f $(LLMSSMatMSUSYEFTHiggs_mAmu_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBMSSMatMSUSYEFTHiggs_mAmu)
		-rm -f $(LLMSSMatMSUSYEFTHiggs_mAmu_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBMSSMatMSUSYEFTHiggs_mAmu_OBJ)
		-rm -f $(EXEMSSMatMSUSYEFTHiggs_mAmu_OBJ)
		-rm -f $(LLMSSMatMSUSYEFTHiggs_mAmu_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXEMSSMatMSUSYEFTHiggs_mAmu_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(MSSMatMSUSYEFTHiggs_mAmu_TARBALL) \
		$(LIBMSSMatMSUSYEFTHiggs_mAmu_SRC) $(LIBMSSMatMSUSYEFTHiggs_mAmu_HDR) \
		$(EXEMSSMatMSUSYEFTHiggs_mAmu_SRC) \
		$(LLMSSMatMSUSYEFTHiggs_mAmu_SRC) $(LLMSSMatMSUSYEFTHiggs_mAmu_MMA) \
		$(MSSMatMSUSYEFTHiggs_mAmu_MK) $(MSSMatMSUSYEFTHiggs_mAmu_INCLUDE_MK) \
		$(MSSMatMSUSYEFTHiggs_mAmu_SLHA_INPUT) $(MSSMatMSUSYEFTHiggs_mAmu_REFERENCES) \
		$(MSSMatMSUSYEFTHiggs_mAmu_GNUPLOT)

$(LIBMSSMatMSUSYEFTHiggs_mAmu_SRC) $(LIBMSSMatMSUSYEFTHiggs_mAmu_HDR) $(EXEMSSMatMSUSYEFTHiggs_mAmu_SRC) $(LLMSSMatMSUSYEFTHiggs_mAmu_SRC) $(LLMSSMatMSUSYEFTHiggs_mAmu_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_MSSMatMSUSYEFTHiggs_mAmu)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_MSSMatMSUSYEFTHiggs_mAmu): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_MSSMatMSUSYEFTHiggs_mAmu)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_MSSMatMSUSYEFTHiggs_mAmu)"
		@echo "Note: to regenerate MSSMatMSUSYEFTHiggs_mAmu source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_MSSMatMSUSYEFTHiggs_mAmu)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_MSSMatMSUSYEFTHiggs_mAmu):
		@true
endif

$(LIBMSSMatMSUSYEFTHiggs_mAmu_DEP) $(EXEMSSMatMSUSYEFTHiggs_mAmu_DEP) $(LLMSSMatMSUSYEFTHiggs_mAmu_DEP) $(LIBMSSMatMSUSYEFTHiggs_mAmu_OBJ) $(EXEMSSMatMSUSYEFTHiggs_mAmu_OBJ) $(LLMSSMatMSUSYEFTHiggs_mAmu_OBJ) $(LLMSSMatMSUSYEFTHiggs_mAmu_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBMSSMatMSUSYEFTHiggs_mAmu_DEP) $(EXEMSSMatMSUSYEFTHiggs_mAmu_DEP) $(LLMSSMatMSUSYEFTHiggs_mAmu_DEP) $(LIBMSSMatMSUSYEFTHiggs_mAmu_OBJ) $(EXEMSSMatMSUSYEFTHiggs_mAmu_OBJ) $(LLMSSMatMSUSYEFTHiggs_mAmu_OBJ) $(LLMSSMatMSUSYEFTHiggs_mAmu_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLMSSMatMSUSYEFTHiggs_mAmu_OBJ) $(LLMSSMatMSUSYEFTHiggs_mAmu_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBMSSMatMSUSYEFTHiggs_mAmu): $(LIBMSSMatMSUSYEFTHiggs_mAmu_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBMSSMatMSUSYEFTHiggs_mAmu) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLMSSMatMSUSYEFTHiggs_mAmu_LIB): $(LLMSSMatMSUSYEFTHiggs_mAmu_OBJ) $(LIBMSSMatMSUSYEFTHiggs_mAmu) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBMSSMatMSUSYEFTHiggs_mAmu_DEP) $(EXEMSSMatMSUSYEFTHiggs_mAmu_DEP)
ALLSRC += $(LIBMSSMatMSUSYEFTHiggs_mAmu_SRC) $(EXEMSSMatMSUSYEFTHiggs_mAmu_SRC)
ALLLIB += $(LIBMSSMatMSUSYEFTHiggs_mAmu)
ALLEXE += $(EXEMSSMatMSUSYEFTHiggs_mAmu_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLMSSMatMSUSYEFTHiggs_mAmu_DEP)
ALLSRC += $(LLMSSMatMSUSYEFTHiggs_mAmu_SRC)
ALLLL  += $(LLMSSMatMSUSYEFTHiggs_mAmu_LIB)
endif
