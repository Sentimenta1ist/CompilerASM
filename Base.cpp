#include "Base.h"


int DispMain = 0;

vector<vector<lexeme>> AllTokens;

vector<struct_of_sentence> AllStruct;

vector<lexeme> MassOfUser;

vector<OneSegment> AllSegments;


/*
 * Dictionary of token
 * If u wanna add instruction to "compi":
 *      1) add to DictionaryOfTokens
 *      2) add to MachineCodeInstruction with another data
 *      3) add to Accessed vector with operands that you want
 */
vector<pair<string, vector<string>>> DictionaryOfTokens ={
         {reg,
                 {"eax", "ebx", "ecx",  "edx",  "esi", "edi", "ebp", "al", "bl",    "dl",  "cl"}},

         {instruction,
                 {"mov", "dec", "test", "push", "bts", "jz", "stosd", "add", "cmp"}},

         {JumpInstr,
                 {"jz"}},

         {directive,
                 {"db", "dd", "equ", "if", "endif"}},

         {directiveIf,
                 {"if", "endif"}},

         {labelSeg,
                 {"data", "code"}},

         {segmentWord,
                 {"segment", "ends", "end"}},

         {registerSeg,
                 {"ds", "cs", "gs", "fs", "bs", "ss"}}};

vector<registerValue> RegistersTable = {
        {"eax","al",0b000},
        {"ecx","cl",0b001},
        {"edx","dl",0b010},
        {"ebx","bl",0b011},
        {"esp","ah",0b100},
        {"ebp","ch",0b101},
        {"esi","dh",0b110},
        {"edi","bh",0b111}};
