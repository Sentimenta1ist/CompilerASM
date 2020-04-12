#include "Parsing.h"

bool compareByLength(const User &a, const User &b)
{
    return a.name.size() < b.name.size();
}

void FillMassOfUsers(){
    User alone;
    for(int i = 0; i < AllTokens.size(); i++){
        if(AllTokens[i].empty())continue;
        for(int j = 0 ; j < AllTokens[i].size() - 1;j++){
                if(AllTokens[i][j].type == "label"){
                    alone.name = AllTokens[i][j].name;
                    alone.disp = 255;
                    MassOfUser.push_back(alone);
                }
                if((AllTokens[i][j].type == "user id or undifined") && (AllTokens[i][j+1].type == "directive")){
                    alone.name = AllTokens[i][j].name;
                    alone.disp = 255;
                    MassOfUser.push_back(alone);
                }
        }
    }
    sort(MassOfUser.begin(),MassOfUser.end(), compareByLength);
}

void LoadFromFile(const char* file) {
    string line;
    string solo = "";
    int indicator_of_rows = 0;
    int indicator_of_lexems = 0;
    lexeme one;
    vector<lexeme>one_row;
    ifstream in_for_numbers(file);
    ofstream out;
    out.open("result.txt");
    if ((in_for_numbers.is_open() && out.is_open()))
    {
        while (getline(in_for_numbers, line))
        {
            indicator_of_lexems = 0;
            for (int i = 0; i < line.size(); i++)
            {
                if ((line[i] == ' ') || (line[i] == '\t'))continue;
                solo += line[i];
                if (line[i + 1] == '\0') {
                    IdentifyLexeme(one, solo, indicator_of_rows, indicator_of_lexems);
                    indicator_of_lexems++;
                    one_row.push_back(one);
                    solo.clear();
                }
                if ((line[i + 1] == ' ') || (line[i + 1] == '\t') || (line[i + 1] == ':') || (line[i + 1] == ',')
                    || (line[i + 1] == '[') || (line[i + 1] == ']') || (line[i + 1] == '*')) {

                    IdentifyLexeme(one, solo, indicator_of_rows, indicator_of_lexems);
                    indicator_of_lexems++;
                    one_row.push_back(one);
                    solo.clear();
                    if ((line[i + 1] == ':') || (line[i + 1] == ',')
                        || (line[i + 1] == '[') || (line[i + 1] == ']') || (line[i + 1] == '*')) {
                        i++;
                        solo += line[i];
                        IdentifyLexeme(one, solo, indicator_of_rows, indicator_of_lexems);
                        indicator_of_lexems++;
                        one_row.push_back(one);
                        solo.clear();
                    }

                }
            }
            indicator_of_rows++;
            AllTokens.push_back(one_row);
            one_row.clear();
        }
    }

    in_for_numbers.close();
    out.close();

    for (int i = 0; i < AllTokens.size(); i++) {
        for (int j = 1; j < AllTokens[i].size(); j++) {
            if ((AllTokens[i][j].name == ":") && (AllTokens[i][j - 1].type == "user id or undifined")) {
                AllTokens[i][j - 1].type = "label";
            }
        }
    }


    for (int i = 0; i < AllTokens.size(); i++) {
        struct_of_sentence alone;
        CreateSyntax(AllTokens[i], alone);
        AllStruct.push_back(alone);
    }
}

void IdentifyLexeme(lexeme& one, string line, int indicator_of_rows, int indicator_of_lexems) {
    one.number_of_lexem = indicator_of_lexems;
    one.number_of_row = indicator_of_rows;
    one.length = line.size();
    bool flag_16const = false;
    bool flag_10const = true;
    bool flag_charconst = false;
    if ((line[0] == '\"') && (line[line.size() - 1] == '\"')) {
        bool flag_charconst = true;
        for (int i = 0; i < line.size(); i++) {
            if (isdigit(line[i])) {
                flag_charconst = false;
            }
        }
        if (flag_charconst) {
            one.name = line;
            one.type = "const char";
            one.type_for_check = "imm";
            return;
        }
    }
    std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::tolower(c); });
    one.name = line;
    if ((line == ":") || (line == ",") || (line == "[") || (line == "]") || (line == "*")) {
        one.type = "single character";
    }
    else {
        for (auto i : DictionaryOfTokens) {
            if (line == i.first) {
                one.type = i.second;
                if(one.type == "register 32"){
                    one.type_for_check = "reg";
                }
                return;
            }
        }
        for (int i = 0; i < line.size(); i++) {
            if (!isdigit(line[i])) {
                flag_10const = false;
            }
            if ((i == line.size() - 1) && (flag_10const == true)) {
                one.type_for_check = "imm";
                one.type = "decimal const";
                return;
            }
            if ((isdigit(line[0])) && (line[line.size() - 1] == 'h')) {
                one.type_for_check = "imm";
                one.type = "hexadecimal const";
                return;
            }
        }
        one.type = "user id or undifined";
        one.type_for_check = "mem";
    }

}

void CreateSyntax(vector<lexeme> AllTokens, struct_of_sentence& alone) {
    for (int i = 0; i < AllTokens.size(); i++) {
        if ((alone.number_of_operand2 > 0)) {
            alone.amount_of_operand2++;

            continue;
        }
        if ((alone.number_of_operand1 > 0) && (AllTokens[i].name != ",")) {
            alone.amount_of_operand1++;
            continue;
        }
        if ((AllTokens[i].type == "user id or undifined") && (i == 0)) {
            alone.number_of_label = AllTokens[i].number_of_lexem;
            continue;
        }
        if ((AllTokens[i].type == "label")) {
            alone.number_of_label = AllTokens[i].number_of_lexem;
            continue;
        }
        if ((AllTokens[i].type == "instruction") || (AllTokens[i].type == "directive") ||
            (AllTokens[i].type == "directiveIF_ENDIF") || (AllTokens[i].type == "segmentword") ||
            (AllTokens[i].type == "equ_directive")) {
            alone.amount_of_mnemonic = AllTokens[i].number_of_lexem;
            alone.amount_of_mnemonic = 1;
        }
        if (((AllTokens[i].type == "user id or undifined") || (AllTokens[i].type == "32 register") ||
             (AllTokens[i].type == "id_segment_register") || (AllTokens[i].type == "const char")
             || (AllTokens[i].type == "decimal const") || (AllTokens[i].type == "hexadecimal const"))) {
            alone.number_of_operand1 = AllTokens[i].number_of_lexem;
            alone.amount_of_operand1 = 1;
        }
        if ((AllTokens[i].name == ",")) {
            i++;
            alone.number_of_operand2 = AllTokens[i].number_of_lexem;
            alone.amount_of_operand2 = 1;
            continue;
        }
        alone.number_of_row = AllTokens[i].number_of_row;
    }
}

