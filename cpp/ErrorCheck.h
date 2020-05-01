#pragma once
#include "Base.h"
#include "Addition.h"
#include "FirstSecondStage.h"
//#include "Parsing.h"

struct ErrorOfOperands{
    string instr;
    string operand1;
    string operand2;
};


extern vector<ErrorOfOperands> Accessed;

bool CheckForUndefined(vector<lexeme> );
bool CheckForOperands(vector<lexeme> );
bool FullCheckOFLine(vector <lexeme>);

void check();
