#ifndef LEX_SUPPORT_H
#define LEX_SUPPORT_H

#include <stdio.h>
#include <string>

extern FILE* yyin;
extern char yytext_buffer[1024];
extern char* yytext;
extern int yylineno;
extern std::string current_token_text;

// Thiết lập giá trị ban đầu
void init_lexer_vars();

#endif