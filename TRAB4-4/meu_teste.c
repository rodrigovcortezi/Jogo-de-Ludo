#include <stdio.h>
#include <stdlib.h>
#include "TABULEIRO.h"
#include "PECAS.h"

int main ()
{
	/*int i ;
	PEC_tpPeca pecas[16] = { NULL , NULL , NULL , NULL , NULL , NULL , 
		NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL , NULL  } ;
	TAB_tpLudo pTabuleiro ;
	TAB_CondRet retorno_tab ;
	PEC_CondRet retorno_pec ;
	retorno_tab = TAB_CriaTabuleiro_Ludo( &pTabuleiro ) ;
	for ( i = 0 ; i < 16 ; i ++ ) 
		retorno_pec = PEC_CriaPeca ( pecas , i , i/4 ) ;
	for ( i = 0 ; i < 2 ; i++ ) {	
		retorno_tab = TAB_InserePecaInicio ( pTabuleiro , pecas[0] ) ;
		printf ( "Condicao de retorno ( INSERE PECA INICIO ) : %d\n\n" , retorno_tab ) ;
	}

	//retorno_tab = TAB_MovePeca ( pTabuleiro , pecas[0] , 1 ) ;
	//printf ( "Condicao de retorno ( MOVE PECA ) : %d\n\n" , retorno_tab ) ;
	*/
	TAB_CondRet retorno_tab ;
	retorno_tab = TAB_DesenhaTabuleiro ( NULL ) ;
	return 0 ;
}




