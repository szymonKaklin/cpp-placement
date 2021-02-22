
cmake_minimum_required(VERSION 3.12)

project(Calculator)

add_executable(calculator
    source/main.cpp
    README.md
)

target_compile_features(calculator PRIVATE cxx_std_17)
