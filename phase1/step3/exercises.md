# Phase 1.3: Compilation and Tooling Deep Dive - Exercises

## Exercise Requirements

All exercises should be completed using modern CMake (3.15+) and modern C++ (C++20). Focus on applying the compilation and tooling concepts learned in this section to realistic HFT scenarios.

---

## Exercise 1: Modern CMake Build System for Market Data Processor

**Objective**: Create a sophisticated CMake build system for a multi-component market data processing system.

### Requirements

Create a project structure with the following components:
- `market_data_parser` - Static library for parsing market data feeds
- `order_book` - Static library for maintaining order books
- `latency_monitor` - Static library for measuring processing latency
- `trading_engine` - Executable that uses all libraries
- `benchmark_suite` - Executable for performance testing

### Specifications

1. **Project Structure**:
   ```
   hft_system/
   ├── CMakeLists.txt
   ├── libs/
   │   ├── market_data_parser/
   │   │   ├── CMakeLists.txt
   │   │   ├── include/market_data_parser/parser.hpp
   │   │   └── src/parser.cpp
   │   ├── order_book/
   │   │   ├── CMakeLists.txt
   │   │   ├── include/order_book/order_book.hpp
   │   │   └── src/order_book.cpp
   │   └── latency_monitor/
   │       ├── CMakeLists.txt
   │       ├── include/latency_monitor/monitor.hpp
   │       └── src/monitor.cpp
   ├── apps/
   │   ├── trading_engine/
   │   │   ├── CMakeLists.txt
   │   │   └── main.cpp
   │   └── benchmark_suite/
   │       ├── CMakeLists.txt
   │       └── benchmark_main.cpp
   └── cmake/
       └── modules/
           └── FindJemalloc.cmake
   ```

2. **CMake Requirements**:
   - Use modern target-based CMake
   - Implement proper include directory propagation
   - Use generator expressions for conditional compilation
   - Support Debug, Release, and RelWithDebInfo build types
   - Configure different optimization levels for each build type
   - Enable precompiled headers for common includes
   - Integrate ccache if available
   - Support both GCC and Clang compilers

3. **Build Configuration**:
   - **Release mode**: `-O3 -march=native -flto -ffast-math`
   - **Debug mode**: `-O0 -g3 -fsanitize=address -fsanitize=undefined`
   - **RelWithDebInfo**: `-O2 -g -DNDEBUG`

4. **Dependencies to Integrate**:
   - Find and link with system threads library
   - Create a custom FindJemalloc.cmake module
   - Optional: Integrate with Boost (if available)

### Starter Code Templates

**Root CMakeLists.txt**:
```cmake
cmake_minimum_required(VERSION 3.15)
project(HFTSystem VERSION 1.0.0 LANGUAGES CXX)

# TODO: Implement modern CMake configuration
# - Set C++20 standard
# - Configure compiler-specific optimizations
# - Set up ccache if available
# - Configure precompiled headers
# - Add subdirectories
```

**Library CMakeLists.txt Template**:
```cmake
# TODO: Create a modern library target
# - Use target_sources() for source files
# - Set up proper include directories with BUILD_INTERFACE/INSTALL_INTERFACE
# - Configure target properties
# - Link required dependencies
```

**Evaluation Criteria**:
- Proper use of modern CMake features
- Correct dependency management
- Appropriate use of generator expressions
- Build optimization configuration
- Code organization and maintainability

---

## Exercise 2: Dependency Management with Conan

**Objective**: Set up comprehensive dependency management for a trading system using Conan.

### Requirements

Create a Conan-based build system for a trading application that uses:
- Boost (system, thread, chrono libraries)
- Google Benchmark for performance testing
- spdlog for logging
- Protocol Buffers for message serialization
- Optional: jemalloc for memory optimization (Linux only)

### Specifications

1. **Create conanfile.py** with:
   - Proper version constraints for all dependencies
   - Options for enabling/disabling features
   - Platform-specific dependencies
   - Custom settings for HFT optimization

2. **Integration Requirements**:
   - Generate CMake files using Conan
   - Support multiple compiler toolchains
   - Enable cross-platform builds
   - Configure for different optimization profiles

3. **Build Profiles**:
   - `hft-release`: Maximum optimization for production
   - `hft-debug`: Debug symbols with some optimization
   - `hft-profile`: Release with profiling information

### Starter Code

**conanfile.py Template**:
```python
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps

class TradingSystemConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    options = {
        # TODO: Define options for feature toggles
        # - enable_profiling: [True, False]
        # - use_jemalloc: [True, False]
        # - optimization_level: ["debug", "release", "profile"]
    }
    
    def requirements(self):
        # TODO: Add required dependencies with proper version constraints
        pass
    
    def generate(self):
        # TODO: Generate CMake toolchain and dependencies
        pass
```

**Evaluation Criteria**:
- Correct Conan package specification
- Proper dependency version management
- Platform-specific configuration
- Integration with CMake
- Build profile customization

---

## Exercise 3: Advanced Debugging Setup

**Objective**: Configure comprehensive debugging environment for a latency-critical trading application.

### Requirements

Set up debugging configuration for a trading system that can:
- Debug multi-threaded order processing
- Monitor memory usage and detect leaks
- Profile performance bottlenecks
- Set conditional breakpoints based on trading conditions

### Specifications

1. **Create debugging configuration files**:
   - GDB initialization script (`.gdbinit`)
   - VS Code launch configuration (`launch.json`)
   - LLDB configuration script

2. **Debugging Scenarios to Support**:
   - Break when order latency exceeds threshold
   - Monitor specific memory addresses for cache-line analysis
   - Debug template instantiations
   - Track thread-specific execution paths

3. **Performance Debugging**:
   - Configure for CPU profiling with perf
   - Set up memory profiling with Valgrind
   - Enable sanitizers for different build types

### Starter Code

**GDB Configuration Template**:
```gdb
# .gdbinit template
# TODO: Configure GDB for C++ debugging
# - Enable pretty printing
# - Set up custom commands for HFT debugging
# - Configure automatic breakpoints
# - Set up memory watching commands
```

**VS Code launch.json Template**:
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug Trading Engine",
            "type": "cppdbg",
            "request": "launch",
            // TODO: Configure debugging environment
            // - Set program path and arguments
            // - Configure environment variables
            // - Set up pre-launch tasks
            // - Configure sanitizers
        }
    ]
}
```

**Evaluation Criteria**:
- Comprehensive debugging configuration
- Appropriate use of conditional breakpoints
- Memory and performance monitoring setup
- Integration with development environment
- HFT-specific debugging scenarios

---

## Exercise 4: Build Optimization Pipeline

**Objective**: Create an optimized build pipeline that minimizes compilation time while maximizing runtime performance.

### Requirements

Develop a build system that demonstrates:
- Parallel compilation optimization
- Incremental build efficiency
- Profile-guided optimization (PGO)
- Link-time optimization (LTO)
- Build caching strategies

### Specifications

1. **Compilation Time Optimization**:
   - Configure ccache for maximum efficiency
   - Implement precompiled headers strategy
   - Use Ninja generator for parallel builds
   - Optimize dependency inclusion

2. **Runtime Performance Optimization**:
   - Implement PGO workflow
   - Configure LTO for release builds
   - Set up CPU-specific optimizations
   - Enable SIMD instruction usage

3. **Build Analysis**:
   - Measure compilation times
   - Analyze binary size impact
   - Profile build bottlenecks
   - Compare optimization strategies

### Starter Code

**CMake Optimization Template**:
```cmake
# TODO: Implement advanced build optimizations
# - Configure parallel compilation
# - Set up ccache integration
# - Implement precompiled headers
# - Configure PGO workflow
# - Set up LTO for release builds

# Performance measurement target
add_custom_target(measure_build_time
    # TODO: Add commands to measure build performance
)

# Binary size analysis target
add_custom_target(analyze_binary_size
    # TODO: Add commands to analyze binary size
)
```

**Evaluation Criteria**:
- Effective use of build optimization techniques
- Measurable improvement in compilation time
- Appropriate runtime performance optimizations
- Comprehensive build analysis
- Documentation of optimization trade-offs

---

## Exercise 5: Cross-Platform HFT Build System

**Objective**: Create a cross-platform build system that maintains consistent performance across different operating systems and compilers.

### Requirements

Design a build system for an HFT application that:
- Supports Linux, Windows, and macOS
- Works with GCC, Clang, and MSVC
- Maintains consistent optimization levels
- Handles platform-specific dependencies
- Provides uniform debugging experience

### Specifications

1. **Platform Abstraction**:
   - Abstract platform-specific optimizations
   - Handle different linker requirements
   - Manage platform-specific libraries
   - Configure platform-appropriate debugging tools

2. **Compiler Abstraction**:
   - Normalize optimization flags across compilers
   - Handle compiler-specific warnings
   - Manage different standard library implementations
   - Configure appropriate sanitizers per compiler

3. **Dependency Management**:
   - Use vcpkg for cross-platform dependencies
   - Handle platform-specific optional dependencies
   - Manage different library naming conventions

### Starter Code

**Cross-Platform CMakeLists.txt Template**:
```cmake
# TODO: Implement cross-platform build configuration
# - Detect platform and compiler
# - Set platform-specific optimizations
# - Configure appropriate dependencies
# - Set up debugging tools per platform

# Platform detection
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # TODO: Linux-specific configuration
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # TODO: Windows-specific configuration
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # TODO: macOS-specific configuration
endif()

# Compiler detection
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # TODO: GCC-specific flags
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # TODO: Clang-specific flags
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # TODO: MSVC-specific flags
endif()
```

**Evaluation Criteria**:
- Successful builds on multiple platforms
- Consistent performance across platforms
- Proper handling of platform differences
- Maintainable and readable configuration
- Comprehensive testing across environments

---

## Solutions and Common Issues

### Exercise 1 Solutions

**Common Issues**:
- Using directory-based CMake instead of target-based
- Incorrect include directory propagation
- Missing generator expressions for conditional builds
- Improper dependency linking

**Solution Approach**:
```cmake
# Modern target-based library example
add_library(market_data_parser STATIC)
target_sources(market_data_parser PRIVATE src/parser.cpp)
target_include_directories(market_data_parser
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_compile_features(market_data_parser PUBLIC cxx_std_20)

# Proper optimization configuration
target_compile_options(market_data_parser PRIVATE
    $<$<CONFIG:Release>:-O3 -march=native -flto>
    $<$<CONFIG:Debug>:-O0 -g3 -fsanitize=address>
)
```

### Exercise 2 Solutions

**Common Issues**:
- Incorrect dependency version specifications
- Missing platform-specific dependencies
- Improper CMake integration
- Incomplete build profile configuration

**Solution Approach**:
```python
def requirements(self):
    self.requires("boost/1.81.0")
    self.requires("benchmark/1.7.1")
    self.requires("spdlog/1.11.0")
    if self.settings.os == "Linux" and self.options.use_jemalloc:
        self.requires("jemalloc/5.3.0")

def generate(self):
    tc = CMakeToolchain(self)
    if self.options.optimization_level == "release":
        tc.variables["CMAKE_BUILD_TYPE"] = "Release"
        tc.variables["ENABLE_LTO"] = True
    tc.generate()
```

### Exercise 3 Solutions

**Common Issues**:
- Inadequate breakpoint conditions
- Missing sanitizer configuration
- Improper debugging symbol setup
- Insufficient environment variable configuration

**Solution Approach**:
```gdb
# .gdbinit for HFT debugging
set print pretty on
set print array on
define break_on_high_latency
    break process_order if latency_ns > 1000
end
define watch_order_book
    watch order_book.best_bid
    watch order_book.best_ask
end
```

### Exercise 4 Solutions

**Common Issues**:
- Inadequate ccache configuration
- Missing precompiled header optimization
- Improper parallel build setup
- Insufficient performance measurement

**Solution Approach**:
```cmake
# ccache setup
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    # Configure ccache environment
    set(ENV{CCACHE_MAXSIZE} "10G")
    set(ENV{CCACHE_COMPRESS} "true")
endif()

# Precompiled headers
target_precompile_headers(trading_engine PRIVATE
    <vector> <string> <memory> <chrono> <atomic>
    <boost/asio.hpp>
)
```

### Exercise 5 Solutions

**Common Issues**:
- Platform-specific code in wrong locations
- Inconsistent optimization flags across platforms
- Missing platform-specific dependencies
- Inadequate cross-platform testing

**Solution Approach**:
```cmake
# Unified optimization approach
function(set_hft_optimizations target)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE
            $<$<CONFIG:Release>:-O3 -march=native -flto>
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} PRIVATE
            $<$<CONFIG:Release>:/O2 /GL /arch:AVX2>
        )
    endif()
endfunction()
```

These exercises provide hands-on experience with the compilation and tooling concepts essential for professional C++ development in HFT environments. Focus on understanding the underlying principles and trade-offs involved in each optimization technique.
