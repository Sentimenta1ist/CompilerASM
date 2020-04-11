#pragma once

#include "Addition.h"

void IdentifyLexeme(lexeme &, string, int, int);

void CreateSyntax(vector<lexeme>, struct_of_sentence &alone);

void LoadFromFile(const char *);

void Displacement(const char *);

