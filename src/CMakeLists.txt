set(Sources Error.cpp
        Scanner.cpp
        Parser.cpp
        utls/Object.cpp
        Expr.cpp
)


add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${Sources} ${Headers})