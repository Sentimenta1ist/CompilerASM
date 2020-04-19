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

    string one =  "Consgresss";
    string two = "ons";
    //cout << Hex("10001001b");

    string operand = "012345eax9789";
    for(auto it: RegistersTable){

        size_t found = operand.find(it.reg32Name);
        if(found != string::npos){
            cout << found;

        }
    }

    int q1 = 0b00;
    int q2 = 0b000;
    int q3 = 0b000;

    q1 |= 0b11;
    q2 |= 0b111;
    q3 |= 0b111;
   // cout << Hex((q1 << 3 | q2) << 3 | q3) << endl;
   // cout << q1  << endl;
//    size_t found = one.find(two);
//    if(found != string::npos){
//        cout << "+";
//    }
//    for(int i = 0; i < MassOfUser.size();i++){
//        cout << MassOfUser[i].name << ' '<< MassOfUser[i].type;
//    }

    createAllLst("test.asm");
    for(int i = 0; i < MassOfUser.size();i++){
        cout << MassOfUser[i].name << ' '<< MassOfUser[i].type << ' ' << Hex(MassOfUser[i].displacement,2) << endl;
    }
//    for(int i = 0; i < AllSegments.size(); i++){
//        cout << "name = " << AllSegments[i].name << "; size = " << HexForDisp(AllSegments[i].size) << endl;
//    }






    return 0;
}
