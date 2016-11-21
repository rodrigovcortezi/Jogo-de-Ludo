
#include <stdio.h>
#include <stdlib.h>
#include "LCIRC.H"

struct elemento
{
	int x ;
	char c ;
} ;

typedef struct elemento Elem ;

Elem *cria_elemento( int x , char c ) ;

int main()
{
	Elem *novo ;
	int i ;
	LST_Circular pLista ;
	LST_CondRet retorno_lst ;
	retorno_lst = LST_CriaLista ( &pLista , NULL ) ;

	for ( i = 0 ; i < 10 ; i++ ) {
		novo = cria_elemento ( i , 'a' + i ) ;
		retorno_lst = LST_InsereElemDireita ( pLista , novo ) ;
	}
	novo = cria_elemento ( 100 , 'z' ) ;
	retorno_lst = LST_BuscaElemento ( pLista , novo ) ;
	printf ( "Retorno da busca: %d\n" , retorno_lst ) ;

	
	return 0 ;

}

Elem *cria_elemento( int x , char c )
{
	Elem *new ;
	new = (Elem *) malloc ( sizeof ( Elem ) ) ;
	if ( new == NULL ) { printf("Faltou memoria\n"); exit(1); }

	new->x = x ;
	new->c = c ;
	return new ;
}