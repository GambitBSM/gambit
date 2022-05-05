GAMBIT: building on Mac OSX with AppleClang
===========================================

This file supplements the main README.md with a full walkthrough of the steps required to get GAMBIT up and running on a clean Mac Mini with an M1 (arm64) processor.  The steps should however be applicable to other Macs as well.

We assume in this walkthrough that you want to use the AppleClang compiler that ships with OSX.  If you want to use gcc instead, you can certainly do that, it's just more work.  You need to install it, install whatever dependencies are relevant for you, and then follow the instructions in README.md. Be careful to specify that you want to use gcc everywhere; you may run into linking problems if you build some dependencies accidentally with clang.  In general it is easier to just build using the built-in AppleClang.

Install clang
```
Xcode-select --install
```

Upgrade to latest version of pip (numpy will fail to install if you don't)
```
python3 -m pip install --upgrade pip
```

NB: You must use the system python3 (and pip3 in the steps below)! In case of doubt (if you have installed other python versions) check with 'which python3' and 'which pip3' what python3/pip3 points to, and use 
```
/full/path/to/the/system/python3
/full/path/to/the/system/pip3
```
instead.

Install homebrew
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> /Users/$USER/.zprofile
eval "$(/opt/homebrew/bin/brew shellenv)"
```

Install dependencies
```
brew install cmake
brew install gfortran
brew install libx11
brew install boost
brew install eigen
brew install libomp
brew install gsl
brew install ossp-uuid
brew install hdf5@1.10
pip3 install numpy
pip3 install pyyaml
```

If you want scanners to be parallelised
```
brew install openmpi
```

If you want to use the classy or DarkAges backends
```
pip3 install cython
pip3 install scipy
```

If you want to use the DarkAges backend
```
pip3 install dill
pip3 install future
```

Fix paths
```
echo 'export PATH="/opt/homebrew/opt/hdf5@1.10/bin:$PATH"' >> ~/.zprofile
. ~/.zprofile
```

Configure GAMBIT.  Key optional extras:
  `-D WITH_MPI=ON` if you want scanners to be parallelised
  `-D WITH_HEPMC=ON` if you want HepMC enabled
```
cmake -D PYTHON_EXECUTABLE=/usr/bin/python3 -D PYTHON_LIBRARY=/Library/Developer/CommandLineTools/Library/Frameworks/Python3.framework/Versions/Current/Python3 -D PYTHON_INCLUDE_DIR=/Library/Developer/CommandLineTools/Library/Frameworks/Python3.framework/Headers ..
```

Now, see the instructions in the main README.md for possible make targets, and CMAKE_FLAGS.md for other cmake options.


If you want to use Restframes, GReAT or the HepLike backend, prepare for some pain: you also need ROOT.
First install XCode from the app store (yes, all 12.6GB of it).

You can then do
```
brew install root
echo 'pushd /opt/homebrew >/dev/null; . bin/thisroot.sh; popd >/dev/null' >> ~/.zprofile
. ~/.zprofile
```

Then, rerun cmake in your GAMBIT build dir with the optional extra(s):
  `-D WITH_ROOT=ON ` if you want just ROOT enabled (and therefore GReAT and HepLike but no RestFrames)
  `-D WITH_ROOT=ON -DWITH_RESTFRAMES=ON` if you want RestFrames too.
If you want to use GReAT, now do
```
make great
cmake ..
```
Now, rebuild GAMBIT itself (`make -j8` or similar, depending on how many cores you have).  You should also be able to build HepLike under the `make backends` target, or directly with
```
make heplike
```

GAMBIT and GReAT should work fine like this. Restframes may or may not manage to link in the end, depending on your version of OSX, your hardware and exactly when you are trying to do this.  The situation is exactly the same if you instead build ROOT from source.  At the time of writing, the ROOT authors have not updated ROOT to work with recent versions of Xcode (>13.0), and you will get linking errors arising from hardcoded links in the ROOT binaries to various OSX libraries that changed location between XCode 13.0 and 13.1:
```
ld: file not found: /System/Library/PrivateFrameworks/CoreSymbolication.framework/Versions/A/CoreSymbolication for architecture arm64
```
Of course you are a Mac user and likely expect that "everything just works"; have a word to the ROOT authors about that, and the wisdom of hardcoding library paths rather than determining (or even at least confirming!) them at cmake time.


