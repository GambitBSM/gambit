HEADING='=============================='
BLUE="\n${HEADING}\n\033[1;34m[GAMBIT-BUILD]  "
NO_COL="\033[0m\n${HEADING}\n\n"

echo -e "${BLUE}running gambit scan${NO_COL}"
export OMP_NUM_THREADS=1
# export slots=32
(mkdir ../work || true) && \
cd ../work && \
rm -rf ./* && \
mpiexec --oversubscribe -np 32 ../gambit -rf ../yaml_files/THDMI.yaml > out.txt
