#include "lex_support.h"
#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <grammar_file> <input_file>" << std::endl;
        return 1;
    }
    
    std::string grammarFile = argv[1];
    std::string inputFile = argv[2];
    
    LL1Parser parser(grammarFile, inputFile);
    parser.parseInput();
    
    return 0;
}