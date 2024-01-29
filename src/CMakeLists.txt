set(Sources Error.cpp
        Scanner.cpp
        AstPrettyPrint.cpp
        Expr/BinaryExp.cpp
        Expr/LiteralExp.cpp
        Expr/Grouping.cpp
        Expr/UnaryExp.cpp
)


add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${Sources} ${Headers})