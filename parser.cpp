#include "parser.hpp"

void reportError(const string& message) {
    cerr << "Error: " << message << endl;
}

vector<string> splitSymbols(const string& str) {
    vector<string> result;
    stringstream ss(str);
    string token;

    while (ss >> token) {
        result.push_back(token);
    }

    return result;
}

bool GrammarAnalyzer::isTerminal(const string& symbol) const {
    return terminals.find(symbol) != terminals.end();
}

bool GrammarAnalyzer::isNonTerminal(const string& symbol) const {
    return nonTerminals.find(symbol) != nonTerminals.end();
}

void GrammarAnalyzer::loadGrammar(const string& grammarFile) {
    ifstream file(grammarFile);
    if (!file.is_open()) {
        cerr << "Error opening grammar file: " << grammarFile << endl;
        return;
    }

    string line;
    int productionNumber = 0;

    while (getline(file, line)) {
        trim(line);
        if (line.empty() || line[0] == '#') continue;

        auto parts = splitSymbols(line);
        if (parts.size() < 3 || parts[1] != "->") {
            cerr << "Invalid production format: " << line << endl;
            continue;
        }

        string lhs = parts[0];
        vector<string> rhs(parts.begin() + 2, parts.end());
        productions.emplace_back(lhs, rhs, productionNumber++);

        nonTerminals.insert(lhs);
        terminals.erase(lhs);

        for (const auto& symbol : rhs) {
            if (symbol != EPSILON && symbol != END_MARKER) {
                if (!isNonTerminal(symbol)) {
                    terminals.insert(symbol);
                }
            }
        }
    }

    // Giả sử ký hiệu đầu tiên trong danh sách sản xuất là ký hiệu bắt đầu
    if (!productions.empty()) {
        startSymbol = productions[0].lhs;
    }

    file.close();

    computeFirstSets();
    computeFollowSets();
    computeParsingTable();
}

void GrammarAnalyzer::computeFirstSets() {
    // Khởi tạo tập FIRST rỗng cho mọi ký hiệu không kết thúc
    for (const auto& nonTerminal : nonTerminals) {
        firstSets[nonTerminal] = {};
    }
    
    // Khởi tạo tập FIRST cho các ký hiệu kết thúc
    for (const auto& terminal : terminals) {
        firstSets[terminal] = {terminal};
    }
    
    // Thêm epsilon vào firstSet của epsilon
    firstSets[EPSILON] = {EPSILON};
    
    bool changed = true;
    while (changed) {
        changed = false;
        
        for (const auto& production : productions) {
            string lhs = production.lhs;
            const auto& rhs = production.rhs;
            
            // Trường hợp: X -> ε
            if (rhs.size() == 1 && rhs[0] == EPSILON) {
                if (firstSets[lhs].insert(EPSILON).second) {
                    changed = true;
                }
                continue;
            }
            
            // Trường hợp: X -> Y1 Y2 ... Yn
            bool allCanDeriveEpsilon = true;
            for (size_t i = 0; i < rhs.size(); ++i) {
                const string& Yi = rhs[i];
                
                // Thêm FIRST(Yi) - {ε} vào FIRST(X)
                bool YiHasEpsilon = false;
                for (const auto& symbol : firstSets[Yi]) {
                    if (symbol != EPSILON) {
                        if (firstSets[lhs].insert(symbol).second) {
                            changed = true;
                        }
                    } else {
                        YiHasEpsilon = true;
                    }
                }
                
                // Nếu Yi không thể sinh ra epsilon, dừng lại
                if (!YiHasEpsilon) {
                    allCanDeriveEpsilon = false;
                    break;
                }
            }
            
            // Nếu tất cả Y1..Yn đều có thể sinh ra epsilon, thêm epsilon vào FIRST(X)
            if (allCanDeriveEpsilon) {
                if (firstSets[lhs].insert(EPSILON).second) {
                    changed = true;
                }
            }
        }
    }
}

set<string> GrammarAnalyzer::computeFirstOfSequence(const vector<string>& sequence) {
    set<string> result;
    
    if (sequence.empty()) {
        result.insert(EPSILON);
        return result;
    }
    
    bool allCanDeriveEpsilon = true;
    for (const auto& symbol : sequence) {
        bool symbolHasEpsilon = false;
        
        for (const auto& firstSymbol : firstSets[symbol]) {
            if (firstSymbol != EPSILON) {
                result.insert(firstSymbol);
            } else {
                symbolHasEpsilon = true;
            }
        }
        
        if (!symbolHasEpsilon) {
            allCanDeriveEpsilon = false;
            break;
        }
    }
    
    if (allCanDeriveEpsilon) {
        result.insert(EPSILON);
    }
    
    return result;
}

void GrammarAnalyzer::computeFollowSets() {
    // Khởi tạo tập FOLLOW rỗng cho mọi ký hiệu không kết thúc
    for (const auto& nonTerminal : nonTerminals) {
        followSets[nonTerminal] = {};
    }
    
    // Thêm $ vào FOLLOW của ký hiệu bắt đầu
    followSets[startSymbol].insert(END_MARKER);
    
    bool changed = true;
    while (changed) {
        changed = false;
        
        for (const auto& production : productions) {
            string lhs = production.lhs;
            const auto& rhs = production.rhs;
            
            for (size_t i = 0; i < rhs.size(); ++i) {
                const string& current = rhs[i];
                
                // Chỉ quan tâm đến các ký hiệu không kết thúc
                if (!isNonTerminal(current)) continue;
                
                // Trường hợp: A -> αBβ, thêm FIRST(β) - {ε} vào FOLLOW(B)
                vector<string> beta(rhs.begin() + i + 1, rhs.end());
                set<string> firstOfBeta = computeFirstOfSequence(beta);
                
                for (const auto& symbol : firstOfBeta) {
                    if (symbol != EPSILON) {
                        if (followSets[current].insert(symbol).second) {
                            changed = true;
                        }
                    }
                }
                
                // Nếu FIRST(β) chứa ε, thêm FOLLOW(A) vào FOLLOW(B) hoặc trường hợp A -> αB
                if (firstOfBeta.count(EPSILON) > 0) {
                    for (const auto& symbol : followSets[lhs]) {
                        if (followSets[current].insert(symbol).second) {
                            changed = true;
                        }
                    }
                }
            }
        }
    }
}

void GrammarAnalyzer::computeParsingTable() {
    for (const auto& nonTerminal : nonTerminals) {
        for (const auto& terminal : terminals) {
            parsingTable[nonTerminal][terminal] = -1;
        }
        parsingTable[nonTerminal][END_MARKER] = -1;
    }

    for (const auto& production : productions) {
        string A = production.lhs;
        const auto& alpha = production.rhs;
        int productionNumber = production.productionNumber;

        // Quy tắc 1: Với mọi a ∈ FIRST(α), thêm A -> α vào M[A, a]
        set<string> firstOfAlpha = computeFirstOfSequence(alpha);
        for (const auto& symbol : firstOfAlpha) {
            if (symbol != EPSILON) {
                parsingTable[A][symbol] = productionNumber;
            }
        }

        // Quy tắc 2: Nếu ε ∈ FIRST(α), với mọi b ∈ FOLLOW(A), thêm A -> α vào M[A, b]
        if (firstOfAlpha.count(EPSILON) > 0) {
            for (const auto& b : followSets[A]) {
                if (parsingTable[A][b] != -1) {
                    std::cerr << "Xung đột trong bảng LL(1) tại [" << A << ", " << b << "]" << std::endl;
                    std::cerr << "  Đã có: " << parsingTable[A][b] << ", muốn thêm: " << productionNumber << std::endl;
                } else {
                    parsingTable[A][b] = productionNumber;
                }
            }
        }
    }
}

void GrammarAnalyzer::printProductions() const {
    for (const auto& production : productions) {
        cout << production.toString() << endl;
    }
}

void GrammarAnalyzer::printFirstSets() const {
    cout << "FIRST Sets:" << endl;
    for (const auto& entry : firstSets) {
        if (isTerminal(entry.first) || entry.first == EPSILON) {
            continue; // Bỏ qua các ký hiệu kết thúc
        }
        
        cout << entry.first << ": { ";
        for (const auto& symbol : entry.second) {
            cout << symbol << " ";
        }
        cout << "}" << endl;
    }
}

void GrammarAnalyzer::printFollowSets() const {
    cout << "FOLLOW Sets:" << endl;
    for (const auto& entry : followSets) {
        cout << entry.first << ": { ";
        for (const auto& symbol : entry.second) {
            cout << symbol << " ";
        }
        cout << "}" << endl;
    }
}

void GrammarAnalyzer::printParsingTable() const {
    std::cout << "LL(1) Parsing Table:" << std::endl;
    
    std::cout << std::setw(10) << " ";
    for (const auto& terminal : terminals) {
        std::cout << std::setw(10) << terminal;
    }
    std::cout << std::setw(10) << END_MARKER << std::endl;
    
    for (const auto& nonTerminal : nonTerminals) {
        std::cout << std::setw(10) << nonTerminal;
        
        for (const auto& terminal : terminals) {
            try {
                int productionNumber = parsingTable.at(nonTerminal).at(terminal);
                if (productionNumber >= 0) {
                    std::cout << std::setw(10) << productionNumber;
                } else {
                    std::cout << std::setw(10) << "";
                }
            } catch (const std::out_of_range&) {
                std::cout << std::setw(10) << "error";
            }
        }
        
        try {
            int productionNumber = parsingTable.at(nonTerminal).at(END_MARKER);
            if (productionNumber >= 0) {
                std::cout << std::setw(10) << productionNumber;
            } else {
                std::cout << std::setw(10) << "";
            }
        } catch (const std::out_of_range&) {
            std::cout << std::setw(10) << "error";
        }
        
        std::cout << std::endl;
    }
}

bool LL1Parser::parse() {
    // Khởi tạo như trước
    map<int, shared_ptr<ParseTreeNode>> stackNodeMap;
    stack<pair<string, int>> parseStack;
    int nextNodeId = 0;
    
    parseTree = make_shared<ParseTreeNode>(grammarAnalyzer.getStartSymbol());
    stackNodeMap[nextNodeId] = parseTree;
    
    parseStack.push({grammarAnalyzer.getEndMarker(), -1});
    parseStack.push({grammarAnalyzer.getStartSymbol(), nextNodeId++});

    currentToken = lexer.nextToken();
    bool hasErrors = false;
    
    // Xác định các non-terminal có thể sinh ra epsilon
    set<string> canDeriveEpsilon = computeEpsilonDerivingNonTerminals();
    
    while (!parseStack.empty() && !lexer.isAtEnd()) {
        auto [top, nodeId] = parseStack.top();
        parseStack.pop();

        // Xử lý lỗi từ vựng
        if (currentToken.type == TokenType::L_TOKEN_ERROR) {
            reportError("Lexical error: " + currentToken.message + 
                      " at line " + to_string(currentToken.line));
            hasErrors = true;
            currentToken = lexer.nextToken();
            continue;
        }

        if (grammarAnalyzer.isTerminal(top) || top == grammarAnalyzer.getEndMarker()) {
            if (top == tokenTypeName(currentToken.type) || 
                (top == grammarAnalyzer.getEndMarker() && currentToken.type == TokenType::L_TOKEN_EOF)) {
                // Xử lý khớp terminal như cũ
                if (nodeId != -1) {
                    auto terminalNode = make_shared<ParseTreeNode>(top);
                    terminalNode->lexeme = currentToken.lexeme;
                    stackNodeMap[nodeId]->addChild(terminalNode);
                }
                
                if (top != grammarAnalyzer.getEndMarker()) {
                    currentToken = lexer.nextToken();
                }
            } else {
                // Lỗi khớp terminal
                reportError("Expected " + top + " but found " + tokenTypeName(currentToken.type) + 
                          " at line " + to_string(currentToken.line));
                hasErrors = true;
                
                // Giả sử bỏ qua terminal this và tiếp tục
                continue;
            }
        } else {
            // Xử lý non-terminal
            int productionNumber = grammarAnalyzer.getParseTableEntry(top, tokenTypeName(currentToken.type));

            if (productionNumber == -1) {
                // Lỗi không tìm thấy quy tắc sản xuất
                reportError("No production for " + top + " with " + 
                          tokenTypeName(currentToken.type) + " at line " + to_string(currentToken.line));
                hasErrors = true;
                
                // Cách 2: Kiểm tra xem non-terminal có thể sinh ra epsilon không
                if (canDeriveEpsilon.find(top) != canDeriveEpsilon.end()) {
                    // Áp dụng quy tắc epsilon - không đẩy gì vào stack, bỏ qua non-terminal này
                    reportError("Assuming " + top + " derives epsilon at line " + 
                              to_string(currentToken.line));
                    
                    // Thêm node epsilon vào cây parse nếu cần
                    if (nodeId != -1) {
                        auto& node = stackNodeMap[nodeId];
                        node->production = {grammarAnalyzer.getEpsilon()};
                    }
                    
                    // Tiếp tục mà không đẩy gì vào stack
                    continue;
                } else {
                    // Nếu không thể sinh ra epsilon, bỏ qua token hiện tại
                    currentToken = lexer.nextToken();
                    // Đẩy lại non-terminal vào stack
                    parseStack.push({top, nodeId});
                }
            } else {
                // Áp dụng quy tắc sản xuất như cũ
                const auto& production = grammarAnalyzer.getProduction(productionNumber);
                
                // Cập nhật node trong cây parse
                if (nodeId != -1) {
                    auto& node = stackNodeMap[nodeId];
                    node->production = production.rhs;
                    
                    // Tạo các node con
                    vector<shared_ptr<ParseTreeNode>> childNodes;
                    for (const auto& symbol : production.rhs) {
                        if (symbol != grammarAnalyzer.getEpsilon()) {
                            auto childNode = make_shared<ParseTreeNode>(symbol);
                            node->addChild(childNode);
                            childNodes.push_back(childNode);
                        }
                    }
                    
                    // Đẩy quy tắc sản xuất vào stack
                    for (int i = production.rhs.size() - 1; i >= 0; i--) {
                        if (production.rhs[i] != grammarAnalyzer.getEpsilon()) {
                            int childNodeId = nextNodeId++;
                            stackNodeMap[childNodeId] = childNodes[i];
                            parseStack.push({production.rhs[i], childNodeId});
                        }
                    }
                } else {
                    // Trường hợp không cần xây dựng node
                    for (auto it = production.rhs.rbegin(); it != production.rhs.rend(); ++it) {
                        if (*it != grammarAnalyzer.getEpsilon()) {
                            parseStack.push({*it, -1});
                        }
                    }
                }
            }
        }
    }

    return !hasErrors && lexer.isAtEnd();
}

// Phương thức để bỏ qua đến khi gặp token cụ thể
void LL1Parser::skipToToken(TokenType targetToken) {
    while (currentToken.type != targetToken && 
           currentToken.type != TokenType::L_TOKEN_EOF) {
        currentToken = lexer.nextToken();
    }
}

// Kiểm tra xem non-terminal có phải là một phần quan trọng của ngữ cảnh phân tích
bool LL1Parser::isContextualNonTerminal(const string& symbol) {
    static set<string> contextualSymbols = {
        "stmt", "stmts", "if_stmt", "for_stmt", "do_while_stmt", 
        "block_stmt", "expression"
    };
    
    return contextualSymbols.find(symbol) != contextualSymbols.end();
}

set<string> LL1Parser::computeEpsilonDerivingNonTerminals() {
    set<string> result;
    
    // Duyệt qua tất cả các quy tắc sản xuất
    for (const auto& production : grammarAnalyzer.getProductions()) {
        // Kiểm tra nếu quy tắc trực tiếp sinh ra epsilon
        if (production.rhs.size() == 1 && production.rhs[0] == grammarAnalyzer.getEpsilon()) {
            result.insert(production.lhs);
        }
    }
    
    // Kiểm tra từ tập FIRST
    for (const auto& nonTerminal : grammarAnalyzer.getNonTerminals()) {
        const auto& firstSet = grammarAnalyzer.getFirstSet(nonTerminal);
        if (firstSet.find(grammarAnalyzer.getEpsilon()) != firstSet.end()) {
            result.insert(nonTerminal);
        }
    }
    
    return result;
}