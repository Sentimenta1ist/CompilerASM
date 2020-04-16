#include "MachineCode.h"

vector<MachineCodeInstructionStruct> MachineCodeInstruction{
        {"add",0xFF,0,0,0 },
        {"push",0x68,0,0,0 },
        {"cmp",0x83,0,0,0 },
        {"test",0x85,0,0,0 },
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

/*
 * return the string of bytes for lines with instruction
 */
string MachineCodeForInstruction(vector<lexeme> OneLine){
    if(OneLine[0].type != instruction)return "";
    string MachineCode = "";
    for(auto dicLexeme:MachineCodeInstruction){
        if(OneLine[0].name == dicLexeme.name){
            MachineCode += Hex(dicLexeme.opcode);
        }
    }
    return MachineCode;
}

/*
 * return the string of bytes if some value type was created
 */
string MachineCodeForDirective(vector<lexeme>OneLine){
    string MachineCode = "";
    if(OneLine[1].type != directive)return "";
    for(int i = 0; i < OneLine.size();i++) {
        for (auto it : MachineCodeDirective) {
            if (OneLine[i].name == it.name) {
                if (OneLine[i + 1].type == constChar) {
                    // cout << OneLine[i+1].name;
                    return Hex(OneLine[i + 1].name);
                }
                return Hex(Dec(OneLine[i + 1]), it.SizeOfCode);
            }
        }
    }
}

/*
 * Sum all machine code in this line
 */
string MachineCodeForOneLine( vector<lexeme> OneLine){
    if(OneLine.empty())return "";
    string MachineCode = "";
    MachineCode +=  MachineCodeForDirective(OneLine);
    MachineCode += MachineCodeForInstruction(OneLine);

    return MachineCode;
}

/*
 * Sum disp in machine code in this line
 */
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

/*
 * cout all lst file
 */
void createAllLst( char * inputFile){
    ifstream file(inputFile);
    string lineInFile = "";
    if (file.is_open() ) {
        for (int i = 0; i < AllTokens.size(); i++) {
            getline(file,lineInFile);
            string result = "    ";
            result += MachineCodeForOneLine(AllTokens[i]);
            result.insert(0, HexForDisp(DispMain));
            DispMain += Displacement(MachineCodeForOneLine(AllTokens[i]));
            for (int k = result.size(); k < 40; k++) {
                result += ' ';
            }
            result += '|';
            cout << result;
            cout << " " << lineInFile;
            cout << endl;

            /*
             * cycle - check for ending or starе of new segment
             */
            for (int j = 0; j < AllTokens[i].size(); j++) {
                if ((AllTokens[i][j].type == segmentWord) && (AllTokens[i][0].type == label)) {
                    //OneSegment alone;
                    //alone.name = AllTokens[i][0].name;
                    //AllSegments.push_back()
                    if (AllTokens[i][j].name == "segment") {
                        DispMain = 0;
                    }
                    if (AllTokens[i][j].name == "ends") {
                        OneSegment alone;
                        alone.name = AllTokens[i][0].name;
                        alone.size = DispMain;
                        AllSegments.push_back(alone);
                        DispMain = 0;
                    }
                }
            }
            /*
            * cycle - check for ending or star of new segment
            */

        }
    }
    file.close();
}
