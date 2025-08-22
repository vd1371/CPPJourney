#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstring>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()


struct MarketData {
    std::array<char, 9> symbol;  // Symbol (max 8 characters + null terminator)
    double price;                // double
    int volume;                  // integer
    long long timestamp;         // 64bit integer
};

class MarketDataManager {
    private:
        std::vector<MarketData> marketData;

    public:
        void addMarketData(const MarketData& data) {
            marketData.push_back(data);
        }

        void printMarketData() {
            for (const auto& data : marketData) {
                std::cout << "Symbol: " << data.symbol.data() << ", Price: " << data.price << ", Volume: " << data.volume << ", Timestamp: " << data.timestamp << std::endl;
            }
        }

        void findHighestVolume() {
            int highestVolume = 0;
            for (const auto& data : marketData) {
                if (data.volume > highestVolume) {
                    highestVolume = data.volume;
                }
            }
            std::cout << "Highest Volume: " << highestVolume << std::endl;
        }

        void findAveragePrice() {
            double averagePrice = 0;
            for (const auto& data : marketData) {
                averagePrice += data.price;
            }
            averagePrice /= marketData.size();

            std::cout << "Average Price: " << averagePrice << std::endl;
        }
};

// Populate the market data with 10 random market data
void populateMarketData(MarketDataManager& marketDataManager) {
    for (int i = 0; i < 10; i++) {
        MarketData marketData;
        // Copy symbol safely, ensuring max 8 characters
        std::strncpy(marketData.symbol.data(), "AAPL", 8);
        marketData.symbol[8] = '\0';  // Ensure null termination
        
        marketData.price = rand() % 1000;
        marketData.volume = rand() % 1000;
        marketData.timestamp = 1713859200 + i;
        marketDataManager.addMarketData(marketData);
    }
}

int main() {
    // Seed the random number generator with current time
    srand(static_cast<unsigned int>(time(nullptr)));
    
    MarketDataManager marketDataManager;
    populateMarketData(marketDataManager);
    marketDataManager.printMarketData();
    marketDataManager.findHighestVolume();
    marketDataManager.findAveragePrice();
    return 0;
}