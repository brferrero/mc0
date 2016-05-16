#include <stdio.h>

int main ()
{
  int n, i;
  printf ("Digite um inteiro positivo : ");
  scanf ("%d", &n);
  for (i = 1; i*(i + 1)*(i + 2) < n; i++);
  if ((i * (i+1) * (i+2)) == n)
    printf ("%d * %d * %d = %d\n", i, i+1, i+2, n);
  else printf ("%d nao e' triangular, \n", n);
  return 0;
}

  
