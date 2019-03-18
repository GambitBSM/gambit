modname = NMSSM  # as an example  
PreDef = -DGENERATIONMIXING -DONLYDOUBLE
# setting various paths  
InDir = ../include
Mdir = ${InDir}
VPATH = 3-Body-Decays:LoopDecays:TwoLoopMasses:Observables:SM 
name = ../lib/libSPhenoNMSSM.a
 
# check if SARAH module and SPheno are compatibel  
minV=330.00 
cVersion =$(shell expr $(version) \>= $(minV))
#  
# options for various compilers  
#  
# Default Compiler  
F90=gfortran
comp= -c -O -module ${Mdir} -I${InDir}  
LFlagsB= -O  
# Intels ifort,debug modus  
ifeq (${F90},ifortg)  
F90=ifort  
comp= -c -g -module ${Mdir} -I${InDir}  
LFlagsB= -g  
endif  
# gfortran  
ifeq (${F90},gfortran)  
comp= -c -g -ffree-line-length-none -J${Mdir} -I${InDir}  
LFlagsB= -g  
endif  
# g95  
ifeq (${F90},g95)  
comp= -c -O -fmod=${Mdir} -I${InDir}  
LFlagsB= -O  
endif  
# Lahey F95 compiler  
ifeq (${F90},lf95)  
comp=-c -O -M ${Mdir} -I${InDir}  
LFlagsB=-O  
endif  
# NAG f95/2003  
ifeq (${F90},nagfor)  
comp= -c -O -mdir ${Mdir} -I${InDir}  
LFlagsB= -O -DONLYDOUBLE -mdir ${MDir} -I${InDir}  
endif   
.SUFFIXES : .o .ps .f90 .F90 .a 
bin/SPhenoNMSSM:
ifeq (${cVersion},1)
	 cd ../src ; ${MAKE} F90=${F90} 
	 ${MAKE} F90=${F90} ${name} 
	 ${MAKE} F90=${F90} SPhenoNMSSM.o 
	 ${F90} -c TwoLoopMasses/effpotasat.f 
	 ${F90} -o SPhenoNMSSM ${LFlagsB} SPhenoNMSSM.o effpotasat.o ../lib/libSPhenoNMSSM.a ../lib/libSPheno.a
	 mv SPhenoNMSSM ../bin
	 rm SPhenoNMSSM.o  
${name}:  ${name}(Settings.o) ${name}(Model_Data_NMSSM.o)  \
 ${name}(RGEs_NMSSM.o)   \
 ${name}(Couplings_NMSSM.o) ${name}(TreeLevelMasses_NMSSM.o) ${name}(TadpoleEquations_NMSSM.o) \
 ${name}(LoopCouplings_NMSSM.o) ${name}(CouplingsForDecays_NMSSM.o) \
 ${name}(TreeLevel_Decays_NMSSM.o) \
 ${name}(Glu_NMSSM.o)  ${name}(Chi_NMSSM.o)  ${name}(Cha_NMSSM.o)  ${name}(Sd_NMSSM.o)  ${name}(Su_NMSSM.o)  ${name}(Se_NMSSM.o)  ${name}(Sv_NMSSM.o)  \
${name}(AddLoopFunctions.o) ${name}(Kinematics.o) \
 ${name}(EffPotFunctions.o) ${name}(DerivativesEffPotFunctions.o) ${name}(EffectivePotential_NMSSM.o) \
 ${name}(2LPoleFunctions.o) ${name}(2LPole_NMSSM.o) \
 ${name}(TwoLoopHiggsMass_SARAH.o) \
 ${name}(LoopMasses_NMSSM.o) \
 ${name}(RGEs_SM_HC.o) ${name}(Couplings_SM_HC.o) ${name}(TreeLevelMasses_SM_HC.o) ${name}(LoopMasses_SM_HC.o)   \
${name}(CouplingsCT_NMSSM.o) \
${name}(Bremsstrahlung.o) ${name}(DecayFFS.o) ${name}(DecayFFV.o) ${name}(DecaySSS.o) ${name}(DecaySSV.o) ${name}(DecaySFF.o) ${name}(DecaySVV.o) \
 ${name}(LoopDecaySd_NMSSM.o)  ${name}(LoopDecaySu_NMSSM.o)  ${name}(LoopDecaySe_NMSSM.o)  ${name}(LoopDecaySv_NMSSM.o)  ${name}(LoopDecayhh_NMSSM.o)  ${name}(LoopDecayAh_NMSSM.o)  ${name}(LoopDecayHpm_NMSSM.o)  ${name}(LoopDecayGlu_NMSSM.o)  ${name}(LoopDecayChi_NMSSM.o)  ${name}(LoopDecayCha_NMSSM.o)  ${name}(LoopDecayFu_NMSSM.o) \
 ${name}(Wrapper_LoopDecay_Sd_NMSSM.o)  ${name}(Wrapper_LoopDecay_Su_NMSSM.o)  ${name}(Wrapper_LoopDecay_Se_NMSSM.o)  ${name}(Wrapper_LoopDecay_Sv_NMSSM.o)  ${name}(Wrapper_LoopDecay_hh_NMSSM.o)  ${name}(Wrapper_LoopDecay_Ah_NMSSM.o)  ${name}(Wrapper_LoopDecay_Hpm_NMSSM.o)  ${name}(Wrapper_LoopDecay_Glu_NMSSM.o)  ${name}(Wrapper_LoopDecay_Chi_NMSSM.o)  ${name}(Wrapper_LoopDecay_Cha_NMSSM.o)  ${name}(Wrapper_LoopDecay_Fu_NMSSM.o) ${name}(OneLoopDecays_NMSSM.o) \
 ${name}(BranchingRatios_NMSSM.o) ${name}(HiggsCS_NMSSM.o) ${name}(RunSM_NMSSM.o) \
 ${name}(Unitarity_NMSSM.o) \
${name}(FlavorKit_LFV_NMSSM.o) ${name}(FlavorKit_QFV_NMSSM.o) ${name}(FlavorKit_Observables_NMSSM.o)\
 ${name}(LowEnergy_NMSSM.o) \
 ${name}(Boundaries_NMSSM.o)  ${name}(InputOutput_NMSSM.o) 
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
	 rm -f bin/SPheno3 lib/*.a *~ */*.o */*~ include/*
#
# Suffix rules
#
.f90.a:
	 ${F90} ${comp} $< 
	 ar -ruc -U $@ $*.o
	 rm -f $*.o
.F90.a:
	 ${F90} ${comp} ${PreDef} $< 
	 ar -ruc -U $@ $*.o
	 rm -f $*.o
.f90.o:
	 ${F90} ${comp} $<
.f90.ps:
	 a2ps -o $*.ps $<
.h.ps:
	 a2ps -o $*.ps $<
