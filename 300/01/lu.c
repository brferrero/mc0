/*
*
* Nome: Bruno Ferrero
*
* MAC300 - EP1: Decomposicao de Cholesky e LU
*
* Set/2015  
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NMAX 1000

/* Decomposicao de Chlolesky */
/*col*/
/* Fator de Cholesky: o fator está na parte triangular inferior de A */
int cholcol (int n, double A[][NMAX]);
int forwcol (int n, double A[][NMAX], double b[]);
int backcol (int n, double A[][NMAX], double b[], int trans);

/*row*/
int cholrow (int n, double A[][NMAX]);
int forwrow (int n, double A[][NMAX], double b[]);
int backrow (int n, double A[][NMAX], double b[], int trans);

/* Decomposicao LU */
void swap (double *a, double *b);
int lucol(int n, double A[][NMAX], int p[]);
int sscol(int n, double A[][NMAX], int p[], double b[]);
int lurow (int n, double A[][NMAX], int p[]);
int ssrow(int n, double A[][NMAX], int p[], double b[]);


/*funcoes auxiliares*/
void le_entrada (char *fname, int *n, double A[][NMAX], double b[NMAX]);
void imprime_matriz (double A[][NMAX], int n);
void imprime_vetor (double x[NMAX], int n);
void imprime_indices (int i, int j);
void transposta (double A[][NMAX], int n);

/********************************************************************************/

int main (int argc, char *argv[])
{
    clock_t start, end;
    /*char fname[] = "exemplo10.dat";*/
    double A[NMAX][NMAX], b[NMAX];
    int p[NMAX];
    int n = 0;
    le_entrada (argv[1], &n, A, b);
    /*Cholesky: colunas*/
    printf ("Decomposicao de Cholesky: orientada a coluna\n");
    start = clock();
    cholcol (n, A);
    end = clock();
    printf( "A=GG': %f segundos \n", (end-start)/(double)CLOCKS_PER_SEC );
    start = clock();
    forwcol (n, A, b);
    end = clock();
    printf( "Gy=b : %f segundos \n", (end-start)/(double)CLOCKS_PER_SEC );
    start = clock();
    backcol (n, A, b, 0);
    end = clock();
    printf( "G'x=b: %f segundos \n", (end-start)/(double)CLOCKS_PER_SEC );
    
    /*Cholesky: linhas*/
    printf ("\nDecomposicao de Cholesky: orientada a linha\n");
    le_entrada (argv[1], &n, A, b);
    start = clock();
    cholrow (n, A);
    end = clock();
    printf( "A=GG': %f segundos \n", (end-start)/(double)CLOCKS_PER_SEC );
    start = clock();
    forwrow (n, A, b);
    end = clock();
    printf( "Gy=b : %f segundos \n", (end-start)/(double)CLOCKS_PER_SEC );
    start = clock();
    backrow (n, A, b, 0);
    end = clock();
    printf( "G'x=b: %f segundos \n", (end-start)/(double)CLOCKS_PER_SEC );

    /*LU: colunas*/
    printf ("\nDecomposicao LU: orientada a coluna\n");
    le_entrada (argv[1], &n, A, b);
    start = clock();
    lucol(n, A, p); 
    end = clock();
    printf( "PA=LU: %f segundos \n", (end-start)/(double)CLOCKS_PER_SEC );
    start = clock();
    sscol (n, A, p, b);
    end = clock();
    printf( "LUx=Pb: %f segundos \n", (end-start)/(double)CLOCKS_PER_SEC );

    /*LU: linhas*/
    printf ("\nDecomposicao LU: orientada a linha\n");
    le_entrada (argv[1], &n, A, b);
    start = clock();
    lurow(n, A, p); 
    end = clock();
    printf( "PA=LU: %f segundos \n", (end-start)/(double)CLOCKS_PER_SEC );
    start = clock();
    ssrow (n, A, p, b);
    end = clock();
    printf( "LUx=Pb: %f segundos \n", (end-start)/(double)CLOCKS_PER_SEC );

    return 0;
}

/********************************************************************************/
/* PARTE 1: Cholesky */
/* COLUNAS */

/* Cholesky por coluna (produto interno) */
int cholcol (int n, double A[][NMAX]) 
{
    int i, j, k;
    for (j = 0; j < n; j++) {
        for (k = 0; k < j; k++)
            A[j][j] = A[j][j] - (A[j][k])*(A[j][k]);
        if (A[j][j] <= 0) {
            printf ("Matriz não é definida positiva!\n");
            return -1;
        }
        /*Calcula elemento da diagonal*/
        A[j][j] = sqrt (A[j][j]);
        for (i = j+1;i < n; i++) {
            for (k = 0; k < j; k++)
                A[i][j] = A[i][j] - (A[i][k]*A[j][k]);
            /*Calcula elementos abaixo da diagonal*/
            A[i][j] = A[i][j]/A[j][j];
        }
    }
    return 1;
}

/* Resolove Ax=b a partir da fatoracao de A obtida por cholcol */
/* Recebe uma matriz triangular inferior e resolve Ax=b (por colunas)*/
int forwcol (int n, double A[][NMAX], double b[])
{
    int i, j;
    for (j = 0; j < n; j++) {
        if (A[j][j] == 0.0) { /* definir um EPISLON */ 
            printf ("matriz provavelmente singular!\n");
            return -1;
        }
        b[j] = b[j]/A[j][j];
        for (i = j+1; i < n; i++)
            b[i] = b[i] - A[i][j]*b[j];
    }
    return 1;
}

/*(trans == 0) -> Ax=b, A triangular superior; (trans == 1) -> A'x=b*/
int backcol (int n, double A[][NMAX], double b[], int trans)
{
    if (trans)
        return forwcol (n, A, b);
    else {
        int i, j;
        for (j = n-1; j >= 0; j--) {
            if (A[j][j] == 0.0)
                return -1;
            b[j] = b[j]/A[j][j];
            for (i = j-1; i >= 0; i--)
                /*indices trocados: simulando uma transposta*/
                b[i] = b[i] - A[j][i]*b[j];
        }
    }        
    return 0;
}

/* LINHAS */

/* Cholesky por linhas */
int cholrow (int n, double A[][NMAX]) 
{
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            if (i == j) {
                for (k = 0; k < i; k++) 
                    A[i][i] = A[i][i] - (A[i][k])*(A[i][k]);
                if (A[i][i] <= 0) {
                    printf ("Matriz não é definida positiva!\n");
                    return -1;
                }
                /*Calcula elemento da diagonal*/
                A[i][i] = sqrt (A[i][i]);
            }
            else {
                for (k = 0; k < j; k++)
                    A[i][j] = A[i][j] - (A[i][k]*A[j][k]);
                /*Calcula elementos a esquerda do elemento diagonal*/
                A[i][j] = A[i][j]/A[j][j];
            }
        }
    }
    return 0; 
}


/* Recebe uma matriz triangular inferior e resolve Ax=b (por linhas)*/
int forwrow (int n, double A[][NMAX], double b[]) 
{
    int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++) 
            b[i] = b[i] - A[i][j]*b[j];
        if (A[j][j] == 0.0) {
            printf ("matriz provavelmente singular!\n");
            return -1;
        }    
        b[i] = b[i]/A[i][i];
    }
    return 1;
}

/**/
int backrow (int n, double A[][NMAX], double b[], int trans)
{
    if (trans)
        return forwrow (n, A, b);
    else {
        int i,j;
        for (i = n-1; i >= 0; i--) {
            for (j = n-1; j > i; j--) 
                b[i] = b[i] - A[j][i]*b[j];
            if (A[i][i] == 0.0) {
                printf ("matriz deve ser singular!\n");
                return -1;
            }    
            b[i] = b[i]/A[i][i];
        }
        return 1;
    }
}

/********************************************************************************/

/* PARTE 2: Decomposicao LU */
void swap(double *a, double *b)
{
    double temp;
    temp = *b;
    *b   = *a;
    *a   = temp;   
}

int lucol(int n, double A[][NMAX], int p[]) 
{
    int i, j, k;
    int imax;
    for (k = 0; k < n; k++) {
        imax = k;
        for (i = k+1; i < n; i++) 
            if (fabs (A[i][k]) > fabs (A[imax][k]))
                imax = i;
        /*linha que sera permutada*/
        p[k] = imax;
        if (p[k] != k)
            /*permuta linha*/    
            for (j = 0; j < n; j++) 
                swap (&A[k][j], &A[p[k]][j]);

        if (A[k][k] == 0) {
            printf ("matriz provavelmente singular!\n");
            return -1;
        }
        /*calcula os multiplicadors da linha i*/
        for (i = k+1; i < n; i++)
            A[i][k] = A[i][k]/A[k][k];
        for (j = k+1; j < n; j++)
            for (i = k+1; i < n; i++)
                A[i][j] = A[i][j] - A[k][j]*A[i][k];
    }
    return 1;
}

int lurow(int n, double A[][NMAX], int p[]) 
{
    int i, j, k;
    int imax;
    for (k = 0; k < n; k++) {
        imax = k;
        for (i = k+1; i < n; i++) 
            if (fabs (A[i][k]) > fabs (A[imax][k]))
                imax = i;
        /*linha que sera permutada*/
        p[k] = imax;
        if (p[k] != k)
            /*permuta linha*/    
            for (j = 0; j < n; j++) 
                swap (&A[k][j], &A[p[k]][j]);

        if (A[k][k] == 0) {
            printf ("matriz provavelmente singular!\n");
            return -1;
        }
        for (i = k+1; i < n; i++) {
            /*calcula os multiplicadors da linha i*/
            A[i][k] = A[i][k]/A[k][k];
            for (j = k+1; j < n; j++)
                A[i][j] = A[i][j] - A[k][j]*A[i][k];
        }
    }
    if (A[n-1][n-1] == 0) {
        printf ("matriz provavelmente singular!\n");
        return -1;
    }
    return 1;
}


int sscol(int n, double A[][NMAX], int p[], double b[])
{
    int i, j;
    /*permuta vetor b*/
    for (i = 0; i < n; i++) 
        swap (&b[i],&b[p[i]]);

    /* Ly=b */
    for (j = 0; j < n; j++) {
        for (i = j+1; i < n; i++)
            b[i] = b[i] - A[i][j]*b[j];
    /*Como a diagonal de L e' 1, nao e' necessario dividir por A[i][i]*/ 
    }
    /* Ux=b */ 
    for (j = n-1; j >= 0; j--) {
        b[j] = b[j]/A[j][j];
        for (i = j-1; i >= 0; i--)
            b[i] = b[i] - A[i][j]*b[j];
    }

    return 0;
}

int ssrow(int n, double A[][NMAX], int p[], double b[])
{
    int i, j;
    /*permuta vetor b*/
    for (i = 0; i < n; i++) 
        swap (&b[i],&b[p[i]]);
    /* Ly=b */
    for (i = 0; i < n; i++)
        for (j = 0; j < i; j++)
            b[i] = b[i] - A[i][j]*b[j];

    /* Ux=b */
    for (i = n-1; i >= 0; i--) {
        for (j = i+1; j < n; j++)
            b[i] = b[i] - A[i][j]*b[j];
        b[i] = b[i]/A[i][i];
    }
    return 0;
}

/********************************************************************************/

/* AUXILIARES */
/* le um arquivo de texto, cujo formato foi especificado no enunciado do EP */
void le_entrada (char *fname, int *n, double A[][NMAX], double b[NMAX])
{
    FILE *in = NULL;
    int i, j, k, n2;
    double a;

    in = fopen (fname, "r");
    if (in == NULL) {
        printf ("Erro!\n");
        exit (1);
    }

    fscanf (in, "%d", n);
    n2 = (*n)*(*n);
    /*printf ("tam n = %d\n",*n);*/
    for (k = 0; k < n2; k++) {
        fscanf (in, "%d %d %lf", &i, &j, &a);
        A[i][j] = a;
    }
    for (k = 0; k < *n; k++) {
         fscanf (in, "%d %lf", &i, &a);
         b[i] = a;
    }
    fclose (in);
}

void imprime_matriz (double A[][NMAX], int n)
{
    int i, j;
    printf ("[\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf ("  \t%2g", A[i][j]);
        printf (";\n");
    }

    printf ("];\n");
}

void imprime_vetor (double x[NMAX], int n)
{
    int i;
    for (i=0; i<n; i++) printf("%g\n",x[i]);
}

void imprime_indices (int i, int j)
{
    printf ("(%d , %d)\n",i,j);
}

/*foi utilizada para testes; nao e' utilizada em nenhuma funcao*/
void transposta (double A[][NMAX], int n)
{
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i+1; j < n; j++)
            swap (&A[i][j], &A[j][i]);
    }
}

