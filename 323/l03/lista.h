/*
 * LISTA 03 - Lista Ligada
 * ex. 6)
 *
 * Bruno Ferrero   nUSP 3690142
 * Data: 12/04/2010 
 *
 */

typedef int Item;

typedef struct cel {
        Item info;
        struct cel *prox;
} celula;

typedef celula *lista;

/* recebe um item e uma lista e devolve 1 caso o item esteja na lista */
int pertence (lista p, Item x);
/* recebe duas listas e devolve uma nova lista que é a uniao das listas a e b*/
lista uniao (lista a, lista b);
/* recebe duas listas e devolve uma nova lista que é a intersecao das listas a
   e b */
lista interseccao (lista a, lista b);
/* recebe duas listas e devolve uma nova lista que sao os elementos que estao
   em a mas nao estao em b */
lista diferenca (lista a, lista b);

/**/
lista LISTAinicia (lista l);
lista LISTAinsere (lista p, Item x);
void LISTAdump (lista p);




