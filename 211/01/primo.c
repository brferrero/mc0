/****************************************************************
*
* Curso: BCC                                 Disciplina: MAC 211
* Data : 30/03/2010                          Exercic. Programa 1
* Compilador utilizado : gcc versao (Debian 4.3.2-1.1)
*
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>

int filtra_os_primos (unsigned short int p, unsigned short int r, char * nome_arquivo_entrada, char * nome_arquivo_saida);

int main (int argc, char *argv[]) 
{
    unsigned short int p, r;
    
    if (argc != 5) {
        printf ("Uso: %s <p> <r> <arq_in> <arq_saida>\n",argv[0]);
        exit (1);
    }
    p = atoi(argv[1]);
    r = atoi (argv[2]);
    printf ("Foram encontrados %d primos.\n", filtra_os_primos (p, r, argv[3],argv[4]));
    return 0;

}

int filtra_os_primos (unsigned short int p, unsigned short int r, char * nome_arquivo_entrada, char * nome_arquivo_saida) {

    FILE *arq;
    FILE *arqout;
    unsigned short int n;       
    int divisor; 
    int eprimo; 
    int cont = 0;
   
    arq = fopen(nome_arquivo_entrada,"r");
    arqout = fopen (nome_arquivo_saida, "w");

    while (!feof(arq)) {
        fscanf (arq,"%hu ",&n);
        if (n >= p && n <= r) {
            if (n <= 1 || (n != 2 && n % 2 == 0))
                eprimo = 0; 
            else 
                eprimo = 1; 
            for (divisor = 3; divisor <= n/2 && eprimo; divisor += 2)
                if (n % divisor == 0) 
                    eprimo = 0; 
            if (eprimo) {
                fprintf(arqout,"%hu ",n);
                cont++;
            }
        }
    }
    fclose(arq);
    fclose(arqout);
    return cont;
}
