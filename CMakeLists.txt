cmake_minimum_required(VERSION 3.25)
project(CLI_Timer)

set(CMAKE_CXX_STANDARD 23)

add_executable(CLI_Timer ./src/main.cpp)

# Set compiler flags
target_compile_options(CLI_Timer PRIVATE -Wall -O3)
