#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

char **readFile(const char *fileName, int *lines)
{
    FILE *file;
    long size;
    char *buffer;

    file = fopen(fileName, "r");

    // Make sure file is read
    if (file == NULL)
    {
        displayError("Could not open file");
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    // Allocate
    buffer = (char *)malloc(size + 1); // Null terminator
    if (buffer == NULL)
    {
        fclose(file);
        displayError("Couldnt allocate memory");
    }

    // Read
    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    // Getting number of new lines
    *lines = 1;
    for (int i = 0; i < size; i++)
    {
        if (buffer[i] == '\n')
        {
            (*lines)++;
        }
    }

    fclose(file);

    char **bufferLines = (char **)malloc((*lines) * sizeof(char *));

    // Seperate by lines
    char *token = strtok(buffer, "\n");
    int indexCounter = 0;
    while (token != NULL)
    {
        bufferLines[indexCounter] = token;
        indexCounter++;
        token = strtok(NULL, "\n");
    }

    return bufferLines;
}

void writeFile(const char **contents, const char *fileName, int lineNumbers)
{
    FILE *file;

    file = fopen(fileName, "w");

    for (int i = 0; i < lineNumbers; i++)
    {
        fprintf(file, contents[i]);
        if (i < lineNumbers - 1) // On last row, do not add new line
        {
            fprintf(file, "\n");
        }
    }

    fclose(file);
}