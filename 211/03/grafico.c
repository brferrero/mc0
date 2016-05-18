/*********************************************************************
 *  Curso: BCC                                 Disciplina: MAC 211
 *  Data : 2/6/2010                       Exercic. Projeto(parte 2)
 *  Compilador utilizado : gcc versao 4.1.2
 *  ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "oceano.h"
#include "item.h"
#include "fisica.h"

/*limpa todo o oceano*/
void limpaOceano(BITMAP * oceano, BITMAP * buffer)
{
    blit(oceano, buffer, 0, 0, 0, 0, OC_SIZE_X, OC_SIZE_Y);
}

/*imprime todo o oceano*/
void desenhaOceano(BITMAP * buffer, BITMAP * tela)
{
    blit(buffer, tela, 0, 0, 0, 0, OC_SIZE_X, OC_SIZE_Y);
}

void desenhaAsimov(BITMAP * tela)
{
    float posx, posy, raio;
    getAsimovPosicao(&posx, &posy, &raio);
    circlefill(tela, posx, posy, raio, makecol(255, 215, 0));
}

void desenhaCorais(BITMAP * tela)
{
    int i;
    float posx, posy, raio;
    for (i = 0; i < numCoraisNoVetor(); i++) {
	getCoralPosicao(i, &posx, &posy, &raio);
	circlefill(tela, posx, posy, raio, makecol(0, 150, 0));
    }

}

void desenhaNaufragos(BITMAP * tela)
{
    naufrago *primeiro, *next;
    float posx, posy, vx, vy, raio;
    primeiro = nextNaufrago();	/*atua como uma cabeca de lista circular */
    next = primeiro;
    do {			/*enquanto nao da a volta na lista e percorre todos os naufragos */
	if (next == NULL)
	    break;
	getNaufragoPosVel(next, &posx, &posy, &vx, &vy);
	getNaufragoRaio(next, &raio);
	circlefill(tela, posx, posy, raio, makecol(255, 0, 0));
	next = nextNaufrago();
    } while (next != primeiro);
}


void desenhaBotes(BITMAP * tela)
{
    int i;
    float x1, y1, x2, y2, x3, y3;
    for (i = 0; i < NUMBOTES; i++) {
	getBotePontosDesenho(i, &x1, &y1, &x2, &y2, &x3, &y3);
	if ((i % 2) == 0)
	    triangle(tela, x1, y1, x2, y2, x3, y3, makecol(205, 127, 50));
	else
	    triangle(tela, x1, y1, x2, y2, x3, y3, makecol(138, 43, 226));
    }
}
