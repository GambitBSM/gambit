echo "creating a release build of gambit..." && \
cd .. && \
(mkdir build || true ) && \
cd build && \
(make nuke-all && make clean || true ) && \
rm -rf ./* && \
cmake -D CMAKE_CXX_COMPILER=g++ -D CMAKE_C_COMPILER=gcc -D CMAKE_Fortran_COMPILER=gfortran -D CMAKE_BUILD_TYPE=Release_O3 -D WITH_MPI=ON -D BUILD_FS_MODELS="THDM_I;THDM_II;THDM_LS;THDM_flipped" -D WITH_ROOT=ON -D WITH_RESTFRAMES=ON -D WITH_HEPMC=ON .. && \
make scanners && make higgsbounds && make higgssignals && make superiso && make THDMC && make heplike && cmake .. && make -j64 gambit
# cmake -D CMAKE_CXX_COMPILER=g++ -D CMAKE_C_COMPILER=gcc -D CMAKE_Fortran_COMPILER=gfortran -D CMAKE_BUILD_TYPE=None -D CMAKE_C_FLAGS=-O3 -D CMAKE_CXX_FLAGS=-O3 -D CMAKE_Fortran_FLAGS=-O3 -D WITH_MPI=ON -D BUILD_FS_MODELS="THDM_I;THDM_II;THDM_LS;THDM_flipped" -D WITH_ROOT=ON -D WITH_RESTFRAMES=ON -D WITH_HEPMC=ON .. && \
# make scanners && make higgsbounds && make higgssignals && make superiso && make THDMC && make heplike && cmake .. && make -j64 gambit
