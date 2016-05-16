/*
 * Autor: Bruno Ferrero  
 * n.USP: 3690142  Curso: BCC
 *
 * Data: 04/04/2010
 * gcc version 4.3.2 (Debian 4.3.2-1.1)
 *
 * CRUEL.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "STACK.h"

#define MAX 52

/*VAR GLOBAIS*/
Item BARALHO[MAX];
apontador P[12];      /* pilha de cartas */
apontador P_naipe[4]; /* pilha de naipes */


/*FUNCOES*/
void embaralha (void);
void inicia_jogo (void);
void redistribui (void);
void estado_atual (void);
void imprime_jog (Item , int, int);
int conta_pontos (void);
int mesmo_naipe (Item, Item);
int pCarta_pNaipe (Item, Item); /* pilha de carta -> pilha de naipe */
int pCarta_pCarta (Item, Item); /* pilha de carta -> pilha de carta */
int jogadaT1 (void);            /* jogada tipo 1; pCarta->pNaipe */
int jogadaT2 (void);            /* jogada tipo 1; pCarta->pCarta */
void movimenta (Item, int, int);

int main () 
{
    int pontos;
    int de_novo = 1;

    while (de_novo) {
        embaralha();
        inicia_jogo();
        /*imprime estado inicial*/
        printf (" INICIO: \n");
        estado_atual();
        printf ("\n\n==============================\n\n");
        /*jogando - pilha de cartas para pilha de naipes*/
        jogadaT1();

        /*jogando*/
        while (jogadaT1() || jogadaT2() ) {
            printf ("\n Redistribui: \n");
            redistribui();
        }
        estado_atual();
        pontos = conta_pontos();

        if (pontos == 0) {
            printf ("\nVENCEU !!!\n\n");
        }
        else printf ("\nPONTOS: %d\n\n", pontos);
        printf ("Jogar novamente: SIM [1], NAO [0]: ");
        scanf ("%d",&de_novo);
    }
    return 0;
}

void embaralha (void) {
    int i, x;
    Item card;
    Item b[48];
    for (i = 2; i <= 13; i++) {
        /* preenche vetor com as cartas (sem as) */
        card.num = i;
        card.naipe = COPAS;
        b[i-2] = card;
        card.naipe = OUROS;
        b[i+10] = card;
        card.naipe = ESPADAS;
        b[i+22] = card;
        card.naipe = PAUS;
        b[i+34] = card;
    }
    /*embaralhando*/
    /*srand (time(NULL));*/ 
    for (i = 0; i < 48; i++) { 
        x = rand ()%(48-i);
        BARALHO[i] = b[x];
        b[x] = b[47-i];
    }
}

void inicia_jogo () {
    int i;
    Item carta_0;
    /*inicializa as 12 pilhas*/
    for (i = 0; i < 12; i++) 
        P[i] = PILHAinit();
    /*distribuindo o baralho nas 12 pilhas*/
    for (i = 0; i < 12; i++) {
        P[i] = PILHAput (P[i], BARALHO[0+4*i]);
        P[i] = PILHAput (P[i], BARALHO[1+4*i]);
        P[i] = PILHAput (P[i], BARALHO[2+4*i]);
        P[i] = PILHAput (P[i], BARALHO[3+4*i]);
    }
    /*montes contendo as pilhas de cada naipe*/
    for (i = 0; i < 4; i++ ) {
        P_naipe[i] = PILHAinit();
        carta_0.num = 1;
        carta_0.naipe = 1 + i;
        P_naipe[i] = PILHAput (P_naipe[i], carta_0);
    }
}

/*empilha todas as pilhas da mesa em uma pilha auxiliar e depois desempilha 4*/
/*cartas por pilha; utiliza uma pilha auxiliar (inverte) para manter a ordem */
/*relativa ao empilhar e desempilhar na/da pilha baraux                      */
void redistribui () {
    int i, j;
    apontador baraux;
    apontador inverte;
    baraux = PILHAinit ();
    inverte = PILHAinit ();
    /*empilhando os montes*/
    for (i = 11; i >= 0; i--) {
        while (!PILHAempty (P[i])) {
            /*esvaziando a P[i]*/
            inverte = PILHAput (inverte, PILHAtopo(P[i]));
            P[i] = PILHAget (P[i]);
        }
        while (!PILHAempty(inverte)) {
            /*empilha tudo mantendo a ordem dentro de cada pilha*/
            baraux = PILHAput (baraux, PILHAtopo(inverte));
            inverte = PILHAget (inverte);
        }
    }
    /*rearranjando*/
    i = -1;
    while (!PILHAempty (baraux)) {
        i++;
        for (j = 0; j < 4; j++) {
            if (!PILHAempty (baraux)) {
                /*recolocando as cartas nas pilhas*/
                inverte = PILHAput(inverte, PILHAtopo(baraux));
                baraux = PILHAget (baraux);
            }
        }
        while (!PILHAempty(inverte)) {
            /*empilha tudo mantendo a ordem dentro de cada pilha*/
            P[i] = PILHAput (P[i], PILHAtopo(inverte));
            inverte = PILHAget (inverte);
        }

    }
}

int conta_pontos () {
    int i;
    int cont = 0;
    /*empilhando os montes*/
    for (i = 11; i >= 0; i--) {
        while (!PILHAempty (P[i])) {
            /*esvaziando as P[i]*/
            P[i] = PILHAget (P[i]);
            cont++;
        }
    }
    return cont;
}

/*imprime estado atual das pilhas*/
void estado_atual () {
    int i;
    printf ("\n");
    for (i = 0; i < 4; i++)
        ITEMprint (PILHAtopo (P_naipe[i]));
    printf ("\n");
    printf ("==============================\n");
    for (i = 0; i < 12 && !PILHAempty(P[i]); i++)
        ITEMprint (PILHAtopo (P[i]));
    printf ("\n");
}

void imprime_jog (Item card, int destino, int tipo) {
    if (tipo == 1) {
        printf ("\n Pilha de NAIPES: mova");
        ITEMprint (card);
        printf (" para a pilha %d\n", destino+1);
    }
    else {
        printf ("\n Pilha de CARTAS: mova");
        ITEMprint (card);
        printf (" para a pilha %d\n", destino+1);
    }
}

/*recebe duas cartas e verifica se sao do mesmo naipe*/
    int mesmo_naipe (Item a, Item b) {
        if (a.naipe == b.naipe)
            return 1;
        else 
            return 0;
    }

/*recebe duas cartas e verifica se carta b é a carta seguinte de a*/
    int pCarta_pNaipe (Item a, Item b) {
        if (mesmo_naipe (a, b))
            return (a.num == b.num+1);
        else       
            return 0;
    }

/*recebe duas cartas e verifica se carta b é a carta anterior de a*/
    int pCarta_pCarta (Item a, Item b) {
        if (mesmo_naipe (a, b))
            return (a.num == b.num-1);
        else       
            return 0;
    }

/*empilha "entra" em "a" e desempilha "sai"*/
void movimenta (Item a, int entra, int sai) {
    P[entra] = PILHAput (P[entra],a);
    P[sai] = PILHAget(P[sai]);
}

/* jogada tipo 1; pCarta->pNaipe */
int jogadaT1 () {
    Item a, b;
    int i, j;
    int jogou = 0;
    int tipo = 1;
    for (i = 0; i < 12 && !PILHAempty(P[i]); i++) {
        a = PILHAtopo (P[i]);
        for (j = 0; j < 4; j++) {
            b = PILHAtopo (P_naipe[j]);
            if (pCarta_pNaipe (a, b)) {
                /*movimenta*/
                imprime_jog (a, j, tipo);
                estado_atual();
                P_naipe[j] = PILHAput (P_naipe[j], a);
                P[i] = PILHAget(P[i]);
                i = -1;
                jogou = 1;
                break;
            }
        }
    }
    return jogou;
}

/* jogada tipo 2; pCarta->pCarta */
int jogadaT2 () {
    Item a, b;
    Item card;
    int i, j;
    int jogou = 0;
    int achou = 1;
    int devolve = 0;
    int orig, dest;
    int tipo = 2;
    card.num = -1;
    card.naipe = -1;
    while (achou) { /*enquanto houver jogada entre as 12 pilhas da mesa*/
        achou = 0;
        for (i = 0; i < 12 && !PILHAempty (P[i]); i++) {
            a = PILHAtopo (P[i]);
            for (j = 0; j < 12 && !PILHAempty (P[j]); j++) {
                b = PILHAtopo (P[j]);
                if (pCarta_pCarta (a, b)) { /*verfica se jogada é valida*/
                    if (a.num > card.num) { /*só guarda a maior jogada*/
                        jogou = 1;
                        /*guardando a jogada*/
                        orig = i;
                        dest = j;
                        card = a;
                        break;
                    }
                }
            }
        }
        if (jogou) {
            /*faz jogada*/
            devolve = 1;
            imprime_jog (card, dest, tipo);
            estado_atual();
            movimenta (card, dest, orig);
            card.num = -1;
            jogou = 0;
            achou = 1;
        }
        jogadaT1();
    }
    return devolve;
}



