#!/bin/sh

cmake -S . -B build -DWITH_ROOT=OFF -Ditch="DarkBit;ColliderBit;CosmoBit;FlavBit;PrecisionBit;NeutrinoBit;ObjectivesBit;DecayBit;SpecBit" 

cd build
make -j$(nproc) scanners
cmake ..
make -j$(nproc) gambit
cd ..