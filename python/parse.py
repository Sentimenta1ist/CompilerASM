import base_information
from base_information import types_of_lexemes

def read_from_file(test_file):
    file = open(test_file, "r")
    for line in file:
        line.expandtabs()
        for symbol in types_of_lexemes.get(base_information.ONE_SYMBL_LEXEME):
            new_symbol = ' ' + symbol + ' '
            line = line.replace(symbol, new_symbol)
        result = line.split()

        print(result)
