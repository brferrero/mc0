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
#include "colisao.h"

static int naufragosNovos = 0;	/*naufragos gerados depois do inicio do jogo */
static float freqGeraPassageiro;	/*frequencia com que os naufragos sao gerados */
static float mediaDaVelocidadeGerada;	/*velocidade media dos naufragos gerados */
static float desvioDaVelocidadeGerada;	/*desvio padrao da velocidade media */

/*determina o local o asimov naufragou*/
void naufragioAsimov(void)
{
    int posi, posj;
    posi = (rand() % OC_SIZE_X);
    posj = (rand() % OC_SIZE_Y);
    while ((posi - RAIOASIMOV < 0) || (posi + RAIOASIMOV >= OC_SIZE_X) ||
	   (posj - RAIOASIMOV < 0) || (posj + RAIOASIMOV >= OC_SIZE_Y)) {
	posi = (rand() % OC_SIZE_X);
	posj = (rand() % OC_SIZE_Y);
    }
    setAsimovPosicao((float) posi, (float) posj, RAIOASIMOV);
}

/*povoa o oceano com corais em posicoes aleatorias*/
void populaCorais(int quantidade)
{
    int lin, col, i;
    float raio;
    /*limita o numero maximo de corais gerados */
    if (quantidade > MAX_CORAIS)
	quantidade = MAX_CORAIS;
    for (i = 0; i < quantidade; i++) {
	raio = geraTamanhoCoral();
	lin = rand() % OC_SIZE_X;
	col = rand() % OC_SIZE_Y;
	while (!podeCriarPosicao((float) lin, (float) col, raio)) {
	    lin = rand() % OC_SIZE_X;
	    col = rand() % OC_SIZE_Y;
	}
	setCoralPosicao(i, (float) lin, (float) col, raio);
    }
}

float geraTamanhoCoral(void)
{
    int chave;
    chave = rand() % 3;
    if (chave == 0)
	return CORALPQ;
    else if (chave == 1)
	return CORALMD;
    else
	return CORALGR;
}

void getBotePontosDesenho(int indice, float *x1, float *y1, float *x2,
			  float *y2, float *x3, float *y3)
{

    float posx, posy, dx, dy, dir, raio;

    getBotePosVel(indice, &posx, &posy, &dx, &dy);
    euclidianoParaPolar(dx, dy, &dir, &raio);
    getBoteRaio(indice, &raio);
    /*ponto da frente do triangulo */
    polarParaEuclidiano(dir, raio, &dx, &dy);
    *x1 = posx + dx;
    *y1 = posy + dy;
    /*deslocamento de 150 graus para o proximo vertice do triangulo */
    dir += 150;
    if (dir > 360)
	dir -= 360;
    polarParaEuclidiano(dir, raio, &dx, &dy);
    *x2 = posx + dx;
    *y2 = posy + dy;
    /*deslocamento de 60 graus para o proximo vertice do triangulo */
    dir += 60;
    if (dir > 360)
	dir -= 360;
    polarParaEuclidiano(dir, raio, &dx, &dy);
    *x3 = posx + dx;
    *y3 = posy + dy;
}


/*povoa o oceano com naufragos em posicao aleatorias*/
void populaNaufragos(int quantidade)
{
    int lin, col, i;
    float vx, vy;

    for (i = 0; i < quantidade; i++) {
	/*teste limite de naufragos gerados */
	if (numNaufragosNoVetor() >= MAX_NAUFRAGOS)
	    break;
	sorteiaVelocidade(&vx, &vy);
	lin = rand() % OC_SIZE_X;
	col = rand() % OC_SIZE_Y;
	/*verifica se intersecciona com naufragos gerados anteriores */
	while (!podeCriarPosicao((float) lin, (float) col, RAIONAUFRAGO)) {
	    lin = rand() % OC_SIZE_X;
	    col = rand() % OC_SIZE_Y;
	}
	criaNaufrago((float) lin, (float) col, vx, vy);
    }
}

/*cria os botes posicionados em algum lugar da borda do oceano*/
void criaBotes(void)
{
    int borda1, borda2, i;
    float vx, vy;

    for (i = 0; i < NUMBOTES; i++) {
	sorteiaVelocidade(&vx, &vy);
	sorteiaBordas(&borda1, &borda2, RAIOBOTE);
	/*verifica se intersecciona com objetos criados anteriormente */
	while (!podeCriarPosicao((float) borda1, (float) borda2, RAIOBOTE)) {
	    sorteiaBordas(&borda1, &borda2, RAIOBOTE);
	}
	criaBote(i, (float) borda1, (float) borda2, vx, vy);
    }
}

/*povoa o oceano com naufragos posicionados na borda*/
void geraNaufragosBorda(int quantidade)
{
    int lin, col, i;
    float vx, vy;
    for (i = 0; i < quantidade; i++) {
	if (numNaufragosNoVetor() >= MAX_NAUFRAGOS)
	    break;
	sorteiaVelocidade(&vx, &vy);
	sorteiaBordas(&lin, &col, RAIONAUFRAGO);

	while (!podeCriarPosicao((float) lin, (float) col, RAIONAUFRAGO))
	    sorteiaBordas(&lin, &col, RAIONAUFRAGO);
#ifdef DEBUG_COLISAO
	printf("gerado naufrago em (%d, %d)\n", lin, col);
#endif
	criaNaufrago((float) lin, (float) col, vx, vy);
    }
}

int podeCriarPosicao(float posx, float posy, float raio)
{
    int i;
    float coralPosx, coralPosy, coralRaio;
    float asimovPosx, asimovPosy, asimovRaio;
    naufrago *primeiro, *next;
    float posx2, posy2, vx2, vy2;
    float raio2;

    /*verifica se estao dentro das limitacoes do oceano (tela) */
    if (posx - raio < 0 || posx + raio >= OC_SIZE_X)
	return 0;
    if (posy - raio < 0 || posy + raio >= OC_SIZE_Y)
	return 0;

    /*verifica se nao vai ser sobreposto ao navio asimov */
    getAsimovPosicao(&asimovPosx, &asimovPosy, &asimovRaio);
    if (distanciaEuclidiana(posx, posy, asimovPosx, asimovPosy) <
	asimovRaio + raio)
	return 0;

    /*verifica se nao vai ser sobreposto a algum coral */
    for (i = 0; i < numCoraisNoVetor(); i++) {
	getCoralPosicao(i, &coralPosx, &coralPosy, &coralRaio);
	if (distanciaEuclidiana(posx, posy, coralPosx, coralPosy) <
	    coralRaio + raio) {
	    return 0;
	}
    }
    primeiro = nextNaufrago();	/*atua como uma cabeca de lista circular */
    next = primeiro;
    do {			/*enquanto nao da a volta na lista e percorre todos os naufragos */
	if (next == NULL)
	    break;
	getNaufragoPosVel(next, &posx2, &posy2, &vx2, &vy2);
	getNaufragoRaio(next, &raio2);
	if (distanciaEuclidiana(posx, posy, posx2, posy2) < raio2 + raio)
	    return 0;
	next = nextNaufrago();
    } while (next != primeiro);

    /*verifica se nao vai ser sobreposto aos botes */
    for (i = 0; i < NUMBOTES; i++) {
	if (boteEstaAtivo(i)) {
	    getBotePosVel(i, &posx2, &posy2, &vx2, &vy2);
	    getBoteRaio(i, &raio2);
	    if (distanciaEuclidiana(posx, posy, posx2, posy2) <
		raio2 + raio) {
		return 0;
	    }
	}
    }
    return 1;
}

/*retorna um valor de bordas aleatorio para as variaveis borda1 e borda2*/
void sorteiaBordas(int *borda1, int *borda2, int raio)
{
    int sorteio;
    sorteio = rand() % 4;
    if (sorteio == 0) {
	*borda1 = 0 + raio;
	*borda2 = rand() % OC_SIZE_Y;
    } else if (sorteio == 1) {
	*borda1 = OC_SIZE_X - 1 - raio;
	*borda2 = rand() % OC_SIZE_Y;
    } else if (sorteio == 2) {
	*borda1 = rand() % OC_SIZE_X;
	*borda2 = OC_SIZE_Y - 1 - raio;
    } else if (sorteio == 3) {
	*borda1 = rand() % OC_SIZE_X;
	*borda2 = 0 + raio;
    }
}

/*sorteia um vetor velocidade com distribuicao ????uniforme?????*/
void sorteiaVelocidade(float *vx, float *vy)
{
    int sorteio;
    float dir, vel = VELMAX + 1;
    sorteio = rand() % 8;
    if (sorteio == 0)
	dir = NORTE;
    else if (sorteio == 1)
	dir = NORDESTE;
    else if (sorteio == 2)
	dir = LESTE;
    else if (sorteio == 3)
	dir = SUDESTE;
    else if (sorteio == 4)
	dir = SUL;
    else if (sorteio == 5)
	dir = SUDOESTE;
    else if (sorteio == 6)
	dir = OESTE;
    else if (sorteio == 7)
	dir = NOROESTE;
    while (vel > VELMAX)
	vel = gauss();
    if (vel < 0)
	vel = -vel;
    polarParaEuclidiano(dir, vel, vx, vy);
    limiteVelocidade(vx, vy);
}

/*devolve o numero de naufragos criados apartir do primeiro instante do jogo
  Nao leva em consideracao os naufragos criados antes da primeira iteracao*/
int numNaufragosNovos(void)
{
    return naufragosNovos;
}

/*frequencia com que os naufragos sao gerados por unidade de tempo*/
void frequenciaGeracaoNaufrago(void)
{
    int chance;
    int naufragosGerados;
    if (freqGeraPassageiro < 1.0) {
	chance = (int) (freqGeraPassageiro * 100);
	if (rand() % 100 < chance) {
	    geraNaufragosBorda(1);
	    naufragosNovos++;
	}
    } else {
	naufragosGerados = (int) (freqGeraPassageiro * 2) + 0.5;
	while (naufragosGerados > 0) {
	    if (rand() % 100 < 50) {
		geraNaufragosBorda(1);
		naufragosNovos++;
	    }
	    naufragosGerados--;
	}
    }
}

/*distribuicao uniforme entre 0 e 1*/
float uniform(void)
{
    float t;
    t = (float) rand() / RAND_MAX;
    return (t);
}

/*distribuicao de gauss (obtido da internet)*/
float gauss(void)
{
    int i;
    float x, y;
    for (x = 0, i = 0; i < 12; i++) {
	x = x + uniform();
    }
    x = x - 6.0;
    y = mediaDaVelocidadeGerada + x * desvioDaVelocidadeGerada;
    return (y);
}

/*define a frequencia de passageiros*/
void setFreqGeraPassageiro(float freq)
{
    freqGeraPassageiro = freq;
}

/*define a media e o desvio padrao da distribuicao usada para gerar o vetor velocidade*/
void setMediaDaVelocidadeGerada(float media, float desvio)
{
    mediaDaVelocidadeGerada = media;
    desvioDaVelocidadeGerada = desvio;
}
