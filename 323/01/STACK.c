/*
 * Autor: Bruno Ferrero  
 * n.USP: 3690142  Curso: BCC
 *
 * Data: 04/04/2010
 * gcc version 4.3.2 (Debian 4.3.2-1.1)
 *
 * STACK.c
 */


#include <stdlib.h>
#include <stdio.h>
#include "STACK.h"

apontador PILHAinit () {
    apontador p;
    p = malloc (sizeof (pilha));
    p = NULL;
    return p;
}

apontador PILHAput (apontador topo, Item x) {
    apontador novo;
    novo = malloc (sizeof (pilha));
    novo->item = x;
    novo->prox = topo;
    return novo;
}

apontador PILHAget (apontador topo) {
    apontador aux;
    if (topo == NULL)
        printf ("ERRO!! PILHA VAZIA!");
    aux = topo->prox;
    free (topo);
    return aux;
}

int PILHAempty (apontador topo) {
    return (topo == NULL);
}

Item PILHAtopo (apontador topo) {
    return (topo->item);
}

void PILHAdump (apontador topo) {
    apontador aux;
    aux = topo;
    while (aux != NULL) {
        ITEMprint (aux->item);
        printf("\n");
        aux = aux->prox;
    }
}

