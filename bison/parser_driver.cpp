#include <iostream>
#include <fstream>
#include <string>
#include "lexer.hpp"
#include "upl_types.h"

using namespace std;

// Khai báo biến và hàm từ parser
extern ASTNode* program_root;
extern Lexer* current_lexer;
extern int error_count;
extern int yyparse();
extern void printAST(ASTNode* node, int depth);

void printUsage(const char* programName) {
    cout << "Usage: " << programName << " <input_file> [options]" << endl;
    cout << "Options:" << endl;
    cout << "  --dot <filename>  Export AST to DOT format" << endl;
    cout << "  --help            Show this help message" << endl;
}

int main(int argc, char* argv[]) {
    // Kiểm tra tham số dòng lệnh
    if (argc < 2) {
        cerr << "Error: Input file required." << endl;
        printUsage(argv[0]);
        return 1;
    }
    
    string inputFile = argv[1];
    string dotFile = "";
    
    // Xử lý các tùy chọn
    for (int i = 2; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--dot" && i + 1 < argc) {
            dotFile = argv[++i];
        } else if (arg == "--help") {
            printUsage(argv[0]);
            return 0;
        } else {
            cerr << "Unknown option: " << arg << endl;
            printUsage(argv[0]);
            return 1;
        }
    }
    
    try {
        // Khởi tạo lexer
        current_lexer = new Lexer(inputFile);
        
        // Reset biến đếm lỗi
        error_count = 0;
        
        // Bắt đầu phân tích cú pháp
        cout << "Starting parsing..." << endl;
        int result = yyparse();
        
        if (result == 0 && error_count == 0) {
            cout << "Parsing successful!" << endl;
            
            // In cây cú pháp
            if (program_root) {
                // In cây cú pháp ở dạng text
                cout << "\nAbstract Syntax Tree:" << endl;
                printAST(program_root, 0);
                
                // Xuất cây cú pháp sang định dạng DOT nếu có yêu cầu
                if (!dotFile.empty()) {
                    program_root->exportDOT(dotFile);
                }
                
                // Giải phóng bộ nhớ
                delete program_root;
            }
        } else {
            cout << "Parsing failed with " << error_count << " errors." << endl;
        }
        
        delete current_lexer;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}