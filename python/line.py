from base_information import types_of_lexemes


def determine_type(name):

    for one_type in types_of_lexemes.values():
        print(one_type)


class OneLexeme(object):

    def __init__(self, name, type_of):
        self.name = name
        self.type_of = type_of

    def reconstructor(self, name, type_of):
        self.name = name
        self.type_of = type_of

    def set_name(self, name):
        self.name = name

    def set_type_of(self, type_of):
        self.type_of = type_of


