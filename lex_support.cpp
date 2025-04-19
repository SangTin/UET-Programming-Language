#include "lex_support.h"
#include <string.h>

// Định nghĩa các biến toàn cục
FILE* yyin = NULL;
char yytext_buffer[1024];
char* yytext = yytext_buffer;
int yylineno = 1;
std::string current_token_text;

void init_lexer_vars() {
    yyin = NULL;
    yylineno = 1;
    memset(yytext_buffer, 0, sizeof(yytext_buffer));
    current_token_text = "";
}