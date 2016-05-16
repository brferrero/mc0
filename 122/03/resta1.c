/*
   ep3 - Resta Um.
   Bruno Ferrero

   Enquanto houver jogadas possiveis, acha e empilha todas as jogadas possiveis
   do tabuleiro a cada passo. Faz a ultima jogada e desempilha esta. Quando nao
   houver mais jogadas possiveis, retorna o tabuleiro ao estado anterior e tenta
   a jogada do topo da pilha.
 */

/* compilado com gcc version 4.0.1 (Apple Inc. build 5490)
 * gcc -Wall -pedantic -ansi ep3_bruno.c
 * time ./a.out
 * real	0m5.523s
 * user	0m5.459s
 * sys	0m0.019s
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 200

void imprime_tabuleiro (int tabuleiro[][7], int n)
{
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf ("%d ", tabuleiro[i][j]);
        printf ("\n");
    }
}

typedef struct {
    int lin, col;
    int tipo; /*tipo 1: pra cima; tipo 2: pra direita; tipo 3: pra baixo; tipo 4: pra esq*/
    int ordem;
} jogada;

jogada pilha[MAX];  /*armazena as jogadas possiveis*/
jogada solucao[31]; /*vetor com as solucoes*/

void empilha (jogada p[], int *topo, jogada x)
{
    if (*topo == MAX)
        printf("nao cabe mais!\n");
    p[*topo] = x;
    (*topo)++;
}

void desempilha (int *topo)
{
    if (*topo == 0)
        printf ("vazia!\n");
    (*topo)--;
}

int pilha_vazia (int topo)
{
    return (topo == 0);
}

jogada topodapilha (jogada p[], int topo)
{
    if (pilha_vazia (topo))
        printf ("estorou!\n");
    return (p[topo-1]);
}

void faz_jogada (int tabuleiro[][7], jogada jog);
void desfaz_jogada (int tabuleiro[][7], jogada jog);
int seleciona_jogadas (int tabuleiro[][7], int n, int *topo, int nj);

int main ()
{
    int tab[7][7];
    int i,j; 
    int topo = 0;
    int n = 7;
    int njogs=0;
    jogada atual;
    /*gera tabuleiro*/
    for (i = 0; i < 7; i++) 
        for (j = 0; j < 7; j++)
            tab[i][j] = 2;
    for (i = 2; i < 5; i++) 
        for (j = 0; j < 7; j++)
            tab[i][j] = 1;
    for (i = 2; i < 5; i++) 
        for (j = 0; j < 7; j++)
            tab[j][i] = 1;
    tab[3][3] = 0;
    /*tabuleiro tradicional gerado*/
    imprime_tabuleiro(tab,n);
    printf("\n");
    while (njogs < 31) { /* 31 movimentos pra terminar o jogo */
        if (seleciona_jogadas(tab,n,&topo,njogs)) {       /*verifica se há jogadas e as empilha*/
            solucao[njogs] = topodapilha (pilha,topo);    /*guarda a jogada feita */ 
            faz_jogada (tab, solucao[njogs]);
            desempilha(&topo);                            /*desempilha a jogada feita*/
            njogs++;
        }
        else { /*backtracking*/
            if (pilha_vazia(topo)) {
                printf("eita!\n");
                return 0;
            }
            atual =  topodapilha (pilha,topo);
            while(njogs > atual.ordem) {                /*desfaz até achar a jogada da vez (ordem)*/
                desfaz_jogada (tab, solucao[njogs-1]);
                njogs--;
            }
            njogs = atual.ordem;
            faz_jogada (tab, atual);
            desempilha(&topo); 
            solucao[njogs] = atual;
            njogs++;
            /*printf ("jogada BT i = %d j = %d tipo = %d topo = %d\n njogs = %d\n", atual.lin, atual.col, atual.tipo, topo,njogs);*/
        }
    }

    /*imprime solucao*/
    for (i=0; i<31; i++) {
        printf("Jogada = %2d lin = %d col = %d ", solucao[i].ordem+1, solucao[i].lin, solucao[i].col);
        switch (solucao[i].tipo) {
            case 1: printf ("para CIMA\n"); break;
            case 2: printf ("para DIREITA\n"); break;
            case 3: printf ("para BAIXO\n"); break;
            case 4: printf ("para ESQUERDA\n"); break;
        }
    }
    printf("\n");
    /*tabuleiro final*/
    imprime_tabuleiro(tab,n);

    return 0;
}

/*acha e empilha todas as jogadas possiveis*/
int seleciona_jogadas (int tabuleiro[][7], int n, int *topo, int nj)
{
    int i, j;
    int aux = 0;
    jogada aux1, aux2, aux3, aux4;

    for (i = 0; i < n; i++) 
        for (j = 0; j < n; j++) {
            /*jogada 1*/
            if (tabuleiro[i][j] == 1 && tabuleiro[i-1][j] == 1 && tabuleiro[i-2][j] == 0 && (i-2) >= 0) {
                aux1.lin = i;
                aux1.col = j;
                aux1.tipo = 1;
                aux1.ordem = nj;
                aux = 1;
                empilha (pilha, topo, aux1);
            }
            /*jogada 2*/
            if (tabuleiro[i][j] == 1 && tabuleiro[i][j+1] == 1 && tabuleiro[i][j+2] == 0 && (j+2) < n) {
                aux2.lin = i;
                aux2.col = j;
                aux2.tipo = 2;
                aux2.ordem = nj;
                aux = 1;
                empilha (pilha, topo, aux2);
            }
            /*jogada 3*/
            if (tabuleiro[i][j] == 1 && tabuleiro[i+1][j] == 1 && tabuleiro[i+2][j] == 0 && (i+2) < n) {
                aux3.lin = i;
                aux3.col = j;
                aux3.tipo = 3;
                aux3.ordem = nj;
                aux = 1;
                empilha (pilha, topo, aux3);
            }
            /*jogada 4*/
            if (tabuleiro[i][j] == 1 && tabuleiro[i][j-1] == 1 && tabuleiro[i][j-2] == 0 && (j-2) >= 0) {
                aux4.lin = i;
                aux4.col = j;
                aux4.tipo = 4;
                aux4.ordem = nj;
                aux = 1;
                empilha (pilha, topo, aux4);
            }
        }
    if (aux == 0) /*nao empilhou jogadas*/
        return 0;
    return 1;
}

/*recebe um tabuleiro e uma jogada, e aplica a jogada no tabuleiro*/
void faz_jogada (int tabuleiro[][7], jogada jog)
{
    int i, j;
    i = jog.lin;
    j = jog.col;
    if (jog.tipo == 1) {
        tabuleiro[i][j] = 0;
        tabuleiro[i-1][j] = 0;
        tabuleiro[i-2][j] = 1;
    }
    if (jog.tipo == 2) {
        tabuleiro[i][j] = 0;
        tabuleiro[i][j+1] = 0;
        tabuleiro[i][j+2] = 1;
    }
    if (jog.tipo == 3) {
        tabuleiro[i][j] = 0;
        tabuleiro[i+1][j] = 0;
        tabuleiro[i+2][j] = 1;
    }
    if (jog.tipo == 4) {
        tabuleiro[i][j] = 0;
        tabuleiro[i][j-1] = 0;
        tabuleiro[i][j-2] = 1;
    }
}

void desfaz_jogada (int tabuleiro[][7], jogada jog)
{
    int i, j;
    i = jog.lin;
    j = jog.col;
    if (jog.tipo == 1) {
        tabuleiro[i][j] = 1;
        tabuleiro[i-1][j] = 1;
        tabuleiro[i-2][j] = 0;
    }
    if (jog.tipo == 2) {
        tabuleiro[i][j] = 1;
        tabuleiro[i][j+1] = 1;
        tabuleiro[i][j+2] = 0;
    }
    if (jog.tipo == 3) {
        tabuleiro[i][j] = 1;
        tabuleiro[i+1][j] = 1;
        tabuleiro[i+2][j] = 0;
    }
    if (jog.tipo == 4) {
        tabuleiro[i][j] = 1;
        tabuleiro[i][j-1] = 1;
        tabuleiro[i][j-2] = 0;
    }
}


