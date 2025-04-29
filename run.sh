#!/bin/bash

# Source files to check for changes
SOURCE_FILES="main.cpp lexer.cpp lexer.hpp parser.cpp parser.hpp"
EXECUTABLE="upl_parser"

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

# Check if we need to compile
need_compile=false

# If executable doesn't exist, we need to compile
if [ ! -f "$EXECUTABLE" ]; then
    echo "Executable not found. Compilation needed."
    need_compile=true
# Otherwise check if any source file is newer than the executable
elif [ "${BUILD:-false}" = true ]; then
    need_compile=true
else
    for src_file in $SOURCE_FILES; do
        if [ ! -f "$src_file" ]; then
            echo "Warning: Source file $src_file not found!"
            continue
        fi
        
        # Compare modification times
        if [ "$src_file" -nt "$EXECUTABLE" ]; then
            echo "Source file $src_file has been modified. Recompilation needed."
            need_compile=true
            break
        fi
    done
fi

# Compile the program if needed
if [ "$need_compile" = true ]; then
    echo "Compiling..."
    g++ -std=c++17 main.cpp lexer.cpp parser.cpp -o $EXECUTABLE

    # Check if compilation was successful
    if [ $? -ne 0 ]; then
        echo "Compilation failed!"
        exit 1
    fi
    echo "Compilation successful."
else
    echo "No changes detected. Skipping compilation."
fi

if [ -f "parse_tree.dot" ]; then
    echo "Removing old parse tree DOT file..."
    rm parse_tree.dot
fi

# Run the program with the specified options
./$EXECUTABLE --g input_grammar.txt --i input.txt "$@"

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