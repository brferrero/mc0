/*
 *
 * Nome: Bruno Ferrero
 *
 * MAC300 - EP2: Gradientes Conjugados para matrizes esparsas
 *
 * Nov/2015  
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NMAX 10000
#define EPSILON 0.000001

/* operacoes com vetores */
void iguala_vetor (int n, double a[], double b[]);
void soma_vetor (int n, double c[], double a[], double b[]);
void sub_vetor (int n, double c[], double a[], double b[]);
void mult_escalar_vetor (int n, double c[], double a[], double lambda);
double produto_interno (int n,  double a[], double b[]);
/* produto matriz vetor */
void produto_matriz_vetor (int n, int nz,  double b[], double A[], int linha[], int coluna[], double x[]);
/* metodo dos gradientes conjugados */
int cg (int n, int nz,  double b[], double A[], int linha[], int coluna[], double x[]);

/* le matriz esparsa em vetores */
void le_entrada (char *fname, int *n, int *nz, double A[NMAX], double b[NMAX], int linha[NMAX], int coluna[NMAX]);


/********************************************************************************/
int main (int argc, char *argv[])
{
    /*char fname[] = "teste.dat";*/
    double A[NMAX], x[NMAX], b[NMAX];
    int linha[NMAX], coluna[NMAX];
    /* nz é o número de entradas não nulas da matriz */
    int n, nz;
    le_entrada (argv[1], &n, &nz, A, b, linha, coluna);
    cg (n, nz, b, A, linha, coluna, x);
    return 0;
}

/********************************************************************************/

/* a = b */
void iguala_vetor (int n, double a[], double b[])
{
    int i;
    for (i = 0; i < n; i++) a[i] = b[i];
}


/* calcula a soma de vetores c = a + b; devolve o resultado em c */
void soma_vetor (int n, double c[], double a[], double b[])
{
    int i;
    for (i = 0; i < n; i++) c[i] = a[i]+b[i];
}

/* calcula a subtração de vetores c = a - b; devolve o resultado em c */
void sub_vetor (int n, double c[], double a[], double b[])
{
    int i;
    for (i = 0; i < n; i++) c[i] = a[i]-b[i];
}

/* calcula a multiplicacao por escalar de vetores c = lambda.a; devolve o resultado em c */
void mult_escalar_vetor (int n, double c[], double a[], double lambda)
{
    int i;
    for (i = 0; i < n; i++) c[i] = lambda*a[i];
}

/* calcula o produto xy; devolve o resultado em x */
double produto_interno (int n,  double a[], double b[])
{
    int i;
    double x = 0;
    for (i = 0; i < n; i++)
        x += a[i]*b[i];
    return x;
}

/********************************************************************************/

/* produto Ax; A matriz esparsa*/
/* calcula o produto b = Ax; devolve o resultado em b */
void produto_matriz_vetor (int n, int nz,  double b[], double A[], int linha[], int coluna[], double x[])
{
    int k;
    for (k = 0; k < n; k++)
        b[k] = 0;

    for (k = 0; k < nz; k++)
        b[linha[k]] = b[linha[k]] + A[k]*x[coluna[k]];
}

/* Metodo dos gradientes conjugados: baseado no Trefethen */
int cg (int n, int nz,  double b[], double A[], int linha[], int coluna[], double x[])
{
    double alfa;        /*step length*/
    double beta;        /*improvement*/
    double r0, rk = 1;
    double r[NMAX];     /*residual*/ 
    double p[NMAX];     /*search direction*/
    double xn[NMAX];    /*approximate solution*/ 
    double vaux1[NMAX];
    double vaux2[NMAX];
    int k;
    /*inicializacao*/
    for (k = 0; k < n; k++) {
        xn[k] = 0.0;
        p[k] = r[k] = b[k];
    }

    for (k = 0; k < nz; k++) {
        if (sqrt(rk/r0) <= EPSILON) {
            iguala_vetor (n, x, xn);
            printf("aqui");
            return 1;
        }

        /*r'r*/
        r0 = produto_interno (n, r, r);
        /*Ap*/
        produto_matriz_vetor (n, nz, vaux1, A, linha, coluna, p);
        /*alfa = rk/p'Ap ; vaux1=Ap */
        alfa = r0/(produto_interno (n, p, vaux1));
        /*alfa.p ; vaux2=alfa.p*/
        mult_escalar_vetor (n, vaux2, p, alfa);
        /*xn = xn + vaux2 */
        soma_vetor (n, xn, xn, vaux2);
        /*alfa.Ap ; = alfa.vaux1*/
        mult_escalar_vetor (n, vaux2, vaux1, alfa);
        /*rn = rn - alfa.Ap*/
        sub_vetor (n, r, r, vaux2);
        /*beta*/
        rk = produto_interno (n, r, r);
        beta = rk/r0;
        /*beta.pn*/
        mult_escalar_vetor (n, vaux2, p, beta);
        /*pn = r + beta.pn*/
        soma_vetor (n, p, p, vaux2);

    }
    iguala_vetor (n, x, xn);
    return 0;
}

/********************************************************************************/

/* AUXILIARES */
/* le um arquivo de texto contendo uma matriz com n entradas nao nulas */
void le_entrada (char *fname, int *n, int *nz, double A[NMAX], double b[NMAX], int linha[NMAX], int coluna[NMAX])
{
    FILE *in = NULL;
    int i, j, k;
    double a;

    in = fopen (fname, "r");
    if (in == NULL) {
        printf ("Erro!\n");
        exit (1);
    }

    fscanf (in, "%d %d", n, nz);
    for (k = 0; k < *nz; k++) {
        fscanf (in, "%d %d %lf", &i, &j, &a);
        A[k] = a;
        linha[k] = i;
        coluna[k] = j;
    }
    for (k = 0; k < *n; k++) {
        fscanf (in, "%d %lf", &i, &a);
        b[k] = a;
    }
    fclose (in);
}

