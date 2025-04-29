#ifndef UPL_TYPES_H
#define UPL_TYPES_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// Định nghĩa cấu trúc cây cú pháp
struct ASTNode {
    std::string type;
    std::string value;
    std::vector<ASTNode*> children;

    ASTNode(std::string t, std::string v = "") : type(t), value(v) {}
    ~ASTNode() {
        for (auto child : children) {
            delete child;
        }
    }
    
    void addChild(ASTNode* child) {
        children.push_back(child);
    }
    
    // Thêm hàm xuất DOT
    void exportDOT(const std::string& filename) const {
        std::ofstream dotFile(filename);
        if (!dotFile.is_open()) {
            std::cerr << "Error: Cannot open file " << filename << " for writing." << std::endl;
            return;
        }
        
        dotFile << "digraph AST {\n";
        dotFile << "  node [shape=box, fontname=\"Arial\", fontsize=10];\n";
        
        int nodeCounter = 0;
        exportDOTNode(dotFile, nodeCounter, -1);
        
        dotFile << "}\n";
        dotFile.close();
        
        std::cout << "AST exported to " << filename << std::endl;
        std::cout << "Use 'dot -Tpng " << filename << " -o ast.png' to generate image." << std::endl;
    }
    
private:
    // Hàm hỗ trợ đệ quy để xuất từng node sang DOT
    void exportDOTNode(std::ofstream& os, int& nodeCounter, int parentId) const {
        int myId = nodeCounter++;
        
        // Tạo label cho node
        std::string nodeLabel = type;
        if (!value.empty()) {
            nodeLabel += "\\n(" + value + ")";
        }
        
        // Tạo node
        os << "  node" << myId << " [label=\"" << nodeLabel << "\"];\n";
        
        // Kết nối với node cha nếu có
        if (parentId != -1) {
            os << "  node" << parentId << " -> node" << myId << ";\n";
        }
        
        // Xuất các node con
        for (const auto& child : children) {
            if (child) {
                child->exportDOTNode(os, nodeCounter, myId);
            }
        }
    }
};

#endif // UPL_TYPES_H