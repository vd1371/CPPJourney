# Phase 1, Step 2: Modern C++ Fundamentals

## Overview

This step introduces the foundational modern C++ features that revolutionized the language starting with C++11. You'll learn how these features make C++ more expressive, safer, and easier to use while maintaining the performance characteristics that make it ideal for high-frequency trading systems.

## Learning Objectives

- Master C++11/14 core features: `auto`, `decltype`, and trailing return types
- Understand modern initialization syntax and initializer lists
- Implement lambda expressions with capture clauses and generic lambdas
- Utilize smart pointers for automatic memory management
- Apply these features to create more maintainable and efficient code

## Prerequisites

- Completion of Phase 1, Step 1 (Core Syntax and Language Basics)
- Basic understanding of C++ functions, pointers, and references
- Familiarity with basic memory management concepts

## 2.1 C++11/14 Core Features

### 2.1.1 The `auto` Keyword

The `auto` keyword enables automatic type deduction, eliminating the need to explicitly specify types when the compiler can infer them.

```cpp
// Traditional C++98 approach
std::vector<int>::iterator it = vec.begin();
std::map<std::string, double>::const_iterator cit = prices.find("AAPL");

// Modern C++11+ approach
auto it = vec.begin();                    // Type: std::vector<int>::iterator
auto cit = prices.find("AAPL");          // Type: std::map<std::string, double>::const_iterator
auto price = 42.99;                      // Type: double
auto name = "AAPL";                      // Type: const char*
```

**HFT Context**: In trading systems, `auto` reduces verbosity when working with complex iterator types and template instantiations, making code more readable during rapid development cycles.

**Best Practices**:
- Use `auto` when the type is obvious from the context
- Avoid `auto` when it reduces code clarity
- Be explicit about types when they're part of the interface contract

### 2.1.2 `decltype` and Type Deduction

`decltype` allows you to determine the type of an expression at compile time, which is crucial for template metaprogramming and generic code.

```cpp
template<typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

// C++14: Simplified return type deduction
template<typename T1, typename T2>
auto add(T1 a, T2 b) {
    return a + b;
}

// decltype in variable declarations
int x = 42;
decltype(x) y = x;           // y has the same type as x (int)
decltype((x)) z = x;         // z is int& (parentheses create a reference)
```

**HFT Application**: `decltype` is essential for creating generic trading algorithms that work with different numeric types (int, double, custom decimal types) while maintaining type safety.

### 2.1.3 Trailing Return Types

Trailing return types provide a way to specify return types after the parameter list, which is especially useful when the return type depends on the parameters.

```cpp
// Traditional approach - can be complex with templates
template<typename Container>
typename Container::value_type getFirst(const Container& c) {
    return c.empty() ? typename Container::value_type{} : c.front();
}

// Modern approach with trailing return type
template<typename Container>
auto getFirst(const Container& c) -> decltype(c.front()) {
    return c.empty() ? decltype(c.front()){} : c.front();
}

// C++14: Even simpler
template<typename Container>
auto getFirst(const Container& c) {
    return c.empty() ? decltype(c.front()){} : c.front();
}
```

## 2.2 Modern Initialization

### 2.2.1 Uniform Initialization

C++11 introduced uniform initialization syntax using braces `{}`, which provides consistent initialization across all types.

```cpp
// Traditional C++98 initialization
int x = 42;
int y(42);
std::vector<int> v;
v.push_back(1);
v.push_back(2);
v.push_back(3);

// Modern uniform initialization
int x{42};                    // Direct initialization
int y = {42};                 // Copy initialization
std::vector<int> v{1, 2, 3}; // List initialization
std::array<int, 3> arr{1, 2, 3}; // Array initialization

// Class initialization
struct Point {
    int x, y;
};
Point p{10, 20};             // Aggregate initialization
```

**HFT Benefits**: Uniform initialization prevents narrowing conversions and provides compile-time safety for critical financial calculations.

### 2.2.2 Initializer Lists

Initializer lists allow you to pass a list of values to constructors and functions, enabling more flexible object creation.

```cpp
#include <initializer_list>
#include <vector>

class OrderBook {
public:
    OrderBook(std::initializer_list<double> prices) 
        : price_levels(prices.begin(), prices.end()) {}
    
    void addLevels(std::initializer_list<double> new_prices) {
        price_levels.insert(price_levels.end(), new_prices.begin(), new_prices.end());
    }
    
private:
    std::vector<double> price_levels;
};

// Usage
OrderBook book{100.50, 100.75, 101.00, 101.25};
book.addLevels({99.75, 99.50});
```

**Trading System Application**: Initializer lists are perfect for setting up default price levels, order types, or configuration parameters in trading systems.

### 2.2.3 Preventing Narrowing Conversions

Uniform initialization prevents implicit narrowing conversions, which is crucial for financial applications where precision matters.

```cpp
// These would compile in C++98 but are dangerous
int narrow1 = 3.14;          // Truncates to 3
char narrow2 = 300;           // Undefined behavior on most systems

// Modern C++ prevents these
// int narrow1{3.14};        // Compilation error: narrowing conversion
// char narrow2{300};        // Compilation error: narrowing conversion

// Explicit conversions when needed
int safe1{static_cast<int>(3.14)};
char safe2{static_cast<char>(300)};
```

## 2.3 Lambda Expressions

### 2.3.1 Basic Lambda Syntax

Lambda expressions provide a way to create anonymous function objects inline, making code more concise and readable.

```cpp
// Traditional function object
struct PriceFilter {
    double threshold;
    PriceFilter(double t) : threshold(t) {}
    bool operator()(double price) const {
        return price > threshold;
    }
};

// Modern lambda equivalent
auto priceFilter = [threshold](double price) {
    return price > threshold;
};

// Usage
std::vector<double> prices{100.0, 150.0, 75.0, 200.0};
auto expensive = std::find_if(prices.begin(), prices.end(), 
    [](double p) { return p > 150.0; });
```

### 2.3.2 Capture Clauses

Lambda capture clauses determine how variables from the enclosing scope are accessed within the lambda.

```cpp
double threshold = 100.0;
std::string symbol = "AAPL";

// Value capture (default)
auto lambda1 = [threshold, symbol](double price) {
    return price > threshold && symbol == "AAPL";
};

// Reference capture
auto lambda2 = [&threshold, &symbol](double price) {
    threshold = price;  // Modifies original variable
    return price > 100.0;
};

// Mixed capture
auto lambda3 = [threshold, &symbol](double price) {
    // threshold is copied, symbol is referenced
    return price > threshold;
};

// Capture all by value
auto lambda4 = [=](double price) {
    return price > threshold;
};

// Capture all by reference
auto lambda5 = [&](double price) {
    return price > threshold;
};
```

**HFT Capture Guidelines**:
- Use value capture for small, simple types (int, double)
- Use reference capture for large objects or when you need to modify the original
- Be careful with reference capture to avoid dangling references
- Consider using `[=, &specific_var]` for mixed capture patterns

### 2.3.3 Generic Lambdas (C++14)

C++14 introduced generic lambdas that can work with any type, making them extremely powerful for template-like functionality.

```cpp
// Generic lambda for any numeric type
auto numericCompare = [](auto a, auto b) {
    return a < b;
};

// Usage with different types
int result1 = numericCompare(5, 10);           // true
double result2 = numericCompare(3.14, 2.71);   // false
long result3 = numericCompare(1000L, 500L);    // false

// Generic lambda in algorithms
std::vector<int> ints{3, 1, 4, 1, 5};
std::vector<double> doubles{3.14, 2.71, 1.41};

std::sort(ints.begin(), ints.end(), [](auto a, auto b) { return a < b; });
std::sort(doubles.begin(), doubles.end(), [](auto a, auto b) { return a < b; });
```

**Trading System Application**: Generic lambdas are perfect for creating reusable comparison functions that work with different price types, order types, or time representations.

## 2.4 Smart Pointers

### 2.4.1 `std::unique_ptr`

`unique_ptr` provides exclusive ownership semantics with automatic cleanup, eliminating the need for manual `delete` calls.

```cpp
#include <memory>
#include <iostream>

class Order {
public:
    Order(double price, int quantity) : price_(price), quantity_(quantity) {
        std::cout << "Order created: " << price_ << " x " << quantity_ << std::endl;
    }
    
    ~Order() {
        std::cout << "Order destroyed: " << price_ << " x " << quantity_ << std::endl;
    }
    
    double getPrice() const { return price_; }
    int getQuantity() const { return quantity_; }
    
private:
    double price_;
    int quantity_;
};

// Creating unique_ptr
auto order1 = std::make_unique<Order>(100.50, 100);
auto order2 = std::unique_ptr<Order>(new Order(101.00, 50));

// Transferring ownership
auto order3 = std::move(order1);  // order1 is now nullptr
// auto order4 = order3;          // Compilation error: can't copy unique_ptr

// Checking ownership
if (order1) {
    std::cout << "Order1 price: " << order1->getPrice() << std::endl;
} else {
    std::cout << "Order1 is null" << std::endl;
}
```

**HFT Memory Management**: `unique_ptr` is ideal for order objects, market data structures, and other resources that have single ownership in trading systems.

### 2.4.2 `std::shared_ptr`

`shared_ptr` enables shared ownership with reference counting, automatically cleaning up when the last reference is destroyed.

```cpp
#include <memory>
#include <vector>

class MarketData {
public:
    MarketData(const std::string& symbol, double price) 
        : symbol_(symbol), price_(price) {}
    
    const std::string& getSymbol() const { return symbol_; }
    double getPrice() const { return price_; }
    
private:
    std::string symbol_;
    double price_;
};

// Creating shared ownership
auto marketData = std::make_shared<MarketData>("AAPL", 150.25);

// Multiple references
std::vector<std::shared_ptr<MarketData>> dataSources;
dataSources.push_back(marketData);  // Reference count: 2
dataSources.push_back(marketData);  // Reference count: 3

// Checking reference count
std::cout << "Reference count: " << marketData.use_count() << std::endl;

// Automatic cleanup when all references are gone
dataSources.clear();  // Reference count: 1
marketData.reset();   // Reference count: 0, object destroyed
```

**Trading System Usage**: `shared_ptr` is perfect for market data that needs to be accessed by multiple components (order management, risk engine, reporting system).

### 2.4.3 `std::weak_ptr`

`weak_ptr` provides a non-owning reference to an object managed by `shared_ptr`, preventing circular references.

```cpp
#include <memory>
#include <iostream>

class Order {
public:
    Order(const std::string& id) : id_(id) {}
    
    void setParentOrder(std::weak_ptr<Order> parent) {
        parent_ = parent;
    }
    
    void process() {
        if (auto parent = parent_.lock()) {
            std::cout << "Processing order " << id_ 
                      << " with parent " << parent->id_ << std::endl;
        } else {
            std::cout << "Parent order no longer exists" << std::endl;
        }
    }
    
    std::string id_;
private:
    std::weak_ptr<Order> parent_;
};

// Usage
auto parentOrder = std::make_shared<Order>("PARENT-001");
auto childOrder = std::make_shared<Order>("CHILD-001");

childOrder->setParentOrder(parentOrder);

// Process orders
childOrder->process();  // Parent exists
parentOrder.reset();    // Parent destroyed
childOrder->process();  // Parent no longer exists
```

**HFT Application**: `weak_ptr` is essential for order hierarchies, parent-child relationships, and avoiding memory leaks in complex trading systems.

### 2.4.4 Smart Pointer Best Practices

```cpp
// Prefer make_* functions over direct new
auto ptr1 = std::make_unique<Order>(100.50, 100);  // Good
auto ptr2 = std::unique_ptr<Order>(new Order(100.50, 100));  // Avoid

// Use unique_ptr by default, shared_ptr only when needed
std::unique_ptr<Order> order;  // Single owner
std::shared_ptr<MarketData> data;  // Multiple owners

// Avoid raw pointers when possible
void processOrder(const std::unique_ptr<Order>& order);  // Good
void processOrder(Order* order);  // Avoid

// Use weak_ptr to break circular references
class Strategy {
    std::weak_ptr<RiskManager> risk_;  // Prevents circular reference
};
```

## 2.5 Performance Considerations

### 2.5.1 Lambda Performance

Lambdas have minimal runtime overhead and can be inlined by the compiler for optimal performance.

```cpp
// Compiler can inline this lambda for optimal performance
auto fastFilter = [](double price) { return price > 100.0; };

// Usage in hot path
for (const auto& price : prices) {
    if (fastFilter(price)) {
        // Process expensive price
    }
}
```

### 2.5.2 Smart Pointer Overhead

Smart pointers have minimal runtime overhead compared to raw pointers:

```cpp
// Performance comparison
void rawPointerAccess(Order* order) {
    auto price = order->getPrice();  // Direct access
}

void smartPointerAccess(const std::unique_ptr<Order>& order) {
    auto price = order->getPrice();  // Same performance as raw pointer
}
```

**HFT Performance Tip**: The performance cost of smart pointers is negligible compared to the safety and correctness benefits they provide.

## 2.6 Common Pitfalls and Solutions

### 2.6.1 Lambda Capture Issues

```cpp
// Problem: Capturing by reference in async context
std::thread([&localVar]() {
    // localVar might be destroyed when thread executes
}).detach();

// Solution: Capture by value or ensure lifetime
std::thread([localVar]() {
    // Safe: localVar is copied
}).detach();

// Or ensure proper lifetime management
auto sharedData = std::make_shared<Data>();
std::thread([sharedData]() {
    // Safe: shared ownership
}).detach();
```

### 2.6.2 Smart Pointer Misuse

```cpp
// Problem: Circular references with shared_ptr
class Node {
    std::shared_ptr<Node> next_;  // Circular reference
};

// Solution: Use weak_ptr for one direction
class Node {
    std::weak_ptr<Node> next_;  // Breaks circular reference
};
```

## Summary

Modern C++ fundamentals provide the building blocks for writing safer, more expressive, and more maintainable code. The features introduced in this step—`auto`, `decltype`, uniform initialization, lambda expressions, and smart pointers—form the foundation of modern C++ programming practices.

These features are particularly valuable in high-frequency trading systems where:
- Type safety prevents costly runtime errors
- Lambda expressions enable clean, inline algorithm customization
- Smart pointers eliminate memory leaks and provide exception safety
- Modern initialization syntax prevents narrowing conversions in financial calculations

In the next step, you'll build upon these fundamentals to explore advanced compilation techniques and tooling that will help you create production-ready trading systems.
