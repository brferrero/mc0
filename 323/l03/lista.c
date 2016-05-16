/*
 *
 * LISTA 03 - Lista Ligada
 * ex. 6)
 *
 * Bruno Ferrero   nUSP 3690142
 * Data: 12/04/2010 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


/* Pertence(A, x) */
int pertence (lista p, Item x) {
    while (p != NULL) {
          if (p->info == x)
             return 1;
          p = p->prox;
    }
    return 0;
             
}

/* Uniao(A, B) */
lista uniao (lista a, lista b) {
      lista c;
      c = LISTAinicia (c);
      while (a != NULL) {
          c = LISTAinsere (c, a->info);
          a = a->prox;         
      }
      while (b != NULL) {
          if (!pertence (c,b->info))
              c = LISTAinsere (c, b->info);
          b = b->prox;         
      }  
      return c;
}

/* Interseccao(A, B) */
lista interseccao (lista a, lista b) {     
      lista c;
      Item aux;
      c = LISTAinicia (c);
      while (a != NULL) {
            aux = a->info;
            if (pertence (b, aux) && !pertence (c, aux)) {
               c = LISTAinsere (c, aux);
               }
            a = a->prox;
      }
      return c;
}

/* Diferenca(A, B) */
lista diferenca (lista a, lista b) {
      lista c;
      Item aux;
      c = LISTAinicia (c);
      while (a != NULL) {
            aux = a->info;
            if (!pertence (b, aux) && !pertence (c, aux)) {
               c = LISTAinsere (c, aux);
            }
            a = a->prox;
      }
      return c;
}


/* inicia um ptr para celula (lista) */
lista LISTAinicia (lista l) {
    return l = NULL;
}

lista LISTAinsere (lista p, Item x) {
          lista nova;
          lista aux = p;
          nova = malloc (sizeof (celula));
          nova->info = x;
          nova->prox = NULL;
          if (p == NULL)
             return nova;
          while (aux->prox != NULL) {
                aux = aux->prox;
          }
          aux->prox = nova;
          return p;         
}

void LISTAdump (lista p) {
     while (p != NULL) {
           printf ("%4d", p->info);
           p = p->prox;
     }
     printf ("\n");
}


