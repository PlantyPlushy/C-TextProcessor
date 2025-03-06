#ifndef ui
#define ui

void checkArgCount(int count);
char confirmationMessage(const char *before, const char *after, int lineNumber);
void finalCount(int wordsChanged, int linesChanged);
void noChangeMessage();
void displayError(const char *errorMessage);

#endif