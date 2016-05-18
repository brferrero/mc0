/*********************************************************************
 *  Curso: BCC                                 Disciplina: MAC 211
 *  Data : 2/6/2010                       Exercic. Projeto(parte 2)
 *  Compilador utilizado : gcc versao 4.1.2
 *  ******************************************************************/

#include <allegro.h>
#include "item.h"
#include "fisica.h"
#include "oceano.h"
#include "colisao.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static int tempo = 0;

/* o naufrago continua na mesma direcao com 65% de chance;
  muda para as demais direcoes com 5% de chance cada uma */
int sorteioMarkov(float vx, float vy, float *newVx, float *newVy)
{
    int sorteio;
    float dir, vel;
    euclidianoParaPolar(vx, vy, &dir, &vel);
    sorteio = rand() % 100;
    if (sorteio < 65) {
	limiteVelocidade(&vx, &vy);
	*newVx = vx;
	*newVy = vy;
	return sorteio;
    } else if (sorteio >= 65 && sorteio < 70) {
	dir = dir + (1.0 * ANGtheta);
	if (dir >= 360)
	    dir -= 360;
    } else if (sorteio >= 70 && sorteio < 75) {
	dir = dir + (2.0 * ANGtheta);
	if (dir >= 360)
	    dir -= 360;
    } else if (sorteio >= 75 && sorteio < 80) {
	dir = dir + (3.0 * ANGtheta);
	if (dir >= 360)
	    dir -= 360;
    } else if (sorteio >= 80 && sorteio < 85) {
	dir = dir + (4.0 * ANGtheta);
	if (dir >= 360)
	    dir -= 360;
    } else if (sorteio >= 85 && sorteio < 90) {
	dir = dir + (5.0 * ANGtheta);
	if (dir >= 360)
	    dir -= 360;
    } else if (sorteio >= 90 && sorteio < 95) {
	dir = dir + (6.0 * ANGtheta);
	if (dir >= 360)
	    dir -= 360;
    } else if (sorteio >= 95 && sorteio < 100) {
	dir = dir + (7.0 * ANGtheta);
	if (dir >= 360)
	    dir -= 360;
    }
    polarParaEuclidiano(dir, vel, &vx, &vy);
    /*limita a intensidade das velocidades */
    limiteVelocidade(&vx, &vy);
    *newVx = vx;
    *newVy = vy;
    return sorteio;
}

/*atualiza a proxima posicao do naufrago utilizando para isso o seu vetor velocidade*/
void calculaProximaPosicaoParticula(particula * p)
{
    float vx, vy, posx, posy;
    getParticulaPosVel(p, &posx, &posy, &vx, &vy);
    setParticulaNextPosicao(p, posx + vx, posy + vy);
}

/*atualiza a proxima direcao do naufrago utilizando para isso uma cadeia de markov*/
void calculaProximaDirecaoParticula(particula * p)
{
    float vx, vy, posx, posy;
    float newVx, newVy;
    getParticulaPosVel(p, &posx, &posy, &vx, &vy);
    sorteioMarkov(vx, vy, &newVx, &newVy);
    setParticulaNextVelocidade(p, newVx, newVy);
}

/*calcula a proxima posicao e velocidade de todos os naufragos*/
void calculaProximoEstadoParticulas(void)
{
    int i;
    naufrago *primeiro, *next;
    particula *p;

    for (i = 0; i < NUMBOTES; i++) {
	if (boteEstaAtivo(i)) {
	    p = getParticulaBote(i);
	    calculaProximaPosicaoParticula(p);
	    calculaProximaDirecaoParticula(p);
	}
    }

    primeiro = nextNaufrago();	/*atua como uma cabeca de lista circular */
    if (primeiro != NULL) {
	p = getParticulaNaufrago(primeiro);
	calculaProximaPosicaoParticula(p);
	calculaProximaDirecaoParticula(p);
	next = nextNaufrago();
	while (next != primeiro) {	/*enquanto nao da a volta na lista e percorre todos os naufragos */
	    p = getParticulaNaufrago(next);
	    calculaProximaPosicaoParticula(p);
	    calculaProximaDirecaoParticula(p);
	    next = nextNaufrago();
	}
    }
}

/*troca posicao e velocidade atual, por proxima posicao e proxima velocidade. eh a execucao de um passo de tempo*/
void iteracaoParaProximoPasso(void)
{
    int i;
    int indice1, indice2;
    float nextPosx, nextPosy, nextVx, nextVy;
    naufrago *passageiro;

    atualizaEstruturaColisao();
    while (existeColisao(&indice1, &indice2)) {
	trataColisao(indice1, indice2);
	atualizaEstruturaColisao();
    }

    for (i = 0; i < NUMBOTES; i++) {
	if (boteEstaAtivo(i)) {
	    getBoteNextPosVel(i, &nextPosx, &nextPosy, &nextVx, &nextVy);
	    setBotePosicao(i, nextPosx, nextPosy);
	    setBoteVelocidade(i, nextVx, nextVy);
	}
    }

    for (i = 0; i < MAX_NAUFRAGOS; i++) {
	passageiro = getNaufragoPorIndice(i);
	if (naufragoEstaLivre(passageiro))
	    continue;		/*se o elemento naufrago nao esta inicializado no jogo, pula ele */
	/*trata todas as colisoes da particula p */
	if (naufragoEstaLivre(passageiro))
	    continue;
	getNaufragoNextPosVel(passageiro, &nextPosx, &nextPosy, &nextVx,
			      &nextVy);
	setNaufragoPosicao(passageiro, nextPosx, nextPosy);
	setNaufragoVelocidade(passageiro, nextVx, nextVy);
    }
}

/*transferencia de momento assumindo colisao elastica e que cada naufrago tem o mesmo peso*/
void transfereMomento(naufrago * passivo, naufrago * ativo)
{
    /*formula: v1f = 2m2v2i/(m1 + m2) + v1i(m1 - m2)/(m1 + m2) */
    /*         v2f = 2m1v1i/(m1 + m2) + v2i(m2 - m1)/(m2 + m1) */
    float pposx, pposy, pvx, pvy;
    float aposx, aposy, avx, avy;
    getNaufragoPosVel(ativo, &aposx, &aposy, &avx, &avy);
    getNaufragoPosVel(passivo, &pposx, &pposy, &pvx, &pvy);
    setNaufragoVelocidade(ativo, pvx, pvy);	/*troca as velocidades */
    setNaufragoVelocidade(passivo, avx, avy);
}

/*limita as velocidades*/
void limiteVelocidade(float *vx, float *vy)
{
    if (*vx > VXMAX) {
	*vx = VXMAX;
    } else if (*vx < -VXMAX) {
	*vx = -VXMAX;
    }
    if (*vy > VYMAX) {
	*vy = VYMAX;
    } else if (*vy < -VYMAX) {
	*vy = -VYMAX;
    }
}

/*transforma de coordenada polar para coordenada euclidiana*/
void polarParaEuclidiano(float dir, float vel, float *vx, float *vy)
{
    *vx = vel * cos(GRAUS2RAD(dir));
    *vy = vel * sin(GRAUS2RAD(dir));
}

/*transforma de coordenada euclidiana para coordenada polar*/
void euclidianoParaPolar(float vx, float vy, float *dir, float *vel)
{
    *vel = sqrt(vx * vx + vy * vy);
    if (*vel >= EPS) {
	/*decompoe a direcao */
	*dir = RAD2GRAUS(atan2(vy, vx));
	if (*dir < 0)
	    *dir += 360.0;
    }
}

/*incrementa o tempo do jogo*/
void incrementaTempo(int incremento)
{
    tempo += incremento;
}

float distanciaEuclidiana(float x1, float y1, float x2, float y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

/*retorna o tempo*/
int getTempo(void)
{
    return tempo;
}
