from base_information import types_of_lexemes


def get_key(dictionary, value):
    for k, v in dictionary.items():
        if v == value:
            return k

# check push
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

    def __init__(self, name, number, ):
        self.type_of = determine_type(name)
        if determine_type(name) == 'char const':
            self.name = name
        else:
            self.name = name.lower()
        self.number = number

    def __print__(self):
        print("%s %s", self.name, self.type_of)

    def reconstructor(self, name, type_of, number):
        self.type_of = type_of
        self.name = name
        self.number = number

    def set_name(self, name):
        self.name = name

    def set_type_of(self, type_of):
        self.type_of = type_of

    def __repr__(self):
        return '|{:3}|{:15}|{:8}|{:19}|'.format(self.number, self.name, len(self.name), self.type_of)


class OneLine(object):
    def __init__(self, one_line_of_lexeme):
        self.list_of_this_line = one_line_of_lexeme
        self.name = ''
        for one_lexeme in one_line_of_lexeme:
            self.name += str(one_lexeme.name) + ' '
        self.displacement = 0

    def new_disp_of_line(self, displacement):
        self.displacement = displacement

    def __repr__(self):
        return '{}'.format(self.name)
