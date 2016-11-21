
#include <stdio.h>
#include "PECAS.H"

int main ()
{
	PEC_tpPeca pPeca[4] ;
	PEC_CondRet retorno_pec ;
	int cor, final ,i;
	char status ;

	//printf("Address before calling function CRIA: %p\n",pPeca[0]) ;
	retorno_pec = PEC_CriaPeca ( pPeca, 0, 0 ) ;
	//printf("Address after calling function CRIA: %p\n",pPeca[0]) ;
	retorno_pec = PEC_CriaPeca ( pPeca, 1, 1 ) ;
	retorno_pec = PEC_CriaPeca ( pPeca, 2, 2 ) ;
	retorno_pec = PEC_CriaPeca ( pPeca, 3, 3 ) ;
	retorno_pec = PEC_AtualizaPeca ( pPeca[3] , 1, 'G' ) ;
	printf("retorno = %u",retorno_pec);
	i = 0 ;
	while ( i < 4 ) {
		retorno_pec = PEC_ObtemInfo ( pPeca[i] , &cor, &final, &status ) ;
		printf("====== PECA %d ======\n Cor: %d\nFinal: %d\nStatus: %c\n", i+1 ,cor, final, status) ;
		i++;
	}

	return 0 ;
}