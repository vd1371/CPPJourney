# Phase 1.3: Compilation and Tooling Deep Dive - Quiz

## Instructions
Answer all questions. For multiple choice questions, select the best answer. For code analysis questions, explain your reasoning.

---

### Question 1 (Multiple Choice)
Which CMake approach is considered modern and recommended for large projects?

A) Directory-based builds with global variables  
B) Target-based builds with target properties  
C) File-based builds with explicit paths  
D) Variable-based builds with cache entries  

---

### Question 2 (True/False)
True or False: Generator expressions in CMake are evaluated at generate time (when CMake creates build files), not at configure time.

---

### Question 3 (Multiple Choice)
In high-frequency trading applications, which compiler optimization flags combination would provide the best performance for production builds?

A) `-O1 -g`  
B) `-O2 -march=generic`  
C) `-O3 -march=native -flto -ffast-math`  
D) `-Os -fomit-frame-pointer`  

---

### Question 4 (Code Analysis)
Analyze the following CMake code and identify what's wrong with this approach:

```cmake
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++20")
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(trading_app main.cpp)
target_link_libraries(trading_app boost_system)
```

What issues do you see and how would you fix them using modern CMake practices?

---

### Question 5 (Multiple Choice)
When using Conan package manager, which file is typically used to specify project dependencies and build requirements?

A) `CMakeLists.txt`  
B) `conanfile.py` or `conanfile.txt`  
C) `requirements.txt`  
D) `package.json`  

---

### Question 6 (Short Answer)
Explain the difference between `PRIVATE`, `PUBLIC`, and `INTERFACE` keywords in CMake's `target_link_libraries()` command. When would you use each one?

---

### Question 7 (Multiple Choice)
In GDB, which command would you use to set a breakpoint that only triggers when a specific condition is met (e.g., when a variable `latency` exceeds 10 microseconds)?

A) `break function_name if latency > 10`  
B) `conditional break function_name latency > 10`  
C) `break function_name when latency > 10`  
D) `breakpoint set function_name --condition latency > 10`  

---

### Question 8 (Code Analysis)
Given this CMake generator expression, explain what it does and when it would be useful:

```cmake
target_compile_options(hft_engine PRIVATE
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:-march=native -mtune=native>
)
```

---

### Question 9 (Multiple Choice)
Which tool would be most effective for speeding up incremental C++ builds in a large codebase?

A) Using more CPU cores  
B) Implementing ccache  
C) Switching to Clang compiler  
D) Using static libraries instead of shared libraries  

---

### Question 10 (Short Answer)
In the context of high-frequency trading systems, why might you want to use different optimization levels for different parts of your codebase? Provide a specific example scenario.

---

### Question 11 (True/False)
True or False: Precompiled headers in CMake using `target_precompile_headers()` can significantly reduce compilation time for large projects with many common includes.

---

### Question 12 (Multiple Choice)
When debugging a C++ application with complex template instantiations using LLDB, which command would help you inspect the actual type of a template parameter?

A) `type info template_param`  
B) `type lookup template_param`  
C) `print typeof(template_param)`  
D) `show template template_param`  

---

### Bonus Question (Advanced)
Explain how you would set up a CMake build system for a high-frequency trading application that needs to:
- Use different optimization levels for latency-critical vs. non-critical code
- Support both GCC and Clang compilers
- Integrate with both Conan and vcpkg package managers
- Include debugging symbols in development but strip them in production
- Enable static analysis tools in the build pipeline

Provide a brief architectural overview of your CMake configuration approach.
