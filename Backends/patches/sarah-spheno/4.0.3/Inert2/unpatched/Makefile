modname = Inert2  # as an example  
PreDef = -DGENERATIONMIXING -DONLYDOUBLE
# setting various paths  
InDir = ../include
Mdir = ${InDir}
VPATH = 3-Body-Decays:LoopDecays:TwoLoopMasses:Observables:SM 
name = ../lib/libSPhenoInert2.a
 
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
bin/SPhenoInert2:
ifeq (${cVersion},1)
	 cd ../src ; ${MAKE} F90=${F90} 
	 ${MAKE} F90=${F90} ${name} 
	 ${MAKE} F90=${F90} SPhenoInert2.o 
	 ${F90} -o SPhenoInert2 ${LFlagsB} SPhenoInert2.o ../lib/libSPhenoInert2.a ../lib/libSPheno.a
	 mv SPhenoInert2 ../bin
	 rm SPhenoInert2.o  
${name}:  ${name}(Settings.o) ${name}(Model_Data_Inert2.o)  \
 ${name}(RGEs_Inert2.o)   \
 ${name}(Couplings_Inert2.o) ${name}(TreeLevelMasses_Inert2.o) ${name}(TadpoleEquations_Inert2.o) \
 ${name}(LoopCouplings_Inert2.o) ${name}(CouplingsForDecays_Inert2.o) \
 ${name}(TreeLevel_Decays_Inert2.o) \
 ${name}(Fu.o)  ${name}(Fe.o)  ${name}(Fd.o)  \
${name}(AddLoopFunctions.o) ${name}(Kinematics.o) \
 ${name}(2LPoleFunctions.o) ${name}(2LPole_Inert2.o) \
 ${name}(LoopMasses_Inert2.o) \
 ${name}(RGEs_SM_HC.o) ${name}(Couplings_SM_HC.o) ${name}(TreeLevelMasses_SM_HC.o) ${name}(LoopMasses_SM_HC.o)   \
${name}(CouplingsCT_Inert2.o) \
${name}(Bremsstrahlung.o) ${name}(DecayFFS.o) ${name}(DecayFFV.o) ${name}(DecaySSS.o) ${name}(DecaySSV.o) ${name}(DecaySFF.o) ${name}(DecaySVV.o) \
 ${name}(LoopDecayFu_Inert2.o)  ${name}(LoopDecayFe_Inert2.o)  ${name}(LoopDecayFd_Inert2.o)  ${name}(LoopDecayhh_Inert2.o)  ${name}(LoopDecayH0_Inert2.o)  ${name}(LoopDecayA0_Inert2.o)  ${name}(LoopDecayHp_Inert2.o) \
 ${name}(Wrapper_LoopDecay_Fu_Inert2.o)  ${name}(Wrapper_LoopDecay_Fe_Inert2.o)  ${name}(Wrapper_LoopDecay_Fd_Inert2.o)  ${name}(Wrapper_LoopDecay_hh_Inert2.o)  ${name}(Wrapper_LoopDecay_H0_Inert2.o)  ${name}(Wrapper_LoopDecay_A0_Inert2.o)  ${name}(Wrapper_LoopDecay_Hp_Inert2.o) ${name}(OneLoopDecays_Inert2.o) \
 ${name}(BranchingRatios_Inert2.o) ${name}(HiggsCS_Inert2.o) ${name}(RunSM_Inert2.o) \
${name}(FlavorKit_LFV_Inert2.o) ${name}(FlavorKit_QFV_Inert2.o) ${name}(FlavorKit_Observables_Inert2.o)\
 ${name}(LowEnergy_Inert2.o) \
 ${name}(Boundaries_Inert2.o)  ${name}(InputOutput_Inert2.o) 
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
