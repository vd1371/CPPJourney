cmake_minimum_required(VERSION 3.16)
project(MarketLogging)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find spdlog package
find_package(spdlog REQUIRED)

# Create executable
add_executable(logging logging.cpp)

# Link against spdlog
target_link_libraries(logging spdlog::spdlog)

# Set compiler flags
target_compile_options(logging PRIVATE -Wall -Wextra)

# Optional: Enable debug symbols
set(CMAKE_BUILD_TYPE Debug)
