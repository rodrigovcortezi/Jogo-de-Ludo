
/***************************************************************************
*  $MCI Módulo de implementação: TAB  Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
*  Gestor:  Professor Alessandro Garcia
*  Autores: rvc - Rodrigo Villardi Cortezi
*
*  $HA Histórico de evolução:
*     Versão |  Autor  |      Data     |    Observações
*       2    |   rvc   |  13/out/2016  |  finalização de desenvolvimento
*       1    |   rvc   |  30/set/2016  |  início desenvolvimento
*
***************************************************************************/
 
#define BRANCO 5
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#include "LISTA.H"
#include "LCIRC.H"
#include "PECAS.H"
 
 
#define TABULEIRO_OWN
#include "TABULEIRO.H"
#undef TABULEIRO_OWN
 
/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor do tabuleiro de ludo
*
***********************************************************************/
 
typedef struct Tabuleiro {
 
    LST_Circular casas ;
        /* Ponteiro para a lista de casas */
 
} TAB_TabuleiroLudo ;
 
/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da casa
*
***********************************************************************/
 
typedef struct TAB_casa {
    int cor ;
        /* Indica a cor da casa */
 
    PEC_tpPeca conteudo ;
        /* Ponteiro para o conteudo da casa */
 
    LIS_tppLista desvio ;
        /* Ponteiro para o desvio */
 
} TAB_Casa ;
typedef void ( *pFunc ) ( void * ) ; typedef void **ppVoid ;
 
/***** Protótipo das funções encapsuladas no módulo *****/
 
static TAB_Casa *CriaCasa ( LIS_tppLista desvio , 
                             PEC_tpPeca conteudo , int cor ) ;

static int ProcuraPeca ( TAB_TabuleiroLudo *pTabuleiro , PEC_tpPeca pPeca ) ;
 
static void LiberarCasa ( TAB_Casa *pCasa ) ;
 
 
/*****  Código das funções exportadas pelo módulo  *****/
 
/***************************************************************************
*
*  Função: TAB  &Criar tabuleiro
*  ****/
 
 
TAB_CondRet TAB_CriaTabuleiro_Ludo( TAB_TabuleiroLudo **pTabuleiro )  
{   
    int i, k , j ;
 
    LST_Circular pListaCirc ;
 
    LIS_tppLista pListaSimples ;

    TAB_Casa *casa ;
 
    LST_CondRet retorno_lst ;
 
    LIS_tpCondRet retorno_lis ;

    *pTabuleiro = ( TAB_TabuleiroLudo *) malloc ( sizeof ( TAB_TabuleiroLudo ) ) ;
    
    if ( *pTabuleiro == NULL )
    {
        return TAB_CondRetFaltouMemoria ;
    }
 
    retorno_lst = LST_CriaLista ( &pListaCirc , ( pFunc ) LiberarCasa ) ;
    if ( retorno_lst != LST_CondRetOK )
    {
        return TAB_CondRetFaltouMemoria ;
    } 
 
    for( i = 0 ; i < 4 ; i++ ){
         
        for( k = 0; k < 12 ; k++ ){
 
            casa = CriaCasa ( NULL , NULL , BRANCO ) ;
            if ( casa == NULL )
            {
                return TAB_CondRetFaltouMemoria ;
            }
            retorno_lst = LST_InsereElemDireita( pListaCirc , casa ) ;
            if ( retorno_lst != LST_CondRetOK )
            {
                return TAB_CondRetFaltouMemoria ;
            }
 
        }
 
        retorno_lis = LIS_CriarLista( ( pFunc ) LiberarCasa , &pListaSimples ) ;
        if ( retorno_lis != LIS_CondRetOK )
        {
            return TAB_CondRetFaltouMemoria ;
        }

        casa = CriaCasa ( pListaSimples , NULL , i ) ;
        if ( casa == NULL )
        {
            return TAB_CondRetFaltouMemoria ;
        }
        retorno_lst = LST_InsereElemDireita ( pListaCirc , casa ) ;
        if ( retorno_lst !=  LST_CondRetOK )
        {
            return TAB_CondRetFaltouMemoria ;
        }

        for ( j = 0 ; j < 6 ; j++ ){
 
            casa = CriaCasa ( NULL , NULL , i ) ;
            if ( casa == NULL )
            {
                return TAB_CondRetFaltouMemoria ;
            }
            retorno_lis = LIS_InserirElementoApos( pListaSimples , casa ) ;
            if ( retorno_lis != LIS_CondRetOK )
            {
                return TAB_CondRetFaltouMemoria ;
            }
                 
        }
 
    }
 
    (*pTabuleiro)->casas = pListaCirc ;
 
    return TAB_CondRetOK ;
 
} /* Fim função: TAB  &Criar tabuleiro */

/***************************************************************************
*
*  Função: TAB  &Mover peça
*  ****/
 
 
TAB_CondRet TAB_MovePeca( TAB_TabuleiroLudo *pTabuleiro, PEC_tpPeca pPeca , int n )
{
 
    TAB_Casa *casa , *aux;

    int cor , final , cor2, final2 , cond ;
 
    char status , status2 ;

    LIS_tppLista caminho_final = NULL;

    LIS_tpCondRet retorno_lis ;

    PEC_CondRet retorno_pec ;

    if ( n <= 0 || n > 6 )
    {
        return TAB_CondRetMovimentoInvalido ;
    }

    retorno_pec = PEC_ObtemCor ( pPeca , &cor ) ;
    if ( retorno_pec != PEC_CondRetOK )
        return TAB_CondRetPecaNaoExiste ;
    
    PEC_ObtemFinal ( pPeca , &final ) ;
    PEC_ObtemStatus ( pPeca , &status ) ;
 
    if ( status == 'F' )
    {
        return TAB_CondRetPecaMorta ;
    }

    if ( final == 1 )
    {
        return TAB_CondRetMovimentoInvalido ;
    }
 
    cond = ProcuraPeca ( pTabuleiro , pPeca ) ;
    if ( cond == 0 )
    {
        return TAB_CondRetNaoEncontrouPeca ;
    }
    
    LST_ObterValor ( pTabuleiro->casas , ( ppVoid ) &casa ) ;

    aux = casa ;
    if ( casa->conteudo == pPeca ) {     

    	while ( aux->cor != cor && n > 0 ) {
    		LST_AvancarElementoCorrente ( pTabuleiro->casas , 1 ) ;
    		LST_ObterValor ( pTabuleiro->casas , (ppVoid) &aux ) ;
    		n-- ;
    	}
    	if ( n != 0 ) {
    		caminho_final = aux->desvio ;
    		LIS_IrInicioLista ( caminho_final ) ;
    		retorno_lis = LIS_AvancarElementoCorrente ( caminho_final , n-1 ) ;
    		if ( retorno_lis == LIS_CondRetFimLista )
    			return TAB_CondRetMovimentoInvalido ;
    		LIS_ObterValor ( caminho_final , ( ppVoid ) &aux ) ;
    	}

    }
    else {                  

    	caminho_final = casa->desvio ;
    	retorno_lis = LIS_AvancarElementoCorrente ( caminho_final , n ) ;
    	if ( retorno_lis == LIS_CondRetFimLista )
    		return TAB_CondRetMovimentoInvalido ;
    	LIS_ObterValor ( caminho_final , ( ppVoid ) &aux ) ;
        
    }

    if ( caminho_final != NULL ) {      //somente é necessario verificar se chegou na casa final se entrou na reta final

        retorno_lis = LIS_AvancarElementoCorrente ( caminho_final , 1 ) ;       
        if ( retorno_lis == LIS_CondRetFimLista ) {                 //verifica se chegou na casa final
            PEC_AtualizaPeca ( pPeca , 1 , 'D' ) ;      //se chegou, somente é sinalizado que aquela peça chegou na casa final ( final = 1 )
            casa->conteudo = NULL ;         //limpa a casa onde a peça estava antes do movimento
            // as peças que chegarem ao final não serão inseridas na casa final. Não é possível guardar mais de uma peça em uma casa
            return TAB_CondRetOK ;
        }

    }

    if ( aux->conteudo != NULL ) {
    
        PEC_ObtemInfo ( aux->conteudo , &cor2, &final2, &status2 ) ;
        if ( cor2 == cor ) 
            return TAB_CondRetMovimentoInvalido ;
              
        PEC_AtualizaPeca ( aux->conteudo , 0 , 'F' ) ;
        
    }



    casa->conteudo = NULL ;
    aux->conteudo = pPeca ;
 
    return TAB_CondRetOK ;
 
}/* Fim função: TAB  &Mover Peça */


 
/***************************************************************************
*
*  Função: TAB  &Insere peça no inicio
*  ****/
 
 
TAB_CondRet TAB_InserePecaInicio ( TAB_TabuleiroLudo *pTabuleiro , PEC_tpPeca pPeca )
{
     
    int cor, cor2 ;
 
    char status , status2 ;
 
    TAB_Casa *casa ;

    PEC_CondRet retorno_pec ;
 
    retorno_pec = PEC_ObtemStatus ( pPeca , &status ) ;
    if ( retorno_pec != PEC_CondRetOK )
        return TAB_CondRetPecaNaoExiste ;

    if ( status == 'D' )
    {
        return TAB_CondRetMovimentoInvalido ;
    }
    PEC_ObtemCor ( pPeca , &cor ) ; 
    LST_ObterValor ( pTabuleiro->casas , ( ppVoid ) &casa ) ;
 
    while ( casa->cor != cor ){
        LST_AvancarElementoCorrente ( pTabuleiro->casas , 1 ) ;
        LST_ObterValor ( pTabuleiro->casas , ( ppVoid ) &casa ) ;
    }
 
    LST_AvancarElementoCorrente ( pTabuleiro->casas , 2 ) ;
 
    LST_ObterValor ( pTabuleiro->casas , ( ppVoid ) &casa ) ;
    
    
    if ( casa->conteudo != NULL ){
    
        PEC_ObtemCor ( casa->conteudo , &cor2 ) ;
        if ( cor2 == cor )
        {
            return TAB_CondRetMovimentoInvalido ;
        }
        PEC_AtualizaPeca ( casa->conteudo, 0, 'F' ) ;
    }

    PEC_AtualizaPeca ( pPeca , 0 , 'D' ) ;
 
    casa->conteudo = pPeca ;
 
    return TAB_CondRetOK ;
 
} /* Fim função: TAB  &Insere peça no inicio */
 
 
/***************************************************************************
*
*  Função: TAB  &Gera valor
*  ****/
 
TAB_CondRet TAB_LancaDado ( int * pValor )
{
  
    int ValorAleatorio ;
  
    srand ( time ( NULL ) ) ;
    ValorAleatorio = ( rand() % 6 ) + 1 ;
      
    * pValor = ValorAleatorio ;
  
    return TAB_CondRetOK ;
  
} /* Fim função: TAB  &Gera Valor */



/***************************************************************************
*
*  Função: TAB  &Destroi Tabuleiro
*  ****/
 
TAB_CondRet TAB_DestruirTabuleiro ( TAB_TabuleiroLudo *pTabuleiro )
{
 
    LST_DestruirLista ( pTabuleiro->casas ) ;
 
    return TAB_CondRetOK ;
 
} /* Fim função: TAB  &Destroi Tabuleiro */
 
 
 
/****************  Código das funções encapsuladas no módulo  **********************/
 
 
static TAB_Casa *CriaCasa ( LIS_tppLista desvio , PEC_tpPeca conteudo , int cor )
{
    TAB_Casa *nv ;
     
    nv  = (TAB_Casa *) malloc ( sizeof ( TAB_Casa ) ) ;
     
    if( nv == NULL ){
        return NULL ;
    }
 
    nv->cor = cor ;
 
    nv->desvio = desvio ;
 
    nv->conteudo = conteudo ;
 
    return nv ;
} 

static int ProcuraPeca ( TAB_TabuleiroLudo *pTabuleiro , PEC_tpPeca pPeca )			//retorna 1 caso tenha encontrado a peça e 0 caso contrário
{
    TAB_Casa *casa, *aux, *aux2 ;
    LIS_tppLista caminho_final ;
    LIS_tpCondRet retorno_lis ;
    int cor ;
      
    PEC_ObtemCor ( pPeca , &cor ) ;

    LST_ObterValor ( pTabuleiro->casas , (ppVoid) &casa ) ;
    aux = casa ;
    do {

        if ( aux->conteudo == pPeca )
            return 1 ;

        else if ( aux->cor == cor && aux->desvio != NULL ) {
            caminho_final = aux->desvio ;
            LIS_IrInicioLista( caminho_final ) ;
            do {

                LIS_ObterValor ( caminho_final , ( ppVoid ) &aux2 ) ;
                if ( aux2->conteudo == pPeca )
                    return 1 ;
                retorno_lis = LIS_AvancarElementoCorrente ( caminho_final , 1 ) ;

            } while ( retorno_lis != LIS_CondRetFimLista ) ;
        }

        LST_AvancarElementoCorrente ( pTabuleiro->casas , 1 ) ;
        LST_ObterValor ( pTabuleiro->casas , (ppVoid) &aux ) ;

    } while ( aux != casa ) ;

    return 0 ;
   
}
 
static void LiberarCasa ( TAB_Casa *pCasa ) 
{
 
    if ( pCasa->desvio != NULL )
    {
        LIS_DestruirLista( pCasa->desvio ) ;
    }
 
    if ( pCasa->conteudo != NULL )
    {
        PEC_DestroiPeca ( pCasa->conteudo ) ;
    }
     
    pCasa = NULL ;
}

