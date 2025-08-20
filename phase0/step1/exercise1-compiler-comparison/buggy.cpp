#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Intentional error: wrong type
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << std::endl;
    }

    // Intentional error: unused variable
    int unused_variable = 10;

    // Intentional error: missing semicolon
    std::cout << "Hello, World!"

        return 0;
}