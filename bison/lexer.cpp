#include "lexer.hpp"

string tokenTypeName(TokenType type) {
    switch (type) {
        case L_TOKEN_BEGIN: return "BEGIN";
        case L_TOKEN_END: return "END";
        case L_TOKEN_INT: return "INT";
        case L_TOKEN_BOOL: return "BOOL";
        case L_TOKEN_IF: return "IF";
        case L_TOKEN_THEN: return "THEN";
        case L_TOKEN_ELSE: return "ELSE";
        case L_TOKEN_DO: return "DO";
        case L_TOKEN_WHILE: return "WHILE";
        case L_TOKEN_FOR: return "FOR";
        case L_TOKEN_PRINT: return "PRINT";
        case L_TOKEN_PLUS: return "PLUS";
        case L_TOKEN_MULTIPLY: return "MULTIPLY";
        case L_TOKEN_GREATER: return "GREATER";
        case L_TOKEN_GREATER_EQUAL: return "GREATER_EQUAL";
        case L_TOKEN_EQUAL: return "EQUAL";
        case L_TOKEN_ASSIGN: return "ASSIGN";
        case L_TOKEN_LEFT_PAREN: return "LEFT_PAREN";
        case L_TOKEN_RIGHT_PAREN: return "RIGHT_PAREN";
        case L_TOKEN_LEFT_BRACE: return "LEFT_BRACE";
        case L_TOKEN_RIGHT_BRACE: return "RIGHT_BRACE";
        case L_TOKEN_SEMICOLON: return "SEMICOLON";
        case L_TOKEN_IDENTIFIER: return "IDENTIFIER";
        case L_TOKEN_NUMBER: return "NUMBER";
        case L_TOKEN_EOF: return "$";
        case L_TOKEN_ERROR: return "ERROR";
        case L_TOKEN_TRUE: return "TRUE";
        case L_TOKEN_FALSE: return "FALSE";
        default: return "UNKNOWN";
    }
}

vector<Token> Lexer::scanTokens() {
    vector<Token> tokens;
    
    while (!reader->isAtEnd()) {
        // Đặt điểm bắt đầu token mới
        reader->setLexemeBegin();
        
        Token token = nextToken();
        if (token.type != L_TOKEN_EOF) {
            tokens.push_back(token);
        }
        
        if (token.type == L_TOKEN_EOF) {
            break;
        }
    }
    
    return tokens;
}

Token Lexer::nextToken() {
    skipWhitespace();
    
    // Đặt điểm bắt đầu token mới sau khi bỏ qua whitespace
    reader->setLexemeBegin();

    if (reader->isAtEnd()) {
        return Token(L_TOKEN_EOF, "", reader->getLine(), reader->getColumn());
    }

    char c = reader->advance();

    switch (c) {
        case '(': return Token(L_TOKEN_LEFT_PAREN, "(", reader->getLine(), reader->getColumn());
        case ')': return Token(L_TOKEN_RIGHT_PAREN, ")", reader->getLine(), reader->getColumn());
        case '{': return Token(L_TOKEN_LEFT_BRACE, "{", reader->getLine(), reader->getColumn());
        case '}': return Token(L_TOKEN_RIGHT_BRACE, "}", reader->getLine(), reader->getColumn());
        case ';': return Token(L_TOKEN_SEMICOLON, ";", reader->getLine(), reader->getColumn());
        case '+': return Token(L_TOKEN_PLUS, "+", reader->getLine(), reader->getColumn());
        case '*': return Token(L_TOKEN_MULTIPLY, "*", reader->getLine(), reader->getColumn());

        case '>': {
            if (match('=')) {
                return Token(L_TOKEN_GREATER_EQUAL, ">=", reader->getLine(), reader->getColumn());
            }
            return Token(L_TOKEN_GREATER, ">", reader->getLine(), reader->getColumn());
        }

        case '=': {
            if (match('=')) {
                return Token(L_TOKEN_EQUAL, "==", reader->getLine(), reader->getColumn());
            }
            return Token(L_TOKEN_ASSIGN, "=", reader->getLine(), reader->getColumn());
        }

        case '/': {
            if (match('/')) {
                // Comment một dòng
                while (reader->peek() != '\n' && !reader->isAtEnd()) {
                    reader->advance();
                }
                return nextToken();
            } else if (match('*')) {
                // Comment nhiều dòng
                while (!(reader->peek() == '*' && reader->peekNext() == '/') && !reader->isAtEnd()) {
                    reader->advance();
                }
                
                if (reader->isAtEnd()) {
                    return Token(L_TOKEN_ERROR, "", reader->getLine(), reader->getColumn(), "Unterminated comment");
                }
                
                // Bỏ qua */ kết thúc
                reader->advance(); // *
                reader->advance(); // /
                
                return nextToken();
            }
            return Token(L_TOKEN_ERROR, "", reader->getLine(), reader->getColumn(), "Unexpected character");
        }
        
        default: {
            if (isdigit(c)) {
                return scanNumber();
            } else if (isalpha(c)) {
                return scanIdentifier();
            } else {
                return Token(L_TOKEN_ERROR, string(1, c), reader->getLine(), reader->getColumn(), "Unexpected character \'" + string(1, c) + "\'");
            }
        }
    }
}

void Lexer::skipWhitespace() {
    while (true) {
        char c = reader->peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
            case '\n':
                reader->advance();
                break;
            default:
                return;
        }
    }
}

bool Lexer::match(char expected) {
    if (reader->isAtEnd() || reader->peek() != expected) {
        return false;
    }
    
    reader->advance();
    return true;
}

Token Lexer::scanIdentifier() {
    // Đọc toàn bộ identifier
    while (isalnum(reader->peek())) {
        reader->advance();
    }
    
    const string &lexeme = reader->getLexeme();
    
    // Kiểm tra từ khóa
    TokenType type = L_TOKEN_IDENTIFIER;
    if (keywords.find(lexeme) != keywords.end()) {
        type = keywords[lexeme];
        return Token(type, lexeme, reader->getLine(), reader->getColumn());
    } else {
        // Kiểm tra tính hợp lệ của identifier
        bool valid = true;
        if (!isalpha(lexeme[0])) {
            valid = false;
        } else {
            size_t i = 1;
            while (i < lexeme.size() && isalpha(lexeme[i])) {
                i++;
            }
            
            // Từ vị trí i đến cuối chuỗi phải toàn là số
            while (i < lexeme.size()) {
                if (!isdigit(lexeme[i])) {
                    valid = false;
                    break;
                }
                i++;
            }
        }
        
        if (!valid) {
            return Token(L_TOKEN_ERROR, lexeme, reader->getLine(), reader->getColumn(), "Invalid identifier \'" + lexeme + "\'");
        }
        
        return Token(type, lexeme, reader->getLine(), reader->getColumn(), lexeme);
    }
}

Token Lexer::scanNumber() {
    // Đọc toàn bộ số
    while (isdigit(reader->peek())) {
        reader->advance();
    }

    if (isalpha(reader->peek())) {
        while (isalnum(reader->peek())) {
            reader->advance();
        }
        
        return Token(L_TOKEN_ERROR, reader->getLexeme(), reader->getLine(), reader->getColumn(), "Invalid number \'" + reader->getLexeme() + "\'");
    }
    
    // Lấy lexeme từ lexemeBegin đến forward
    string lexeme = reader->getLexeme();
    
    return Token(L_TOKEN_NUMBER, lexeme, reader->getLine(), reader->getColumn(), lexeme);
}