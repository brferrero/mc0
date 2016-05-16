typedef struct jogada {
        int lin;
        int col;
}Jog;

typedef Jog Item;
        
typedef struct cel {
       Item info;
       struct cel *prox;
}celula;

typedef celula *apontador;

apontador empilha (apontador topo, Item x);
apontador desempilha (apontador topo);
int pilhaVazia (apontador topo);
Item topoDaPilha (apontador topo);
