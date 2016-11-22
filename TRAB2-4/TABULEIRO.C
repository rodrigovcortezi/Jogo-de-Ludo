ALTERACAO
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
 
 
/***** Protótipo das funções encapsuladas no módulo *****/
 
static TAB_Casa *CriaCasa ( LIS_tppLista desvio , 
                             PEC_tpPeca conteudo , int cor ) ;

static TAB_Casa *ProcuraPeca ( TAB_Ludo pTabuleiro , PEC_tpPeca pPeca ) ;
 
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
 
    retorno_lst = LST_CriaLista ( &pListaCirc , LiberarCasa ) ;
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
 
        retorno_lis = LIS_CriarLista( LiberarCasa , &pListaSimples ) ;
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
 
 
TAB_CondRet TAB_MovePeca( TAB_Ludo pTabuleiro, PEC_tpPeca pPeca , int n )
{
 
    TAB_Casa *casa , *aux ;
 
    int cor , final , cor2, final2 ;
 
    char status , status2 ;

    LIS_tppLista lista_aux ;

    LIS_tpCondRet retorno_lis ;

    if ( n <= 0 )
    {
        return TAB_CondRetMovimentoInvalido ;
    }

    PEC_ObtemInfo ( pPeca , &cor, &final, &status ) ;
 
    if ( status == 'F' )
    {
        return TAB_CondRetPecaMorta ;
    }
 
    casa = ProcuraPeca ( pTabuleiro , pPeca ) ;
    if ( casa == NULL )
    {
        return TAB_CondRetNaoEncontrouPeca ;
    }
    
    aux = casa ;
 
    while ( n ) {
                 
        if ( casa->cor != cor ) {

            LST_AvancarElementoCorrente ( pTabuleiro->casas , 1) ;
            LST_ObterValor ( pTabuleiro->casas , casa ) ;
            n-- ;

        }
 
        else {
            lista_aux = casa->desvio ;

            if ( casa->desvio != NULL ) {

                IrInicioLista ( lista_aux ) ;
                n-- ;

            }

            retorno_lis = LIS_AvancarElementoCorrente ( lista_aux , n ) ;
            if ( retorno_lis == LIS_CondRetFimLista )
            {
                return TAB_CondRetMovimentoInvalido ;    
            }
            
            if ( final == 0 )
                PEC_AtualizaPeca ( pPeca , 1 , 'D' ) ;
            

            LIS_ObterValor ( lista_aux , casa ) ;
            break ;
        } 
        
    }

    

    if ( casa->conteudo != NULL ){
    
        PEC_ObtemInfo ( casa->conteudo , &cor2, &final2, &status2 ) ;
        if ( cor2 == cor )
        {
            return TAB_CondRetMovimentoInvalido ;
        }
        PEC_AtualizaPeca ( casa->conteudo , 0 , 'F' ) ;
        
    }

    aux->conteudo = NULL ;
    casa->conteudo = pPeca ;
 
    return TAB_CondRetOK ;
 
}/* Fim função: TAB  &Mover Peça */

 
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

static TAB_Casa *ProcuraPeca ( TAB_Ludo pTabuleiro , PEC_tpPeca pPeca )
{

    TAB_Casa *casa , *aux ;
 
    int cor , final , flag , i ;
 
    char status ;
 
    PEC_ObtemInfo( pPeca , &cor, &final, &status ) ;

    flag = 0 ;
    if ( final == 0 ) {
        for ( i = 0 ; i < 52 ; i++ ){        
            LST_ObterValor ( pTabuleiro->casas , casa ) ;
 
            if (casa->conteudo == pPeca)
                return casa ;
            else
                LST_AvancarElementoCorrente ( pTabuleiro->casas , 1 ) ;
        }
    }
    else {
        for ( i = 0 ; i < 52 && flag != 1 ; i++ ){
            LST_ObterValor ( pTabuleiro->casas , casa ) ;
 
            if ( casa->desvio != NULL && casa->cor == cor ){
                flag = 1 ;
            }
            else
                LST_AvancarElementoCorrente ( pTabuleiro->casas , 1 ) ;
        }
 
        aux = casa;
        IrInicioLista( casa->desvio ) ;
        for ( i = 0 ; i < 6 ; i++ ){
            LIS_ObterValor( casa->desvio , aux ) ;
            if ( aux->conteudo == pPeca )
                return casa ;
            else
                LIS_AvancarElementoCorrente ( casa->desvio , 1 ) ; 
        }
 
    }
 
    return NULL ;
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

