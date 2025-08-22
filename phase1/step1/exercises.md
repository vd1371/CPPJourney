# Exercises: Core Syntax and Language Basics

## Overview
These exercises will help you practice the core C++ concepts covered in this step. Each exercise builds upon the previous one and incorporates real-world HFT scenarios. Focus on writing clean, efficient code that demonstrates modern C++ practices.

## Exercise 1: Basic Market Data Structure
**Difficulty**: Beginner  
**Estimated Time**: 15 minutes

### Requirements
Create a simple market data structure and functions to process basic trading information.

### Task
1. Define a `MarketData` struct with the following fields:
   - Symbol (string, max 8 characters)
   - Price (double)
   - Volume (integer)
   - Timestamp (64-bit integer)
2. Implement a function to calculate the average price from an array of market data
3. Create a function to find the highest volume trade
4. Use modern C++ initialization and range-based for loops

### Starter Template
```cpp
#include <iostream>
#include <string>
#include <vector>

// TODO: Define MarketData struct

// TODO: Implement calculate_average_price function

// TODO: Implement find_highest_volume function

int main() {
    // TODO: Create sample market data and test functions
    return 0;
}
```

### Evaluation Criteria
- Correct struct definition with appropriate data types
- Proper use of const references for efficiency
- Modern C++11+ features (auto, range-based for)
- Clean, readable code structure

---

## Exercise 2: Order Processing System
**Difficulty**: Beginner-Intermediate  
**Estimated Time**: 25 minutes

### Requirements
Build a simple order processing system that demonstrates control structures, functions, and basic error handling.

### Task
1. Create an `Order` struct with:
   - Order ID (integer)
   - Symbol (string)
   - Quantity (integer)
   - Price (double)
   - Order type (char: 'M' for market, 'L' for limit, 'S' for stop)
2. Implement order validation functions:
   - Check if price is positive
   - Verify quantity is within limits (1-10000)
   - Validate symbol length (1-8 characters)
3. Create a function to process orders based on type
4. Use switch statements and proper error handling

### Starter Template
```cpp
#include <iostream>
#include <string>
#include <vector>

// TODO: Define Order struct

// TODO: Implement validation functions

// TODO: Implement order processing function

int main() {
    // TODO: Create test orders and demonstrate functionality
    return 0;
}
```

### Evaluation Criteria
- Proper use of switch statements and control structures
- Input validation and error handling
- Function overloading where appropriate
- Const correctness and efficient parameter passing

---

## Exercise 3: Price Calculator with Pointers and References
**Difficulty**: Intermediate  
**Estimated Time**: 30 minutes

### Requirements
Create a price calculation system that demonstrates understanding of pointers, references, and memory management.

### Task
1. Implement a `PriceCalculator` class with:
   - Methods to calculate bid-ask spread
   - Volume-weighted average price (VWAP)
   - Price change percentage
2. Use pointers and references appropriately:
   - Pass large data structures by const reference
   - Use pointers for optional parameters
   - Demonstrate pointer arithmetic for array processing
3. Include proper error handling for edge cases
4. Optimize for performance (consider inline functions)

### Starter Template
```cpp
#include <iostream>
#include <vector>
#include <cmath>

class PriceCalculator {
public:
    // TODO: Implement constructor and methods
    
    // TODO: Calculate bid-ask spread
    double calculate_spread(double bid, double ask);
    
    // TODO: Calculate VWAP
    double calculate_vwap(const std::vector<double>& prices, 
                         const std::vector<int>& volumes);
    
    // TODO: Calculate price change percentage
    double calculate_change_percent(double old_price, double new_price);
    
    // TODO: Process price array with pointer arithmetic
    void process_prices(double* prices, int count);
};

int main() {
    // TODO: Test PriceCalculator functionality
    return 0;
}
```

### Evaluation Criteria
- Correct use of pointers vs. references
- Efficient parameter passing
- Proper error handling
- Performance considerations (inline functions)

---

## Exercise 4: Market Data Logger
**Difficulty**: Intermediate  
**Estimated Time**: 35 minutes

### Requirements
Build a file I/O system for logging market data and order activities.

### Task
1. Create a `MarketLogger` class with:
   - Methods to log market data to files
   - Order activity logging
   - Error logging with timestamps
2. Implement file I/O operations:
   - Write market data in CSV format
   - Append order logs with timestamps
   - Read and parse log files
3. Use modern C++ features:
   - RAII for file handling
   - Exception safety
   - Const correctness
4. Include data validation and formatting

### Starter Template
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>

class MarketLogger {
private:
    std::string log_directory;
    
public:
    // TODO: Constructor and destructor
    
    // TODO: Log market data to CSV
    bool log_market_data(const std::string& symbol, double price, 
                        int volume, uint64_t timestamp);
    
    // TODO: Log order activity
    bool log_order(int order_id, const std::string& symbol, 
                  int quantity, double price, char order_type);
    
    // TODO: Read and parse log files
    std::vector<std::string> read_log_entries(const std::string& filename);
    
    // TODO: Get current timestamp
    uint64_t get_current_timestamp();
};

int main() {
    // TODO: Test MarketLogger functionality
    return 0;
}
```

### Evaluation Criteria
- Proper file I/O operations
- RAII implementation
- Exception safety
- Data formatting and validation

---

## Exercise 5: High-Performance Order Book
**Difficulty**: Advanced  
**Estimated Time**: 45 minutes

### Requirements
Design a simple order book system that demonstrates advanced understanding of C++ fundamentals for HFT applications.

### Task
1. Create an `OrderBook` class with:
   - Bid and ask price levels
   - Order matching logic
   - Market depth tracking
2. Implement performance optimizations:
   - Cache-friendly data structures
   - Efficient memory layout
   - Minimal function call overhead
3. Use modern C++ features:
   - Auto type deduction
   - Range-based for loops
   - Constexpr where appropriate
4. Include benchmarking capabilities

### Starter Template
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <iomanip>

struct OrderLevel {
    double price;
    int total_quantity;
    int order_count;
};

class OrderBook {
private:
    // TODO: Design efficient data structures for bids and asks
    
public:
    // TODO: Constructor and destructor
    
    // TODO: Add order to book
    void add_order(double price, int quantity, bool is_bid);
    
    // TODO: Remove order from book
    void remove_order(double price, int quantity, bool is_bid);
    
    // TODO: Get best bid and ask
    double get_best_bid() const;
    double get_best_ask() const;
    
    // TODO: Get market depth
    std::vector<OrderLevel> get_market_depth(int levels) const;
    
    // TODO: Match orders
    void match_orders();
    
    // TODO: Benchmark order processing
    void benchmark_performance(int iterations);
};

int main() {
    // TODO: Test OrderBook with realistic market scenarios
    return 0;
}
```

### Evaluation Criteria
- Efficient data structure design
- Performance optimization techniques
- Modern C++ feature usage
- Realistic HFT scenario handling

---

## Bonus Exercise: Cross-Compiler Compatibility
**Difficulty**: Advanced  
**Estimated Time**: 20 minutes

### Requirements
Ensure your code compiles and runs correctly with different C++ compilers (GCC, Clang, MSVC).

### Task
1. Test all previous exercises with at least two different compilers
2. Identify and fix any compiler-specific issues
3. Use feature detection macros where necessary
4. Document any compiler-specific workarounds

### Evaluation Criteria
- Cross-compiler compatibility
- Proper use of feature detection
- Documentation of compiler differences

---

## General Guidelines

### Code Quality
- Use meaningful variable and function names
- Include appropriate comments for complex logic
- Follow consistent formatting and indentation
- Implement proper error handling

### Performance Considerations
- Minimize unnecessary copying
- Use const references for large objects
- Consider cache locality in data structures
- Profile critical code paths

### Modern C++ Practices
- Prefer range-based for loops over traditional loops
- Use auto for type deduction where appropriate
- Implement RAII for resource management
- Leverage const correctness

### Testing
- Test with various input values
- Include edge cases and error conditions
- Verify performance characteristics
- Test cross-compiler compatibility

---

## Submission Requirements

For each exercise, provide:
1. Complete, compilable source code
2. Brief explanation of design decisions
3. Performance analysis (for advanced exercises)
4. Any compiler-specific considerations

**Remember**: In HFT systems, every nanosecond counts. Focus on writing efficient, predictable code that can handle high-frequency market data processing.
