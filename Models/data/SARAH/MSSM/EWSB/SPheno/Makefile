modname = MSSM  # as an example  
PreDef = -DGENERATIONMIXING -DONLYDOUBLE
# setting various paths  
InDir = ../include
Mdir = ${InDir}
name = ../lib/libSPhenoMSSM.a
 
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
bin/SPhenoMSSM:
ifeq (${cVersion},1)
	 cd ../src ; ${MAKE} F90=${F90} 
	 ${MAKE} F90=${F90} ${name} 
	 ${MAKE} F90=${F90} SPhenoMSSM.o 
	 ${F90} -c effpotasat.f 
	 ${F90} -o SPhenoMSSM ${LFlagsB} SPhenoMSSM.o effpotasat.o ../lib/libSPhenoMSSM.a ../lib/libSPheno.a
	 mv SPhenoMSSM ../bin
	 rm SPhenoMSSM.o  
${name}:  ${name}(Model_Data_MSSM.o)  \
 ${name}(RGEs_MSSM.o)   \
 ${name}(Couplings_MSSM.o) ${name}(SusyMasses_MSSM.o) ${name}(TadpoleEquations_MSSM.o) \
 ${name}(LoopCouplings_MSSM.o) ${name}(CouplingsForDecays_MSSM.o) \
 ${name}(SusyDecays_MSSM.o) \
 ${name}(Glu_MSSM.o)  ${name}(Chi_MSSM.o)  ${name}(Cha_MSSM.o)  ${name}(Sd_MSSM.o)  ${name}(Su_MSSM.o)  ${name}(Se_MSSM.o)  ${name}(Sv_MSSM.o)  \
 ${name}(EffPotFunctions.o) ${name}(DerivativesEffPotFunctions.o) ${name}(EffectivePotential_MSSM.o) \
 ${name}(2LPoleFunctions.o) ${name}(2LPole_MSSM.o) \
 ${name}(BranchingRatios_MSSM.o) ${name}(TwoLoopHiggsMass_SARAH.o) ${name}(LoopMasses_MSSM.o) \
 ${name}(HiggsCS_MSSM.o) ${name}(RunSM_MSSM.o) \
 ${name}(FineTuning_MSSM.o) \
 ${name}(LowEnergy_MSSM.o) \
${name}(FlavorKit_LFV_MSSM.o) ${name}(FlavorKit_QFV_MSSM.o) ${name}(FlavorKit_Observables_MSSM.o)\
 ${name}(SugraRuns_MSSM.o)  ${name}(InputOutput_MSSM.o) 
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
