# Step 0.2 Quiz: Modern C++ Standards and Compiler Support

## 📝 Quiz Instructions

- **Time Limit**: 45 minutes
- **Total Points**: 100
- **Passing Score**: 70 points
- **Format**: Multiple choice, true/false, and practical questions
- **Resources Allowed**: Quick reference guide only

---

## 🎯 Section 1: C++ Standards Overview (25 points)

### Question 1 (5 points)
Which C++ standard introduced the `auto` keyword and lambda expressions?
- [ ] A) C++98
- [ ] B) C++11 ✅
- [ ] C) C++14
- [ ] D) C++17

### Question 2 (5 points)
What is the main benefit of using C++17 over C++14 for new projects?
- [ ] A) Better performance
- [ ] B) More compiler support
- [ ] C) Structured bindings and std::optional ✅
- [ ] D) Smaller binary size

### Question 3 (5 points)
Which C++ standard introduced concepts and ranges?
- [ ] A) C++17
- [ ] B) C++20 ✅
- [ ] C) C++23
- [ ] D) C++14

### Question 4 (5 points)
What does the `__cplusplus` macro represent?
- [ ] A) Compiler version
- [ ] B) C++ standard version ✅
- [ ] C) ABI version
- [ ] D) Library version

### Question 5 (5 points)
Which standard introduced `std::expected` for error handling?
- [ ] A) C++20
- [ ] B) C++23 ✅
- [ ] C) C++17
- [ ] D) C++14

---

## 🔧 Section 2: Compiler Configuration (25 points)

### Question 6 (5 points)
What flag should you use to compile with C++20 standard in GCC?
- [ ] A) `-std=c++20` ✅
- [ ] B) `-c++20`
- [ ] C) `-standard=c++20`
- [ ] D) `-cpp20`

### Question 7 (5 points)
Which compiler flag enables strict ISO compliance?
- [ ] A) `-strict`
- [ ] B) `-iso`
- [ ] C) `-pedantic` ✅
- [ ] D) `-compliance`

### Question 8 (5 points)
What is the purpose of the `-fconcepts` flag in GCC?
- [ ] A) Enable experimental concepts support ✅
- [ ] B) Enable constexpr functions
- [ ] C) Enable coroutines
- [ ] D) Enable modules

### Question 9 (5 points)
Which flag should you use to enable address sanitizer?
- [ ] A) `-fsanitize=address` ✅
- [ ] B) `-address-sanitizer`
- [ ] C) `-sanitize-address`
- [ ] D) `-asan`

### Question 10 (5 points)
What does the `-Wabi` flag do?
- [ ] A) Enables ABI warnings ✅
- [ ] B) Disables ABI warnings
- [ ] C) Sets ABI version
- [ ] D) Checks ABI compatibility

---

## 🧪 Section 3: Feature Detection (25 points)

### Question 11 (5 points)
Which macro should you check to detect if concepts are supported?
- [ ] A) `__cpp_concepts` ✅
- [ ] B) `__has_concepts`
- [ ] C) `__concepts_supported`
- [ ] D) `__cpp_lib_concepts`

### Question 12 (5 points)
What does `__has_include(<optional>)` check?
- [ ] A) If std::optional is available ✅
- [ ] B) If optional header exists
- [ ] C) If optional is implemented
- [ ] D) If optional is deprecated

### Question 13 (5 points)
Which feature test macro indicates support for structured bindings?
- [ ] A) `__cpp_structured_bindings` ✅
- [ ] B) `__cpp_bindings`
- [ ] C) `__structured_bindings`
- [ ] D) `__cpp_structured`

### Question 14 (5 points)
What is the value of `__cplusplus` for C++17?
- [ ] A) 201703L ✅
- [ ] B) 2017
- [ ] C) 17
- [ ] D) 201700L

### Question 15 (5 points)
Which macro should you use to detect generic lambda support?
- [ ] A) `__cpp_generic_lambdas` ✅
- [ ] B) `__cpp_lambdas`
- [ ] C) `__generic_lambdas`
- [ ] D) `__cpp_lambda_generic`

---

## 🔗 Section 4: ABI and Linking (25 points)

### Question 16 (5 points)
What does ABI stand for?
- [ ] A) Application Binary Interface ✅
- [ ] B) Application Build Interface
- [ ] C) Application Binary Integration
- [ ] D) Application Build Integration

### Question 17 (5 points)
Which compiler flag specifies the ABI version?
- [ ] A) `-fabi-version=N` ✅
- [ ] B) `-abi-version=N`
- [ ] C) `-version-abi=N`
- [ ] D) `-fabi=N`

### Question 18 (5 points)
What tool can you use to check exported symbols in a shared library?
- [ ] A) `nm -D` ✅
- [ ] B) `objdump -T`
- [ ] C) `readelf -s`
- [ ] D) All of the above

### Question 19 (5 points)
Why is ABI compatibility important?
- [ ] A) For source code compatibility
- [ ] B) For binary compatibility between compiled code ✅
- [ ] C) For header file compatibility
- [ ] D) For compiler compatibility

### Question 20 (5 points)
Which C++ feature can significantly affect ABI?
- [ ] A) constexpr functions
- [ ] B) Virtual functions ✅
- [ ] C) Static functions
- [ ] D) Inline functions

---

## 🎯 Bonus Section: Practical Application (10 points)

### Question 21 (5 points)
You need to write code that works with both C++17 and C++20. Which approach is best?
- [ ] A) Use only C++17 features
- [ ] B) Use C++20 features with feature detection ✅
- [ ] C) Use the latest standard available
- [ ] D) Write separate versions for each standard

### Question 22 (5 points)
Your project needs to support both GCC 9 and GCC 12. Which C++ standard should you target?
- [ ] A) C++11
- [ ] B) C++14
- [ ] C) C++17 ✅
- [ ] D) C++20

---

## 🔍 Practical Exercise (20 points)

### Exercise 1: Feature Detection Program (10 points)
Write a C++ program that detects and reports the following features:
- C++ standard version
- Compiler and version
- Support for: auto, lambdas, concepts, ranges, coroutines

**Requirements:**
- Use feature test macros
- Handle missing features gracefully
- Output should be clear and formatted

### Exercise 2: Multi-Standard Compilation (10 points)
Create a CMakeLists.txt that builds the same source file with multiple C++ standards (11, 14, 17, 20).

**Requirements:**
- Create separate targets for each standard
- Use proper CMake properties
- Include basic testing


## ✅ Answer Key

### Section 1: C++ Standards Overview
1. B) C++11
2. C) Structured bindings and std::optional
3. B) C++20
4. B) C++ standard version
5. B) C++23

### Section 2: Compiler Configuration
6. A) `-std=c++20`
7. C) `-pedantic`
8. A) Enable experimental concepts support
9. A) `-fsanitize=address`
10. A) Enables ABI warnings

### Section 3: Feature Detection
11. A) `__cpp_concepts`
12. A) If std::optional is available
13. A) `__cpp_structured_bindings`
14. A) 201703L
15. A) `__cpp_generic_lambdas`

### Section 4: ABI and Linking
16. A) Application Binary Interface
17. A) `-fabi-version=N`
18. D) All of the above
19. B) For binary compatibility between compiled code
20. B) Virtual functions

### Bonus Section
21. B) Use C++20 features with feature detection
22. C) C++17

---

## 🎯 Learning Objectives Check

After completing this quiz, you should be able to:

- [ ] **Understand C++ standards evolution** from C++11 to C++23
- [ ] **Configure compiler flags** for different C++ standards
- [ ] **Set up multiple compiler versions** for compatibility testing
- [ ] **Understand ABI compatibility** and linking considerations
- [ ] **Use feature detection macros** effectively
- [ ] **Choose appropriate standards** for different use cases
- [ ] **Troubleshoot standard-related** compilation issues

