#include "FirstSecondStage.h"



void CreateSyntax(vector<lexeme> Tokens, struct_of_sentence& alone) {
    for (int i = 0; i < Tokens.size(); i++) {
        if ((alone.number_of_operand2 > 0)) {
            alone.amount_of_operand2++;
            continue;
        }
        if ((alone.number_of_operand1 > 0) && (Tokens[i].name != ",")) {
            alone.amount_of_operand1++;
            continue;
        }
        if ((Tokens[i].type == userId) && (i == 0)) {
            alone.number_of_label = Tokens[i].number_of_lexem;
            continue;
        }
        if ((Tokens[i].type == label)||(Tokens[i].type == labelSeg)) {
            alone.number_of_label = Tokens[i].number_of_lexem;
            continue;
        }
        if ((Tokens[i].type == instruction) || (Tokens[i].type == directive) ||
            (Tokens[i].type == "directiveIF_ENDIF") || (Tokens[i].type == segmentWord)) {
            alone.number_of_mnemonic = Tokens[i].number_of_lexem;
            alone.amount_of_mnemonic = 1;
            continue;
        }
        if (((Tokens[i].type == userId) || (Tokens[i].type == reg) ||
             (Tokens[i].type == segmentWord) || (Tokens[i].type == constChar)
             || (Tokens[i].type == constDecimal) || (Tokens[i].type == constHex) || (Tokens[i].name == "["))) {
            alone.number_of_operand1 = Tokens[i].number_of_lexem;
            alone.amount_of_operand1 = 1;
        }
        if ((Tokens[i].name == ",")) {
            i++;
            alone.number_of_operand2 = Tokens[i].number_of_lexem;
            alone.amount_of_operand2 = 1;
            continue;
        }
        alone.number_of_row = Tokens[i].number_of_row;
    }
}

void LexemeSyntax(const char* file , bool out){
    string line;
    int indicator_of_rows = -1;
    lexeme one;
    ifstream in(file);
    if (in.is_open()){
        while (getline(in, line)) {
            indicator_of_rows++;
            struct_of_sentence alone;
            CreateSyntax(AllTokens[indicator_of_rows], alone);
            AllStruct.push_back(alone);
            if(out){
                cout << "" << line << endl << endl;
                cout << " Lexical analysis:" << endl;
                cout << " ------------------------------------------------" << endl;
                cout << "| # |      Lex      |   Len  |      Type         |" << endl;
                cout << "|---|---------------|--------|-------------------|" << endl;
                for(int j = 0; j < AllTokens[indicator_of_rows].size(); j++){
                    cout << '|' << setw(3 )<< j << "|";
                    cout << setw(15) << AllTokens[indicator_of_rows][j].name << '|';
                    cout << setw(8) << AllTokens[indicator_of_rows][j].name.size() << "|";
                    cout << setw(19) << AllTokens[indicator_of_rows][j].type << "|" << endl;
                }
                cout << "-------------------------------------------------" << endl;
                cout << endl;
                cout << " Syntax :" << endl;
                cout << " ------------------------------------------------" << endl;
                if(alone.number_of_label == -1) cout << "|      |";
                else cout << "|" << setw(6) << alone.number_of_label << "|";
                if(alone.number_of_mnemonic == -1) cout << "      |";
                else cout << setw(6) << alone.number_of_mnemonic << "|";
                if(alone.amount_of_mnemonic == -1) cout << "      |";
                else cout << setw(6) << alone.amount_of_mnemonic << "|";
                if(alone.number_of_operand1 == -1) cout << "      |";
                else cout << setw(6) << alone.number_of_operand1 << "|";
                if(alone.amount_of_operand1 == -1) cout << "      |";
                else cout << setw(6) << alone.amount_of_operand1 << "|";
                if(alone.number_of_operand2 == -1) cout << "      |";
                else cout << setw(6) << alone.number_of_operand2 << "|";
                if(alone.amount_of_operand2 == -1) cout << "      |";
                else cout << setw(6) << alone.amount_of_operand2 << "|";
                cout << endl;
                cout << " ------------------------------------------------" << endl;
                cout << endl;
            }
        }
    }
}