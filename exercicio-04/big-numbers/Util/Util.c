#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

void boolean_print(boolean bool)
{
    if(bool == TRUE)
    {
        printf("True\n");
    }
    else if(bool == FALSE)
    {
        printf("False\n");
    }
    else
    {
        printf("ERRO\n");
    }
}

int power(int x, int y){
      if(y == 0)
        return 1;
     return (x * power(x,y-1) );
    }