set(Sources Error.cpp
        Scanner.cpp
)


add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${Sources} ${Headers})