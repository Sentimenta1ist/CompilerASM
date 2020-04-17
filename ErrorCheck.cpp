#include "ErrorCheck.h"

vector<ErrorOfOperands> Accessed{
        {"stosd",nonOperand,  nonOperand},
        {"push", const32,nonOperand},
        {"cmp",  reg32,  reg32},
        {"test", reg32,  mem32},
        {"bts",  mem32,  reg32},
        {"mov",  reg32,  const32},
        {"add",  mem32,  const32},
        {"jz",  mem32,nonOperand },

        {"push", const8,nonOperand},
        {"cmp",  reg8,  reg8},
        {"test", reg8,  mem8},
        {"bts",  mem8,  reg8},
        {"mov",  reg8,  const8},
        {"add",  mem8,  const8},
        {"jz",  mem8,nonOperand }
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
    return false;
}

bool FullCheckOFLine(vector <lexeme> line){
    if(CheckForOperands(line))return true;
    if(CheckForUndefined(line)) return true;
    return false;
}


void check(){
    cout << "work";
}
