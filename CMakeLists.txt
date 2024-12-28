cmake_minimum_required(VERSION 3.10)
project(LifeSimulator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(LifeSimulator ${SOURCES})

# Link spdlog
find_package(spdlog REQUIRED)
target_link_libraries(LifeSimulator PRIVATE spdlog::spdlog)

# Add and link nlohmann/json
add_subdirectory(external/json)
target_link_libraries(LifeSimulator PRIVATE nlohmann_json::nlohmann_json)

# Enable verbose build output
set(CMAKE_VERBOSE_MAKEFILE ON)
