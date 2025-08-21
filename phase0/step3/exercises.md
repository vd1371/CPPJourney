# Exercises: Development Tools and Quality Assurance

## Overview
These exercises will help you set up and use modern C++ development tools for quality assurance. You'll configure static analysis, code formatting, debugging tools, and integrate them into your development workflow.

## Exercise 1: Setting Up Static Analysis Tools

### Objective
Set up clang-tidy and cppcheck for a C++ project and configure them to catch common issues.

### Requirements
- Install clang-tidy and cppcheck
- Configure tools for HFT-focused analysis
- Create a basic project structure
- Run analysis and interpret results

### Starter Code
Create a simple project with the following structure:
```
quality-demo/
├── CMakeLists.txt
├── include/
│   └── trading_engine.h
├── src/
│   ├── trading_engine.cpp
│   └── main.cpp
└── .clang-format
```

**CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.20)
project(QualityDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable clang-tidy
option(ENABLE_CLANG_TIDY "Enable clang-tidy" ON)

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY 
            ${CLANG_TIDY_EXE};
            -checks=performance-*,bugprone-*,modernize-*;
            -header-filter=.*
        )
    endif()
endif()

add_executable(trading_demo src/main.cpp src/trading_engine.cpp)

# Custom target for static analysis
add_custom_target(analyze
    COMMAND cppcheck --enable=all --xml --xml-version=2 
            ${CMAKE_SOURCE_DIR}/src 2> ${CMAKE_BINARY_DIR}/cppcheck-report.xml
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running static analysis"
)
```

**trading_engine.h:**
```cpp
#pragma once
#include <string>
#include <vector>
#include <memory>

class Order {
public:
    Order(std::string symbol, double price, int quantity);
    ~Order();
    
    std::string getSymbol() const;
    double getPrice() const;
    int getQuantity() const;
    
private:
    std::string symbol;
    double price;
    int quantity;
};

class TradingEngine {
public:
    TradingEngine();
    ~TradingEngine();
    
    void processOrder(const Order& order);
    void addOrder(const Order& order);
    std::vector<Order> getOrders() const;
    
private:
    std::vector<Order> orders;
    std::unique_ptr<int> internalState;
};
```

**trading_engine.cpp:**
```cpp
#include "trading_engine.h"
#include <iostream>

Order::Order(std::string symbol, double price, int quantity) 
    : symbol(std::move(symbol)), price(price), quantity(quantity) {
}

Order::~Order() {
    // Potential issue: destructor with side effects
    std::cout << "Order destroyed" << std::endl;
}

std::string Order::getSymbol() const {
    return symbol;
}

double Order::getPrice() const {
    return price;
}

int Order::getQuantity() const {
    return quantity;
}

TradingEngine::TradingEngine() : internalState(std::make_unique<int>(0)) {
}

TradingEngine::~TradingEngine() = default;

void TradingEngine::processOrder(const Order& order) {
    // Potential issue: copying instead of reference
    Order orderCopy = order;
    addOrder(orderCopy);
}

void TradingEngine::addOrder(const Order& order) {
    orders.push_back(order);
}

std::vector<Order> TradingEngine::getOrders() const {
    return orders; // Potential issue: returning copy
}
```

**main.cpp:**
```cpp
#include "trading_engine.h"
#include <iostream>

int main() {
    TradingEngine engine;
    
    // Create some orders
    Order order1("AAPL", 150.0, 100);
    Order order2("GOOGL", 2800.0, 50);
    
    engine.addOrder(order1);
    engine.addOrder(order2);
    
    // Process orders
    engine.processOrder(order1);
    
    // Get and display orders
    auto orders = engine.getOrders();
    for (const auto& order : orders) {
        std::cout << "Symbol: " << order.getSymbol() 
                  << ", Price: " << order.getPrice() 
                  << ", Quantity: " << order.getQuantity() << std::endl;
    }
    
    return 0;
}
```

### Tasks
1. **Install Tools**: Install clang-tidy and cppcheck on your system
2. **Build Project**: Use CMake to build the project with clang-tidy enabled
3. **Run Analysis**: Execute both clang-tidy and cppcheck on the source code
4. **Fix Issues**: Identify and fix the quality issues found by the tools
5. **Re-run Analysis**: Verify that all issues have been resolved

### Evaluation Criteria
- All tools are properly installed and configured
- Project builds successfully with clang-tidy enabled
- Static analysis identifies the intentional issues in the code
- Issues are properly fixed according to modern C++ best practices
- Final analysis shows no critical issues



## Exercise 2: Debugging and Memory Analysis

### Objective
Set up and use debugging tools (GDB/LLDB) and memory analysis tools (Valgrind) to identify and fix issues in C++ code.

### Requirements
- Configure debugging tools for the trading engine project
- Use Valgrind to detect memory issues
- Practice advanced debugging techniques
- Integrate debugging into the development workflow

### Enhanced Project
Add the following problematic code to your trading engine:

**Add to trading_engine.cpp:**
```cpp
void TradingEngine::processOrder(const Order& order) {
    // Memory leak: allocate but never delete
    int* temp = new int(42);
    
    // Potential null pointer dereference
    if (internalState) {
        *internalState = *temp;
    }
    
    // Use after free (simulated)
    delete temp;
    *temp = 100; // This will cause issues
    
    addOrder(order);
}

void TradingEngine::addOrder(const Order& order) {
    // Potential issue: copying large objects
    orders.push_back(order);
    
    // Memory allocation without bounds checking
    if (orders.size() > 1000) {
        // Simulate memory exhaustion
        while (true) {
            orders.push_back(order);
        }
    }
}
```

### Tasks
1. **Debug Setup**: Configure GDB/LLDB for the project
2. **Memory Analysis**: Use Valgrind to detect memory issues
3. **Interactive Debugging**: Set breakpoints and examine program state
4. **Issue Resolution**: Fix all identified problems
5. **Verification**: Confirm that all issues are resolved

### Debugging Scenarios
- Set breakpoints on specific trading functions
- Use conditional breakpoints for specific order types
- Examine memory layout of data structures
- Trace execution flow through complex code paths
- Use reverse debugging to understand crash scenarios

### Evaluation Criteria
- Debugging tools are properly configured
- Valgrind identifies all memory issues
- Interactive debugging sessions are productive
- All identified issues are properly resolved
- Debugging workflow is integrated into development process



## Solutions

### Exercise 1: Static Analysis Solutions

**Problems Identified and Fixed:**

1. **Destructor with Side Effects**: The original `Order::~Order()` destructor had a `std::cout` statement, which violates the principle that destructors should not have side effects. This can cause issues in production environments and makes the code unpredictable.

2. **Unnecessary Object Copying**: In `TradingEngine::processOrder()`, the code was creating an unnecessary copy of the order object (`Order orderCopy = order;`), which wastes memory and CPU cycles, especially critical in HFT systems.

3. **Return by Value Instead of Reference**: The `getOrders()` method was returning a copy of the entire vector, which is expensive for large collections and unnecessary when the caller only needs to read the data.

4. **Missing Const Correctness**: The `getOrders()` method should return a const reference to prevent accidental modifications to the internal data structure.


**Fixed trading_engine.cpp:**
```cpp
#include "trading_engine.h"
#include <iostream>

Order::Order(std::string symbol, double price, int quantity) 
    : symbol(std::move(symbol)), price(price), quantity(quantity) {
}

Order::~Order() = default; // Remove side effects

std::string Order::getSymbol() const {
    return symbol;
}

double Order::getPrice() const {
    return price;
}

int Order::getQuantity() const {
    return quantity;
}

TradingEngine::TradingEngine() : internalState(std::make_unique<int>(0)) {
}

TradingEngine::~TradingEngine() = default;

void TradingEngine::processOrder(const Order& order) {
    // Use reference to avoid copying
    addOrder(order);
}

void TradingEngine::addOrder(const Order& order) {
    orders.push_back(order);
}

const std::vector<Order>& TradingEngine::getOrders() const {
    return orders; // Return const reference to avoid copying
}
```

**Updated trading_engine.h:**
```cpp
#pragma once
#include <string>
#include <vector>
#include <memory>

class Order {
public:
    Order(std::string symbol, double price, int quantity);
    ~Order() = default;
    
    std::string getSymbol() const;
    double getPrice() const;
    int getQuantity() const;
    
private:
    std::string symbol;
    double price;
    int quantity;
};

class TradingEngine {
public:
    TradingEngine();
    ~TradingEngine() = default;
    
    void processOrder(const Order& order);
    void addOrder(const Order& order);
    const std::vector<Order>& getOrders() const; // Return const reference
    
private:
    std::vector<Order> orders;
    std::unique_ptr<int> internalState;
};
```



### Exercise 2: Debugging Solutions

**Problems Identified and Fixed:**

1. **Memory Leaks**: The original code used raw pointers (`int* temp = new int(42)`) without proper cleanup, causing memory leaks that could accumulate over time in long-running HFT systems.

2. **Use After Free**: The code deleted a pointer and then immediately tried to dereference it (`delete temp; *temp = 100;`), which causes undefined behavior and potential crashes.

3. **Infinite Loop Risk**: The `addOrder` method had an infinite loop condition (`while (true)`) that could cause the system to hang when processing large numbers of orders.

4. **Missing Bounds Checking**: The code didn't validate the size of the orders vector before adding new elements, potentially leading to memory exhaustion.

5. **Unsafe Pointer Access**: The code accessed pointers without proper null checks, which could lead to segmentation faults.

**Fixed trading_engine.cpp:**
```cpp
void TradingEngine::processOrder(const Order& order) {
    // Use RAII instead of raw pointers
    auto temp = std::make_unique<int>(42);
    
    // Safe pointer access
    if (internalState && temp) {
        *internalState = *temp;
    }
    
    // No manual memory management needed
    addOrder(order);
}

void TradingEngine::addOrder(const Order& order) {
    // Add bounds checking
    if (orders.size() >= 1000) {
        throw std::runtime_error("Order limit exceeded");
    }
    
    orders.push_back(order);
}
```



## Conclusion

These exercises provide hands-on experience with modern C++ development tools and quality assurance practices. By completing them, you'll have a solid foundation for maintaining high-quality code in HFT development environments while balancing performance requirements with code reliability.

The key is to integrate these tools into your daily development workflow, ensuring that quality issues are caught early and consistently addressed across your codebase.
