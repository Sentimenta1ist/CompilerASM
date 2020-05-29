REG_8 = 'reg 8'
REG_16 = 'reg 16'
DIRECTIVE = 'directive'
INSTRUCTION = 'instruction'
SEGMENT_WORD = 'segment word'
LABEL_SEGMENT = 'segment label'
ONE_SYMBL_LEXEME = 'one smb lexeme'


class InstructionInformation(object):
    def __init__(self, name, opcode):
        self.name = name;



        

types_of_lexemes = {
    REG_16: ['ax', 'cx', 'dx', 'bx', 'sp', 'bp', 'si', 'di'],
    REG_8: ['al', 'cl', 'dl', 'bl', 'ah', 'ch', 'dh', 'bh'],
    INSTRUCTION: ['jg', 'dec', 'lods', 'test', 'or', 'rol', 'das', 'add', 'mov'],
    DIRECTIVE: ['db', 'dd'],
    LABEL_SEGMENT: ['code', 'data'],
    ONE_SYMBL_LEXEME: [';', ',', ':', ']', '[', '+', '*'],
    SEGMENT_WORD: ['segment', 'end', 'ends']
}

global_dictionary = [

]

all_lexemes = []

all_lines_of_lexemes = []