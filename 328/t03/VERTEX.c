#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "VERTEX.h"

/* cria um novo no */
link NEW (Vertex w) {
    link x = malloc (sizeof *x);
    x->w = w;
    x->next = NULL;
    return x;
}

/* cria um vertice com os campos passados pelos parametros */
Vertex NEWvertex (int id, Target nome, Comando comandos) {
    Vertex x = malloc (sizeof *x);
    x->id = id;
    strcpy (x->nome, nome);
    strcpy (x->comandos, comandos);
    return x;
}

/*seta um comando de um Vertex*/
void SETcomandos (Vertex v, Comando comandos) {
    strcpy (v->comandos, comandos);
}

/*recebe dois vertices e devolve 1 caso eles tenham mesmo nome*/
int VERTEXcompare (Vertex v, Vertex w) {
    if (strcmp (v->nome, w->nome) == 0)
        return 1;
    else 
        return 0;
}

/*-------------------------------------------------------*/
