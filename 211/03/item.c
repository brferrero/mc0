/*********************************************************************
 *  Curso: BCC                                 Disciplina: MAC 211
 *  Data : 2/6/2010                       Exercic. Projeto(parte 2)
 *  Compilador utilizado : gcc versao 4.1.2
 *  ******************************************************************/

/*nesse arquivo se encontram os setters e getters de itens do jogo*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "item.h"

/*vetor que armazena naufragos*/
static naufrago naufragos[MAX_NAUFRAGOS];
static fixo corais[MAX_CORAIS];
static fixo asimov;
static bote botes[NUMBOTES];
static int numeroCoraisNoVetor = 0;
static int proximoNaufrago = 0;
static int numeroNaufragosNoVetor = 0;


/*cria um naufrago no vetor de naufragos*/
int criaNaufrago(float posx, float posy, float vx, float vy)
{
    int i;
    for (i = 0; i < MAX_NAUFRAGOS; i++) {
	if (naufragos[i].livre == 1) {
	    naufragos[i].movimento.posx = posx;
	    naufragos[i].movimento.posy = posy;
	    naufragos[i].movimento.vx = vx;
	    naufragos[i].movimento.vy = vy;
	    naufragos[i].movimento.raio = RAIONAUFRAGO;
	    naufragos[i].livre = 0;
	    numeroNaufragosNoVetor++;
	    return i;
	}
    }
    return -1;
}

/*cria um naufrago no vetor de naufragos*/
void criaBote(int indice, float posx, float posy, float vx, float vy)
{
    botes[indice].ativo = 1;
    botes[indice].movimento.posx = posx;
    botes[indice].movimento.posy = posy;
    botes[indice].movimento.vx = vx;
    botes[indice].movimento.vy = vy;
    botes[indice].movimento.raio = RAIOBOTE;
}

/*remove um naufrago do vetor de naufragos*/
void removeNaufrago(naufrago * passageiro)
{
    passageiro->livre = 1;
    numeroNaufragosNoVetor--;
}

/*retorna o numero de naufragos colocados no vetor de naufragos*/
int numNaufragosNoVetor(void)
{
    return numeroNaufragosNoVetor;
}

/*retorna o numero de corais colocados no vetor de corais*/
int numCoraisNoVetor(void)
{
    return numeroCoraisNoVetor;
}

/*inicializa o vetor de naufragos, marcando-os como livres para uso*/
void inicializaVetorNaufragos(void)
{
    int i;
    for (i = 0; i < MAX_NAUFRAGOS; i++)
	naufragos[i].livre = 1;
}

/*funcao que obtem o naufrago em funcao de seu indice na matriz oceano. devolve NULL se nao encontra-lo*/
naufrago *getNaufrago(int posi, int posj)
{
    int i;
    for (i = 0; i < MAX_NAUFRAGOS; i++) {
	if (naufragos[i].livre)
	    continue;
	if (NEAREST(naufragos[i].movimento.posx) == posi
	    && NEAREST(naufragos[i].movimento.posy) == posj)
	    return &(naufragos[i]);
    }
    return NULL;
}


/*seta uma posicao para a particula fornecida*/
void setParticulaPosicao(particula * p, float posx, float posy)
{
    p->posx = posx;
    p->posy = posy;
}

/*seta uma velocidade para o particula fornecida*/
void setParticulaVelocidade(particula * p, float vx, float vy)
{
    p->vx = vx;
    p->vy = vy;
}

/*obtem a posicao e a velocidade da particula fornecida*/
void getParticulaPosVel(particula * p, float *posx, float *posy, float *vx,
			float *vy)
{
    *posx = p->posx;
    *posy = p->posy;
    *vx = p->vx;
    *vy = p->vy;
}

/*seta a posicao para a particula fornecida que sera usada na proxima iteracao*/
void setParticulaNextPosicao(particula * p, float nextPosx, float nextPosy)
{
    p->nextx = nextPosx;
    p->nexty = nextPosy;
}

/*seta a velocidade para a particula fornecida que sera usada na proxima iteracao*/
void setParticulaNextVelocidade(particula * p, float nextVx, float nextVy)
{
    p->nextVx = nextVx;
    p->nextVy = nextVy;
}

/*obtem a posicao e a velocidade da particula fornecida que sera usado na proxima iteracao*/
void getParticulaNextPosVel(particula * p, float *nextPosx,
			    float *nextPosy, float *nextVx, float *nextVy)
{
    *nextPosx = p->nextx;
    *nextPosy = p->nexty;
    *nextVx = p->nextVx;
    *nextVy = p->nextVy;
}

void setParticulaRaio(particula * p, float raio)
{
    p->raio = raio;
}

float getParticulaRaio(particula * p)
{
    return p->raio;
}

/*obtem a posicao e a velocidade do naufrago fornecido*/
void getNaufragoPosVel(naufrago * passageiro, float *posx, float *posy,
		       float *vx, float *vy)
{
    particula *p;
    p = getParticulaNaufrago(passageiro);
    getParticulaPosVel(p, posx, posy, vx, vy);
}

/*seta a posicao para o naufrago fornecido que sera usada na proxima iteracao*/
void setNaufragoNextPosicao(naufrago * passageiro, float nextPosx,
			    float nextPosy)
{
    particula *p;
    p = getParticulaNaufrago(passageiro);
    setParticulaNextPosicao(p, nextPosx, nextPosy);
}

/*seta a velocidade para o naufrago fornecido que sera usada na proxima iteracao*/
void setNaufragoNextVelocidade(naufrago * passageiro, float nextVx,
			       float nextVy)
{
    particula *p;
    p = getParticulaNaufrago(passageiro);
    setParticulaNextVelocidade(p, nextVx, nextVy);
}

/*obtem a posicao e a velocidade do naufrago fornecido que sera usado na proxima iteracao*/
void getNaufragoNextPosVel(naufrago * passageiro, float *nextPosx,
			   float *nextPosy, float *nextVx, float *nextVy)
{
    particula *p;
    p = getParticulaNaufrago(passageiro);
    getParticulaNextPosVel(p, nextPosx, nextPosy, nextVx, nextVy);
}

/*seta uma posicao para o naufrago fornecido*/
void setNaufragoPosicao(naufrago * passageiro, float posx, float posy)
{
    particula *p;
    p = getParticulaNaufrago(passageiro);
    setParticulaPosicao(p, posx, posy);
}

/*seta uma velocidade para o naufrago fornecido*/
void setNaufragoVelocidade(naufrago * passageiro, float vx, float vy)
{
    particula *p;
    p = getParticulaNaufrago(passageiro);
    setParticulaVelocidade(p, vx, vy);
}

particula *getParticulaNaufrago(naufrago * passageiro)
{
    return &(passageiro->movimento);
}

void setNaufragoRaio(naufrago * passageiro, float raio)
{
    particula *p;
    p = getParticulaNaufrago(passageiro);
    setParticulaRaio(p, raio);
}

void getNaufragoRaio(naufrago * passageiro, float *raio)
{
    particula *p;
    p = getParticulaNaufrago(passageiro);
    *raio = getParticulaRaio(p);
}

naufrago *getNaufragoPorIndice(int i)
{
    return &(naufragos[i]);
}

naufrago *getNaufragoPorIndiceDinamico(int i)
{
    int j;
    naufrago *passageiro;
    int cont = 0;

    for (j = 0; j < MAX_NAUFRAGOS; j++) {
	passageiro = getNaufragoPorIndice(j);
	if (naufragoEstaLivre(passageiro))
	    continue;
	if (cont == i)
	    return &(naufragos[j]);
	cont++;
    }
    return NULL;
}

int naufragoEstaLivre(naufrago * p)
{
    return p->livre;
}

/*a funcao retorna um naufrago do vetor de naufragos, simulando uma lista ligada circular*/
naufrago *nextNaufrago(void)
{
    int antigo;
    int controle = 0;
    while (naufragos[proximoNaufrago].livre && controle < MAX_NAUFRAGOS) {
	proximoNaufrago = (proximoNaufrago + 1) % MAX_NAUFRAGOS;
	controle++;
    }
    if (controle == MAX_NAUFRAGOS) {
	return NULL;
    }
    antigo = proximoNaufrago;
    proximoNaufrago = (proximoNaufrago + 1) % MAX_NAUFRAGOS;
    return &(naufragos[antigo]);
}

void getCoralPosicao(int index, float *posx, float *posy, float *raio)
{
    *posx = corais[index].posx;
    *posy = corais[index].posy;
    *raio = corais[index].raio;
}

void setCoralPosicao(int index, float posx, float posy, float raio)
{
    corais[index].posx = posx;
    corais[index].posy = posy;
    corais[index].raio = raio;
    numeroCoraisNoVetor++;	/*o numero de corais deve ser fixo, portanto cada vez que setamos um, criamos um */
}

void getAsimovPosicao(float *posx, float *posy, float *raio)
{
    *posx = asimov.posx;
    *posy = asimov.posy;
    *raio = asimov.raio;
}

void setAsimovPosicao(float posx, float posy, float raio)
{
    asimov.posx = posx;
    asimov.posy = posy;
    asimov.raio = raio;
}


/*obtem a posicao e a velocidade do bote fornecido*/
void getBotePosVel(int indice, float *posx, float *posy, float *vx,
		   float *vy)
{
    particula *p;
    p = getParticulaBote(indice);
    getParticulaPosVel(p, posx, posy, vx, vy);
}

/*seta a posicao para o btoe fornecido que sera usada na proxima iteracao*/
void setBoteNextPosicao(int indice, float nextPosx, float nextPosy)
{
    particula *p;
    p = getParticulaBote(indice);
    setParticulaNextPosicao(p, nextPosx, nextPosy);
}

/*seta a velocidade para o bote fornecido que sera usada na proxima iteracao*/
void setBoteNextVelocidade(int indice, float nextVx, float nextVy)
{
    particula *p;
    p = getParticulaBote(indice);
    setParticulaNextVelocidade(p, nextVx, nextVy);
}

/*obtem a posicao e a velocidade do bote fornecido que sera usado na proxima iteracao*/
void getBoteNextPosVel(int indice, float *nextPosx, float *nextPosy,
		       float *nextVx, float *nextVy)
{
    particula *p;
    p = getParticulaBote(indice);
    getParticulaNextPosVel(p, nextPosx, nextPosy, nextVx, nextVy);
}

/*seta uma posicao para o bote fornecido*/
void setBotePosicao(int indice, float posx, float posy)
{
    particula *p;
    p = getParticulaBote(indice);
    setParticulaPosicao(p, posx, posy);
}

/*seta uma velocidade para o bote fornecido*/
void setBoteVelocidade(int indice, float vx, float vy)
{
    particula *p;
    p = getParticulaBote(indice);
    setParticulaVelocidade(p, vx, vy);
}

void getBoteRaio(int indice, float *raio)
{
    particula *p;
    p = getParticulaBote(indice);
    *raio = getParticulaRaio(p);
}

void inicializaBotes(void)
{
    int i;
    for (i = 0; i < NUMBOTES; i++) {
	botes[i].ativo = 0;
	botes[i].naufragosSalvos = 0;
    }
}

particula *getParticulaBote(int indice)
{
    return &(botes[indice].movimento);
}

char boteEstaAtivo(int indice)
{
    return botes[indice].ativo;
}

int particulaEhBote(particula * p)
{
    int i;
    for (i = 0; i < NUMBOTES; i++)
	if (getParticulaBote(i) == p)
	    return 1;

    return 0;
}
