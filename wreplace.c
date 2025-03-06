#include "./wreplace.h"
#include "ui.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int wordsChanged = 0;

static char *initBuffer(int length)
{
    char *buffer = (char *)malloc((length + 1) * sizeof(char));
    if (buffer == NULL)
    {
        displayError("Couldnt allocate memory");
    }
    buffer[length] = '\0';
    return buffer;
}

// Replaces a substring with a substitution
static void replace(char *original, const char *substitution, int start)
{
    for (int i = 0; substitution[i]; i++)
    {
        original[start + i] = substitution[i];
    }
    wordsChanged++;
}

// Builds a string of *
static char *censorBuilder(int length)
{
    char *censor = initBuffer(length);
    for (int i = 0; i < length; i++)
    {
        censor[i] = '*';
    }

    return censor;
}

static void toLowerCase(char *original)
{
    for (int i = 0; original[i]; i++)
    {
        original[i] = tolower(original[i]);
    }
}

static void toUpperCase(char *original)
{
    for (int i = 0; original[i]; i++)
    {
        original[i] = toupper(original[i]);
    }
}

char *commandRC(const char *word, const char *before)
{
    char *censor = censorBuilder(strlen(word));

    // Save before
    char *after = initBuffer(strlen(before));
    strcpy(after, before);

    char *found = strstr(after, word);
    while (found)
    {
        int start = found - after;
        replace(after, censor, start);

        found = strstr(found + strlen(word), word);
    }

    free(censor);

    return after;
}

char *commandRI(const char *word, const char *before)
{
    char *censor = censorBuilder(strlen(word));

    // Save before
    char *after = initBuffer(strlen(before));
    strcpy(after, before);

    // Make a temp variable to hold a lower case version of the text
    char *tempAfter = initBuffer(strlen(after));
    strcpy(tempAfter, after);

    // Same here
    char *tempWord = initBuffer(strlen(word));
    strcpy(tempWord, word);

    // Lower case temp and word
    toLowerCase(tempAfter);
    toLowerCase(tempWord);

    char *found = strstr(tempAfter, tempWord);
    while (found)
    {
        int start = found - tempAfter;
        replace(after, censor, start);

        found = strstr(found + strlen(tempWord), tempWord);
    }

    free(censor);
    free(tempAfter);
    free(tempWord);

    return after;
}

char *commandUK(const char *word, const char *before)
{
    // Save before
    char *after = initBuffer(strlen(before));
    strcpy(after, before);

    char *found = strstr(after, "*");
    while (found)
    {
        int start = found - after;
        while (*found == '*')
        {
            found++;
        }

        int end = found - after;
        int length = end - start;

        if (length == strlen(word))
        {
            replace(after, word, start);
        }

        found = strstr(found, "*");
    }

    return after;
}

char *commandUM(const char *word, const char *before)
{
    // Save before
    char *after = initBuffer(strlen(before));
    strcpy(after, before);

    // Used in case word needs to be turned into upper or lower case
    char *tempWord = initBuffer(strlen(word));

    char *found = strstr(after, "*");
    while (found)
    {

        int start = found - after;
        while (*found == '*')
        {
            found++;
        }

        int end = found - after;
        int length = end - start;

        if (length == strlen(word))
        {
            strcpy(tempWord, word);

            // Bounds checking
            if (start >= 1 && isalpha(after[start - 1]))
            {
                if (isupper(after[start - 1]))
                {
                    toUpperCase(tempWord);
                }
                else
                {
                    toLowerCase(tempWord);
                }
            }
            else if (isalpha(after[end]))
            {
                if (isupper(after[end]))
                {
                    toUpperCase(tempWord);
                }
                else
                {
                    toLowerCase(tempWord);
                }
            }

            replace(after, tempWord, start);
        }

        found = strstr(found, "*");
    }

    free(tempWord);

    return after;
}