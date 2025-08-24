# Solutions: Phase 1, Step 2 - Modern C++ Fundamentals

## Exercise 1: Smart Order Management System

### Solution with Issues Commented Out

```cpp
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Order {
public:
    Order(double price, int quantity, const std::string& symbol)
        : price_(price), quantity_(quantity), symbol_(symbol) {
        std::cout << "Order created: " << symbol_ << " " << quantity_ 
                  << " @ " << price_ << std::endl;
    }
    
    ~Order() {
        std::cout << "Order destroyed: " << symbol_ << " " << quantity_ 
                  << " @ " << price_ << std::endl;
    }
    
    double getPrice() const { return price_; }
    int getQuantity() const { return quantity_; }
    const std::string& getSymbol() const { return symbol_; }
    
private:
    double price_;
    int quantity_;
    std::string symbol_;
};

class OrderBook {
public:
    // Previous issue: Using raw pointers instead of smart pointers
    // void addOrder(Order* order) { orders_.push_back(order); }
    
    // Correct: Using unique_ptr for ownership
    void addOrder(std::unique_ptr<Order> order) {
        orders_.push_back(std::move(order));
    }
    
    // Previous issue: Manual memory management
    // ~OrderBook() {
    //     for (auto* order : orders_) delete order;
    // }
    
    // Correct: Automatic cleanup with smart pointers
    
    void processOrders(const std::string& symbol, 
                      std::function<bool(const Order&)> filter) {
        // Previous issue: Complex iterator type declaration
        // std::vector<std::unique_ptr<Order>>::iterator it = orders_.begin();
        
        // Correct: Using auto for type deduction
        auto it = std::remove_if(orders_.begin(), orders_.end(),
            [&symbol, &filter](const std::unique_ptr<Order>& order) {
                return order->getSymbol() == symbol && filter(*order);
            });
        
        orders_.erase(it, orders_.end());
    }
    
    size_t getOrderCount() const { return orders_.size(); }
    
private:
    std::vector<std::unique_ptr<Order>> orders_;
};

int main() {
    // Previous issue: Raw pointer creation
    // Order* order1 = new Order(100.50, 100, "AAPL");
    
    // Correct: Using make_unique
    auto order1 = std::make_unique<Order>(100.50, 100, "AAPL");
    auto order2 = std::make_unique<Order>(101.00, 50, "AAPL");
    auto order3 = std::make_unique<Order>(99.75, 200, "GOOGL");
    
    OrderBook book;
    
    // Previous issue: Passing raw pointers
    // book.addOrder(order1);
    
    // Correct: Moving unique_ptr
    book.addOrder(std::move(order1));
    book.addOrder(std::move(order2));
    book.addOrder(std::move(order3));
    
    std::cout << "Initial order count: " << book.getOrderCount() << std::endl;
    
    // Using lambda for filtering
    auto expensiveFilter = [](const Order& order) {
        return order.getPrice() > 100.0;
    };
    
    book.processOrders("AAPL", expensiveFilter);
    
    std::cout << "After processing: " << book.getOrderCount() << std::endl;
    
    return 0;
}
```

### Key Issues Fixed:
1. **Memory Management**: Replaced raw pointers with `std::unique_ptr`
2. **Type Deduction**: Used `auto` for complex iterator types
3. **Ownership Transfer**: Properly moved `unique_ptr` objects
4. **RAII**: Automatic cleanup with smart pointers

---

## Exercise 2: Market Data Filtering with Lambdas

### Solution with Issues Commented Out

```cpp
#include <memory>
#include <vector>
#include <functional>
#include <chrono>
#include <string>
#include <iostream>

struct MarketData {
    // Previous issue: Basic struct without proper initialization
    // double price;
    // int volume;
    // std::string timestamp;
    
    // Correct: Using uniform initialization and proper types
    double price{0.0};
    int volume{0};
    std::chrono::system_clock::time_point timestamp;
    std::string symbol;
    
    MarketData(double p, int v, const std::string& sym)
        : price{p}, volume{v}, symbol{sym}, 
          timestamp{std::chrono::system_clock::now()} {}
};

class DataFilter {
public:
    // Previous issue: Function pointer approach
    // typedef bool (*FilterFunc)(const MarketData&);
    // std::vector<FilterFunc> filters_;
    
    // Correct: Using lambda expressions and function objects
    using FilterFunc = std::function<bool(const MarketData&)>;
    std::vector<FilterFunc> filters_;
    
    // Previous issue: Template with explicit types
    // template<typename T>
    // void addFilter(bool (*filter)(const MarketData&, T), T value);
    
    // Correct: Generic lambda-based filtering
    template<typename T>
    void addFilter(T value, std::function<bool(const MarketData&, T)> filter) {
        // Previous issue: Manual capture
        // filters_.push_back([filter, value](const MarketData& data) {
        //     return filter(data, value);
        // });
        
        // Correct: Using capture by value for safety
        filters_.push_back([filter, value](const MarketData& data) {
            return filter(data, value);
        });
    }
    
    // Previous issue: Manual iteration
    // std::vector<std::shared_ptr<MarketData>> filterData(
    //     const std::vector<std::shared_ptr<MarketData>>& data) {
    //     std::vector<std::shared_ptr<MarketData>> result;
    //     for (size_t i = 0; i < data.size(); ++i) {
    //         bool passed = true;
    //         for (size_t j = 0; j < filters_.size(); ++j) {
    //             if (!filters_[j](*data[i])) {
    //                 passed = false;
    //                 break;
    //             }
    //         }
    //         if (passed) result.push_back(data[i]);
    //     }
    //     return result;
    // }
    
    // Correct: Using modern algorithms and lambdas
    std::vector<std::shared_ptr<MarketData>> filterData(
        const std::vector<std::shared_ptr<MarketData>>& data) {
        
        std::vector<std::shared_ptr<MarketData>> result;
        
        std::copy_if(data.begin(), data.end(), std::back_inserter(result),
            [this](const std::shared_ptr<MarketData>& item) {
                // Previous issue: Manual filter checking
                // for (auto filter : filters_) {
                //     if (!filter(*item)) return false;
                // }
                // return true;
                
                // Correct: Using std::all_of with lambda
                return std::all_of(filters_.begin(), filters_.end(),
                    [&item](const FilterFunc& filter) {
                        return filter(*item);
                    });
            });
        
        return result;
    }
};

int main() {
    // Previous issue: Raw pointer creation
    // MarketData* data1 = new MarketData(100.50, 1000, "AAPL");
    
    // Correct: Using make_shared for shared ownership
    auto data1 = std::make_shared<MarketData>(100.50, 1000, "AAPL");
    auto data2 = std::make_shared<MarketData>(101.00, 500, "AAPL");
    auto data3 = std::make_shared<MarketData>(99.75, 2000, "GOOGL");
    
    std::vector<std::shared_ptr<MarketData>> marketData{data1, data2, data3};
    
    DataFilter filter;
    
    // Previous issue: Function pointer approach
    // bool priceFilter(const MarketData& data, double threshold) {
    //     return data.price > threshold;
    // }
    // filter.addFilter(priceFilter, 100.0);
    
    // Correct: Using lambda expressions
    filter.addFilter(100.0, [](const MarketData& data, double threshold) {
        return data.price > threshold;
    });
    
    filter.addFilter(500, [](const MarketData& data, int minVolume) {
        return data.volume >= minVolume;
    });
    
    auto filteredData = filter.filterData(marketData);
    
    std::cout << "Filtered " << filteredData.size() << " data points" << std::endl;
    
    return 0;
}
```

### Key Issues Fixed:
1. **Lambda Usage**: Replaced function pointers with lambda expressions
2. **Modern Algorithms**: Used `std::copy_if` and `std::all_of`
3. **Smart Pointers**: Used `std::shared_ptr` for shared data
4. **Generic Lambdas**: Implemented template-based filtering

---

## Exercise 3: Advanced Order Matching Engine

### Solution with Issues Commented Out

```cpp
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <algorithm>

enum class OrderType { BUY, SELL };
enum class OrderStatus { PENDING, FILLED, CANCELLED };

class Order {
public:
    Order(const std::string& id, OrderType type, double price, int quantity)
        : id_{id}, type_{type}, price_{price}, quantity_{quantity}, 
          status_{OrderStatus::PENDING} {}
    
    // Previous issue: Using shared_ptr for parent (circular reference)
    // std::shared_ptr<Order> parent_;
    
    // Correct: Using weak_ptr to break circular references
    std::weak_ptr<Order> parent_;
    
    void setParentOrder(std::weak_ptr<Order> parent) {
        parent_ = parent;
    }
    
    void process() {
        // Previous issue: Direct access without checking
        // if (parent_) {
        //     std::cout << "Processing with parent: " << parent_->getId() << std::endl;
        // }
        
        // Correct: Safe access using lock()
        if (auto parent = parent_.lock()) {
            std::cout << "Processing order " << id_ 
                      << " with parent " << parent->getId() << std::endl;
        } else {
            std::cout << "Parent order no longer exists" << std::endl;
        }
    }
    
    const std::string& getId() const { return id_; }
    OrderType getType() const { return type_; }
    double getPrice() const { return price_; }
    int getQuantity() const { return quantity_; }
    OrderStatus getStatus() const { return status_; }
    
    void setStatus(OrderStatus status) { status_ = status; }
    
private:
    std::string id_;
    OrderType type_;
    double price_;
    int quantity_;
    OrderStatus status_;
};

class MatchingEngine {
public:
    // Previous issue: Manual memory management
    // std::vector<Order*> buyOrders_;
    // std::vector<Order*> sellOrders_;
    
    // Correct: Using unique_ptr for ownership
    std::vector<std::unique_ptr<Order>> buyOrders_;
    std::vector<std::unique_ptr<Order>> sellOrders_;
    
    void addOrder(std::unique_ptr<Order> order) {
        // Previous issue: Manual type checking
        // if (order->getType() == OrderType::BUY) {
        //     buyOrders_.push_back(order);
        // } else {
        //     sellOrders_.push_back(order);
        // }
        
        // Correct: Using lambda for cleaner logic
        auto addToContainer = [](auto& container, auto order) {
            container.push_back(std::move(order));
        };
        
        if (order->getType() == OrderType::BUY) {
            addToContainer(buyOrders_, std::move(order));
        } else {
            addToContainer(sellOrders_, std::move(order));
        }
    }
    
    void matchOrders() {
        // Previous issue: Manual matching logic
        // for (auto buyIt = buyOrders_.begin(); buyIt != buyOrders_.end(); ++buyIt) {
        //     for (auto sellIt = sellOrders_.begin(); sellIt != sellOrders_.end(); ++sellIt) {
        //         if ((*buyIt)->getPrice() >= (*sellIt)->getPrice()) {
        //             // Match found
        //         }
        //     }
        // }
        
        // Correct: Using modern algorithms and lambdas
        auto matchPredicate = [](const std::unique_ptr<Order>& buy,
                                const std::unique_ptr<Order>& sell) {
            return buy->getPrice() >= sell->getPrice() && 
                   buy->getStatus() == OrderStatus::PENDING &&
                   sell->getStatus() == OrderStatus::PENDING;
        };
        
        // Find matching orders
        for (auto& buyOrder : buyOrders_) {
            if (buyOrder->getStatus() != OrderStatus::PENDING) continue;
            
            auto sellMatch = std::find_if(sellOrders_.begin(), sellOrders_.end(),
                [&buyOrder](const std::unique_ptr<Order>& sell) {
                    return matchPredicate(buyOrder, sell);
                });
            
            if (sellMatch != sellOrders_.end()) {
                executeMatch(*buyOrder, **sellMatch);
            }
        }
    }
    
private:
    void executeMatch(Order& buyOrder, Order& sellOrder) {
        // Previous issue: No exception safety
        // buyOrder.setStatus(OrderStatus::FILLED);
        // sellOrder.setStatus(OrderStatus::FILLED);
        
        // Correct: Exception-safe status updates
        try {
            buyOrder.setStatus(OrderStatus::FILLED);
            sellOrder.setStatus(OrderStatus::FILLED);
            
            std::cout << "Match executed: " << buyOrder.getId() 
                      << " <-> " << sellOrder.getId() << std::endl;
        } catch (const std::exception& e) {
            // Rollback on error
            buyOrder.setStatus(OrderStatus::PENDING);
            sellOrder.setStatus(OrderStatus::PENDING);
            throw;
        }
    }
};

int main() {
    auto engine = std::make_unique<MatchingEngine>();
    
    // Create orders with proper ownership
    auto buyOrder = std::make_unique<Order>("BUY-001", OrderType::BUY, 100.50, 100);
    auto sellOrder = std::make_unique<Order>("SELL-001", OrderType::SELL, 100.00, 100);
    
    // Set parent-child relationship
    auto childOrder = std::make_unique<Order>("CHILD-001", OrderType::BUY, 100.25, 50);
    childOrder->setParentOrder(std::shared_ptr<Order>(buyOrder.get()));
    
    // Add orders to engine
    engine->addOrder(std::move(buyOrder));
    engine->addOrder(std::move(sellOrder));
    engine->addOrder(std::move(childOrder));
    
    // Process orders
    childOrder->process();
    
    // Match orders
    engine->matchOrders();
    
    return 0;
}
```

### Key Issues Fixed:
1. **Circular References**: Used `std::weak_ptr` instead of `std::shared_ptr`
2. **Exception Safety**: Implemented proper error handling and rollback
3. **Modern Algorithms**: Used `std::find_if` with lambdas
4. **Memory Management**: Proper `unique_ptr` usage throughout

---

## Exercise 4: Performance Benchmarking System

### Solution with Issues Commented Out

```cpp
#include <memory>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>

class BenchmarkRunner {
public:
    // Previous issue: Basic timing without statistics
    // void benchmarkSmartPtr() {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     // ... benchmark code ...
    //     auto end = std::chrono::high_resolution_clock::now();
    //     auto duration = end - start;
    //     std::cout << "Duration: " << duration.count() << std::endl;
    // }
    
    // Correct: Comprehensive benchmarking with statistics
    struct BenchmarkResult {
        std::vector<double> measurements;
        double mean;
        double stdDev;
        double min;
        double max;
    };
    
    BenchmarkResult benchmarkSmartPtr(size_t iterations) {
        std::vector<double> measurements;
        measurements.reserve(iterations);
        
        for (size_t i = 0; i < iterations; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            
            // Benchmark smart pointer operations
            std::vector<std::unique_ptr<int>> smartPtrs;
            for (int j = 0; j < 1000; ++j) {
                smartPtrs.push_back(std::make_unique<int>(j));
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double, std::micro>(end - start);
            measurements.push_back(duration.count());
        }
        
        return calculateStatistics(measurements);
    }
    
    BenchmarkResult benchmarkRawPtr(size_t iterations) {
        std::vector<double> measurements;
        measurements.reserve(iterations);
        
        for (size_t i = 0; i < iterations; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            
            // Previous issue: Memory leak potential
            // std::vector<int*> rawPtrs;
            // for (int j = 0; j < 1000; ++j) {
            //     rawPtrs.push_back(new int(j));
            // }
            
            // Correct: Proper cleanup
            std::vector<int*> rawPtrs;
            for (int j = 0; j < 1000; ++j) {
                rawPtrs.push_back(new int(j));
            }
            
            // Cleanup to prevent memory leaks
            for (auto ptr : rawPtrs) {
                delete ptr;
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double, std::micro>(end - start);
            measurements.push_back(duration.count());
        }
        
        return calculateStatistics(measurements);
    }
    
    BenchmarkResult benchmarkLambda(size_t iterations) {
        std::vector<double> measurements;
        measurements.reserve(iterations);
        
        std::vector<int> data(10000);
        std::iota(data.begin(), data.end(), 0);
        
        for (size_t i = 0; i < iterations; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            
            // Previous issue: Manual loop
            // std::vector<int> result;
            // for (int val : data) {
            //     if (val % 2 == 0) result.push_back(val);
            // }
            
            // Correct: Using lambda with algorithm
            std::vector<int> result;
            std::copy_if(data.begin(), data.end(), std::back_inserter(result),
                [](int val) { return val % 2 == 0; });
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double, std::micro>(end - start);
            measurements.push_back(duration.count());
        }
        
        return calculateStatistics(measurements);
    }
    
    void compareBenchmarks(size_t iterations = 100) {
        std::cout << "Running benchmarks with " << iterations << " iterations...\n\n";
        
        auto smartPtrResult = benchmarkSmartPtr(iterations);
        auto rawPtrResult = benchmarkRawPtr(iterations);
        auto lambdaResult = benchmarkLambda(iterations);
        
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Smart Pointer Benchmark:\n";
        printResult(smartPtrResult);
        
        std::cout << "\nRaw Pointer Benchmark:\n";
        printResult(rawPtrResult);
        
        std::cout << "\nLambda Benchmark:\n";
        printResult(lambdaResult);
        
        // Performance comparison
        std::cout << "\nPerformance Analysis:\n";
        double smartPtrOverhead = (smartPtrResult.mean - rawPtrResult.mean) / rawPtrResult.mean * 100;
        std::cout << "Smart pointer overhead: " << smartPtrOverhead << "%\n";
        
        double lambdaEfficiency = (rawPtrResult.mean - lambdaResult.mean) / rawPtrResult.mean * 100;
        std::cout << "Lambda efficiency gain: " << lambdaEfficiency << "%\n";
    }
    
private:
    BenchmarkResult calculateStatistics(const std::vector<double>& measurements) {
        BenchmarkResult result;
        result.measurements = measurements;
        
        // Previous issue: Manual calculation
        // double sum = 0;
        // for (double val : measurements) sum += val;
        // result.mean = sum / measurements.size();
        
        // Correct: Using std::accumulate
        result.mean = std::accumulate(measurements.begin(), measurements.end(), 0.0) / measurements.size();
        
        // Calculate standard deviation
        double variance = 0.0;
        for (double val : measurements) {
            variance += (val - result.mean) * (val - result.mean);
        }
        result.stdDev = std::sqrt(variance / measurements.size());
        
        // Find min/max
        auto [minIt, maxIt] = std::minmax_element(measurements.begin(), measurements.end());
        result.min = *minIt;
        result.max = *maxIt;
        
        return result;
    }
    
    void printResult(const BenchmarkResult& result) {
        std::cout << "  Mean: " << result.mean << " μs\n";
        std::cout << "  Std Dev: " << result.stdDev << " μs\n";
        std::cout << "  Min: " << result.min << " μs\n";
        std::cout << "  Max: " << result.max << " μs\n";
    }
};

int main() {
    BenchmarkRunner runner;
    
    // Run comprehensive benchmarks
    runner.compareBenchmarks(100);
    
    return 0;
}
```

### Key Issues Fixed:
1. **Memory Leaks**: Proper cleanup in raw pointer benchmark
2. **Statistics**: Comprehensive statistical analysis
3. **Modern Algorithms**: Used `std::copy_if` with lambdas
4. **Performance Measurement**: Proper timing and comparison

---

## Exercise 5: Configuration Management System

### Solution with Issues Commented Out

```cpp
#include <memory>
#include <variant>
#include <string>
#include <map>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

// Previous issue: Using union (C-style)
// union ConfigValue {
//     int intVal;
//     double doubleVal;
//     char* stringVal;
// };

// Correct: Using std::variant for type safety
using ConfigValue = std::variant<int, double, std::string, bool>;

class Configuration {
public:
    // Previous issue: Manual validation
    // void setValue(const std::string& key, int value) {
    //     if (value < 0) throw std::invalid_argument("Value must be positive");
    //     config_[key] = value;
    // }
    
    // Correct: Lambda-based validation
    using Validator = std::function<bool(const ConfigValue&)>;
    
    void setValue(const std::string& key, const ConfigValue& value, 
                  Validator validator = nullptr) {
        if (validator && !validator(value)) {
            throw std::invalid_argument("Validation failed for key: " + key);
        }
        config_[key] = value;
    }
    
    // Previous issue: Type-unsafe access
    // int getIntValue(const std::string& key) {
    //     return config_[key]; // Unsafe cast
    // }
    
    // Correct: Type-safe access with std::visit
    template<typename T>
    T getValue(const std::string& key) const {
        auto it = config_.find(key);
        if (it == config_.end()) {
            throw std::out_of_range("Key not found: " + key);
        }
        
        try {
            return std::get<T>(it->second);
        } catch (const std::bad_variant_access&) {
            throw std::runtime_error("Type mismatch for key: " + key);
        }
    }
    
    // Previous issue: Manual initialization
    // Configuration() {
    //     config_["max_orders"] = 1000;
    //     config_["risk_limit"] = 100000.0;
    //     config_["enable_logging"] = true;
    // }
    
    // Correct: Using initializer list
    Configuration(std::initializer_list<std::pair<std::string, ConfigValue>> init) {
        for (const auto& [key, value] : init) {
            config_[key] = value;
        }
    }
    
    // Builder pattern with modern C++ syntax
    class Builder {
    public:
        Builder& addInt(const std::string& key, int value, Validator validator = nullptr) {
            if (validator && !validator(ConfigValue{value})) {
                throw std::invalid_argument("Invalid int value for key: " + key);
            }
            config_[key] = value;
            return *this;
        }
        
        Builder& addDouble(const std::string& key, double value, Validator validator = nullptr) {
            if (validator && !validator(ConfigValue{value})) {
                throw std::invalid_argument("Invalid double value for key: " + key);
            }
            config_[key] = value;
            return *this;
        }
        
        Builder& addString(const std::string& key, const std::string& value, Validator validator = nullptr) {
            if (validator && !validator(ConfigValue{value})) {
                throw std::invalid_argument("Invalid string value for key: " + key);
            }
            config_[key] = value;
            return *this;
        }
        
        Builder& addBool(const std::string& key, bool value, Validator validator = nullptr) {
            if (validator && !validator(ConfigValue{value})) {
                throw std::invalid_argument("Invalid bool value for key: " + key);
            }
            config_[key] = value;
            return *this;
        }
        
        Configuration build() const {
            return Configuration(config_);
        }
        
    private:
        std::map<std::string, ConfigValue> config_;
    };
    
    static Builder builder() {
        return Builder{};
    }
    
    void printConfig() const {
        std::cout << "Configuration:\n";
        for (const auto& [key, value] : config_) {
            std::cout << "  " << key << ": ";
            std::visit([](const auto& v) { std::cout << v; }, value);
            std::cout << "\n";
        }
    }
    
private:
    std::map<std::string, ConfigValue> config_;
    
    // Private constructor for builder pattern
    Configuration(const std::map<std::string, ConfigValue>& config) : config_(config) {}
};

int main() {
    try {
        // Previous issue: Manual configuration setup
        // Configuration config;
        // config.setValue("max_orders", 1000);
        // config.setValue("risk_limit", 100000.0);
        
        // Correct: Using initializer list
        Configuration config{
            {"max_orders", 1000},
            {"risk_limit", 100000.0},
            {"enable_logging", true},
            {"strategy_name", std::string{"Momentum"}}
        };
        
        // Using builder pattern
        auto config2 = Configuration::builder()
            .addInt("max_orders", 2000, [](const ConfigValue& v) {
                return std::get<int>(v) > 0 && std::get<int>(v) <= 10000;
            })
            .addDouble("risk_limit", 500000.0, [](const ConfigValue& v) {
                return std::get<double>(v) > 0;
            })
            .addString("strategy_name", "Arbitrage")
            .addBool("enable_logging", true)
            .build();
        
        // Print configurations
        std::cout << "Config 1:\n";
        config.printConfig();
        
        std::cout << "\nConfig 2:\n";
        config2.printConfig();
        
        // Access values with type safety
        auto maxOrders = config.getValue<int>("max_orders");
        auto riskLimit = config.getValue<double>("risk_limit");
        auto strategyName = config.getValue<std::string>("strategy_name");
        
        std::cout << "\nAccessed values:\n";
        std::cout << "Max orders: " << maxOrders << "\n";
        std::cout << "Risk limit: " << riskLimit << "\n";
        std::cout << "Strategy: " << strategyName << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Configuration error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
```

### Key Issues Fixed:
1. **Type Safety**: Replaced union with `std::variant`
2. **Validation**: Lambda-based validation system
3. **Initialization**: Modern initializer list usage
4. **Builder Pattern**: Clean, modern implementation
5. **Exception Safety**: Proper error handling throughout

---

## Summary of Common Issues and Solutions

### 1. Memory Management
- **Issue**: Manual `new`/`delete` leading to memory leaks
- **Solution**: Use smart pointers (`unique_ptr`, `shared_ptr`, `weak_ptr`)

### 2. Type Safety
- **Issue**: Unsafe type casting and unions
- **Solution**: Use `std::variant`, `auto`, and `decltype`

### 3. Modern Algorithms
- **Issue**: Manual loops and iterations
- **Solution**: Use STL algorithms with lambda expressions

### 4. Exception Safety
- **Issue**: Poor error handling and resource cleanup
- **Solution**: Implement RAII and proper exception handling

### 5. Performance
- **Issue**: Inefficient data structures and algorithms
- **Solution**: Use modern C++ features and benchmark performance

These solutions demonstrate the power of modern C++ features in creating safe, efficient, and maintainable code suitable for high-frequency trading systems.
