/* ****************************** */
/* Bruno Ferrero    n.USP 3690142 */
/* MAC0122          25/08/2009    */
/* EP1                            */
/* Compilador: gcc version 4.0.1  */
/* ****************************** */

/* conta em quantos passos a funcao chega em 1 para todos os naturais em um  */
/* determinado intervalo dado na entrada; As entradas sao lidas ate o usuario*/
/* entrar com um zero; somente aceita numeros positivos.                     */

/* para passar no UVa online judge, fazer modificacoes na entrada/saida      */
/* indicadas no codigo, o Run Time dado pelo juiz foi de 0.024               */

/* aloquei um vetor de tamanho MAX (variavel global), que armazenara todos os*/
/* numeros testados pela funcao para TODOS OS INTERVALOS dados, caso sejaa   */
/* dado um numero maior que o tamanho do vetor esse numero nao sera aramaze -*/
/* nado.                                                                     */

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

unsigned long int resolvidos[MAX];

unsigned long long int fn (unsigned long long int n);

int main ()
{
    unsigned long long int n1, n2, i;
    unsigned long long int aux, maior;
    /* zera o vetor */
    for (i = 0; i <= MAX; i++)
        resolvidos[i] = 0;
    n1 = 1;
    n2 = 1;
    scanf ("%llu", &n1);
    while (n1 != 0 && n2 != 0)
    {
        scanf ("%llu", &n2);
        printf ("\n");
        /* juiz */
        /*printf ("%llu %llu\n", n1, n2);*/
        maior = 0;
        /* troca */
        if (n2 < n1)
        {
            i = n1;
            n1 = n2;
            n2 = i;
        }
        for (i = n1; i <= n2; i++)
        {
            if (resolvidos[i] == 0)
            {
                /* armazena os resolvidos, nao sendo necessario */
                /* chamar a funcao novamente para este i.       */
                aux = fn (i);
                resolvidos[i] = aux;
            }
            else 
                aux = resolvidos[i];
            /* guarda o maior; juiz eletronico */    
            /* if (aux > maior)
                 maior = aux; */
            printf ("%llu %lu\n", i, resolvidos[i]);
        }
        printf ("\n");
        /* juiz */
        /*printf (" %llu\n", maior);*/
        n1 = 0;
        scanf ("%llu",&n1);
    }
    return 0;
}


/* Calcula recursivamente cada termo ate chegar em 1 */
/* devolvendo o numero de passos                     */

unsigned long long int fn (unsigned long long int n)
{
    int passos;
    if (n != 1) {
        if (n % 2) {
            if (3*n+1 >= MAX)
                passos = fn (3*n+1) + 1;
            else {
                if (resolvidos[3*n+1] != 0)
                    passos = resolvidos[3*n+1] + 1;
                else passos = fn (3*n+1) + 1;
            }
        }
        else {
            if (n/2 >= MAX)
                passos = fn (n/2) + 1;
            else {
                if (resolvidos[n/2] != 0){
                    passos = resolvidos[n/2] + 1;
                    /*printf("\nENTROU\n");*/
                }
                else passos = fn (n/2) + 1;
            }
        }
        if (n <= MAX)
            resolvidos[n] = passos;
        return passos;
    }
    /* para funfar no juiz eletronico se n == 1, return 1; e nao 0 */
    else return 0;
}



