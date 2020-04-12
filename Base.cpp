//
// Created by sentimental on 08.04.20.
//

#include "Base.h"


//smth nEW
//AGA


int DataSize = 0;
int DispMain = 0;

vector<vector<lexeme>> AllTokens;

vector<struct_of_sentence> AllStruct;

vector<User> MassOfUser;

vector<pair<string, string>> DictionaryOfTokens = {{"data",    "label_d"},
                                                   {"segment", "segmentword"},
                                                   {"db",      "directive"},
                                                   {"dd",      "directive"},
                                                   {"equ",     "directive"},
                                                   {"ends",    "segmentword"},
                                                   {"code",    "label_c"},
                                                   {"jz",      "instruction"},
                                                   {"mov",     "instruction"},
                                                   {"eax",     "register 32"},
                                                   {"dec",     "instruction"},
                                                   {"push",    "instruction"},
                                                   {"esi",     "register 32"},
                                                   {"test",    "instruction"},
                                                   {"fs",      "id_segment_register"},
                                                   {"bts",     "instruction"},
                                                   {"add",     "instruction"},
                                                   {"if",      "directiveIF_ENDIF"},
                                                   {"endif",   "directiveIF_ENDIF"},
                                                   {"edi",     "register 32"},
                                                   {"stosd",   "instruction"},
                                                   {"cmp",     "instruction"},
                                                   {"end",     "segmentword"}};

vector<machine_code_lexeme> Machine_code{
        {"add",0b1000,0,0,0 },
        {"mov",0xF1,0,0,0 },
        {"dec",0xF4,0,0,0 },
        {"and",0xF5,0,0,0 },
        {"cmp",0xF6,0,0,0 }
};