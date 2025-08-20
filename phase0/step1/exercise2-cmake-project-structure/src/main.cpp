#include <iostream>
#include "calculator.h"

int main() {
    Calculator calculator;
    std::cout << calculator.add(1, 2) << std::endl;
    std::cout << calculator.subtract(1, 2) << std::endl;
    std::cout << calculator.multiply(1, 2) << std::endl;

    try {
        std::cout << calculator.divide(1, 0) << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}