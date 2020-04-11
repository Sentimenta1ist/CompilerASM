#include "Parsing.h"

int main() {

    LoadFromFile("test.asm");

    for(int i = 0; i < AllTokens.size(); i++){
        for(int j = 0 ; j < AllTokens[i].size();j++){
            //cout << AllTokens[i][j].name << ' ';
        }
        //cout << endl;
    }
    vector<string> test = {
            {"mov ax,bx"},
            {"mov ax,bx"},
            {"mov ax,bx"},
            {"mov ax,bx"},
            {"mov ax,bx"},
            {"mov ax,bx"},
    };
    for(int i = 0; i < Machine_code.size(); i++){
        cout << Machine_code[i].opcode << ' ';
    }

    return 0;
}
