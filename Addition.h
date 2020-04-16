#pragma once
#include "Base.h"

extern vector<pair<int, char>> dictionaryHex;

int Dec(lexeme);
string Hex(int);
string HexForDisp(int);
string Hex(string);
string Hex(int , int);

string IdentifyOperand(string);