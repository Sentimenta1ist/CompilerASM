#include "Line.h"

Line::Line() {
    displacement = 0;
}


Line::Line(const vector<lexeme> &lineOfLexeme) : line_of_lexeme(lineOfLexeme) {}
