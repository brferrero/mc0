/*
 *  Alunos: 
 *  GABRIEL TORRES GOMES PATO   NUSP 5128401
 *  RENATO AVILA DOS SANTOS		NUSP 6910041
 *  BRUNO FERRERO               NUSP 3690142
 *  MATHEUS DE LIMA BARBOSA     NUSP 5968663
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BRANCO 1
#define PRETO 2

typedef struct _jogada
{
    int i;
    int j;
} jogada;

/* VARIAVEIS GLOBAIS */
int tab[14][14];
int rodada = 0;
int cor_oponente;
int cor_nossa;
jogada P_oponente[300];
jogada P_nossa[300];
int topo_nosso = 0;
int topo_oponente = 0;
int cont_ponte = 0;
int ponte_valida = 1;

/* FUNCOES OBRIGATORIAS */
void inicializaJogo (int time);
jogada novaJogada ();
void recebeJogada (jogada jog);
/* FUNCOES EXTRAS */
int jogada_valida (jogada jogue);
int fim_de_jogo (int cor_peca);
void atualizatab (jogada, int);
jogada verifica_ponte (int time);
int busca_fim (int cor ); 
void imprime ();
/* PILHA */
int pilhaVazia (int topo);   
jogada topoPilha (jogada p[], int topo);
void empilha (jogada P[], int *topo, jogada t);
void desempilha (int *topo);
int pilhaVazia (int topo); 

/**************************************************************************************************/
/* RECEBE JOGADA E DEVOLVE SE A MESMA FOI VALIDA */
int jogada_valida (jogada jogue)
{
    if (jogue.i >= 14 || jogue.j >= 14 || jogue.i < 0 || jogue.j < 0)
        return 0;
    if (tab[jogue.i][jogue.j] == 0)
        return 1;
    return 0;
}

/**************************************************************************************************/
/* RECEBE COR DE UM TIME E DEVOLVE SE JOGO TERMINOU */
int fim_de_jogo (int cor_peca)
{
    int front, front2;
    front = 0; 
    front2 = 0;
    if (rodada < 25)
        return 0;
    return busca_fim (cor_peca);
}

/**************************************************************************************************/
/* DETERMINA QUEM JOGA EM CADA TIME */
void inicializaJogo (int time)
{
    if (time == 1) {
        cor_nossa = BRANCO;
        cor_oponente = PRETO;
    }
    else {
        cor_nossa = PRETO;
        cor_oponente = BRANCO;
    }
}

/**************************************************************************************************/
/* RECEBE JOGOADA ADVERSARIA E ATUALIZA NOSSO TABULEIRO */
void recebeJogada (jogada jog)
{
    jogada t;
    if (rodada == 1) {
        t = topoPilha (P_nossa, topo_nosso);
        /*pie rule*/
        if (jog.i == t.i && jog.j == t.j) {
            inicializaJogo(PRETO);
            rodada--;
            desempilha(&topo_nosso);
        }
    }
    else if (!jogada_valida (jog)) {
        printf("Jogada Invalida! Voce Perdeu! =D\n");
        exit(0);
    }
    atualizatab (jog, cor_oponente);
    empilha (P_oponente, &topo_oponente, jog);
}

/**************************************************************************************************/
/* VERIFICA SE ALGUM TIME(cor) ATRAVESSOU O TABULEIRO */
int busca_fim (int cor)
{
    int i, j, marca;
    int tab_aux[14][14];
    marca = 1;
    for (i = 0; i < 14; i++)
        for (j = 0; j < 14; j++)
            tab_aux[i][j] = 0;
    if (cor == 1) {
        for (j = 0; j < 14; j++) {
            if (tab[0][j] == cor)
                tab_aux[0][j] = marca;
            marca++;
        }
        for (i = 1; i < 14; i++) {
            for (j = 0; j < 14; j++) {
                if (tab[i][j] == cor) {
                    if (tab_aux[i-1][j] != 0)
                        tab_aux[i][j] = tab_aux[i-1][j];
                    else if (tab_aux[i-1][j+1] != 0)
                        tab_aux[i][j] = tab_aux[i-1][j+1];
                    else if (j-1 >= 0 && tab[i][j-1] != 0)
                        tab_aux[i][j] = tab_aux[i][j-1];
                }
                if (i == 13 && tab_aux[i][j] != 0)
                    return 1;
            }
        }
    }
    else {
        marca = 0;
        for (i = 0; i < 14; i++) {
            if (tab[i][0] == cor)
                tab_aux[i][0] = marca;
            marca++;
        }
        for (j = 1; j < 14; j++) {
            for (i = 0; i < 14; i++) {
                if (tab[i][j] == cor) {
                    if (tab_aux[i][j-1] != 0)
                        tab_aux[i][j] = tab_aux[i][j-1];
                    else if (tab_aux[i+1][j-1] != 0)
                        tab_aux[i][j] = tab_aux[i+1][j-1];
                    else if (i-1 >= 0 && tab[i-1][j] != 0)
                        tab_aux[i][j] = tab_aux[i-1][j];
                }
                if (j == 13 && tab_aux[i][j] != 0)
                    return 1;
            }
        }
    }
    return 0;
}

/*************************************************************************************************/
/* DEVOLVE NOSSA JOGADA */
jogada novaJogada ()
{
    jogada minha, oponente, minha_anterior;
    int x, y, i, j, z, w;
    /*FAZENDO PRIMEIRA JOGADA*/
    if (pilhaVazia (topo_nosso)) {
        if (cor_nossa == PRETO) {
            /*nao faremos o swap, pois nao eh util para nossa estrategia*/
            oponente = topoPilha (P_oponente, topo_oponente);
            z = oponente.i;
            w = oponente.j;
            if (z == 8 && w == 0) {
                minha.i = 7;
                minha.j = 0;
            }
            else {
                minha.i = 8;
                minha.j = 0;
            }
        }
        else {
            if (z == 0 && w == 8) {
                minha.i = 0;
                minha.j = 7;
            }
            else {
                minha.i = 0;
                minha.j = 8;
            }
        }
        empilha (P_nossa, &topo_nosso, minha);
        atualizatab (minha, cor_nossa);
        return minha;
    }

    minha_anterior = topoPilha (P_nossa, topo_nosso); /*ultima jogada*/
    x = minha_anterior.i;
    y = minha_anterior.j;
    oponente = topoPilha (P_oponente, topo_oponente);
    z = oponente.i;
    w = oponente.j;

    /*FECHANDO AS PONTES QUE O ADVERSARIO TENTA BLOQUEAR*/
    if (z+1 < 14 && z-1 >= 0 && w-1 >= 0 && tab[z+1][w-1] == cor_nossa && tab[z-1][w] == cor_nossa && tab[z][w-1] == 0) /*fecha ponte pela esquerda*/
    {
        minha.i = z;
        minha.j = w-1;
        cont_ponte--;
        atualizatab (minha, cor_nossa);
        return minha;
    }
    if (z+1 < 14 && z-1 >= 0 && w+1 < 14 && tab[z+1][w] == cor_nossa && tab[z-1][w+1] == cor_nossa && tab[z][w+1] == 0) /*fecha ponte pela direita*/
    {
        minha.i = z;
        minha.j = w+1;
        cont_ponte--;
        atualizatab (minha, cor_nossa);
        return minha;
    }
    if (z-1 >= 0 && w+1 < 14 && tab[z][w+1] == cor_nossa && tab[z-1][w] == cor_nossa && tab[z-1][w+1] == 0) /*fecha ponte pela diagonal superior*/
    {
        minha.i = z-1;
        minha.j = w+1;
        cont_ponte--;
        atualizatab (minha, cor_nossa);
        return minha;
    }
    if (z+1 < 14 && w-1 >= 0 && tab[z][w-1] == cor_nossa && tab[z+1][w] == cor_nossa && tab[z+1][w-1] == 0) /*fecha ponte pela diagonal inferior*/
    {
        minha.i = z+1;
        minha.j = w-1;
        cont_ponte--;
        atualizatab (minha, cor_nossa);
        return minha;
    }
    if (z+1 < 14 && w+1 < 14 && w-1 >= 0 && tab[z+1][w-1] == cor_nossa && tab[z][w+1] == cor_nossa && tab[z+1][w] == 0) /*fecha ponte diagonal inf. baixo*/
    {
        minha.i = z+1;
        minha.j = w;
        cont_ponte--;
        atualizatab (minha, cor_nossa);
        return minha;
    }
    if (w+1 < 14 && z-1 >= 0 && w-1 >= 0 && tab[z][w-1] == cor_nossa && tab[z-1][w+1] == cor_nossa && tab[z-1][w] == 0) /*fecha ponte diagonal sup. baixo.*/
    {
        minha.i = z-1;
        minha.j = w;
        cont_ponte--;
        atualizatab (minha, cor_nossa);
        return minha;
    }

    /*FAZENDO PONTES*/
    if (cor_nossa == PRETO && ponte_valida && z < 12)
    {
        if (y == 12) {
            /*atravessou o tabuleiro*/
            if (x-1 >= 0 && tab[x-1][y+1] == 0) {
                minha.i = x-1;
                minha.j = y+1;
                ponte_valida = 0;
                atualizatab (minha, cor_nossa);
                return minha;
            }
            if (tab[x][y+1] == 0) {
                minha.i = x;
                minha.j = y+1;
                ponte_valida = 0;
                atualizatab (minha, cor_nossa);
                return minha;
            }
        }
        if (x-1 >= 0 && y+2 < 14 && tab[x-1][y+2] == 0) /*ponte para direita superior*/
        {
            minha.i = x-1;
            minha.j = y+2;
            cont_ponte++;
            empilha (P_nossa, &topo_nosso, minha);
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (x+1 < 14 && y+1 < 14 && tab[x+1][y+1] == 0) /*ponte para direita inferior*/
        {
            minha.i = x+1;
            minha.j = y+1;
            cont_ponte++;
            empilha (P_nossa, &topo_nosso, minha);
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (x+1 < 14 && y-2 >= 0 && tab[x+1][y-2] == 0) /*ponte para esquerda inferior*/
        {
            minha.i = x+1;
            minha.j = y-2;
            cont_ponte++;
            empilha (P_nossa, &topo_nosso, minha);
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (x-1 >= 0 && y-1 >= 0 && tab[x-1][y-1] == 0) /*ponte para esquerda superior*/
        {
            minha.i = x-1;
            minha.j = y-1;
            cont_ponte++;
            empilha (P_nossa, &topo_nosso, minha);
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (x+2 < 14 && y-1 >= 0 && tab[x+2][y-1] == 0) /*ponte vertical para baixo*/
        {
            minha.i = x+2;
            minha.j = y-1;
            cont_ponte++;
            empilha (P_nossa, &topo_nosso, minha);
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (x-2 >= 0 && y+1 < 14 && tab[x-2][y+1] == 0) /*ponte vertical para cima*/
        {
            minha.i = x-2;
            minha.j = y+1;
            cont_ponte++;
            empilha (P_nossa, &topo_nosso, minha);
            atualizatab (minha, cor_nossa);
            return minha;
        }
    }
    else if (cor_nossa == BRANCO && ponte_valida && w < 12) {
        if (x == 12) {
            if (y-1 >= 0 && tab[x+1][y-1] == 0) {
                minha.i = x+1;
                minha.j = y-1;
                ponte_valida = 0;
                empilha (P_nossa, &topo_nosso, minha);
                atualizatab (minha, cor_nossa);
                return minha;
            }
            if(tab[x+1][y] == 0) {
                minha.i = x+1;
                minha.j = y;
                ponte_valida = 0;
                empilha (P_nossa, &topo_nosso, minha);
                atualizatab (minha, cor_nossa);
                return minha;
            }
        }
        /*FAZENDO PONTES*/
        if (x+2 < 14 && y-1 >= 0 && tab[x+2][y-1] == 0) /*ponte vertical para baixo*/
        {
            minha.i = x+2;
            minha.j = y-1;
            cont_ponte++;
            empilha (P_nossa, &topo_nosso, minha);
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (x-2 >= 0 && y+1 < 14 && tab[x-2][y+1] == 0) /*ponte vertical para cima*/
        {
            minha.i = x-2;
            minha.j = y+1;
            cont_ponte++;
            empilha (P_nossa, &topo_nosso, minha);
            atualizatab (minha, cor_nossa);
            return minha;
        }		
        if (x+1 < 14 && y+1 < 14 && tab[x+1][y+1] == 0) /*ponte para direita inferior*/
        {
            minha.i = x+1;
            minha.j = y+1;
            cont_ponte++;
            empilha (P_nossa, &topo_nosso, minha);
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (x+1 < 14 && y-2 >= 0 && tab[x+1][y-2] == 0) /*ponte para esquerda inferior*/
        {
            minha.i = x+1;
            minha.j = y-2;
            cont_ponte++;
            empilha (P_nossa, &topo_nosso, minha);
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (x-1 >= 0 && y-1 >= 0 && tab[x-1][y-1] == 0) /*ponte para esquerda superior*/
        {
            minha.i = x-1;
            minha.j = y-1;
            cont_ponte++;
            empilha (P_nossa, &topo_nosso, minha);
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (x-1 >= 0 && y+2 < 14 && tab[x-1][y+2] == 0) /*ponte para direita superior*/
        {
            minha.i = x-1;
            minha.j = y+2;
            cont_ponte++;
            empilha (P_nossa, &topo_nosso, minha);
            atualizatab (minha, cor_nossa);
            return minha;
        }
    }

    /*FECHANDO PONTES QUE NAO CORREM PERIGO IMEDIATO*/
    minha = verifica_ponte(cor_nossa);
    if (minha.i != -1 && minha.j != -1) {
        atualizatab (minha, cor_nossa);
        return minha;
    }

    /*BLOQUEANDO JOGADA ADVERSARIA*/
    if(cor_nossa == PRETO) {
        if (z+1 < 14 && tab[z+1][w] == 0) /*bloqueio baixo direita*/
        {
            minha.i = z+1;
            minha.j = w;
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (z+1 < 14 && w-1 >= 0 && tab[z+1][w-1] == 0) /*bloqueio baixo esquerda*/
        {
            minha.i = z+1;
            minha.j = w-1;
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (z-1 >= 0 && tab[z-1][w] == 0) /*bloqueio cima esquersa*/
        {
            minha.i = z-1;
            minha.j = w;
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (z-1 >= 0 && w+1 < 14 && tab[z-1][w+1] == 0) /*bloqueio cima direita*/
        {
            minha.i = z-1;
            minha.j = w+1;
            atualizatab (minha, cor_nossa);
            return minha;
        }
    }
    else {
        if (w+1 < 14 && tab[z][w+1] == 0) /*bloqueio direita*/
        {
            minha.i = z;
            minha.j = w+1;
            atualizatab (minha, cor_nossa);
            return minha;
        }
        if (w-1 >= 0 && tab[z][w-1] == 0) /*bloqueio esquerda*/
        {
            minha.i = z;
            minha.j = w-1;
            atualizatab (minha, cor_nossa);
            return minha;
        }
    }

    /*JOGANDO NAS REDONDEZAS DA ULTIMA JOGADA*/
    for (i = x-3; i < x+3; i++) {
        for (j = y-3; j < y+3; j++) {
            if (i >= 0 && i < 14 && j >= 0 && j < 14 && tab[i][j] == 0) {
                minha.i = i;
                minha.j = j;
                empilha (P_nossa, &topo_nosso, minha);
                atualizatab (minha, cor_nossa);
                return minha;
            }
        }
    }
    /*FAZ A PRIMEIRA JOGADA LIVRE*/
    for (i = 0; i < 14; i++) {
        for (j = 0; j < 14; j++) {
            if (tab[i][j] == 0) {
                minha.i = i;
                minha.j = j;
                atualizatab(minha, cor_nossa);
                return minha;
            }
        }
    }
    return minha;
}

/*************************************************************************************************/

void imprime ()
{
    int i, j,k;
    printf ("\033[41;31;1m-------------------------------------------\033[m");
    printf ("\n");
    for (i = 0; i < 14; i++) {	
        for (k = 0; k < i; k++)
            printf ("  ");
        printf ("\033[44;34;1m\\\033[m");
        printf (" ");
        for (j = 0; j < 14; j++) {
            if(tab[i][j] == BRANCO) {
                printf ("\033[31;1m%c  \033[m", 42);
                /*printf("%d",BRANCO);*/
            }
            else if(tab[i][j] == PRETO) {
                printf ("\033[34;1m%c  \033[m", 42);
                /*printf ("%d",PRETO);*/
            }
            else 
                printf ("%c  ",'-');
        }
        printf ("\033[44;34;1m\\\033[m");
        printf ("\n");
    }
    printf ("                           ");
    printf ("\033[41;31;1m--------------------------------------------\033[m");
    printf ("\n");
}

/**************************************************************************************************/

void atualizatab (jogada jog, int cor)
{
    tab[jog.i][jog.j] = cor;
}

/**************************************************************************************************/
void empilha (jogada P[], int *topo, jogada t)
{
    P[*topo] = t;
    (*topo)++;
}

/***************************************************************************************************/

void desempilha (int *topo)
{
    if (*topo == 0)
        printf ("ERRO."); /* \n */
    else
        (*topo)--;
}

/***************************************************************************************************/

int pilhaVazia (int topo)
{
    return (topo == 0);
}

/***************************************************************************************************/

jogada topoPilha (jogada p[], int topo)
{
    return (p[topo-1]);
}

/***************************************************************************************************/
/* RECEBE UM TIME E VERIFICA SE HA ALGUMA PONTE PARA ESTE TIME */
jogada verifica_ponte (int time)
{
    jogada nova, jog;
    int i, x, y, procura;
    if (time == cor_nossa)
        procura = topo_nosso;
    else
        procura = topo_oponente;

    for (i = 0; i < procura; i++) {
        if (time == cor_nossa)
            nova = topoPilha (P_nossa, topo_nosso-i);
        else
            nova = topoPilha (P_oponente, topo_oponente-i);
        x = nova.i;
        y = nova.j;
        if (x+2 < 14 && y-1 >= 0 && tab[x+2][y-1] == time) /*vertical para baixo*/
        {
            if (tab[x+1][y-1] == 0 && tab[x+1][y] != time) {
                jog.i = x+1;
                jog.j = y-1;
                return jog;
            }
            if (tab[x+1][y] == 0 && tab[x+1][y-1] != time) {
                jog.i = x+1;
                jog.j = y;
                return jog;
            }
        }

        if (x-2 >= 0 && y+1 < 14 && tab[x-2][y+1] == time) /*vertical para cima*/
        {
            if (tab[x-1][y+1] == 0 && tab[x-1][y] != time) {
                jog.i = x-1;
                jog.j = y+1;
                return jog;
            }
            if (tab[x-1][y] == 0 && tab[x-1][y+1] != time) {
                jog.i = x-1;
                jog.j = y;
                return jog;
            }
        }

        if (x+1 < 14 && y+1 < 14 && tab[x+1][y+1] == time) /*diagonal direita baixo*/
        {
            if (tab[x+1][y] == 0 && tab[x][y+1] != time) {
                jog.i = x+1;
                jog.j = y;
                return jog;
            }
            if (tab[x][y+1] == 0 && tab[x+1][y] != time) {
                jog.i = x;
                jog.j = y+1;
                return jog;
            }
        }

        if (x-1 >= 0 && y-1 >= 0 && tab[x-1][y-1] == time) /*diagonal direita cima*/
        {
            if (tab[x-1][y] == 0 && tab[x][y-1] != time) {
                jog.i = x-1;
                jog.j = y;
                return jog;
            }
            if (tab[x][y-1] == 0 && tab[x-1][y] != time) {
                jog.i = x;
                jog.j = y-1;
                return jog;
            }
        }

        if (x-1 >= 0 && y+2 < 14 && tab[x-1][y+2] == time) /*diagonal esquerda cima*/
        {
            if (tab[x-1][y+1] == 0 && tab[x][y+1] != time) {
                jog.i = x-1;
                jog.j = y+1;
                return jog;
            }
            if (tab[x][y+1] == 0 && tab[x-1][y+1] != time) {
                jog.i = x;
                jog.j = y+1;
                return jog;
            }
        }

        if (x+1 < 14 && y-2 >= 0 && tab[x+1][y-2] == time) /*diagonal esuqerda baixo*/
        {
            if (tab[x+1][y-1] == 0 && tab[x][y-1] != time) {
                jog.i = x+1;
                jog.j = y-1;
                return jog;
            }
            if (tab[x][y-1] == 0 && tab[x+1][y-1] != time) {
                jog.i = x;
                jog.j = y-1;
                return jog;
            }
        }
    }
    jog.i = -1;
    jog.j = -1;
    return jog;
}

/***************************************************************************************************/

int main ()
{
    jogada jog;
    int i;
    inicializaJogo (1);
    printf ("inicializou\n");
    if (cor_nossa == BRANCO ) {
        novaJogada ();
        printf ("Vai jogar com branco\n");
        printf ("Essa eh a minha jogada\n");
        imprime ();
        rodada++;

    }
    scanf ("%d %d", &jog.i, &jog.j);
    recebeJogada (jog);
    printf ("Essa eh sua jogada\n");
    imprime ();
    rodada++;
    printf ("\n \n");
    for (i = 0; i < 14*14; i++) {
        novaJogada ();
        rodada++;
        printf ("Essa eh a minha jogada\n");
        imprime ();
        if (fim_de_jogo(cor_nossa)) {
            printf ("Ganhei amigao ;D\n");
            return 0;
        }
        printf ("\n \n");
        scanf ("%d %d", &jog.i, &jog.j);
        recebeJogada (jog);
        rodada++;
        printf ("Essa eh sua jogada\n");
        imprime ();
        if (fim_de_jogo(cor_oponente)) {
            printf ("Voce ganhou. Parabens\n");
            return 0;
        }
        printf ("\n \n");
    }	
    return 0;
}

/***************************************************************************************************/
