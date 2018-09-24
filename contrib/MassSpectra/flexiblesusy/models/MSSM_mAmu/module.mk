DIR          := models/MSSM_mAmu
MODNAME      := MSSM_mAmu
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes

MSSM_mAmu_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

MSSM_mAmu_MK     := \
		$(DIR)/module.mk

MSSM_mAmu_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

MSSM_mAmu_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

MSSM_mAmu_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

MSSM_mAmu_INCLUDE_MK := \
		$(MSSM_mAmu_SUSY_BETAS_MK) \
		$(MSSM_mAmu_SOFT_BETAS_MK)

MSSM_mAmu_SLHA_INPUT := \
		$(DIR)/LesHouches.in.MSSM_mAmu_generated \
		$(DIR)/LesHouches.in.MSSM_mAmu

MSSM_mAmu_REFERENCES := \
		$(DIR)/MSSM_mAmu_references.tex

MSSM_mAmu_GNUPLOT := \
		$(DIR)/MSSM_mAmu_plot_rgflow.gnuplot \
		$(DIR)/MSSM_mAmu_plot_spectrum.gnuplot

MSSM_mAmu_TARBALL := \
		$(MODNAME).tar.gz

LIBMSSM_mAmu_SRC := \
		$(DIR)/MSSM_mAmu_a_muon.cpp \
		$(DIR)/MSSM_mAmu_edm.cpp \
		$(DIR)/MSSM_mAmu_effective_couplings.cpp \
		$(DIR)/MSSM_mAmu_info.cpp \
		$(DIR)/MSSM_mAmu_input_parameters.cpp \
		$(DIR)/MSSM_mAmu_mass_eigenstates.cpp \
		$(DIR)/MSSM_mAmu_observables.cpp \
		$(DIR)/MSSM_mAmu_physical.cpp \
		$(DIR)/MSSM_mAmu_slha_io.cpp \
		$(DIR)/MSSM_mAmu_soft_parameters.cpp \
		$(DIR)/MSSM_mAmu_susy_parameters.cpp \
		$(DIR)/MSSM_mAmu_utilities.cpp \
		$(DIR)/MSSM_mAmu_weinberg_angle.cpp

EXEMSSM_mAmu_SRC := \
		$(DIR)/run_MSSM_mAmu.cpp \
		$(DIR)/run_cmd_line_MSSM_mAmu.cpp \
		$(DIR)/scan_MSSM_mAmu.cpp
LLMSSM_mAmu_LIB  :=
LLMSSM_mAmu_OBJ  :=
LLMSSM_mAmu_SRC  := \
		$(DIR)/MSSM_mAmu_librarylink.cpp

LLMSSM_mAmu_MMA  := \
		$(DIR)/MSSM_mAmu_librarylink.m \
		$(DIR)/run_MSSM_mAmu.m

LIBMSSM_mAmu_HDR := \
		$(DIR)/MSSM_mAmu_cxx_diagrams.hpp \
		$(DIR)/MSSM_mAmu_a_muon.hpp \
		$(DIR)/MSSM_mAmu_convergence_tester.hpp \
		$(DIR)/MSSM_mAmu_edm.hpp \
		$(DIR)/MSSM_mAmu_effective_couplings.hpp \
		$(DIR)/MSSM_mAmu_ewsb_solver.hpp \
		$(DIR)/MSSM_mAmu_ewsb_solver_interface.hpp \
		$(DIR)/MSSM_mAmu_high_scale_constraint.hpp \
		$(DIR)/MSSM_mAmu_info.hpp \
		$(DIR)/MSSM_mAmu_initial_guesser.hpp \
		$(DIR)/MSSM_mAmu_input_parameters.hpp \
		$(DIR)/MSSM_mAmu_low_scale_constraint.hpp \
		$(DIR)/MSSM_mAmu_mass_eigenstates.hpp \
		$(DIR)/MSSM_mAmu_model.hpp \
		$(DIR)/MSSM_mAmu_model_slha.hpp \
		$(DIR)/MSSM_mAmu_observables.hpp \
		$(DIR)/MSSM_mAmu_physical.hpp \
		$(DIR)/MSSM_mAmu_slha_io.hpp \
		$(DIR)/MSSM_mAmu_spectrum_generator.hpp \
		$(DIR)/MSSM_mAmu_spectrum_generator_interface.hpp \
		$(DIR)/MSSM_mAmu_soft_parameters.hpp \
		$(DIR)/MSSM_mAmu_susy_parameters.hpp \
		$(DIR)/MSSM_mAmu_susy_scale_constraint.hpp \
		$(DIR)/MSSM_mAmu_utilities.hpp \
		$(DIR)/MSSM_mAmu_weinberg_angle.hpp

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
-include $(MSSM_mAmu_SUSY_BETAS_MK)
-include $(MSSM_mAmu_SOFT_BETAS_MK)
-include $(MSSM_mAmu_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(MSSM_mAmu_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSM_mAmu_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(MSSM_mAmu_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBMSSM_mAmu_SRC := $(sort $(LIBMSSM_mAmu_SRC))
EXEMSSM_mAmu_SRC := $(sort $(EXEMSSM_mAmu_SRC))

LIBMSSM_mAmu_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBMSSM_mAmu_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBMSSM_mAmu_SRC)))

EXEMSSM_mAmu_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXEMSSM_mAmu_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXEMSSM_mAmu_SRC)))

EXEMSSM_mAmu_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXEMSSM_mAmu_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXEMSSM_mAmu_SRC)))

LIBMSSM_mAmu_DEP := \
		$(LIBMSSM_mAmu_OBJ:.o=.d)

EXEMSSM_mAmu_DEP := \
		$(EXEMSSM_mAmu_OBJ:.o=.d)

LLMSSM_mAmu_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLMSSM_mAmu_SRC)))

LLMSSM_mAmu_OBJ  := $(LLMSSM_mAmu_SRC:.cpp=.o)
LLMSSM_mAmu_LIB  := $(LLMSSM_mAmu_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBMSSM_mAmu     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_MSSM_mAmu := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_MSSM_mAmu := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBMSSM_mAmu) $(EXEMSSM_mAmu_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(MSSM_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSM_mAmu_SRC) $(MSSM_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBMSSM_mAmu_HDR) $(MSSM_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXEMSSM_mAmu_SRC) $(MSSM_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSM_mAmu_SRC) $(MSSM_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLMSSM_mAmu_MMA) $(MSSM_mAmu_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(MSSM_mAmu_MK) $(MSSM_mAmu_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(MSSM_mAmu_INCLUDE_MK) $(MSSM_mAmu_INSTALL_DIR)
ifneq ($(MSSM_mAmu_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(MSSM_mAmu_SLHA_INPUT) $(MSSM_mAmu_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(MSSM_mAmu_REFERENCES) $(MSSM_mAmu_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(MSSM_mAmu_GNUPLOT) $(MSSM_mAmu_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBMSSM_mAmu_DEP)
		-rm -f $(EXEMSSM_mAmu_DEP)
		-rm -f $(LLMSSM_mAmu_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBMSSM_mAmu)
		-rm -f $(LLMSSM_mAmu_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBMSSM_mAmu_OBJ)
		-rm -f $(EXEMSSM_mAmu_OBJ)
		-rm -f $(LLMSSM_mAmu_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXEMSSM_mAmu_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(MSSM_mAmu_TARBALL) \
		$(LIBMSSM_mAmu_SRC) $(LIBMSSM_mAmu_HDR) \
		$(EXEMSSM_mAmu_SRC) \
		$(LLMSSM_mAmu_SRC) $(LLMSSM_mAmu_MMA) \
		$(MSSM_mAmu_MK) $(MSSM_mAmu_INCLUDE_MK) \
		$(MSSM_mAmu_SLHA_INPUT) $(MSSM_mAmu_REFERENCES) \
		$(MSSM_mAmu_GNUPLOT)

$(LIBMSSM_mAmu_SRC) $(LIBMSSM_mAmu_HDR) $(EXEMSSM_mAmu_SRC) $(LLMSSM_mAmu_SRC) $(LLMSSM_mAmu_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_MSSM_mAmu)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_MSSM_mAmu): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_MSSM_mAmu)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_MSSM_mAmu)"
		@echo "Note: to regenerate MSSM_mAmu source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_MSSM_mAmu)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_MSSM_mAmu):
		@true
endif

$(LIBMSSM_mAmu_DEP) $(EXEMSSM_mAmu_DEP) $(LLMSSM_mAmu_DEP) $(LIBMSSM_mAmu_OBJ) $(EXEMSSM_mAmu_OBJ) $(LLMSSM_mAmu_OBJ) $(LLMSSM_mAmu_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBMSSM_mAmu_DEP) $(EXEMSSM_mAmu_DEP) $(LLMSSM_mAmu_DEP) $(LIBMSSM_mAmu_OBJ) $(EXEMSSM_mAmu_OBJ) $(LLMSSM_mAmu_OBJ) $(LLMSSM_mAmu_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLMSSM_mAmu_OBJ) $(LLMSSM_mAmu_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBMSSM_mAmu): $(LIBMSSM_mAmu_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBMSSM_mAmu) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLMSSM_mAmu_LIB): $(LLMSSM_mAmu_OBJ) $(LIBMSSM_mAmu) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBMSSM_mAmu_DEP) $(EXEMSSM_mAmu_DEP)
ALLSRC += $(LIBMSSM_mAmu_SRC) $(EXEMSSM_mAmu_SRC)
ALLLIB += $(LIBMSSM_mAmu)
ALLEXE += $(EXEMSSM_mAmu_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLMSSM_mAmu_DEP)
ALLSRC += $(LLMSSM_mAmu_SRC)
ALLLL  += $(LLMSSM_mAmu_LIB)
endif
