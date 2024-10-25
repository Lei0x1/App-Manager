# CMake Presets Explanation

## General Settings

- **version**: Specifies the version of the CMake presets file format.
- **cmakeMinimumRequired**: Minimum required version of CMake.

## Configure Presets

### Release Preset

- **name**: `release`
- **description**: Release Configuration for optimized build.
- **hidden**: `false` - The preset is visible for selection.
- **generator**: `"MinGW Makefiles"` - Specifies the generator for building the project.
- **binaryDir**: `${sourceDir}/build/release` - Output directory for build files.
- **cacheVariables**:
  - **CMAKE_CXX_STANDARD**: `"17"` - Sets the C++ standard to C++17.
  - **CMAKE_BUILD_TYPE**: `"Release"` - Specifies the build type as Release.
  - **CMAKE_CXX_FLAGS_RELEASE**: `"-O3 -DNDEBUG"` - Flags for optimization:
    - `-O3`: Enables maximum optimizations.
    - `-DNDEBUG`: Disables assertions and debug info.
  - **CMAKE_EXE_LINKER_FLAGS**: `"-s"` - Strips symbols from the executable to reduce size.
  - **CMAKE_POSITION_INDEPENDENT_CODE**: `"ON"` - Generates position-independent code for shared libraries.
  - **CMAKE_INTERPROCEDURAL_OPTIMIZATION**: `"ON"` - Enables link-time optimization for better performance.

### Debug Preset

- **name**: `debug`
- **description**: Debug Configuration with symbols and no optimizations.
- **hidden**: `false` - The preset is visible for selection.
- **generator**: `"MinGW Makefiles"` - Specifies the generator for building the project.
- **binaryDir**: `${sourceDir}/build/debug` - Output directory for build files.
- **cacheVariables**:
  - **CMAKE_CXX_STANDARD**: `"17"` - Sets the C++ standard to C++17.
  - **CMAKE_BUILD_TYPE**: `"Debug"` - Specifies the build type as Debug.
  - **CMAKE_CXX_FLAGS_DEBUG**: `"-g -O0"` - Flags for debugging:
    - `-g`: Generates debug symbols for debugging tools.
    - `-O0`: Disables optimizations to simplify debugging.
  - **CMAKE_POSITION_INDEPENDENT_CODE**: `"ON"` - Generates position-independent code for shared libraries.
  - **CMAKE_EXPORT_COMPILE_COMMANDS**: `"ON"` - Exports compile commands for IDE integration.

## Build Presets

### Build Release

- **name**: `build_release`
- **hidden**: `false` - The preset is visible for selection.
- **configurePreset**: `"release"` - References the `release` configuration preset.
- **jobs**: `8` - Number of parallel jobs to use for building.
- **targets**: `["MyProject"]` - Specifies the project targets to build.
- **nativeToolOptions**: `["-j8"]` - Indicates to run up to 8 jobs in parallel during the build.

### Build Debug

- **name**: `build_debug`
- **hidden**: `false` - The preset is visible for selection.
- **configurePreset**: `"debug"` - References the `debug` configuration preset.
- **jobs**: `8` - Number of parallel jobs to use for building.
- **targets**: `["MyProject"]` - Specifies the project targets to build.
- **nativeToolOptions**: `["-j8"]` - Indicates to run up to 8 jobs in parallel during the build.

For more information, refer to the [CMakePresets Manual](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html).
