# Phase 1.3: Compilation and Tooling - Quick Reference

## Advanced CMake Cheat Sheet

### Modern Target-Based CMake

```cmake
# Create library target
add_library(target_name STATIC|SHARED|INTERFACE sources...)

# Set target properties
set_target_properties(target PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE ON
)

# Target-specific compile options
target_compile_options(target PRIVATE|PUBLIC|INTERFACE options...)

# Target-specific definitions
target_compile_definitions(target PRIVATE|PUBLIC|INTERFACE definitions...)

# Target include directories
target_include_directories(target
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link libraries to targets
target_link_libraries(target PRIVATE|PUBLIC|INTERFACE libraries...)
```

### Generator Expressions (Essential)

```cmake
# Configuration-based conditions
$<$<CONFIG:Release>:options_for_release>
$<$<CONFIG:Debug>:options_for_debug>

# Compiler-based conditions
$<$<CXX_COMPILER_ID:GNU>:gcc_specific_options>
$<$<CXX_COMPILER_ID:Clang>:clang_specific_options>
$<$<CXX_COMPILER_ID:MSVC>:msvc_specific_options>

# Platform-based conditions
$<$<PLATFORM_ID:Linux>:linux_libraries>
$<$<PLATFORM_ID:Windows>:windows_libraries>

# Boolean conditions
$<$<BOOL:${ENABLE_FEATURE}>:feature_options>
```

### HFT-Optimized CMake Template

```cmake
# Performance-critical build setup
add_library(hft_core STATIC ${SOURCES})

target_compile_options(hft_core PRIVATE
    $<$<CONFIG:Release>:-O3 -march=native -flto>
    $<$<CONFIG:Debug>:-O0 -g3 -fsanitize=address>
)

target_compile_definitions(hft_core PRIVATE
    $<$<CONFIG:Release>:NDEBUG ENABLE_SIMD>
    $<$<CONFIG:Debug>:DEBUG_LOGGING>
)

# Precompiled headers for large projects
target_precompile_headers(hft_core PRIVATE
    <vector> <string> <memory> <chrono> <atomic>
    <boost/asio.hpp>
)
```

## Dependency Management

### Conan Essentials

```python
# conanfile.py template
from conan import ConanFile

class ProjectConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "boost/1.81.0", "protobuf/3.21.9"
    
    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()
```

```bash
# Conan workflow
conan profile detect --force
conan install . --build=missing -s build_type=Release
cmake --preset conan-release
cmake --build --preset conan-release
```

### vcpkg Essentials

```json
// vcpkg.json
{
  "dependencies": ["boost-system", "protobuf", "benchmark"],
  "builtin-baseline": "2023.08.09"
}
```

```cmake
# CMake integration
find_package(Boost REQUIRED COMPONENTS system)
find_package(protobuf CONFIG REQUIRED)
target_link_libraries(target PRIVATE Boost::system protobuf::libprotobuf)
```

## Debugging Commands

### GDB Quick Commands

```bash
# Essential GDB commands
gdb ./program
(gdb) run args...                    # Start program
(gdb) break file.cpp:line           # Set breakpoint
(gdb) break func if condition       # Conditional breakpoint
(gdb) watch variable                # Watch variable changes
(gdb) bt                           # Backtrace
(gdb) print variable               # Print variable
(gdb) info locals                  # Show local variables
(gdb) continue                     # Continue execution
(gdb) step                         # Step into function
(gdb) next                         # Step over function
(gdb) finish                       # Step out of function

# C++ specific
(gdb) set print pretty on          # Pretty print structures
(gdb) info functions Pattern       # Find functions matching pattern
(gdb) ptype ClassName              # Show class definition
```

### LLDB Quick Commands

```bash
# Essential LLDB commands
lldb ./program
(lldb) process launch -- args...   # Start program
(lldb) breakpoint set -f file.cpp -l line  # Set breakpoint
(lldb) breakpoint set -n function --condition 'var > 10'  # Conditional
(lldb) watchpoint set variable -w write    # Watch variable
(lldb) thread backtrace            # Backtrace
(lldb) frame variable variable     # Print variable
(lldb) frame variable -A           # Show all variables
(lldb) continue                    # Continue execution
(lldb) thread step-in              # Step into function
(lldb) thread step-over            # Step over function
(lldb) thread step-out             # Step out of function

# C++ specific
(lldb) type lookup ClassName       # Show class definition
(lldb) expr --raw -- printf("...")  # Execute C code
```

## Build Optimization

### Compiler Optimization Flags

```cmake
# Release optimization (HFT-focused)
set(RELEASE_FLAGS
    -O3              # Maximum optimization
    -march=native    # Use all CPU instructions
    -mtune=native    # Tune for current CPU
    -flto            # Link-time optimization
    -ffast-math      # Aggressive math optimizations
    -funroll-loops   # Loop unrolling
)

# Debug flags
set(DEBUG_FLAGS
    -O0                     # No optimization
    -g3                     # Maximum debug info
    -fsanitize=address      # Address sanitizer
    -fsanitize=undefined    # UB sanitizer
    -fno-omit-frame-pointer # Keep frame pointer
)
```

### Parallel Build Configuration

```cmake
# Parallel compilation setup
include(ProcessorCount)
ProcessorCount(N)
set(CMAKE_BUILD_PARALLEL_LEVEL ${N})

# Use Ninja for fastest builds
set(CMAKE_GENERATOR "Ninja")

# ccache for faster rebuilds
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()
```

```bash
# Build commands
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

## HFT-Specific Tips

### Performance Build Settings

```cmake
# Ultra-low latency optimizations
target_compile_options(trading_engine PRIVATE
    -O3 -march=native -mtune=native -flto
    -ffast-math -funroll-loops
    -fomit-frame-pointer
    -msse4.2 -mavx2  # SIMD instructions
)

# Memory optimization
target_compile_definitions(trading_engine PRIVATE
    ENABLE_JEMALLOC
    DISABLE_EXCEPTION_HANDLING
    FAST_PATH_ONLY
)
```

### Debug-Optimized Builds

```cmake
# Debug with some optimization for performance testing
target_compile_options(trading_engine PRIVATE
    $<$<CONFIG:RelWithDebInfo>:-O2 -g -DNDEBUG>
)
```

### Static Analysis Integration

```cmake
# clang-tidy integration
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=-*,modernize-*,performance-*")

# Include What You Use
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use")
```

## Common Issues and Solutions

| Issue | Solution |
|-------|----------|
| Slow compilation | Use ccache, precompiled headers, Ninja generator |
| Large binary size | Use `-Os`, remove debug symbols, strip binaries |
| Runtime performance | Enable LTO, use `-O3 -march=native` |
| Memory issues | Use sanitizers (`-fsanitize=address,undefined`) |
| Template errors | Use concepts (C++20) or SFINAE |
| Link errors | Check library order, use `target_link_libraries` |
| Missing symbols | Verify all dependencies are linked |
| ABI issues | Ensure consistent compiler and std lib versions |

## Build System Best Practices

1. **Always use target-based CMake** - avoid global variables
2. **Use generator expressions** for conditional builds
3. **Enable parallel builds** with appropriate job counts
4. **Use ccache** for faster incremental builds
5. **Implement precompiled headers** for large projects
6. **Configure sanitizers** for debug builds
7. **Use modern package managers** (Conan/vcpkg)
8. **Enable static analysis** in CI/CD pipelines
9. **Separate build types** (Debug, Release, RelWithDebInfo)
10. **Profile and optimize** critical paths regularly
