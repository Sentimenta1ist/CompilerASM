#include "ErrorCheck.h"

vector<ErrorOfOperands> Accessed{
//        {"stosd",nonOperand,  nonOperand},
//        {"push", const32,nonOperand},
//        {"cmp",  reg32,  reg32},
//        {"test", reg32,  mem32},
//        {"bts",  mem32,  reg32},
//        {"mov",  reg32,  const32},
//        {"add",  mem32,  const32},
//        {"jz",  mem32,nonOperand },
//
//        {"push", const8,nonOperand},
//        {"cmp",  reg8,  reg8},
//        {"test", reg8,  mem8},
//        {"bts",  mem8,  reg8},
//        {"mov",  reg8,  const8},
//        {"add",  mem8,  const8},
//        {"jz",  mem8,nonOperand }
};

bool CheckForUndefined(vector<lexeme> example) {

//    int flag = 0;
//    for (int i = 0; i < example.size(); i++) {
//        if (example[i].type == userId) {
//            flag = 0;
//            for (int j = 0; j < MassOfUser.size(); j++) {
//                if (example[i].name == MassOfUser[j].name) {
//                    flag = 1;
//                    break;
//                }
//            }
//            //example[i].type = undefined;
//            if (flag == 0) {
//                return true;
//            }
//
//        }
//    }
    return false;
}

bool CheckForOperands(vector<lexeme> example){        //return true if n operand with instruction error
    if(example[0].type != instruction) return false;
    LineInstruction alone;
    CreateOperandsForInstruction(example,alone);
    IdentifyOperand(alone);
    int flag_of_error_operands = 1;
    for(auto it: MachineCodeInstruction){
        if(it.op1 == alone.TypeOperand1 && it.op2 == alone.TypeOperand2 && it.name == alone.instr){
            flag_of_error_operands = 0;
        }
    }
    return flag_of_error_operands;
}

bool FullCheckOFLine(vector <lexeme> line){

    if(CheckForUndefined(line)) return true;

    //if(CheckForOperands(line))return true;
    return false;
}


void check(){
    cout << "work";
}
