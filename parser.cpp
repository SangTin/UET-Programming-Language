#include "parser.hpp"

vector<string> splitSymbols(const string& str) {
    vector<string> result;
    stringstream ss(str);
    string token;

    while (ss >> token) {
        result.push_back(token);
    }

    return result;
}

//========================================= ParseTreeNode =========================================
void ParseTreeNode::printTreeEnhanced(int depth, bool isLast) const {
    string indent = "";
    for (int i = 0; i < depth; i++) {
        indent += "│  ";
    }
    
    string connector = isLast ? "└─ " : "├─ ";
    if (depth > 0) {
        cout << indent.substr(0, indent.length() - 4) << connector;
    }
    
    cout << symbol;
    if (!lexeme.empty()) {
        cout << " (" << lexeme << ")";
    }
    cout << endl;
    
    for (size_t i = 0; i < children.size(); i++) {
        children[i]->printTreeEnhanced(depth + 1, i == children.size() - 1);
    }
}

void ParseTreeNode::exportToDot(ostream& os, int& nodeCounter, int parentId) const {
    int myId = nodeCounter++;
    
    // Tạo node
    os << "  node" << myId << " [label=\"" << symbol;
    if (!lexeme.empty()) {
        os << "\\n(" << lexeme << ")";
    }
    os << "\"];" << endl;
    
    // Kết nối với node cha
    if (parentId != -1) {
        os << "  node" << parentId << " -> node" << myId << ";" << endl;
    }
    
    // Tiếp tục với các node con
    for (const auto& child : children) {
        child->exportToDot(os, nodeCounter, myId);
    }
}

void ParseTreeNode::exportFullTreeToDot(const string& filename) const {
    ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        cerr << "Error: Cannot open file " << filename << " for writing." << endl;
        return;
    }
    
    int counter = 0;
    
    dotFile << "digraph ParseTree {" << endl;
    dotFile << "  node [shape=box, fontname=\"Arial\", fontsize=10];" << endl;
    
    exportToDot(dotFile, counter);
    
    dotFile << "}" << endl;
    dotFile.close();
    
    cout << "Parse tree exported to " << filename << endl;
    cout << "Run 'dot -Tpng " << filename << " -o tree.png' to generate image" << endl;
}
//========================================= ParseTreeNode =========================================

//======================================== GrammarAnalyzer ========================================
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
//======================================== GrammarAnalyzer ========================================

//=========================================== LL1Parser ===========================================
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
    
    // Xác định các non-terminal có thể sinh ra epsilon
    set<string> canDeriveEpsilon = computeEpsilonDerivingNonTerminals();
    
    while (!parseStack.empty()) {
        auto [top, nodeId] = parseStack.top();
        parseStack.pop();

        // Xử lý lỗi từ vựng
        if (currentToken.type == TokenType::L_TOKEN_ERROR) {
            errorReporter.reportError(currentToken.line, currentToken.column, currentToken.message);
            
            // Bỏ qua token lỗi và tìm điểm đồng bộ
            currentToken = lexer.nextToken();
            
            while (currentToken.type == TokenType::L_TOKEN_ERROR && !lexer.isAtEnd()) {
                errorReporter.reportError(currentToken.line, currentToken.column, currentToken.message);
                currentToken = lexer.nextToken();
            }
            
            skipToSynchronizingToken();
            
            parseStack.push({top, nodeId});
            continue;
        }

        if (grammarAnalyzer.isTerminal(top) || top == grammarAnalyzer.getEndMarker()) {
            if (top == tokenTypeName(currentToken.type) || 
                (top == grammarAnalyzer.getEndMarker() && currentToken.type == TokenType::L_TOKEN_EOF)) {
                // Khớp terminal
                if (nodeId != -1 && stackNodeMap.find(nodeId) != stackNodeMap.end()) {
                    auto node = stackNodeMap[nodeId];
                    
                    // FIX: Lưu đúng lexeme từ currentToken
                    if (!currentToken.lexeme.empty()) {
                        node->setLexeme(currentToken.lexeme);
                    } else {
                        // Fallback cho các token không có lexeme
                        node->setLexeme(tokenTypeName(currentToken.type));
                    }
                }
                
                if (top != grammarAnalyzer.getEndMarker()) {
                    currentToken = lexer.nextToken();
                }
            } else {
                // Lỗi khớp terminal
                errorReporter.reportError(currentToken.line, currentToken.column, 
                    "Expected " + top + " but found " + tokenTypeName(currentToken.type));
                
                continue;
            }
        } else {
            // Xử lý non-terminal
            int productionNumber = grammarAnalyzer.getParseTableEntry(top, tokenTypeName(currentToken.type));

            if (productionNumber == -1) {
                // Kiểm tra xem non-terminal có thể sinh ra epsilon không
                if (canDeriveEpsilon.find(top) != canDeriveEpsilon.end()) {
                    // Thêm node epsilon vào cây parse nếu cần
                    if (nodeId != -1) {
                        auto& node = stackNodeMap[nodeId];
                        node->production = {grammarAnalyzer.getEpsilon()};
                    }
                    
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

    return !errorReporter.errorsFound() && lexer.isAtEnd();
}

// Phương thức để bỏ qua đến khi gặp token cụ thể
void LL1Parser::skipToToken(TokenType targetToken) {
    while (currentToken.type != targetToken && 
           currentToken.type != TokenType::L_TOKEN_EOF) {
        currentToken = lexer.nextToken();
    }
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

void LL1Parser::skipToSynchronizingToken() {
    while (synchronizationTokens.find(currentToken.type) == synchronizationTokens.end() && 
           currentToken.type != TokenType::L_TOKEN_EOF) {
        currentToken = lexer.nextToken();
    }
}

void LL1Parser::generateIntermediateCode() {
    if (!parseTree) {
        cout << "No parse tree available for code generation." << endl;
        return;
    }
    
    cout << "Starting intermediate code generation..." << endl;
    traverseAndGenerate(parseTree);
}

void LL1Parser::printIntermediateCode() {
    codeGen.printCode();
}

void LL1Parser::traverseAndGenerate(shared_ptr<ParseTreeNode> node) {
    if (!node) return;
    
    if (node->symbol == "if_stmt") {
        handleIfStatement(node);
        return;
    }

    if (node->symbol == "do_while_stmt") {
        handleDoWhile(node);
        return;
    }

    if (node->symbol == "for_stmt") {
        handleForLoop(node);
        return;
    }

    // Xử lý các con trước (bottom-up approach)
    for (auto child : node->children) {
        traverseAndGenerate(child);
    }
    
    // Sinh mã cho node hiện tại dựa trên loại production
    string symbol = node->symbol;
    
    if (symbol == "expression") {
        handleExpression(node);
    } else if (symbol == "addition") {
        handleAddition(node);
    } else if (symbol == "multiplication") {
        handleMultiplication(node);
    } else if (symbol == "factor") {
        handleFactor(node);
    } else if (symbol == "assignment") {
        handleAssignment(node);
    } else if (symbol == "declaration") {
        handleDeclaration(node);
    } else if (symbol == "declaration_tail") {
        handleDeclarationTail(node);
    } else if (symbol == "if_stmt") {
        handleIfStatement(node);
    } else if (symbol == "do_while_stmt") {
        handleDoWhile(node);
    } else if (symbol == "for_stmt") {
        handleForLoop(node);
    } else if (symbol == "print_stmt") {
        handlePrintStatement(node);
    } else if (symbol == "stmt") {
        handleStatement(node);
    } else if (symbol == "stmts") {
        handleStatements(node);
    }
}

void LL1Parser::handleFactor(shared_ptr<ParseTreeNode> node) {
    auto children = node->children;
    
    if (children.size() == 1) {
        auto child = children[0];
        string childSymbol = child->symbol;
        
        if (childSymbol == "IDENTIFIER" || childSymbol == "NUMBER" || 
            childSymbol == "TRUE" || childSymbol == "FALSE") {
            
            string value = child->getLexeme();
            if (value.empty()) {
                // Fallback nếu không có lexeme
                if (childSymbol == "TRUE") value = "true";
                else if (childSymbol == "FALSE") value = "false";
                else value = childSymbol; // Tạm thời
            }
            
            node->setAddr(value);
            node->setCode("");
        }
    } else if (children.size() == 3) {
        // factor -> LEFT_PAREN expression RIGHT_PAREN
        auto expr = children[1]; // expression
        node->setAddr(expr->getAddr());
        node->setCode(expr->getCode());
    }
}

void LL1Parser::handleMultiplication(shared_ptr<ParseTreeNode> node) {
    auto children = node->children;
    
    if (children.size() == 2) {
        // multiplication -> factor multiplication_tail
        auto factor = children[0];        // factor
        auto mult_tail = children[1];     // multiplication_tail
        
        // Bắt đầu với factor
        node->setAddr(factor->getAddr());
        node->setCode(factor->getCode());
        
        // Xử lý multiplication_tail để tạo chuỗi phép nhân
        handleMultiplicationTail(node, mult_tail);
    }
}

void LL1Parser::handleMultiplicationTail(shared_ptr<ParseTreeNode> currentResult, shared_ptr<ParseTreeNode> tailNode) {
    auto children = tailNode->children;
    
    if (children.empty() || (children.size() == 1 && children[0]->symbol == "ε")) {
        // multiplication_tail -> ε (base case)
        return;
    }
    
    if (children.size() == 3) {
        // multiplication_tail -> MULTIPLY factor multiplication_tail
        auto multiply_op = children[0];   // MULTIPLY
        auto factor = children[1];        // factor
        auto next_tail = children[2];     // multiplication_tail
        
        // Tạo temp mới cho phép nhân hiện tại
        string temp = codeGen.newTemp();
        codeGen.emit("*", currentResult->getAddr(), factor->getAddr(), temp);
        
        // Cập nhật kết quả hiện tại
        currentResult->setAddr(temp);
        currentResult->setCode(currentResult->getCode() + factor->getCode());
        
        // Đệ quy xử lý phần tail còn lại
        handleMultiplicationTail(currentResult, next_tail);
    }
}

void LL1Parser::handleAddition(shared_ptr<ParseTreeNode> node) {
    auto children = node->children;
    
    if (children.size() == 2) {
        // addition -> multiplication addition_tail
        auto multiplication = children[0];  // multiplication
        auto add_tail = children[1];        // addition_tail
        
        // Bắt đầu với multiplication
        node->setAddr(multiplication->getAddr());
        node->setCode(multiplication->getCode());
        
        // Xử lý addition_tail để tạo chuỗi phép cộng
        handleAdditionTail(node, add_tail);
    }
}

void LL1Parser::handleAdditionTail(shared_ptr<ParseTreeNode> currentResult, shared_ptr<ParseTreeNode> tailNode) {
    auto children = tailNode->children;
    
    if (children.empty() || (children.size() == 1 && children[0]->symbol == "ε")) {
        // addition_tail -> ε (base case)
        return;
    }
    
    if (children.size() == 3) {
        // addition_tail -> PLUS multiplication addition_tail
        auto plus_op = children[0];       // PLUS
        auto multiplication = children[1]; // multiplication
        auto next_tail = children[2];     // addition_tail
        
        // Tạo temp mới cho phép cộng hiện tại
        string temp = codeGen.newTemp();
        codeGen.emit("+", currentResult->getAddr(), multiplication->getAddr(), temp);
        
        // Cập nhật kết quả hiện tại
        currentResult->setAddr(temp);
        currentResult->setCode(currentResult->getCode() + multiplication->getCode());
        
        // Đệ quy xử lý phần tail còn lại
        handleAdditionTail(currentResult, next_tail);
    }
}

void LL1Parser::handleExpression(shared_ptr<ParseTreeNode> node) {
    auto children = node->children;
    
    if (children.size() == 2) {
        // expression -> addition expression_tail
        auto addition = children[0];      // addition
        auto expr_tail = children[1];     // expression_tail
        
        // Bắt đầu với addition
        node->setAddr(addition->getAddr());
        node->setCode(addition->getCode());
        
        // Xử lý expression_tail để tạo chuỗi phép so sánh
        handleExpressionTail(node, expr_tail);
    }
}

void LL1Parser::handleExpressionTail(shared_ptr<ParseTreeNode> currentResult, shared_ptr<ParseTreeNode> tailNode) {
    auto children = tailNode->children;
    
    if (children.empty() || (children.size() == 1 && children[0]->symbol == "ε")) {
        // expression_tail -> ε (base case)
        return;
    }
    
    if (children.size() == 3) {
        // expression_tail -> relop addition expression_tail
        auto relop = children[0];         // relop (>, >=, ==)
        auto addition = children[1];      // addition
        auto next_tail = children[2];     // expression_tail
        
        // Lấy operator từ relop node
        string op = getRelopOperator(relop);
        
        // Tạo temp mới cho phép so sánh hiện tại
        string temp = codeGen.newTemp();
        codeGen.emit(op, currentResult->getAddr(), addition->getAddr(), temp);
        
        // Cập nhật kết quả hiện tại
        currentResult->setAddr(temp);
        currentResult->setCode(currentResult->getCode() + addition->getCode());
        
        // Đệ quy xử lý phần tail còn lại
        handleExpressionTail(currentResult, next_tail);
    }
}

// Helper method để lấy operator từ relop node
string LL1Parser::getRelopOperator(shared_ptr<ParseTreeNode> relopNode) {
    // relop -> GREATER | GREATER_EQUAL | EQUAL
    if (!relopNode->children.empty()) {
        auto opNode = relopNode->children[0];
        string opSymbol = opNode->symbol;
        
        if (opSymbol == "GREATER") return ">";
        else if (opSymbol == "GREATER_EQUAL") return ">=";
        else if (opSymbol == "EQUAL") return "==";
    }
    return ">"; // default
}

void LL1Parser::handleAssignment(shared_ptr<ParseTreeNode> node) {
    auto children = node->children;
    
    if (children.size() == 3) {
        // assignment -> IDENTIFIER ASSIGN expression
        auto id = children[0];      // IDENTIFIER
        auto assign = children[1];  // ASSIGN
        auto expr = children[2];    // expression
        
        string varName = id->getLexeme().empty() ? id->symbol : id->getLexeme();
        
        codeGen.emit("=", expr->getAddr(), "", varName);
        
        string code = expr->getCode();
        node->setCode(code);
    }
}

void LL1Parser::handleDeclaration(shared_ptr<ParseTreeNode> node) {
    auto children = node->children;
    
    if (children.size() == 2) {
        // declaration -> dtype declaration_tail
        auto dtype = children[0];         // dtype (int/bool)
        auto decl_tail = children[1];     // declaration_tail
        
        // Chuyển tiếp code từ declaration_tail (nếu có assignment)
        node->setCode(decl_tail->getCode());
    }
}

void LL1Parser::handleDeclarationTail(shared_ptr<ParseTreeNode> node) {
    auto children = node->children;
    
    if (children.size() == 2) {
        // declaration_tail -> IDENTIFIER id_tail
        auto identifier = children[0];    // IDENTIFIER
        auto id_tail = children[1];       // id_tail
        
        // Xử lý id_tail để xem có assignment không
        handleIdTail(identifier, id_tail, node);
    }
}

void LL1Parser::handleIdTail(shared_ptr<ParseTreeNode> identifier, 
                             shared_ptr<ParseTreeNode> idTailNode, 
                             shared_ptr<ParseTreeNode> resultNode) {
    auto children = idTailNode->children;
    
    if (children.empty() || (children.size() == 1 && children[0]->symbol == "ε")) {
        // id_tail -> ε (chỉ khai báo, không khởi tạo)
        resultNode->setCode("");
    } else if (children.size() == 2) {
        // id_tail -> ASSIGN expression
        auto assign = children[0];        // ASSIGN
        auto expression = children[1];    // expression
        
        string varName = identifier->getLexeme().empty() ? identifier->symbol : identifier->getLexeme();
        
        // Sinh mã gán giá trị khởi tạo
        codeGen.emit("=", expression->getAddr(), "", varName);
        
        string code = expression->getCode();
        resultNode->setCode(code);
    }
}

void LL1Parser::handleStatement(shared_ptr<ParseTreeNode> node) {
    // stmt có thể chứa các loại statement khác nhau
    // Chuyển tiếp code từ statement con
    string code = "";
    for (auto child : node->children) {
        code += child->getCode();
    }
    node->setCode(code);
}

void LL1Parser::handleStatements(shared_ptr<ParseTreeNode> node) {
    // stmts -> stmt stmts_tail hoặc epsilon
    string code = "";
    for (auto child : node->children) {
        code += child->getCode();
    }
    node->setCode(code);
}

void LL1Parser::handlePrintStatement(shared_ptr<ParseTreeNode> node) {
    auto children = node->children;
    
    // print_stmt -> PRINT LEFT_PAREN expression RIGHT_PAREN
    if (children.size() == 4) {
        auto expr = children[2]; // expression
        
        codeGen.emit("param", expr->getAddr());
        codeGen.emit("call", "print", "1");
        
        node->setCode(expr->getCode());
    }
}

void LL1Parser::handleDoWhile(shared_ptr<ParseTreeNode> node) {
    auto children = node->children;
    
    // do_while_stmt -> DO stmt WHILE LEFT_PAREN expression RIGHT_PAREN
    if (children.size() >= 6) {
        auto doKeyword = children[0];    // DO
        auto stmt = children[1];         // stmt (body của loop)
        auto whileKeyword = children[2]; // WHILE
        auto leftParen = children[3];    // LEFT_PAREN
        auto condition = children[4];    // expression (điều kiện)
        auto rightParen = children[5];   // RIGHT_PAREN
        
        string startLabel = codeGen.newLabel();
        
        // 1. Đặt nhãn bắt đầu loop
        codeGen.emit("label", "", "", "", startLabel);
        
        // 2. Traverse và sinh mã cho body trước
        traverseAndGenerate(stmt);
        
        // 3. Traverse và sinh mã cho condition
        traverseAndGenerate(condition);
        
        // 4. Kiểm tra condition có addr không
        if (condition->getAddr().empty()) {
            cout << "ERROR: Do-while condition không có addr!" << endl;
            return;
        }
        
        // 5. Sinh mã jump về đầu loop nếu condition = true
        codeGen.emit("if", condition->getAddr(), "", "", startLabel);
        node->setCode("");
    } else {
        cout << "ERROR: do-while structure không đúng, có " << children.size() << " children" << endl;
    }
}

void LL1Parser::handleForLoop(shared_ptr<ParseTreeNode> node) {
    auto children = node->children;
    
    // for_stmt -> FOR LEFT_PAREN for_init SEMICOLON for_condition SEMICOLON for_update RIGHT_PAREN stmt
    if (children.size() >= 9) {
        auto forKeyword = children[0];    // FOR
        auto leftParen = children[1];     // LEFT_PAREN
        auto forInit = children[2];       // for_init
        auto semicolon1 = children[3];    // SEMICOLON
        auto forCondition = children[4];  // for_condition
        auto semicolon2 = children[5];    // SEMICOLON
        auto forUpdate = children[6];     // for_update
        auto rightParen = children[7];    // RIGHT_PAREN
        auto stmt = children[8];          // stmt (body của loop)
        
        // Tạo labels
        string conditionLabel = codeGen.newLabel();  // Nhãn kiểm tra điều kiện
        string endLabel = codeGen.newLabel();        // Nhãn kết thúc loop
        
        // 1. Sinh mã cho initialization
        if (hasForInit(forInit)) {
            traverseAndGenerate(forInit);
        }
        
        // 2. Nhãn kiểm tra điều kiện
        codeGen.emit("label", "", "", "", conditionLabel);

        // 3. Sinh mã cho condition và jump
        if (hasForCondition(forCondition)) {
            traverseAndGenerate(forCondition);

            // Lấy addr của condition từ expression bên trong for_condition
            auto conditionExpr = findChild(forCondition, "expression");
            if (conditionExpr && !conditionExpr->getAddr().empty()) {
                codeGen.emit("ifFalse", conditionExpr->getAddr(), "", "", endLabel);
            }
        }
        
        // 4. Sinh mã cho body
        traverseAndGenerate(stmt);
        
        // 5. Sinh mã update
        if (hasForUpdate(forUpdate)) {
            traverseAndGenerate(forUpdate);
        }
        
        // 6. Nhãn kết thúc (optional, có thể dùng cho break statement)
        codeGen.emit("label", "", "", "", endLabel);
        node->setCode("");
    } else {
        cout << "ERROR: for-loop structure không đúng, có " << children.size() << " children" << endl;
    }
}

bool LL1Parser::hasForInit(shared_ptr<ParseTreeNode> forInitNode) {
    if (!forInitNode || forInitNode->children.empty()) {
        return false;
    }
    
    // for_init -> declaration | assignment | ε
    return forInitNode->children.size() > 0 && 
           forInitNode->children[0]->symbol != "ε";
}

bool LL1Parser::hasForCondition(shared_ptr<ParseTreeNode> forConditionNode) {
    if (!forConditionNode || forConditionNode->children.empty()) {
        return false;
    }
    
    // for_condition -> expression | ε
    return forConditionNode->children.size() > 0 && 
           forConditionNode->children[0]->symbol != "ε";
}

bool LL1Parser::hasForUpdate(shared_ptr<ParseTreeNode> forUpdateNode) {
    if (!forUpdateNode || forUpdateNode->children.empty()) {
        return false;
    }
    
    // for_update -> assignment | ε
    return forUpdateNode->children.size() > 0 && 
           forUpdateNode->children[0]->symbol != "ε";
}

void LL1Parser::handleIfStatement(shared_ptr<ParseTreeNode> node) {
    auto children = node->children;
    
    // if_stmt -> IF LEFT_PAREN expression RIGHT_PAREN THEN LEFT_BRACE stmts RIGHT_BRACE else_part
    if (children.size() >= 8) {
        auto condition = children[2];    // expression
        auto thenStmts = children[6];    // stmts trong then block
        
        traverseAndGenerate(condition);

        // Tìm else_part - có thể ở vị trí 8 hoặc cuối
        shared_ptr<ParseTreeNode> elsePart = nullptr;
        for (size_t i = 8; i < children.size(); i++) {
            if (children[i]->symbol == "else_part") {
                elsePart = children[i];
                break;
            }
        }
        
        string elseLabel = codeGen.newLabel();
        string endLabel = codeGen.newLabel();
        
        if (condition->getAddr().empty()) {
            cout << "ERROR: Condition không có addr!" << endl;
            return;
        }
        
        // 2. Kiểm tra có else không
        if (elsePart && hasElseBlock(elsePart)) {
            // if-then-else
            codeGen.emit("ifFalse", condition->getAddr(), "", "", elseLabel);
            
            // 3. Sinh mã cho then block
            traverseAndGenerateStatements(thenStmts);
            codeGen.emit("goto", "", "", "", endLabel);
            
            // 4. Sinh mã cho else block
            codeGen.emit("label", "", "", "", elseLabel);
            generateElseCode(elsePart);
            codeGen.emit("label", "", "", "", endLabel);
            
        } else {
            // if-then only
            codeGen.emit("ifFalse", condition->getAddr(), "", "", endLabel);
            
            // 3. Sinh mã cho then block
            traverseAndGenerateStatements(thenStmts);
            codeGen.emit("label", "", "", "", endLabel);
        }
        
        node->setCode("");
    }
}

// Helper methods
bool LL1Parser::hasElseBlock(shared_ptr<ParseTreeNode> elsePart) {
    if (!elsePart || elsePart->children.empty()) {
        return false;
    }
    
    // else_part -> ELSE LEFT_BRACE stmts RIGHT_BRACE | ε
    return elsePart->children.size() >= 4;
}

void LL1Parser::generateElseCode(shared_ptr<ParseTreeNode> elsePart) {
    if (!elsePart || elsePart->children.size() < 4) return;
    
    // else_part -> ELSE LEFT_BRACE stmts RIGHT_BRACE
    auto elseStmts = elsePart->children[2]; // stmts
    traverseAndGenerateStatements(elseStmts);
}

void LL1Parser::traverseAndGenerateStatements(shared_ptr<ParseTreeNode> stmtsNode) {
    if (!stmtsNode) return;
    
    // stmts -> stmt stmts_tail | ε
    auto children = stmtsNode->children;
    
    for (auto child : children) {
        if (child->symbol == "stmt") {
            traverseAndGenerate(child);
        } else if (child->symbol == "stmts_tail") {
            traverseAndGenerateStatements(child);
        }
    }
}

shared_ptr<ParseTreeNode> LL1Parser::findChild(shared_ptr<ParseTreeNode> parent, const string& symbol) {
    if (!parent) return nullptr;
    
    for (auto child : parent->children) {
        if (child->symbol == symbol) {
            return child;
        }
    }
    return nullptr;
}

vector<shared_ptr<ParseTreeNode>> LL1Parser::findChildren(shared_ptr<ParseTreeNode> parent, const string& symbol) {
    vector<shared_ptr<ParseTreeNode>> result;
    if (!parent) return result;
    
    for (auto child : parent->children) {
        if (child->symbol == symbol) {
            result.push_back(child);
        }
    }
    return result;
}

bool LL1Parser::isTerminal(const string& symbol) {
    // Kiểm tra xem symbol có phải terminal không
    return symbol.find("TOKEN") != string::npos || 
           symbol == "IDENTIFIER" || symbol == "NUMBER" ||
           symbol == "TRUE" || symbol == "FALSE" ||
           symbol == "PLUS" || symbol == "MULTIPLY" ||
           symbol == "ASSIGN" || symbol == "SEMICOLON";
}
//=========================================== LL1Parser ===========================================