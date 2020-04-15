#include "MachineCode.h"

vector<MachineCodeInstructionStruct> MachineCodeInstruction{
        {"add",0xFF,0,0,0 },
        {"push",0x68,0,0,0 },
        {"cmp",0x83,0,0,0 },
        {"test",0xA9,0,0,0 },
        {"stosd",0xA9,0,0,0 },
        {"mov",0xA9,0,0,0 },
        {"dec",0xA9,0,0,0 },
        {"bts",0xA9,0,0,0 },
        {"jz",0xA9,0,0,0 }
};

vector<MachineCodeDirectiveStruct> MachineCodeDirective{
        {"db",0,1},
        {"dd",0,4},
        {"equ",0,0}
};


string MachineCodeForOneLine( vector<lexeme> OneLine){
    string MachineCode = "";
    for(int i = 0; i < OneLine.size();i++) {
        for(auto it : MachineCodeDirective) {
            if(OneLine[i].name == it.name) {
                if(OneLine[i + 1].type == constChar) {
                   // cout << OneLine[i+1].name;
                    return Hex(OneLine[i+1].name);
                }
                return Hex(Dec(OneLine[i+1]),it.SizeOfCode);
            }
        }
    }
    return "--";
}

int Displacement(string MachineCode){
    int disp = 0;
    if(MachineCode[0] == '=') return disp;
    for(auto i :MachineCode){
        if(((i >= 'A')&&(i <= 'F')) || ((i >= '0')&&(i <= '9'))){
            disp++;
        }
    }

    return disp/=2;
}

void createAllLst(){


    int disp = 0;
    for(int i = 0; i < AllTokens.size();i++) {
        string result = "    ";
        result += MachineCodeForOneLine(AllTokens[i]);
        result.insert(0,HexForDisp(disp));
        disp += Displacement(MachineCodeForOneLine(AllTokens[i]));
        for(int k = result.size(); k < 40; k++){
            result += ' ';
        }
        result+='|';
        cout << result;
        for(int j = 0; j < AllTokens[i].size(); j++){
            cout << ' ' << AllTokens[i][j].name << ' ';
        }
        cout << endl;
    }
}
