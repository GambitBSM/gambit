modname = NMSSMEFT  # as an example
PreDef = -DGENERATIONMIXING -DONLYDOUBLE
# setting various paths
InDir = ../include
Mdir = ${InDir}
VPATH = 3-Body-Decays:LoopDecays:TwoLoopMasses:Observables:SM
name = ../lib/libSPhenoNMSSMEFT.a
shared = lib/libSPhenoNMSSMEFT.so

# check if SARAH module and SPheno are compatibel
minV=330.00
cVersion =$(shell expr $(version) \>= $(minV))
#
# options for various compilers
#
# Default Compiler
F90=gfortran
comp= -c -O -fPIC -module ${Mdir} -I${InDir}
LFlagsB= -fPIC
# Intels ifort,debug modus
ifeq (${F90},ifortg)
F90=ifort
comp= -c -g -fPIC -module ${Mdir} -I${InDir}
LFlagsB= -g -fPIC
endif
# gfortran
ifeq (${F90},gfortran)
comp= -c -g -fPIC --free-line-length-none -J${Mdir} -I${InDir}
LFlagsB= -g -fPIC
endif
# g95
ifeq (${F90},g95)
comp= -c -O -fPIC -fmod=${Mdir} -I${InDir}
LFlagsB= -O -fPIC
endif
# Lahey F95 compiler
ifeq (${F90},lf95)
comp=-c -O -fPIC -M ${Mdir} -I${InDir}
LFlagsB=-O -fPIC
endif
# NAG f95/2003
ifeq (${F90},nagfor)
comp= -c -O -fpic -mdir ${Mdir} -I${InDir}
LFlagsB= -O -fpic -DONLYDOUBLE -mdir ${MDir} -I${InDir}
endif
.SUFFIXES : .o .ps .f90 .F90 .a
${shared}:
	cd ../src ; rm -f *.o ; ${MAKE} F90=${F90}
	${MAKE} F90=${F90} ${name}
	${MAKE} F90=${F90} SPhenoNMSSMEFT.o
	ar x ../lib/libSPhenoNMSSMEFT.a
	ar x ../lib/libSPheno.a
	${F90} -shared -o ../${shared} ${LFlagsB} *.o
	rm *.o
bin/SPhenoNMSSMEFT:
ifeq (${cVersion},1)
	 cd ../src ; ${MAKE} F90=${F90}
	 ${MAKE} F90=${F90} ${name}
	 ${MAKE} F90=${F90} SPhenoNMSSMEFT.o
	 ${F90} -c TwoLoopMasses/effpotasat.f
	 ${F90} -o SPhenoNMSSMEFT ${LFlagsB} SPhenoNMSSMEFT.o effpotasat.o ../lib/libSPhenoNMSSMEFT.a ../lib/libSPheno.a
	 mv SPhenoNMSSMEFT ../bin
	 rm SPhenoNMSSMEFT.o
${name}:  ${name}(Settings.o) ${name}(Model_Data_NMSSMEFT.o)  \
 ${name}(RGEs_NMSSMEFT.o)   \
 ${name}(Couplings_NMSSMEFT.o) ${name}(TreeLevelMasses_NMSSMEFT.o) ${name}(TadpoleEquations_NMSSMEFT.o) \
 ${name}(LoopCouplings_NMSSMEFT.o) ${name}(CouplingsForDecays_NMSSMEFT.o) \
 ${name}(TreeLevel_Decays_NMSSMEFT.o) \
 ${name}(Chi_NMSSMEFT.o)  ${name}(Cha_NMSSMEFT.o)  \
${name}(AddLoopFunctions.o) ${name}(Kinematics.o) \
 ${name}(EffPotFunctions.o) ${name}(DerivativesEffPotFunctions.o) ${name}(EffectivePotential_NMSSMEFT.o) \
 ${name}(2LPoleFunctions.o) ${name}(2LPole_NMSSMEFT.o) \
 ${name}(TwoLoopHiggsMass_SARAH.o) \
 ${name}(LoopMasses_NMSSMEFT.o) \
 ${name}(RGEs_SM_HC.o) ${name}(Couplings_SM_HC.o) ${name}(TreeLevelMasses_SM_HC.o) ${name}(LoopMasses_SM_HC.o)   \
${name}(CouplingsCT_NMSSMEFT.o) \
${name}(Bremsstrahlung.o) ${name}(DecayFFS.o) ${name}(DecayFFV.o) ${name}(DecaySSS.o) ${name}(DecaySSV.o) ${name}(DecaySFF.o) ${name}(DecaySVV.o) \
 ${name}(LoopDecayhh_NMSSMEFT.o)  ${name}(LoopDecayAh_NMSSMEFT.o)  ${name}(LoopDecayHpm_NMSSMEFT.o)  ${name}(LoopDecayChi_NMSSMEFT.o)  ${name}(LoopDecayCha_NMSSMEFT.o)  ${name}(LoopDecayFu_NMSSMEFT.o) \
 ${name}(Wrapper_LoopDecay_hh_NMSSMEFT.o)  ${name}(Wrapper_LoopDecay_Ah_NMSSMEFT.o)  ${name}(Wrapper_LoopDecay_Hpm_NMSSMEFT.o)  ${name}(Wrapper_LoopDecay_Chi_NMSSMEFT.o)  ${name}(Wrapper_LoopDecay_Cha_NMSSMEFT.o)  ${name}(Wrapper_LoopDecay_Fu_NMSSMEFT.o) ${name}(OneLoopDecays_NMSSMEFT.o) \
 ${name}(BranchingRatios_NMSSMEFT.o) ${name}(HiggsCS_NMSSMEFT.o) ${name}(RunSM_NMSSMEFT.o) \
 ${name}(LowEnergy_NMSSMEFT.o) \
${name}(FlavorKit_LFV_NMSSMEFT.o) ${name}(FlavorKit_QFV_NMSSMEFT.o) ${name}(FlavorKit_Observables_NMSSMEFT.o)\
 ${name}(Boundaries_NMSSMEFT.o)  ${name}(InputOutput_NMSSMEFT.o)
else
	 @echo -------------------------------------------------------------------
	 @echo ERROR:
	 @echo The installed SPheno is version not compatibel with this module
	 @echo Please, upgrade at least to SPheno version 3.3.0.
	 @echo The current SPheno version can be downloaded from
	 @echo http://www.hepforge.org/downloads/spheno
	 @echo -------------------------------------------------------------------
endif
clean:
	 rm -f *.o *~ */*.o */*~
cleanall:
	 rm -f bin/SPheno3 lib/*.a lib/*.so *~ */*.o */*~ include/*
#
# Suffix rules
#
.f90.a:
	 ${F90} ${comp} $<
	 ar -ruc $@ $*.o
	 rm -f $*.o
.F90.a:
	 ${F90} ${comp} ${PreDef} $<
	 ar -ruc $@ $*.o
	 rm -f $*.o
.f90.o:
	 ${F90} ${comp} $<
.f90.ps:
	 a2ps -o $*.ps $<
.h.ps:
	 a2ps -o $*.ps $<
