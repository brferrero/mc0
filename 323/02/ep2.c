/********************************************************************
 *  Nome : Bruno Ferrero                             N.USP 3690142
 *  Curso: BCC                                 Disciplina: MAC 323
 *  Data : 05/2010                                     EP2 - BST's
 *  gcc version 4.3.2 (Debian 4.3.2-1.1)
 *  *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "BST.h"

void limpa (char *p, int max);
void carregaArq (char *nome_arq);
int main (int argc, char *argv[])
{
    char c = 0;
    char addLivro = 0;
    char pal[MAX_PALAVRA]; /*palavra*/
    char nome_arq[MAX_PALAVRA];/*nome do arq que contem o livro*/
    char flag[1];
    Item aux;
    Info aux2;
    limpa (pal, MAX_PALAVRA);
    if (argc < 2) {
        printf ("Uso: <prompt>%s <arq_entrada>\n", argv[0]);
        exit (1);
    }
    strncpy (flag, argv[1], 2);
    /*verifica as flags*/
    if (flag[0] == '-') {
        if (argc < 3) {
            printf ("Uso: <prompt>%s -f <arq_entrada>\n", argv[0]);
            exit (1);
        }
        strcpy (nome_arq,argv[2]);
    }
    else
        strcpy (nome_arq,argv[1]);
    
    /* inicia a BST */
    STinit();
    /* armazena o arquivo na BST*/
    carregaArq (nome_arq);
    /*busca as palavras na BST*/
    while (c != 'n') {
        printf ("Digite a palavra a ser buscada: ");
        scanf ("%s",pal);
        aux = STsearch (pal);
        if (aux != NULL) {
            aux2 = aux->info;
            while (aux2 != NULL) { /*verifica se ocorre em mais de um livro*/
                printf ("%s\n", aux2->livro);
                imprime (aux2);
                aux2 = aux2->next;
            }
        }
        else 
            printf ("%s - palavra nao encontrada!\n", pal);
        printf ("Deseja fazer nova busca: [s] [n]\n");
        scanf (" %c",&c);
        if (c == 's') {
            printf ("Deseja inserir novo livro: [s] [n]\n");
            scanf (" %c", &addLivro);
            if (addLivro == 's') {
                printf ("Digite o nome do arquivo a ser armazenado:\n");
                scanf ("%s",nome_arq);
                /*carrega o novo livro*/
                carregaArq (nome_arq);
            }
        }
    }
    return 0;
}

/*recebe um string contendo o nome de um arquivo a ser lido e armazenado na BST*/
void carregaArq (char *nome_arq){
    FILE *arq;
    char c;
    int nl;
    int cont = 0;
    char pal[MAX_PALAVRA]; /*palavra*/
    Item novoItem; /*que vai ser inserido na BST*/
    Item aux;
    nl = 1;
    arq = fopen (nome_arq,"r");
    while (!feof(arq)) {
        fscanf (arq, "%c", &c);
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == 39 || c == 96) { /*39 =='''*/
            /*ainda está dentro de uma palavra*/
            pal[cont++] = c;
        }
        else {
            if (cont != 0) {
                /*insere na BST*/
                if (STsearch (pal) == NULL) {
                    /*a chave ainda nao existe na BST*/
                    novoItem = newItem (pal, nome_arq, nl);
                    STinsert (novoItem);
                }
                else {
                    /*a chave ja está na BST; atualiza o item*/
                    aux = STsearch (pal);
                    aux = atualizaItem (aux, nome_arq, nl);
                }
                limpa (pal, MAX_PALAVRA);
            }
            cont = 0;
            if (c == '\n')
                nl++; /*conta linhas*/
        }
    }
     fclose (arq);
}

/* limpa vetor */
void limpa (char *p, int max) {
    int i = 0;
    for (i=0; i<max; i++)
        p[i] = 0;
}
