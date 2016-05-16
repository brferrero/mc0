/*
 * LISTA 03 - Lista Ligada
 * ex. 6)
 *
 * Bruno Ferrero   nUSP 3690142
 * Data: 12/04/2010 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main ()
{   
    int i;
    lista a;
    lista b;
    lista c;
    a = LISTAinicia (a);
    b = LISTAinicia (b);
    for (i = 0; i < 4; i++)
        a = LISTAinsere (a,i+2);
    a = LISTAinsere (a,15);    
    for (i = 1; i <= 10; i++)
        b = LISTAinsere (b,i); 
    printf ("lista A:\n");
    LISTAdump (a);
    printf ("lista B:\n");
    LISTAdump (b);

    printf ("Uniao (A,B):\n");
    c = uniao (a,b);
    LISTAdump (c);
    printf ("Interseccao (A,B):\n");
    c = interseccao (a,b);
    LISTAdump (c);
    printf ("Diferenca (A,B):\n");
    c = diferenca (a,b);
    LISTAdump (c);
    return 0;
}
