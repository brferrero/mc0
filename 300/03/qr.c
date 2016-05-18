/*
*
* Nome: Bruno Ferrero
*
* MAC300 - EP3: Matrizes ortogonais e o problema de quadrados mínimos
*
* Nov/2015  
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NMAX 1000
#define EPSILON 0.000000000001

/* Fatoracao QR: com reflexoes (Householder) */
void qr (int m, int n, double A[][NMAX], double norma[], double gama[], int p[]);
void calc_norma (int m, int n, double A[][NMAX], double norma[]);
void linsolve (int m, int n, double A[][NMAX], double norma[], double gama[], double b[], int p[]);

/*funcoes auxiliares*/
void swap (double *a, double *b);
void le_entrada (char *fname, int *m, int *n, double A[][NMAX], double b[NMAX]);
void imprime_matriz (double A[][NMAX], int m, int n);
void imprime_vetor (double x[NMAX], int m);
void imprime_indices (int i, int j);
void transposta (double A[][NMAX], int n);

/********************************************************************************/

int main (int argc, char *argv[])
{
    clock_t start, end;
    /*char fname[] = "exemplo10.dat";*/
    double A[NMAX][NMAX], b[NMAX], norma[NMAX], gama[NMAX];
    int p[NMAX];
    int n, m = 0;

    le_entrada (argv[1], &m, &n, A, b);
    /*imprime_matriz (A, m, n);*/
    start = clock();
    qr (m, n, A, norma, gama, p);
    end = clock();
    printf( "QR: %f segundos \n", (end-start)/(double)CLOCKS_PER_SEC );
    start = clock();
    linsolve (m, n, A, norma, gama, b, p);
    end = clock();
    printf( "Ax=b: %f segundos \n", (end-start)/(double)CLOCKS_PER_SEC );
    printf( "solução de Ax=b; \nx = \n");
    /*vetor x */
    imprime_vetor (b, n);

    return 0;
}

/********************************************************************************/

/* a funcao recebe uma matriz de dim m x n : o vetor norma armazena as normas   * 
 * das colunas de A; o vetor gama armazena os multiplicadores gama do metodo QR;*
 * e p guarda as permutacoes de colunas durante o processo.                     *
 * O resultado da fatoracao é armazenado na propria A e no vetor de norma: os   *
 * vetores ortogonais (Q) estão na parte triangular inferior. A diagonol da     *
 * da matriz triangular superior esta no vetor norma.                           */
void qr (int m, int n, double A[][NMAX], double norma[], double gama[], int p[])
{
    int i, j, k, jmax;
    double S[NMAX];

    /*gera vetor com normas das colunas de A*/ 
    calc_norma (m, n, A, norma);

    for (k = 0; k < n && k < m; k++) {
        p[k] = k;
        jmax = k;
        for (j = k+1; j < n; j++)
            if (norma[jmax] < norma[j])
                jmax = j;

        /*caso posto incompleto*/
        if (fabs(norma[jmax]) < EPSILON)
            break;
        
        /*permuta colunas */
        if ( k != jmax ) {
            p[k] = jmax;
            for (i = 0; i < m; i++) {
                S[0] = A[i][k];
                A[i][k] = A[i][jmax];
                A[i][jmax] = S[0];
            }
            S[0] = norma[jmax];
            norma[jmax] = norma[k];
            norma[k] = S[0];
        }
        /*gama e norma*/
        if (A[k][k] < 0) 
            norma[k] = (-1)*norma[k];
        
        A[k][k] = norma[k] + A[k][k];
        gama[k] = (A[k][k] / norma[k]);

        /*atualiza A: u esta na propria coluna da matriz*/
        for (i = k+1; i < m; i++)
            A[i][k] = A[i][k]/A[k][k];
        A[k][k] = 1.0;

        /*fazendo as multiplicacoes com as outras colunas da Q*/
        for (j = k + 1 ; j < m; j++)
            S[j] = 0.0;

        /*calcula todos os vetores S de uma vez so*/
        for (i = k; i < m; i++) 
            for (j = k+1; j < n; j++)
                S[j] += A[i][k] * A[i][j];

        for (j = k+1; j < n; j++)
            S[j] *= gama[k];

        /*percorre orientado a coluna para fazer a atualizacao*/
        for (i = k; i < m; i++)
            for (j = k+1; j < n; j++)
                A[i][j] -= S[j] * A[i][k];

        /*subtraindo a linha eliminada das normas das colunas restantes*/
        for (j = k+1 ; j < m; j++)
            norma[j] = sqrt (norma[j] * norma[j] - A[k][j] * A[k][j]);
    }
}

void calc_norma (int m, int n, double A[][NMAX], double norma[])
{
	int i, j;
	double max[NMAX];
    
    /*inicia vetor de normas*/
	for (j = 0; j < n; j++) norma[j]=0.0;

	/* buscando o maior numero evitar overflow*/
    for (j = 0; j < n ; j++) 
        max[j] = fabs(A[0][j]);
	
	for (i = 1 ; i < m; i++)
		for (j = 0; j < n ; j++)
			if (fabs(A[i][j]) > max[j]) 
                max[j] = fabs(A[i][j]);

    /*calcula norma das colunas de A: orientado a linhas*/    
	for (i = 0; i < m; i++)
		for (j = 0; j < n ; j++)
            norma[j] += (A[i][j]/max[j]) * (A[i][j]/max[j]);
	/* corrige magnitude da norma */
    for (j = 0; j < n; j++)
		norma[j] = max[j] * sqrt (norma[j]);
}

/* a funcao linsolve utiliza A e os vetores norma, gama e p calculados pela qr()*
 * e calcual Ax=b; A solucao é devolvida no proprio vetor b                     */
void linsolve (int m, int n, double A[][NMAX], double norma[], double gama[], double b[], int p[])
{
	int i, j, k;
	double S;

	/* multiplica Qb */
    for (k = 0; k < n; k++) {
		if (fabs (norma[k]) < EPSILON) break;
		S = 0.0;
		for (i = k; i < m; i++)
			S += A[i][k] * b[i];

		S *= gama[k];

		for (i = k; i < m; i++)
			b[i] -= S * A[i][k];
	}

	/*backrow*/
    for (i = k-1; i >= 0; i--) {
        for (j = i+1; j < n; j++)
            b[i] -= A[i][j] * b[j];
        /*reverte o sinal da norma*/
        b[i] = b[i] / -norma[i];
    }
	
    /*zerando x para o caso de posto incompleto*/
	for (j = k; j < n ; j++) b[j] = 0;
		
	/*desfaz permutacao*/
    for(i = k-1; i >= 0 ; i--) {
        swap (&b[i], &b[p[i]]);
    }
}


/********************************************************************************/

/* AUXILIARES */
/* le um arquivo de texto, cujo formato foi especificado no enunciado do EP */
void le_entrada (char *fname, int *m, int *n, double A[][NMAX], double b[NMAX])
{
    FILE *in = NULL;
    int i, j, k, mn;
    double a;

    in = fopen (fname, "r");
    if (in == NULL) {
        printf ("Erro de entrada.\n");
        exit (1);
    }

    fscanf (in, "%d %d", m, n);
    mn = (*m)*(*n);
    /*printf ("tam n = %d\n",mn);*/
    for (k = 0; k < mn; k++) {
        fscanf (in, "%d %d %lf", &i, &j, &a);
        A[i][j] = a;
    }
    for (k = 0; k < *m; k++) {
         fscanf (in, "%d %lf", &i, &a);
         b[i] = a;
    }
    fclose (in);
}

void imprime_matriz (double A[][NMAX], int m, int n)
{
    int i, j;
    printf ("[\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
            printf ("%8.4f  ", A[i][j]);
        printf (";\n");
    }
    printf ("];\n");
}

void imprime_vetor (double x[NMAX], int m)
{
    int i;
    for (i=0; i<m; i++) printf ("%8.6f\n",x[i]);
}

void imprime_indices (int i, int j)
{
    printf ("(%d , %d)\n",i,j);
}

void swap(double *a, double *b)
{
    double temp;
    temp = *b;
    *b   = *a;
    *a   = temp;   
}
