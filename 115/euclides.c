#include<stdio.h>
int main ()
{
  int atu, ant, resto;
  printf("Entre com os dois numeros inteiros para determinar o MDC : ");
  scanf("%d%d",&ant,&atu);
  printf("MDC(%d,%d) = ", ant, atu);
  while ((ant%atu) != 0) {
    resto = ant%atu;
    ant = atu;
    atu = resto;
  }
  printf("%d\n",atu);
  return 0;
}
