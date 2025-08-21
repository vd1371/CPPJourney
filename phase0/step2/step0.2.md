# Step 0.2: Modern C++ Standards and Compiler Support

## 🎯 Learning Objectives

By the end of this step, you will:
- Understand the evolution of C++ standards from C++11 to C++23
- Configure compiler flags for different C++ standards
- Set up multiple compiler versions for compatibility testing
- Understand ABI compatibility and linking considerations
- Know how to leverage modern C++ features effectively

## 📚 Understanding C++ Standards Evolution

### The Modern C++ Timeline

| Standard | Year | Major Features | Compiler Support |
|----------|------|----------------|------------------|
| **C++11** | 2011 | auto, lambda, smart pointers, move semantics | Full support |
| **C++14** | 2014 | generic lambdas, binary literals, constexpr relaxations | Full support |
| **C++17** | 2017 | structured bindings, std::optional, if constexpr | Full support |
| **C++20** | 2020 | concepts, modules, coroutines, ranges | Growing support |
| **C++23** | 2023 | std::expected, std::flat_map, more constexpr | Limited support |

### Why Multiple Standards Matter

1. **Legacy Code**: Existing projects may target older standards
2. **Compiler Support**: Newer features may not be available everywhere
3. **Performance**: Different standards have different optimization opportunities
4. **Portability**: Wider compatibility with older systems

## 🔧 Setting Up Multiple Compiler Versions

### Install Additional GCC Versions

```bash
# Install multiple GCC versions
sudo apt update
sudo apt install gcc-9 g++-9 gcc-10 g++-10 gcc-11 g++-11 gcc-12 g++-12 gcc-13 g++-13

# Verify installations
for version in 9 10 11 12 13; do
    echo "GCC-$version:"
    gcc-$version --version | head -1
    echo "G++-$version:"
    g++-$version --version | head -1
    echo "---"
done
```

### Install Multiple Clang Versions

```bash
# Add LLVM repository for latest versions
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -

# For Ubuntu 22.04 (adjust based on your version)
echo "deb http://apt.llvm.org/jammy/ llvm-toolchain-jammy-15 main" | sudo tee /etc/apt/sources.list.d/llvm.list
echo "deb http://apt.llvm.org/jammy/ llvm-toolchain-jammy-16 main" | sudo tee -a /etc/apt/sources.list.d/llvm.list
echo "deb http://apt.llvm.org/jammy/ llvm-toolchain-jammy-17 main" | sudo tee -a /etc/apt/sources.list.d/llvm.list

sudo apt update

# Install multiple Clang versions
sudo apt install clang-15 clang++-15 clang-16 clang++-16 clang-17 clang++-17

# Verify installations
for version in 15 16 17; do
    echo "Clang-$version:"
    clang-$version --version | head -1
    echo "Clang++-$version:"
    clang++-$version --version | head -1
    echo "---"
done
```

### Configure Alternative Compilers

```bash
# Set up alternatives for easy switching
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 110
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 120
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 130

sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 110
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 120
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 130

# Configure alternatives
sudo update-alternatives --config gcc
sudo update-alternatives --config g++
```

## 🚩 Compiler Flags for Different Standards

### Standard Selection Flags

```bash
# C++11 (2011)
g++ -std=c++11 source.cpp

# C++14 (2014) 
g++ -std=c++14 source.cpp

# C++17 (2017)
g++ -std=c++17 source.cpp

# C++20 (2020)
g++ -std=c++20 source.cpp

# C++23 (2023) - Latest
g++ -std=c++23 source.cpp

# GNU extensions (default)
g++ -std=gnu++20 source.cpp

# Strict ISO compliance
g++ -std=c++20 -pedantic source.cpp
```

### Feature Detection Flags

```bash
# Enable specific language features
g++ -std=c++20 -fconcepts -fcoroutines -fmodules-ts source.cpp

# Clang-specific module support
clang++ -std=c++20 -stdlib=libc++ -fmodules source.cpp

# Show feature support
g++ -std=c++23 -v -E -x c++ - < /dev/null 2>&1 | grep -E "(collect2|ld)"
```

### Compatibility Flags

```bash
# ABI compatibility
g++ -std=c++17 -fabi-version=11 source.cpp

# Backward compatibility
g++ -std=c++20 -Wno-c++11-narrowing source.cpp

# Forward compatibility warnings
g++ -std=c++17 -Wc++20-compat source.cpp
```

## 🧪 Testing Compiler Support

### Create Feature Detection Program

```cpp
// feature_test.cpp
#include <iostream>
#include <iomanip>

// Macro definitions for feature testing
#define FEATURE_TEST(feature, macro) \
    std::cout << std::setw(30) << std::left << feature << ": " \
              << (macro ? "YES" : "NO") << std::endl

int main() {
    std::cout << "C++ Standard: " << __cplusplus << std::endl;
    std::cout << "Compiler: ";
    
#ifdef __GNUC__
    std::cout << "GCC " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__;
#elif defined(__clang__)
    std::cout << "Clang " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__;
#else
    std::cout << "Unknown";
#endif
    std::cout << std::endl << std::endl;

    std::cout << "Feature Support:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    // C++11 features
    FEATURE_TEST("Auto keyword", __cpp_auto_type >= 200704);
    FEATURE_TEST("Lambda expressions", __cpp_lambdas >= 200907);
    FEATURE_TEST("Range-based for", __cpp_range_based_for >= 200907);
    FEATURE_TEST("Smart pointers", __has_include(<memory>));
    
    // C++14 features
    FEATURE_TEST("Generic lambdas", __cpp_generic_lambdas >= 201304);
    FEATURE_TEST("Variable templates", __cpp_variable_templates >= 201304);
    FEATURE_TEST("Binary literals", __cpp_binary_literals >= 201304);
    
    // C++17 features
    FEATURE_TEST("Structured bindings", __cpp_structured_bindings >= 201606);
    FEATURE_TEST("If constexpr", __cpp_if_constexpr >= 201606);
    FEATURE_TEST("Fold expressions", __cpp_fold_expressions >= 201603);
    FEATURE_TEST("std::optional", __has_include(<optional>));
    
    // C++20 features
    FEATURE_TEST("Concepts", __cpp_concepts >= 201907);
    FEATURE_TEST("Coroutines", __cpp_coroutines >= 201902);
    FEATURE_TEST("Modules", __cpp_modules >= 201907);
    FEATURE_TEST("Ranges", __has_include(<ranges>));
    FEATURE_TEST("std::format", __has_include(<format>));
    
    // C++23 features
    FEATURE_TEST("std::expected", __has_include(<expected>));
    FEATURE_TEST("std::flat_map", __cpp_lib_flat_map >= 202207);
    FEATURE_TEST("std::ranges::to", __cpp_lib_ranges_to_container >= 202202);
    
    return 0;
}
```

### Test Across Multiple Standards

```bash
# Create test script
cat > test_standards.sh << 'EOF'
#!/bin/bash

echo "Testing C++ Standards Support"
echo "=============================="

standards=("c++11" "c++14" "c++17" "c++20" "c++23")
compilers=("g++" "clang++")

for compiler in "${compilers[@]}"; do
    echo
    echo "Testing with $compiler:"
    echo "----------------------"
    
    for std in "${standards[@]}"; do
        echo -n "  $std: "
        if $compiler -std=$std -o feature_test_${compiler}_${std} feature_test.cpp 2>/dev/null; then
            echo "✓ Compiles"
            # Optionally run and show output
            # ./feature_test_${compiler}_${std}
        else
            echo "✗ Failed"
        fi
    done
done

# Cleanup
rm -f feature_test_*
EOF

chmod +x test_standards.sh
./test_standards.sh
```

## 🔗 Understanding ABI Compatibility

### What is ABI?

**Application Binary Interface (ABI)** defines how compiled code interacts:
- Function calling conventions
- Data layout in memory
- Name mangling schemes
- Exception handling mechanisms

### ABI Compatibility Issues

```cpp
// abi_test.cpp
#include <iostream>
#include <string>
#include <vector>

// Demonstration of ABI-sensitive code
class MyClass {
private:
    std::string name;
    std::vector<int> data;
    
public:
    MyClass(const std::string& n) : name(n) {}
    
    // Virtual function affects ABI
    virtual void display() const {
        std::cout << "Name: " << name << std::endl;
    }
    
    // Template functions can affect ABI
    template<typename T>
    void addData(T value) {
        data.push_back(static_cast<int>(value));
    }
};

// C-style interface for ABI stability
extern "C" {
    MyClass* create_myclass(const char* name) {
        return new MyClass(std::string(name));
    }
    
    void destroy_myclass(MyClass* obj) {
        delete obj;
    }
    
    void display_myclass(MyClass* obj) {
        obj->display();
    }
}

int main() {
    MyClass obj("Test");
    obj.display();
    obj.addData(42);
    
    return 0;
}
```

### Testing ABI Compatibility

```bash
# Compile with different ABI versions
g++ -std=c++17 -fabi-version=11 -shared -fPIC -o libtest_abi11.so abi_test.cpp
g++ -std=c++17 -fabi-version=15 -shared -fPIC -o libtest_abi15.so abi_test.cpp

# Check symbols
nm -D libtest_abi11.so | grep create_myclass
nm -D libtest_abi15.so | grep create_myclass

# Check ABI with objdump
objdump -T libtest_abi11.so | head -20
objdump -T libtest_abi15.so | head -20
```

## 🔧 CMake Configuration for Multiple Standards

### Advanced CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.20)
project(ModernCppStandards)

# Set default C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable GNU extensions

# Function to create targets for different standards
function(create_std_target target_name source_file std_version)
    add_executable(${target_name}_cpp${std_version} ${source_file})
    set_target_properties(${target_name}_cpp${std_version} PROPERTIES
        CXX_STANDARD ${std_version}
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )
    target_compile_options(${target_name}_cpp${std_version} PRIVATE
        -Wall -Wextra -Wpedantic
    )
endfunction()

# Create targets for different standards
create_std_target(feature_test feature_test.cpp 11)
create_std_target(feature_test feature_test.cpp 14)
create_std_target(feature_test feature_test.cpp 17)
create_std_target(feature_test feature_test.cpp 20)

# Try C++23 if supported
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 13)
    create_std_target(feature_test feature_test.cpp 23)
endif()

# Compiler-specific flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(feature_test_cpp20 PRIVATE -fconcepts)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(feature_test_cpp20 PRIVATE -stdlib=libc++)
endif()

# Feature detection
include(CheckCXXSourceCompiles)

check_cxx_source_compiles("
    #include <concepts>
    template<typename T>
    concept Integral = std::integral<T>;
    int main() { return 0; }
" HAS_CONCEPTS)

if(HAS_CONCEPTS)
    message(STATUS "Concepts support detected")
    target_compile_definitions(feature_test_cpp20 PRIVATE HAS_CONCEPTS)
endif()

# Testing targets
enable_testing()

add_test(NAME TestCpp11 COMMAND feature_test_cpp11)
add_test(NAME TestCpp14 COMMAND feature_test_cpp14)
add_test(NAME TestCpp17 COMMAND feature_test_cpp17)
add_test(NAME TestCpp20 COMMAND feature_test_cpp20)

# Custom test for standard verification
add_test(NAME VerifyStandards 
    COMMAND ${CMAKE_COMMAND} -E echo "All standards tested successfully")
```

## 🎯 Best Practices for Standard Selection

### Choosing the Right Standard

```cpp
// guidelines.cpp - Demonstration of standard selection criteria

// C++11: Baseline modern C++
void cpp11_features() {
    // Use when you need wide compatibility
    auto x = 42;                    // auto keyword
    std::vector<int> v = {1,2,3};   // initializer lists
    auto lambda = [](int a) { return a * 2; }; // lambdas
}

// C++14: Incremental improvements
void cpp14_features() {
    // Generic lambdas
    auto generic_lambda = [](auto x) { return x * 2; };
    
    // Binary literals
    auto flags = 0b1010'1111;
    
    // std::make_unique
    auto ptr = std::make_unique<int>(42);
}

// C++17: Major productivity boost
void cpp17_features() {
    // Structured bindings
    std::pair<int, std::string> p{42, "hello"};
    auto [num, str] = p;
    
    // std::optional
    std::optional<int> maybe_value = 42;
    if (maybe_value) {
        // Use value
    }
    
    // if constexpr
    if constexpr (sizeof(int) == 4) {
        // Compile-time conditional
    }
}

// C++20: Game-changing features
void cpp20_features() {
    // Concepts (when available)
    #ifdef __cpp_concepts
    template<std::integral T>
    T add(T a, T b) {
        return a + b;
    }
    #endif
    
    // Ranges (when available)
    #ifdef __cpp_lib_ranges
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto even = v | std::views::filter([](int i) { return i % 2 == 0; });
    #endif
}

// C++23: Cutting edge
void cpp23_features() {
    // std::expected (when available)
    #ifdef __cpp_lib_expected
    std::expected<int, std::string> divide(int a, int b) {
        if (b == 0) return std::unexpected("Division by zero");
        return a / b;
    }
    #endif
}
```

### Recommendation Matrix

| Use Case | Recommended Standard | Reason |
|----------|---------------------|---------|
| **Legacy systems** | C++11/14 | Wide compiler support |
| **New projects** | C++17/20 | Good balance of features and support |
| **High-performance** | C++20 | Concepts, ranges, coroutines |
| **Experimental** | C++23 | Latest features |
| **Library development** | C++17 | Good compatibility |

## 🔍 Debugging Standard Issues

### Common Standard-Related Problems

```cpp
// debug_standards.cpp
#include <iostream>

// Problem 1: Feature not available in standard
void narrowing_conversion() {
    // This warns in C++11+, error in C++23
    int x = 3.14;  // narrowing conversion
    std::cout << x << std::endl;
}

// Problem 2: Different behavior across standards
void auto_deduction() {
    // C++11/14: deduces std::initializer_list<int>
    // C++17+: deduces int
    auto x = {1};
    std::cout << typeid(x).name() << std::endl;
}

// Problem 3: Deprecated features
void deprecated_features() {
    // std::auto_ptr deprecated in C++11, removed in C++17
    #if __cplusplus < 201703L
    // std::auto_ptr<int> ptr(new int(42));  // Don't use this!
    #endif
    
    // Use std::unique_ptr instead
    std::unique_ptr<int> ptr(new int(42));
}

int main() {
    std::cout << "C++ Standard: " << __cplusplus << std::endl;
    
    narrowing_conversion();
    auto_deduction();
    deprecated_features();
    
    return 0;
}
```

### Compilation Tests

```bash
# Create comprehensive test
cat > compile_test.sh << 'EOF'
#!/bin/bash

echo "Standard Compatibility Testing"
echo "============================="

# Test file with potential issues
cat > test_code.cpp << 'CODE'
#include <iostream>
#include <memory>
#include <vector>

int main() {
    // Test auto deduction changes
    auto x = {1, 2, 3};
    
    // Test narrowing conversion
    int y = 3.14;
    
    // Test aggregate initialization
    struct Point { int x, y; };
    Point p{1, 2};
    
    std::cout << "Compiled successfully!" << std::endl;
    return 0;
}
CODE

standards=("c++11" "c++14" "c++17" "c++20")

for std in "${standards[@]}"; do
    echo
    echo "Testing $std:"
    echo "============"
    
    # Test with GCC
    echo -n "GCC: "
    if g++ -std=$std -Werror -o test_gcc_$std test_code.cpp 2>/dev/null; then
        echo "✓ Success"
    else
        echo "✗ Failed"
        g++ -std=$std -o test_gcc_$std test_code.cpp 2>&1 | head -3
    fi
    
    # Test with Clang
    echo -n "Clang: "
    if clang++ -std=$std -Werror -o test_clang_$std test_code.cpp 2>/dev/null; then
        echo "✓ Success"
    else
        echo "✗ Failed"
        clang++ -std=$std -o test_clang_$std test_code.cpp 2>&1 | head -3
    fi
done

# Cleanup
rm -f test_code.cpp test_gcc_* test_clang_*
EOF

chmod +x compile_test.sh
./compile_test.sh
```

## 🎯 Next Steps

After mastering this step, you should:

1. ✅ Understand the evolution of C++ standards
2. ✅ Configure multiple compiler versions
3. ✅ Use appropriate compiler flags for each standard
4. ✅ Test feature availability across compilers
5. ✅ Understand ABI compatibility considerations
6. ✅ Choose the right standard for your project

## 📚 Additional Resources

- **C++ Standard Status**: https://en.cppreference.com/w/cpp/compiler_support
- **GCC C++ Status**: https://gcc.gnu.org/projects/cxx-status.html
- **Clang C++ Status**: https://clang.llvm.org/cxx_status.html
- **Microsoft C++ Status**: https://docs.microsoft.com/en-us/cpp/overview/visual-cpp-language-conformance

## 🚀 Ready for Step 0.3?

In the next step, we'll explore **Development Tools and Quality Assurance**, covering:
- Static analysis tools in depth
- Advanced debugging techniques  
- Code formatting and style enforcement
- Setting up continuous integration for C++

---

*Understanding C++ standards is crucial for writing portable, maintainable code that leverages the best features available while maintaining compatibility with your target environments.*
