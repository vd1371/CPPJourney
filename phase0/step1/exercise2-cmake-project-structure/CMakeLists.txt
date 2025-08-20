# Create CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(Calculator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Include directories
include_directories(include)

# Create executable
add_executable(calculator 
    src/main.cpp
    src/calculator.cpp
)

# Set target properties
target_compile_options(calculator PRIVATE -O2)