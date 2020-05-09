#include "FirstSecondStage.h"
#include "MachineCode.h"


int main() {
    LoadFromFile("test.asm");
    LexemeSyntax("test.asm" , 0);
    createAllLst("test.asm");

    return 0;
}
