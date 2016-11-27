#include <stdlib.h>
#include <stdio.h>
#include "JOGO.h"
#include "TABULEIRO.h"

#define VERMELHO "\033[01;31m" 
#define AZUL     "\033[01;34m"
#define VERDE    "\033[01;32m"
#define AMARELO  "\033[01;33m"

typedef struct jogo
{
	TAB_tpLudo pTabuleiro ;
	PEC_tpPeca pecas[16] ;
	int num_jogadores ;
} JOGO_Ludo ;

static void LimpaCabeca ( JOGO_Ludo *pJogo ) ;

JOGO_CondRet JOGO_InicializaJogo ( JOGO_Ludo **pJogo )
{
	int num , cor , i , k;
	TAB_tpLudo pTabuleiro ;
	TAB_CondRet retorno_tab ;
	PEC_CondRet retorno_pec ;
	*pJogo = (JOGO_Ludo *) malloc ( sizeof ( JOGO_Ludo ) ) ;
	if ( *pJogo == NULL )
	{
		return JOGO_CondRetFaltouMemoria ;
	}

	LimpaCabeca( *pJogo ) ;

	retorno_tab = TAB_CriaTabuleiro_Ludo( &pTabuleiro ) ; 
	if ( retorno_tab != TAB_CondRetOK )
	{
		return JOGO_CondRetFaltouMemoria ;
	}

	printf ( "Digite o numero de jogadores: " ) ;
	scanf ( "%d" , &num ) ;
	if ( num < 2 || num > 4 )
	{
		return JOGO_CondRetNumeroDeJogadoresInvalido ;
	}
	printf ( "Escolha uma das cores abaixo:\n" VERMELHO "0 - Vermelho\n" AZUL 
		"1 - Azul\n" VERDE "2 - Verde\n" AMARELO "3 - Amarelo\n" ) ;

	for ( i = 0 ; i < num ; i++ ) {
		printf ( "Jogador %d: " , ( i + 1 ) ) ;
		scanf ( "%d" , &cor ) ;
		retorno_pec = PEC_CriaPeca ( (*pJogo)->pecas , 4*cor, cor ) ;
		switch ( retorno_pec ) {
			case PEC_CondRetOK : {
				for ( k = ( 4*cor + 1 ) ; k < k + 3 ; k++ ) {
					retorno_pec = PEC_CriaPeca ( (*pJogo)->pecas , k , cor ) ;
					if ( retorno_pec != PEC_CondRetOK )
						return JOGO_CondRetFaltouMemoria ;
				}
			}

			case PEC_CondRetFaltaMemoria : 
				return JOGO_CondRetFaltouMemoria ;
			
			case PEC_CondRetJaExiste : 
				return JOGO_CondRetCorJaEscolhida ;

			case PEC_CondRetCorInvalida :
				return JOGO_CondRetCorInvalida ;
			
			default : 
				printf ( "Condicao de retorno inesperada \n" ) ;
				
		}
	}
	
	(*pJogo)->pTabuleiro = pTabuleiro ;
	(*pJogo)->num_jogadores = num ;

	return JOGO_CondRetOK ;
}





static void LimpaCabeca ( JOGO_Ludo *pJogo )
{
	int i ;
	pJogo->pTabuleiro = NULL ;

	for ( i = 0 ; i < 16 ; i++ )
		pJogo->pecas[i] = NULL ;

	pJogo->num_jogadores = 0 ;
}














