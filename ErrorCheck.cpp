#include "ErrorCheck.h"

vector<ErrorOfOperands> Accesed{
        {"stosd","-1",  "-1"},
        {"push", "const","-"},
        {"cmp",  "reg",  "reg"},
        {"test", "reg",  "mem"},
        {"bts",  "mem",  "reg"},
        {"mov",  "reg",  "mem"},
        {"add",  "mem",  "const"},
        {"jnz",  "-1",   "-1"},
};

bool Errortest(vector<lexeme> example){
    int flag = 0;
    for(int i = 0; i < example.size(); i++){
        if(example[i].type == userId) {
            flag = 0;
            for (int j = 0; j < MassOfUser.size(); j++) {
                if (example[i].name == MassOfUser[j].name) {
                    flag = 1;
                    break;
                }
            }
            if(flag == 0) return true;
        }
    }




    return false;
}

void Diplacement(vector<lexeme> example) {
    if(Errortest(example)){
        cout << "* error! *      |" ;
        return;
    }
    cout << "                |" ;
    DispMain++;
}