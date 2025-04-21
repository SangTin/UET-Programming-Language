#!/bin/bash

# Initialize variables
BUILD=0
PARSER_ARGS=()

# Parse script arguments
for arg in "$@"; do
    if [ "$arg" = "--build" ]; then
        BUILD=1
    else
        PARSER_ARGS+=("$arg")
    fi
done

# Build only if --build flag is provided
if [ $BUILD -eq 1 ]; then
    echo "Compiling..."
    g++ -std=c++17 -o upl_parser main.cpp lexer.cpp parser.cpp
    
    # Check if compilation was successful
    if [ $? -ne 0 ]; then
        echo "Compilation failed!"
        exit 1
    fi
    
    echo "Compilation successful!"
else
    # Check if executable exists, if not, warn the user
    if [ ! -f ./upl_parser ]; then
        echo "Warning: upl_parser executable not found. Run with --build to compile first."
        exit 1
    fi
fi

# Run the program with the remaining arguments
./upl_parser "${PARSER_ARGS[@]}"