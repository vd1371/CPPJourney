#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>

class PriceCalculator {
private:
    // A vector for bids and asks
    std::vector<std::pair<double, int>> bids;
    std::vector<std::pair<double, int>> asks;

public:
    PriceCalculator() {
        // Seed the random number generator
        std::srand(std::time(nullptr));
        
        // Initialize with some default prices
        generateInitialPrices();
    }

    // Generate initial bid and ask prices
    void generateInitialPrices() {
        for (int i = 0; i < 100; i++) {
            double bidPrice = 100.0 + i * 0.01;
            int volume = rand() % 900 + 100;
            bids.push_back(std::make_pair(bidPrice, volume));
        }
        for (int i = 0; i < 100; i++) {
            double askPrice = 102.0 - i * 0.01;
            int volume = rand() % 900 + 100;
            asks.push_back(std::make_pair(askPrice, volume));
        }
    }

    // Add a bid
    void addBid(double price, int volume) {
        bids.push_back(std::make_pair(price, volume));
    }

    // Add an ask
    void addAsk(double price, int volume) {
        asks.push_back(std::make_pair(price, volume));
    }

    // Calculate Volume Weighted Average Price for the vector of bids
    double calculateVWAP(const std::vector<std::pair<double, int>>& bids) {
        double totalVolume = 0;
        double totalPriceVolume = 0;
        for (const auto& bid : bids) {
            totalVolume += bid.second;
            totalPriceVolume += bid.first * bid.second;
        }
        return totalPriceVolume / totalVolume;
    }

    // Calculate VWAP using pointer arithmetic
    double calculateVWAPWithPointers(const std::vector<std::pair<double, int>>& bids) {
        if (bids.empty()) return 0.0;
        
        double totalVolume = 0;
        double totalPriceVolume = 0;
        
        const std::pair<double, int>* ptr = bids.data();
        const std::pair<double, int>* endPtr = bids.data() + bids.size();
        
        while (ptr < endPtr) {
            totalVolume += ptr->second;
            totalPriceVolume += ptr->first * ptr->second;
            ptr++;
        }
        
        return totalPriceVolume / totalVolume;
    }

    // Demonstrate pointer arithmetic with raw arrays
    void demonstratePointerArithmetic() {
        std::cout << "\n=== POINTER ARITHMETIC DEMONSTRATIONS ===\n";
        
        // Create a simple array for demonstration
        double prices[] = {100.50, 101.25, 102.00, 103.75, 104.50};
        int volumes[] = {1000, 1500, 2000, 1750, 1200};
        const int size = 5;
        
        std::cout << "Original arrays:\n";
        std::cout << "Prices: ";
        for (int i = 0; i < size; i++) {
            std::cout << prices[i] << " ";
        }
        std::cout << "\nVolumes: ";
        for (int i = 0; i < size; i++) {
            std::cout << volumes[i] << " ";
        }
        std::cout << "\n\n";
        
        // Method 1: Basic pointer arithmetic traversal
        std::cout << "1. Basic pointer arithmetic traversal:\n";
        double* pricePtr = prices;
        int* volumePtr = volumes;
        
        for (int i = 0; i < size; i++) {
            std::cout << "Price[" << i << "] = " << *(pricePtr + i) 
                      << ", Volume[" << i << "] = " << *(volumePtr + i) << "\n";
        }
        
        // Method 2: Pointer increment traversal
        std::cout << "\n2. Pointer increment traversal:\n";
        pricePtr = prices;
        volumePtr = volumes;
        
        for (int i = 0; i < size; i++) {
            std::cout << "Price[" << i << "] = " << *pricePtr 
                      << ", Volume[" << i << "] = " << *volumePtr << "\n";
            pricePtr++;  // Move to next element
            volumePtr++; // Move to next element
        }
        
        // Method 3: Pointer arithmetic for reverse traversal
        std::cout << "\n3. Reverse traversal using pointer arithmetic:\n";
        pricePtr = prices + size - 1;  // Point to last element
        volumePtr = volumes + size - 1;
        
        for (int i = size - 1; i >= 0; i--) {
            std::cout << "Price[" << i << "] = " << *pricePtr 
                      << ", Volume[" << i << "] = " << *volumePtr << "\n";
            pricePtr--;  // Move to previous element
            volumePtr--;
        }
        
        // Method 4: Pointer arithmetic for finding array bounds
        std::cout << "\n4. Array bounds using pointer arithmetic:\n";
        double* beginPtr = prices;
        double* endPtr = prices + size;
        
        std::cout << "Array starts at: " << beginPtr << "\n";
        std::cout << "Array ends at: " << endPtr << "\n";
        std::cout << "Number of elements: " << (endPtr - beginPtr) << "\n";
        
        // Method 5: Pointer arithmetic for array manipulation
        std::cout << "\n5. Array manipulation using pointers:\n";
        pricePtr = prices;
        volumePtr = volumes;
        
        // Double all prices and volumes
        for (int i = 0; i < size; i++) {
            *pricePtr *= 2.0;
            *volumePtr *= 2;
            pricePtr++;
            volumePtr++;
        }
        
        // Display modified arrays
        std::cout << "Modified arrays (doubled):\n";
        std::cout << "Prices: ";
        for (int i = 0; i < size; i++) {
            std::cout << prices[i] << " ";
        }
        std::cout << "\nVolumes: ";
        for (int i = 0; i < size; i++) {
            std::cout << volumes[i] << " ";
        }
        std::cout << "\n";
        
        // Method 6: Pointer arithmetic for finding specific elements
        std::cout << "\n6. Finding elements using pointer arithmetic:\n";
        pricePtr = prices;
        volumePtr = volumes;
        
        // Find the maximum price
        double* maxPricePtr = pricePtr;
        for (int i = 1; i < size; i++) {
            if (*(pricePtr + i) > *maxPricePtr) {
                maxPricePtr = pricePtr + i;
            }
        }
        
        int maxIndex = maxPricePtr - pricePtr;  // Calculate index using pointer arithmetic
        std::cout << "Maximum price: " << *maxPricePtr << " at index " << maxIndex << "\n";
        
        // Method 7: Pointer arithmetic for array slicing
        std::cout << "\n7. Array slicing using pointer arithmetic:\n";
        double* sliceStart = prices + 1;  // Start from second element
        double* sliceEnd = prices + 4;    // End at fourth element
        
        std::cout << "Slice from index 1 to 3: ";
        for (double* ptr = sliceStart; ptr <= sliceEnd; ptr++) {
            std::cout << *ptr << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    PriceCalculator calculator;
    
    // Demonstrate pointer arithmetic
    calculator.demonstratePointerArithmetic();
    
    // Show VWAP calculation using both methods
    std::cout << "\n=== VWAP CALCULATION COMPARISON ===\n";
    
    // Create some sample data
    std::vector<std::pair<double, int>> sampleBids = {
        {100.50, 1000},
        {101.25, 1500},
        {102.00, 2000},
        {103.75, 1750},
        {104.50, 1200}
    };
    
    double vwap1 = calculator.calculateVWAP(sampleBids);
    double vwap2 = calculator.calculateVWAPWithPointers(sampleBids);
    
    std::cout << "VWAP using range-based for: " << std::fixed << std::setprecision(2) << vwap1 << "\n";
    std::cout << "VWAP using pointer arithmetic: " << std::fixed << std::setprecision(2) << vwap2 << "\n";
    
    return 0;
}