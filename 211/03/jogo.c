/*********************************************************************
 *  Curso: BCC                                 Disciplina: MAC 211
 *  Data : 2/6/2010                       Exercic. Projeto(parte 2)
 *  Compilador utilizado : gcc versao 4.1.2
 *  ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#include <sys/time.h>
#include "item.h"
#include "fisica.h"
#include "oceano.h"
#include "grafico.h"
#include "colisao.h"

void estatisticaVelocidade(float velMediaEsperada);

int main(int argc, char *argv[])
{
    float freq, velMedia;
    struct timespec requisitado;
    struct timeval start_time;
    struct timeval stop_time;
    long int timeLoop;

    int semente;

    BITMAP *buffer = NULL;
    BITMAP *oceano = NULL;

    /*argumentos de entrada */
    if (argc == 2) {
	freq = atof(argv[1]);
	velMedia = 1;
	srand(time(NULL));
    } else if (argc == 3) {
	freq = atof(argv[1]);
	velMedia = atof(argv[2]);
	srand(time(NULL));
    } else if (argc == 4) {
	freq = atof(argv[1]);
	velMedia = atof(argv[2]);
	semente = atoi(argv[3]);
	srand(semente);
    }
    /*parametros default */
    else {
	freq = 0.5;
	velMedia = 3;
	srand(20);
    }

    setFreqGeraPassageiro(freq);
    setMediaDaVelocidadeGerada(velMedia, 0.5);

    allegro_init();

    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, OC_SIZE_X, OC_SIZE_Y, 0, 0);
    buffer = create_bitmap(OC_SIZE_X, OC_SIZE_Y);

    /*oceano = load_bitmap("oceano_azul.bmp", NULL);  le a imagem do oceano */
    oceano = create_bitmap(OC_SIZE_X, OC_SIZE_Y);
    clear_to_color(oceano, makecol(0, 0, 128));

    limpaOceano(oceano, buffer);

    inicializaVetorNaufragos();
    inicializaBotes();
    naufragioAsimov();		/*coloca o naufragio em alguma posicao da tela */
    populaCorais(30);
    populaNaufragos(30);
    criaBotes();
    inicializaEstruturaColisao();

    desenhaAsimov(buffer);
    desenhaCorais(buffer);
    desenhaNaufragos(buffer);
    desenhaBotes(buffer);
    desenhaOceano(buffer, screen);
    incrementaTempo(1);

    requisitado.tv_sec = 0;

    while (numNaufragosNoVetor() > 0) {
	gettimeofday(&start_time, NULL);
	calculaProximoEstadoParticulas();
	iteracaoParaProximoPasso();
	limpaOceano(oceano, buffer);
	desenhaAsimov(buffer);
	desenhaCorais(buffer);
	desenhaNaufragos(buffer);
	desenhaBotes(buffer);
	desenhaOceano(buffer, screen);
	frequenciaGeracaoNaufrago();
	incrementaTempo(1);
	gettimeofday(&stop_time, NULL);
	timeLoop = (stop_time.tv_usec - start_time.tv_usec);
	timeLoop *= 1000;
	requisitado.tv_nsec = 100000000;	/*10 quadros por segundo */
	requisitado.tv_nsec -= timeLoop;
	nanosleep(&requisitado, NULL);
    }
    destroy_bitmap(buffer);
    destroy_bitmap(oceano);
    readkey();
    return 0;
}

END_OF_MAIN()

/*lista parametros pedidos para teste*/
void estatisticaVelocidade(float velMediaEsperada)
{
    float posx, posy, vx, vy, max, min, vel, dir, soma;
    int naufragos;
    naufrago *next, *primeiro;
    naufragos = 0;
    soma = 0;
    max = 0;
    min = 1.4;

    primeiro = nextNaufrago();
    next = primeiro;
    do {
	getNaufragoPosVel(next, &posx, &posy, &vx, &vy);
	euclidianoParaPolar(vx, vy, &dir, &vel);
	if (vel > max)
	    max = vel;
	if (vel < min)
	    min = vel;
	soma += vel;
	naufragos++;
	next = nextNaufrago();
    } while (next != primeiro && next != NULL);
    printf
	("Velocida maxima = %g, minima = %g, media = %g, media esperada = %g\n",
	 max, min, soma / (float) naufragos, velMediaEsperada);
}
