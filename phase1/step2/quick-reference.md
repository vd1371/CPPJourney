# Quick Reference: Modern C++ Fundamentals

## C++11/14 Core Features

### `auto` Keyword
```cpp
auto it = vec.begin();                    // Type deduction
auto price = 42.99;                      // double
auto name = "AAPL";                      // const char*
```
**HFT Tip**: Use `auto` for complex iterator types to reduce verbosity in trading algorithms.

### `decltype` and Type Deduction
```cpp
template<typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

// C++14: Simplified
template<typename T1, typename T2>
auto add(T1 a, T2 b) {
    return a + b;
}
```
**HFT Tip**: Essential for generic trading algorithms working with different numeric types.

### Trailing Return Types
```cpp
template<typename Container>
auto getFirst(const Container& c) -> decltype(c.front()) {
    return c.empty() ? decltype(c.front()){} : c.front();
}
```

## Modern Initialization

### Uniform Initialization
```cpp
int x{42};                               // Direct initialization
std::vector<int> v{1, 2, 3};            // List initialization
std::array<int, 3> arr{1, 2, 3};       // Array initialization
Point p{10, 20};                        // Aggregate initialization
```
**HFT Tip**: Prevents narrowing conversions in financial calculations.

### Initializer Lists
```cpp
class OrderBook {
public:
    OrderBook(std::initializer_list<double> prices) 
        : price_levels(prices.begin(), prices.end()) {}
};

OrderBook book{100.50, 100.75, 101.00, 101.25};
```
**HFT Tip**: Perfect for setting default price levels and configuration parameters.

## Lambda Expressions

### Basic Syntax
```cpp
auto priceFilter = [threshold](double price) {
    return price > threshold;
};

// Generic lambda (C++14)
auto numericCompare = [](auto a, auto b) {
    return a < b;
};
```

### Capture Clauses
```cpp
double threshold = 100.0;
std::string symbol = "AAPL";

auto lambda1 = [threshold, symbol](double price) { /* value capture */ };
auto lambda2 = [&threshold, &symbol](double price) { /* reference capture */ };
auto lambda3 = [=](double price) { /* capture all by value */ };
auto lambda4 = [&](double price) { /* capture all by reference */ };
auto lambda5 = [=, &specific_var](double price) { /* mixed capture */ };
```
**HFT Guidelines**:
- Value capture for small types (int, double)
- Reference capture for large objects or when modifying original
- Avoid dangling references in async contexts

## Smart Pointers

### `std::unique_ptr` (Exclusive Ownership)
```cpp
auto order = std::make_unique<Order>(100.50, 100);
auto order2 = std::move(order);          // Transfer ownership
if (order) { /* check ownership */ }     // order is now nullptr
```
**HFT Usage**: Order objects, market data structures with single ownership.

### `std::shared_ptr` (Shared Ownership)
```cpp
auto marketData = std::make_shared<MarketData>("AAPL", 150.25);
std::vector<std::shared_ptr<MarketData>> dataSources;
dataSources.push_back(marketData);       // Reference count: 2
std::cout << marketData.use_count();    // Check reference count
```
**HFT Usage**: Market data accessed by multiple components.

### `std::weak_ptr` (Non-owning Reference)
```cpp
class Order {
    std::weak_ptr<Order> parent_;
public:
    void process() {
        if (auto parent = parent_.lock()) {
            // Parent exists
        } else {
            // Parent destroyed
        }
    }
};
```
**HFT Usage**: Break circular references in order hierarchies.

## Best Practices

### Smart Pointer Guidelines
```cpp
// Prefer make_* functions
auto ptr1 = std::make_unique<Order>(100.50, 100);  // Good
auto ptr2 = std::unique_ptr<Order>(new Order(100.50, 100));  // Avoid

// Use unique_ptr by default, shared_ptr only when needed
std::unique_ptr<Order> order;            // Single owner
std::shared_ptr<MarketData> data;        // Multiple owners

// Avoid raw pointers
void processOrder(const std::unique_ptr<Order>& order);  // Good
void processOrder(Order* order);          // Avoid
```

### Lambda Best Practices
```cpp
// Capture by value in async contexts
std::thread([localVar]() { /* safe */ }).detach();

// Use generic lambdas for reusable comparisons
auto priceCompare = [](auto a, auto b) { return a < b; };
```

## Performance Notes

- **Lambdas**: Minimal overhead, can be inlined by compiler
- **Smart Pointers**: Negligible runtime cost vs. safety benefits
- **Uniform Initialization**: Compile-time safety with no runtime cost
- **auto/decltype**: Zero runtime overhead, compile-time only

## Common Pitfalls

1. **Lambda Capture Issues**: Avoid reference capture in async contexts
2. **Circular References**: Use `weak_ptr` to break cycles
3. **Narrowing Conversions**: Uniform initialization prevents these
4. **Dangling References**: Ensure proper lifetime management

## HFT-Specific Applications

- **Order Management**: `unique_ptr` for order ownership
- **Market Data**: `shared_ptr` for multi-component access
- **Algorithm Customization**: Lambdas for strategy parameters
- **Type Safety**: `auto` and `decltype` for generic algorithms
- **Memory Safety**: Smart pointers prevent leaks in critical systems
