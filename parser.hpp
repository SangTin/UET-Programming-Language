#include <bits/stdc++.h>
#include "lexer.hpp"
#include "error_reporter.hpp"

using namespace std;

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

vector<string> splitSymbols(const std::string& str);

struct ParseTreeNode {
    string symbol;
    vector<string> production;  // Quy tắc sản xuất được áp dụng (nếu là non-terminal)
    string lexeme;  // Giá trị thực tế của token (nếu là terminal)
    vector<shared_ptr<ParseTreeNode>> children;
    
    ParseTreeNode(const string& symbol) : symbol(symbol) {}
    
    void addChild(shared_ptr<ParseTreeNode> child) {
        children.push_back(child);
    }
    
    void printTree(int depth = 0) const {
        string indent(depth * 2, ' ');
        cout << indent << symbol;
        
        if (!lexeme.empty()) {
            cout << " (" << lexeme << ")";
        }
        cout << endl;
        
        for (const auto& child : children) {
            child->printTree(depth + 1);
        }
    }

    void printTreeEnhanced(int depth = 0, bool isLast = true) const;
    void exportToDot(ostream& os, int& nodeCounter, int parentId = -1) const;
    void exportFullTreeToDot(const string& filename) const;
};

struct Production {
    string lhs;
    vector<string> rhs;
    int productionNumber;

    Production(string lhs, vector<string> rhs, int productionNumber)
        : lhs(lhs), rhs(rhs), productionNumber(productionNumber) {}

    string toString() const { 
        string result = lhs + " -> ";
        for (const auto& symbol : rhs) {
            result += symbol + " ";
        }
        return result;
    }
};

class GrammarAnalyzer {
private:

    vector<Production> productions;
    set<string> terminals;
    set<string> nonTerminals;

    map<string, set<string>> firstSets;
    map<string, set<string>> followSets;

    map<string, map<string, int>> parsingTable;

    const string EPSILON = "ε";
    const string END_MARKER = "$";

    string startSymbol;
public:
    void loadGrammar(const string& grammarFile);

    bool isTerminal(const string& symbol) const;
    bool isNonTerminal(const string& symbol) const;

    const string& getStartSymbol() const { return startSymbol; }
    const string& getEpsilon() const { return EPSILON; }
    const string& getEndMarker() const { return END_MARKER; }
    const int getParseTableEntry(const string& nonTerminal, const string& terminal) const {
        if (parsingTable.find(nonTerminal) == parsingTable.end()) {
            cout << "Non-terminal not found: " << nonTerminal << endl;
            return -1;
        }
        
        auto& innerMap = parsingTable.at(nonTerminal);
        if (innerMap.find(terminal) == innerMap.end()) {
            cout << "Terminal not found for " << nonTerminal << ": " << terminal << endl;
            return -1;
        }
        
        return innerMap.at(terminal);
    }
    const Production& getProduction(int index) const {
        return productions[index];
    }
    const set<string>& getTerminals() const { return terminals; }
    const set<string>& getNonTerminals() const { return nonTerminals; }
    const set<string>& getFirstSet(const string& symbol) const {
        return firstSets.at(symbol);
    }
    const vector<Production>& getProductions() const {
        return productions;
    }
    
    // Debugging
    void printProductions() const;
    void printFirstSets() const;
    void printFollowSets() const;
    void printParsingTable() const;
private:
    void computeFirstSets();
    void computeFollowSets();
    void computeParsingTable();
    set<string> computeFirstOfSequence(const vector<string>& sequence);
};

class LL1Parser {
private:
    set<TokenType> synchronizationTokens = {
        L_TOKEN_SEMICOLON,     // Kết thúc phát biểu (;)
        L_TOKEN_BEGIN,         // Bắt đầu chương trình
        L_TOKEN_END,           // Kết thúc chương trình
        L_TOKEN_LEFT_BRACE,    // Bắt đầu khối lệnh ({)
        L_TOKEN_RIGHT_BRACE,   // Kết thúc khối lệnh (})
        L_TOKEN_IF,            // Bắt đầu phát biểu if
        L_TOKEN_THEN,          // Phần then của if
        L_TOKEN_ELSE,          // Phần else của if
        L_TOKEN_DO,            // Bắt đầu vòng lặp do
        L_TOKEN_WHILE,         // Bắt đầu/kết thúc vòng lặp
        L_TOKEN_FOR,           // Bắt đầu vòng lặp for
        L_TOKEN_PRINT,         // Phát biểu print
        L_TOKEN_INT,           // Khai báo kiểu int
        L_TOKEN_BOOL,          // Khai báo kiểu bool
        L_TOKEN_RIGHT_PAREN    // Kết thúc biểu thức trong ngoặc
    };

    GrammarAnalyzer grammarAnalyzer;
    ErrorReporter errorReporter = ErrorReporter();
    Lexer lexer;
    Token currentToken;

    shared_ptr<ParseTreeNode> parseTree;

    bool parse();
    void skipToToken(TokenType targetToken);

    set<string> computeEpsilonDerivingNonTerminals();
    void skipToSynchronizingToken();
public:
    LL1Parser(const string& grammarFile, const string& inputFile)
        : lexer(inputFile) {
        grammarAnalyzer.loadGrammar(grammarFile);
    }

    bool parseInput() {
        return parse();
    }

    void printParseTree() const {
        if (parseTree) {
            cout << "Parse Tree:" << endl;
            parseTree->printTree();
        } else {
            cout << "No parse tree available." << endl;
        }
    }

    void printErrors() const {
        errorReporter.printErrors();
    }

    void printEnhancedParseTree() const {
        if (parseTree) {
            parseTree->printTreeEnhanced();
        } else {
            cout << "No parse tree available." << endl;
        }
    }
    
    void exportParseTreeToDot(const string& filename) const {
        if (parseTree) {
            parseTree->exportFullTreeToDot(filename);
        } else {
            cout << "No parse tree available to export." << endl;
        }
    }

    void printParsingTable() const {
        grammarAnalyzer.printParsingTable();
    }

    void printProductions() const {
        grammarAnalyzer.printProductions();
    }

    void printFirstSets() const {
        grammarAnalyzer.printFirstSets();
    }

    void printFollowSets() const {
        grammarAnalyzer.printFollowSets();
    }

    void printTerminals() const {
        cout << "Terminals:" << endl;
        for (const auto& terminal : grammarAnalyzer.getTerminals()) {
            cout << terminal << endl;
        }
    }

    void printNonTerminals() const {
        cout << "Non-terminals:" << endl;
        for (const auto& nonTerminal : grammarAnalyzer.getNonTerminals()) {
            cout << nonTerminal << endl;
        }
    }
};