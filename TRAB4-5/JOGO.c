/***************************************************************************
 *  $MCI Módulo de implementação: JOGO  Módulo Jogo / Principal
 *
 *  Arquivo gerado:              JOGO.c
 *  Letras identificadoras:      JOGO
 *
 *  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
 *  Gestor:  Professor Alessandro Garcia
 *  Autores: lr, dcr, rvc
 *
 *  $HA Histórico de evolução:
 *     Versão |  Autores   |      Data     |    Observações
 *       2    | lr,dcr,rvc |  01/dez/2016  | término desenvolvimento
 *       1    | lr,dcr,rvc |  25/nov/2016  | início desenvolvimento
 *
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "PECAS.H"
#include "TABULEIRO.H"

#define RED     "\x1b[31m"
#define BLUE    "\x1b[34m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"
#define MAGENTA "\x1b[35m"

#define ln printf("\n")
#define pf(X) printf((X))
#define pcor(X) pf((X)==0?(RESET):((X)==1?(BLUE):((X)==2?(RED):((X)==3?(GREEN):((X)==4?(YELLOW):(MAGENTA))))))

/***********************************************************************
*
*  $TC Tipo de dados: JOGO Descritor dos dados dos jogadores
*
***********************************************************************/

typedef struct Jogador{

	char nome[81];
	/* Nome do Jogador */

	int cor;
	/* Cor do Jogador */

} JOGO_Jogador;

/***** Protótipo das funções encapsuladas no módulo *****/

static int JogarDado ( void );

static void DesenhaPlacar ( PEC_tpPecas * pPecas , JOGO_Jogador * vtJogadores, int num_jogadores );

static int VerificaVencedor ( PEC_tpPecas * pPecas, int num_jogadores);

/*****  Código da função principal do módulo  *****/

int main (void)
{
	int i        ;
	int dado     ;
	int cor = 0  ;
	int resposta ;
	int num_jogadores = 2;

	JOGO_Jogador vtJogadores[4] ;

	PEC_tpPecas vtPecas[16] ;
	TAB_tpLudo  pTabuleiro  ;

	PEC_CondRet PecasRetorno     ;
	TAB_CondRet TabuleiroRetorno ;

	pf("\n\n\n");
	pcor(2); pf("\t\t     ██╗ ██████╗  ██████╗  ██████╗     ██████╗ ███████╗    ██╗     ██╗   ██╗██████╗  ██████╗ \n"); pcor(0);
	pcor(2); pf("\t\t     ██║██╔═══██╗██╔════╝ ██╔═══██╗    ██╔══██╗██╔════╝    ██║     ██║   ██║██╔══██╗██╔═══██╗\n"); pcor(0);
	pcor(2); pf("\t\t     ██║██║   ██║██║  ███╗██║   ██║    ██║  ██║█████╗      ██║     ██║   ██║██║  ██║██║   ██║\n"); pcor(0);
	pcor(2); pf("\t\t██   ██║██║   ██║██║   ██║██║   ██║    ██║  ██║██╔══╝      ██║     ██║   ██║██║  ██║██║   ██║\n"); pcor(0);
	pcor(2); pf("\t\t╚█████╔╝╚██████╔╝╚██████╔╝╚██████╔╝    ██████╔╝███████╗    ███████╗╚██████╔╝██████╔╝╚██████╔╝\n"); pcor(0);
	pcor(2); pf("\t\t ╚════╝  ╚═════╝  ╚═════╝  ╚═════╝     ╚═════╝ ╚══════╝    ╚══════╝ ╚═════╝ ╚═════╝  ╚═════╝ \n"); pcor(0);
	pf("\n\n----------------------------------------------------------------------------------------------------------------------------------");
	pf("\n\n\t"); pf("Seja bem vindo a aplicacao do Jogo de Ludo que foi desenvolvido pela equipe de desenvolvimento LRDCRC. Essa aplicacao foi\n");
    pf("desenvolvida na universidade PUC-RIO em 2016.2 na disciplina INF1301. Antes de iniciarmos a partida, vamos definirmos os jogadores\n");
    pf("e as suas cores...\n\n\n");
    pf("DIGITE O NOME DO 'PRIMEIRO' JOGADOR: "); scanf(" %80[^\n]", vtJogadores[0].nome); vtJogadores[0].cor = 0;
    pf("A COR DA SUA PECA SERA ------ "); pcor(2); pf("VERMELHA "); pcor(0); pf("------"); pf("\n\n");
    pf("DIGITE O NOME DO 'SEGUNDO' JOGADOR: "); scanf(" %80[^\n]", vtJogadores[1].nome); vtJogadores[1].cor = 1;
    pf("A COR DA SUA PECA SERA ------ "); pcor(1); pf("AZUL "); pcor(0); pf("------"); pf("\n\n");
    pf(".-----------------------------------.\n");
    pf("| 1. Caso tenha mais jogadores.     |\n");
    pf("| 2.Caso 'NAO' tenha mais jogadores.|\n");
    pf(".-----------------------------------.\n");
    pf("AGORA DIGITE SUA RESPOSTA: "); scanf("%d", &resposta); pf("\n\n");
    if(resposta < 1 || resposta > 2)
    {
    	pcor(5); pf("\tNUMERO INVALIDO !!\n\n"); pcor(0);
    	pf(".-----------------------------------.\n");
    	pf("| 1. Caso tenha mais jogadores.     |\n");
    	pf("| 2.Caso 'NAO' tenha mais jogadores.|\n");
    	pf(".-----------------------------------.\n");
    	pf("AGORA DIGITE SUA RESPOSTA: "); scanf("%d", &resposta); pf("\n\n");

    	if(resposta < 1 || resposta > 2)
    	{
    		pcor(5); pf("\tNUMERO INVALIDO !! INICIAR EXECUTAVEL NOVAMENTE . . .\n\n"); pcor(0);
    		exit(1);
    	}

    	if(resposta == 1)
    	{
    		num_jogadores++;
    		pf("DIGITE O NOME DO 'TERCEIRO' JOGADOR: "); scanf(" %80[^\n]", vtJogadores[2].nome); vtJogadores[2].cor = 2;
    		pf("A COR DA SUA PECA SERA ------ "); pcor(3); pf("VERDE "); pcor(0); pf("------"); pf("\n\n");
    		pf(".-----------------------------------.\n");
    		pf("| 1. Caso tenha mais jogadores.     |\n");
    		pf("| 2.Caso 'NAO' tenha mais jogadores.|\n");
    		pf(".-----------------------------------.\n");
    		pf("AGORA DIGITE SUA RESPOSTA: "); scanf("%d", &resposta); pf("\n\n");
    		if (resposta < 1 || resposta > 2)
    		{
    			pcor(5); pf("\tNUMERO INVALIDO !!\n\n"); pcor(0);
    			pf(".-----------------------------------.\n");
    			pf("| 1. Caso tenha mais jogadores.     |\n");
    			pf("| 2.Caso 'NAO' tenha mais jogadores.|\n");
    			pf(".-----------------------------------.\n");
    			pf("AGORA DIGITE SUA RESPOSTA: "); scanf("%d", &resposta); pf("\n\n");

    			if(resposta < 1 || resposta > 2)
    			{
    				pcor(5); pf("\tNUMERO INVALIDO !! INICIAR EXECUTAVEL NOVAMENTE . . .\n\n"); pcor(0);
    				exit(1);
    			}
    		}
    		if(resposta == 1)
    		{
    			num_jogadores++;
    			pf("DIGITE O NOME DO 'ULTIMO' JOGADOR: "); scanf(" %80[^\n]", vtJogadores[3].nome); vtJogadores[3].cor = 3;
    			pf("A COR DA SUA PECA SERA ------ "); pcor(4); pf("AMARELO "); pcor(0); pf("------"); pf("\n\n");
    		}
    	}
    }
    pf("\n----------------------------------------------------------------------------------------------------------------------------------\n\n");
    pf("\t\t\t\tPRIMEIRO PASSO CONCLUIDO !\n\n"); 
    pf("\tAgora para podermos iniciar a partida, o jogador devera estar ciente das regras do jogo que estao sendo representadas\n");
    pf("na especificacao de requisitos do Software... TENHAM UM OTIMO JOGO !!!"); pf("\n\n");

    for (i = 0 ; i < num_jogadores ; i ++) /* CRIACAO DAS PECAS */
    {
    	cor = i / 4 ;
    	PecasRetorno = PEC_Pecas (vtPecas, i, cor);
    	switch ( PecasRetorno ) 
			{
				case PEC_CondRetFaltaMemoria :
					pcor(5); pf("\n\n\tMEMORIA INSUFICIENTE PARA CRIAR PECAS !!\n\n"); pcor(0);
				case PEC_CondRetJaExiste :
					pcor(5); pf("\n\n\tPECA JA FOI CRIADA !!\n\n"); pcor(0);
				default :
					pcor(5); pf("\n\n\tERRO INESPERADO !!\n\n"); pcor(0);
			}
    }

    TabuleiroRetorno = TAB_CriaTabuleiro_Ludo( &pTabuleiro ) ;
	
	if ( TabuleiroRetorno != TAB_CondRetOK )
	{
		pcor(5); pf("\n\n\tMEMORIA INSUFICIENTE PARA CRIAR TABULEIRO !!\n\n"); pcor(0);
	}

	pf("\t--------------------------------------------------INICIO DO JOGO-------------------------------------------------------\n\n");

	do
	{
		// DESENHA TABULEIRO
		pf("\n\n\tAGORA E A VEZ DO VERMELHO !! VAMOS JOGAR O DADO . . .\n\n");
		//JOGAR DADO E VERIFICAR NUMERO
		//DECIDIR ACÃO COM USUARIO

		//DESENHA TABULEIRO
		pf("\n\n\tAGORA E A VEZ DO AZUL !! VAMOS JOGAR O DADO . . .\n\n");
		//JOGAR DADO E VERIFICAR NUMERO
		//DECIDIR ACÃO COM USUARIO

		if (num_jogadores > 2)
		{
			//DESENHA TABULEIRO
			pf("\n\n\tAGORA E A VEZ DO VERDE !! VAMOS JOGAR O DADO . . .\n\n");
			//JOGAR DADO E VERIFICAR NUMERO
			//DECIDIR ACÃO COM USUARIO

			if(num_jogadores > 3)
			{
				//DESENHA TABULEIRO
				pf("\n\n\tAGORA E A VEZ DO AMARELO !! VAMOS JOGAR O DADO . . .\n\n");
				//JOGAR DADO E VERIFICAR NUMERO
				//DECIDIR ACÃO COM USUARIO
			}
		}

	} while (VerificaVencedor (vtPecas, num_jogadores) != 1);
	
	pf("\n\n");
	pcor(4); pf("\t\t.----------------------------------------------.\n"); pcor(0);
    pcor(4); pf("\t\t|                                              |\n"); pcor(0);
    pcor(4); pf("\t\t|     PARABENS !!! TEMOS UM VENCEDOR . . .     |\n"); pcor(0);
    pcor(4); pf("\t\t|                                              |\n"); pcor(0);
    pcor(4); pf("\t\t.----------------------------------------------.\n"); pcor(0);
    pf("\n\n");

	DesenhaPlacar( vtPecas, vtJogadores , num_jogadores );

    for (i = 0 ; i < num_jogadores ; i ++) /* DESTRUICAO DAS PECAS */
    {
    	PecasRetorno = PEC_DestroiPeca (vtPecas[i]);
    	switch ( PecasRetorno ) 
			{
				case PEC_CondRetNaoExiste :
					pcor(5); pf("\n\n\tPECA QUE DESEJA DESTRUIR NAO EXISTE !!\n\n"); pcor(0);
				default :
					pcor(5); pf("\n\n\tERRO INESPERADO !!\n\n"); pcor(0);
			}
    }

    TabuleiroRetorno = TAB_DestruirTabuleiro ( pTabuleiro ); /* DESTRUICAO DO TABULEIRO */

    if ( TabuleiroRetorno != TAB_CondRetOK )
	{
		pcor(5); pf("\n\n\tERRO INESPERADO !!\n\n"); pcor(0);
	}

	pf("\n\n");
	pcor(2); pf("\t\t__/\\\\\\\\\\\\\\\\\\_________________________________________\n"); pcor(0);
	pcor(2); pf("\t\t _\\/\\\\///////////___________________________________________\n"); pcor(0);
	pcor(2); pf("\t\t  _\\/\\\\______________/\\\\___________________________________\n"); pcor(0);
	pcor(2); pf("\t\t   _\\/\\\\\\\\\\\\_____\\///_____/\\\\\\__/\\\\\\_______________\n"); pcor(0);
	pcor(2); pf("\t\t    _\\/\\\\///////_______/\\\\__/\\\\\\///\\\\\\///\\\\__________\n"); pcor(0);
	pcor(2); pf("\t\t     _\\/\\\\____________\\/\\\\_\\/\\\\__\\//\\\\___\\/\\\\_______\n"); pcor(0);
	pcor(2); pf("\t\t      _\\/\\\\____________\\/\\\\_\\/\\\\__\\//\\\\___\\/\\\\_______\n"); pcor(0);
	pcor(2); pf("\t\t       _\\/\\\\____________\\/\\\\_\\/\\\\__\\//\\\\___\\/\\\\_______\n"); pcor(0);
	pcor(2); pf("\t\t        _\\///______________\\///_ _\\///____\\////_____\\////________\n"); pcor(0);
	pf("\n\n");

	return 0;

}    /* Fim função: MAIN */

/****************  Código das funções encapsuladas no módulo  **********************/

static int JogarDado ( void )
{
	int valor;
	TAB_CondRet TabuleiroRetorno;
	TabuleiroRetorno = TAB_LancaDado ( &valor );
	if(TabuleiroRetorno != TAB_CondRetOK)
	{
		pcor(5); pf("\n\n\tERRO INESPERADO !!\n\n"); pcor(0);
	}
	pcor(1); pf("\t\t\t+------+    \n"); pcor(0);   
	pcor(1); pf("\t\t\t|`.    | `. \n"); pcor(0);   
	pcor(1); pf("\t\t\t|  `+--+---+\n"); pcor(0);   
	pcor(1); pf("\t\t\t|   |  |   |\n"); pcor(0);   
	pcor(1); pf("\t\t\t+---+--+.  |\n"); pcor(0);   
	pcor(1); pf("\t\t\t `. |    `.|\n"); pcor(0);   
	pcor(1); pf("\t\t\t   `+------+\n"); pcor(0);
	pf("\n\n")
	pf("---------AO JOGAR O DADO VOCE OBTEVE O NUMERO: %d --------\n\n", valor);
	return valor;
}

static void DesenhaPlacar ( PEC_tpPecas * pPecas , JOGO_Jogador * vtJogadores , int num_jogadores )
{
	int i, k, final, maior = 0, pos = 0;
	int qtdfim[] = {0,0,0,0};

	for(i = 0 ; i < num_jogadores ; i++)
	{
		for(k = 0 ; k < 4 ; k++)
		{
			PecasRetorno = PEC_ObtemFinal ( pPecas[pos] , &final );
			switch ( PecasRetorno ) 
			{
				case PEC_CondRetNaoExiste :
					pcor(5); pf("\n\n\tPECA NAO EXISTE !!\n\n"); pcor(0);
				default :
					pcor(5); pf("\n\n\tERRO INESPERADO !!\n\n"); pcor(0);
			}
			pos++ ;
			
			if (final == 1)
				qtdfim[i]++;
		}
	}
	for (i = 0; i < 4; i++)
	{
		if(qtdfim[i]>qtdfim[maior])
			maior = i;
	}

	pf("\n\n");
	pcor(4); pf("O JOGADOR %s E O VENCEDOR DO JOGO COM '4' PONTOS !!!\n\n", vtJogadores[maior].nome ); pcor(0);
	for (i = 0; i < 4; i++)
	{
		pf("JOGADOR: %s OBTEVE %d PONTOS !!\n", vtJogadores[i].nome ,qtdfim[i] );
	}
	pf("\n");
}

static int VerificaVencedor ( PEC_tpPecas * pPecas, int num_jogadores)
{
	int i, cor, numcor = 0, final, cont = 0 ;
	PEC_CondRet PecasRetorno ;

	for(i = 0 ; i < (num_jogadores*4) ; i++)
	{
		PecasRetorno = PEC_ObtemCor ( pPecas[i] , &cor );

		switch ( PecasRetorno ) 
		{
			case PEC_CondRetNaoExiste :
				pcor(5); pf("\n\n\tPECA NAO EXISTE !!\n\n"); pcor(0);
			default :
				pcor(5); pf("\n\n\tERRO INESPERADO !!\n\n"); pcor(0);
		}

		PecasRetorno = PEC_ObtemFinal ( pPecas[i] , &final );

		switch ( PecasRetorno ) 
		{
			case PEC_CondRetNaoExiste :
				pcor(5); pf("\n\n\tPECA NAO EXISTE !!\n\n"); pcor(0);
			default :
				pcor(5); pf("\n\n\tERRO INESPERADO !!\n\n"); pcor(0);
		}

		if(numcor == cor)
		{
			if(final == 1)
			{
				cont ++;
			}
			else
			{
				numcor++;
				cont = 0;
			}
		}
		
		if (cont == 4)
		{
			return 1;
		}
	}
	return 0;
}

/************* Fim do módulo de implementação: JOGO Módulo jogo / Principal ****************/
