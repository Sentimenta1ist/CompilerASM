#include "MachineCode.h"

/*
 * 80 /0 ib     ADD r/m8, imm8
 * 81 /0 id     ADD r/m32, imm32
 * 83 /0 ib     ADD r/m32, imm8
 *
 * 6A   PUSH imm8
 * 68   PUSH imm32
 *
 * 3A /r    CMP r8, r/m8
 * 3B /r    CMP r32, r/m32
 *
 * 84 /r    TEST r/m8, r8
 * 85 /r    TEST r/m32, r32
 *
 * 48+rd    DEC r32
 *
 * 0FAB     BTS r/m32, r32
 *
 * AB   STOSD
 *
 * 74 cb    JZ rel8     Якщо нуль (ZF = 1)
 */


vector<MachineCodeInstructionStruct> MachineCodeInstruction{  //create for 32 bit operands
        {0,"add",0x81,1 },
        {0,"push",0x68,0 },
        {0,"cmp",0x3B,1},
        {0,"test",0x85,1},
        {0,"stosd",0xAB,0 },
        {0,"mov",0x8B,1}, //if mordm have
        {0,"mov",0xA1,0 }, //if operand 1 - "al" or "eax" - modrm - 0
        {0,"dec",0x48,0, 1},
        {0,"bts",0x0FAB,0 },
        {0,"jz",0xA9,0}
};

vector<MachineCodeDirectiveStruct> MachineCodeDirective{
        {"db",0,1},
        {"dd",0,4},
        {"equ",0,0}
};

string JccMachineCode(){
    return "74 00 90 90 90 90";
}
/*
 * Func for create operands (only for line with instruction!!!)
 */
void CreateOperandsForInstruction(vector<lexeme> OneLine, LineInstruction &alone){
    alone.instr = OneLine[0].name;
    alone.operand1 = "";
    alone.operand2 = "";
    alone.TypeOperand2 = "";
    alone.TypeOperand1 = "";
    int flagSecondOperand = 0;
    for(int i = 1; i < OneLine.size(); i++){
        if(OneLine[i].name == ","){
            flagSecondOperand = 1;
            continue;
        }
        if(flagSecondOperand == 1){
            alone.operand2 += OneLine[i].name;
            continue;
        }
        alone.operand1 += OneLine[i].name;
    }
    alone.TypeOperand1 = IdentifyOperand(alone.operand1);
    alone.TypeOperand2 = IdentifyOperand(alone.operand2);
}

string ImmCodeOneLine(LineInstruction alone){
    string res = "";
    if((alone.TypeOperand1 != const8)&&(alone.TypeOperand2 != const8)){
        return "";
    }
    if(alone.TypeOperand1 == const8) {
        res = Hex(Dec(alone.operand1),1);
        return res;
    }

    if(alone.TypeOperand2 == const8) {
        res = Hex(Dec(alone.operand2),1);
        if((alone.TypeOperand1 == mem32)||(alone.TypeOperand1 == mem32)){
            return Hex(Dec(alone.operand2),4);
        }
        return res;
    }
}

string OpCodeOneLine( LineInstruction alone){
    string res = "";

    /*
     * add adding registers and check for const.
     *
     *
     */
    for(auto it: MachineCodeInstruction){
        if((it.name == alone.instr)&&(!(ModrmOneLine(alone).empty()))&&(it.mod_r_m == 1)){
            if(it.registerInOpCode ){
                for(auto regi : RegistersTable){
                    if((regi.reg32Name == alone.operand1)||(regi.reg32Name == alone.operand2)){
                        return Hex(it.opcode | regi.value);
                    }
                }
                //return Hex(it.opcode |)
            }
            return Hex(it.opcode);
        }
        if((it.name == alone.instr)&&(ModrmOneLine(alone).empty())&&(it.mod_r_m == 0)){
            return Hex(it.opcode);
        }

    }
    //return res;
}

/*
 * create only modrm
 */
string ModrmOneLine( LineInstruction alone){

    int mod = 0b00;
    int regis = 0b000;
    int regrm = 0b000;

    if(alone.TypeOperand1 == nonOperand){
        return "";
    }
    else if(alone.instr == "mov"){
        if((alone.operand1 == "eax")||(alone.operand1 == "al")){
            return "";
        }
    }
    for(auto it:MachineCodeInstruction ){
        if((it.name == alone.instr)&&(it.mod_r_m == 0) &&(it.name != "mov")){
            return "";
        }
    }



    return Hex((mod << 3 | regis) << 3 | regrm);
}

/*
 * create only sib
 */
string SibOneLine( LineInstruction alone){
    int scale = 0b00;
    char scaleDec = '0';
    int index = 0b000;
    int base = 0b101; //default base is 101

    string operand;
    if(alone.TypeOperand1 == mem32){
        operand = alone.operand1;
    }
    else if(alone.TypeOperand2 == mem32){
        operand = alone.operand2;
    }
    else return "";
    if(operand.find("*") == string::npos) return "";

    for(auto it: RegistersTable){

        //search index reg
        size_t found_index = operand.find(it.reg32Name);
        if((found_index != string::npos)&&(operand[found_index + 3] == '*')){
            index |= it.value;
            //scaleDec = operand[found + 4];
            for(auto ScaleDefine:ScaleTable){
                if(ScaleDefine.second == operand[found_index + 4]){
                    scale |= ScaleDefine.first;
                }
            }
        }
        //if base another
        if((found_index != string::npos)&&(operand[found_index + 3] == '+')) {
            base &= 0b000;
            base |= it.value;
        }
    }
    return Hex((scale << 3 | index) << 3 | base);
}

/*
 * create only disp
 */
string DispOneLine(LineInstruction alone){
    string res = "";
    if((alone.TypeOperand1 == mem32)) {
        for(auto UserElement :MassOfUser){
            size_t found = alone.operand1.find(UserElement.name);
            if((found != string::npos)&&(UserElement.type != label)){
                return Hex(UserElement.displacement,4);

            }
        }
    }

    if((alone.TypeOperand2 == mem32)) {
        for(auto UserElement :MassOfUser){
            size_t found = alone.operand2.find(UserElement.name);
            if((found != string::npos)&&(UserElement.type != label)){
                return Hex(UserElement.displacement,4);
            }
        }
    }

    return res;
}

/*
 * return the string of bytes for lines with instruction
 */
string MachineCodeForInstruction(vector<lexeme> OneLine){
    if(OneLine[0].type != instruction)return "";
    string MachineCode = "";
    LineInstruction alone;
    CreateOperandsForInstruction(OneLine,alone);
    MachineCode += OpCodeOneLine(alone) + " "+ ModrmOneLine(alone)+
            " " + SibOneLine(alone)+ " " +DispOneLine(alone) + " " + ImmCodeOneLine(alone);
    return MachineCode;
}

/*
 * return the string of bytes if some value type was created
 */
string MachineCodeForDirective(vector<lexeme>OneLine){
    string MachineCode = "";
    if(OneLine.size() < 2) return "";
    if(OneLine[1].type != directive)return "";

    for(int i = 0; i < MassOfUser.size(); i++){
        if(MassOfUser[i].name == OneLine[0].name){
            MassOfUser[i].displacement = DispMain;
            if(MassOfUser[i].directiveOfThis == "equ"){
                MassOfUser[i].displacement = MassOfUser[i].size;
            }
        }
    }
    for(int i = 0; i < OneLine.size();i++) {
        for (auto it : MachineCodeDirective) {
            if (OneLine[i].name == it.name) {
                if (OneLine[i + 1].type == constChar) {
                    return Hex(OneLine[i + 1].name);
                }
                return Hex(Dec(OneLine[i + 1]), it.SizeOfCode);
            }
        }
    }
    return MachineCode;
}

/*
 * Sum all machine code in this line
 */
string MachineCodeForOneLine( vector<lexeme> OneLine){
    if(OneLine.empty())return "";
    if(OneLine[0].name == ";") return "";
    if(FullCheckOFLine(OneLine)) return errorMessage;
    if(OneLine[0].name == "end") {
        DispMain = -1;
        return "";
    }
    string MachineCode = "";
    MachineCode +=  MachineCodeForDirective(OneLine);
    MachineCode += MachineCodeForInstruction(OneLine);


    if(OneLine[0].name == "jz"){            //mod only for jcc instruction(may be will be update// )
        MachineCode = JccMachineCode();
    }

    return MachineCode;
}

/*
 * Sum disp in machine code in this line
 */

int Displacement(string MachineCode){
    //string MachineCode = MachineCodeForOneLine(Oneline);
    if(MachineCode == errorMessage) return 0;
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


            /*
            * create the mass of displacement
            */
            ElementOfDisp alone;
            alone.Line = AllTokens[i];
            alone.Value = DispMain;
            MassOfDisp.push_back(alone);
            /*
             * create the mass of displacement
             */

            getline(file,lineInFile);
            string result = "";
            string MachineCodeOne = MachineCodeForOneLine(AllTokens[i]);

            result += MachineCodeOne;                                   //comment this line, if u wanna only Displacement column
            result.insert(0, HexForDisp(MassOfDisp[MassOfDisp.size() - 1].Value));
            result.insert(6,"   "); // for good output
            for (int k = result.size(); k < 40; k++) {
                result += ' ';
            }
            result += '|';
            cout << result;
            cout << " " << lineInFile;
            cout << endl;

            /*
             *
             */
            //if(AllTokens.empty()) continue;
            if (AllTokens[i].empty()) continue;
            if (AllTokens[i][0].type == label) {
                for (int j = 0; j < MassOfUser.size(); j++) {
                    if (MassOfUser[j].name == AllTokens[i][0].name) {
                        MassOfUser[j].displacement = DispMain;
                        break;
                    }
                }

            }
            /*
             *
             */

            DispMain += Displacement(MachineCodeOne);
            /*
             * cycle - check for ending or starе of new segment
             */
            for (int j = 0; j < AllTokens[i].size(); j++) {
                if ((AllTokens[i][j].type == segmentWord) && (AllTokens[i][0].type == labelSeg)) {
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

    //table out put

    TableOutPut();

}
