# ScannerBit Python interface


## Build instructions 

Below are some example steps to build the ScannerBit Python interface. Please change the various paths and compiler settings according to your system.

```
# Start from the base gambit directory

mkdir build

cd build

cmake -DCMAKE_BUILD_TYPE=Release -DEIGEN3_INCLUDE_DIR=/path/to/your/eigen-3.4.0 -DWITH_PYTHON_SCANNERBIT=True -DWITH_MPI=True -DWITH_ROOT=False -DCMAKE_CXX_COMPILER=g++-11 -DCMAKE_C_COMPILER=gcc-11 -DCMAKE_Fortran_COMPILER=gfortran-11 -Ditch="DarkBit;ColliderBit;CosmoBit;FlavBit;PrecisionBit;NeutrinoBit;ObjectivesBit;DecayBit;SpecBit" ..

# Build individual scanners that can be auto-downloaded by the cmake system, 
# or just do "make scanners" to build all of them
make diver
make polychord
make multinest

cmake ..

make -jN ScannerBit_python_interface  # N is number of cores for parallel build

cd ..
```

If the build was successfull you should now have a shared library `ScannerBit.so` (or `ScannerBit.dylib`) in `ScannerBit/python/`.


## Example

The file `example.py` shows a first example of how to use the ScannerBit python interface. To run it using MPI parallelisation, do 

```
mpiexec -np N python example.py
```

where `N` is the number of MPI processes. 






