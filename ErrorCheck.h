#pragma once
#include "Base.h"
#include "Addition.h"
#include "FirstSecondStage.h"

struct ErrorOfOperands{
    string instr;
    string operand1;
    string operand2;
};


extern vector<ErrorOfOperands> Accesed;
bool CheckForUndefined(vector<lexeme> example);

bool CheckForOperands(vector<lexeme> example);
void check();
