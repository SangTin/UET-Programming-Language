#ifndef ERROR_REPORTER_HPP
#define ERROR_REPORTER_HPP

#include <string>
#include <vector>
#include <iostream>

struct Error {
    int line;
    int column;
    std::string message;
    
    Error(int line, int column, const std::string& message)
        : line(line), column(column), message(message) {}
};

class ErrorReporter {
private:
    std::vector<Error> errors;
    bool hasErrors;

public:
    ErrorReporter() : hasErrors(false) {}
    
    void reportError(int line, int column, const std::string& message) {
        errors.emplace_back(line, column, message);
        hasErrors = true;
    }
    
    bool errorsFound() const {
        return hasErrors;
    }
    
    const std::vector<Error>& getErrors() const {
        return errors;
    }
    
    void printErrors() const {
        if (!hasErrors) {
            std::cout << "No errors found." << std::endl;
            return;
        }
        
        std::cout << "Errors found: " << errors.size() << std::endl;
        for (const auto& error : errors) {
            std::cerr << " Error at line " << error.line 
                      << ", column " << error.column << ": " 
                      << error.message << std::endl;
        }
    }
};

#endif // ERROR_REPORTER_HPP