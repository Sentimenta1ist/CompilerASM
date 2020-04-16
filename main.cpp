#include "FirstSecondStage.h"
#include "MachineCode.h"

int main() {

    LoadFromFile("test.asm");
    LexemeSyntax("test.asm" , 0);
    FillMassOfUsers();

    createAllLst("test.asm");
    for(int i = 0; i < AllSegments.size(); i++){
        cout << "name = " << AllSegments[i].name << "; size = " << HexForDisp(AllSegments[i].size) << endl;
    }






    return 0;
}
