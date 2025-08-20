#include <iostream>
#include <vector>
#include <string>

void processData(std::vector<int>& data) {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] > 100) {
            std::cout << "Large number found: " << data[i] << std::endl;
        }
    }
}

int main() {
    std::vector<int> numbers = {50, 150, 25, 200, 75};
    
    processData(numbers);
    
    std::string message = "Hello";
    std::cout << message << std::endl;
    
    return 0;
}