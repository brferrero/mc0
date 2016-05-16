/*
 * Autor: Bruno Ferrero  
 * n.USP: 3690142  Curso: BCC
 *
 * Data: 04/04/2010
 * gcc version 4.3.2 (Debian 4.3.2-1.1)
 *
 * STACK.h
 */

/* definicoes da pilha */

#define COPAS 1
#define OUROS 2
#define ESPADAS 3
#define PAUS 4

#define ITEMprint(A) printf("%4d(\033[31;1m%d\033[m)", A.num, A.naipe)

struct carta {
    int num;
    int naipe;
};

typedef struct carta Item; /* item e' do tipo carta */

typedef struct cel {
    Item item;
    struct cel *prox;
}pilha;

typedef pilha *apontador;

apontador PILHAinit (void);                  /* inicializa */
int PILHAempty (apontador topo);             /* verifica se esta vazia */
apontador PILHAput (apontador topo, Item x); /* insere item */
apontador PILHAget (apontador topo);         /* remove item */
Item PILHAtopo (apontador topo);             /* topo da pilha */
void PILHAdump (apontador topo);             /* imprime pilha */
