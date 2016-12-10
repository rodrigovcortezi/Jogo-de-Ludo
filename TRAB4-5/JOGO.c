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

#include "TABULEIRO.h"

#define JOGO_OWN
#include "JOGO.h"
#undef JOGO_OWN

/***********************************************************************
 *
 *  $TC Tipo de dados: JOGO Jogo de Ludo
 *
 ***********************************************************************/

typedef struct jogo
{
	TAB_tpLudo pTabuleiro ;
	/* Ponteiro para Tabuleiro */
	
	PEC_tpPeca pecas[16] ;
	/* Vetor de Peças */
	
	int num_jogadores ;
	/* Numero de jogadores */
	
} JOGO_Ludo ;

/***** Protótipo das funções encapsuladas no módulo *****/

static void LimpaCabeca ( JOGO_Ludo *pJogo ) ;

static int VerificaPecaDentro ( JOGO_Ludo *pJogo , int cor )

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: JOGO  &Inicializa Jogo
 *  ****/

JOGO_CondRet JOGO_InicializaJogo ( JOGO_Ludo **pJogo , int num , int *cor ) 
{
	int i ;

	TAB_tpLudo pTabuleiro   ;
	TAB_CondRet retorno_tab ;
	PEC_CondRet retorno_pec ;
	
	if ( num < 2 || num > 4 )
	{
		return JOGO_CondRetNumeroDeJogadoresInvalido ;
	}

	for ( i = 0 ; i < num ; i++ )
	{
		if ( cor[i] < 0 || cor[i] > 3 )
		{
			return JOGO_CondRetCorInvalida ;
		}
	}

	* pJogo = ( JOGO_Ludo * ) malloc ( sizeof ( JOGO_Ludo ) ) ;
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

	for ( i = 0 ; i < num ; i++ ) 
	{
		for ( k = 4*cor[i] ; k < k + 4 ; k++ ) 
		{
			retorno_pec = PEC_CriaPeca ( (*pJogo)->pecas , k , cor[i]) ;
			switch ( retorno_pec ) 
			{
				case PEC_CondRetFaltaMemoria :
					return JOGO_CondRetFaltouMemoria ;
				case PEC_CondRetJaExiste :
					return JOGO_CondRetCorJaEscolhida ;
				default :
					printf ( "Erro inesperado \n" ) ;
			}
		}
	}

	(*pJogo)->pTabuleiro    = pTabuleiro ;
	(*pJogo)->num_jogadores = num        ;
	
	// DesenhaTabuleiro () ;
	
	return JOGO_CondRetOK ;
	
}  /* Fim função: JOGO  &Inicializa Jogo */

/***************************************************************************
 *
 *  Função: JOGO  &Realiza Jogada
 *  ****/

JOGO_CondRet JOGO_RealizaJogada ( JOGO_Ludo *pJogo , int cor ) 
{
	int dado ;
	TAB_CondRet retorno_tab ;

	TAB_LancaDado ( &dado ) ;
	// DesenhaDado () ;
	


}   /* Fim função: JOGO  &Realiza Jogada */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
 *
 *  $FC Função: JOGO  -Limpa cabeça
 *
 ***********************************************************************/

static void LimpaCabeca ( JOGO_Ludo *pJogo )
{
	int i ;
	pJogo->pTabuleiro = NULL ;

	for ( i = 0 ; i < 16 ; i++ )
		pJogo->pecas[i] = NULL ;

	pJogo->num_jogadores = 0 ;
}

/***********************************************************************
 *
 *  $FC Função: JOGO  -Verifica Peca Dentro
 *
 ***********************************************************************/

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
