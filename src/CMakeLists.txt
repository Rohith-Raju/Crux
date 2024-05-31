set(Sources Error.cpp
        Scanner.cpp
        Parser.cpp
        utls/Object.cpp
        Expr.cpp
				AstPrinter.cpp
				Interpreter.cpp
				Statement.cpp
				Function.cpp
				Resolver.cpp
				env/Env.cpp
)


add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${Sources} ${Headers})
