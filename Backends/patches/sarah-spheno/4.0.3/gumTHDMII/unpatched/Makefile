modname = gumTHDMII  # as an example  
PreDef = -DGENERATIONMIXING -DONLYDOUBLE
# setting various paths  
InDir = ../include
Mdir = ${InDir}
VPATH = 3-Body-Decays:LoopDecays:TwoLoopMasses:Observables:SM 
name = ../lib/libSPhenogumTHDMII.a
 
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
bin/SPhenogumTHDMII:
ifeq (${cVersion},1)
	 cd ../src ; ${MAKE} F90=${F90} 
	 ${MAKE} F90=${F90} ${name} 
	 ${MAKE} F90=${F90} SPhenogumTHDMII.o 
	 ${F90} -o SPhenogumTHDMII ${LFlagsB} SPhenogumTHDMII.o ../lib/libSPhenogumTHDMII.a ../lib/libSPheno.a
	 mv SPhenogumTHDMII ../bin
	 rm SPhenogumTHDMII.o  
${name}:  ${name}(Settings.o) ${name}(Model_Data_gumTHDMII.o)  \
 ${name}(RGEs_gumTHDMII.o)   \
 ${name}(Couplings_gumTHDMII.o) ${name}(TreeLevelMasses_gumTHDMII.o) ${name}(TadpoleEquations_gumTHDMII.o) \
 ${name}(LoopCouplings_gumTHDMII.o) ${name}(CouplingsForDecays_gumTHDMII.o) \
 ${name}(TreeLevel_Decays_gumTHDMII.o) \
 ${name}(Fu.o)  ${name}(Fe.o)  ${name}(Fd.o)  \
${name}(AddLoopFunctions.o) ${name}(Kinematics.o) \
 ${name}(2LPoleFunctions.o) ${name}(2LPole_gumTHDMII.o) \
 ${name}(LoopMasses_gumTHDMII.o) \
 ${name}(RGEs_SM_HC.o) ${name}(Couplings_SM_HC.o) ${name}(TreeLevelMasses_SM_HC.o) ${name}(LoopMasses_SM_HC.o)   \
${name}(CouplingsCT_gumTHDMII.o) \
${name}(Bremsstrahlung.o) ${name}(DecayFFS.o) ${name}(DecayFFV.o) ${name}(DecaySSS.o) ${name}(DecaySSV.o) ${name}(DecaySFF.o) ${name}(DecaySVV.o) \
 ${name}(LoopDecayFu_gumTHDMII.o)  ${name}(LoopDecayFe_gumTHDMII.o)  ${name}(LoopDecayFd_gumTHDMII.o)  ${name}(LoopDecayhh_gumTHDMII.o)  ${name}(LoopDecayAh_gumTHDMII.o)  ${name}(LoopDecayHm_gumTHDMII.o) \
 ${name}(Wrapper_LoopDecay_Fu_gumTHDMII.o)  ${name}(Wrapper_LoopDecay_Fe_gumTHDMII.o)  ${name}(Wrapper_LoopDecay_Fd_gumTHDMII.o)  ${name}(Wrapper_LoopDecay_hh_gumTHDMII.o)  ${name}(Wrapper_LoopDecay_Ah_gumTHDMII.o)  ${name}(Wrapper_LoopDecay_Hm_gumTHDMII.o) ${name}(OneLoopDecays_gumTHDMII.o) \
 ${name}(BranchingRatios_gumTHDMII.o) ${name}(HiggsCS_gumTHDMII.o) ${name}(RunSM_gumTHDMII.o) \
 ${name}(Unitarity_gumTHDMII.o) \
${name}(FlavorKit_LFV_gumTHDMII.o) ${name}(FlavorKit_QFV_gumTHDMII.o) ${name}(FlavorKit_Observables_gumTHDMII.o)\
 ${name}(LowEnergy_gumTHDMII.o) \
 ${name}(Boundaries_gumTHDMII.o)  ${name}(InputOutput_gumTHDMII.o) 
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
