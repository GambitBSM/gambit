# \author Pengxuan Zhu <pengxuan.zhu@adelaide.edu.au>
# \date 2026 Sep
#
# Upstream LLVM on macOS or Linux, shared by GAMBIT and standalone presets.
# All profiles use build/; switching compilers requires --fresh.

include("${CMAKE_CURRENT_LIST_DIR}/NativePresetToolchain.cmake")
native_configure_preset_toolchain(llvm)
