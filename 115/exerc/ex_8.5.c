#include <stdio.h>
#define MAX 50

void max (int n, int a[][MAX], int *pk, int *plin, int *pcol);
void le_matriz (int matriz[][MAX], int lin, int col);
void escreve_matriz (int matriz[][MAX], int lin, int col); 

int main ()
{
  int i, j, n, maior, linha, coluna, a[MAX][MAX];
  printf ("Digite o tamanho da matriz : ");
  scanf ("%d", &n);
  le_matriz (a, n, n);
  escreve_matriz (a, n, n);
  printf ("Elemento \t linha \t coluna \n"); 
  for (i = 0; i < n*n; i++) {
    max (n, a, &maior, &linha, &coluna);
    a[linha][coluna] = 0;
    printf ("%4d \t %11d \t %4d \n", maior, linha, coluna);
  }
  return 0;
}

void le_matriz (int matriz[][MAX], int lin, int col)
{
  int i, j;
  for (i = 0; i < lin; i++) {
    printf ("Entre com os %d elementos da linha %d : ", col, i);
    for (j = 0; j < col; j++)
      scanf ("%d", &matriz[i][j]);
  }
}

void escreve_matriz (int matriz[][MAX], int lin, int col)
{
  int i, j;
  for (i = 0; i < lin; i++) {
    for (j = 0; j < col; j++)
      printf (" %4d", matriz[i][j]);
    printf ("\n");
  }
}

void max (int n, int a[][MAX], int *pk, int *plin, int *pcol)
{
  int i, j, maior, linha, coluna;
  maior = a[n][n];
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      if (a[i][j] > maior) {
	maior = a[i][j];
	*plin = i;
	*pcol = j;
      }
  }
  *pk = maior;
}
