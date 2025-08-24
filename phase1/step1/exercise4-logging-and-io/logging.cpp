#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class MarketLogger {
private:
    std::shared_ptr<spdlog::logger> logger;
    std::string log_directory;
    
public:
    MarketLogger(const std::string& log_directory) : log_directory(log_directory) {
        // Create console and file sinks
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_directory + ".log");
        
        // Create logger with both sinks
        std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
        logger = std::make_shared<spdlog::logger>("market_logger", sinks.begin(), sinks.end());
        
        // Set log level and format
        logger->set_level(spdlog::level::info);
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%t] %v");
        
        // Register the logger globally
        spdlog::register_logger(logger);
        
        logger->info("MarketLogger initialized with log file: {}.log", log_directory);
    }

    // Log market data to both console and file
    bool log_market_data(const std::string& symbol, double price, 
                        int volume, uint64_t timestamp)
    {
        try {
            logger->info("Market Data: Symbol={}, Price={:.2f}, Volume={}, Timestamp={}", 
                        symbol, price, volume, timestamp);
            
            // Also log to CSV for data analysis
            std::ofstream csv_file(log_directory + "_market_data.csv", std::ios::app);
            if (csv_file.is_open()) {
                csv_file << timestamp << "," << price << "," << volume << "," << symbol << std::endl;
                csv_file.close();
                return true;
            } else {
                logger->error("Failed to open CSV file for market data");
                return false;
            }
        } catch (const std::exception& e) {
            logger->error("Exception in log_market_data: {}", e.what());
            return false;
        }
    }
    
    // Log order activity
    bool log_order(int order_id, const std::string& symbol, 
                  int quantity, double price, char order_type)
    {
        try {
            std::string type_str = (order_type == 'B') ? "BUY" : "SELL";
            logger->info("Order: ID={}, Symbol={}, Type={}, Quantity={}, Price={:.2f}", 
                        order_id, symbol, type_str, quantity, price);
            
            // Also log to CSV for order tracking
            std::ofstream csv_file(log_directory + "_orders.csv", std::ios::app);
            if (csv_file.is_open()) {
                csv_file << order_id << "," << symbol << "," << quantity << "," 
                        << price << "," << order_type << std::endl;
                csv_file.close();
                return true;
            } else {
                logger->error("Failed to open CSV file for orders");
                return false;
            }
        } catch (const std::exception& e) {
            logger->error("Exception in log_order: {}", e.what());
            return false;
        }
    }

    // Log general descriptions/info
    bool log_description(const std::string& description) {
        try {
            logger->info("Description: {}", description);
            return true;
        } catch (const std::exception& e) {
            logger->error("Exception in log_description: {}", e.what());
            return false;
        }
    }
    
    // Log warnings
    void log_warning(const std::string& message) {
        logger->warn("Warning: {}", message);
    }
    
    // Log errors
    void log_error(const std::string& message) {
        logger->error("Error: {}", message);
    }
    
    // Log debug information
    void log_debug(const std::string& message) {
        logger->debug("Debug: {}", message);
    }
    
    // Read and parse log files
    std::vector<std::string> read_log_entries(const std::string& filename)
    {
        std::vector<std::string> entries;
        try {
            std::ifstream file(filename);
            if (!file.is_open()) {
                logger->error("Failed to open file: {}", filename);
                return entries;
            }
            
            std::string line;
            while (std::getline(file, line)) {
                entries.push_back(line);
            }
            logger->info("Successfully read {} entries from {}", entries.size(), filename);
        } catch (const std::exception& e) {
            logger->error("Exception reading file {}: {}", filename, e.what());
        }
        return entries;
    }
    
    // Get current timestamp
    uint64_t get_current_timestamp()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    }
    
    // Set log level
    void set_log_level(spdlog::level::level_enum level) {
        logger->set_level(level);
        logger->info("Log level set to: {}", spdlog::level::to_string_view(level));
    }
    
    // Flush all pending log messages
    void flush() {
        logger->flush();
    }
};

struct MarketData {
    std::string symbol;
    double price;
    int volume;
    uint64_t timestamp;
    char order_type;
};

int main() {
    try {
        // Initialize spdlog
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%t] %v");
        
        MarketLogger logger("market_data");
        
        // Set log level to debug for development
        logger.set_log_level(spdlog::level::debug);
        
        // Log some market data
        MarketData data;
        data.symbol = "AAPL";
        data.price = 150.75;
        data.volume = 1000;
        data.order_type = 'B';
        data.timestamp = logger.get_current_timestamp();
        
        logger.log_market_data(data.symbol, data.price, data.volume, data.timestamp);
        
        // Log some orders
        logger.log_order(1001, "AAPL", 500, 150.50, 'B');
        logger.log_order(1002, "AAPL", 300, 151.00, 'S');
        
        // Log some general information
        logger.log_description("Market session started");
        logger.log_warning("High volatility detected in tech sector");
        logger.log_debug("Processing market data updates");
        
        // Demonstrate different log levels
        logger.log_description("Market data processing completed successfully");
        
        // Flush all logs before exit
        logger.flush();
        
        spdlog::info("Program completed successfully");
        
    } catch (const std::exception& e) {
        spdlog::critical("Fatal error in main: {}", e.what());
        return 1;
    }
    
    return 0;
}