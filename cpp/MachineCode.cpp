#include "MachineCode.h"

string JccMachineCode(){
    return "74 00 90 90 90 90";
}


string ImmCodeOneLine(LineInstruction alone){
    if(alone.TypeOperand1 == IMM8){

        return Hex(Dec(alone.operand1),1);
    }
    else if(alone.TypeOperand1 == IMM32)return Hex(Dec(alone.operand1),4);
    if(alone.TypeOperand2 == IMM8)return Hex(Dec(alone.operand2),1);
    else if(alone.TypeOperand2 == IMM32)return Hex(Dec(alone.operand2),4);
    else return "";
}

string OpCodeOneLine( LineInstruction alone){
    string res = "";
    for(auto it: MachineCodeInstruction){
        if(it.name == alone.instr && it.op1 == alone.TypeOperand1 && it.op2 == alone.TypeOperand2){
            if(it.registerInOpCode){

                for(auto regi : RegistersTable){
                    if((regi.reg32Name == alone.operand1)||(regi.reg32Name == alone.operand2)||(regi.reg8Name == alone.operand2)||(regi.reg8Name == alone.operand1)){
                        return Hex(it.opcode | regi.value);
                    }
                }
            }
            return Hex(it.opcode);
        }

    }
}

/*
 * create only modrm
 */
string ModrmOneLine( LineInstruction alone){

    int mod = 0b00;
    int regis = 0b000;
    int regrm = 0b000;

    if(alone.TypeOperand1 == NoOperand){
        return "";
    }

    for(auto it:MachineCodeInstruction ){
        if((!it.mod_r_m)&&(it.name == alone.instr)){
            return "";
        }
    }
    string res = DispOneLine(alone);
    if(res.size() == 2){
        mod |= 0b01;
    }
    if(res.size() == 8){
        mod |= 0b10;
    }
    if(IsItRegister(alone.TypeOperand1) && IsItRegister(alone.TypeOperand2)){
        mod |= 0b11;
    }

    if(IsItRegister(alone.TypeOperand1)){
        for(auto regi : RegistersTable){
            if((regi.reg32Name == alone.operand1)||(regi.reg32Name == alone.operand2)||(regi.reg8Name == alone.operand2)||(regi.reg8Name == alone.operand1)){
                regis |= regi.value;
            }
        }
    }
    if(IsItRegister(alone.TypeOperand2)){
        for(auto regi : RegistersTable){
            if((regi.reg32Name == alone.operand1)||(regi.reg32Name == alone.operand2)||(regi.reg8Name == alone.operand2)||(regi.reg8Name == alone.operand1)){
                regis |= regi.value;
            }
        }
    }


    return Hex((mod << 3 | regis) << 3 | regrm);
}

/*
 * create only sib
 */
string SibOneLine( LineInstruction alone){
    int scale = 0b00;
    int index = 0b000;
    int base = 0b101; //default base is 101

    string operand;
    if(IsItMemory(alone.TypeOperand1)){
        operand = alone.operand1;
    }
    else if(IsItMemory(alone.TypeOperand2)){
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
    if(IsItMemory(alone.TypeOperand1)) {
        for(auto UserElement :MassOfUser){
            size_t found = alone.operand1.find(UserElement.name);
            if((found != string::npos)&&(UserElement.type != label)){
                return Hex(UserElement.displacement,4);

            }
        }
    }

    if(IsItMemory(alone.TypeOperand2)) {
        for(auto UserElement :MassOfUser){
            size_t found = alone.operand2.find(UserElement.name);
            if((found != string::npos)&&(UserElement.type != label)){
                return Hex(UserElement.displacement,4);
            }
        }
    }
    return "";
}

/*
 * return the string of bytes for lines with instruction
 */
string MachineCodeForInstruction(vector<lexeme> OneLine){
    if(OneLine[0].type != instruction)return "";
    string MachineCode = "";
    LineInstruction alone;
    CreateOperandsForInstruction(OneLine,alone);
    //MachineCode += "1-" + alone.TypeOperand1 + " 2-" + alone.TypeOperand2;

    MachineCode += OpCodeOneLine(alone) + " "+ ModrmOneLine(alone)+
            " " + SibOneLine(alone)+ " " +DispOneLine(alone) + " " +ImmCodeOneLine(alone);
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

    if(OneLine[0].name == "jz") return JccMachineCode();          //mod only for jcc instruction( may be will be update )

    MachineCode +=  MachineCodeForDirective(OneLine);
    MachineCode += MachineCodeForInstruction(OneLine);


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

    FillMassOfUsers();
    IfDirectiveWorking();

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
