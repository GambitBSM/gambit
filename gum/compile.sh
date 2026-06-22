rm -rf build
pip install future
cmake -S . -B build -Ditch_Mathematica=ON
cd build
make -j32 marty_test