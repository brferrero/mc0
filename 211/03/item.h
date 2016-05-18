/*********************************************************************
 *  Curso: BCC                                 Disciplina: MAC 211
 *  Data : 2/6/2010                       Exercic. Projeto(parte 2)
 *  Compilador utilizado : gcc versao 4.1.2
 *  ******************************************************************/

/*define as estruturas de dados de cada elemento do jogo*/
/*as estruturas estao modeladas como circulos, abaixo o raio de cada tipo*/
#define RAIOBOTE 16.0
#define RAIOASIMOV 22.0
#define RAIONAUFRAGO 4.0
#define CORALPQ 6.0
#define CORALMD 10.0
#define CORALGR 14.0

#define NOMEMAX 14		/*tamanho maximo do nome (string) do jogador */
#define NUMBOTES 2		/*numero de botes no jogo */
#define MAX_NAUFRAGOS 300	/*numero maximo de nafragos permitidos no jogo */
#define MAX_CORAIS 50		/*numero maximo de corais permitidos no jogo */
#define NEAREST(A) ((int) (A + 0.5f))	/*arredonda o float A para o inteiro mais proximo */

/*estruturas e variaveis*/
/*elemento particula (faz parte de objetos que possuem movimento)*/
struct node1 {
    float posx;
    float posy;
    float nextx;
    float nexty;
    float vx;
    float vy;
    float nextVx;
    float nextVy;
    float raio;
};
typedef struct node1 particula;

/*elemento que representa um naufrago*/
struct node2 {
    char livre;
    particula movimento;
};
typedef struct node2 naufrago;

/*elemento fixo (faz parte de objetos que nao possuem movimento)*/
struct node3 {
    float posx;
    float posy;
    float raio;
};
typedef struct node3 fixo;

/*elemento que representa um bote*/
struct node4 {
    char ativo;
    int naufragosSalvos;
    particula movimento;
};
typedef struct node4 bote;

/*funcoes de naufragos*/
int numNaufragosNoVetor(void);
int criaNaufrago(float posx, float posy, float vx, float vy);
void removeNaufrago(naufrago * passageiro);
void inicializaVetorNaufragos(void);
void setNaufragoPosicao(naufrago * passageiro, float posx, float posy);
void setNaufragoVelocidade(naufrago * passageiro, float vx, float vy);
void getNaufragoPosVel(naufrago * passageiro, float *posx, float *posy,
		       float *vx, float *vy);
void setNaufragoNextPosicao(naufrago * passageiro, float nextPosx,
			    float nextPosy);
void setNaufragoNextVelocidade(naufrago * passageiro, float nextVx,
			       float nextVy);
void getNaufragoNextPosVel(naufrago * passageiro, float *nextPosx,
			   float *nextPosy, float *nextVx, float *nextVy);
void getNaufragoRaio(naufrago * passageiro, float *raio);
void setNaufragoRaio(naufrago * passageiro, float raio);
naufrago *getNaufrago(int posi, int posj);
naufrago *nextNaufrago(void);
particula *getParticulaNaufrago(naufrago * passageiro);
naufrago *getNaufragoPorIndice(int i);
int naufragoEstaLivre(naufrago * p);
naufrago *getNaufragoPorIndiceDinamico(int i);
/*funcoes de coral*/
void getCoralPosicao(int index, float *posx, float *posy, float *raio);
void setCoralPosicao(int index, float posx, float posy, float raio);
int numCoraisNoVetor(void);
/*funcoes do asimov*/
void setAsimovPosicao(float posx, float posy, float raio);
void getAsimovPosicao(float *posx, float *posy, float *raio);
/*funcoes de particula*/
void setParticulaPosicao(particula * p, float posx, float posy);
void setParticulaVelocidade(particula * p, float vx, float vy);
void getParticulaPosVel(particula * p, float *posx, float *posy, float *vx,
			float *vy);
void setParticulaNextPosicao(particula * p, float nextPosx,
			     float nextPosy);
void setParticulaNextVelocidade(particula * p, float nextVx, float nextVy);
void getParticulaNextPosVel(particula * p, float *nextPosx,
			    float *nextPosy, float *nextVx, float *nextVy);
void setParticulaRaio(particula * p, float raio);
float getParticulaRaio(particula * p);
/*funcoes do bote*/
void getBotePosVel(int indice, float *posx, float *posy, float *vx,
		   float *vy);
void setBoteNextPosicao(int indice, float nextPosx, float nextPosy);
void setBoteNextVelocidade(int indice, float nextVx, float nextVy);
void getBoteNextPosVel(int indice, float *nextPosx, float *nextPosy,
		       float *nextVx, float *nextVy);
void setBotePosicao(int indice, float posx, float posy);
void setBoteVelocidade(int indice, float vx, float vy);
void getBoteRaio(int indice, float *raio);
particula *getParticulaBote(int indice);
void criaBote(int indice, float posx, float posy, float vx, float vy);
char boteEstaAtivo(int indice);
void inicializaBotes(void);
int particulaEhBote(particula * p);
