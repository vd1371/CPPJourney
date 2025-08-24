# Exercises: Phase 1, Step 2 - Modern C++ Fundamentals

## Overview

These exercises will help you practice the modern C++ features covered in this step. Each exercise builds upon the previous ones and incorporates real-world high-frequency trading scenarios. Complete them in order to reinforce your understanding.

## Exercise 1: Smart Order Management System

### Objective
Create a basic order management system using smart pointers and modern C++ features.

### Requirements
- Implement an `Order` class with price, quantity, and symbol
- Use `std::unique_ptr` for order ownership
- Implement an `OrderBook` class that manages orders
- Use uniform initialization and initializer lists
- Demonstrate proper memory management

### Starter Code
```cpp
#include <memory>
#include <vector>
#include <string>
#include <iostream>

// TODO: Implement Order class with smart pointer management
// TODO: Implement OrderBook class with modern C++ features
// TODO: Demonstrate auto, decltype, and lambda usage

int main() {
    // TODO: Create order management system
    // TODO: Add orders to order book
    // TODO: Process orders with lambda expressions
    return 0;
}
```

### Evaluation Criteria
- Correct use of `std::unique_ptr` and `std::make_unique`
- Proper implementation of uniform initialization
- Effective use of `auto` and `decltype`
- Clean, readable code with modern C++ idioms

### HFT Context
This system simulates the core order management functionality found in real trading engines, where orders must be safely managed and processed without memory leaks.

---

## Exercise 2: Market Data Filtering with Lambdas

### Objective
Create a flexible market data filtering system using lambda expressions and modern C++ features.

### Requirements
- Implement a `MarketData` class with price, volume, and timestamp
- Create a `DataFilter` class that uses lambda expressions for filtering
- Implement generic filtering algorithms using C++14 features
- Use `std::shared_ptr` for shared market data
- Demonstrate capture clauses and generic lambdas

### Starter Code
```cpp
#include <memory>
#include <vector>
#include <functional>
#include <chrono>
#include <string>

struct MarketData {
    // TODO: Implement market data structure
};

class DataFilter {
public:
    // TODO: Implement filtering methods using lambdas
    // TODO: Support generic filtering with auto parameters
    // TODO: Use capture clauses appropriately
};

// TODO: Implement main function with filtering examples
```

### Evaluation Criteria
- Correct implementation of lambda expressions with capture clauses
- Effective use of generic lambdas (C++14)
- Proper smart pointer usage for shared data
- Clean separation of concerns between data and filtering logic

### HFT Context
Market data filtering is crucial in trading systems for identifying relevant price movements, volume spikes, and other market events that trigger trading decisions.

---

## Exercise 3: Advanced Order Matching Engine

### Objective
Build a sophisticated order matching engine that demonstrates advanced modern C++ features.

### Requirements
- Implement order matching logic using lambda expressions
- Use `std::weak_ptr` to prevent circular references
- Create a generic order type system using `auto` and `decltype`
- Implement exception-safe resource management
- Use modern initialization throughout

### Starter Code
```cpp
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <stdexcept>

enum class OrderType { BUY, SELL };
enum class OrderStatus { PENDING, FILLED, CANCELLED };

class Order {
    // TODO: Implement order with weak_ptr for parent relationships
};

class MatchingEngine {
public:
    // TODO: Implement matching logic using lambdas
    // TODO: Use weak_ptr to avoid circular references
    // TODO: Implement exception-safe operations
};

// TODO: Implement main function with comprehensive testing
```

### Evaluation Criteria
- Correct use of `std::weak_ptr` to break circular references
- Effective lambda-based matching algorithms
- Exception safety and RAII principles
- Modern C++ syntax and idioms throughout

### HFT Context
Order matching engines are the heart of trading systems, responsible for executing trades efficiently while maintaining data integrity and preventing memory leaks.

---

## Exercise 4: Performance Benchmarking System

### Objective
Create a performance benchmarking system that measures the efficiency of different modern C++ approaches.

### Requirements
- Benchmark smart pointer vs. raw pointer performance
- Measure lambda expression overhead
- Compare different initialization methods
- Use `std::chrono` for precise timing
- Implement statistical analysis of results

### Starter Code
```cpp
#include <memory>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

class BenchmarkRunner {
public:
    // TODO: Implement benchmarking methods
    // TODO: Compare smart pointers vs raw pointers
    // TODO: Measure lambda performance
    // TODO: Analyze initialization performance
};

// TODO: Implement main function with comprehensive benchmarks
```

### Evaluation Criteria
- Accurate performance measurement using modern timing facilities
- Meaningful comparison between different approaches
- Statistical analysis of results
- Clean, maintainable benchmarking code

### HFT Context
Performance is critical in high-frequency trading. Understanding the overhead of different C++ features helps developers make informed decisions about when to use each approach.

---

## Exercise 5: Configuration Management System

### Objective
Build a flexible configuration management system using modern C++ features.

### Requirements
- Implement a `Config` class using initializer lists
- Use `std::variant` (C++17) for different value types
- Implement lambda-based configuration validation
- Use smart pointers for configuration ownership
- Create a builder pattern with modern C++ syntax

### Starter Code
```cpp
#include <memory>
#include <variant>
#include <string>
#include <map>
#include <functional>
#include <initializer_list>

class ConfigValue {
    // TODO: Implement using std::variant for multiple types
};

class Configuration {
public:
    // TODO: Implement configuration management
    // TODO: Use initializer lists for setup
    // TODO: Implement lambda-based validation
};

// TODO: Implement main function with configuration examples
```

### Evaluation Criteria
- Effective use of `std::variant` for type-safe configuration values
- Clean initializer list implementation
- Lambda-based validation system
- Modern C++ design patterns

### HFT Context
Configuration management is essential in trading systems for setting risk parameters, order limits, and strategy parameters that can be changed without recompilation.

---

## Submission Guidelines

1. **Complete all exercises** in order of difficulty
2. **Use modern C++ features** extensively throughout your solutions
3. **Include comprehensive testing** for each exercise
4. **Document your design decisions** with comments
5. **Measure performance** where applicable
6. **Ensure exception safety** in all implementations

## Bonus Challenges

- **Memory Profiling**: Use tools like Valgrind to verify no memory leaks
- **Performance Optimization**: Profile your code and optimize bottlenecks
- **Template Metaprogramming**: Extend exercises with template-based solutions
- **Exception Handling**: Implement comprehensive error handling strategies

## Evaluation Rubric

| Criteria | Excellent (5) | Good (3) | Needs Improvement (1) |
|----------|---------------|----------|----------------------|
| Modern C++ Usage | Extensive use of C++11/14 features | Moderate use of modern features | Limited modern C++ usage |
| Code Quality | Clean, readable, well-structured | Generally clean with minor issues | Poor structure or readability |
| Performance | Optimized and benchmarked | Basic performance considerations | No performance considerations |
| HFT Relevance | Strong trading system context | Moderate trading relevance | Weak trading system context |
| Exception Safety | Comprehensive RAII and exception safety | Basic exception safety | Poor exception handling |

**Total Score**: 25 points (5 points per exercise)

**Passing Score**: 15 points (60%)

Complete these exercises to solidify your understanding of modern C++ fundamentals and prepare for the next step in your C++ journey.
