HEADING='=============================='
BLUE="\n${HEADING}\n\033[1;34m[GAMBIT-BUILD]  "
NO_COL="\033[0m\n${HEADING}\n\n"

echo -e "${BLUE}running gambit scan${NO_COL}"
export OMP_NUM_THREADS=1
# export slots=32
(mkdir ../work || true) && \
cd .. && \
rm -rf work/*

# won't work on Gadi
cd work && \
mpiexec -np 12 ../gambit -rf ../yaml_files/THDM_physical.yaml > out.txt

# export I_MPI_DEBUG=5 && \
# export OMP_NUM_THREADS=1 && \
# export I_MPI_HYDRA_BRANCH_COUNT=$(($PBS_NCPUS / 48)) && \
# export HOSTFILE=hosts_${PBS_JOBID}.txt && \
# uniq < ${PBS_NODEFILE} > ${HOSTFILE} && \
# export CPN=$( grep -c ${HOSTNAME} ${PBS_NODEFILE} ) && \
# cd work

# # Intel MPI command
# mpirun -np $(( ${PBS_NCPUS}/${OMP_NUM_THREADS} )) -ppn $(( ${CPN}/${OMP_NUM_THREADS} )) -f ../${HOSTFILE} ../gambit -f ../yaml_files/THDMI.yaml

# # OpenMPI command
# # mpirun -np -npernode $(( ${CPN}/${OMP_NUM_THREADS} )) -hostfile ${HOSTFILE} -output-filename stdout ${GDIR}/gambit -f ${GDIR}/${YAMLF}

# # -outfile-pattern=stdout/out-%r -errfile-pattern=stderr/err-%r
# rm ../${HOSTFILE}
