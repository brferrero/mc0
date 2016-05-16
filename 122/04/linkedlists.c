/* ****************************** */
/* Bruno Ferrero    n.USP 3690142 */
/* MAC0122          26/11/2009    */
/* EP4                            */
/* Compilador: gcc version 4.0.1  */
/* ****************************** */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct aluno Aluno;
typedef struct disciplina Disciplina;
typedef struct aluno_disciplina Aluno_Disciplina;
typedef struct aluno_disciplina *pAluno_Disciplina;

struct aluno_disciplina {
    int ind_aluno;
    int ind_disc;
    pAluno_Disciplina prox_aluno;
    pAluno_Disciplina prox_disc;
};

struct aluno {
    int               nusp;
    char              nome[64];
    pAluno_Disciplina inicio; /* apontador para lista de disciplinas*/
};

struct disciplina {
    char              sigla[8];
    char              nome[64];
    pAluno_Disciplina inicio; /* apontador para lista de alunos*/
};

/*vetores*/
Aluno *vet_a;      /* vetor de alunos; esta ordenado pelo nusp */
Disciplina *vet_d; /* vetor de de disciplinas; está ordenado pela sigla */

/*funcoes*/
void *mallocX (unsigned int nbytes); /* /~pf */
/* busca binaria*/
int busca_bin (Aluno v[], int n, int x);
int busca_bin2 (Disciplina v[], int n, char x[8]);
/*insercao*/
int insere_aluno (pAluno_Disciplina *lista, Aluno_Disciplina x);
int insere_disc (pAluno_Disciplina *lista, Aluno_Disciplina x);
/*remocao*/
int remova (pAluno_Disciplina *lista, Aluno_Disciplina x);
int remova_d (pAluno_Disciplina *lista, Aluno_Disciplina x);

void imprime_lista (Aluno lista, FILE *arq);
void imprime_listad (Disciplina lista, FILE *arq);

int main (int argc, char *argv[])
{
    FILE *fp_a; /* arquivo de alunos */
    FILE *fp_d; /* arquivo de disciplinas */
    FILE *fp_i; /* arquivo de instrucoes */
    FILE *fp_s; /* aquivo de saida */

    int n_alunos, n_disc, n_inst;
    int i, k, l;
    int aluno;
    char aux[8];
    char letra;
    Aluno_Disciplina alu_disc;

    /* verificando entradas */
    if (argc < 5)
    {
	fprintf (stdout, 
		"Uso: %s <arq_alunos> <arq_disc> <arq_instr>  <arq_saida>\n", argv[0]);
	return -1;
    }

    if ((fp_a = fopen(argv[1],"r")) == NULL)
    {
	fprintf(stderr,
		"%s: arquivo de alunos %s nao pode ser aberto.\n",
		argv[0], argv[1]);
	return -1;
    }

    if ((fp_d = fopen(argv[2],"r")) == NULL)
    {
	fprintf(stderr,
		"%s: arquivo de disciplinas %s nao pode ser aberto.\n",
		argv[0], argv[2]);
	return -1;
    }

    if ((fp_i = fopen(argv[3],"r")) == NULL)
    {
	fprintf (stderr, 
		"%s: arquivo de instrucoes %s nao pode ser aberto.\n", argv[0], argv[3]);
	return -1;
    }

    if ((fp_s = fopen(argv[4],"w")) == NULL)
    {
	fprintf (stderr, 
		"%s: arquivo de saida %s nao pode ser aberto.\n", argv[0], argv[4]);
	return -1;
    }
    /*le arquivos*/
    fscanf (fp_a, "%d", &n_alunos);
    fscanf (fp_d, "%d", &n_disc);
    fscanf (fp_i, "%d", &n_inst);
    /*fprintf (fp_s, "%d alunos; %d disciplinas; %d instrucoes\n", n_alunos, n_disc, n_inst);*/

    /* constroi vetor vet_a */
    vet_a = mallocX ((n_alunos)*sizeof(Aluno));
    for (i = 0; i < n_alunos; i++) 
	fscanf (fp_a, "%d %[^\n]", &vet_a[i].nusp, vet_a[i].nome);

    /* constroi vetor vet_d */
    vet_d = mallocX ((n_disc)*sizeof(Disciplina));
    for (i = 0; i < n_disc; i++) 
	fscanf (fp_d, " %s %[^\n]", vet_d[i].sigla, vet_d[i].nome);

    /* instrucoes */
    k = 0;
    l = n_inst;
    while (k < l) {
	fscanf (fp_i, "%c", &letra);
	switch (letra) {
	    /*MATRICULA*/
	    case 'M': fscanf (fp_i, "%d %[^\n]", &aluno, aux);
		      fprintf (fp_s, "%c %d %s\n", letra, aluno,aux);
		      k++;
		      alu_disc.ind_aluno = busca_bin (vet_a, n_alunos, aluno);
		      if (alu_disc.ind_aluno == -1) { 
			  fprintf (fp_s,"     Aluno de no. USP %d nao encontrado.\n\n",aluno);
			  break;
		      }
		      alu_disc.ind_disc = busca_bin2 (vet_d, n_disc, aux);
		      if (alu_disc.ind_disc == -1) {
			  fprintf (fp_s,"     Disciplina %s nao encontrada.\n\n",aux);
			  break;
		      }
		      insere_disc (&vet_a[alu_disc.ind_aluno].inicio, alu_disc);
		      if (insere_aluno (&vet_d[alu_disc.ind_disc].inicio,alu_disc))
			  fprintf (fp_s,"     Aluno de no. USP %d foi matriculado em %s. \n\n",
				  vet_a[alu_disc.ind_aluno].nusp, vet_d[alu_disc.ind_disc].sigla);
		      else fprintf (fp_s, "     Aluno de no. USP %d ja' esta matriculado em %s.\n\n", 
			      aluno, vet_d[alu_disc.ind_disc].sigla);
		      break;
	    /*CANCELA*/
	    case 'C': fscanf (fp_i, "%d %[^\n]", &aluno, aux);
		      fprintf (fp_s,"%c %d %s\n", letra, aluno,aux);
		      k++;
		      alu_disc.ind_aluno = busca_bin (vet_a, n_alunos, aluno);
		      if (alu_disc.ind_aluno == -1) {
			  fprintf (fp_s,"     Aluno de no. USP %d nao encontrado.\n\n",aluno);
			  break;
		      }
		      alu_disc.ind_disc = busca_bin2 (vet_d, n_disc, aux);
		      if (alu_disc.ind_disc == -1) {
			  fprintf (fp_s,"     Disciplina %s nao encontrada.\n\n",aux);
			  break;
		      }
		      remova_d(&vet_a[alu_disc.ind_aluno].inicio, alu_disc);
		      if (remova (&vet_d[alu_disc.ind_disc].inicio, alu_disc)) {
			  fprintf (fp_s,"     Matricula do aluno de no. USP %d na disciplina %s foi cancelada. \n\n",
				  vet_a[alu_disc.ind_aluno].nusp, vet_d[alu_disc.ind_disc].sigla);
		      }
		      else  fprintf (fp_s,"     O aluno de no. USP %d nao esta matriculado em %s. \n\n",
			      vet_a[alu_disc.ind_aluno].nusp, vet_d[alu_disc.ind_disc].sigla);
		      break;
	    /*IMPRIME LISTA DE DISCIPLINAS DE A*/
	    case 'A': fscanf (fp_i, " %[^\n]", aux);
		      fprintf (fp_s, "%c %s\n", letra, aux);
		      k++;
		      i = busca_bin2 (vet_d, n_disc, aux);
		      if (i == -1) {
			  fprintf (fp_s,"     Disciplina %s nao encontrada.\n\n",aux);
			  break;
		      }
		      imprime_listad (vet_d[i], fp_s);
		      fprintf(fp_s,"\n");
		      break;
	    /*IMPRIME LISTA DE ALUNOS DE D*/
	    case 'D': fscanf (fp_i, " %d", &aluno);
		      fprintf (fp_s,"%c %d\n", letra, aluno);
		      k++;
		      i = busca_bin (vet_a, n_alunos, aluno);
		      if (i == -1) {
			  fprintf (fp_s,"     Aluno de no. USP %d nao encontrado.\n\n",aluno);
			  break;
		      }
		      imprime_lista (vet_a[i], fp_s);
		      fprintf(fp_s,"\n");
		      break;
	}
    }

    /* libera */
    free(vet_a);
    free(vet_d);
    fclose (fp_a);
    fclose (fp_d);
    fclose (fp_i);
    fclose (fp_s);
    return 0;
}

/*FUNCOES*/

/* ~pf */
void *mallocX (unsigned int nbytes) 
{
    void *ptr;
    ptr = malloc (nbytes);
    if (ptr == NULL) {
	printf ("Socorro! malloc devolveu NULL!\n");
	exit (EXIT_FAILURE);
    }
    return ptr;
}

/* busca um nusp no vetor Aluno */
int busca_bin (Aluno v[], int n, int x)
{
    int ini, fim, meio;
    ini = 0;
    fim = n-1;
    meio = (n-1)/2;
    while (ini <= fim && v[meio].nusp != x) {
	if (v[meio].nusp < x)
	    ini = meio + 1;
	else
	    fim = meio - 1;
	meio = (ini+fim)/2;
    }
    if (ini <= fim)
	return meio;
    if (v[ini].nusp == x)
	return ini;
    else return -1; /*nao achou*/
}

/* busca uma sigla no vetor Aluno */
/* utiliza a funcao strcmp para comparar "tamanho" de strings */
int busca_bin2 (Disciplina v[], int n, char x[8])
{
    int ini, fim, meio;
    ini = 0;
    fim = n-1;
    meio = (n-1)/2;
    while (ini <= fim && strncmp (v[meio].sigla, x,8) != 0) {
	if (strncmp (v[meio].sigla, x,8) < 0)
	    ini = meio + 1;
	else
	    fim = meio - 1;
	meio = (ini+fim)/2;
    }
    if (ini <= fim)
	return meio;
    if (strncmp (v[ini].sigla, x,8) == 0)
	return ini;
    else return -1; /*nao achou*/
}

/* insere na ordem correta um Aluno_Disciplina na lista */
int insere_aluno (pAluno_Disciplina *lista, Aluno_Disciplina x)
{   /* inicio -> prox_aluno */
    pAluno_Disciplina nova;
    pAluno_Disciplina p, ant;
    char aux_1[64];
    char aux_2[64];
    int i, j;
    p = *lista;
    ant = NULL;
    nova = mallocX (sizeof (Aluno_Disciplina));
    nova->ind_aluno = x.ind_aluno;
    nova->ind_disc = x.ind_disc;
    if (p == NULL) { 
	*lista = nova;
	return 1;
    }
    else {
	i = x.ind_aluno;
	strcpy (aux_1,vet_a[i].nome);
	for(i = 0; aux_1[i] != '\0'; i++)
	    aux_1[i] = toupper(aux_1[i]);     /*para maiusculas*/
	/*conteudo*/
	while (p != NULL) {
	    j = p->ind_aluno;
	    strcpy (aux_2,vet_a[j].nome);
	    for(i = 0; aux_2[i] != '\0'; i++)
		aux_2[i] = toupper(aux_2[i]); /*para maiusculas*/
	    if (strcmp (aux_1,aux_2) == 0)    /*agora as strings estao em caixa alta*/
		return 0;
	    if (strcmp (aux_1,aux_2) < 0)     
		break;                        /*fora de ordem, ordene*/
	    ant = p;
	    p = p->prox_aluno;
	}
	nova->prox_aluno = p;
	if (ant == NULL)
	    *lista = nova;
	else 
	    ant->prox_aluno = nova;
	return 1;
    }
}

int insere_disc (pAluno_Disciplina *lista, Aluno_Disciplina x)
{   /* inicio -> prox_disc */
    pAluno_Disciplina nova;
    pAluno_Disciplina p, ant;
    int i, j;
    p = *lista;
    ant = NULL;
    nova = mallocX (sizeof (Aluno_Disciplina));
    nova->ind_aluno = x.ind_aluno;
    nova->ind_disc = x.ind_disc;
    if (p == NULL) { 
	*lista = nova;
	return 1;
    }
    else {
	i = x.ind_disc;
	/*conteudo*/
	while (p != NULL) {
	    j = p->ind_disc;
	    if (i == j)
		return 0;
	    if (i < j) 
		break;
	    ant = p;
	    p = p->prox_disc;
	}
	nova->prox_disc = p;
	if (ant == NULL)
	    *lista = nova;
	else 
	    ant->prox_disc = nova;
	return 1;
    }
}

/* remove aluno */
int remova (pAluno_Disciplina *lista, Aluno_Disciplina x)
{
    pAluno_Disciplina ant, atual, aux;
    ant = NULL;
    atual = *lista;
    while (atual != NULL && atual->ind_aluno != x.ind_aluno) {
	ant = atual;
	atual = atual->prox_aluno;
    }
    if (atual == NULL) {
	return 0;
    }
    else {
	if (ant == NULL) {
	    aux = atual->prox_aluno;
	    free(atual);
	    *lista = aux;
	}
	else {
	    ant->prox_aluno = atual->prox_aluno;
	    free (atual);
	}
	return 1;
    }
}
/* remove disciplina */
int remova_d (pAluno_Disciplina *lista, Aluno_Disciplina x)
{
    pAluno_Disciplina ant, atual, aux;
    ant = NULL;
    atual = *lista;
    while (atual != NULL && atual->ind_disc != x.ind_disc) {
	ant = atual;
	atual = atual->prox_disc;
    }
    if (atual == NULL) {
	return 0;
    }
    else {
	if (ant == NULL) {
	    aux = atual->prox_disc;
	    free(atual);
	    *lista = aux;
	}
	else {
	    ant->prox_disc = atual->prox_disc;
	    free (atual);
	}
	return 1;
    }
}

/*lista de disciplinas*/
void imprime_lista (Aluno lista, FILE *arq)
{
    int i;
    if (lista.inicio == NULL )
	fprintf (arq, "      Aluno nao esta matricula em disciplina alguma.\n");
    else
	while (lista.inicio != NULL) {
	    i = lista.inicio->ind_disc;
	    fprintf (arq, "     %s %s\n", vet_d[i].sigla, vet_d[i].nome);
	    lista.inicio = lista.inicio->prox_disc;
	}
}

/*lista de alunos*/
void imprime_listad (Disciplina lista, FILE *arq)
{
    int i;
    if (lista.inicio == NULL )
	fprintf (arq, "      Nao ha aluno matriculado.\n");
    else
	while (lista.inicio != NULL) {
	    i = lista.inicio->ind_aluno;
	    fprintf (arq, "      %d %s\n",vet_a[i].nusp, vet_a[i].nome);
	    lista.inicio = lista.inicio->prox_aluno;
	}
}
