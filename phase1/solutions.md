# Solutions: Core Syntax and Language Basics

## Overview
This document provides solutions to the exercises along with explanations of common problems and their fixes. Each solution demonstrates modern C++ best practices and HFT-specific optimizations.

---

## Exercise 1: Basic Market Data Structure

### Solution
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

struct MarketData {
    std::string symbol;
    double price;
    int volume;
    uint64_t timestamp;
    
    // Constructor with validation
    MarketData(const std::string& sym, double p, int vol, uint64_t ts)
        : symbol(sym), price(p), volume(vol), timestamp(ts) {
        // Validate symbol length
        if (symbol.length() > 8) {
            symbol = symbol.substr(0, 8);
        }
    }
};

// Calculate average price using const reference for efficiency
double calculate_average_price(const std::vector<MarketData>& market_data) {
    if (market_data.empty()) {
        return 0.0;
    }
    
    // Use std::accumulate for efficient summation
    double total = std::accumulate(market_data.begin(), market_data.end(), 0.0,
        [](double sum, const MarketData& data) { return sum + data.price; });
    
    return total / market_data.size();
}

// Find highest volume trade
const MarketData* find_highest_volume(const std::vector<MarketData>& market_data) {
    if (market_data.empty()) {
        return nullptr;
    }
    
    // Use std::max_element with custom comparator
    return &(*std::max_element(market_data.begin(), market_data.end(),
        [](const MarketData& a, const MarketData& b) {
            return a.volume < b.volume;
        }));
}

int main() {
    // Create sample market data using modern C++ initialization
    std::vector<MarketData> data = {
        {"AAPL", 150.25, 1000, 1640995200000ULL},
        {"GOOGL", 2800.50, 500, 1640995200001ULL},
        {"MSFT", 320.75, 2000, 1640995200002ULL}
    };
    
    // Calculate and display average price
    double avg_price = calculate_average_price(data);
    std::cout << "Average price: $" << std::fixed << std::setprecision(2) 
              << avg_price << '\n';
    
    // Find and display highest volume trade
    const MarketData* highest_vol = find_highest_volume(data);
    if (highest_vol) {
        std::cout << "Highest volume: " << highest_vol->symbol 
                  << " with " << highest_vol->volume << " shares\n";
    }
    
    return 0;
}
```

### Common Problems and Fixes

#### Problem 1: Inefficient Parameter Passing
```cpp
// WRONG: Copying large vectors
double calculate_average_price(std::vector<MarketData> market_data) {
    // This creates a copy of the entire vector!
}

// CORRECT: Use const reference
double calculate_average_price(const std::vector<MarketData>& market_data) {
    // No copying, just reference to original data
}
```

#### Problem 2: Missing Null Checks
```cpp
// WRONG: No validation for empty containers
double calculate_average_price(const std::vector<MarketData>& market_data) {
    double total = 0.0;
    for (const auto& data : market_data) {
        total += data.price;
    }
    return total / market_data.size(); // Crashes if vector is empty!
}

// CORRECT: Check for empty container
double calculate_average_price(const std::vector<MarketData>& market_data) {
    if (market_data.empty()) {
        return 0.0; // Safe default value
    }
    // ... rest of implementation
}
```

#### Problem 3: Inefficient Loops
```cpp
// WRONG: Traditional for loop with index
for (size_t i = 0; i < market_data.size(); ++i) {
    total += market_data[i].price;
}

// CORRECT: Range-based for loop (C++11)
for (const auto& data : market_data) {
    total += data.price;
}

// EVEN BETTER: Use STL algorithms
double total = std::accumulate(market_data.begin(), market_data.end(), 0.0,
    [](double sum, const MarketData& data) { return sum + data.price; });
```

---

## Exercise 2: Order Processing System

### Solution
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

struct Order {
    int order_id;
    std::string symbol;
    int quantity;
    double price;
    char order_type;
    
    // Constructor with validation
    Order(int id, const std::string& sym, int qty, double prc, char type)
        : order_id(id), symbol(sym), quantity(qty), price(prc), order_type(type) {
        validate_order();
    }
    
private:
    void validate_order() {
        if (price < 0.0) {
            throw std::invalid_argument("Price must be positive");
        }
        if (quantity < 1 || quantity > 10000) {
            throw std::invalid_argument("Quantity must be between 1 and 10000");
        }
        if (symbol.length() < 1 || symbol.length() > 8) {
            throw std::invalid_argument("Symbol length must be between 1 and 8");
        }
        if (order_type != 'M' && order_type != 'L' && order_type != 'S') {
            throw std::invalid_argument("Invalid order type");
        }
    }
};

// Validation functions
bool is_valid_price(double price) {
    return price > 0.0;
}

bool is_valid_quantity(int quantity) {
    return quantity >= 1 && quantity <= 10000;
}

bool is_valid_symbol(const std::string& symbol) {
    return symbol.length() >= 1 && symbol.length() <= 8;
}

// Order processing with switch statement
void process_order(const Order& order) {
    std::cout << "Processing order " << order.order_id << " for " 
              << order.symbol << '\n';
    
    switch (order.order_type) {
        case 'M':
            std::cout << "Market order - executing immediately\n";
            break;
        case 'L':
            std::cout << "Limit order - waiting for price " << order.price << '\n';
            break;
        case 'S':
            std::cout << "Stop order - will trigger at " << order.price << '\n';
            break;
        default:
            std::cout << "Unknown order type\n";
            break;
    }
}

// Function overloading for different order types
void process_order(int order_id, const std::string& symbol) {
    std::cout << "Processing order " << order_id << " for " << symbol << '\n';
}

void process_order(int order_id, const std::string& symbol, double price) {
    std::cout << "Processing order " << order_id << " for " << symbol 
              << " at price " << price << '\n';
}

int main() {
    try {
        // Create test orders
        std::vector<Order> orders = {
            {1, "AAPL", 100, 150.25, 'L'},
            {2, "GOOGL", 50, 0.0, 'M'},
            {3, "MSFT", 200, 320.75, 'S'}
        };
        
        // Process each order
        for (const auto& order : orders) {
            process_order(order);
            std::cout << "---\n";
        }
        
        // Test function overloading
        process_order(4, "TSLA");
        process_order(5, "TSLA", 850.50);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    
    return 0;
}
```

### Common Problems and Fixes

#### Problem 1: Missing Break Statements in Switch
```cpp
// WRONG: Missing break statements cause fall-through
switch (order.order_type) {
    case 'M':
        std::cout << "Market order\n";
    case 'L':  // This will execute even for market orders!
        std::cout << "Limit order\n";
        break;
}

// CORRECT: Always include break statements
switch (order.order_type) {
    case 'M':
        std::cout << "Market order\n";
        break;
    case 'L':
        std::cout << "Limit order\n";
        break;
}
```

#### Problem 2: Inefficient String Passing
```cpp
// WRONG: Passing string by value (creates copy)
void process_order(int id, std::string symbol) {
    // symbol is copied here
}

// CORRECT: Pass by const reference
void process_order(int id, const std::string& symbol) {
    // No copying, just reference
}
```

#### Problem 3: Poor Error Handling
```cpp
// WRONG: No error handling
void validate_order() {
    if (price < 0.0) {
        // Just return or print error - caller doesn't know about failure
        return;
    }
}

// CORRECT: Use exceptions for error handling
void validate_order() {
    if (price < 0.0) {
        throw std::invalid_argument("Price must be positive");
    }
}
```

---

## Exercise 3: Price Calculator with Pointers and References

### Solution
```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

class PriceCalculator {
public:
    // Inline function for performance-critical calculations
    inline double calculate_spread(double bid, double ask) {
        if (bid <= 0.0 || ask <= 0.0) {
            throw std::invalid_argument("Prices must be positive");
        }
        if (bid >= ask) {
            throw std::invalid_argument("Bid must be less than ask");
        }
        return ask - bid;
    }
    
    // Calculate VWAP using const references for efficiency
    double calculate_vwap(const std::vector<double>& prices, 
                         const std::vector<int>& volumes) {
        if (prices.size() != volumes.size() || prices.empty()) {
            throw std::invalid_argument("Invalid input data");
        }
        
        double total_value = 0.0;
        int total_volume = 0;
        
        // Use range-based for loop for cleaner code
        for (size_t i = 0; i < prices.size(); ++i) {
            if (prices[i] <= 0.0 || volumes[i] <= 0) {
                throw std::invalid_argument("Invalid price or volume");
            }
            total_value += prices[i] * volumes[i];
            total_volume += volumes[i];
        }
        
        return total_volume > 0 ? total_value / total_volume : 0.0;
    }
    
    // Calculate price change percentage
    double calculate_change_percent(double old_price, double new_price) {
        if (old_price <= 0.0) {
            throw std::invalid_argument("Old price must be positive");
        }
        
        return ((new_price - old_price) / old_price) * 100.0;
    }
    
    // Process prices using pointer arithmetic
    void process_prices(double* prices, int count) {
        if (!prices || count <= 0) {
            throw std::invalid_argument("Invalid pointer or count");
        }
        
        double* end = prices + count;
        double* current = prices;
        
        // Use pointer arithmetic for efficient iteration
        while (current != end) {
            if (*current <= 0.0) {
                throw std::invalid_argument("Invalid price encountered");
            }
            // Process price (e.g., apply commission, round to tick size)
            *current = std::round(*current * 100.0) / 100.0; // Round to 2 decimal places
            ++current;
        }
    }
    
    // Overloaded version for optional parameters using pointers
    double calculate_spread_with_commission(double bid, double ask, 
                                          double* commission = nullptr) {
        double spread = calculate_spread(bid, ask);
        
        if (commission) {
            spread -= *commission; // Apply commission if provided
        }
        
        return std::max(spread, 0.0); // Ensure non-negative spread
    }
};

int main() {
    try {
        PriceCalculator calc;
        
        // Test spread calculation
        double spread = calc.calculate_spread(100.0, 100.05);
        std::cout << "Spread: $" << std::fixed << std::setprecision(2) 
                  << spread << '\n';
        
        // Test VWAP calculation
        std::vector<double> prices = {100.0, 101.0, 102.0};
        std::vector<int> volumes = {100, 200, 150};
        double vwap = calc.calculate_vwap(prices, volumes);
        std::cout << "VWAP: $" << vwap << '\n';
        
        // Test price change calculation
        double change = calc.calculate_change_percent(100.0, 105.0);
        std::cout << "Price change: " << std::fixed << std::setprecision(2) 
                  << change << "%\n";
        
        // Test pointer arithmetic
        double price_array[] = {100.123, 101.456, 102.789};
        calc.process_prices(price_array, 3);
        std::cout << "Processed prices: ";
        for (double price : price_array) {
            std::cout << price << " ";
        }
        std::cout << '\n';
        
        // Test optional commission parameter
        double commission = 0.01;
        double spread_with_commission = calc.calculate_spread_with_commission(
            100.0, 100.05, &commission);
        std::cout << "Spread with commission: $" << spread_with_commission << '\n';
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    
    return 0;
}
```

### Common Problems and Fixes

#### Problem 1: Incorrect Use of Pointers vs References
```cpp
// WRONG: Using pointer when reference is more appropriate
void calculate_vwap(std::vector<double>* prices, std::vector<int>* volumes) {
    // Need to check for null pointers everywhere
    if (!prices || !volumes) return;
    // ... implementation
}

// CORRECT: Use const references for non-nullable parameters
void calculate_vwap(const std::vector<double>& prices, 
                   const std::vector<int>& volumes) {
    // No null checks needed, guaranteed to be valid
    // ... implementation
}
```

#### Problem 2: Missing Null Pointer Checks
```cpp
// WRONG: No validation of pointer parameters
void process_prices(double* prices, int count) {
    // This will crash if prices is nullptr!
    for (int i = 0; i < count; ++i) {
        prices[i] = std::round(prices[i] * 100.0) / 100.0;
    }
}

// CORRECT: Always validate pointer parameters
void process_prices(double* prices, int count) {
    if (!prices || count <= 0) {
        throw std::invalid_argument("Invalid pointer or count");
    }
    // ... safe implementation
}
```

#### Problem 3: Inefficient Parameter Passing
```cpp
// WRONG: Passing large vectors by value
double calculate_vwap(std::vector<double> prices, std::vector<int> volumes) {
    // Creates copies of both vectors!
}

// CORRECT: Pass by const reference
double calculate_vwap(const std::vector<double>& prices, 
                     const std::vector<int>& volumes) {
    // No copying, just references
}
```

---

## Exercise 4: Market Data Logger

### Solution
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <filesystem>

class MarketLogger {
private:
    std::string log_directory;
    
public:
    // Constructor with RAII
    MarketLogger(const std::string& directory) : log_directory(directory) {
        // Create directory if it doesn't exist
        std::filesystem::create_directories(log_directory);
    }
    
    // Destructor (RAII cleanup)
    ~MarketLogger() = default;
    
    // Log market data to CSV with RAII file handling
    bool log_market_data(const std::string& symbol, double price, 
                        int volume, uint64_t timestamp) {
        std::string filename = log_directory + "/market_data.csv";
        
        // Use RAII: file automatically closes when out of scope
        std::ofstream file(filename, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Failed to open market data log file\n";
            return false;
        }
        
        // Format: Symbol,Price,Volume,Timestamp
        file << symbol << "," 
             << std::fixed << std::setprecision(2) << price << ","
             << volume << ","
             << timestamp << "\n";
        
        return file.good();
    }
    
    // Log order activity with timestamp
    bool log_order(int order_id, const std::string& symbol, 
                  int quantity, double price, char order_type) {
        std::string filename = log_directory + "/orders.log";
        
        std::ofstream file(filename, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Failed to open order log file\n";
            return false;
        }
        
        uint64_t timestamp = get_current_timestamp();
        
        // Format: Timestamp,OrderID,Symbol,Quantity,Price,Type
        file << timestamp << ","
             << order_id << ","
             << symbol << ","
             << quantity << ","
             << std::fixed << std::setprecision(2) << price << ","
             << order_type << "\n";
        
        return file.good();
    }
    
    // Read and parse log entries with exception safety
    std::vector<std::string> read_log_entries(const std::string& filename) {
        std::vector<std::string> entries;
        std::string full_path = log_directory + "/" + filename;
        
        std::ifstream file(full_path);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open log file: " + full_path);
        }
        
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                entries.push_back(line);
            }
        }
        
        return entries;
    }
    
    // Get current timestamp in milliseconds
    uint64_t get_current_timestamp() {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
    
    // Parse CSV line safely
    std::vector<std::string> parse_csv_line(const std::string& line) {
        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string field;
        
        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }
        
        return fields;
    }
    
    // Get log statistics
    struct LogStats {
        size_t total_entries;
        size_t market_data_entries;
        size_t order_entries;
    };
    
    LogStats get_log_statistics() {
        LogStats stats = {0, 0, 0};
        
        try {
            auto market_entries = read_log_entries("market_data.csv");
            auto order_entries = read_log_entries("orders.log");
            
            stats.market_data_entries = market_entries.size();
            stats.order_entries = order_entries.size();
            stats.total_entries = stats.market_data_entries + stats.order_entries;
            
        } catch (const std::exception& e) {
            std::cerr << "Error reading log statistics: " << e.what() << '\n';
        }
        
        return stats;
    }
};

int main() {
    try {
        // Create logger with RAII
        MarketLogger logger("./logs");
        
        // Log some market data
        logger.log_market_data("AAPL", 150.25, 1000, 1640995200000ULL);
        logger.log_market_data("GOOGL", 2800.50, 500, 1640995200001ULL);
        
        // Log some orders
        logger.log_order(1, "AAPL", 100, 150.25, 'L');
        logger.log_order(2, "GOOGL", 50, 2800.50, 'M');
        
        // Read and display log entries
        std::cout << "Market data entries:\n";
        auto market_entries = logger.read_log_entries("market_data.csv");
        for (const auto& entry : market_entries) {
            std::cout << entry << '\n';
        }
        
        std::cout << "\nOrder entries:\n";
        auto order_entries = logger.read_log_entries("orders.log");
        for (const auto& entry : order_entries) {
            std::cout << entry << '\n';
        }
        
        // Display statistics
        auto stats = logger.get_log_statistics();
        std::cout << "\nLog Statistics:\n";
        std::cout << "Total entries: " << stats.total_entries << '\n';
        std::cout << "Market data entries: " << stats.market_data_entries << '\n';
        std::cout << "Order entries: " << stats.order_entries << '\n';
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    
    return 0;
}
```

### Common Problems and Fixes

#### Problem 1: Manual File Management
```cpp
// WRONG: Manual file handling without RAII
bool log_market_data(const std::string& symbol, double price, 
                    int volume, uint64_t timestamp) {
    std::ofstream* file = new std::ofstream("data.csv", std::ios::app);
    if (!file->is_open()) {
        delete file;  // Manual cleanup
        return false;
    }
    
    *file << symbol << "," << price << "," << volume << "," << timestamp << "\n";
    
    bool success = file->good();
    file->close();
    delete file;  // Manual cleanup
    return success;
}

// CORRECT: Use RAII - file automatically closes
bool log_market_data(const std::string& symbol, double price, 
                    int volume, uint64_t timestamp) {
    std::ofstream file("data.csv", std::ios::app);
    if (!file.is_open()) {
        return false;
    }
    
    file << symbol << "," << price << "," << volume << "," << timestamp << "\n";
    
    return file.good();
    // File automatically closes when function exits
}
```

#### Problem 2: Poor Exception Safety
```cpp
// WRONG: No exception handling
std::vector<std::string> read_log_entries(const std::string& filename) {
    std::vector<std::string> entries;
    std::ifstream file(filename);
    
    std::string line;
    while (std::getline(file, line)) {
        entries.push_back(line);  // Could throw if memory allocation fails
    }
    
    return entries;  // Could throw during copy
}

// CORRECT: Exception-safe implementation
std::vector<std::string> read_log_entries(const std::string& filename) {
    std::vector<std::string> entries;
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    try {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                entries.push_back(line);
            }
        }
    } catch (...) {
        // Clean up and rethrow
        file.close();
        throw;
    }
    
    return entries;
}
```

#### Problem 3: Inefficient String Concatenation
```cpp
// WRONG: Multiple string concatenations
std::string full_path = log_directory + "/" + filename;

// CORRECT: Use filesystem path or single concatenation
std::filesystem::path full_path = log_directory / filename;
// Or
std::string full_path = log_directory + "/" + filename;  // Single operation
```

---

## Exercise 5: High-Performance Order Book

### Solution
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

// Cache-friendly order level structure
struct OrderLevel {
    double price;
    int total_quantity;
    int order_count;
    
    // Constructor for efficient initialization
    OrderLevel(double p = 0.0, int qty = 0, int count = 0)
        : price(p), total_quantity(qty), order_count(count) {}
};

class OrderBook {
private:
    // Use maps for efficient price level management
    // Bids: highest price first (descending)
    // Asks: lowest price first (ascending)
    std::map<double, OrderLevel, std::greater<double>> bids;
    std::map<double, OrderLevel, std::less<double>> asks;
    
    // Performance tracking
    mutable uint64_t operation_count = 0;
    
public:
    OrderBook() = default;
    ~OrderBook() = default;
    
    // Add order to book with performance optimization
    void add_order(double price, int quantity, bool is_bid) {
        if (price <= 0.0 || quantity <= 0) {
            throw std::invalid_argument("Invalid price or quantity");
        }
        
        auto& book = is_bid ? bids : asks;
        auto it = book.find(price);
        
        if (it != book.end()) {
            // Update existing level
            it->second.total_quantity += quantity;
            it->second.order_count++;
        } else {
            // Create new level
            book.emplace(price, OrderLevel(price, quantity, 1));
        }
        
        operation_count++;
    }
    
    // Remove order from book
    void remove_order(double price, int quantity, bool is_bid) {
        if (price <= 0.0 || quantity <= 0) {
            throw std::invalid_argument("Invalid price or quantity");
        }
        
        auto& book = is_bid ? bids : asks;
        auto it = book.find(price);
        
        if (it != book.end()) {
            it->second.total_quantity -= quantity;
            it->second.order_count--;
            
            if (it->second.total_quantity <= 0) {
                book.erase(it);
            }
        }
        
        operation_count++;
    }
    
    // Get best bid (highest price)
    double get_best_bid() const {
        operation_count++;
        return bids.empty() ? 0.0 : bids.begin()->first;
    }
    
    // Get best ask (lowest price)
    double get_best_ask() const {
        operation_count++;
        return asks.empty() ? 0.0 : asks.begin()->first;
    }
    
    // Get market depth efficiently
    std::vector<OrderLevel> get_market_depth(int levels) const {
        std::vector<OrderLevel> depth;
        depth.reserve(levels * 2); // Pre-allocate for efficiency
        
        // Add bid levels
        int bid_count = 0;
        for (const auto& [price, level] : bids) {
            if (bid_count >= levels) break;
            depth.push_back(level);
            bid_count++;
        }
        
        // Add ask levels
        int ask_count = 0;
        for (const auto& [price, level] : asks) {
            if (ask_count >= levels) break;
            depth.push_back(level);
            ask_count++;
        }
        
        operation_count++;
        return depth;
    }
    
    // Simple order matching logic
    void match_orders() {
        while (!bids.empty() && !asks.empty()) {
            double best_bid = bids.begin()->first;
            double best_ask = asks.begin()->first;
            
            if (best_bid >= best_ask) {
                // Match found - execute trade
                int trade_quantity = std::min(
                    bids.begin()->second.total_quantity,
                    asks.begin()->second.total_quantity
                );
                
                // Update quantities
                remove_order(best_bid, trade_quantity, true);
                remove_order(best_ask, trade_quantity, false);
                
                std::cout << "Trade executed: " << trade_quantity 
                          << " shares at $" << best_ask << '\n';
            } else {
                break; // No more matches
            }
        }
    }
    
    // Benchmark order processing performance
    void benchmark_performance(int iterations) {
        std::cout << "Benchmarking order book performance...\n";
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Add orders
        for (int i = 0; i < iterations; ++i) {
            double price = 100.0 + (i % 100) * 0.01;
            int quantity = (i % 1000) + 1;
            bool is_bid = (i % 2 == 0);
            
            add_order(price, quantity, is_bid);
        }
        
        // Get market depth
        for (int i = 0; i < iterations / 10; ++i) {
            get_market_depth(10);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Processed " << iterations << " orders in " 
                  << duration.count() << " microseconds\n";
        std::cout << "Average time per operation: " 
                  << (double)duration.count() / operation_count << " microseconds\n";
        
        // Display current book state
        std::cout << "\nCurrent order book state:\n";
        std::cout << "Bids: " << bids.size() << " levels\n";
        std::cout << "Asks: " << asks.size() << " levels\n";
        std::cout << "Best bid: $" << std::fixed << std::setprecision(2) 
                  << get_best_bid() << '\n';
        std::cout << "Best ask: $" << std::fixed << std::setprecision(2) 
                  << get_best_ask() << '\n';
    }
    
    // Get spread
    double get_spread() const {
        double best_bid = get_best_bid();
        double best_ask = get_best_ask();
        
        if (best_bid > 0.0 && best_ask > 0.0) {
            return best_ask - best_bid;
        }
        return 0.0;
    }
};

int main() {
    try {
        OrderBook book;
        
        // Add some sample orders
        book.add_order(100.00, 1000, true);   // Bid
        book.add_order(100.01, 500, true);    // Bid
        book.add_order(100.05, 1000, false);  // Ask
        book.add_order(100.06, 750, false);   // Ask
        
        std::cout << "Initial order book:\n";
        std::cout << "Best bid: $" << std::fixed << std::setprecision(2) 
                  << book.get_best_bid() << '\n';
        std::cout << "Best ask: $" << std::fixed << std::setprecision(2) 
                  << book.get_best_ask() << '\n';
        std::cout << "Spread: $" << std::fixed << std::setprecision(2) 
                  << book.get_spread() << '\n';
        
        // Get market depth
        auto depth = book.get_market_depth(5);
        std::cout << "\nMarket depth (5 levels):\n";
        for (const auto& level : depth) {
            std::cout << "Price: $" << std::fixed << std::setprecision(2) 
                      << level.price << ", Qty: " << level.total_quantity 
                      << ", Orders: " << level.order_count << '\n';
        }
        
        // Match orders
        std::cout << "\nMatching orders...\n";
        book.match_orders();
        
        // Benchmark performance
        std::cout << "\n";
        book.benchmark_performance(10000);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    
    return 0;
}
```

### Common Problems and Fixes

#### Problem 1: Inefficient Data Structure Choice
```cpp
// WRONG: Using vector for price levels (O(n) search)
std::vector<OrderLevel> bids;
std::vector<OrderLevel> asks;

// CORRECT: Use map for O(log n) search
std::map<double, OrderLevel, std::greater<double>> bids;  // Descending
std::map<double, OrderLevel, std::less<double>> asks;     // Ascending
```

#### Problem 2: Missing Pre-allocation
```cpp
// WRONG: No pre-allocation for vectors
std::vector<OrderLevel> get_market_depth(int levels) const {
    std::vector<OrderLevel> depth;
    // Vector grows dynamically, causing reallocations
    
    for (const auto& [price, level] : bids) {
        depth.push_back(level);  // Potential reallocation
    }
    return depth;
}

// CORRECT: Pre-allocate for efficiency
std::vector<OrderLevel> get_market_depth(int levels) const {
    std::vector<OrderLevel> depth;
    depth.reserve(levels * 2);  // Pre-allocate space
    
    for (const auto& [price, level] : bids) {
        depth.push_back(level);  // No reallocation needed
    }
    return depth;
}
```

#### Problem 3: Inefficient Loops
```cpp
// WRONG: Traditional for loop with index
for (size_t i = 0; i < bids.size(); ++i) {
    auto it = bids.begin();
    std::advance(it, i);  // Expensive operation
    // Process *it
}

// CORRECT: Range-based for loop
for (const auto& [price, level] : bids) {
    // Process level directly
}
```

---

## Summary of Key Learning Points

### 1. Modern C++ Best Practices
- **RAII**: Always use RAII for resource management
- **Const correctness**: Mark parameters and methods as const when possible
- **References over pointers**: Use references for non-nullable parameters
- **Range-based for**: Prefer over traditional indexed loops

### 2. Performance Optimization
- **Cache locality**: Structure data for sequential access
- **Pre-allocation**: Reserve vector capacity when size is known
- **Efficient data structures**: Choose appropriate containers (map vs vector)
- **Inline functions**: Use for small, frequently called functions

### 3. Error Handling
- **Exceptions**: Use for error conditions that prevent normal operation
- **Validation**: Always validate input parameters
- **Exception safety**: Ensure resources are properly cleaned up

### 4. HFT-Specific Considerations
- **Memory layout**: Optimize struct member ordering for cache performance
- **Latency**: Minimize function calls and dynamic allocations in hot paths
- **Predictability**: Avoid undefined behavior and use deterministic algorithms
- **Benchmarking**: Always measure performance characteristics

### 5. Common Pitfalls to Avoid
- **Manual resource management**: Use RAII instead
- **Inefficient parameter passing**: Pass large objects by const reference
- **Missing validation**: Always check input parameters
- **Poor data structure choice**: Consider performance characteristics

These solutions demonstrate how to write efficient, maintainable C++ code suitable for high-frequency trading applications while following modern C++ best practices.
