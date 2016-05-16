#include <stdio.h>
int main()
{
  int n, i, j, aux, lido, soma, cont;
  printf("Leia o numero de elementos da sequencia : ");
  scanf("%d",&n);
  soma = 0;
  for (i=1; i<=n; i++) {
    printf("Leia o %do elemento da sequencia : ",i);
    scanf("%d",&lido);
    if (lido !=1 ) {
      aux = 0;
      cont = 2;
      while (cont < lido) {
	if (lido%cont == 0) 
	  aux = aux + 1;
	cont++;
      }
      if (aux == 0) 
	soma = soma + lido;
    }
  }
  printf("a soma dos primos da seq e : %d\n", soma);
  return 0;
}


