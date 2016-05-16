#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

apontador empilha (apontador topo, Item x)
{
          apontador novo;
          novo = malloc (sizeof (celula));
          novo->info = x;
          novo->prox = topo;
          return novo;
}

apontador desempilha (apontador topo)
{
          apontador aux;
          if (topo == NULL)
             printf ("ERRO!!");
          aux = topo->prox;
          free (topo);
          return aux;
}

int pilhaVazia (apontador topo)
{
    return (topo==NULL);
}

Item topoDaPilha (apontador topo)
{
     return (topo->info);
}
