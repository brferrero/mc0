/********************************************************************
 *  Nome : Bruno Ferrero                             N.USP 3690142
 *  Curso: BCC                                 Disciplina: MAC 323
 *  Data : 05/2010                                     EP2 - BST's
 *  gcc version 4.3.2 (Debian 4.3.2-1.1)
 *  *****************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Item.h"

/* recebe uma chave, um livro e a linha que ocorre uma nova chave
 * e devolve um item para ser inserido na BST */
Item newItem (Key v, Livro l, int n) {
    Item x = NULL;
    Info y = NULL;
    Linhas z = NULL;
    x = malloc (sizeof (sItem));   /*ITEMnode*/
    y = malloc (sizeof (sInfo));   /*INFOnode*/
    z = malloc (sizeof (sLinhas)); /*LINHAnode*/
    /*Linhas: atribui numero da linha e next linha*/
    z->linha = n;
    z->next = NULL;
    /*Info: atribui nome do livro, lista de linhas e next livro*/
    strcpy (y->livro, l);
    y->linha = z;
    y->next = NULL;
    /*Item: atribui chave e info*/
    strcpy (Chave(x), v);
    x->info = y;
    return x;
}

/* recebe um Item, um Livro e um inteiro representando uma linha
 * atualiza o node Info com o nome do livro e linha */
Item atualizaItem (Item x, Livro l, int n) {
    Linhas nova = NULL;
    Info aux = NULL;
    /*verifica se o livro l já foi inserido na lista*/
    aux = buscaLivro (x->info, l);
    if (aux != NULL) {
        /*livro já está na BST*/
        nova = aux->linha;
        nova = insertLinha (nova, n);
        aux->linha = nova;
    }
    else {
        /*insere novo livro*/
        aux = x->info;
        aux = insertInfo (aux, l, n);
        x->info = aux;
    }
    return x;
}

/* insere n na lista de linhas p */
Linhas insertLinha (Linhas p, int n) {
    Linhas nova = NULL;
    Linhas aux = p;
    nova = malloc (sizeof (sLinhas));
    nova->linha = n;
    nova->next = NULL;
    if (p == NULL) {
        return nova;
    }
    else {
        while (aux->next != NULL) /*insere no final*/
            aux = aux->next;
        aux->next = nova;
        return p;
    }
}

/* insere l na lista p; insere n na lista correspondente ao livro l */
Info insertInfo (Info p, Livro l, int n) {
    Info nova;
    Info aux = p;
    nova = malloc (sizeof (sInfo));
    strcpy (nova->livro, l);
    nova->linha = NULL; 
    nova->linha = insertLinha (nova->linha, n);
    nova->next = NULL;
    if (p == NULL)
        return nova;
    else {
        while (aux->next != NULL) 
            aux = aux->next;
        aux->next = nova;
        return p;
    }
}

/* recebe uma lista p e um livro l e verifica se l está em p */
Info buscaLivro (Info p, Livro l) {
    Info aux = p;
    while (aux != NULL) {
        if (strcmp (aux->livro, l) == 0) {
            return p;/*aux*/
        }
        aux = aux->next; 
    }
    return NULL;
}

/* recebe um nome de arquivo e imprime a linha nLinha
 * desse arquivo */
static void imprimeLinha (char *nome_arq, int nLinha) {
    FILE *arq;
    char c;
    int nl;
    arq = fopen (nome_arq,"r");
    nl = 1;
    while (!feof(arq) && nl <= nLinha) {
        fscanf (arq, "%c", &c);
        if (nl == nLinha) {
            printf ("%c",c);
        }
        if (c == '\n')
            nl++; /*conta linhas*/
    }
    fclose (arq);
}

/* recebe um Info e imprime a lista de linha desse Info */
void imprime (Info p) {
    Linhas aux;
    aux = p->linha;
    while (aux != NULL) {
        printf ("    %d: ", aux->linha);
        imprimeLinha (p->livro, aux->linha);
        aux = aux->next;
    }
}
/***********************************/
