%{
#include <iostream>
#include <string>
#include <vector>
#include "lexer.hpp"

extern int yylex();
extern char* yytext;
extern int yylineno;
extern FILE* yyin;

void yyerror(const char* s);
void report_error(const char* msg, int line, const char* token);

std::vector<std::string> syntax_errors;
int error_count = 0;
const int MAX_ERRORS = 20;
%}

%define parse.error verbose

%token TOKEN_BEGIN TOKEN_END TOKEN_INT TOKEN_BOOL
%token TOKEN_IF TOKEN_THEN TOKEN_ELSE TOKEN_DO TOKEN_WHILE TOKEN_FOR TOKEN_PRINT
%token TOKEN_PLUS TOKEN_MULTIPLY TOKEN_GREATER TOKEN_GREATER_EQUAL TOKEN_EQUAL TOKEN_ASSIGN
%token TOKEN_LEFT_PAREN TOKEN_RIGHT_PAREN TOKEN_LEFT_BRACE TOKEN_RIGHT_BRACE
%token TOKEN_SEMICOLON TOKEN_IDENTIFIER TOKEN_NUMBER
%token TOKEN_TRUE TOKEN_FALSE

%left TOKEN_EQUAL
%left TOKEN_GREATER TOKEN_GREATER_EQUAL 
%left TOKEN_PLUS
%left TOKEN_MULTIPLY

%precedence THEN
%precedence TOKEN_ELSE

%%


program
    : TOKEN_BEGIN stmts TOKEN_END
    | TOKEN_BEGIN error TOKEN_END { yyerrok; }
    ;

stmts
    : stmts stmt
    | /* empty */
    ;

stmt
    : expression TOKEN_SEMICOLON
    | assignment TOKEN_SEMICOLON
    | declaration TOKEN_SEMICOLON
    | if_stmt
    | do_while_stmt TOKEN_SEMICOLON
    | for_stmt
    | print_stmt TOKEN_SEMICOLON
    | block_stmt
    | error TOKEN_SEMICOLON { 
        yyerrok; /* Khôi phục sau lỗi tại dấu chấm phẩy */ 
        if (++error_count > MAX_ERRORS) YYABORT;
      }
    ;

expression
    : expression relop addition
    | addition
    ;

addition
    : addition TOKEN_PLUS multiplication
    | multiplication
    ;

multiplication
    : multiplication TOKEN_MULTIPLY factor
    | factor
    ;

factor
    : TOKEN_IDENTIFIER
    | TOKEN_NUMBER
    | TOKEN_TRUE
    | TOKEN_FALSE
    | TOKEN_LEFT_PAREN expression TOKEN_RIGHT_PAREN
    ;

declaration
    : dtype assignment
    | dtype TOKEN_IDENTIFIER
    ;

assignment
    : TOKEN_IDENTIFIER TOKEN_ASSIGN expression
    ;

if_stmt
    : TOKEN_IF TOKEN_LEFT_PAREN expression TOKEN_RIGHT_PAREN TOKEN_THEN stmt %prec THEN
    | TOKEN_IF TOKEN_LEFT_PAREN expression TOKEN_RIGHT_PAREN TOKEN_THEN stmt TOKEN_ELSE stmt
    ;

do_while_stmt
    : TOKEN_DO stmt TOKEN_WHILE TOKEN_LEFT_PAREN expression TOKEN_RIGHT_PAREN
    ;

for_stmt
    : TOKEN_FOR TOKEN_LEFT_PAREN init TOKEN_SEMICOLON condition TOKEN_SEMICOLON update TOKEN_RIGHT_PAREN stmt
    ;

init
    : declaration
    | assignment
    | /* empty */
    ;

condition
    : expression
    | /* empty */
    ;

update
    : assignment
    | /* empty */
    ;

print_stmt
    : TOKEN_PRINT TOKEN_LEFT_PAREN expression TOKEN_RIGHT_PAREN
    ;

block_stmt
    : TOKEN_LEFT_BRACE stmts TOKEN_RIGHT_BRACE
    | TOKEN_LEFT_BRACE error TOKEN_RIGHT_BRACE { 
        yyerrok; /* Khôi phục lỗi trong khối */ 
        report_error("Error in block statement", yylineno, yytext);
      }
    ;

dtype
    : TOKEN_INT
    | TOKEN_BOOL
    ;

relop
    : TOKEN_GREATER
    | TOKEN_GREATER_EQUAL
    | TOKEN_EQUAL
    ;

%%

void yyerror(const char* s) {
    std::string error = std::string(s) + " at line " + std::to_string(yylineno) + 
                        " near token '" + std::string(yytext) + "'";
    std::cerr << error << std::endl;
    
    // Lưu lại lỗi
    syntax_errors.push_back(error);
}

void report_error(const char* msg, int line, const char* token) {
    std::string error = std::string(msg) + " at line " + std::to_string(line) + 
                       " near token '" + std::string(token) + "'";
    std::cerr << error << std::endl;
    syntax_errors.push_back(error);
}