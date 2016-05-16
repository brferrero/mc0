/*
 * LISTA 02 - PILHA
 * ex. 6) n Rainhas
 *
 * Bruno Ferrero   nUSP 3690142
 * Data: 12/04/2010 
 *
 */


/* empilha */
void PILHApush (int p[], int *topo, int x) {
    p[*topo] = x;
    (*topo)++;
}

/* desempilha */
void PILHApop (int *topo) {
    (*topo)--;
}

/* verifica se a pilha está vazia*/
int PILHAempty (int topo) {
    return (topo == 0);
}

/* devolve o topo da pilha */
int PILHAtopo (int p[], int topo) {
    return (p[topo-1]);
}
