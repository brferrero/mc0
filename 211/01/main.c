/****************************************************************
*
* Curso: BCC                                 Disciplina: MAC 211
* Data : 30/03/2010                          Exercic. Programa 1
* Compilador utilizado : gcc versao (Debian 4.3.2-1.1)
*
*****************************************************************/

#include<stdio.h>
#include<stdlib.h>

int filtra_os_primos (unsigned short int p, unsigned short int r, char * nome_arquivo_entrada, char * nome_arquivo_saida);

int main(int argc, char * argv[]) {

	short int p; /* */
	short int r; /* */

        /*verificando os argumentos passados ao programa*/
        if(argc!=5){
                printf("Nao foram fornecidas todas as informacoes necessarias para o programa.\n");
                printf("Tente: %s p r arquivo_entrada arquivo_saida.\n", argv[0]);
                return -1;
        }
        p=atoi(argv[1]);
        r=atoi(argv[2]);

        printf("Foram encontrados %d primos.\n", filtra_os_primos (p, r, argv[3], argv[4]));
	
        /*abrindo arquivo de leitura
        if((file_out = fopen(argv[2], "w"))==NULL) {
               printf("Arquivo %s nao pode ser aberto para gravacao\n", argv[2]);
                return 1;
        }

	fprintf(file_out, "\n");
	fclose(file_out);*/
	return 0;
}

