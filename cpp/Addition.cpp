//
// Created by sentimental on 08.04.20.
//
#include "Addition.h"

vector<pair<int, char>> dictionaryHex = {{0,  '0'},
                                         {1,  '1'},
                                         {2,  '2'},
                                         {3,  '3'},
                                         {4,  '4'},
                                         {5,  '5'},
                                         {6,  '6'},
                                         {7,  '7'},
                                         {8,  '8'},
                                         {9,  '9'},
                                         {10, 'A'},
                                         {11, 'B'},
                                         {12, 'C'},
                                         {13, 'D'},
                                         {14, 'E'},
                                         {15, 'F'}};




string Hex(int number) {
    string result = "";
    if(number == 0)return "00";
    int remainder = number;
    while (remainder != 0) {
        for (int i = 0; i < dictionaryHex.size(); i++) {
            if (remainder % 16 == dictionaryHex[i].first) {
                result.insert(0, 1,dictionaryHex[i].second);
            }
        }
        remainder /= 16;
    }
    if(result.size() % 2 != 0 )result.insert(0,1, '0');
    return result;
}

string Hex(int number, int size){
    string result = Hex(number);
    if(size == 0){
        for(int i = result.size(); i < 4; i++){
            result.insert(0, "0");
        }
        result.insert(0, "=");
    }
    for(int i = result.size(); i < size * 2; i++){
        result.insert(0, "0");
    }
    return result;
}


string Hex(string number) {
    string result;

    //restract bin string(optional)
//    string bin;
//    if(number.empty())return "";
//    if((number[number.size() - 1] == 'b')&&(number.size() == 9)){           //its mean number is "00000000b"
//        for(int i = 0; i < 4; i++){
//            bin += number[i];
//        }
//        for(auto it : dictionaryBin){
//            if(bin == it.first) bin = it.second;
//        }
//        result += bin;
//
//        bin.clear();
//        for(int i = 4; i < 8; i++){
//            bin += number[i];
//        }
//        for(auto it : dictionaryBin){
//            if(bin == it.first) bin = it.second;
//        }
//        result += bin;
//        return result;
//    }


    for(int i = 0; i < number.size();i++){
        result += Hex(int(number[i])) + ' ';
    }
    return result;
}

string HexForDisp(int number){
    string result = Hex(number);
    result.insert (result.size() ,"|");
    if (number == 0)return "|0000|";
    if (number == -1)return "|----|";
    for (int i = result.size(); i < 5; i++) {
        result.insert(0, "0");
    }
    result.insert(0, "|");
    return result;
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
    IdentifyOperand(alone);
}

int Dec(lexeme constName){
    int result = 0;
    if(constName.type == constDecimal) return stoi(constName.name);
    if(constName.type == constHex)  {
        //if(constName.name[0])
        for(int i = constName.name.size() - 2; i >= 0 ; i--){
            for(int j = 0; j < dictionaryHex.size(); j++){
                if(dictionaryHex[j].second == toupper(constName.name[i])){
                   result += dictionaryHex[j].first * pow(16,constName.name.size() - 2 - i);
                }
            }
        }
    }
    return result;
}

bool IsItMemory(string alone){
    return(alone == MEM32 || alone == MEM16 || alone == MEM8);
}

bool IsItRegister(string alone){
    return (alone == REG32 || alone == REG16 || alone == REG8);
}


void IdentifyOperand(LineInstruction &alone){
    int FlagOperand1 = 0;
    int FlagOperand2 = 0;
      if(alone.operand1.empty() && alone.operand2.empty()) {
          alone.operand1 = NoOperand;
          alone.TypeOperand1 = NoOperand;
          alone.operand2 = NoOperand;
          alone.TypeOperand2 = NoOperand;
          return;
      }
      if(alone.operand2.empty()){
          //alone.operand2 = NoOperand;
          alone.TypeOperand2 = NoOperand;
          //FlagOperand1 = 1;
          //check register
          for(auto it: RegistersTable){
              if(it.reg8Name == alone.operand1){
                  alone.TypeOperand1 = REG8;
                  return;
              }
              if(it.reg16Name == alone.operand1){
                  alone.TypeOperand1 = REG16;
                  return;
              }
              if(it.reg32Name == alone.operand1){
                  alone.TypeOperand1 = REG32;
                  return;
              }
          }

          //check memory
          for(auto UserElement :MassOfUser){
              size_t found = alone.operand1.find(UserElement.name);
              if((found != string::npos)/*&&(UserElement.type != label)*/){
                  if(UserElement.directiveOfThis == "db"){
                      alone.TypeOperand1 = MEM8;
                      return;
                  }
                  if(UserElement.directiveOfThis == "dd"){
                      alone.TypeOperand1 = MEM32;
                      return;
                  }
              }
          }

          //check imm
          alone.TypeOperand1 = IMM8;
          return;
      }

    for(auto it: RegistersTable) {
        if (it.reg8Name == alone.operand1) {
            alone.TypeOperand1 = REG8;
            FlagOperand1 = 1;
        }
        if (it.reg16Name == alone.operand1) {
            alone.TypeOperand1 = REG16;
            FlagOperand1 = 1;
        }
        if (it.reg32Name == alone.operand1) {
            alone.TypeOperand1 = REG32;
            FlagOperand1 = 1;
        }

        if (it.reg8Name == alone.operand2) {
            alone.TypeOperand2 = REG8;
            FlagOperand2 = 1;
        }
        if (it.reg16Name == alone.operand2) {
            alone.TypeOperand2 = REG16;
            FlagOperand2 = 1;
        }
        if (it.reg32Name == alone.operand2) {
            alone.TypeOperand2 = REG32;
            FlagOperand2 = 1;
        }
    }

    for(auto UserElement :MassOfUser){
        size_t found = alone.operand1.find(UserElement.name);
        if((found != string::npos)&&(UserElement.type != label)){
            if(UserElement.directiveOfThis == "db"){
                alone.TypeOperand1 = MEM8;
                FlagOperand1 = 1;
            }
            if(UserElement.directiveOfThis == "dd"){
                alone.TypeOperand1 = MEM32;
                FlagOperand1 = 1;
            }
        }

        found = alone.operand2.find(UserElement.name);
        if((found != string::npos)&&(UserElement.type != label)){
            if(UserElement.directiveOfThis == "db"){
                alone.TypeOperand2 = MEM8;
                FlagOperand2 = 1;
            }
            if(UserElement.directiveOfThis == "dd"){
                alone.TypeOperand2 = MEM32;
                FlagOperand2 = 1;
            }
        }
    }
    if(!FlagOperand1 && alone.operand1[alone.operand1.size() - 1] == ']'){
        if(alone.TypeOperand2 == REG32){
            alone.TypeOperand1 = MEM32;
            return;
        }
        if(alone.TypeOperand2 == REG8){
            alone.TypeOperand1 = MEM8;
            return;
        }
    }
    if(!FlagOperand2 && alone.operand2[alone.operand2.size() - 1] == ']'){
        if(alone.TypeOperand1 == REG32){
            alone.TypeOperand2 = MEM32;
            return;
        }
        if(alone.TypeOperand1 == REG8){
            alone.TypeOperand2 = MEM8;
            return;
        }
    }

    if(!FlagOperand2){
        if(alone.instr == "add"){   //and another instr if u have
            if(alone.TypeOperand1 == REG32 || alone.TypeOperand1 == MEM32){
                if(Dec(alone.operand2) < 256){
                    alone.TypeOperand2 = IMM8;
                    return;
                }
            }
        }
        if((alone.TypeOperand1 == REG32) || (alone.TypeOperand1 == MEM32)) {
            alone.TypeOperand2 = IMM32;
            return;
        }
        if((alone.TypeOperand1 == REG8) || (alone.TypeOperand1 == MEM8)) {
            alone.TypeOperand2 = IMM8;
            return;
        }
    }
}

bool EqualsOfVector(vector<lexeme> first,vector<lexeme> second){
    if(first.size() != second.size())return false;
    for(int i = 0; i < first.size(); i++){
        if(first[i].name != second[i].name){
            return false;
        }
    }
    return true;
}

void TableOutPut(){
    cout << endl << " Segments:" << endl;
    cout << "--------------------------------------------\n"
            "|#  |Name           |Size       |Length     |\n"
            "--------------------------------------------\n";
    for(int i = 0; i < AllSegments.size(); i++){
        cout << "| " << setw(1) << i << " |";
        std::transform(AllSegments[i].name.begin(), AllSegments[i].name.end(), AllSegments[i].name.begin(), [](unsigned char c) { return std::toupper(c); });
        cout << setw(15) <<left<< AllSegments[i].name <<"|" ;
        cout << setw(11) << "32" << "|";
        cout << setw(11) << Hex(AllSegments[i].size,2)  << "|" << endl;
    }
    cout << "-------------------------------------------" << endl;

    cout << endl << " Segment register:" << endl;
    cout << "----------------------------------------\n"
            "|#  |Segment Register   |Destination   |\n"
            "----------------------------------------\n";
    for(int i = 0; i < TableOfPrefixesSegment.size(); i++){
        cout << "|" << setw(3) << i << "|";
        std::transform(TableOfPrefixesSegment[i].prefix.begin(), TableOfPrefixesSegment[i].prefix.end(), TableOfPrefixesSegment[i].prefix.begin(), [](unsigned char c) { return std::toupper(c); });
        cout << setw(19) <<  TableOfPrefixesSegment[i].prefix << "|";
        cout << setw(14) << TableOfPrefixesSegment[i].fullName << "|" << endl;
    }
    cout << "---------------------------------------" << endl;

    cout << endl << " User defines names:" << endl;
    cout << "--------------------------------------------------\n"
            "| # |Name       |Type       |Value    |Attr      |\n"
            "--------------------------------------------------\n";
    for(int i = 0; i < MassOfUser.size(); i++){
        cout << "|" << setw(3) << i << "|";
        std::transform(MassOfUser[i].name.begin(), MassOfUser[i].name.end(), MassOfUser[i].name.begin(), [](unsigned char c) { return std::toupper(c); });
        cout << setw(11) << MassOfUser[i].name << "|";
        std::transform(MassOfUser[i].directiveOfThis.begin(), MassOfUser[i].directiveOfThis.end(), MassOfUser[i].directiveOfThis.begin(), [](unsigned char c) { return std::toupper(c); });
        cout << setw(11) << MassOfUser[i].directiveOfThis << "|";   //add directive
        cout << setw(9) << Hex(MassOfUser[i].displacement,2) << "|";
        std::transform(MassOfUser[i].segment.begin(), MassOfUser[i].segment.end(), MassOfUser[i].segment.begin(), [](unsigned char c) { return std::toupper(c); });
        cout << setw(10) << MassOfUser[i].segment << "|";//add segment
        cout << endl;
    }
    cout << "--------------------------------------------------\n";
}

int Dec(string number){
    if(number[number.size() - 1] == 'h'){
        lexeme one;
        one.type = constHex;
        one.name = number;
        return Dec(one);
    }
    for(int i = 0; i < number.size();i++){
        if((number[i] <= '9')&&(number[i] >='0')){
            return stoi(number);
        }
    }
    return 1000;
}
