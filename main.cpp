#include "FirstSecondStage.h"
#include "MachineCode.h"




int main() {
    LoadFromFile("test.asm");
    LexemeSyntax("test.asm" , 0);
    FillMassOfUsers();
    IfDirectiveWorking();
    createAllLst("test.asm");
    //cout << Dec("0a");
    return 0;
}
