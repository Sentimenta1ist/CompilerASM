#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <regex>

using namespace std;

struct lexeme {
    int number_of_lexem;
    int number_of_row;
    string name;
    int length;
    string type;
    string type_for_check;
    int label = -1;
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

struct machine_code_lexeme{
    string name;
    int opcode;
    int mod_r_m;
    int sib;
    int disp;

};

struct User{
    string name;
    int disp;

};

extern vector<machine_code_lexeme> Machine_code;
extern vector<User> MassOfUser;
extern vector<vector<lexeme>> AllTokens;
extern vector<struct_of_sentence> AllStruct;
extern vector<pair<string, string>> DictionaryOfTokens;

extern int DataSize;
extern int DispMain;
