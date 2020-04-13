#include "Base.h"

int DataSize = 0;
int DispMain = 0;

vector<vector<lexeme>> AllTokens;

vector<struct_of_sentence> AllStruct;

vector<User> MassOfUser;

vector<pair<string, vector<string>>> DictionaryOfTokens ={
         {reg,
                 {"eax", "ebx", "ecx",  "edx",  "esi", "edi", "ebp", "al", "bl",    "dl",  "cl"}},

         {instruction,
                 {"mov", "dec", "test", "push", "bts", "jz", "stosd", "add", "cmp"}},

         {directive,
                 {"db", "dd", "dq", "equ", "if", "endif"}},

         {labelCode,
                 {"data", "code"}},

         {segmentWord,
                 {"segment", "ends", "end"}},

         {registerSeg,
                 {"ds", "cs", "gs", "fs", "bs", "ss"}}};


vector<machine_code_lexeme> Machine_code{
        {"add",0xFF,0,0,0 },
        {"push",0x68,0,0,0 },
        {"cmp",0x83,0,0,0 },
        {"test",0xA9,0,0,0 }
};