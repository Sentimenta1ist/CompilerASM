#include "ErrorCheck.h"
#include "FirstSecondStage.h"

int main() {

    LoadFromFile("test.asm");

    LexemeSyntax("test.asm" , 0);




    FillMassOfUsers();
    LexemeSyntax("test.asm" , 1);

    for(int i = 0; i < AllTokens.size(); i++){
        if(AllTokens[i].empty())continue;
        cout << Hex(DispMain);
        Diplacement(AllTokens[i]);
        for(int j = 0 ; j < AllTokens[i].size();j++){
            cout << AllTokens[i][j].name << ' ';
        }
        cout << endl;
    }

    for(int i = 0; i < MassOfUser.size(); i++){
        cout << MassOfUser[i].name << "   " <<   Hex(MassOfUser[i].disp) << endl;
    }


    return 0;
}
