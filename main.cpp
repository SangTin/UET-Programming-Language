#include "lex_support.h"
#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --g <grammar_file>    Specify the grammar file (required)" << std::endl;
    std::cout << "  --i <input_file>      Specify the input file (required)" << std::endl;
    std::cout << "  --verbose             Enable verbose output" << std::endl;
    std::cout << "  --tree <format>       Specify parse tree output format (cmd/dot)" << std::endl;
    std::cout << "  --output <file>       Specify output file for parse tree (default: parse_tree.dot)" << std::endl;
    std::cout << "  --productions         Print the grammar productions" << std::endl;
    std::cout << "  --first               Print the FIRST sets" << std::endl;
    std::cout << "  --follow              Print the FOLLOW sets" << std::endl;
    std::cout << "  --table               Print the LL(1) parsing table" << std::endl;
    std::cout << "  --terminals           Print the list of terminals" << std::endl;
    std::cout << "  --non-terminals       Print the list of non-terminals" << std::endl;
    std::cout << "  --help                Display this help message" << std::endl;
}

int main(int argc, char* argv[]) {
    // Default values
    std::string grammarFile = "";
    std::string inputFile = "";
    std::string treeFormat = ""; // empty means no tree output
    std::string outputFile = "parse_tree.dot";
    bool verbose = false;
    bool printProductions = false;
    bool printFirst = false;
    bool printFollow = false;
    bool printTable = false;
    bool printTerminals = false;
    bool printNonTerminals = false;
    
    // Parse command line arguments
    std::unordered_map<std::string, std::string*> optionMap = {
        {"--g", &grammarFile},
        {"--i", &inputFile},
        {"--tree", &treeFormat},
        {"--output", &outputFile}
    };
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "--help") {
            printUsage(argv[0]);
            return 0;
        } else if (arg == "--verbose") {
            verbose = true;
        } else if (arg == "--productions") {
            printProductions = true;
        } else if (arg == "--first") {
            printFirst = true;
        } else if (arg == "--follow") {
            printFollow = true;
        } else if (arg == "--table") {
            printTable = true;
        } else if (arg == "--terminals") {
            printTerminals = true;
        } else if (arg == "--non-terminals") {
            printNonTerminals = true;
        } else if (optionMap.find(arg) != optionMap.end()) {
            // This is an option that requires a value
            if (i + 1 < argc) {
                *optionMap[arg] = argv[i + 1];
                i++; // Skip the next argument since we've used it as a value
            } else {
                std::cerr << "Error: Option " << arg << " requires a value." << std::endl;
                printUsage(argv[0]);
                return 1;
            }
        } else {
            std::cerr << "Error: Unknown option " << arg << std::endl;
            printUsage(argv[0]);
            return 1;
        }
    }
    
    // Check if required options are provided
    if (grammarFile.empty()) {
        std::cerr << "Error: Grammar file (--g) is required." << std::endl;
        printUsage(argv[0]);
        return 1;
    }
    
    // If we're only printing grammar info, we don't need the input file
    bool onlyGrammarInfo = printProductions || printFirst || printFollow || 
                          printTable || printTerminals || printNonTerminals;
    
    // Check if input file is required but not provided
    if (inputFile.empty() && !onlyGrammarInfo) {
        std::cerr << "Error: Input file (--i) is required for parsing." << std::endl;
        printUsage(argv[0]);
        return 1;
    }
    
    // Validate tree format if specified
    if (!treeFormat.empty() && treeFormat != "cmd" && treeFormat != "dot") {
        std::cerr << "Error: Tree format must be either 'cmd' or 'dot'." << std::endl;
        printUsage(argv[0]);
        return 1;
    }
    
    // If verbose mode is enabled, print the configuration
    if (verbose) {
        std::cout << "Configuration:" << std::endl;
        std::cout << "  Grammar file: " << grammarFile << std::endl;
        if (!inputFile.empty()) {
            std::cout << "  Input file: " << inputFile << std::endl;
        }
        if (!treeFormat.empty()) {
            std::cout << "  Tree output format: " << treeFormat << std::endl;
            if (treeFormat == "dot") {
                std::cout << "  Output file: " << outputFile << std::endl;
            }
        }
    }
    
    try {
        // Initialize parser
        LL1Parser parser(grammarFile, inputFile);
        
        // Print grammar information if requested
        if (printProductions) {
            std::cout << "\n===== Grammar Productions =====\n" << std::endl;
            parser.printProductions();
            std::cout << std::endl;
        }
        
        if (printFirst) {
            std::cout << "\n===== FIRST Sets =====\n" << std::endl;
            parser.printFirstSets();
            std::cout << std::endl;
        }
        
        if (printFollow) {
            std::cout << "\n===== FOLLOW Sets =====\n" << std::endl;
            parser.printFollowSets();
            std::cout << std::endl;
        }
        
        if (printTable) {
            std::cout << "\n===== LL(1) Parsing Table =====\n" << std::endl;
            parser.printParsingTable();
            std::cout << std::endl;
        }
        
        if (printTerminals) {
            std::cout << "\n===== Terminals =====\n" << std::endl;
            parser.printTerminals();
            std::cout << std::endl;
        }
        
        if (printNonTerminals) {
            std::cout << "\n===== Non-Terminals =====\n" << std::endl;
            parser.printNonTerminals();
            std::cout << std::endl;
        }
        
        // If no input file is provided, we're done
        if (inputFile.empty()) {
            return 0;
        }
        
        // Parse the input
        if (verbose) {
            std::cout << "Starting parsing..." << std::endl;
        }
        
        bool success = parser.parseInput();
        
        if (success) {
            std::cout << "Parsing successful!" << std::endl;
            
            if (treeFormat == "cmd") {
                std::cout << "\nParse Tree (Enhanced View):" << std::endl;
                parser.printEnhancedParseTree();
            } else if (treeFormat == "dot") {
                parser.exportParseTreeToDot(outputFile);
            } else if (verbose) {
                // In verbose mode, print basic parse tree if no specific format requested
                parser.printParseTree();
            }
        } else {
            std::cout << "Parsing failed!" << std::endl;
            parser.printErrors();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}