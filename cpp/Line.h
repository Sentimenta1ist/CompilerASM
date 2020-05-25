#ifndef COURSEWORK_LINE_H
#define COURSEWORK_LINE_H

#include "Base.h"

class Line{
public:
    Line();

    Line(const vector <lexeme> &lineOfLexeme);

    ~Line()= default;;

private:
    int displacement;
    vector<lexeme>line_of_lexeme;

};


#endif //COURSEWORK_LINE_H
