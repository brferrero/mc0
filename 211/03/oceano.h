/*********************************************************************
 *  Curso: BCC                                 Disciplina: MAC 211
 *  Data : 2/6/2010                       Exercic. Projeto(parte 2)
 *  Compilador utilizado : gcc versao 4.1.2
 *  ******************************************************************/

#define OC_SIZE_X 1024
#define OC_SIZE_Y 768

 /*FUNCOES*/ void criaBotes(void);
void getBotePontosDesenho(int indice, float *x1, float *y1, float *x2,
			  float *y2, float *x3, float *y3);
void sorteiaBordas(int *borda1, int *borda2, int raio);
void sorteiaVelocidade(float *vx, float *vy);
void populaCorais(int quantidade);
void populaNaufragos(int quantidade);
void geraNaufragosBorda(int quantidade);
void frequenciaGeracaoNaufrago();
void setFreqGeraPassageiro(float freq);
void setMediaDaVelocidadeGerada(float media, float desvio);
int numNaufragosNovos(void);
int naufragosNovo(void);
int limpaJanela(void);
float uniform(void);
float gauss(void);
int podeCriarPosicao(float posx, float posy, float raio);
float geraTamanhoCoral(void);
void naufragioAsimov(void);
