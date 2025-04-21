// upl_types.h
#ifndef UPL_TYPES_H
#define UPL_TYPES_H

#include <string>
#include <vector>

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
};

#endif // UPL_TYPES_H