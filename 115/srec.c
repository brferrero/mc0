#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int a[5] = {1, 2, 3, 4, 5};
    printf ("soma = %d\n", somaR (a, 4));

    return 0;
}

int somaR (int a[], int n)
{
    if (n == 0)
        return a[0];
    else return a[n] + somaR(a,n-1);
}
