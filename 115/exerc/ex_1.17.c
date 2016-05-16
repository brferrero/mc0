#include<stdio.h>
int main ()
{
  int decimal, base, resto, binario, pot10, aux;
  printf("leia um decimal e a base para conversao :");
  scanf("%d%d",&decimal,&base);
  aux = decimal;
  pot10=1;
  binario = 0;
  while (decimal > 0) {
    resto = decimal%base;
    decimal = decimal/base;
    binario = binario + resto * pot10;
    pot10 = pot10 * 10;
  }
  printf("O numero %d escrito na base %d: %d\n", aux, base, binario);
 return 0;
}
