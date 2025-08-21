# Step 0.2: Quick Reference - Modern C++ Standards

## 🚀 Standard Selection Commands

### Basic Compilation
```bash
# C++11 (2011) - Baseline modern C++
g++ -std=c++11 -Wall -Wextra -o program source.cpp

# C++14 (2014) - Generic lambdas, binary literals
g++ -std=c++14 -Wall -Wextra -o program source.cpp

# C++17 (2017) - Structured bindings, std::optional
g++ -std=c++17 -Wall -Wextra -o program source.cpp

# C++20 (2020) - Concepts, ranges, coroutines
g++ -std=c++20 -Wall -Wextra -o program source.cpp

# C++23 (2023) - Latest features
g++ -std=c++23 -Wall -Wextra -o program source.cpp
```

### Compiler-Specific Features
```bash
# GCC with concepts support
g++ -std=c++20 -fconcepts -o program source.cpp

# Clang with modules
clang++ -std=c++20 -stdlib=libc++ -fmodules -o program source.cpp

# Strict ISO compliance
g++ -std=c++20 -pedantic -o program source.cpp
```

## 📊 C++ Standards Comparison

| Feature | C++11 | C++14 | C++17 | C++20 | C++23 |
|---------|--------|--------|--------|--------|--------|
| **auto** | ✅ | ✅ | ✅ | ✅ | ✅ |
| **lambdas** | ✅ | ✅ | ✅ | ✅ | ✅ |
| **range-for** | ✅ | ✅ | ✅ | ✅ | ✅ |
| **generic lambdas** | ❌ | ✅ | ✅ | ✅ | ✅ |
| **binary literals** | ❌ | ✅ | ✅ | ✅ | ✅ |
| **structured bindings** | ❌ | ❌ | ✅ | ✅ | ✅ |
| **if constexpr** | ❌ | ❌ | ✅ | ✅ | ✅ |
| **std::optional** | ❌ | ❌ | ✅ | ✅ | ✅ |
| **concepts** | ❌ | ❌ | ❌ | ✅ | ✅ |
| **ranges** | ❌ | ❌ | ❌ | ✅ | ✅ |
| **coroutines** | ❌ | ❌ | ❌ | ✅ | ✅ |
| **std::expected** | ❌ | ❌ | ❌ | ❌ | ✅ |

## 🎯 Standard Selection Guide

### Choose C++11 When:
- Working with legacy systems
- Need maximum compiler compatibility
- Using older embedded systems

### Choose C++14 When:
- Need generic lambdas
- Want incremental improvements over C++11
- Working with slightly older codebases

### Choose C++17 When:
- Starting new projects
- Need structured bindings and std::optional
- Want good balance of features and compatibility

### Choose C++20 When:
- Can use modern compilers
- Want concepts and ranges
- Building high-performance applications

### Choose C++23 When:
- Experimenting with cutting-edge features
- Using latest compilers
- Contributing to standard development

## 🔧 Compiler Version Requirements

### GCC Support
```bash
# Check GCC version
g++ --version

# Minimum versions for full support:
# C++11: GCC 4.8+
# C++14: GCC 5+
# C++17: GCC 7+
# C++20: GCC 10+ (partial), GCC 11+ (good)
# C++23: GCC 13+ (partial)
```

### Clang Support
```bash
# Check Clang version
clang++ --version

# Minimum versions for full support:
# C++11: Clang 3.3+
# C++14: Clang 3.4+
# C++17: Clang 5+
# C++20: Clang 12+ (partial), Clang 15+ (good)
# C++23: Clang 17+ (partial)
```

## 🏗️ CMake Standard Configuration

### Basic Standard Setting
```cmake
# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

### Per-Target Standards
```cmake
# Different standards for different targets
add_executable(legacy_app legacy.cpp)
set_target_properties(legacy_app PROPERTIES CXX_STANDARD 11)

add_executable(modern_app modern.cpp)
set_target_properties(modern_app PROPERTIES CXX_STANDARD 20)
```

### Feature Detection
```cmake
# Check for specific features
include(CheckCXXSourceCompiles)

check_cxx_source_compiles("
    #include <concepts>
    int main() { return 0; }
" HAS_CONCEPTS)

if(HAS_CONCEPTS)
    target_compile_definitions(myapp PRIVATE HAS_CONCEPTS)
endif()
```

## 🧪 Feature Testing Macros

### Standard Feature Test Macros
```cpp
#include <iostream>

void check_features() {
    std::cout << "C++ Standard: " << __cplusplus << std::endl;
    
    // Check specific features
    #ifdef __cpp_auto_type
    std::cout << "Auto: " << __cpp_auto_type << std::endl;
    #endif
    
    #ifdef __cpp_lambdas
    std::cout << "Lambdas: " << __cpp_lambdas << std::endl;
    #endif
    
    #ifdef __cpp_concepts
    std::cout << "Concepts: " << __cpp_concepts << std::endl;
    #endif
}
```

### Header Availability
```cpp
// Check for header availability
#if __has_include(<optional>)
    #include <optional>
    #define HAS_OPTIONAL 1
#endif

#if __has_include(<concepts>)
    #include <concepts>
    #define HAS_CONCEPTS 1
#endif

#if __has_include(<ranges>)
    #include <ranges>
    #define HAS_RANGES 1
#endif
```

## ⚡ Common Compiler Flags

### Warning Flags
```bash
# Essential warnings
-Wall -Wextra -Wpedantic

# Additional useful warnings
-Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
-Wunused -Woverloaded-virtual -Wpedantic -Wconversion
-Wsign-conversion -Wmisleading-indentation -Wduplicated-cond
-Wduplicated-branches -Wlogical-op -Wnull-dereference
-Wuseless-cast -Wdouble-promotion -Wformat=2
```

### Optimization Flags
```bash
# Debug build
-g -O0 -DDEBUG

# Release build
-O2 -DNDEBUG

# Maximum optimization
-O3 -march=native -DNDEBUG

# Size optimization
-Os -DNDEBUG
```

### Sanitizer Flags
```bash
# Address sanitizer
-fsanitize=address -g

# Undefined behavior sanitizer
-fsanitize=undefined -g

# Thread sanitizer
-fsanitize=thread -g

# Memory sanitizer (Clang only)
-fsanitize=memory -g
```

## 🔍 ABI Considerations

### ABI Version Control
```bash
# Specify ABI version
g++ -fabi-version=11 source.cpp

# Check ABI compatibility
g++ -Wabi source.cpp

# Disable ABI warnings
g++ -Wno-abi source.cpp
```

### Symbol Analysis
```bash
# Check exported symbols
nm -D libname.so

# Demangle C++ symbols
nm -D libname.so | c++filt

# Check ABI with objdump
objdump -T libname.so
```

## 📝 Quick Test Commands

### Feature Detection Test
```bash
# Create and run feature test
cat > feature_test.cpp << 'EOF'
#include <iostream>
int main() {
    std::cout << "C++ Standard: " << __cplusplus << std::endl;
    return 0;
}
EOF

# Test with different standards
for std in c++11 c++14 c++17 c++20 c++23; do
    echo -n "$std: "
    if g++ -std=$std -o test feature_test.cpp 2>/dev/null; then
        ./test
    else
        echo "Not supported"
    fi
done

rm -f feature_test.cpp test
```

### Compiler Support Test
```bash
# Test compiler support for specific features
echo '#include <concepts>' | g++ -std=c++20 -x c++ - -fsyntax-only 2>/dev/null && echo "Concepts: YES" || echo "Concepts: NO"
echo '#include <ranges>' | g++ -std=c++20 -x c++ - -fsyntax-only 2>/dev/null && echo "Ranges: YES" || echo "Ranges: NO"
echo '#include <coroutine>' | g++ -std=c++20 -x c++ - -fsyntax-only 2>/dev/null && echo "Coroutines: YES" || echo "Coroutines: NO"
```

## 🎯 Troubleshooting Common Issues

### Standard Not Recognized
```bash
# Update compiler
sudo apt update && sudo apt upgrade gcc g++

# Check available standards
g++ -std=c++ # Press Tab for completion
```

### Missing Features
```bash
# Check feature support
g++ -std=c++20 -dM -E - < /dev/null | grep __cpp_

# Enable experimental features
g++ -std=c++2b -fconcepts-ts -fmodules-ts source.cpp
```

### Linking Issues
```bash
# Link standard library
g++ -std=c++20 -lstdc++ source.cpp

# Link specific runtime
clang++ -std=c++20 -stdlib=libc++ source.cpp
```

## 📚 Useful Resources

- **Standard Status**: https://en.cppreference.com/w/cpp/compiler_support
- **GCC Status**: https://gcc.gnu.org/projects/cxx-status.html  
- **Clang Status**: https://clang.llvm.org/cxx_status.html
- **Compiler Explorer**: https://godbolt.org/
- **C++ Insights**: https://cppinsights.io/

## ✅ Verification Checklist

Before proceeding:
- [ ] Can compile with C++11, C++14, C++17, C++20
- [ ] Understand feature availability in each standard
- [ ] Know how to detect features at compile time
- [ ] Can configure CMake for different standards
- [ ] Understand ABI compatibility basics
- [ ] Can troubleshoot standard-related compilation issues

---

*Keep this reference handy when working with different C++ standards!*
