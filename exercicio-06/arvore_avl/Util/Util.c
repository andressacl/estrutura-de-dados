#include <stdio.h>
#include <stdlib.h>
// #include <stdbool.h>
#include "Util.h"

void boolean_print(boolean b)
{
    if(b == TRUE)
    {
        printf("True\n");
    }
    else if(b == FALSE)
    {
        printf("False\n");
    }
    else
    {
        printf("ERRO\n");
    }
}

char *readLine() {
    char *string = NULL;
    char currentInput;
    int index = 0;
    do {
        currentInput = (char)getchar();
        string = (char *) realloc(string, sizeof(char) * (index + 1));
        string[index] = currentInput;
        index++;
        if(currentInput == '\r')
        {
            currentInput = (char)getchar();
        }
    } while(((currentInput != '\n') && (currentInput != '\r')) && (currentInput != EOF));
    string[index - 1] = '\0';
    return string;
}

// int max(int a, int b){
//   if(a>b) return a;
//   return b;
// }
