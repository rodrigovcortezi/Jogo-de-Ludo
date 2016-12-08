/***************************************************************************
*  $MCI Modulo de implementação: TTAB Teste tabuleiro
*
*  Arquivo gerado:              TESTTAB.C
*  Letras identificadoras:      TTAB
*
*  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
*  Gestor:  Professor Alessandro Garcia
*  Autores: dcr - Daniel Cunha Rios 
*
*  $HA Histórico de evolução:
*     Versão |  Autor   |      Data     |    Observações
*       2    |   dcr    |  13/set/2016  | finalização desenvolvimento
*       1    |   dcr    |  30/set/2016  | início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include	"TABULEIRO.H"
#include    "PECAS.H"

#include    "TST_Espc.h"
#include    "Generico.h"
#include    "LerParm.h"


static const char CRIAR_TAB_LUDO_CMD          [ ] = "=criartab"        ;
static const char MOVER_PECA_CMD              [ ] = "=moverpeca"       ;
static const char INSERIR_PECA_INICIO_CMD     [ ] = "=inserirpecaini"  ;
static const char LANCAR_DADO_CMD             [ ] = "=lancardado"      ;
static const char DESTRUIR_TAB_CMD            [ ] = "=destruirtab"     ;

#define MAX_PECAS 15 //USADO PARA VETOR DE PECAS

#define MAX_TABULEIRO 10 //USADO PARA VETOR DE PECAS

/***********************************************************************
*
*  $FC Função: TTAB &Testar tabuleiro
*
*  $ED Descrição da função
*     Criar um tabuleiro
*
*     Comandos disponíveis:
*
*     =criartab                         Tab CondRetEsp
*     =moverpeca                        Tab IndPeca QtdMov CondRetEsp
*     =inserirpecaini                   Tab IndPeca CondRetEsp
*	  =lancardado   				    CondRetEsp
*	  =destruirtab   				    Tab CondRetEsp
*
***********************************************************************/

TAB_tpLudo vtTabuleiro[MAX_TABULEIRO]; //DECLARACAO DO VETOR DE TABULEIRO

PEC_tpPeca vtPecas[MAX_PECAS]; //DECLARAÇAO DO VETOR DE PECAS

/***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int tab           =-1 ;
	int ret           =-1 ;
	int qtdMov        =-1 ;
	int CondRetEsp    =-1 ;
	int CondRetObtido =-1 ;
	int numLidos      =-1 ;
	int indPeca       =-1 ;
	int valor             ;
	int i                 ;



	for(i=0;i<16;i++)
	{
		ret = PEC_CriaPeca ( vtPecas, i, i/4 ) ;
		if ( ret != PEC_CondRetOK )
			break;
	}

	PEC_AtualizaPeca ( vtPecas[7] , 0 , 'D' ) ;

	/* Testar Criar Tabuleiro */

	if( strcmp( ComandoTeste , CRIAR_TAB_LUDO_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii", &tab, &CondRetEsp) ;
		if( numLidos != 2 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_CriaTabuleiro_Ludo ( &vtTabuleiro [tab] ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao criar tabuleiro") ;


	} /* fim ativa: Criar Tabuleiro */


	/* Testar Mover Peça */

	else if( strcmp( ComandoTeste , MOVER_PECA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iiii", &tab, &indPeca, &qtdMov, &CondRetEsp ) ;
		if( numLidos != 4 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_MovePeca ( vtTabuleiro [tab], vtPecas [indPeca], qtdMov ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao mover peça") ;


	} /* fim ativa: Mover Peça */


	/* Testar Inserir peça no inicio */

	else if( strcmp( ComandoTeste , INSERIR_PECA_INICIO_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iii", &tab, &indPeca, &CondRetEsp ) ;
		if( numLidos != 3 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_InserePecaInicio ( vtTabuleiro [tab], vtPecas [indPeca] ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Inserir peça no inicio") ;


	} /* fim ativa: Inserir peça no inicio */


	/* Testar Lançar o dado */

	else if( strcmp( ComandoTeste , LANCAR_DADO_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "i", &CondRetEsp ) ;
		if( numLidos != 1 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_LancaDado ( &valor ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Lançar o dado") ;


	} /* fim ativa: Lançar o dado */


	/* Testar Destruir tabuleiro */

	else if( strcmp( ComandoTeste , DESTRUIR_TAB_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii", &tab, &CondRetEsp ) ;
		if( numLidos != 2 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_DestruirTabuleiro ( vtTabuleiro [tab] ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Destruir tabuleiro") ;


	} /* fim ativa: Destruir tabuleiro */

    return TST_CondRetNaoConhec ;

}  /* Fim função: TTAB &Testar tabuleiro */

/********** Fim do módulo de implementação: TTAB Teste lista de símbolos **********/