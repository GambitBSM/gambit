# Minimum compiler versions for GAMBIT.  Included from CMakeLists.txt and
# from CBS script-mode discovery (cmake -P), so keep this file free of
# project() state.

include_guard(GLOBAL)

set(MIN_GCC_VERSION 9.1)
set(MIN_ICC_VERSION 15.0.2)
set(MIN_CLANG_VERSION 10.0.0)
set(MIN_APPLECLANG_VERSION 13.0.0)
