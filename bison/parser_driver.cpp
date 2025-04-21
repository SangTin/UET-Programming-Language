#include <iostream>
#include <fstream>
#include "lexer.hpp"
#include "upl_types.h"

using namespace std;

// Khai báo biến và hàm từ parser
extern ASTNode* program_root;
extern Lexer* current_lexer;
extern int yyparse();  // Hàm yyparse() truyền thống
extern void printAST(ASTNode* node, int depth);
extern int error_count;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    
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
                cout << "\nAbstract Syntax Tree:" << endl;
                printAST(program_root, 0);
                
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