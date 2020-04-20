#pragma once
#include "Base.h"

extern vector<pair<int, char>> dictionaryHex;

int Dec(lexeme);
int Dec(string number);
string Hex(int);
string HexForDisp(int);
string Hex(string);
string Hex(int , int);

string IdentifyOperand(string example);
bool EqualsOfVector(vector<lexeme> first,vector<lexeme> second);

void TableOutPut();