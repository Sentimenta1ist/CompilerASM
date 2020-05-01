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

vector<pair<string, string>> dictionaryBin =
                                        {{"0000",  "0"},
                                         {"0001",  "1"},
                                         {"0010",  "2"},
                                         {"0011",  "3"},
                                         {"0100",  "4"},
                                         {"0101",  "5"},
                                         {"0110",  "6"},
                                         {"0111",  "7"},
                                         {"1000",  "8"},
                                         {"1001",  "9"},
                                         {"1010", "A"},
                                         {"1011", "B"},
                                         {"1100", "C"},
                                         {"1101", "D"},
                                         {"1110", "E"},
                                         {"1111", "F"}};


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
    alone.sizeOpernad1 = 8;
    alone.sizeOpernad2 = 8;
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

void IdentifyOperand(LineInstruction &alone){

    if(example.empty()) alone. "-1";
    for(auto table: RegistersTable){
        if(table.reg32Name == example){
            return "reg32";
        }
        if(table.reg8Name == example) {
            return "reg8";
        }
    }

    //check for hex const
    if((isdigit(example[0]))&&(example[example.size() - 1] == 'h')){
        return "const8";
    }

    //check for decimal const
    int flagOfDecimal = 0;
    for( auto it:example){
        if(!isdigit(it))flagOfDecimal = 1;
    }
    if(flagOfDecimal == 0)return "const8";
    /*
     *must identify
     */

    return "mem32";
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
    for(int i = 0; i < number.size();i++){
        if((number[i] <= '9')&&(number[i] >='0')){
            return stoi(number);
        }
    }
    return 1000;
}