#include <stdio.h>
#include "TABULEIRO.H"

int main()
{
	TAB_tpLudo pTabuleiro ;
	TAB_CondRet retorno_tab ;
	retorno_tab = TAB_CriaTabuleiro_Ludo( &pTabuleiro ) ;
	//retorno_tab = TAB_DestruirTabuleiro ( pTabuleiro ) ;
	printf("RETORNO: %d\n\n",retorno_tab) ;
	return 0 ;
}