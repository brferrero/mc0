#include <stdio.h>
int main ()
{
  int n, i, soma;
  printf("Entre com um No inteiro positivo para verificar se ele e perfeito : ");
  scanf("%d",&n);
  soma = 0;
  for (i=1; i<n; i++) {
    if (n%i==0) 
      soma = soma + i;
  }
  if (soma == n)
    printf("%d e' um numero perfeito\n",n);
  else 
    printf("%d NAO e' um numero perfeito\n",n); 
  return 0;
}
