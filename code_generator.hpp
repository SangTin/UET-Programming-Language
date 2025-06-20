#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct ThreeAddressInstruction {
    string op;      // Toán tử hoặc loại lệnh
    string arg1;    // Toán hạng 1
    string arg2;    // Toán hạng 2 (có thể rỗng)
    string result;  // Kết quả (có thể rỗng)
    string label;   // Nhãn (cho goto, if, etc.)
    
    ThreeAddressInstruction(string operation, string argument1 = "", 
                           string argument2 = "", string res = "", string lab = "")
        : op(operation), arg1(argument1), arg2(argument2), result(res), label(lab) {}
    
    string toString() const {
        if (op == "label") {
            return label + ":";
        } else if (op == "goto") {
            return "goto " + label;
        } else if (op == "if") {
            return "if " + arg1 + " goto " + label;
        } else if (op == "ifFalse") {
            return "ifFalse " + arg1 + " goto " + label;
        } else if (op == "if_relop") {
            return "if " + arg1 + " " + arg2 + " " + result + " goto " + label;
        } else if (op == "param") {
            return "param " + arg1;
        } else if (op == "call") {
            return "call " + arg1 + ", " + arg2;
        } else if (op == "return") {
            return "return " + (arg1.empty() ? "" : arg1);
        } else if (op == "=") {
            return result + " = " + arg1;
        } else {
            return result + " = " + arg1 + " " + op + " " + arg2;
        }
    }
};

class CodeGenerator {
private:
    vector<ThreeAddressInstruction> instructions;
    int tempCounter;
    int labelCounter;

public:
    CodeGenerator() : tempCounter(0), labelCounter(0) {}
    
    string newTemp() {
        return "t" + to_string(++tempCounter);
    }
    
    string newLabel() {
        return "L" + to_string(++labelCounter);
    }
    
    void emit(string op, string arg1 = "", string arg2 = "", string result = "", string label = "") {
        instructions.push_back(ThreeAddressInstruction(op, arg1, arg2, result, label));
    }
    
    void printCode() const {
        cout << "=== Three-Address Code ===" << endl;
        for (const auto& instr : instructions) {
            cout << instr.toString() << endl;
        }
    }
    
    vector<ThreeAddressInstruction>& getInstructions() { 
        return instructions; 
    }
    
    void clear() {
        instructions.clear();
        tempCounter = 0;
        labelCounter = 0;
    }
};

#endif