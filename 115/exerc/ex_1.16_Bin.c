#include<stdio.h>
int main()
{
  int binario, pot, decimal;
  printf("Entre com um mumero binario : ");
  scanf("%d",&binario);
  pot=1;
  decimal=0;
  while (binario != 0) {
    decimal = decimal + binario%10*pot;
    binario = binario/10;
    pot = pot*2;
  }
 printf("%d\n", decimal);
 return 0;
}

