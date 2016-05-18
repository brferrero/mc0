/*********************************************************************
 *  Curso: BCC                                 Disciplina: MAC 211
 *  Data : 2/6/2010                       Exercic. Projeto(parte 2)
 *  Compilador utilizado : gcc versao 4.1.2
 *  ******************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"item.h"
#include"fisica.h"
#include"oceano.h"
#include"colisao.h"

/*
 * vetor que armazena todos os elementos que terao a colisao tratada
 */
static fixo elementosDeColisao[1 + MAX_CORAIS + NUMBOTES +
			       MAX_NAUFRAGOS + 4];
static int valorLimite1;	/* asimov esta abaixo do valorLimite1 */
static int valorLimite2;	/* valorLimite1 <= corais < valorLimite2 */
static int valorLimite3;	/* valorLimite2 <= naufragos <
				 * valorLimite3 */
static int valorLimite4;	/* valorLimite3 <= botes < valorLimite4 */
			   /*
			    * valorLimite4 <= bordas 
			    */

/*
 * essa funcao posiciona os elementos estaticos (que nao possuem
 * movimento) no vetor de tratamento de colisao deve ser chamada apenas
 * uma vez, no inicio, depois de todos os elementos terem sido
 * inicializados mas antes de iniciar o jogo loop do jogo.
 */
void inicializaEstruturaColisao(void)
{
    int i;
    float coralPosx, coralPosy, coralRaio;	/* dados do coral */
    float asimovPosx, asimovPosy, asimovRaio;	/* dados do asimov */

    /*
     * posiciona o navio asimov 
     */
    getAsimovPosicao(&asimovPosx, &asimovPosy, &asimovRaio);
    setElCol(0, asimovPosx, asimovPosy, asimovRaio);
    valorLimite1 = 1;

    /*
     * posiciona os corais 
     */
    valorLimite2 = valorLimite1;
    for (i = 1; i < numCoraisNoVetor() + 1; i++) {
	getCoralPosicao(i - 1, &coralPosx, &coralPosy, &coralRaio);
	setElCol(i, coralPosx, coralPosy, coralRaio);
	valorLimite2++;
    }
}

/*
 * essa funcao posiciona os elementos dinamicos (que nao possuem
 * movimento) no vetor de tratamento de colisao deve ser chamada todo
 * momento antes de se calcula as colisoes
 */
void atualizaEstruturaColisao(void)
{
    int i;
    float nextPosx, nextPosy, nextVx, nextVy, raio;
    naufrago *passageiro;

    /*
     * posiciona os naufragos 
     */
    valorLimite3 = valorLimite2;
    for (i = 0; i < MAX_NAUFRAGOS; i++) {
	passageiro = getNaufragoPorIndice(i);
	if (naufragoEstaLivre(passageiro))
	    continue;		/* naufrago nao inicializado no jogo */
	getNaufragoNextPosVel(passageiro, &nextPosx, &nextPosy, &nextVx,
			      &nextVy);
	getNaufragoRaio(passageiro, &raio);
	setElCol(valorLimite3, nextPosx, nextPosy, raio);
	valorLimite3++;
    }
    /*
     * posiciona os botes 
     */
    valorLimite4 = valorLimite3;
    for (i = 0; i < NUMBOTES; i++) {
	if (boteEstaAtivo(i)) {
	    getBoteNextPosVel(i, &nextPosx, &nextPosy, &nextVx, &nextVy);
	    getBoteRaio(i, &raio);
	    setElCol(valorLimite4, nextPosx, nextPosy, raio);
	    valorLimite4++;
	}
    }
}

/*
 * procura pela distancia minima entre todos os elementos do jogo se ela
 * for menor do que o raio desses elementos, entao existe colisao e essa
 * deve ser a primeira a ser tratada indice2 deve ser sempre maior doque
 * indice1
 */
int existeColisao(int *indice1, int *indice2)
{
    int i, j, aux;
    float dist;
    float posx1, posy1, raio1;
    float posx2, posy2, raio2;
    float min = 5000;

    *indice1 = -1;
    *indice2 = -1;

    for (i = 0; i < valorLimite4; i++) {
	getElCol(i, &posx1, &posy1, &raio1);
	/*
	 * verifica colisao com os elementos do vetor 
	 */
	for (j = i + 1; j < valorLimite4; j++) {
	    getElCol(j, &posx2, &posy2, &raio2);
	    dist = distanciaEuclidiana(posx1, posy1, posx2, posy2);
	    if (dist < min && dist < raio1 + raio2) {
		min = dist;
		*indice1 = i;
		*indice2 = j;
	    }
	}
	/*
	 * verifica colisao com as boras 
	 */
	if (fabs(posx1) < min && fabs(posx1) < raio1) {
	    min = fabs(posx1);
	    *indice1 = i;
	    *indice2 = valorLimite4;	/* borda esquerda */
	} else if (fabs((OC_SIZE_X) - posx1) < min
		   && fabs((OC_SIZE_X) - posx1) < raio1) {
	    min = fabs((OC_SIZE_X) - posx1);
	    *indice1 = i;
	    *indice2 = valorLimite4 + 1;	/* borda direita */
	}
	if (fabs(posy1) < min && fabs(posy1) < raio1) {
	    min = fabs(posy1);
	    *indice1 = i;
	    *indice2 = valorLimite4 + 2;	/* borda superior */
	} else if (fabs((OC_SIZE_Y) - posy1) < min
		   && fabs((OC_SIZE_Y) - posy1) < raio1) {
	    min = fabs((OC_SIZE_Y) - posy1);
	    *indice1 = i;
	    *indice2 = valorLimite4 + 3;	/* borda inferior */
	}
    }
    /*
     * verifica se colidiu com elemento ou com borda 
     */
    getElCol(*indice1, &posx1, &posy1, &raio1);
    if (*indice2 < valorLimite4) {
	getElCol(*indice2, &posx2, &posy2, &raio2);
    } else {
	raio2 = 0.0;
    }
    if (raio1 + raio2 > min) {
	if (*indice1 > *indice2) {
	    aux = *indice1;
	    *indice1 = *indice2;
	    *indice2 = aux;
	}
	return 1;
    }
    /*
     * nao houve colisao 
     */
    else {
	*indice1 = -1;
	*indice2 = -1;
	return 0;
    }
}

/*
 * o tratamento da colisao, se inicia pelos elementos mais proximos dentre 
 * todos os elementos que podem colidir
 */
void trataColisao(int indice1, int indice2)
{
    float vx, vy, posx, posy;	/* elemento que esta testando a colisao */
    float nextVx, nextVy, nextPosx, nextPosy;
    float raio;
    float coralPosx, coralPosy, coralRaio;	/* dados do coral */
    float asimovPosx, asimovPosy, asimovRaio;	/* dados do asimov */
    naufrago *next, *passageiro;
    float posx2, posy2, vx2, vy2;	/* dados de outro elemento */
    float nextVx2, nextVy2, nextPosx2, nextPosy2;
    float raio2;
    int indiceBote, indiceBote2;
    int borda1, borda2;

    /*
     * colisao de naufrago com... 
     */
    if (indice2 >= valorLimite2 && indice2 < valorLimite3) {
	passageiro = getNaufragoPorIndiceDinamico(indice2 - valorLimite2);
	getNaufragoNextPosVel(passageiro, &nextPosx, &nextPosy, &nextVx,
			      &nextVy);
	getNaufragoPosVel(passageiro, &posx, &posy, &vx, &vy);
	getNaufragoRaio(passageiro, &raio);

	/*
	 * asimov 
	 */
	if (indice1 < valorLimite1) {
	    getAsimovPosicao(&asimovPosx, &asimovPosy, &asimovRaio);
#ifdef DEBUG_COLISAO
	    printf("colidiu naufrago com asimov (%g, %g), tempo=%d\n",
		   nextPosx, nextPosy, getTempo());
#endif
	    /*
	     * trata colisao com asimov 
	     */
	    setNaufragoNextPosicao(passageiro, posx, posy);
	    setNaufragoNextVelocidade(passageiro, -vx, -vy);
	}
	/*
	 * coral 
	 */
	else if (indice1 >= valorLimite1 && indice1 < valorLimite2) {
	    getCoralPosicao(indice1 - valorLimite1, &coralPosx, &coralPosy,
			    &coralRaio);
#ifdef DEBUG_COLISAO
	    printf("colidiu naufrago com coral (%g, %g), tempo=%d\n",
		   nextPosx, nextPosy, getTempo());
#endif
	    /*
	     * trata colisao com coral 
	     */
	    setNaufragoNextPosicao(passageiro, posx, posy);
	    setNaufragoNextVelocidade(passageiro, -vx, -vy);
	}
	/*
	 * naufrago 
	 */
	else if (indice1 >= valorLimite2 && indice1 < valorLimite3) {
	    next = getNaufragoPorIndiceDinamico(indice1 - valorLimite2);
	    getNaufragoPosVel(next, &posx2, &posy2, &vx2, &vy2);
	    getNaufragoNextPosVel(next, &nextPosx2, &nextPosy2, &nextVx2,
				  &nextVy2);
	    getNaufragoRaio(next, &raio2);
#ifdef DEBUG_COLISAO
	    printf("colidiu naufrago com naufrago em (%g, %g), tempo=%d\n",
		   nextPosx, nextPosy, getTempo());
#endif
	    /*
	     * trata colisao com naufrago 
	     */
	    setNaufragoNextPosicao(passageiro, posx, posy);
	    setNaufragoNextVelocidade(passageiro, vx2, vy2);
	    setNaufragoNextPosicao(next, posx2, posy2);
	    setNaufragoNextVelocidade(next, vx, vy);
	}
	/*
	 * bote 
	 */
	else if (indice1 >= valorLimite3 && indice1 < valorLimite4) {
#ifdef DEBUG_COLISAO
	    printf("NUNCA DEVERIA ENTRAR AQUI!, tempo=%d\n", getTempo());
#endif
	}
	/*
	 * borda 
	 */
	else {
#ifdef DEBUG_COLISAO
	    printf("NUNCA DEVERIA ENTRAR AQUI!, tempo=%d\n", getTempo());
#endif
	}
    }
    /*
     * colisao de bote com... 
     */
    else if (indice2 >= valorLimite3 && indice2 < valorLimite4) {
	indiceBote = indice2 - valorLimite3;
	getBoteNextPosVel(indiceBote, &nextPosx, &nextPosy, &nextVx,
			  &nextVy);
	getBotePosVel(indiceBote, &posx, &posy, &vx, &vy);
	getBoteRaio(indiceBote, &raio);
	/*
	 * asimov 
	 */
	if (indice1 < valorLimite1) {
	    getAsimovPosicao(&asimovPosx, &asimovPosy, &asimovRaio);
#ifdef DEBUG_COLISAO
	    printf("colidiu bote com asimov (%g, %g), tempo=%d\n",
		   nextPosx, nextPosy, getTempo());
#endif
	    /*
	     * trata colisao com asimov 
	     */
	    setBoteNextPosicao(indiceBote, posx, posy);
	    setBoteNextVelocidade(indiceBote, -vx, -vy);
	}
	/*
	 * coral 
	 */
	else if (indice1 >= valorLimite1 && indice1 < valorLimite2) {
	    getCoralPosicao(indice1 - valorLimite1, &coralPosx, &coralPosy,
			    &coralRaio);
#ifdef DEBUG_COLISAO
	    printf("colidiu bote com coral (%g, %g), tempo=%d\n", nextPosx,
		   nextPosy, getTempo());
#endif
	    /*
	     * trata colisao com coral 
	     */
	    if (rand() % 2 == 0) {
		/*
		 * probabilidade de 50% do bote afundar 
		 */
		sorteiaBordas(&borda1, &borda2, raio);
		while (!podeCriarPosicao
		       ((float) borda1, (float) borda2, raio))
		    sorteiaBordas(&borda1, &borda2, raio);
		sorteiaVelocidade(&vx, &vy);
		setBoteNextPosicao(indiceBote, (float) borda1,
				   (float) borda2);
		setBoteNextVelocidade(indiceBote, vx, vy);
	    } else {
		/*
		 * probabilidade de 50% do bote colidir elasticamente com
		 * o coral 
		 */
		setBoteNextPosicao(indiceBote, posx, posy);
		setBoteNextVelocidade(indiceBote, -vx, -vy);

	    }
	}
	/*
	 * naufrago 
	 */
	else if (indice1 >= valorLimite2 && indice1 < valorLimite3) {
	    passageiro =
		getNaufragoPorIndiceDinamico(indice1 - valorLimite2);
	    getNaufragoPosVel(passageiro, &posx2, &posy2, &vx2, &vy2);
	    getNaufragoPosVel(passageiro, &nextPosx2, &nextPosy2, &nextVx2,
			      &nextVy2);
	    getNaufragoRaio(passageiro, &raio2);
#ifdef DEBUG_COLISAO
	    printf("colidiu bote com naufrago em (%g, %g), tempo=%d\n",
		   nextPosx, nextPosy, getTempo());
#endif
	    removeNaufrago(passageiro);
	}
	/*
	 * bote 
	 */
	else if (indice1 >= valorLimite3 && indice1 < valorLimite4) {
	    indiceBote2 = indice1 - valorLimite3;
	    getBotePosVel(indiceBote2, &posx2, &posy2, &vx2, &vy2);
	    getBoteNextPosVel(indiceBote2, &nextPosx2, &nextPosy2,
			      &nextVx2, &nextVy2);
	    getBoteRaio(indiceBote2, &raio2);
#ifdef DEBUG_COLISAO
	    printf("colidiu bote com bote (%g, %g), tempo=%d\n", nextPosx,
		   nextPosy, getTempo());
#endif
	    /*
	     * trata colisao com bote 
	     */
	    setBoteNextPosicao(indiceBote, posx, posy);
	    setBoteNextVelocidade(indiceBote, vx2, vy2);
	    setBoteNextPosicao(indiceBote2, posx2, posy2);
	    setBoteNextVelocidade(indiceBote2, vx, vy);
	}
	/*
	 * borda 
	 */
	else {
#ifdef DEBUG_COLISAO
	    printf("NUNCA DEVERIA ENTRAR AQUI222!, tempo=%d\n",
		   getTempo());
#endif
	}
    }
    /*
     * colisao de borda com... 
     */
    else if (indice2 >= valorLimite4) {
	/*
	 * naufrago 
	 */
	if (indice1 >= valorLimite2 && indice1 < valorLimite3) {
	    passageiro =
		getNaufragoPorIndiceDinamico(indice1 - valorLimite2);
	    getNaufragoNextPosVel(passageiro, &nextPosx, &nextPosy,
				  &nextVx, &nextVy);
	    getNaufragoPosVel(passageiro, &posx, &posy, &vx, &vy);
	    getNaufragoRaio(passageiro, &raio);
	    if (indice2 == valorLimite4) {
#ifdef DEBUG_COLISAO
		printf("naufrago colidiu parede esquerda, tempo=%d\n",
		       getTempo());
#endif
		setNaufragoNextPosicao(passageiro, (float) (0.0 + raio),
				       nextPosy);
		setNaufragoNextVelocidade(passageiro, -vx, nextVy);
	    } else if (indice2 == valorLimite4 + 1) {
#ifdef DEBUG_COLISAO
		printf("naufrago colidiu parede direita, tempo=%d\n",
		       getTempo());
#endif
		setNaufragoNextPosicao(passageiro,
				       (float) (OC_SIZE_X - raio),
				       nextPosy);
		setNaufragoNextVelocidade(passageiro, -vx, nextVy);
	    }
	    if (indice2 == valorLimite4 + 2) {
#ifdef DEBUG_COLISAO
		printf("naufrago colidiu parede superior, tempo=%d\n",
		       getTempo());
#endif
		setNaufragoNextPosicao(passageiro, nextPosx,
				       (float) (0.0 + raio));
		setNaufragoNextVelocidade(passageiro, nextVx, -vy);
	    } else if (indice2 == valorLimite4 + 3) {
#ifdef DEBUG_COLISAO
		printf("naufrago colidiu parede inferior, tempo=%d\n",
		       getTempo());
#endif
		setNaufragoNextPosicao(passageiro, nextPosx,
				       (float) (OC_SIZE_Y - raio));
		setNaufragoNextVelocidade(passageiro, nextVx, -vy);
	    }
	}
	/*
	 * bote 
	 */
	else if (indice1 >= valorLimite3 && indice1 < valorLimite4) {
	    indiceBote = indice1 - valorLimite3;
	    getBoteNextPosVel(indiceBote, &nextPosx, &nextPosy, &nextVx,
			      &nextVy);
	    getBotePosVel(indiceBote, &posx, &posy, &vx, &vy);
	    getBoteRaio(indiceBote, &raio);
	    if (indice2 == valorLimite4) {
#ifdef DEBUG_COLISAO
		printf("naufrago colidiu parede esquerda, tempo=%d\n",
		       getTempo());
#endif
		setBoteNextPosicao(indiceBote, (float) (0.0 + raio),
				   nextPosy);
		setBoteNextVelocidade(indiceBote, -vx, nextVy);
	    } else if (indice2 == valorLimite4 + 1) {
#ifdef DEBUG_COLISAO
		printf("naufrago colidiu parede direita, tempo=%d\n",
		       getTempo());
#endif
		setBoteNextPosicao(indiceBote, (float) (OC_SIZE_X - raio),
				   nextPosy);
		setBoteNextVelocidade(indiceBote, -vx, nextVy);
	    }
	    if (indice2 == valorLimite4 + 2) {
#ifdef DEBUG_COLISAO
		printf("naufrago colidiu parede superior, tempo=%d\n",
		       getTempo());
#endif
		setBoteNextPosicao(indiceBote, nextPosx,
				   (float) (0.0 + raio));
		setBoteNextVelocidade(indiceBote, nextVx, -vy);
	    } else if (indice2 == valorLimite4 + 3) {
#ifdef DEBUG_COLISAO
		printf("naufrago colidiu parede inferior, tempo=%d\n",
		       getTempo());
#endif
		setBoteNextPosicao(indiceBote, nextPosx,
				   (float) (OC_SIZE_Y - raio));
		setBoteNextVelocidade(indiceBote, nextVx, -vy);
	    }
	} else {
#ifdef DEBUG_COLISAO
	    printf("Erro feio!, tempo=%d\n", getTempo());
#endif
	}
    } else {
#ifdef DEBUG_COLISAO
	printf("Erro!, tempo=%d\n", getTempo());
	printf("indice1 = %d, indice2 = %d\n", indice1, indice2);
	printf
	    ("valorLimite1=%d, valorLimite2=%d, valorLimite3=%d, valorLimite4=%d\n",
	     valorLimite1, valorLimite2, valorLimite3, valorLimite4);
#endif
    }
}

/*
 * getter do elemento de colisao
 */
void getElCol(int index, float *posx, float *posy, float *raio)
{
    *posx = elementosDeColisao[index].posx;
    *posy = elementosDeColisao[index].posy;
    *raio = elementosDeColisao[index].raio;
}

/*
 * setter do elemento de colisao
 */
void setElCol(int index, float posx, float posy, float raio)
{
    elementosDeColisao[index].posx = posx;
    elementosDeColisao[index].posy = posy;
    elementosDeColisao[index].raio = raio;
}
