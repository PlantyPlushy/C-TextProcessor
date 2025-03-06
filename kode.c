#include "./ui.h"
#include "./wreplace.h"
#include "fileread.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char *handleCommand(const char *command, const char *word, char *text)
{
    if (strcmp("RC", command) == 0)
    {
        return commandRC(word, text);
    }
    else if (strcmp("RI", command) == 0)
    {
        return commandRI(word, text);
    }
    else if (strcmp("UK", command) == 0)
    {
        return commandUK(word, text);
    }
    else if (strcmp("UM", command) == 0)
    {
        return commandUM(word, text);
    }
    else
    {
        displayError("Invalid modifcation command. Terminating");
        return NULL;
    }
}

int main(int argc, char const *argv[])
{

    // Handle the number of command line arguements,
    // Must be exactly 3 args (command, word, file),
    // Less or more is an error
    checkArgCount(argc);

    // Read given file
    int lineNumber = 0;
    char **beforeResult = readFile(argv[3], &lineNumber);
    char **afterResult = (char **)malloc((lineNumber) * sizeof(char *));

    char input = 'y';
    bool pressedQuit = false;
    int linesChanged = 0;

    // Handle command
    for (int i = 0; i < lineNumber; i++)
    {
        int oldWordsChanged = wordsChanged;
        char *after = handleCommand(argv[1], argv[2], beforeResult[i]);
        if (input != 'a' && input != 'q')
        {
            input = confirmationMessage(beforeResult[i], after, i + 1);
        }

        if (input == 'y' || input == 'a')
        {
            afterResult[i] = after;
            // Check if there was a word that changed in line
            if (oldWordsChanged < wordsChanged)
            {
                linesChanged++;
            }
        }
        else if (input == 'n' || input == 'q')
        {
            afterResult[i] = beforeResult[i];
            pressedQuit = input == 'q';
            // because the handle command just copies the string, the replace
            // function just ends up counting "wordsChanged". This prevents this bug
            wordsChanged = oldWordsChanged;
        }
        else
        {
            i--; // go back a step
            printf("invalid command");
        }
    }

    writeFile(afterResult, argv[3], lineNumber);

    // Handling exit codes

    // Clean up
    free(beforeResult);
    free(afterResult);

    // Pressed quit?
    if (pressedQuit)
    {
        finalCount(wordsChanged, linesChanged);
        return 1;
    }
    // No changes made
    else if (wordsChanged <= 0)
    {
        noChangeMessage();
        return 2;
    }
    // Program is all
    else
    {
        finalCount(wordsChanged, linesChanged);
        return 0;
    }
}
