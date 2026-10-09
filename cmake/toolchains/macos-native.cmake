# AppleClang from the active Xcode / Command Line Tools installation.
# AppleClang is the native macOS profile; upstream LLVM has a separate preset.

include("${CMAKE_CURRENT_LIST_DIR}/NativePresetToolchain.cmake")
native_configure_preset_toolchain(macos)
