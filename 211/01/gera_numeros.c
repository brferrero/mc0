/****************************************************************
*
* Curso: BCC                                 Disciplina: MAC 211
* Data : 30/03/2010                          Exercic. Programa 1
* Compilador utilizado : gcc versao (Debian 4.3.2-1.1)
*
*****************************************************************/
#include<stdio.h>
#include<stdlib.h>
#define NUM_MAX 99
#define NUM_MIN 2

/*devolve um inteiro aletario entre min e max*/
int randint (int min, int max);

int main(int argc, char * argv[]) {

	int N; /*quantidade de numeros gerados aleatoriamente */
	unsigned short int numero_gerado;
	FILE * file_out;

        /*verificando os argumentos passados ao programa*/
        if(argc!=3){
                printf("Nao foram fornecidas todas as informacoes necessarias para o programa.\n");
                printf("Tente: %s n arquivo_saida.\n", argv[0]);
                printf("Onde n eh o numero de numeros gerados aleatoriamente.\n");
                return -1;
        }
        N=atoi(argv[1]);

        //abrindo arquivo de leitura
        if((file_out = fopen(argv[2], "w"))==NULL) {
                printf("Arquivo %s nao pode ser aberto para gravacao\n", argv[2]);
                return 1;
        }

	srand((unsigned)(time()));

	while(N>0) {
                numero_gerado=randint(NUM_MIN, NUM_MAX);  //faixa de numeros maximo possivel com 16 bits
		fprintf(file_out, "%d ", numero_gerado);
		N--;
	}
	fprintf(file_out, "\n");
	fclose(file_out);
	return 0;
}

//generates a psuedo-random integer between 0 and max
int randint (int min, int max) {
    int k;
    double d;

    d = (double) rand () / ((double) RAND_MAX + 1);
    k = d * (max - min + 1);
    return min + k;
}

