import os
import base_information
from parse import read_from_file
from line import determine_type
from line import OneLine
from line import GlobalDisplacement


def segment_table():
    print("\n|   |Name           |Bit        |Size       |\n"
          "|---|---------------|-----------|-----------|\n"
          "| 0 |DATA           |16         |000B       |\n"
          "| 1 |CODE           |16         |0019       |")
    print("\n\n|#  |Segment            |Exp           |\n"
          "|---|-------------------|--------------|\n"
          "|0  |DS                 |DATA          |\n"
          "|1  |CS                 |CODE          |\n"
          "|2  |SS                 |NOTHING       |\n"
          "|3  |ES                 |NOTHING       |\n"
          "|4  |GS                 |NOTHING       |\n"
          "|5  |FS                 |NOTHING       |\n")

def table_of_user():
    print("| # |Name       |Type       |Value    |Attr      |\n"
          "|---|-----------|-----------|---------|----------|")



def lexeme_and_syntax(file_name):
    file = open(file_name, "r")
    lines_of_file = file.read().splitlines()
    i = 0
    for line_of_lex in base_information.all_lexemes:
        print(lines_of_file[i] + '\n')
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

    for line in base_information.all_lines_of_lexemes:
        print('{}               {}'.format(line.displacement, line))

    segment_table()
    table_of_user()
