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
                 {"db", "dd", "equ", "if", "endif"}},

         {directiveIf,
                 {"if", "endif"}},

         {labelCode,
                 {"data", "code"}},

         {segmentWord,
                 {"segment", "ends", "end"}},

         {registerSeg,
                 {"ds", "cs", "gs", "fs", "bs", "ss"}}};
