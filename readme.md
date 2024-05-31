# Crux Language

Crux is a simple, dynamically-typed scripting language implemented in C++. It features a tree-walk interpreter, a hand-written parser, and a lexical scanner.

## Features

- Lexical analysis (Scanning)
- Parsing (Generating Abstract Syntax Trees)
- Abstract Syntax Tree (AST) printing
- Interpreter (Tree-walk execution)
- Variable declarations and assignments (`var`)
- Control flow (`if`, `while`, `for`, `break`)
- Functions (`fun`)
- Native functions (like `clock()`)
- Basic arithmetic and logical operations
- String concatenation
- Ternary operator (`? :`)
- Variable resolution and scoping

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- A C++ compiler (supporting C++17 or later), such as GCC or Clang.
- CMake (version 3.10 or higher).
- Google Test library (Crux is configured to find it).

### Building the Project

1.  Clone the repository:

    ```bash
    git clone https://github.com/Rohith-Raju/Crux.git
    cd Crux
    ```

2.  Create a build directory and navigate into it:

    ```bash
    mkdir build
    cd build
    ```

3.  Run CMake to configure the project. Make sure Google Test is accessible on your system or specify its location if necessary.

    ```bash
    cmake ..
    ```

4.  Build the project:
    ```bash
    make
    ```

This will build the `crux` executable and the test runner.

## Running Crux

You can run Crux in two modes: interpreter mode (REPL) or by providing a script file.

### Interpreter Mode (REPL)

Run the executable without any arguments:

```bash
./crux
```

You will see a `> ` prompt. Type your Crux code and press Enter.

```crux
> var a = 10;
> print(a + 5);
15.000000
> if (a > 5) { print("yes"); } else { print("no"); }
yes
> fun greet(name) { print("Hello, " + name + "!"); }
> greet("World");
Hello, World!
> clock();
1678886400.123456 // (Approximate current time in seconds)
>
```

### Running a Script File

Save your Crux code in a file with the `.crux` extension (e.g., `my_script.crux`). Then run the executable with the file path as an argument:

```bash
./crux my_script.crux
```

Example `my_script.crux`:

```crux
var i = 0;
while (i < 5) {
  print(i);
  i = i + 1;
}

fun factorial(n) {
  if (n == 0) return 1;
  return n * factorial(n - 1);
}

print("Factorial of 5:");
print(factorial(5));
```

## Examples

Here are a few examples showcasing some of Crux's features:

### Variables and Arithmetic

```crux
var x = 10;
var y = 20;
var sum = x + y;
print(sum); // Output: 30.000000

var name = "Crux";
var greeting = "Hello, " + name + "!";
print(greeting); // Output: Hello, Crux!
```

### Control Flow (If/Else)

```crux
var temperature = 25;
if (temperature > 30) {
  print("It's hot!");
} else if (temperature > 20) {
  print("It's warm.");
} else {
  print("It's cool.");
}
// Output: It's warm.
```

### Control Flow (While Loop)

```crux
var count = 3;
while (count > 0) {
  print("Counting down: " + count);
  count = count - 1;
}
// Output:
// Counting down: 3.000000
// Counting down: 2.000000
// Counting down: 1.000000
```

### Control Flow (For Loop)

```crux
for (var i = 0; i < 3; i = i + 1) {
  print("Loop iteration: " + i);
}
// Output:
// Loop iteration: 0.000000
// Loop iteration: 1.000000
// Loop iteration: 2.000000
```

### Functions

```crux
fun add(a, b) {
  return a + b;
}

var result = add(5, 7);
print(result); // Output: 12.000000
```

### Ternary Operator

```crux
var age = 18;
var status = age >= 18 ? "Adult" : "Minor";
print(status); // Output: Adult
```

## Running Tests

The project includes a suite of tests using the Google Test framework.

1.  Ensure you have built the project as described in the "Building the Project" section.
2.  Navigate to the build directory:
    ```bash
    cd build
    ```
3.  Run the test executable:
    ```bash
    ./Crux_test
    ```
    (The exact name of the test executable might vary slightly depending on your CMake configuration, but it's typically named after the project or a test target).

The test output will show you which tests passed or failed.

## GitHub Actions CI/CD

This project uses GitHub Actions for Continuous Integration and Continuous Deployment. The CI/CD pipeline automatically builds the project and runs the tests whenever changes are pushed to the repository.

The workflow configuration files are located in the `.github/workflows/` directory at the root of the repository.

## Project Structure

- `Crux/main.cpp`: The main entry point of the interpreter. Handles command-line arguments and sets up the REPL or file execution.
- `Crux/include/`: Contains header files for different components of the language (Scanner, Parser, Interpreter, Expr, Statement, Token, etc.).
- `Crux/src/`: Contains the implementation files (`.cpp`) for the components defined in the include directory.
- `Crux/test/`: Contains test files using Google Test.
