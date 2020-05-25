#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <regex>

//segodnya ya pYaN

//semantic
#define reg "reg"
#define instruction "instruction"
#define undefined "undefined"
#define directive "directive"
#define labelSeg "labelSegment"
#define segmentWord "segmentWord"
#define registerSeg "registerSeg"
#define directiveIf "directiveIF_ENDIF"

//users
#define constChar "constChar"
#define constDecimal "constDecimal"
#define constHex "constHex"
#define singleLexeme "single lexeme"
#define JumpInstr "instruction jump"
#define label "label"
#define userId "userId"

//for program
#define errorMessage "* error *"


//size of operands
#define MEM32 "mem32"
#define IMM32 "constant32"
#define REG32 "reg32"
#define MEM16 "mem16"
#define IMM16 "constant16"
#define REG16 "reg16"
#define MEM8 "mem8"
#define IMM8 "constant8"
#define REG8 "reg8"

#define NoOperand  "NoOperand"

using namespace std;

/*
 *struct of one lexeme
 * most useful is name and type
 */
struct lexeme {
    int number_of_lexem;
    int number_of_row;
    string name;
    int length;
    string type;
};

struct ElementOfDisp{
    vector <lexeme>Line;
    int Value;
};

/*
 * struct for sentences
 * (first stage of work)
 */
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

/*
 * struct for one segment
 */
struct OneSegment{
    int size;
    string name;
};

/*
 * struct for one user id
 */
struct User{
    string name;
    string type;
    string directiveOfThis;
    string segment;
    int displacement;
    int size;
};

/*
 * struct for Register
 */
struct registerValue{
    string reg32Name;
    string reg16Name;
    string reg8Name;
    int value;
};

struct LineInstruction{
    string instr;
    string operand1;
    string operand2;
    string TypeOperand1;
    string TypeOperand2;
};

struct PrefixSegments{
    string prefix;
    string fullName;
    int value;
};

struct MachineCodeInstructionStruct{
    string name;
    string op1;
    string op2;
    int opcode;
    int mod_r_m = 0;
    int registerInOpCode = 0; // mean that opcode = opcode + register;
};

struct MachineCodeDirectiveStruct{
    string name;
    int Startcode;
    int SizeOfCode;
};

struct ModRMLine{
    int mod;
    string op1;
    string op2;
    //int modrm;
};

extern vector<MachineCodeInstructionStruct> MachineCodeInstruction;
extern vector<MachineCodeDirectiveStruct> MachineCodeDirective;

//vector<ModRMLine> ModTable;
extern vector<ElementOfDisp> MassOfDisp;
extern vector<User> MassOfUser;
extern vector<vector<lexeme>> AllTokens;
extern vector<struct_of_sentence> AllStruct;
extern vector<pair<string, vector<string>>> DictionaryOfTokens;
extern vector<OneSegment> AllSegments;
extern vector<registerValue> RegistersTable;
extern vector<pair<int , char>> ScaleTable;
extern vector <PrefixSegments> TableOfPrefixesSegment;

/*
 * main displacement in program
 */
extern int DispMain;
