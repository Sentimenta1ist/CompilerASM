from base_information import types_of_lexemes


def get_key(dictionary, value):
    for k, v in dictionary.items():
        if v == value:
            return k


def determine_type(name):
    work_space = ''
    work_space += name
    work_space = work_space.lower()
    if len(work_space) == 0:
        return ''

    if work_space[len(work_space) - 1] == 'h' and work_space[0].isdigit():
        return 'hex const'
    if work_space.isdigit():
        return 'decimal const'
    if work_space[len(work_space) - 1] == '\"' and work_space[0] == '\"':
        return 'char const'

    for one_type in types_of_lexemes.values():
        for one_lexeme in one_type:
            if one_lexeme == work_space:
                return get_key(types_of_lexemes, one_type)

    return 'memory or undefined'


class OneLexeme(object):

    def __init__(self, name, type_of, number):
        self.name = name
        self.type_of = type_of
        self.number = number

    def __print__(self):
        print("%s %s", self.name, self.type_of)

    def reconstructor(self, name, type_of, number):
        self.name = name
        self.type_of = type_of
        self.number = number

    def set_name(self, name):
        self.name = name

    def set_type_of(self, type_of):
        self.type_of = type_of

    def __repr__(self):
        return '(# - {}; name - {}; type - {})\n'.format(self.number,self.name, self.type_of)
