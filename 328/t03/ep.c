/*
NOME  : Bruno Ferrero 
CURSO : BCC
NUSP  : 3690142
Make 
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

	Digraph G;
	MakeFile = fopen ("MakeFile", "r");
	if (MakeFile == NULL) {
		printf ("ERRO: Arquivo MakeFile não encontrado\n");
		return 1;
	}
	/*constroi o digrafo*/
	G = DIGRAPHconstroi (MakeFile);
	fclose (MakeFile);
	MakeFileOut = fopen ("MakeFile.dg","w");
	/*imprime saida no arquivo MakeFile.dg*/
	DIGRAPHprint (G, MakeFileOut);
	fclose (MakeFileOut);

	/*imprime na saida padrao*/
	if (argc > 1) {    
		strncpy (flag, argv[1],2);
		/*verifica as flags*/
		if (flag[0] == '-' && flag[1] == 's')
			DIGRAPHshow (G);
	}

	return 0;
}
