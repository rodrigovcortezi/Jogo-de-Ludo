#include <stdio.h>

#define VERMELHO "\033[01;31m" 
#define AZUL     "\033[01;34m"
#define VERDE    "\033[01;32m"
#define AMARELO  "\033[01;33m"

int main ()
{
	printf ( "Escolha uma das cores abaixo:\n" VERMELHO "0 - Vermelho\n" AZUL 
		"1 - Azul\n" VERDE "2 - Verde\n" AMARELO "3 - Amarelo\n" ) ;
	return 0 ;
}