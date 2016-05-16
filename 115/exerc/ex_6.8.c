#include <stdio.h>
#define MAX 20

int main ()
{
  int v1[MAX], v2[MAX], vetor[2*MAX], i, m, n, j, k;
  printf ("Entre com o tamanho de dois vetores : ");
  scanf ("%d%d", &m, &n);
  for (i = 0; i < m; i++) {
    printf ("entre com o %d elemento do vetor 1 : ", i+1);
    scanf ("%d", &v1[i]);
  }
  for (i = 0; i < n; i++) {
    printf ("entre com o %d elemento do vetor 2 : ", i+1);
    scanf ("%d", &v2[i]);
  }
  i = j = k = 0;
  while (i < m && j < n) {
    if (v1[i] < v2[j]) {
      vetor[k] = v1[i];
      i++; k++;
    }
    else {
      if (v1[i] == v2[j]) {
	vetor[k] = v1[i];
	j++; i++; k++;
      }
      else {
	vetor[k] = v2[j];
	j++; k++;
      }
    }
  }
  while (i < m)
    vetor[k] = v1[i];
  while (j < n)
    vetor[k] = v2[j];
  for (i = 0; i < k; i++) 
    printf ("%d ", vetor[i]);
  printf ("\n");

  return 0;
}
  

