#!/bin/bash

# Default build behavior
BUILD=false

# Parse command-line arguments
while [[ $# -gt 0 ]]; do
    case "$1" in
        --build)
            BUILD=true
            shift
            ;;
        *)
            break
            ;;
    esac
done

# Compile the program only if BUILD is true
if [ "$BUILD" = true ]; then
    echo "Compiling..."
    g++ -std=c++17 main.cpp lexer.cpp parser.cpp -o upl_parser

    # Check if compilation was successful
    if [ $? -ne 0 ]; then
        echo "Compilation failed!"
        exit 1
    fi
fi

# Run the program with the specified options
./upl_parser --g input_grammar.txt --i input.txt "$@"

# If DOT file was generated and graphviz is installed, generate image
if [ -f "parse_tree.dot" ]; then
    if command -v dot &> /dev/null; then
        echo "Generating parse tree image..."
        dot -Tpng parse_tree.dot -o parse_tree.png
        echo "Parse tree image saved to parse_tree.png"
        
        # Try to open the image if a GUI environment is available
        if command -v xdg-open &> /dev/null; then
            xdg-open parse_tree.png
        elif command -v open &> /dev/null; then
            open parse_tree.png
        fi
    else
        echo "Graphviz not found. Install it to generate images from DOT files."
        echo "On Ubuntu/Debian: sudo apt-get install graphviz"
        echo "On macOS with Homebrew: brew install graphviz"
        echo "On Windows: download from https://graphviz.org/download/"
    fi
fi