REG_8 = 'reg 8'
REG_16 = 'reg 16'

MEM_8 = 'mem 8'
MEM_16 = 'mem 16'

IMM_8 = 'imm 8'
IMM_16 = 'imm 16'

SEG_REG = 'segment register'

DIRECTIVE = 'directive'
INSTRUCTION = 'instruction'
SEGMENT_WORD = 'segment word'
LABEL_SEGMENT = 'segment label'
ONE_SYMBL_LEXEME = 'one smb lexeme'
NONE_OPERAND = 'no operand'

#today go to kiev :3

# 48+rw     DEC r16
# FE /1     DEC r/m8

# AD        LODS m16
# AC        LODS m8

# 84 /r     TEST r/m8, r8
# 85 /r     TEST r/m16, r16

# 08 /r     OR r/m8, r8
# 09 /r     OR r/m16, r16
# 0A /r     OR r8, r/m8
# 0B /r     OR r16, r/m16
#
# C0 /0 ib  ROL r/m8, imm8
# C0 /0 ib  ROL r/m16, imm8
#
# 2F        DAS
#
# 80 /0 ib  ADD r/m8, imm8
# 81 /0 iw  ADD r/m16, imm16
# 83 /0 ib  ADD r/m16, imm8
#
# 04 ib     ADD AL, imm8
# 05 iw     ADD AX, imm16
#
# 88 /r     MOV r/m8, r8
# 89 /r     MOV r/m16, r16
# 8C /r     MOV r/m16, S_reg


class InstructionInformation(object):
    def __init__(self, name, op_code, operand_1, operand_2, mod_rm, reg_in_op_code):
        self.name = name
        self.op_code = op_code
        self.operand_1 = operand_1
        self.operand_2 = operand_2
        self.mod_rm = mod_rm
        self.reg_in_op_code = reg_in_op_code


dictionary_of_instructions = [
    InstructionInformation("dec", 0x48, REG_8, NONE_OPERAND, mod_rm=0, reg_in_op_code=1),
    InstructionInformation("dec", 0xFE, REG_16, NONE_OPERAND, mod_rm=1, reg_in_op_code=0),

    InstructionInformation("lods", 0xAD, MEM_8, NONE_OPERAND, mod_rm=0, reg_in_op_code=0),
    InstructionInformation("lods", 0xAC, MEM_8, NONE_OPERAND, mod_rm=0, reg_in_op_code=0),

    InstructionInformation("test", 0x84, REG_8, REG_8, mod_rm=1, reg_in_op_code=0),
    InstructionInformation("test", 0x85, REG_16, REG_16, mod_rm=1, reg_in_op_code=0),

    InstructionInformation("or", 0x0A, REG_16, MEM_16, mod_rm=1, reg_in_op_code=0),
    InstructionInformation("or", 0x0A, REG_8, MEM_8, mod_rm=1, reg_in_op_code=0),

    InstructionInformation("das", 0x2F, NONE_OPERAND, NONE_OPERAND, mod_rm=0, reg_in_op_code=0),

    InstructionInformation("add", 0x80, REG_8, IMM_8, mod_rm=0, reg_in_op_code=0),
    InstructionInformation("add", 0x81, REG_8, IMM_8, mod_rm=0, reg_in_op_code=0),
    InstructionInformation("add", 0x83, REG_16, IMM_8, mod_rm=0, reg_in_op_code=0),

    InstructionInformation("mov", 0x88, MEM_8, REG_8, mod_rm=1, reg_in_op_code=0),
    InstructionInformation("mov", 0x89, MEM_16, REG_16, mod_rm=1, reg_in_op_code=0),
    InstructionInformation("mov", 0x8C, MEM_8, SEG_REG, mod_rm=1, reg_in_op_code=0)

]

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
