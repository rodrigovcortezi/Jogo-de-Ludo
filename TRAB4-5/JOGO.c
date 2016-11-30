#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "JOGO.h"
#include "TABULEIRO.h"

typedef struct jogo
{
	TAB_tpLudo pTabuleiro ;
	PEC_tpPeca pecas[16] ;
	int num_jogadores ;
} JOGO_Ludo ;

static void LimpaCabeca ( JOGO_Ludo *pJogo ) ;

JOGO_CondRet JOGO_InicializaJogo ( JOGO_Ludo **pJogo , int num , int *cor ) 
{
	int i ;

	TAB_tpLudo pTabuleiro ;
	TAB_CondRet retorno_tab ;
	PEC_CondRet retorno_pec ;
	
	if ( num < 2 || num > 4 )
	{
		return JOGO_CondRetNumeroDeJogadoresInvalido ;
	}

	for ( i = 0 ; i < num ; i++ )
		if ( cor[i] < 0 || cor[i] > 3 )
			return JOGO_CondRetCorInvalida ;

	*pJogo = ( JOGO_Ludo * ) malloc ( sizeof ( JOGO_Ludo ) ) ;
	if ( pJogo == NULL )
	{
		return JOGO_CondRetFaltouMemoria ;
	}
	LimpaCabeca ( *pJogo ) ;

	retorno_tab = TAB_CriaTabuleiro_Ludo( &pTabuleiro ) ;
	if ( retorno_tab != TAB_CondRetOK )
	{
		return JOGO_CondRetFaltouMemoria ;
	}

	for ( i = 0 ; i < num ; i++ ) {
		for ( k = 4*cor[i] ; k < k + 4 ; k++ ) {
			retorno_pec = PEC_CriaPeca ( (*pJogo)->pecas , k , cor[i]) ;
			switch ( retorno_pec ) {
				case PEC_CondRetFaltaMemoria :
					return JOGO_CondRetFaltouMemoria ;
				case PEC_CondRetJaExiste :
					return JOGO_CondRetCorJaEscolhida ;
				default :
					printf ( "Erro inesperado \n" ) ;
			}
		}
	}

	(*pJogo)->pTabuleiro = pTabuleiro ;
	(*pJogo)->num_jogadores = num ;
	// DesenhaTabuleiro () ;
	return JOGO_CondRetOK ;

}

JOGO_CondRet JOGO_RealizaJogada ( JOGO_Ludo *pJogo , int cor ) 
{
	int dado ;
	TAB_CondRet retorno_tab ;

	TAB_LancaDado ( &dado ) ;
	// DesenhaDado () ;
	


}



static void LimpaCabeca ( JOGO_Ludo *pJogo )
{
	int i ;
	pJogo->pTabuleiro = NULL ;

	for ( i = 0 ; i < 16 ; i++ )
		pJogo->pecas[i] = NULL ;

	pJogo->num_jogadores = 0 ;
}


static int VerificaPecaDentro ( JOGO_Ludo *pJogo , int cor )
{
	int i , cor , final , status ;
	PEC_tpPeca aux ;
	PEC_CondRet retorno_pec ;
	for ( i = 4 * cor ; i < i + 4 ; i++ ) {
		aux = (*pJogo)->pecas[i] ;
		retorno_pec = PEC_ObtemInfo ( aux , &cor , &final , &status ) ;
		if ( status == 'D' )
			return 1 ;
	}
}












