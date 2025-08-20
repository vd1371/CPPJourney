cmake_minimum_required(VERSION 3.20)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(hello_world src/main.cpp)

# Set compiler flags
target_compile_options(hello_world PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -O2
)

# Enable testing
enable_testing()
add_test(NAME HelloWorldTest COMMAND hello_world)