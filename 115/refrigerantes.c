/* ******************************************** */
/* Bruno Ferrero                     3690142    */
/* Oceanografia                Data  08/2006    */
/* MAC_115 Intrducao_a_Computacao               */
/* Exercico_Programa numero 1                   */
/* ******************************************** */

/*             MAQUINA AUTOMATICA DE REFRIGERANTE                       */
/* Recebe moedas de 50, 5 e 1 e devolve troco com menor numero possivel */
/* de moedas e devolve troco com menor numero possivel de moedas        */

#include <stdio.h>
int main ()
{
  int pagamento,   /* valor do pagamento (cada moeda)                    */ 
    pag_total,     /* pagamento total                                    */
    refri_maquina, /* numero de refrigerantes na maquina                 */
    n50 ,n5, n1,   /* n. de moedas para cada valor disponivel na maquina */
    n50_usr,n5_usr,n1_usr, /*n. de moedas de cada valor inserida         */
    n50_tro,n5_tro,n1_tro, /*n. de moedas de cada valor para o troco     */
    total_caixa,   /* valor total no caixa                               */
    preco,         /* preco de cada refrigerante                         */
    valor_compra,  /* preco a ser pago pela compra                       */
    troco,         /* valor de troco a ser recebido                      */
    n_refri;       /* numero de refrigerantes a serem comprados          */
  
  /* entrada dos valores iniciais da maquina */ 

  printf("Entre com numero de moedas de 50 centavos do caixa : ");
  scanf("%d",&n50);
  printf("Entre com numero de moedas de 5 centavos do caixa  : ");
  scanf("%d",&n5);
  printf("Entre com numero de moedas de 1 centavo do caixa   : ");
  scanf("%d",&n1);
  total_caixa = (n50*50) + (n5*5) + n1;
  printf("Entre com a quantidade de refrigerantes a venda : ");
  scanf("%d",&refri_maquina);
  printf("Entre com o preco de cada refrigerante : ");
  scanf("%d",&preco);

  printf("\n Situacao inicial da maquina \n\n"
	 " Quantidade de moedas no caixa : \n"
	 "   50 centavos : _%d_ \n"
	 "    5 centavos : _%d_ \n"
	 "    1 centavo  : _%d_ \n"
	 " Valor total no caixa : %d centavos\n"
	 " Quantidade de refrigerantes a venda : _%d_ \n"
	 " Preco de cada refrigerante : _%d_ \n\n"
	 ,n50, n5, n1, total_caixa, refri_maquina, preco);
  
  printf("Entre com o numero (<= 9) de refrigerantes a ser comprado : ");
  scanf("%d",&n_refri);
  
  /* testa se ha refrigerantes suficiente na maquina para efetuar a venda*/
  /* caso nao haja refrigerantes suficiente, termina o pedido!           */
  if (n_refri <= refri_maquina && n_refri <= 9)  {
         
    valor_compra = n_refri*preco;
    printf("Valor a pagar : %d \n", valor_compra);
 
    n50_usr = 0;
    n5_usr = 0;
    n1_usr = 0;
    pag_total = 0;
    n50_tro = 0;
    n5_tro = 0;
    n1_tro = 0;

    /* recebe as moedas inseridas pelo usuario e armazena nas respectivas*/   
    /* variaveis                                                         */
    printf("Entre com moedas de valores 50, 5 e 1 seguidos por 0: ");
    scanf("%d",&pagamento);
    while (pagamento != 0)  {
      if (pagamento == 50)  {
	n50_usr = n50_usr + 1;
      }
      if (pagamento == 5)  {
	n5_usr = n5_usr + 1;
      }
      if (pagamento == 1)  {
	n1_usr = n1_usr + 1;
      }
      scanf("%d",&pagamento);
    }

    pag_total = (n50_usr*50) + (n5_usr*5) + (n1_usr);

    /* verifica se as moedas inseridas sao suficientes para o pagamento  */
    /* caso na seja suficiente, termina o programa!                      */
    if (pag_total >= valor_compra)  {
      /* atualiza a maquina */
      n50 = n50 + n50_usr;
      n5 = n5 + n5_usr;
      n1 = n1 + n1_usr;
      troco = pag_total - valor_compra;

      total_caixa = (n50*50) + (n5*5) + n1 - troco;
      refri_maquina = refri_maquina - n_refri;
  
      printf("Quantidade de moedas fornecidas pelo usuario : \n"
	     " 50 centavos : %d \n"
	     " 5 centavos  : %d \n"
	     " 1 centavo   : %d \n"
	     "Valor total pago pelo usuario : %d centavos\n"
	     "Valor do troco : %d centavos \n"
	     ,n50_usr, n5_usr, n1_usr,pag_total, troco);

      /* verifica se ha um numero suficiente de moedas de 50 */ 
      if (n50 > 0) {
	if (troco/50 >= n50)  {
	  n50_tro = n50;
	  troco = troco - (n50*50);
	  n50 = 0;
	}
	else  {
	  n50 = n50 - troco/50;
	  n50_tro = troco/50;
	  troco = troco - (troco/50)*50;
	}
      }
  
      /* verifica se ha um numero suficiente de moedas de 5 */
      if (n5 > 0) {
	if (troco/5 >= n5) {
	  n5_tro = n5; 
	  troco = troco - (n5*5);
	  n5 = 0;
	}
	else  {
	  n5 = n5 - troco/5; 
	  n5_tro = troco/5;
	  troco = troco - (troco/5)*5;
	}
      }

      /* verifica se ha um numero suficiente de moedas de 1 */
      if (n1 > 0) {
	if (troco >= n1) {
	  n1_tro = n1;
	  troco = troco - (n1);
	  n1 = 0;
	}
	else  {
	  n1 = n1 - troco;
	  n1_tro = troco;
	  troco = 0;
	}
      }

      /* nao foi possivel dar o troco */
      if (troco > 0)  {
	printf("Nao foi possivel dar o troco! \n\n"
	       "Devolve: %d moedas de 50 centavos\n"
	       "         %d moedas de 5 centavos\n"
	       "         %d moedas de 1 centavo\n",n50_usr,n5_usr,n1_usr);
      }

      /* da o troco com o menor numero de moedas possivel */
      else {
	printf("Quantidades de moedas do troco :\n"
	       "  50 centavos : %d \n"
	       "  5 centavos  : %d \n"
	       "  1 centavo   : %d \n\n", n50_tro, n5_tro, n1_tro);

	/* imprime situacao da maquina apos venda */
	printf("  Situacao da maquina depois de efetuar a venda:\n\n"
	       "Quatidade de moedas no caixa :\n"
	       "  50 centavos : %d \n"
	       "  5 centavos  : %d \n"
	       "  1 centavo   : %d \n"
	       "Valor total no caixa : %d centavos\n"
	       "Quantidade de refrigerates que restam para venda : %d \n"
	       ,n50,n5,n1,total_caixa,refri_maquina);
      }
    }
    /* valor inserido foi menor que o valor da compra */
    else printf("A venda nao pode ser efetuada, valor inserido eh inferior"
		" ao valor total da compra!!!\n\n"
		"Devolve: %d moedas de 50 centavos\n"
		"         %d moedas de 5 centavos\n"
		"         %d moedas de 1 centavo\n",n50_usr,n5_usr,n1_usr);
  }
  /* numero de refrigerantes pedido era menor do que o disponivel */
  else {
    if (n_refri > 9)  
      printf("O numero desejado eh maior do que o numero maximo (9) de "
             "refrigerantes possiveis para uma venda \n");
    else  printf("O numero de refrigerantes desejado eh maior do que o "
		 "disponivel na maquina \n");
  }
  return 0;
}
