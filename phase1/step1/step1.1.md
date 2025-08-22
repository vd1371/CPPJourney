# Phase 1, Step 1.1: Core Syntax and Language Basics

## Overview

This step bridges the gap between Python's dynamic, interpreted nature and C++'s compiled, statically-typed paradigm. You'll learn fundamental C++ syntax while understanding how these concepts apply to high-frequency trading systems where performance, predictability, and low latency are critical.

## Learning Objectives

- Master basic C++ data types and their memory characteristics
- Understand variables, control structures, and function declarations
- Learn pointers and references for efficient memory manipulation
- Implement basic I/O operations and file handling
- Apply modern C++ features (auto, range-based for, nullptr) for cleaner code

## Prerequisites

- Basic programming knowledge (Python experience is helpful)
- Completed Phase 0 setup (compiler, IDE, build tools)
- Understanding of compilation vs. interpretation

## Core Concepts

### 1. Data Types and Memory Management

#### Fundamental Types
C++ provides precise control over data representation, crucial for HFT systems where memory layout affects cache performance:

```cpp
// Integer types with explicit sizes
int8_t small_int = 42;        // 8-bit, -128 to 127
int16_t medium_int = 32767;   // 16-bit, -32,768 to 32,767
int32_t large_int = 2147483647; // 32-bit
int64_t huge_int = 9223372036854775807LL; // 64-bit

// Unsigned variants for non-negative values
uint32_t price = 15000;       // Price in cents (no negative prices)
uint64_t timestamp = 1640995200000ULL; // Unix timestamp in milliseconds

// Floating-point precision
float single_precision = 3.14159f;     // 32-bit, ~7 decimal digits
double double_precision = 3.14159265359; // 64-bit, ~15 decimal digits
long double extended = 3.14159265359L;   // 80-bit or 128-bit (platform dependent)
```

#### Type Modifiers
```cpp
// Const correctness - prevents accidental modification
const double PI = 3.14159;
const int MAX_ORDERS = 10000;

// Volatile - tells compiler value may change externally (important for HFT)
volatile double current_price;  // Price from market data feed
volatile bool market_open;      // Market status flag

// Static - file scope or class member persistence
static int order_counter = 0;   // Persists across function calls
```

#### Memory Layout Considerations
In HFT, understanding memory layout is crucial for cache performance:

```cpp
// Good: Contiguous memory layout for order book
struct Order {
    uint64_t timestamp;     // 8 bytes
    uint32_t price;         // 4 bytes
    uint32_t quantity;      // 4 bytes
    char symbol[8];         // 8 bytes
}; // Total: 24 bytes, cache-line friendly

// Avoid: Padding issues
struct BadOrder {
    char symbol[8];         // 8 bytes
    uint64_t timestamp;     // 8 bytes (may cause padding)
    uint32_t price;         // 4 bytes
    uint32_t quantity;      // 4 bytes
}; // May have padding between symbol and timestamp
```

#### Volatile Variables
The `volatile` keyword is crucial in HFT systems where variables may be modified by external sources like hardware interrupts, memory-mapped I/O, or signal handlers:

```cpp
// Market data variables that change asynchronously
volatile double last_price = 0.0;        // Updated by market data feed
volatile bool market_open = false;       // Updated by market status monitor
volatile uint64_t message_count = 0;     // Updated by message handler

// Hardware register access (memory-mapped I/O)
volatile uint32_t* fpga_status = (uint32_t*)0x80000000;  // FPGA status register
volatile uint32_t* network_buffer = (uint32_t*)0x90000000; // Network card buffer

// Example: Waiting for market data update
void wait_for_price_update() {
    volatile bool price_updated = false;
    
    // Without volatile, compiler might optimize this into infinite loop
    while (!price_updated) {
        // Check if new price data arrived
        if (*fpga_status & 0x01) {  // Check status bit
            price_updated = true;
            last_price = read_market_price();
        }
    }
}

// Example: Signal handling in trading system
volatile sig_atomic_t shutdown_requested = 0;

void signal_handler(int signal) {
    shutdown_requested = 1;  // Safe to modify in signal handler
}

// Main trading loop
void trading_loop() {
    while (!shutdown_requested) {  // Volatile ensures fresh read
        process_market_data();
        execute_trading_strategy();
    }
}
```

**Key Points:**
- **Prevents optimization**: Compiler won't cache volatile variables in registers
- **Forces memory access**: Every read/write goes directly to memory
- **Signal safety**: Use `volatile sig_atomic_t` for signal handler communication
- **Hardware interface**: Essential for memory-mapped hardware registers
- **Not thread-safe**: `volatile` doesn't provide atomic operations or thread safety

**HFT Applications:**
- Market data feeds that update asynchronously
- FPGA communication and status registers
- Network card buffer monitoring
- Interrupt-driven event handling
- Emergency shutdown signals

### 2. Variables and Declaration

#### Variable Declaration and Initialization
Modern C++ provides multiple initialization methods:

```cpp
// Traditional C-style initialization
int old_way = 42;

// Modern uniform initialization (C++11)
int modern_way{42};
int price{15000};
double spread{0.01};

// Auto type deduction (C++11) - useful for complex types
auto current_price = 150.50;           // double
auto symbol = std::string{"AAPL"};     // std::string
auto order_count = 1000;               // int

// Decltype for type inference
int base_price = 100;
decltype(base_price) adjusted_price = base_price * 1.1;
```

#### Scope and Lifetime
```cpp
// Block scope
{
    int local_var = 42;
    // local_var exists only in this block
} // local_var destroyed here

// Function scope
void process_order() {
    static int order_id = 0;  // Persists across function calls
    order_id++;
    int temp_var = 100;       // Destroyed when function exits
}

// Global scope (use sparingly in HFT)
extern const double TICK_SIZE;  // Declared elsewhere
```

### 3. Control Structures

#### Conditional Statements
```cpp
// Basic if-else
if (price > 100.0) {
    std::cout << "High price stock\n";
} else if (price > 50.0) {
    std::cout << "Medium price stock\n";
} else {
    std::cout << "Low price stock\n";
}

// Switch statement for discrete values
switch (order_type) {
    case 'M':  // Market order
        std::cout << "Processing market order\n";
        break;
    case 'L':  // Limit order
        std::cout << "Processing limit order\n";
        break;
    case 'S':  // Stop order
        std::cout << "Processing stop order\n";
        break;
    default:
        std::cout << "Unknown order type\n";
        break;
}

// Modern switch with initialization (C++17)
switch (auto status = get_order_status(); status) {
    case OrderStatus::PENDING:
        std::cout << "Order pending\n";
        break;
    case OrderStatus::FILLED:
        std::cout << "Order filled\n";
        break;
}
```

#### Loops
```cpp
// Traditional for loop
for (int i = 0; i < order_count; ++i) {
    process_order(i);
}

// Range-based for loop (C++11) - preferred for containers
std::vector<int> prices = {100, 101, 102, 103};
for (const auto& price : prices) {
    std::cout << "Price: " << price << '\n';
}

// While loop
while (market_open && !orders.empty()) {
    process_next_order();
}

// Do-while loop
do {
    update_market_data();
} while (market_open);
```

### 4. Functions

#### Function Declaration and Definition
```cpp
// Function declaration (prototype)
double calculate_spread(double bid, double ask);
void process_market_order(const std::string& symbol, int quantity);

// Function definition
double calculate_spread(double bid, double ask) {
    return ask - bid;
}

void process_market_order(const std::string& symbol, int quantity) {
    std::cout << "Processing " << quantity << " shares of " << symbol << '\n';
}

// Inline functions for performance-critical code
inline double fast_multiply(double a, double b) {
    return a * b;
}
```

#### Function Overloading
```cpp
// Overload by parameter types
void log_order(int order_id) {
    std::cout << "Order ID: " << order_id << '\n';
}

void log_order(const std::string& symbol) {
    std::cout << "Symbol: " << symbol << '\n';
}

void log_order(int order_id, const std::string& symbol) {
    std::cout << "Order " << order_id << " for " << symbol << '\n';
}
```

#### Default Parameters
```cpp
void place_order(const std::string& symbol, 
                 int quantity, 
                 double price = 0.0,  // Market order if price not specified
                 char order_type = 'M') {
    // Implementation
}
```

### 5. Pointers and References

#### Pointers
Pointers provide direct memory access, essential for HFT performance:

```cpp
// Pointer declaration and usage
int* price_ptr = nullptr;  // Modern C++11 nullptr instead of NULL
int current_price = 150;

price_ptr = &current_price;  // Address-of operator
std::cout << "Price value: " << *price_ptr << '\n';  // Dereference

// Dynamic memory allocation (use smart pointers in modern C++)
int* dynamic_price = new int{200};
delete dynamic_price;  // Manual cleanup (avoid in modern C++)

// Pointer arithmetic for arrays
int prices[] = {100, 101, 102, 103};
int* first = prices;
int* last = prices + 4;  // Point to one past the end

for (int* p = first; p != last; ++p) {
    std::cout << "Price: " << *p << '\n';
}
```

#### References
References provide safer alternatives to pointers:

```cpp
// L-value reference
int price = 150;
int& price_ref = price;  // Reference to price
price_ref = 151;         // Modifies original price

// Const reference for efficiency
void process_price(const int& price) {
    // Cannot modify price, but avoids copying
    std::cout << "Processing price: " << price << '\n';
}

// R-value reference (C++11) for move semantics
void process_order(int&& order_id) {
    // order_id is a temporary value
    std::cout << "Processing temporary order: " << order_id << '\n';
}
```

### 6. Input/Output Streams

#### Basic I/O Operations
```cpp
#include <iostream>
#include <iomanip>

// Output formatting
std::cout << "Current price: $" << std::fixed << std::setprecision(2) 
          << 150.50 << '\n';

// Input with validation
double get_price() {
    double price;
    std::cout << "Enter price: ";
    
    while (!(std::cin >> price) || price <= 0) {
        std::cin.clear();  // Clear error flags
        std::cin.ignore(10000, '\n');  // Clear input buffer
        std::cout << "Invalid price. Enter a positive number: ";
    }
    
    return price;
}

// String input
std::string get_symbol() {
    std::string symbol;
    std::cout << "Enter symbol: ";
    std::getline(std::cin, symbol);
    return symbol;
}
```

#### File I/O
```cpp
#include <fstream>
#include <sstream>

// Reading market data from file
void read_market_data(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string symbol;
        double price;
        int volume;
        
        if (iss >> symbol >> price >> volume) {
            std::cout << "Symbol: " << symbol 
                      << ", Price: " << price 
                      << ", Volume: " << volume << '\n';
        }
    }
}

// Writing order log to file
void log_order(const std::string& symbol, int quantity, double price) {
    std::ofstream log_file("orders.log", std::ios::app);
    if (log_file.is_open()) {
        log_file << symbol << " " << quantity << " " << price << '\n';
    }
}
```

### 7. Modern C++ Features (C++11+)

#### Auto Keyword
```cpp
// Type deduction for complex types
auto price_vector = std::vector<double>{100.0, 101.0, 102.0};
auto price_map = std::map<std::string, double>{{"AAPL", 150.0}, {"GOOGL", 2800.0}};

// Lambda expressions
auto price_filter = [](double price) { return price > 100.0; };

// Range-based for with auto
for (const auto& [symbol, price] : price_map) {
    std::cout << symbol << ": $" << price << '\n';
}
```

#### Range-Based For Loops
```cpp
// Traditional array iteration
int prices[] = {100, 101, 102, 103};
for (int price : prices) {
    std::cout << "Price: " << price << '\n';
}

// STL container iteration
std::vector<std::string> symbols = {"AAPL", "GOOGL", "MSFT"};
for (const auto& symbol : symbols) {
    std::cout << "Symbol: " << symbol << '\n';
}

// Map iteration (C++17 structured bindings)
std::map<std::string, double> price_data = {{"AAPL", 150.0}, {"GOOGL", 2800.0}};
for (const auto& [symbol, price] : price_data) {
    std::cout << symbol << ": $" << price << '\n';
}
```

#### Nullptr
```cpp
// Modern null pointer constant
int* price_ptr = nullptr;  // Instead of NULL or 0

// Function overloading with nullptr
void process_order(int* order_ptr) {
    std::cout << "Processing order pointer\n";
}

void process_order(int order_id) {
    std::cout << "Processing order ID: " << order_id << '\n';
}

// Call with nullptr
process_order(nullptr);  // Calls first overload
process_order(0);        // Calls second overload
```

## HFT-Specific Considerations

### Performance Implications
- **Cache locality**: Structure data for sequential access patterns
- **Branch prediction**: Minimize conditional statements in hot paths
- **Memory alignment**: Ensure data structures align with cache lines
- **Function inlining**: Use inline for small, frequently called functions

### Latency Optimization
- **Avoid dynamic allocation**: Use stack allocation and object pools
- **Minimize function calls**: Inline critical functions
- **Use references**: Avoid unnecessary copying
- **Const correctness**: Enable compiler optimizations

### Memory Safety
- **RAII**: Use automatic resource management
- **Smart pointers**: Prefer unique_ptr and shared_ptr over raw pointers
- **Bounds checking**: Validate array indices and container access
- **Exception safety**: Design functions to be exception-safe

## Common Pitfalls and Best Practices

### Pitfalls to Avoid
1. **Uninitialized variables**: Always initialize variables
2. **Memory leaks**: Use smart pointers instead of raw pointers
3. **Buffer overflows**: Validate array bounds and use std::vector
4. **Dangling references**: Ensure referenced objects outlive references
5. **Type mismatches**: Use explicit casting when necessary

### Best Practices
1. **Use const**: Mark variables and parameters as const when possible
2. **Prefer references**: Use references over pointers when ownership isn't transferred
3. **RAII**: Let constructors acquire resources and destructors release them
4. **Modern C++**: Leverage auto, range-based for, and nullptr
5. **Clear naming**: Use descriptive names for variables and functions

## Summary

This step establishes the foundation for modern C++ development with a focus on HFT applications. You've learned:

- **Data types** and their memory characteristics for optimal performance
- **Variables and control structures** for program flow control
- **Functions** with modern parameter passing and overloading
- **Pointers and references** for efficient memory manipulation
- **I/O operations** for data input and logging
- **Modern C++ features** that improve code clarity and safety

These fundamentals provide the building blocks for more advanced topics like templates, STL containers, and concurrency. In HFT systems, understanding these basics is crucial for writing performant, maintainable code that can handle high-frequency market data and order processing.

## Next Steps

In the next step (1.2: Modern C++ Fundamentals), you'll explore:
- Advanced initialization techniques
- Lambda expressions for functional programming
- Smart pointers for automatic memory management
- Modern C++11/14 features that enhance code safety and expressiveness
