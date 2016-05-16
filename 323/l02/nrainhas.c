/*
 * LISTA 02 - PILHA
 * ex. 6) n Rainhas
 *
 * Bruno Ferrero   nUSP 3690142
 * Data: 12/04/2010 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "STACK.h"


/*verifica se pode colocar a rainha na col */
int podecolocar (int **tab, int n, int pos, int col);

void nRainhas (int n) {
    int *p;   /* vai guardar a coluna em que as rainhas sao colocadas */
    int **tab; /* tabuleiro */
    int i, j, topo;
    int col;
    int atual; /* linha atual */
    topo = 0;
    p =  (int*)malloc (n*sizeof(int)); /* aloca pilha */
    tab = (int**)malloc (n*sizeof(int));
    for (i = 0; i < n; i++) {    /* aloca tab   */
        tab[i] = (int*)malloc (n*sizeof(int));
        for (j = 0; j < n; j++)
            tab[i][j] = 0;
    }
    atual = col = 0;
    while (atual < n) {
        while (col < atual)
            if (podecolocar (tab, n, atual, col)){
                break;
            }
            else col++;
        if (col < n) { 
            PILHApush (p, &topo, col); /* empilha a coluna em que a rainha foi colocada */
            tab[atual][col] = 1; /* marca tabuleiro com a posicao da rainha */
            atual++;
            col = 0;
        }
        else { /*backtracking*/
            if (PILHAempty (topo)) {
                /* nao achou solucao */
                exit(1);
            }
            col = PILHAtopo (p, topo);
            atual --;
            tab[atual][col] = 0;
            col++;
            PILHApop (&topo);
        }
        printf ("AQUI\n");
    }
    /*solucao*/
    printf ("TERMINO\n");
    for (i = 0; i < n; i++)
        printf ("linha %d; coluna %d ",i+1, p[i]);
    printf ("\n");
    free(p);
    for (i = 0; i < n; i++)    
        free(tab[i]);
}

int podecolocar (int **tab, int n, int pos, int col) {

    int i, j;
    int pode = 1;
    for (i = 0; i < n; i++)    /*verifica linha*/
        if (tab[pos][i] == 1 && i != col)
            pode = 0; /*nao da pra colocar*/
    for (i = 0; i < n; i++)    /* verifica coluna*/
        if (tab[i][col] == 1 && i != pos)
            pode = 0; /*nao da pra colocar*/
    for (i = pos+1, j = col+1; i < n || j < n; i++, j++) /*diagonal para baixo*/
        if (tab[i][j] == 1)
            pode = 0; /*nao da pra colocar*/
     for (i = pos-1, j = col-1; i >= 0 || j >= 0; i--, j--) /*diagonal para cima*/
        if (tab[i][j] == 1)
            pode = 0; /*nao da pra colocar*/
    return pode;
}
