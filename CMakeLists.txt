cmake_minimum_required(VERSION 3.27)
project(crux)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(crux main.cpp
        src/Token.h
        src/Scanner.h
        src/Scanner.cpp
        src/Error.h
        src/Error.cpp
)
