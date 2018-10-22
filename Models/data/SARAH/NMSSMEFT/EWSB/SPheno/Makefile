modname = NMSSM  # as an example  
PreDef = -DGENERATIONMIXING -DONLYDOUBLE
# setting various paths  
InDir = ../include
Mdir = ${InDir}
VPATH = 3-Body-Decays:LoopDecays:TwoLoopMasses:Observables
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
	cd ../src ; ${MAKE} F90=${F90}
	${MAKE} F90=${F90} ${name}
	${MAKE} F90=${F90} SPhenoNMSSM.o
	${F90} -shared -o ../${shared} ${LFlagsB} SPhenoNMSSM.o ../lib/libSPhenoNMSSMEFT.a ../lib/libSPheno.a
bin/SPhenoNMSSMEFT:
ifeq (${cVersion},1)
	 cd ../src ; ${MAKE} F90=${F90} 
	 ${MAKE} F90=${F90} ${name} 
	 ${MAKE} F90=${F90} SPhenoNMSSM.o 
	 ${F90} -o SPhenoNMSSMEFT ${LFlagsB} SPhenoNMSSM.o ../lib/libSPhenoNMSSMEFT.a ../lib/libSPheno.a
	 mv SPhenoNMSSMEFT ../bin
	 rm SPhenoNMSSM.o  
${name}:  ${name}(Model_Data_NMSSM.o)  \
 ${name}(RGEs_NMSSM.o)   \
 ${name}(Couplings_NMSSM.o) ${name}(TreeLevelMasses_NMSSM.o) ${name}(TadpoleEquations_NMSSM.o) \
 ${name}(LoopCouplings_NMSSM.o) ${name}(CouplingsForDecays_NMSSM.o) \
 ${name}(TreeLevel_Decays_NMSSM.o) \
 ${name}(Chi_NMSSM.o)  ${name}(Cha_NMSSM.o)  \
 ${name}(EffPotFunctions.o) ${name}(DerivativesEffPotFunctions.o) ${name}(EffectivePotential_NMSSM.o) \
 ${name}(2LPoleFunctions.o) ${name}(2LPole_NMSSM.o) \
${name}(AddLoopFunctions.o) ${name}(Kinematics.o) \
 ${name}(LoopMasses_NMSSM.o) \
 ${name}(BranchingRatios_NMSSM.o) ${name}(HiggsCS_NMSSM.o) ${name}(RunSM_NMSSM.o) \
 ${name}(LowEnergy_NMSSM.o) \
${name}(FlavorKit_LFV_NMSSM.o) ${name}(FlavorKit_QFV_NMSSM.o) ${name}(FlavorKit_Observables_NMSSM.o)\
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
	 rm -f bin/SPheno3 lib/*.a lib/*.so *~ */*.o */*~ include/*
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
