#include "Base.h"


int DispMain = 0;

vector<vector<lexeme>> AllTokens;

vector<struct_of_sentence> AllStruct;

vector<User> MassOfUser;

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
        {"eax","al","000"},
        {"ecx","cl","001"},
        {"edx","dl","010"},
        {"ebx","bl","011"},
        {"esp","ah","100"},
        {"ebp","ch","101"},
        {"esi","dh","110"},
        {"edi","bh","111"}};
