#pragma once
#include "Base.h"
#include "Addition.h"

struct ErrorOfOperands{
    string instruction;
    string operand1;
    string operand2;
};


extern vector<ErrorOfOperands> Accesed;
bool Errortest(vector<lexeme> example);
void Diplacement(vector<lexeme> example);

