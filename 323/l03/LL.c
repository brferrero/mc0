#include <stdio.h>
#include <stdlib.h>


typedef int Item;

struct cel {
    Item info;
    struct cel *prox;
};

typedef struct cel celula;

typedef celula * apontador;


void insere (Item x, celula *lista)
{
    celula *nova;
    nova = malloc (sizeof (celula));
    nova->info = x;
    nova->prox = lista->prox;
    lista->prox = nova;
}





int main ()
{
    celula c;
    apontador p;

    p = malloc (sizeof(celula));

    insere (1, p);
    insere (2, p);
    insere (3, p);
    insere (4, p);


    printf ("%d\n",p->info);
    p=p->prox;
    printf ("%d\n",p->info);
    p=p->prox;
    printf ("%d\n",p->info);





    c.info = 1;
    c.prox = NULL;



    return 0;
}


