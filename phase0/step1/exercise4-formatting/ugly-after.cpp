#include <algorithm>
#include <iostream>
#include <vector>
int main() {
  std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};
  std::sort(numbers.begin(), numbers.end());
  for (int n : numbers) {
    std::cout << n << " ";
  }
  std::cout << std::endl;
  return 0;
}