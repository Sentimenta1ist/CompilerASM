#ifndef COURSEWORK_MACHINECODE_H
#define COURSEWORK_MACHINECODE_H

#include "Base.h"
#include "Addition.h"
#include "ErrorCheck.h"


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
