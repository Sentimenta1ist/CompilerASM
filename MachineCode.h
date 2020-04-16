#ifndef COURSEWORK_MACHINECODE_H
#define COURSEWORK_MACHINECODE_H

#include "Base.h"
#include "Addition.h"
#include "ErrorCheck.h"

struct MachineCodeInstructionStruct{
    string name;
    int opcode;
    int mod_r_m;
    int sib;
    int disp;
};

struct MachineCodeDirectiveStruct{
    string name;
    int Startcode;
    int SizeOfCode;
};



extern vector<MachineCodeInstructionStruct> MachineCodeInstruction;
extern vector<MachineCodeDirectiveStruct> MachineCodeDirective;

string MachineCodeForInstruction(vector <lexeme>);
string MachineCodeForDirective(vector <lexeme>);
string MachineCodeForOneLine( vector<lexeme> );
int Displacement(string MachineCode);
void createAllLst(char * );


#endif //COURSEWORK_MACHINECODE_H
