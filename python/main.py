import os
import base_information
from parse import read_from_file
from line import determine_type
from line import OneLine


def lexeme_and_syntax(file_name):
    file = open(file_name, "r")
    lines_of_file = file.read().splitlines()
    i = 0
    for line_of_lex in base_information.all_lexemes:
        print(lines_of_file[i]+'\n')
        i += 1
        print("| # |Lex            |     Len|Type               |\n"
              "|---|---------------|--------|-------------------|")
        for lexeme in line_of_lex:
            print(lexeme)
        print('--------------------------------------------------\n')


if __name__ == "__main__":
    read_from_file("test.asm")
    lexeme_and_syntax("test.asm")

    for line in base_information.all_lexemes:
        base_information.all_lines_of_lexemes.append(OneLine(line))

    for i in base_information.all_lines_of_lexemes:
       # print(i)
