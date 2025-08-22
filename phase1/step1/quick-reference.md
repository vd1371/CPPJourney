# Quick Reference: Core Syntax and Language Basics

## Data Types & Memory

### Integer Types
```cpp
int8_t, int16_t, int32_t, int64_t          // Signed integers
uint8_t, uint16_t, uint32_t, uint64_t      // Unsigned integers
int, long, long long                        // Platform-dependent sizes
```

### Floating Point
```cpp
float (32-bit), double (64-bit), long double (80/128-bit)
```

### Type Modifiers
```cpp
const double PI = 3.14159;                  // Immutable
volatile double price;                      // May change externally
static int counter = 0;                     // Persistent across calls
```

## Variable Declaration

### Initialization
```cpp
int old_way = 42;                           // Traditional
int modern_way{42};                         // Uniform initialization (C++11)
auto deduced = 42;                          // Type deduction (C++11)
decltype(var) new_var = value;              // Type inference
```

### Scope
```cpp
{ int local = 42; }                         // Block scope
static int persistent = 0;                  // Function scope
extern const double GLOBAL;                 // Global scope
```

## Control Structures

### Conditionals
```cpp
if (condition) { /* code */ }
else if (condition) { /* code */ }
else { /* code */ }

switch (value) {
    case 1: /* code */ break;
    default: /* code */ break;
}
```

### Loops
```cpp
for (int i = 0; i < n; ++i) { /* code */ }
for (const auto& item : container) { /* code */ }  // Range-based (C++11)
while (condition) { /* code */ }
do { /* code */ } while (condition);
```

## Functions

### Declaration & Definition
```cpp
// Declaration (prototype)
double calculate(double a, double b);

// Definition
double calculate(double a, double b) {
    return a + b;
}

// Inline for performance
inline double fast_calc(double a, double b) {
    return a * b;
}
```

### Overloading & Defaults
```cpp
void process(int id) { /* code */ }
void process(const std::string& name) { /* code */ }
void process(int id, double price = 0.0) { /* code */ }
```

## Pointers & References

### Pointers
```cpp
int* ptr = nullptr;                         // Modern null pointer (C++11)
int value = 42;
ptr = &value;                               // Address-of
int retrieved = *ptr;                       // Dereference

// Dynamic allocation (avoid in modern C++)
int* dynamic = new int{42};
delete dynamic;                              // Manual cleanup
```

### References
```cpp
int original = 42;
int& ref = original;                        // L-value reference
const int& const_ref = original;            // Const reference
void func(int&& temp) { /* code */ }        // R-value reference (C++11)
```

## I/O Operations

### Console I/O
```cpp
#include <iostream>
#include <iomanip>

std::cout << "Price: $" << std::fixed << std::setprecision(2) << 150.50;
std::cin >> variable;
std::getline(std::cin, string_var);
```

### File I/O
```cpp
#include <fstream>
#include <sstream>

std::ifstream input("file.txt");
std::ofstream output("file.txt", std::ios::app);
std::stringstream ss(line);
```

## Modern C++ Features (C++11+)

### Auto & Type Deduction
```cpp
auto price = 150.50;                        // double
auto symbol = std::string{"AAPL"};          // std::string
auto container = std::vector<int>{1, 2, 3}; // std::vector<int>
```

### Range-Based For
```cpp
std::vector<int> prices = {100, 101, 102};
for (const auto& price : prices) { /* code */ }

// Structured bindings (C++17)
std::map<std::string, double> data = {{"AAPL", 150.0}};
for (const auto& [symbol, price] : data) { /* code */ }
```

### Nullptr
```cpp
int* ptr = nullptr;                         // Instead of NULL or 0
process_order(nullptr);                     // Calls pointer overload
process_order(0);                           // Calls int overload
```

## HFT Performance Tips

### Memory Layout
- **Cache alignment**: Structure data for sequential access
- **Padding awareness**: Order struct members by size (largest first)
- **Contiguous storage**: Use arrays/vectors for order books

### Latency Optimization
- **Inline functions**: Use for small, hot-path functions
- **Const correctness**: Enables compiler optimizations
- **References over pointers**: Avoid unnecessary indirection
- **Stack allocation**: Prefer over heap for small objects

### Best Practices
- **RAII**: Automatic resource management
- **Smart pointers**: unique_ptr, shared_ptr over raw pointers
- **Bounds checking**: Validate array access
- **Exception safety**: Design for exception guarantees

## Common Patterns

### Order Processing
```cpp
struct Order {
    uint64_t timestamp;
    uint32_t price;
    uint32_t quantity;
    char symbol[8];
};

void process_order(const Order& order) {
    // Process order efficiently
}
```

### Market Data Handling
```cpp
void update_price(volatile double& price, double new_price) {
    price = new_price;  // Atomic update for market data
}
```

### Error Handling
```cpp
bool validate_price(double price) {
    return price > 0.0 && price < MAX_PRICE;
}

double get_validated_price() {
    double price;
    while (!(std::cin >> price) || !validate_price(price)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return price;
}
```
