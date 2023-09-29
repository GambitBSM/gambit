wget https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz -O- | tar xz
wget http://pyyaml.org/download/pyyaml/PyYAML-3.11.tar.gz -O- | tar xz
source /cvmfs/sft.cern.ch/lcg/views/LCG_103/x86_64-centos7-gcc11-opt/setup.sh 
##export PYTHONPATH="$PWD/PyYAML-3.11/lib:$PYTHONPATH"
git clone git@github.com:GambitBSM/gambit.git --branch SUSYRun2
cd gambit/
mkdir build
cd build/
cmake .. -DWITH_ROOT=ON -DWITH_HEPMC=ON -DBUILD_FS_MODELS=None -Ditch="CosmoBit;DarkBit;NeutrinoBit;Mathematica;PrecisionBit" -DCMAKE_CXX_COMPILER=$(which g++) -DCMAKE_C_COMPILER=$(which gcc) -DWITH_YODA=ON -DPYTHON_LIBRARY=/cvmfs/sft.cern.ch/lcg/views/LCG_103/x86_64-centos7-gcc11-opt/lib/libpython3.9.so -DPYTHON_EXECUTABLE=/cvmfs/sft.cern.ch/lcg/views/LCG_103/x86_64-centos7-gcc11-opt/bin/python3.9 -DPYTHON_INCLUDE_DIR=/cvmfs/sft.cern.ch/lcg/views/LCG_103/x86_64-centos7-gcc11-opt/include/python3.9/ -DEIGEN3_INCLUDE_DIR=$PWD/../../eigen-3.4.0 -DBOOST_INCLUDEDIR=/cvmfs/sft.cern.ch/lcg/views/LCG_103/x86_64-centos7-gcc11-opt/include/boost/ -DBOOST_LIBRARYDIR=/cvmfs/sft.cern.ch/lcg/views/LCG_103/x86_64-centos7-gcc11-opt/lib/

make scanners
cmake ../
make gambit
make pythia
export PYTHIA8DATA=Backends/installed/pythia/8.212/share/Pythia8/xmldoc/
make nulike
