#ifndef makeWordList_H_
#define makeWordList_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "treeWithUniqueChars.h"
#include "options.h"

void subsituteCharacters(char *singleWord, char *toBeSubstituted[], char *replacementChars[], int numberOfCharsToBeSubstituted);
int makeWordList(int numberOfCharacters, char *outputWordlist);

#endif