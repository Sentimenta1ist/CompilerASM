#include "ErrorCheck.h"

vector<ErrorOfOperands> Accesed{
        {"stosd","-1",  "-1"},
        {"push", "const","-"},
        {"cmp",  reg,  "reg"},
        {"test", reg,  "mem"},
        {"bts",  "mem",  "reg"},
        {"mov",  reg,  "mem"},
        {"add",  "mem",  reg},
        {"jnz",  "mem",   "-1"},
};

bool CheckForUndefined(vector<lexeme> example) {
    int flag = 0;
    for (int i = 0; i < example.size(); i++) {
        if (example[i].type == userId) {
            flag = 0;
            for (int j = 0; j < MassOfUser.size(); j++) {
                if (example[i].name == MassOfUser[j].name) {
                    flag = 1;
                    break;
                }
            }
            //example[i].type = undefined;
            if (flag == 0) {
                return true;
            }

        }
    }
    return false;
}

bool CheckForOperands(vector<lexeme> example){        //return true if n operand with instruction error
    if(example.empty()) return false;
    if(example[0].type != instruction) return false;
    for(auto it:example) cout << it.name << ' ';
    cout << endl;
    struct_of_sentence alone;

    CreateSyntax(example, alone);
    for(auto it:Accesed){
        if(it.instr == example[0].name){
            if((alone.number_of_operand1 != -1)&&(it.operand1 == "-1"))return false;
        }
    }

    return false;
}
void check(){
    cout << "work";
}
