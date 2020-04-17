#include "FirstSecondStage.h"
#include "MachineCode.h"

struct LineInstruction2{
    string instr;
    string operand1;
    string operand2;
    string TypeOperand1;
    string TypeOperand2;
};

int main() {

    LoadFromFile("test.asm");
    LexemeSyntax("test.asm" , 0);
    FillMassOfUsers();
//    for(int i = 0; i < MassOfUser.size();i++){
//        cout << MassOfUser[i].name << ' '<< MassOfUser[i].type;
//    }

    createAllLst("test.asm");
//    for(int i = 0; i < AllSegments.size(); i++){
//        cout << "name = " << AllSegments[i].name << "; size = " << HexForDisp(AllSegments[i].size) << endl;
//    }






    return 0;
}
