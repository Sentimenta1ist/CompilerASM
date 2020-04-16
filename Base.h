#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <regex>

//semantic
#define reg "reg"
#define instruction "instruction"
#define undefined "undefined"
#define directive "directive"
#define label "label"
#define segmentWord "segmentWord"
#define registerSeg "registerSeg"
#define directiveIf "directiveIF_ENDIF"

//users
#define constChar "constChar"
#define constDecimal "constDecimal"
#define constHex "constHex"
#define singleLexeme "single lexeme"
#define label "label"
#define userId "userId"
#define nonOp "nonOperand"
#define delimeter ","
#define CONST constChar||constDecimal||constHex

using namespace std;

struct lexeme {
    int number_of_lexem;
    int number_of_row;
    string name;
    int length;
    string type;
    //string type_for_check;
    //int label = -1;
};

struct struct_of_sentence {
    int number_of_row = -1;
    int number_of_label = -1;
    int number_of_mnemonic = -1;
    int number_of_operand1 = -1;
    int number_of_operand2 = -1;
    int amount_of_mnemonic = -1;
    int amount_of_operand1 = -1;
    int amount_of_operand2 = -1;
};

struct OneSegment{
    int size;
    string name;
};

struct User{
    string name;
    int disp;

};

extern vector<User> MassOfUser;
extern vector<vector<lexeme>> AllTokens;
extern vector<struct_of_sentence> AllStruct;
extern vector<pair<string, vector<string>>> DictionaryOfTokens;
extern vector<OneSegment> AllSegments;

extern int DispMain;
