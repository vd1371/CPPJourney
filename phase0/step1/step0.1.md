# Step 0.1: Development Environment Setup

## 🎯 Learning Objectives

By the end of this step, you will:
- Have a fully configured C++ development environment
- Understand the modern C++ toolchain ecosystem
- Be able to compile and run C++ programs
- Have debugging and development tools ready

## 🛠️ Prerequisites Check

Since you're on Linux, you're already in a great position! Let's verify what you have:

```bash
# Check your Linux distribution
cat /etc/os-release

# Check if you have basic build tools
which gcc
which make
which git
```

## 📦 Step 1: Install Modern C++ Compilers

### 1.1 Install GCC (GNU Compiler Collection)

GCC is the most widely used C++ compiler. Let's install the latest version:

```bash
# Update package lists
sudo apt update

# Install GCC and G++ (C++ compiler)
sudo apt install build-essential

# Install additional GCC versions for testing
sudo apt install gcc-12 g++-12 gcc-13 g++-13

# Verify installation
gcc --version
g++ --version
```

**Note**: The `build-essential` package includes the basic build tools you'll need. Having multiple GCC versions allows you to test code compatibility across different C++ standards.

### 1.2 Install Clang/LLVM (Alternative Compiler)

Clang is another excellent compiler with great error messages and modern C++ support:

```bash
# Install Clang and LLVM
sudo apt install clang lldb lld

# Verify installation
clang++ --version
```

**Why Both Compilers?**: Different compilers catch different types of errors and have varying levels of C++ standard support. It's good practice to test your code with multiple compilers.

## 🔧 Step 2: Install CMake (Modern Build System)

CMake is the industry standard for C++ project management:

```bash
# Install CMake
sudo apt install cmake

# Verify installation
cmake --version
```

**Note**: CMake generates build files for your system (Makefiles on Linux, Visual Studio projects on Windows). It's much more powerful than writing Makefiles manually.

## 📚 Step 3: Install Package Managers

### 3.1 Install Conan (Recommended for C++)

Conan is a modern C++ package manager:

```bash
# Install Python and pip if not already installed
sudo apt install python3 python3-pip

# Install Conan
pip3 install conan

# Verify installation
conan --version
```

### 3.2 Install vcpkg (Alternative)

vcpkg is Microsoft's package manager, but works great on Linux:

```bash
# Clone vcpkg repository
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg

# Run bootstrap script
./bootstrap-vcpkg.sh

# Add to PATH (add this to your ~/.bashrc)
export PATH="$PATH:$HOME/vcpkg"

# Verify installation
vcpkg --version
```

## 🎨 Step 4: Configure VS Code

### 4.1 Install VS Code Extensions

Install these essential C++ extensions:

1. **C/C++** (Microsoft) - Core C++ language support
2. **CMake Tools** - CMake integration
3. **C++ TestMate** - Testing framework support
4. **clangd** - Advanced language server
5. **Code Runner** - Quick code execution

### 4.2 Configure C++ Settings

Create `.vscode/settings.json` in your project:

```json
{
    "C_Cpp.default.cppStandard": "c++20",
    "C_Cpp.default.cStandard": "c17",
    "C_Cpp.default.compilerPath": "/usr/bin/g++",
    "C_Cpp.default.intelliSenseMode": "linux-gcc-x64",
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools"
}
```

## 🐛 Step 5: Install Development and Debugging Tools

### 5.1 Install Essential Development Tools

```bash
# Install debugging tools
sudo apt install gdb valgrind

# Install static analysis tools
sudo apt install clang-tidy cppcheck

# Install code formatting tools
sudo apt install clang-format

# Verify installations
gdb --version
valgrind --version
clang-tidy --version
cppcheck --version
clang-format --version
```

### 5.2 Install Additional Useful Tools

```bash
# Install performance profiling tools
sudo apt install perf-tools-unstable

# Install memory checking tools
sudo apt install address-sanitizer
sudo apt-get install libasan8 # For debian based distros

# Install code coverage tools
sudo apt install lcov
```

## ✅ Step 6: Verify Your Setup

Let's create a simple test to ensure everything works:

### 6.1 Create a Test Project

```bash
# Create a test directory
mkdir cpp-test
cd cpp-test

# Create a simple C++ file
cat > main.cpp << 'EOF'
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};
    
    std::cout << "Original numbers: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    std::sort(numbers.begin(), numbers.end());
    
    std::cout << "Sorted numbers: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
EOF
```

### 6.2 Test Compilation with Different Compilers

```bash
# Test with GCC
g++ -std=c++20 -Wall -Wextra -o test_gcc main.cpp
./test_gcc

# Test with Clang
clang++ -std=c++20 -Wall -Wextra -o test_clang main.cpp
./test_clang

# Test with different C++ standards
g++ -std=c++17 -Wall -Wextra -o test_cpp17 main.cpp
g++ -std=c++14 -Wall -Wextra -o test_cpp14 main.cpp
```

### 6.3 Test CMake

```bash
# Create CMakeLists.txt
cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.20)
project(CppTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_cmake main.cpp)
EOF

# Build with CMake
mkdir build
cd build
cmake ..
make
./test_cmake
```

## 🧪 Step 7: Advanced Testing

### 7.1 Test Static Analysis

```bash
# Run clang-tidy
clang-tidy main.cpp -- -std=c++20

# Run cppcheck
cppcheck --enable=all main.cpp
```

### 7.2 Test Debugging

```bash
# Compile with debug symbols
g++ -std=c++20 -g -Wall -Wextra -o test_debug main.cpp

# Run with gdb
gdb ./test_debug
# In gdb, type: run
# Then: quit
```

### 7.3 Test Memory Checking

```bash
# Run with Valgrind
valgrind --leak-check=full ./test_debug
```

## 📋 Step 8: Create Your First CMake Project

Let's create a proper project structure:

```bash
# Go back to your workspace
cd /home/your/path/to/CPPJourney

# Create a proper project structure
mkdir -p Phase0/Step1/hello-world
cd Phase0/Step1/hello-world

# Create project files
cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.20)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(hello_world src/main.cpp)

# Set compiler flags
target_compile_options(hello_world PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -O2
)

# Enable testing
enable_testing()
add_test(NAME HelloWorldTest COMMAND hello_world)
EOF

# Create source directory
mkdir src
cat > src/main.cpp << 'EOF'
#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "Hello! What's your name? ";
    std::getline(std::cin, name);
    
    if (name.empty()) {
        name = "World";
    }
    
    std::cout << "Hello, " << name << "! Welcome to C++!" << std::endl;
    std::cout << "You're using C++ standard: " << __cplusplus << std::endl;
    
    return 0;
}
EOF

# Build and run
mkdir build
cd build
cmake ..
make
./hello_world
```

## 🎓 Step 9: Understanding What You've Set Up

### Compiler Chain
- **GCC**: Most widely used, excellent C++ standard support
- **Clang**: Great error messages, fast compilation, LLVM backend
- **Multiple versions**: Test compatibility across C++ standards

### Build System
- **CMake**: Generates build files, manages dependencies, cross-platform
- **Modern features**: Target-based approach, package finding, testing

### Package Management
- **Conan**: C++-native package manager, excellent dependency resolution
- **vcpkg**: Microsoft's package manager, great for system libraries

### Development Tools
- **GDB/LLDB**: Debuggers for finding and fixing bugs
- **Valgrind**: Memory error detection and profiling
- **clang-tidy/cppcheck**: Static analysis for code quality
- **clang-format**: Consistent code formatting

## 🚀 Step 10: Next Steps Preparation

Before moving to the next step, ensure you can:

1. ✅ Compile C++ code with GCC and Clang
2. ✅ Use different C++ standards (C++14, C++17, C++20)
3. ✅ Build projects with CMake
4. ✅ Debug programs with GDB
5. ✅ Run static analysis tools
6. ✅ Format code with clang-format

## 🎯 Practice Exercises

### Exercise 1: Compiler Exploration
Try compiling the same code with different compilers and standards. Notice any differences in error messages or warnings.

### Exercise 2: CMake Mastery
Modify the CMakeLists.txt to:
- Add compiler warnings
- Set different optimization levels
- Add multiple source files
- Create a library target

### Exercise 3: Tool Integration
Set up VS Code to:
- Format code on save
- Run clang-tidy automatically
- Debug with breakpoints
- Use IntelliSense effectively


## 📚 Additional Resources

- **GCC Documentation**: https://gcc.gnu.org/onlinedocs/
- **Clang Documentation**: https://clang.llvm.org/docs/
- **CMake Documentation**: https://cmake.org/documentation/
- **Conan Documentation**: https://docs.conan.io/
- **VS Code C++ Guide**: https://code.visualstudio.com/docs/languages/cpp

## 🎉 Congratulations!

You've successfully set up a professional C++ development environment! This foundation will serve you well throughout your C++ journey. 

**Ready for the next step?** In Step 0.2, we'll explore modern C++ standards and learn how to configure compilers for different C++ versions.

---

*Remember: A well-configured development environment is like having a good workshop - it makes learning and building much more enjoyable and efficient!*