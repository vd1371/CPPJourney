# Quiz: Step 1 - Development Environment Setup

**Time Limit**: 30 minutes  
**Passing Score**: 80% (24/30 points)

---

## 📋 Section 1: Compiler Knowledge (8 points)

### Question 1.1 (2 points)
Which of the following is NOT a valid reason to install both GCC and Clang compilers?
- [ ] A) Different compilers catch different types of errors
- [ ] B) They have varying levels of C++ standard support
- [ ] C) One compiler is always faster than the other
- [ ] D) It's good practice to test code with multiple compilers

### Question 1.2 (2 points)
What does the `build-essential` package include?
- [ ] A) Only GCC compiler
- [ ] B) GCC, G++, Make, and basic build tools
- [ ] C) All development tools including CMake
- [ ] D) Only debugging tools

### Question 1.3 (2 points)
Which command would you use to check if Clang is properly installed?
- [ ] A) `clang --version`
- [ ] B) `clang++ --version`
- [ ] C) Both A and B
- [ ] D) `which clang`

### Question 1.4 (2 points)
What is the primary advantage of having multiple GCC versions installed?
- [ ] A) Faster compilation
- [ ] B) Testing code compatibility across different C++ standards
- [ ] C) Better error messages
- [ ] D) Smaller executable files

---

## 🔧 Section 2: Build Systems and CMake (8 points)

### Question 2.1 (2 points)
What is the main purpose of CMake?
- [ ] A) To compile C++ code directly
- [ ] B) To generate build files for your system
- [ ] C) To manage package dependencies only
- [ ] D) To format code automatically

### Question 2.2 (2 points)
Which CMake command sets the C++ standard to C++20?
- [ ] A) `set(CMAKE_CXX_STANDARD 20)`
- [ ] B) `set(CMAKE_CXX_STANDARD "c++20")`
- [ ] C) `CMAKE_CXX_STANDARD = 20`
- [ ] D) `set_cxx_standard(20)`

### Question 2.3 (2 points)
What does `CMAKE_CXX_STANDARD_REQUIRED ON` do?
- [ ] A) Enables C++ extensions
- [ ] B) Makes the specified standard mandatory
- [ ] C) Sets the minimum required CMake version
- [ ] D) Enables all compiler warnings

### Question 2.4 (2 points)
Which directory structure is recommended for a CMake project?
- [ ] A) All files in the root directory
- [ ] B) `src/` for source files, `include/` for headers, `build/` for build files
- [ ] C) `build/` for source files, `bin/` for headers
- [ ] D) `code/` for everything

---

## 📦 Section 3: Package Management (6 points)

### Question 3.1 (2 points)
Which package manager is considered the most C++-native?
- [ ] A) vcpkg
- [ ] B) Conan
- [ ] C) apt
- [ ] D) pip

### Question 3.2 (2 points)
What is the main advantage of using Conan over system package managers?
- [ ] A) It's faster to install packages
- [ ] B) Better dependency resolution and version management
- [ ] C) It only works on Linux
- [ ] D) It's free

### Question 3.3 (2 points)
Which command installs Conan using pip?
- [ ] A) `sudo apt install conan`
- [ ] B) `pip3 install conan`
- [ ] C) `npm install conan`
- [ ] D) `brew install conan`

---

## 🐛 Section 4: Development and Debugging Tools (8 points)

### Question 4.1 (2 points)
What is the primary purpose of GDB?
- [ ] A) Code formatting
- [ ] B) Debugging programs
- [ ] C) Static analysis
- [ ] D) Package management

### Question 4.2 (2 points)
Which tool is used for memory error detection and profiling?
- [ ] A) clang-tidy
- [ ] B) Valgrind
- [ ] C) cppcheck
- [ ] D) clang-format

### Question 4.3 (2 points)
What does clang-tidy do?
- [ ] A) Formats code automatically
- [ ] B) Performs static analysis and suggests improvements
- [ ] C) Compiles code faster
- [ ] D) Manages dependencies

### Question 4.4 (2 points)
Which tool would you use to ensure consistent code formatting across a team?
- [ ] A) GDB
- [ ] B) clang-format
- [ ] C) Valgrind
- [ ] D) CMake

---

## 🎯 Section 5: Practical Application (10 points)

### Question 5.1 (3 points)
You want to compile a C++ program with C++20 standard and enable all warnings. Which command is correct?
- [ ] A) `g++ -std=c++20 -Wall -Wextra source.cpp`
- [ ] B) `g++ -std=c++20 -w source.cpp`
- [ ] C) `g++ -std=c++20 source.cpp`
- [ ] D) `g++ -c++20 -Wall source.cpp`

### Question 5.2 (3 points)
You're debugging a program and want to run it with memory checking. Which command should you use?
- [ ] A) `gdb ./program`
- [ ] B) `valgrind --leak-check=full ./program`
- [ ] C) `clang-tidy program.cpp`
- [ ] D) `cppcheck program.cpp`

### Question 5.3 (4 points)
You want to create a CMake project that:
- Uses C++20 standard
- Has compiler warnings enabled
- Creates an executable called "myapp"
- Has source files in a "src" directory

Which CMakeLists.txt is correct?

**Option A:**
```cmake
cmake_minimum_required(VERSION 3.20)
project(MyProject)
set(CMAKE_CXX_STANDARD 20)
add_executable(myapp src/main.cpp)
target_compile_options(myapp PRIVATE -Wall -Wextra)
```

**Option B:**
```cmake
cmake_minimum_required(VERSION 3.20)
project(MyProject)
set(CMAKE_CXX_STANDARD 20)
add_executable(myapp src/*.cpp)
```

**Option C:**
```cmake
project(MyProject)
set(CMAKE_CXX_STANDARD 20)
add_executable(myapp src/main.cpp)
```

**Option D:**
```cmake
cmake_minimum_required(VERSION 3.20)
project(MyProject)
set(CMAKE_CXX_STANDARD 20)
add_executable(myapp src/main.cpp)
target_compile_options(myapp PRIVATE -Wall)
```

---

## 📝 Section 6: Troubleshooting (5 points)

### Question 6.1 (2 points)
Your program compiles with GCC but not with Clang. What should you do first?
- [ ] A) Switch to using only GCC
- [ ] B) Check if both compilers support the C++ standard you're using
- [ ] C) Reinstall Clang
- [ ] D) Use different compiler flags

### Question 6.2 (3 points)
You're getting "command not found" for g++. What's the most likely issue?
- [ ] A) GCC is not installed
- [ ] B) The build-essential package is missing
- [ ] C) PATH environment variable is not set correctly
- [ ] D) All of the above

---

## 🔍 Bonus Questions (Extra Credit: 5 points)

### Bonus 1 (2 points)
What does the `-fPIC` flag do when compiling shared libraries?
- [ ] A) Enables position-independent code
- [ ] B) Optimizes for performance
- [ ] C) Enables debugging symbols
- [ ] D) Sets the C++ standard

### Bonus 2 (3 points)
You want to profile your C++ program for performance. Which tool would be most appropriate?
- [ ] A) Valgrind
- [ ] B) perf
- [ ] C) clang-tidy
- [ ] D) cppcheck

---

