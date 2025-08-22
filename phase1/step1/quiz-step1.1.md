# Quiz: Core Syntax and Language Basics

## Instructions
Answer the following questions to test your understanding of C++ core syntax and language basics. This quiz covers data types, variables, control structures, functions, pointers, references, I/O operations, and modern C++ features.

**Time Limit**: 20 minutes  
**Questions**: 10  
**Format**: Multiple choice, true/false, and short answer

---

## Questions

### 1. Data Types and Memory
Which of the following integer types guarantees exactly 32 bits across all platforms?
- A) `int`
- B) `long`
- C) `int32_t`
- D) `uint32_t`

### 2. Variable Initialization
What is the output of the following code?
```cpp
int x{5.7};
std::cout << x;
```
- A) 5.7
- B) 5
- C) Compilation error
- D) Undefined behavior

### 3. Control Structures
In the following switch statement, what happens if `order_type` is 'L'?
```cpp
switch (order_type) {
    case 'M':
        std::cout << "Market order\n";
        break;
    case 'L':
        std::cout << "Limit order\n";
    case 'S':
        std::cout << "Stop order\n";
        break;
    default:
        std::cout << "Unknown\n";
}
```
- A) Only "Limit order" is printed
- B) "Limit order" followed by "Stop order" is printed
- C) Compilation error
- D) Runtime error

### 4. Functions and Overloading
Which function call will be ambiguous and cause a compilation error?
```cpp
void process(int x);
void process(int& x);
void process(const int& x);

// Function calls:
process(42);
```
- A) All calls are ambiguous
- B) Only `process(42)` is ambiguous
- C) No calls are ambiguous
- D) Cannot determine without more context

### 5. Pointers and References
What is the value of `y` after executing this code?
```cpp
int x = 10;
int* ptr = &x;
int& ref = *ptr;
ref = 20;
int y = x;
```
- A) 10
- B) 20
- C) Undefined
- D) Compilation error

### 6. Modern C++ Features
Which of the following is NOT a valid use of the `auto` keyword?
```cpp
auto x = 42;
auto y = std::string{"hello"};
auto z = new int{5};
auto w = {1, 2, 3, 4};
```
- A) `auto x = 42;`
- B) `auto y = std::string{"hello"};`
- C) `auto z = new int{5};`
- D) `auto w = {1, 2, 3, 4};`

### 7. I/O Operations
What is the output of this code?
```cpp
std::cout << std::fixed << std::setprecision(2) << 3.14159;
```
- A) 3.14159
- B) 3.14
- C) 3.142
- D) Compilation error (missing includes)

### 8. Memory Safety
Which of the following code snippets has a potential memory leak?
```cpp
// Option A
int* ptr = new int{42};
delete ptr;

// Option B
int* ptr = new int{42};
ptr = nullptr;

// Option C
int* ptr = new int{42};
if (condition) {
    delete ptr;
}
```
- A) Only Option A
- B) Only Option B
- C) Only Option C
- D) Options B and C

### 9. HFT Performance
In high-frequency trading systems, why is it important to order struct members by size (largest first)?
- A) To reduce compilation time
- B) To minimize memory padding and improve cache performance
- C) To make the code more readable
- D) To comply with C++ standards

### 10. Edge Cases
What is the output of this code?
```cpp
int x = 5;
{
    int x = 10;
    std::cout << x << " ";
}
std::cout << x;
```
- A) 10 5
- B) 5 10
- C) 10 10
- D) 5 5

---

## Bonus Question (Advanced)
Explain why the following code might behave differently in debug vs. release builds:
```cpp
volatile bool market_open = false;
while (!market_open) {
    // Wait for market to open
}
std::cout << "Market is open!\n";
```

---

**End of Quiz**

*Remember: In HFT systems, understanding these fundamentals is crucial for writing performant, predictable code. Take time to review any concepts you found challenging.*
