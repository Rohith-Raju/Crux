cmake_minimum_required(VERSION 3.27)
project(crux)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)

add_executable(${CMAKE_PROJECT_NAME}_run main.cpp
        include/Parser.h)
target_link_libraries(${CMAKE_PROJECT_NAME}_run ${CMAKE_PROJECT_NAME}_lib)
