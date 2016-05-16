#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S "Hello, World\n"
int main () 
{
    exit (printf (S) == strlen (S) ? 0 : 1);
}
