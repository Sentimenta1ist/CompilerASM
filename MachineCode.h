#ifndef COURSEWORK_MACHINECODE_H
#define COURSEWORK_MACHINECODE_H

#include "Base.h"
#include "Addition.h"
#include "ErrorCheck.h"

struct MachineCodeInstructionStruct{
    int prefix;
    string name;
    int opcode;
    int mod_r_m;
    int registerInOpCode = 0; // mean that opcode = opcode + register;
};

struct MachineCodeDirectiveStruct{
    string name;
    int Startcode;
    int SizeOfCode;
};

extern vector<MachineCodeInstructionStruct> MachineCodeInstruction;
extern vector<MachineCodeDirectiveStruct> MachineCodeDirective;

//split line on   ins - op1 - op2
void CreateOperandsForInstruction(vector<lexeme>, LineInstruction &);

// create machine code
string ImmCodeOneLine(LineInstruction);
string DispOneLine(LineInstruction);
string OpCodeOneLine(LineInstruction);
string SibOneLine(LineInstruction);
string ModrmOneLine( LineInstruction );
string JccMachineCode();

//sum machine code
string MachineCodeForInstruction(vector <lexeme>);
string MachineCodeForDirective(vector <lexeme>);
string MachineCodeForOneLine( vector<lexeme> );


int Displacement(string MachineCode);
void createAllLst(char * );


#endif //COURSEWORK_MACHINECODE_H
