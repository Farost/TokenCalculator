cmake_minimum_required(VERSION 3.8)

set (This Calculator)

project(${Thos} CXX)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(googletest)

set(Headers
    include/token.h 
    include/calculator.h 
)
set (Sources 
    src/token.cpp 
    src/calculator.cpp 
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)