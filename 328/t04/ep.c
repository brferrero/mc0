/*
NOME  : Bruno Ferrero 
CURSO : BCC
NUSP  : 3690142
DATA  : 15/05/2011
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "VERTEX.h"
#include "DIGRAPH.h"

      
int main (int argc, char *argv[])
{
    FILE *MakeFile;
    FILE *MakeFileOut;
    char flag[2];
    int *ts;  /*ordenacao topologica*/
    Digraph G;

    MakeFile = fopen ("MakeFile", "r");

    if (MakeFile == NULL) {
        printf ("ERRO: Arquivo MakeFile não encontrado\n");
        return 1;
    }

    /*constroi o digrafo*/
    G = DIGRAPHconstroi (MakeFile);
    fclose (MakeFile);

    if (argc > 1) {    
        strncpy (flag, argv[1],2);
        /*verifica as flags*/
        if (flag[0] == '-' && flag[1] == 's') {
            MakeFileOut = fopen ("MakeFile.dg","w");
            /*imprime saida no arquivo*/
            DIGRAPHprint (G, MakeFileOut);
            /*imprime na saida padrao*/
            DIGRAPHshow (G);
            fclose (MakeFileOut);
        }
    }

    /*Verifica existencia de ciclos*/
    ts = malloc (G->V*sizeof(int));
    DIGRAPHcycle (G, ts);
    return 0;
}


