# Step 0.1: Practical Exercises

Welcome to your first hands-on C++ session! These exercises will help you master your development environment setup.

**Note**: Some exercises use C++23 features. Make sure you have a recent compiler:
- **GCC 13+** or **Clang 17+** for full C++23 support
- **GCC 10+** or **Clang 10+** for C++20 support
- **GCC 7+** or **Clang 5+** for C++17 support

## 🚀 Quick Start Exercise

Let's begin with a simple "Hello World" to verify everything works:

```bash
# Create a test directory
mkdir ~/cpp-practice
cd ~/cpp-practice

# Create your first C++ file
cat > hello.cpp << 'EOF'
#include <iostream>

int main() {
    std::cout << "Hello, C++ World!" << std::endl;
    std::cout << "I'm learning C++!" << std::endl;
    return 0;
}
EOF

# Compile and run
g++ -std=c++20 -Wall -Wextra -o hello hello.cpp
./hello
```

**Expected Output:**
```
Hello, C++ World!
I'm learning C++!
```

## 🎯 Exercise 1: Compiler Comparison

Create a file with intentional errors to see how different compilers report them:

```bash
# Create a file with errors
cat > buggy.cpp << 'EOF'
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Intentional error: wrong type
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << std::endl;
    }
    
    // Intentional error: unused variable
    int unused = 42;
    
    // Intentional error: missing semicolon
    std::cout << "This line is missing a semicolon"
    
    return 0;
}
EOF
```

Now test with different compilers and standards:

```bash
# Test with GCC C++23 (latest standard, most features)
g++ -std=c++23 -Wall -Wextra -o buggy_gcc23 buggy.cpp

# Test with GCC C++20 (should catch most errors)
g++ -std=c++20 -Wall -Wextra -o buggy_gcc buggy.cpp

# Test with Clang C++23
clang++ -std=c++23 -Wall -Wextra -o buggy_clang23 buggy.cpp

# Test with Clang C++20
clang++ -std=c++20 -Wall -Wextra -o buggy_clang buggy.cpp

# Test with GCC C++17 (fewer warnings)
g++ -std=c++17 -Wall -Wextra -o buggy_cpp17 buggy.cpp
```

**Learning Point**: Notice how different compilers and standards provide different levels of error checking and warnings.

## 🔧 Exercise 2: CMake Project Structure

Create a proper project structure with multiple source files:

```bash
# Create project directory
mkdir cmake-project
cd cmake-project

# Create source files
mkdir src
mkdir include
mkdir build

# Create header file
cat > include/calculator.h << 'EOF'
#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    int add(int a, int b);
    int subtract(int a, int b);
    int multiply(int a, int b);
    double divide(int a, int b);
};

#endif
EOF

# Create implementation file
cat > src/calculator.cpp << 'EOF'
#include "calculator.h"
#include <stdexcept>

int Calculator::add(int a, int b) {
    return a + b;
}

int Calculator::subtract(int a, int b) {
    return a - b;
}

int Calculator::multiply(int a, int b) {
    return a * b;
}

double Calculator::divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return static_cast<double>(a) / b;
}
EOF

# Create main file
cat > src/main.cpp << 'EOF'
#include "calculator.h"
#include <iostream>

int main() {
    Calculator calc;
    
    std::cout << "Calculator Demo" << std::endl;
    std::cout << "10 + 5 = " << calc.add(10, 5) << std::endl;
    std::cout << "10 - 5 = " << calc.subtract(10, 5) << std::endl;
    std::cout << "10 * 5 = " << calc.multiply(10, 5) << std::endl;
    
    try {
        std::cout << "10 / 5 = " << calc.divide(10, 5) << std::endl;
        std::cout << "10 / 0 = " << calc.divide(10, 0) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
EOF

# Create CMakeLists.txt
cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.20)
project(Calculator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Include directories
include_directories(include)

# Create executable
add_executable(calculator 
    src/main.cpp
    src/calculator.cpp
)

# Set target properties
target_compile_options(calculator PRIVATE -O2)
EOF

# Build the project
cd build
cmake ..
make

# Run the program
./calculator
```

**Expected Output:**
```
Calculator Demo
10 + 5 = 15
10 - 5 = 5
10 * 5 = 50
10 / 5 = 2
Error: Division by zero
```

## 🐛 Exercise 3: Debugging Practice

Create a program with a bug and practice debugging:

```bash
# Go back to cpp-practice directory
cd ~/cpp-practice

# Create a buggy program
cat > debug_me.cpp << 'EOF'
#include <iostream>
#include <vector>

int calculateSum(const std::vector<int>& numbers) {
    int sum = 0;
    for (size_t i = 0; i <= numbers.size(); i++) {  // Bug: should be < not <=
        sum += numbers[i];
    }
    return sum;
}

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};
    
    std::cout << "Calculating sum of: ";
    for (int n : data) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    int result = calculateSum(data);
    std::cout << "Sum: " << result << std::endl;
    
    return 0;
}
EOF

# Compile with debug symbols (C++23)
g++ -std=c++23 -g -Wall -Wextra -o debug_me debug_me.cpp

# Also try with C++20 for comparison
g++ -std=c++20 -g -Wall -Wextra -o debug_me_cpp20 debug_me.cpp

# Run with Valgrind to detect memory issues
valgrind --leak-check=full ./debug_me

# Debug with GDB
gdb ./debug_me
```

**In GDB, try these commands:**
```
(gdb) break main
(gdb) run
(gdb) next
(gdb) break calculateSum
(gdb) continue
(gdb) print i
(gdb) print numbers.size()
(gdb) continue
```

**Learning Point**: The bug causes an out-of-bounds access. GDB and Valgrind help you find and understand such issues.

## 🎨 Exercise 4: Code Formatting

Practice using clang-format to maintain consistent code style:

```bash
# Create a poorly formatted file
cat > ugly.cpp << 'EOF'
#include<iostream>
#include<vector>
#include<algorithm>
int main(){
std::vector<int>numbers={3,1,4,1,5,9,2,6};
std::sort(numbers.begin(),numbers.end());
for(int n:numbers){std::cout<<n<<" ";}
std::cout<<std::endl;
return 0;}
EOF

# Format it with clang-format
clang-format -i ugly.cpp

# View the formatted result
cat ugly.cpp

# Create a .clang-format configuration file
cat > .clang-format << 'EOF'
BasedOnStyle: Google
IndentWidth: 4
ColumnLimit: 100
AccessModifierOffset: -4
AlignAfterOpenBracket: Align
AlignConsecutiveAssignments: false
AlignConsecutiveDeclarations: false
AlignEscapedNewlines: Left
AlignOperands: true
AlignTrailingComments: true
AllowAllParametersOfDeclarationOnNextLine: true
AllowShortBlocksOnASingleLine: false
AllowShortCaseLabelsOnASingleLine: false
AllowShortFunctionsOnASingleLine: Empty
AllowShortIfStatementsOnASingleLine: false
AllowShortLoopsOnASingleLine: false
AlwaysBreakAfterReturnType: None
AlwaysBreakBeforeMultilineStrings: true
AlwaysBreakTemplateDeclarations: Yes
BinPackArguments: true
BinPackParameters: true
BraceWrapping:
  AfterClass: false
  AfterControlStatement: false
  AfterEnum: false
  AfterFunction: false
  AfterNamespace: false
  AfterStruct: false
  AfterUnion: false
  BeforeCatch: false
  BeforeElse: false
  IndentBraces: false
BreakBeforeBinaryOperators: None
BreakBeforeBraces: Attach
BreakBeforeTernaryOperators: true
BreakStringLiterals: true
CompactNamespaces: false
ConstructorInitializerAllOnOneLineOrOnePerLine: true
ConstructorInitializerIndentWidth: 4
ContinuationIndentWidth: 4
Cpp11BracedListStyle: true
DerivePointerAlignment: false
DisableFormat: false
ExperimentalAutoDetectBinPacking: false
FixNamespaceComments: true
IncludeBlocks: Preserve
IndentCaseLabels: true
IndentPPDirectives: None
IndentWrappedFunctionNames: false
KeepEmptyLinesAtTheStartOfBlocks: false
MaxEmptyLinesToKeep: 1
NamespaceIndentation: None
PenaltyBreakAssignment: 2
PenaltyBreakBeforeFirstCallParameter: 1
PenaltyBreakComment: 300
PenaltyBreakFirstLessLess: 120
PenaltyBreakString: 1000
PenaltyExcessCharacter: 1000000
PenaltyReturnTypeOnItsOwnLine: 200
PointerAlignment: Left
ReflowComments: true
SortIncludes: true
SortUsingDeclarations: true
SpaceAfterCStyleCast: false
SpaceAfterTemplateKeyword: true
SpaceBeforeAssignmentOperators: true
SpaceInEmptyParentheses: false
SpacesBeforeTrailingComments: 1
SpacesInAngles: false
SpacesInContainerLiterals: false
SpacesInCStyleCastParentheses: false
SpacesInParentheses: false
SpacesInSquareBrackets: false
Standard: Cpp11
TabWidth: 4
UseTab: Never
EOF

# Format the file using your custom style
clang-format -i ugly.cpp
cat ugly.cpp
```

## 🧪 Exercise 5: Static Analysis

Practice using static analysis tools to find potential issues:

```bash
# Create a file with potential issues
cat > analyze_me.cpp << 'EOF'
#include <iostream>
#include <string>
#include <vector>

void processData(std::vector<int>& data) {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] > 100) {
            std::cout << "Large number found: " << data[i] << std::endl;
        }
    }
}

int main() {
    std::vector<int> numbers = {50, 150, 25, 200, 75};
    
    processData(numbers);
    
    std::string message = "Hello";
    std::cout << message << std::endl;
    
    return 0;
}
EOF

# Run clang-tidy
clang-tidy analyze_me.cpp -- -std=c++20

# Run cppcheck
cppcheck --enable=all analyze_me.cpp

# Compile with maximum warnings
g++ -std=c++20 -Wall -Wextra -Wpedantic -Weffc++ -o analyze_me analyze_me.cpp
```

## 🏆 Challenge Exercise: Build a Simple Library

Create a small library project to practice all the tools:

```bash
# Create library project
mkdir simple-lib
cd simple-lib

# Create directory structure
mkdir -p src include tests build

# Create header file
cat > include/math_utils.h << 'EOF'
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <vector>
#include <cmath>

namespace math {
    double mean(const std::vector<double>& values);
    double standardDeviation(const std::vector<double>& values);
    std::vector<double> normalize(const std::vector<double>& values);
    
    template<typename T>
    T clamp(T value, T min, T max) {
        return std::max(min, std::min(max, value));
    }
}

#endif
EOF

# Create implementation
cat > src/math_utils.cpp << 'EOF'
#include "math_utils.h"
#include <numeric>
#include <algorithm>

namespace math {
    double mean(const std::vector<double>& values) {
        if (values.empty()) return 0.0;
        return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
    }
    
    double standardDeviation(const std::vector<double>& values) {
        if (values.size() < 2) return 0.0;
        
        double avg = mean(values);
        double sum = 0.0;
        for (double value : values) {
            sum += (value - avg) * (value - avg);
        }
        return std::sqrt(sum / (values.size() - 1));
    }
    
    std::vector<double> normalize(const std::vector<double>& values) {
        if (values.empty()) return {};
        
        double avg = mean(values);
        double std_dev = standardDeviation(values);
        
        if (std_dev == 0.0) return values;
        
        std::vector<double> normalized;
        normalized.reserve(values.size());
        
        for (double value : values) {
            normalized.push_back((value - avg) / std_dev);
        }
        
        return normalized;
    }
}
EOF

# Create main program
cat > src/main.cpp << 'EOF'
#include "math_utils.h"
#include <iostream>
#include <iomanip>

int main() {
    std::vector<double> data = {1.2, 2.3, 3.4, 4.5, 5.6};
    
    std::cout << "Data: ";
    for (double d : data) {
        std::cout << std::fixed << std::setprecision(2) << d << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Mean: " << std::fixed << std::setprecision(2) 
              << math::mean(data) << std::endl;
    std::cout << "Std Dev: " << std::fixed << std::setprecision(2) 
              << math::standardDeviation(data) << std::endl;
    
    auto normalized = math::normalize(data);
    std::cout << "Normalized: ";
    for (double d : normalized) {
        std::cout << std::fixed << std::setprecision(2) << d << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Clamped 3.0 to [0, 4]: " << math::clamp(3.0, 0.0, 4.0) << std::endl;
    
    return 0;
}
EOF

# Create CMakeLists.txt
cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.20)
project(MathUtils)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Include directories
include_directories(include)

# Create library
add_library(math_utils src/math_utils.cpp)

# Create executable
add_executable(math_demo src/main.cpp)

# Link library to executable
target_link_libraries(math_demo math_utils)

# Set target properties
target_compile_options(math_utils PRIVATE -O2)
target_compile_options(math_demo PRIVATE -O2)

# Enable testing
enable_testing()
add_test(NAME MathUtilsTest COMMAND math_demo)
EOF

# Build the project
cd build
cmake ..
make

# Run the program
./math_demo

# Run tests
ctest --verbose
```

## 📝 Exercise Summary

After completing these exercises, you should be able to:

✅ **Compile C++ code** with multiple compilers and standards (C++17, C++20, C++23)  
✅ **Build projects** using CMake  
✅ **Debug programs** with GDB and Valgrind  
✅ **Format code** with clang-format  
✅ **Analyze code** with static analysis tools  
✅ **Create library projects** with proper structure  

## 🚀 Next Steps

Once you're comfortable with these exercises:

1. **Customize your VS Code settings** for C++ development
2. **Set up automated formatting** on save
3. **Move to Step 0.2**: Modern C++ Standards and Compiler Support
---

*Remember: The best way to learn C++ is by doing. Don't just read - write code, compile it, run it, and debug it!*
