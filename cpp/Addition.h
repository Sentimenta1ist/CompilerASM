#pragma once
#include "Base.h"

extern vector<pair<int, char>> dictionaryHex;

int Dec(lexeme);
int Dec(string number);
string Hex(int);
string HexForDisp(int);
string Hex(string);
string Hex(int , int);

bool IsItMemory(string);
bool IsItRegister(string);

void IdentifyOperand(LineInstruction &);
bool EqualsOfVector(vector<lexeme> first,vector<lexeme> second);

//split line on   ins - op1 - op2 - size1 - size2
void CreateOperandsForInstruction(vector<lexeme>, LineInstruction &);

void TableOutPut();