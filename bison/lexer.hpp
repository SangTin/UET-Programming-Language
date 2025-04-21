#ifndef LEXER_HPP
#define LEXER_HPP

#include <bits/stdc++.h>
using namespace std;

enum TokenType {
    L_TOKEN_EOF, L_TOKEN_BEGIN, L_TOKEN_END, L_TOKEN_INT, L_TOKEN_BOOL, 
    L_TOKEN_IF, L_TOKEN_THEN, L_TOKEN_ELSE, L_TOKEN_DO, L_TOKEN_WHILE, L_TOKEN_FOR, L_TOKEN_PRINT,
    L_TOKEN_PLUS, L_TOKEN_MULTIPLY, L_TOKEN_GREATER, L_TOKEN_GREATER_EQUAL, L_TOKEN_EQUAL, L_TOKEN_ASSIGN,
    L_TOKEN_LEFT_PAREN, L_TOKEN_RIGHT_PAREN, L_TOKEN_LEFT_BRACE, L_TOKEN_RIGHT_BRACE, 
    L_TOKEN_SEMICOLON, L_TOKEN_IDENTIFIER, L_TOKEN_NUMBER, L_TOKEN_ERROR, L_TOKEN_TRUE, L_TOKEN_FALSE
};
string tokenTypeName(TokenType type);

struct Token {
    TokenType type;
    string message, lexeme;
    int line, column;

    Token() = default;
    
    Token(TokenType type, const string& lexeme, int line, int column, const string& message = "")
        : type(type), message(message), lexeme(lexeme), line(line), column(column) {}

    friend ostream& operator<<(ostream& os, const Token& token) {
        if (token.type == L_TOKEN_ERROR) {
            os << "ERROR: " << token.message << " at line " << token.line << ", column " << token.column;
        } else if (token.message.empty()) {
            os << tokenTypeName(token.type);
        } else {
            os << tokenTypeName(token.type) << ' ' << token.message;
        }
        return os;
    }
};

class FileReader {
private:
    ifstream file;
    static const int BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE * 2 + 2]; // 2 buffers + 2 EOF markers
    char* lexemeBegin;               // Con trỏ đến điểm bắt đầu token
    char* forward;                   // Con trỏ đến vị trí đang quét
    int line;
    int column;
    bool reachedEOF;
    string lexemeBuffer;

public:
    FileReader(const string& filename) : line(1), column(0), reachedEOF(false) {
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("Không thể mở file: " + filename);
        }
        
        // Đánh dấu cuối của mỗi buffer bằng ký tự EOF (để xác định khi nào cần đọc buffer tiếp theo)
        buffer[BUFFER_SIZE] = EOF;
        buffer[BUFFER_SIZE * 2 + 1] = EOF;
        
        // Đọc dữ liệu vào buffer đầu tiên
        file.read(buffer, BUFFER_SIZE);
        if (file.gcount() < BUFFER_SIZE) {
            buffer[file.gcount()] = EOF; // Đánh dấu EOF thực sự
            reachedEOF = true;
        }
        
        // Khởi tạo con trỏ
        lexemeBegin = buffer;
        forward = buffer;

        lexemeBuffer.reserve(1024);
    }

    ~FileReader() {
        if (file.is_open()) {
            file.close();
        }
    }

    // Trả về ký tự hiện tại mà không di chuyển con trỏ
    char peek() {
        return *forward;
    }

    // Trả về ký tự kế tiếp mà không di chuyển con trỏ
    char peekNext() {
        if (*(forward + 1) == EOF) {
            loadNextBuffer();
        }
        return *(forward + 1);
    }

    // Di chuyển con trỏ và trả về ký tự mới
    char advance() {
        if (*forward == EOF) {
            loadNextBuffer();
        }
        
        char c = *forward++;
        column++;
        
        if (c == '\n') {
            line++;
            column = 0;
        }
        
        return c;
    }

    // Lấy lexeme hiện tại (từ lexemeBegin đến forward)
    const string& getLexeme() {
        if (lexemeBegin <= forward) {
            lexemeBuffer.assign(lexemeBegin, forward);
        } else {
            lexemeBuffer.clear();
            lexemeBuffer.append(lexemeBegin, buffer + BUFFER_SIZE);
            lexemeBuffer.append(buffer + BUFFER_SIZE + 1, forward);
        }
        return lexemeBuffer;
    }

    // Đặt lại điểm bắt đầu token
    void setLexemeBegin() {
        lexemeBegin = forward;
    }

    // Kiểm tra xem đã đọc hết file chưa
    bool isAtEnd() {
        return reachedEOF && *forward == EOF;
    }

    int getLine() const {
        return line;
    }

    int getColumn() const {
        return column;
    }

private:
    void loadNextBuffer() {
        // Xác định buffer nào đang được sử dụng
        bool usingFirstBuffer = (forward < buffer + BUFFER_SIZE);
        
        // Xác định vị trí để đọc vào
        char* loadPosition = usingFirstBuffer ? buffer + BUFFER_SIZE + 1 : buffer;
        
        // Nếu đã đọc hết file, không làm gì
        if (reachedEOF) return;
        
        // Đọc dữ liệu mới
        file.read(loadPosition, BUFFER_SIZE);
        int bytesRead = file.gcount();
        
        // Đánh dấu EOF nếu cần
        if (bytesRead < BUFFER_SIZE) {
            loadPosition[bytesRead] = EOF;
            reachedEOF = true;
        }
        
        // Cập nhật con trỏ forward
        forward = usingFirstBuffer ? buffer + BUFFER_SIZE + 1 : buffer;
    }
};

class Lexer {
private:
    unique_ptr<FileReader> reader;
    unordered_map<string, TokenType> keywords;

public:
    Lexer(const string& filename) {
        reader = make_unique<FileReader>(filename);
        keywords["begin"] = L_TOKEN_BEGIN;
        keywords["end"] = L_TOKEN_END;
        keywords["int"] = L_TOKEN_INT;
        keywords["bool"] = L_TOKEN_BOOL;
        keywords["if"] = L_TOKEN_IF;
        keywords["then"] = L_TOKEN_THEN;
        keywords["else"] = L_TOKEN_ELSE;
        keywords["do"] = L_TOKEN_DO;
        keywords["while"] = L_TOKEN_WHILE;
        keywords["for"] = L_TOKEN_FOR;
        keywords["print"] = L_TOKEN_PRINT;
        keywords["true"] = L_TOKEN_TRUE;
        keywords["false"] = L_TOKEN_FALSE;
    }

    vector<Token> scanTokens();
    Token nextToken();
    bool isAtEnd() const {
        return reader->isAtEnd();
    }

private:
    void skipWhitespace();
    bool match(char expected);
    Token scanIdentifier();
    Token scanNumber();
};

#endif // LEXER_HPP