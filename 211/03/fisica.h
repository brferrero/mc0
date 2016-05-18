/*********************************************************************
 *  Curso: BCC                                 Disciplina: MAC 211
 *  Data : 2/6/2010                       Exercic. Projeto(parte 2)
 *  Compilador utilizado : gcc versao 4.1.2
 *  ******************************************************************/

#define Pi 3.14159265
#define EPS 0.0000001		/*epsilon utilizado */

/*a convencao de direcao utiliza o circulo trigonometrico, NORTE = 90 graus, LESTE = 0*/
#define NORTE 90.0
#define NORDESTE 45.0
#define LESTE 0.0
#define SUDESTE 315.0
#define SUL 270.0
#define SUDOESTE 225.0
#define OESTE 180.0
#define NOROESTE 135.0
#define ANGtheta 45.0		/*acrescentamos 45 graus a cada direcao */
#define VXMAX 4.0		/*velocidade maxima no eixo x */
#define VYMAX 4.0		/*velocidade maxima no eixo y */
#define VELMAX 5.656854		/*sqrt(VXMAX^2 + VYMAX^2) */

#define RAD2GRAUS(rd) ((180/(Pi))*(rd))	/*radianos para graus */
#define GRAUS2RAD(num) (((num)/180)*Pi)	/*graus para radianos */

 /*FUNCOES*/
    int sorteioMarkov(float vx, float vy, float *newVx, float *newVy);
int getTempo(void);
void calculaProximoEstadoParticulas(void);
void calculaProximaPosicaoParticula(particula * p);
void calculaProximaDirecaoParticula(particula * p);
void limiteVelocidade(float *vx, float *vy);
void transfereMomento(naufrago * passivo, naufrago * ativo);
void iteracaoParaProximoPasso(void);
void polarParaEuclidiano(float dir, float vel, float *vx, float *vy);
void euclidianoParaPolar(float vx, float vy, float *dir, float *vel);
float distanciaEuclidiana(float x1, float y1, float x2, float y2);
void incrementaTempo(int incremento);
