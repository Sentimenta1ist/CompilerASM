from base_information import dictionary_of_instructions


def error_of_operand(operand_1, operand_2):
    for one_instruction in dictionary_of_instructions:
        if operand_1 == one_instruction.operand_1 and operand_2 == one_instruction.operand_2:
            return 0
    return 1
