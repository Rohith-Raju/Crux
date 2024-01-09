set(Sources Error.cpp
        Scanner.cpp)

set(Headers Error.h
        Scanner.h
        Token.h)


add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${Sources} ${Headers})