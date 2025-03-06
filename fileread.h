#ifndef fileread
#define fileread

#include <string.h>

char **readFile(const char *fileName, int *lines);
void writeFile(char **contents, const char *fileName, int lineNumber);

#endif