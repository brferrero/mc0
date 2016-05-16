#include <stdio.h>
#define MAX 50

int main ()
{
  int n, cont, i, j, seq[MAX], aux, vet_cont[MAX];
  printf ("entre com o tamnho da seq : ");
  scanf ("%d", &n);
  printf ("entre com os %d elementos da seq : ", n);
  for (i = 0; i < n; i++)
    scanf ("%d", &seq[i]);
  for (i = 0; i < n; i++) {
    cont = 0;
    printf (" %d aparece ", seq[i]);
    for(j = 0; j < n; j++)
      if (seq[j] == seq[i])
	cont++;
    printf (" %d \n", cont);
  }
  return 0;
}


/* #include <stdio.h> */
/* #define MAX 100 */

/* int main() { */

/*   int n,	     /\* comprimento da sequencia de entrada                *\/ */
/*     i, j, */
/*     conta[MAX],    /\* contador de repeticoes de cada numero da sequencia *\/ */
/*     comp = 0;      /\* comprimento do vetor conta                         *\/		 */
/*   float seq[MAX];   /\* sequencia de entrada sem repeticoes                *\/ */

/*   printf("\nDigite o comprimento da sequencia: "); */
/*   scanf("%d", &n); */

/*   printf("Digite uma sequencia de %d numeros reais: ", n); */
/*   for (i = 0; i < n; i++) { */
/*     scanf("%f", &seq[comp]); */
/*     /\* procura esse numero no vetor seq a partir do inicio *\/ */
/*     for (j = 0; seq[j] != seq[comp]; j++);  /\* comando vazio! *\/ */
/*     if (j == comp) { */
/*       /\* se o numero nunca tinha aparecido *\/ */
/*       conta[comp] = 1; */
/*       comp++; */
/*     } */
/*     else  */
/*       conta[j]++; */
/*   } */

/*   /\* imprime o resultado *\/ */
/*   for (j = 0; j < comp; j++)  */
/*     printf("O numero %f aparece %d vezes na sequencia.\n", seq[j], conta[j]); */
/*   return 0; */
/* } */
