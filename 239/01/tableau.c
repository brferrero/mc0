#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define ALFA 0
#define BETA 1
#define ATOMO 2
#define MAX 1000
#define ESQ(param) (ramo[(param)].arv->esq)
#define DIR(param) (ramo[(param)].arv->dir)
#define VAL(param) (ramo[(param)].valor)
#define SIMB(param) (ramo[(param)].arv->simbolo)
/******************************************************/
typedef struct arvore {
    char simbolo;
    struct arvore * esq;
    struct arvore * dir;
}tree;

typedef struct form_marcada {
    char valor;
    tree * arv;
}f_marc;

char buff[MAX];
f_marc ramo[MAX];
int betas[MAX];
FILE * in;
/******************************************************/
tree * monta_arvore (int comeco)
{
    tree * novo = NULL;
    int i = comeco;
    int qtos_par = 0;
    //printf("Valor do i:%d\n",i);
    while (1)
    {
        /* conta quantos parenteses existem no começo */
        while (buff[i] == '(')
        {
            i++;
            qtos_par++;
        }
        //printf("Qtos par:%d\n", qtos_par);
        /* procura o pai */
        while (qtos_par > 1)
        {
            if (buff[i] == ')')
                qtos_par--;
            i++;
        }

        /* cria no do conectivo central */
        novo = malloc (sizeof(tree));
        /* eh um atomo */
        if (buff[i] != '.' && buff[i+1] == ')')
        {
            novo->simbolo = buff[i];
            //printf("%c\n",novo->simbolo);
            novo->esq = novo->dir = NULL;
        }
        else if (buff[i] != '.' && buff[i+1] == '.') 
        {
            novo->simbolo = buff[i+2];
            //printf("%c\n",novo->simbolo);
            novo->esq = malloc(sizeof(tree));
            novo->dir = malloc(sizeof(tree));
            novo->esq->simbolo = buff[i];
            novo->dir->simbolo = buff[i+4];
            //printf("%c\n",novo->esq->simbolo);
            //printf("%c\n",novo->dir->simbolo);
        }
        /* caso nao seja um atomo */
        else
        {
            i++;
            novo->simbolo = buff[i];
            //printf("%c\n",novo->simbolo);
            if (buff[i] == 'N')
                novo->esq = novo->dir = monta_arvore(i + 2);
            else
            {
                novo->esq = monta_arvore(comeco + 1);
                novo->dir = monta_arvore(i + 2);
            }
        }
        return novo;
    }
}
/******************************************************/
void print_beta (int tam)
{
    int i;
    for (i = 0; i < tam; i++)
        printf (" .%d. ",betas[i]);
    printf ("\n");
}
/******************************************************/
void checa_beta (int valor, char conectivo, int indice)
{
    if ((valor == TRUE && (conectivo == 'O' || conectivo == 'I')) || (valor == FALSE && conectivo == 'A'))
        betas[indice] = BETA;
    if (conectivo >= 'a' && conectivo <= 'z')
        betas[indice] = ATOMO;
}
/******************************************************/
int acha_proximo_seq (int seq_atual)
{
    while (buff[seq_atual] != ',' && buff[seq_atual] != '\0')
        seq_atual++;
    if (buff[seq_atual] == ',')
        return seq_atual+1;
    return -1;
}
/******************************************************/
int expande_alfa (int size, int posicao)
{
    switch (ramo[posicao].arv->simbolo)
    {
        case 'N':
            ramo[size].arv = ESQ(posicao);
            ramo[size].valor = (VAL(posicao) + 1)%2;
            checa_beta(VAL(size), SIMB(size), size);
            size++;
            break;
        case 'A':
            ramo[size].arv = ESQ(posicao);
            ramo[size].valor = TRUE;
            checa_beta(VAL(size), SIMB(size), size);
            size++;
            ramo[size].arv = DIR(posicao);
            ramo[size].valor = TRUE;
            checa_beta(VAL(size), SIMB(size), size);
            size++;
            break;
        case 'O':
            ramo[size].arv = ESQ(posicao);
            ramo[size].valor = FALSE;
            checa_beta(VAL(size), SIMB(size), size);
            size++;
            ramo[size].arv = DIR(posicao);
            ramo[size].valor = FALSE;
            checa_beta(VAL(size), SIMB(size), size);
            size++;
            break;
        case 'I':
            ramo[size].arv = ESQ(posicao);
            ramo[size].valor = TRUE;
            checa_beta(VAL(size), SIMB(size), size);
            size++;
            ramo[size].arv = DIR(posicao);
            ramo[size].valor = FALSE;
            checa_beta(VAL(size), SIMB(size), size);
            size++;
            break;
        default: break;
    }
    return size;
}
/******************************************************/
void resolve (int size)
{
    int i;
    while (1)
    {
        for (i = 0; i < size; i++)
        {
            /* eh uma aravore alfa */
            if (betas[i] == ALFA)
            {
                printf("SIZE ANTES:%d i: %d\n",size, i);
                size = expande_alfa(size, i);
                printf("SIZE DEPOIS:%d\n",size);
                printf("SIMB: %c ", SIMB(size - 1));
                printf("VALUE: %d\n",VAL(size - 1));
                print_beta(size);
                printf("==================\n");
            }
        }
        break;
    }
}
/******************************************************/
int main()
{
    tree * sequente = NULL;
    int seq_atual, i, ramo_qtd = 0;

    in = fopen("teste-tableau.txt", "r");
    /* pega a primeira linha (consequentes), monta as arvores e atribui valor TRUE.
       pega a segunda linha (consequencia), monta as arvores e atribui valor FALSE */
    for (i = 0; i < 2; i++)
    {
        seq_atual = 0;
        fgets (buff, MAX, in);
        printf ("%s\n",buff);

        while (seq_atual != -1)
        {
            betas[ramo_qtd] = FALSE;
            sequente = monta_arvore(seq_atual);
            ramo[ramo_qtd].arv = sequente;
            if (i == 0)
                ramo[ramo_qtd].valor = TRUE;
            if (i == 1)
                ramo[ramo_qtd].valor = FALSE;
            sequente = NULL;
            checa_beta (ramo[ramo_qtd].valor, ramo[ramo_qtd].arv->simbolo, ramo_qtd);
            seq_atual = acha_proximo_seq(seq_atual);
            ramo_qtd++;
            //printf("Valor do ramo acima:%d\tRAIZ:%c\n",ramo[ramo_qtd - 1].valor, ramo[ramo_qtd - 1].arv->simbolo);
            //printf("===============\n");
        }
    }
    resolve (ramo_qtd);
    print_beta (ramo_qtd);
    return 0;
}
/******************************************************/
