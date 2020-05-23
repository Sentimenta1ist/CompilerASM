import base_information
from base_information import types_of_lexemes
from line import OneLexeme
from line import determine_type


def read_from_file(test_file):
    file = open(test_file, "r")
    for line in file:
        line.expandtabs()

        # this cycle change all determinate from '+' to ' + '
        # after changing split on space
        for symbol in types_of_lexemes.get(base_information.ONE_SYMBL_LEXEME):
            new_symbol = ' ' + symbol + ' '
            line = line.replace(symbol, new_symbol)
        one_line_of_lexemes = line.split()

        vector_of_lines = []
        for one_lexeme in one_line_of_lexemes:
            lexeme = OneLexeme(one_lexeme, determine_type(one_lexeme))
            vector_of_lines.append(lexeme)
        base_information.all_lexemes.append(vector_of_lines)
    for one_element in base_information.all_lexemes:
        print(one_element)

