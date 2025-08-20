# Step 0.1: Quick Reference Guide

## 🚀 Essential Commands

### Compiler Commands
```bash
# Compile with GCC
g++ -std=c++20 -Wall -Wextra -o program source.cpp

# Compile with Clang
clang++ -std=c++20 -Wall -Wextra -o program source.cpp

# Compile with debug symbols
g++ -std=c++20 -g -Wall -Wextra -o program source.cpp

# Compile with optimization
g++ -std=c++20 -O2 -Wall -Wextra -o program source.cpp
```

### CMake Commands
```bash
# Create build directory
mkdir build && cd build

# Configure project
cmake ..

# Build project
make

# Clean build
make clean

# Install (if configured)
make install
```

### Debugging Commands
```bash
# Run with GDB
gdb ./program

# Run with Valgrind
valgrind --leak-check=full ./program

# Run with AddressSanitizer
g++ -fsanitize=address -g -o program source.cpp
```

### Code Quality Tools
```bash
# Format code
clang-format -i source.cpp

# Static analysis with clang-tidy
clang-tidy source.cpp -- -std=c++20

# Static analysis with cppcheck
cppcheck --enable=all source.cpp
```

## 📋 Common Compiler Flags

| Flag | Description |
|------|-------------|
| `-std=c++20` | Use C++20 standard |
| `-Wall` | Enable all common warnings |
| `-Wextra` | Enable extra warnings |
| `-Wpedantic` | Strict ISO C++ compliance |
| `-g` | Include debug symbols |
| `-O2` | Level 2 optimization |
| `-fsanitize=address` | Enable AddressSanitizer |
| `-fsanitize=undefined` | Enable UndefinedBehaviorSanitizer |

## 🔧 VS Code Configuration

### Essential Extensions
1. **C/C++** (Microsoft)
2. **CMake Tools**
3. **C++ TestMate**
4. **clangd**
5. **Code Runner**

### Settings (.vscode/settings.json)
```json
{
    "C_Cpp.default.cppStandard": "c++20",
    "C_Cpp.default.cStandard": "c17",
    "C_Cpp.default.compilerPath": "/usr/bin/g++",
    "C_Cpp.default.intelliSenseMode": "linux-gcc-x64",
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
    "editor.formatOnSave": true,
    "C_Cpp.formatting": "clangFormat"
}
```

## 🏗️ Project Structure Template

```
project-name/
├── CMakeLists.txt
├── include/
│   └── header.h
├── src/
│   ├── main.cpp
│   └── implementation.cpp
├── tests/
├── build/
└── .vscode/
    └── settings.json
```

## 📝 CMakeLists.txt Template

```cmake
cmake_minimum_required(VERSION 3.20)
project(ProjectName)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Include directories
include_directories(include)

# Create executable
add_executable(program_name 
    src/main.cpp
    src/other.cpp
)

# Set target properties
target_compile_options(program_name PRIVATE -O2)
```

## 🐛 Common Issues & Solutions

### Compiler Not Found
```bash
# Check if compiler is installed
which g++
which clang++

# Reinstall if needed
sudo apt install --reinstall build-essential
```

### CMake Version Too Old
```bash
# Check version
cmake --version

# Install from source if needed
sudo apt install cmake
```

### Permission Denied
```bash
# Fix ownership
sudo chown -R $USER:$USER /path/to/project

# Fix permissions
chmod +x /path/to/script
```

### Library Not Found
```bash
# Install development packages
sudo apt install libname-dev

# Use pkg-config
pkg-config --cflags --libs library_name
```

## 📚 Useful Resources

- **GCC Manual**: `info gcc` or https://gcc.gnu.org/onlinedocs/
- **CMake Documentation**: https://cmake.org/documentation/
- **C++ Reference**: https://en.cppreference.com/
- **Compiler Explorer**: https://godbolt.org/

## 🎯 Verification Checklist

Before moving to the next step, ensure:

- [ ] GCC and Clang are installed and working
- [ ] CMake 3.20+ is installed
- [ ] VS Code extensions are configured
- [ ] You can compile and run a simple C++ program
- [ ] You can build a project with CMake
- [ ] Debugging tools (GDB, Valgrind) are working
- [ ] Code formatting tools are configured
- [ ] Static analysis tools are working

## 🚀 Next Step Preview

In **Step 0.2**, you'll learn about:
- Modern C++ standards (C++11, C++14, C++17, C++20, C++23)
- Compiler flags for different standards
- ABI compatibility considerations
- Setting up multiple compiler versions

---

*Keep this reference handy during your setup process!*
