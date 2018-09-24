DIR          := models/CMSSM
MODNAME      := CMSSM
SARAH_MODEL  := MSSM
WITH_$(MODNAME) := yes

CMSSM_INSTALL_DIR := $(INSTALL_DIR)/$(DIR)

CMSSM_MK     := \
		$(DIR)/module.mk

CMSSM_SUSY_BETAS_MK := \
		$(DIR)/susy_betas.mk

CMSSM_SOFT_BETAS_MK := \
		$(DIR)/soft_betas.mk

CMSSM_FlexibleEFTHiggs_MK := \
		$(DIR)/FlexibleEFTHiggs.mk

CMSSM_INCLUDE_MK := \
		$(CMSSM_SUSY_BETAS_MK) \
		$(CMSSM_SOFT_BETAS_MK)

CMSSM_SLHA_INPUT := \
		$(DIR)/LesHouches.in.CMSSM_generated \
		$(DIR)/LesHouches.in.CMSSM

CMSSM_REFERENCES := \
		$(DIR)/CMSSM_references.tex

CMSSM_GNUPLOT := \
		$(DIR)/CMSSM_plot_rgflow.gnuplot \
		$(DIR)/CMSSM_plot_spectrum.gnuplot

CMSSM_TARBALL := \
		$(MODNAME).tar.gz

LIBCMSSM_SRC := \
		$(DIR)/CMSSM_a_muon.cpp \
		$(DIR)/CMSSM_edm.cpp \
		$(DIR)/CMSSM_effective_couplings.cpp \
		$(DIR)/CMSSM_info.cpp \
		$(DIR)/CMSSM_input_parameters.cpp \
		$(DIR)/CMSSM_mass_eigenstates.cpp \
		$(DIR)/CMSSM_observables.cpp \
		$(DIR)/CMSSM_physical.cpp \
		$(DIR)/CMSSM_slha_io.cpp \
		$(DIR)/CMSSM_soft_parameters.cpp \
		$(DIR)/CMSSM_susy_parameters.cpp \
		$(DIR)/CMSSM_utilities.cpp \
		$(DIR)/CMSSM_weinberg_angle.cpp

EXECMSSM_SRC := \
		$(DIR)/run_CMSSM.cpp \
		$(DIR)/run_cmd_line_CMSSM.cpp \
		$(DIR)/scan_CMSSM.cpp
LLCMSSM_LIB  :=
LLCMSSM_OBJ  :=
LLCMSSM_SRC  := \
		$(DIR)/CMSSM_librarylink.cpp

LLCMSSM_MMA  := \
		$(DIR)/CMSSM_librarylink.m \
		$(DIR)/run_CMSSM.m

LIBCMSSM_HDR := \
		$(DIR)/CMSSM_cxx_diagrams.hpp \
		$(DIR)/CMSSM_a_muon.hpp \
		$(DIR)/CMSSM_convergence_tester.hpp \
		$(DIR)/CMSSM_edm.hpp \
		$(DIR)/CMSSM_effective_couplings.hpp \
		$(DIR)/CMSSM_ewsb_solver.hpp \
		$(DIR)/CMSSM_ewsb_solver_interface.hpp \
		$(DIR)/CMSSM_high_scale_constraint.hpp \
		$(DIR)/CMSSM_info.hpp \
		$(DIR)/CMSSM_initial_guesser.hpp \
		$(DIR)/CMSSM_input_parameters.hpp \
		$(DIR)/CMSSM_low_scale_constraint.hpp \
		$(DIR)/CMSSM_mass_eigenstates.hpp \
		$(DIR)/CMSSM_model.hpp \
		$(DIR)/CMSSM_model_slha.hpp \
		$(DIR)/CMSSM_observables.hpp \
		$(DIR)/CMSSM_physical.hpp \
		$(DIR)/CMSSM_slha_io.hpp \
		$(DIR)/CMSSM_spectrum_generator.hpp \
		$(DIR)/CMSSM_spectrum_generator_interface.hpp \
		$(DIR)/CMSSM_soft_parameters.hpp \
		$(DIR)/CMSSM_susy_parameters.hpp \
		$(DIR)/CMSSM_susy_scale_constraint.hpp \
		$(DIR)/CMSSM_utilities.hpp \
		$(DIR)/CMSSM_weinberg_angle.hpp

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
-include $(CMSSM_SUSY_BETAS_MK)
-include $(CMSSM_SOFT_BETAS_MK)
-include $(CMSSM_FlexibleEFTHiggs_MK)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),pack-$(MODNAME)-src)
ifeq ($(findstring clean-,$(MAKECMDGOALS)),)
ifeq ($(findstring distclean-,$(MAKECMDGOALS)),)
ifeq ($(findstring doc-,$(MAKECMDGOALS)),)
$(CMSSM_SUSY_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(CMSSM_SOFT_BETAS_MK): run-metacode-$(MODNAME)
		@$(CONVERT_DOS_PATHS) $@
$(CMSSM_FlexibleEFTHiggs_MK): run-metacode-$(MODNAME)
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
LIBCMSSM_SRC := $(sort $(LIBCMSSM_SRC))
EXECMSSM_SRC := $(sort $(EXECMSSM_SRC))

LIBCMSSM_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(LIBCMSSM_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(LIBCMSSM_SRC)))

EXECMSSM_OBJ := \
		$(patsubst %.cpp, %.o, $(filter %.cpp, $(EXECMSSM_SRC))) \
		$(patsubst %.f, %.o, $(filter %.f, $(EXECMSSM_SRC)))

EXECMSSM_EXE := \
		$(patsubst %.cpp, %.x, $(filter %.cpp, $(EXECMSSM_SRC))) \
		$(patsubst %.f, %.x, $(filter %.f, $(EXECMSSM_SRC)))

LIBCMSSM_DEP := \
		$(LIBCMSSM_OBJ:.o=.d)

EXECMSSM_DEP := \
		$(EXECMSSM_OBJ:.o=.d)

LLCMSSM_DEP  := \
		$(patsubst %.cpp, %.d, $(filter %.cpp, $(LLCMSSM_SRC)))

LLCMSSM_OBJ  := $(LLCMSSM_SRC:.cpp=.o)
LLCMSSM_LIB  := $(LLCMSSM_SRC:.cpp=$(LIBLNK_LIBEXT))

LIBCMSSM     := $(DIR)/lib$(MODNAME)$(MODULE_LIBEXT)

METACODE_STAMP_CMSSM := $(DIR)/00_DELETE_ME_TO_RERUN_METACODE

ifeq ($(ENABLE_META),yes)
SARAH_MODEL_FILES_CMSSM := \
		$(shell $(SARAH_DEP_GEN) $(SARAH_MODEL))
endif

.PHONY:         all-$(MODNAME) clean-$(MODNAME) clean-$(MODNAME)-src \
		clean-$(MODNAME)-dep clean-$(MODNAME)-lib \
		clean-$(MODNAME)-obj distclean-$(MODNAME) \
		run-metacode-$(MODNAME) pack-$(MODNAME)-src

all-$(MODNAME): $(LIBCMSSM) $(EXECMSSM_EXE)
		@true

ifneq ($(INSTALL_DIR),)
install-src::
		install -d $(CMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBCMSSM_SRC) $(CMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LIBCMSSM_HDR) $(CMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(EXECMSSM_SRC) $(CMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLCMSSM_SRC) $(CMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(LLCMSSM_MMA) $(CMSSM_INSTALL_DIR)
		$(INSTALL_STRIPPED) $(CMSSM_MK) $(CMSSM_INSTALL_DIR) -m u=rw,g=r,o=r
		install -m u=rw,g=r,o=r $(CMSSM_INCLUDE_MK) $(CMSSM_INSTALL_DIR)
ifneq ($(CMSSM_SLHA_INPUT),)
		install -m u=rw,g=r,o=r $(CMSSM_SLHA_INPUT) $(CMSSM_INSTALL_DIR)
endif
		install -m u=rw,g=r,o=r $(CMSSM_REFERENCES) $(CMSSM_INSTALL_DIR)
		install -m u=rw,g=r,o=r $(CMSSM_GNUPLOT) $(CMSSM_INSTALL_DIR)
endif

clean-$(MODNAME)-dep:
		-rm -f $(LIBCMSSM_DEP)
		-rm -f $(EXECMSSM_DEP)
		-rm -f $(LLCMSSM_DEP)

clean-$(MODNAME)-lib:
		-rm -f $(LIBCMSSM)
		-rm -f $(LLCMSSM_LIB)

clean-$(MODNAME)-obj:
		-rm -f $(LIBCMSSM_OBJ)
		-rm -f $(EXECMSSM_OBJ)
		-rm -f $(LLCMSSM_OBJ)


clean-$(MODNAME): clean-$(MODNAME)-dep clean-$(MODNAME)-lib clean-$(MODNAME)-obj
		-rm -f $(EXECMSSM_EXE)

distclean-$(MODNAME): clean-$(MODNAME)
		@true

clean-generated:: clean-$(MODNAME)-src

clean-obj::     clean-$(MODNAME)-obj

clean::         clean-$(MODNAME)

distclean::     distclean-$(MODNAME)

pack-$(MODNAME)-src:
		tar -czf $(CMSSM_TARBALL) \
		$(LIBCMSSM_SRC) $(LIBCMSSM_HDR) \
		$(EXECMSSM_SRC) \
		$(LLCMSSM_SRC) $(LLCMSSM_MMA) \
		$(CMSSM_MK) $(CMSSM_INCLUDE_MK) \
		$(CMSSM_SLHA_INPUT) $(CMSSM_REFERENCES) \
		$(CMSSM_GNUPLOT)

$(LIBCMSSM_SRC) $(LIBCMSSM_HDR) $(EXECMSSM_SRC) $(LLCMSSM_SRC) $(LLCMSSM_MMA) \
: run-metacode-$(MODNAME)
		@true

run-metacode-$(MODNAME): $(METACODE_STAMP_CMSSM)
		@true

ifeq ($(ENABLE_META),yes)
$(METACODE_STAMP_CMSSM): $(DIR)/start.m $(DIR)/FlexibleSUSY.m $(META_SRC) $(TEMPLATES) $(SARAH_MODEL_FILES_CMSSM)
		"$(MATH)" -run "Get[\"$<\"]; Quit[]"
		@touch "$(METACODE_STAMP_CMSSM)"
		@echo "Note: to regenerate CMSSM source files," \
		      "please remove the file "
		@echo "\"$(METACODE_STAMP_CMSSM)\" and run make"
		@echo "---------------------------------"
else
$(METACODE_STAMP_CMSSM):
		@true
endif

$(LIBCMSSM_DEP) $(EXECMSSM_DEP) $(LLCMSSM_DEP) $(LIBCMSSM_OBJ) $(EXECMSSM_OBJ) $(LLCMSSM_OBJ) $(LLCMSSM_LIB): \
	CPPFLAGS += $(GSLFLAGS) $(EIGENFLAGS) $(BOOSTFLAGS) $(TSILFLAGS) $(HIMALAYAFLAGS)

ifneq (,$(findstring yes,$(ENABLE_LOOPTOOLS)$(ENABLE_FFLITE)))
$(LIBCMSSM_DEP) $(EXECMSSM_DEP) $(LLCMSSM_DEP) $(LIBCMSSM_OBJ) $(EXECMSSM_OBJ) $(LLCMSSM_OBJ) $(LLCMSSM_LIB): \
	CPPFLAGS += $(LOOPFUNCFLAGS)
endif

$(LLCMSSM_OBJ) $(LLCMSSM_LIB): \
	CPPFLAGS += $(shell $(MATH_INC_PATHS) --math-cmd="$(MATH)" -I --librarylink --mathlink)

$(LIBCMSSM): $(LIBCMSSM_OBJ)
		$(MODULE_MAKE_LIB_CMD) $@ $^

$(DIR)/%.x: $(DIR)/%.o $(LIBCMSSM) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(CXX) $(LDFLAGS) -o $@ $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

$(LLCMSSM_LIB): $(LLCMSSM_OBJ) $(LIBCMSSM) $(LIBFLEXI) $(filter-out -%,$(LOOPFUNCLIBS))
		$(LIBLNK_MAKE_LIB_CMD) $@ $(CPPFLAGS) $(CFLAGS) $(call abspathx,$(ADDONLIBS) $^ $(LIBGM2Calc)) $(filter -%,$(LOOPFUNCLIBS)) $(HIMALAYALIBS) $(GSLLIBS) $(BOOSTTHREADLIBS) $(LAPACKLIBS) $(BLASLIBS) $(FLIBS) $(SQLITELIBS) $(TSILLIBS) $(THREADLIBS) $(LDLIBS)

ALLDEP += $(LIBCMSSM_DEP) $(EXECMSSM_DEP)
ALLSRC += $(LIBCMSSM_SRC) $(EXECMSSM_SRC)
ALLLIB += $(LIBCMSSM)
ALLEXE += $(EXECMSSM_EXE)

ifeq ($(ENABLE_LIBRARYLINK),yes)
ALLDEP += $(LLCMSSM_DEP)
ALLSRC += $(LLCMSSM_SRC)
ALLLL  += $(LLCMSSM_LIB)
endif
