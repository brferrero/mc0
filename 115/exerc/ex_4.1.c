#include <stdio.h>

int conta_digitos (int n, int d);
int main ()
{ 
  int a, b, i, permuta;
  printf("Digite dois inteiros: ");
  scanf("%d %d",&a,&b);
  permuta = 1;
  for (i = 1; i <= 9 && permuta; i++) {
    if (conta_digitos (a, i) != conta_digitos (b, i))
      permuta = 0;
  }
  if (permuta)
    printf ("%d e' permutacao de %d.\n", a, b);
  else printf ("%d NAO e' permutacao de %d.\n", a, b);
  return 0;
}

int conta_digitos (int n, int d)
{
  int cont;
  cont = 0;
  while (n != 0) {
    if (n%10 == d)
      cont++;
    n = n/10;
  }
  return cont;
}
