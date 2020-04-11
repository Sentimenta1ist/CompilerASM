#include "ErrorCheck.h"

vector<error> Accesed{
        {"stosd","-1","-1"},
        {"push","const","-"},
        {"cmp","reg","reg"},
        {"test","reg","mem"},
        {"bts","mem","reg"},
        {"mov","reg","mem"},
        {"add","mem","const"},
        {"jnz","-1","-1"},
};

bool Errortest(vector<lexeme> example){
    for(int i = 0 ; i < example.size(); i++){
        for(int j = 0; j < Accesed.size(); j++) {
            if (example[i].name == Accesed[j].instruction){
                if((Accesed[j].operand1 != example[i + 1].type)||(Accesed[j].operand1 != example[i + 2].type)){
                    return true;
                }
            }
        }
    }
    return false;
}
