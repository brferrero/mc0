/*********************************************************************
 *  Curso: BCC                                 Disciplina: MAC 211
 *  Data : 2/6/2010                       Exercic. Projeto(parte 2)
 *  Compilador utilizado : gcc versao 4.1.2
 *  ******************************************************************/

/*#define DEBUG_COLISAO 1*/

void inicializaEstruturaColisao(void);
void atualizaEstruturaColisao(void);
int existeColisao(int *indice1, int *indice2);
void trataColisao(int indice1, int indice2);
void getElCol(int index, float *posx, float *posy, float *raio);
void setElCol(int index, float posx, float posy, float raio);
