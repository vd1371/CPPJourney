#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "Hello! What's your name? ";
    std::getline(std::cin, name);

    if (name.empty()) {
        name = "World";
    }

    std::cout << "Hello, " << name << "! Welcome to C++!" << std::endl;
    std::cout << "You're using C++ standard: " << __cplusplus << std::endl;

    return 0;
}