#include <iostream>
#include <vector>

int calculateSum(const std::vector<int>& numbers) {
    int sum = 0;
    for (size_t i = 0; i <= numbers.size(); i++) {  // Fixed the previous bug
        sum += numbers[i];
        std::cout << "Adding " << numbers[i] << " at index " << i << std::endl;
    }

    return sum;
}

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};

    std::cout << "Calculating sum of: ";
    for (int n : data) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    int result = calculateSum(data);
    std::cout << "Sum: " << result << std::endl;

    return 0;
}