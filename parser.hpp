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
        L_TOKEN_BEGIN, L_TOKEN_END, L_TOKEN_IF, L_TOKEN_THEN, L_TOKEN_ELSE,
        L_TOKEN_DO, L_TOKEN_WHILE, L_TOKEN_FOR, L_TOKEN_PRINT,
        L_TOKEN_INT, L_TOKEN_BOOL, L_TOKEN_LEFT_BRACE, L_TOKEN_RIGHT_BRACE,
        L_TOKEN_SEMICOLON
    };

    GrammarAnalyzer grammarAnalyzer;
    ErrorReporter errorReporter = ErrorReporter();
    Lexer lexer;
    Token currentToken;

    shared_ptr<ParseTreeNode> parseTree;

    bool parse();
    void skipToToken(TokenType targetToken);
    bool isContextualNonTerminal(const string& symbol);

    void reportError(const string& message) {
        errorReporter.reportError(currentToken.line, currentToken.column, message);
    }

    set<string> computeEpsilonDerivingNonTerminals();
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
};