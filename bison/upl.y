%{
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include "lexer.hpp"
#include "upl_types.h"

using namespace std;

// Root của cây cú pháp
ASTNode* program_root = nullptr;

// Lexer hiện tại
Lexer* current_lexer = nullptr;
Token current_token;

// Khai báo các hàm
int yylex();
void yyerror(const char* s);
void printAST(ASTNode* node, int depth = 0);

%}

%union {
    int int_val;
    char* str_val;
    ASTNode* node_ptr;
}

/* Định nghĩa token - phải khớp với các token từ lexer */
%token BEGIN_TOKEN END
%token INT BOOL
%token IF THEN ELSE
%token DO WHILE FOR
%token PRINT
%token PLUS MULTIPLY
%token GREATER GREATER_EQUAL EQUAL
%token ASSIGN
%token LEFT_PAREN RIGHT_PAREN
%token LEFT_BRACE RIGHT_BRACE
%token SEMICOLON
%token <str_val> IDENTIFIER
%token <int_val> NUMBER
%token TRUE FALSE
%token ERROR

/* Định nghĩa kiểu cho các non-terminal */
%type <node_ptr> program stmts stmt
%type <node_ptr> expression addition multiplication factor
%type <node_ptr> assignment declaration declaration_tail
%type <node_ptr> if_stmt else_part
%type <node_ptr> do_while_stmt for_stmt
%type <node_ptr> for_init for_condition for_update
%type <node_ptr> print_stmt block_stmt
%type <node_ptr> dtype relop

/* Xác định token bắt đầu (start symbol) */
%start program

%%

/* Ngữ pháp UPL đầy đủ */

program
    : BEGIN_TOKEN stmts END { 
        $$ = new ASTNode("program");
        $$->addChild($2);
        program_root = $$;
    }
    ;

stmts
    : stmt stmts {
        $$ = new ASTNode("stmts");
        $$->addChild($1);
        
        ASTNode* stmtsNode = $2;
        for (auto& child : stmtsNode->children) {
            $$->addChild(child);
        }
        stmtsNode->children.clear();
        delete stmtsNode;
    }
    | /* epsilon */ { $$ = new ASTNode("stmts"); }
    ;

stmt
    : expression SEMICOLON { $$ = $1; }
    | assignment SEMICOLON { $$ = $1; }
    | declaration SEMICOLON { $$ = $1; }
    | if_stmt { $$ = $1; }
    | do_while_stmt SEMICOLON { $$ = $1; }
    | for_stmt { $$ = $1; }
    | print_stmt SEMICOLON { $$ = $1; }
    | block_stmt { $$ = $1; }
    | error SEMICOLON {
        // Phục hồi sau khi gặp lỗi và tìm thấy dấu chấm phẩy
        $$ = new ASTNode("error");
        yyerrok;  // Báo cho Bison biết đã xử lý lỗi
    }
    | error RIGHT_BRACE {
        // Phục hồi khi gặp dấu } (hữu ích cho lỗi trong khối)
        $$ = new ASTNode("error");
        yyerrok;
    }
    ;

expression
    : addition { $$ = $1; }
    | expression relop addition {
        $$ = $2;
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

addition
    : multiplication { $$ = $1; }
    | addition PLUS multiplication {
        $$ = new ASTNode("addition", "+");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

multiplication
    : factor { $$ = $1; }
    | multiplication MULTIPLY factor {
        $$ = new ASTNode("multiplication", "*");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

factor
    : IDENTIFIER {
        $$ = new ASTNode("identifier", $1);
        free($1);
    }
    | NUMBER {
        $$ = new ASTNode("number", to_string($1));
    }
    | TRUE {
        $$ = new ASTNode("boolean", "true");
    }
    | FALSE {
        $$ = new ASTNode("boolean", "false");
    }
    | LEFT_PAREN expression RIGHT_PAREN {
        $$ = $2;
    }
    ;

declaration
    : dtype declaration_tail {
        $$ = new ASTNode("declaration");
        $$->addChild($1);
        $$->addChild($2);
    }
    ;

declaration_tail
    : IDENTIFIER {
        $$ = new ASTNode("identifier", $1);
        free($1);
    }
    | IDENTIFIER ASSIGN expression {
        $$ = new ASTNode("identifier_with_init", $1);
        $$->addChild($3);
        free($1);
    }
    ;

assignment
    : IDENTIFIER ASSIGN expression {
        $$ = new ASTNode("assignment");
        $$->addChild(new ASTNode("identifier", $1));
        $$->addChild($3);
        free($1);
    }
    ;

if_stmt
    : IF LEFT_PAREN expression RIGHT_PAREN THEN block_stmt else_part {
        $$ = new ASTNode("if_statement");
        $$->addChild($3); // condition
        $$->addChild($6); // then block
        if ($7) {
            $$->addChild($7); // else block (if exists)
        }
    }
    ;

else_part
    : ELSE block_stmt { $$ = $2; }
    | /* epsilon */ { $$ = nullptr; }
    ;

do_while_stmt
    : DO stmt WHILE LEFT_PAREN expression RIGHT_PAREN {
        $$ = new ASTNode("do_while");
        $$->addChild($2); // body
        $$->addChild($5); // condition
    }
    ;

for_stmt
    : FOR LEFT_PAREN for_init SEMICOLON for_condition SEMICOLON for_update RIGHT_PAREN stmt {
        $$ = new ASTNode("for");
        if ($3) $$->addChild($3); // init
        if ($5) $$->addChild($5); // condition
        if ($7) $$->addChild($7); // update
        $$->addChild($9); // body
    }
    ;

for_init
    : declaration { $$ = $1; }
    | assignment { $$ = $1; }
    | /* epsilon */ { $$ = nullptr; }
    ;

for_condition
    : expression { $$ = $1; }
    | /* epsilon */ { $$ = nullptr; }
    ;

for_update
    : assignment { $$ = $1; }
    | /* epsilon */ { $$ = nullptr; }
    ;

print_stmt
    : PRINT LEFT_PAREN expression RIGHT_PAREN {
        $$ = new ASTNode("print");
        $$->addChild($3);
    }
    ;

block_stmt
    : LEFT_BRACE stmts RIGHT_BRACE {
        $$ = new ASTNode("block");
        ASTNode* stmtsNode = $2;
        for (auto& child : stmtsNode->children) {
            $$->addChild(child);
        }
        stmtsNode->children.clear();
        delete stmtsNode;
    }
    ;

dtype
    : INT { $$ = new ASTNode("type", "int"); }
    | BOOL { $$ = new ASTNode("type", "bool"); }
    ;

relop
    : GREATER { $$ = new ASTNode("relop", ">"); }
    | GREATER_EQUAL { $$ = new ASTNode("relop", ">="); }
    | EQUAL { $$ = new ASTNode("relop", "=="); }
    ;

%%

int error_count = 0;
bool recovery_mode = false;

// Hàm chuyển đổi từ TokenType sang token Bison
int tokenTypeToBison(TokenType type) {
    switch (type) {
        case L_TOKEN_BEGIN: return BEGIN_TOKEN;
        case L_TOKEN_END: return END;
        case L_TOKEN_INT: return INT;
        case L_TOKEN_BOOL: return BOOL;
        case L_TOKEN_IF: return IF;
        case L_TOKEN_THEN: return THEN;
        case L_TOKEN_ELSE: return ELSE;
        case L_TOKEN_DO: return DO;
        case L_TOKEN_WHILE: return WHILE;
        case L_TOKEN_FOR: return FOR;
        case L_TOKEN_PRINT: return PRINT;
        case L_TOKEN_PLUS: return PLUS;
        case L_TOKEN_MULTIPLY: return MULTIPLY;
        case L_TOKEN_GREATER: return GREATER;
        case L_TOKEN_GREATER_EQUAL: return GREATER_EQUAL;
        case L_TOKEN_EQUAL: return EQUAL;
        case L_TOKEN_ASSIGN: return ASSIGN;
        case L_TOKEN_LEFT_PAREN: return LEFT_PAREN;
        case L_TOKEN_RIGHT_PAREN: return RIGHT_PAREN;
        case L_TOKEN_LEFT_BRACE: return LEFT_BRACE;
        case L_TOKEN_RIGHT_BRACE: return RIGHT_BRACE;
        case L_TOKEN_SEMICOLON: return SEMICOLON;
        case L_TOKEN_IDENTIFIER: return IDENTIFIER;
        case L_TOKEN_NUMBER: return NUMBER;
        case L_TOKEN_TRUE: return TRUE;
        case L_TOKEN_FALSE: return FALSE;
        case L_TOKEN_EOF: return 0;  // Bison sử dụng 0 cho EOF
        default: return -1;  // Token không xác định
    }
}

// Triển khai hàm yylex cho Bison
int yylex() {
    if (!current_lexer) {
        return 0; // EOF nếu không có lexer
    }
    
    current_token = current_lexer->nextToken();
    
    // Bỏ qua token lỗi từ lexer
    while (current_token.type == L_TOKEN_ERROR) {
        cerr << "Lexical error: " << current_token.message << " at line " 
             << current_token.line << ", column " << current_token.column << endl;
        current_token = current_lexer->nextToken();
    }
    
    // Kiểm tra EOF
    if (current_token.type == L_TOKEN_EOF) {
        return 0;
    }
    
    // Xử lý phục hồi lỗi
    if (recovery_mode) {
        // Tìm kiếm điểm đồng bộ hóa
        bool is_sync_point = false;
        
        switch (current_token.type) {
            case L_TOKEN_SEMICOLON:
            case L_TOKEN_RIGHT_BRACE:
            case L_TOKEN_BEGIN:
            case L_TOKEN_END:
            case L_TOKEN_IF:
            case L_TOKEN_ELSE:
            case L_TOKEN_WHILE:
            case L_TOKEN_DO:
            case L_TOKEN_FOR:
            case L_TOKEN_INT:
            case L_TOKEN_BOOL:
                is_sync_point = true;
                break;
            default:
                break;
        }
        
        if (is_sync_point) {
            recovery_mode = false;
            // Reset yyclearin; // Không cần nếu không sử dụng lookahead
        } else {
            // Skip token nếu không phải điểm đồng bộ hóa
            return yylex(); // Đệ quy để tìm điểm đồng bộ
        }
    }
    
    // Chuyển đổi TokenType sang token Bison
    int token = tokenTypeToBison(current_token.type);
    
    // Xử lý giá trị cho các token có giá trị
    if (current_token.type == L_TOKEN_IDENTIFIER) {
        yylval.str_val = strdup(current_token.lexeme.c_str());
    } else if (current_token.type == L_TOKEN_NUMBER) {
        yylval.int_val = stoi(current_token.lexeme);
    }
    
    return token;
}

// Hàm báo lỗi cải tiến
void yyerror(const char* s) {
    error_count++;
    cerr << "Parse error: " << s << " at line " 
         << current_token.line << ", column " << current_token.column;
    
    // Cung cấp thông tin bổ sung về token hiện tại
    if (current_token.type != L_TOKEN_EOF) {
        cerr << ", unexpected token '" << current_token.lexeme << "'";
    }
    
    cerr << endl;
    
    // Chỉ đặt recovery_mode nếu chưa phục hồi
    if (!recovery_mode) {
        recovery_mode = true;
    }
}

// In cây cú pháp
void printAST(ASTNode* node, int depth) {
    if (!node) return;
    
    string indent(depth * 2, ' ');
    cout << indent << node->type;
    if (!node->value.empty()) {
        cout << " (" << node->value << ")";
    }
    cout << endl;
    
    for (auto child : node->children) {
        printAST(child, depth + 1);
    }
}