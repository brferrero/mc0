#include <stdio.h>

int main()
{
  int num, multi, nat;
  printf("Entre com o numero (> 1) a ser decomposto : ");
  scanf("%d",&num);
  nat=2;
  printf("FATOR     MULTIPLICIDADE \n");
  while (num > 1) {
    multi = 0;
    while (num%nat == 0) {
      num = num/nat;
      multi++;
    }
    if (multi > 0)
      printf("%3d          %5d\n",nat,multi);
    nat++;
  }
  return 0;
}

