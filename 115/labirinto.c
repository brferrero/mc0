#include <stdio.h>
#include <stdlib.h>

#define MMAX 200
#define NMAX 200

/*
  Este programa recebe m, n, p e s como entrada.
  Ele gera um labirinto aleatorio com m linhas e
  n colunas.  Cada casa do labirinto est'a livre
  com probabilidade p e bloqueada com
  probabilidade 1 - p, independentemente.
  O inteiro s 'e usado como a semente do gerador
  de numeros aleatorios. 
 */

int main()
{
    int m, n, pp, qq, seed;
    double p;
    int L[MMAX][NMAX];
    int i, j;

    printf("Forneca m, n, p e s.\n");
    scanf("%d %d %lf %d", &m, &n, &p, &seed);

    srand(seed);
    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    if (rand() < RAND_MAX * p)
		L[i][j] = 0;
	    else
		L[i][j] = -1;

    pp = 1 + m * (rand() / (1.0 * RAND_MAX + 1));
    qq = 1 + n * (rand() / (1.0 * RAND_MAX + 1));

    L[0][0] = L[pp - 1][qq - 1] = 0;

    printf("Labirinto gerado com %d linhas e %d colunas:\n", m, n);
    for (i = 0; i < m; i++) {
	for (j = 0; j < n; j++)
	    printf("%3d", L[i][j]);
	printf("\n");
    }
    printf("Posicao do pedaco de queijo: (%d, %d)\n", pp, qq);

    printf("No formato para seu ep3:\n\n");
    printf("%d %d\n", m, n);
    for (i = 0; i < m; i++) {
	for (j = 0; j < n; j++)
	    if (L[i][j] == 0)
		printf(".");
	    else
		printf("*");
	printf("\n");
    }
    printf("%d %d\n", pp, qq);

    return 0;
}

