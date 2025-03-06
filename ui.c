#include "ui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Arg count must be exactly three, includes "kode" so count must be 4
void checkArgCount(int count)
{
    if (count != 4)
    {
        fprintf(stderr, "Incorrect arguement count, must be: <Command>, <Word>, <File>\n");
        exit(3);
    }
}

char confirmationMessage(const char *before, const char *after, int lineNumber)
{
    printf("\nChanging line %d from \n", lineNumber);
    printf("%s\n", before);
    printf("to\n");
    printf("%s\n", after);
    printf("Confirm?\nYes (Y),\nNo (N),\nAll (A),\nQuit (Q)");

    char answer;
    scanf(" %c", &answer);
    return tolower(answer);
}

void finalCount(int wordsChanged, int linesChanged)
{
    printf("\nChanged %d word(s) in %d line(s)\n", wordsChanged, linesChanged);
}

void noChangeMessage()
{
    printf("\n0 changes made\n");
}

void displayError(const char *errorMessage){
    fprintf(stderr, "%s\n", errorMessage);
    exit(3);
}
