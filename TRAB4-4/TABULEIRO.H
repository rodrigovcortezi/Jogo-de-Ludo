#if ! defined( TABULEIRO_ )
#define TABULEIRO_

/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.H
*  Letras identificadoras:      TAB
*
*  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
*  Gestor:  Professor Alessandro Garcia
*  Autores: lr - Lucas Rodrigues 
*
*  $HA Histórico de evolução:
*     Versão |  Autor  |      Data     |    Observações
*       2    |   lr    |  16/out/2016  | finalização de desenvolvimento
*       1    |   lr    |  28/set/2016  | início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa um tabuleiro de ludo.
*     O tabuleiro possui uma cabeça encapsulando o seu estado.
*     É possivel criar um tabuleiro, deletar um tabuleiro,
*     inserir peca em um tabuleiro, mover peca de um tabuleiro,
*     e gera valor aleatório representando o dado.
*
*     Observacao importante: O modulo do tabuleiro não se importa
*     com as regras do jogo de ludo, o modulo do jogo apenas chamará as 
*	    funções do tabuleiro caso essas regras sejam previamente testadas, 
*	    por exemplo: o jogo avaliará se o jogador poderá mover a peça para
*	    uma casa X, caso ele puder ele chama o modulo tabuleiro.
*	  
***************************************************************************/

#if defined( TABULEIRO_OWN )
#define TABULEIRO_EXT
#else
#define TABULEIRO_EXT extern
#endif

#include "LCIRC.H"
#include "LISTA.H"
#include "PECAS.H"


/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

   typedef enum {

        	TAB_CondRetOK,
               		    /* Concluiu corretamente */   

		      TAB_CondRetFaltouMemoria, 
	       		          /* Faltou Memoria */

          TAB_CondRetPecaNaoExiste,
                      /* Peça não criada */
			   
        	TAB_CondRetPecaMorta,
              		    /* Peça fora de jogo */

        	TAB_CondRetNaoEncontrouPeca,
	      		          /* Não encontrou */

		      TAB_CondRetMovimentoInvalido
	      		          /* Movimento Invalido */
   
   } TAB_CondRet ;

/********** Estrutura Encapsulada Pelo Módulo ************************/

typedef struct Tabuleiro * TAB_tpLudo;

/***********************************************************************
*
*  $FC Função: TAB  &Cria Tabuleiro
*
*  $ED Descrição da função
*     Cria uma tabuleiro de ludo utilizando lista circular e lisa encadeada. 
*     Ele pode armazenar peças de qualquer tipo
*
*  $EP Parâmetros
*     * pTabuleiro - ponteiro para tabuleiro passado como referencia
*
*  $FV Valor retornado
*     TAB_CondRetOK - Se executou corretamente a criaçao do tabuleiro
*     TAB_CondRetFaltouMemoria - Se houve algum problema de memoria
***********************************************************************/

/* Assertivas de Entrada TAB_CriaTabuleiro_Ludo
*  Ter memoria suficiente para criacao da estrutura de tabuleiro
*  O tabuleiro passado como parâmetro faz sentido
*
*  Fim Assertivas de Entrada TAB_CriaTabuleiro_Ludo */

TAB_CondRet TAB_CriaTabuleiro_Ludo( TAB_tpLudo * pTabuleiro ) ; 

/* Assertivas de Saida TAB_CriaTabuleiro_Ludo
*  A memoria referente a estrutura do tabuleiro tem que ser alocada
*  A funcao retornara um TAB_CondRet
*
*  Fim Assertiva de Saida TAB_CriaTabuleiro_Ludo */

/***********************************************************************
*
*  $FC Função: TAB  &Mover peca
*
*  $ED Descrição da função
*     Move uma peca na casa do tabuleiro para outra casa.
*
*  $EP Parâmetros
*     pTabuleiro - ponteiro para tabuleiro a ser modificado
*     pPeca      - ponteiro para a peca a ser movimentada
*     n            - numero de movimentos a andar com a peça
*
*  $FV Valor retornado
*     TAB_CondRetOK - se conseguiu mover corretamente
*     TAB_CondRetPecaMorta - se a peca estiver fora de jogo
*     TAB_CondRetNaoEncontrouPeca - se a peça que não é morta não é achada no tabuleiro
*     TAB_CondRetMovimentoInvalido - se nao foi possivel mover peca
*
***********************************************************************/

/* Assertiva de Entrada TAB_MovePeca
*  Existir um tabuleiro ja criado
*  Existir uma peça passada como parâmetro
*  Existir pelo menos uma casa no tabuleiro para qual essa peça pode se mover.
*
*  Fim Assertiva de Entrada TAB_MovePeca */

TAB_CondRet TAB_MovePeca( TAB_tpLudo pTabuleiro, PEC_tpPeca pPeca , int n ) ;

/* Assertiva de Saida TAB_MovePeca
*  A funcao retornara um TAB_tpCondRet
*
*  Fim Assertiva de Saida TAB_MovePeca */

/***********************************************************************
*
*  $FC Função: TAB  &Insere Peca no Inicio
*
*  $ED Descrição da função
*     Insere uma peca no inicio do tabuleiro de sua cor
*
*  $EP Parâmetros
*     pTabuleiro - poonteiro para tabuleiro a ser trabalhado
*     pPeca - ponteiro para a peça a ser inserida
*
*  $FV Valor retornado
*     TAB_CondRetOK - se conseguiu inserir corretamente
*     TAB_CondRetMovimentoInvalido - se nao pode inserir peca neste local
*
***********************************************************************/

/* Assertivas de Entrada TAB_InserePecaInicio
*  Existir Tabuleiro ja criado
*  Existir peca a ser inserida no tabuleiro
*
*  Fim Assertiva de Entrada TAB_InserePecaInicio  */

TAB_CondRet TAB_InserePecaInicio ( TAB_tpLudo pTabuleiro , PEC_tpPeca pPeca ) ;

/* Assertiva de Saida TAB_InserePecaInicio
*  Inseriu a peça no inicio do tabuleiro
*  A funcao retornara um TAB_CondRet
*
*  Fim Assertiva de Saida TAB_InserePecaInicio */

/***********************************************************************
*
*  $FC Função: TAB  &Gera Valor
*
*  $ED Descrição da função
*     Gera valor de 1 a 6 de um dado.
*
*  $EP Parâmetros
*      * pValor -  ponteiro para endereço onde será armazenado o valor
*                    o valor aleatório gerado pelo dado.
*
*  $FV Valor retornado
*     TAB_CondRetOK - Se valor está dentro do padrão (Número de 1 a 6)	  
*		
***********************************************************************/

/* Assertiva de Entrada TAB_LancaDado
*  Endereço passado como parâmetro deve fazer referência correta.
*
*  Fim Assertiva de Entrada TAB_LancaDado */

TAB_CondRet TAB_LancaDado ( int * pValor ) ;

/* Assertiva de Saida TAB_LancaDado
*  O valor gerado deverá ser corretamente armazenado em pValor.
*  A funcao retorna um TAB_CondRet.
*
*  Fim Assertiva de Saida TAB_LancaDado */

/***********************************************************************
*
*  $FC Função: TAB  &Destroi tabuleiro
*
*  $ED Descrição da função
*     Destrói o tabuleiro criado.
*
*  $EP Parâmetros
*     pTabuleiro - vetor de tabuleiro passado como referencia	  
*
*  $FV Valor retornado
*     TAB_CondRetOK - destruiu
*
***********************************************************************/

/* Assertivas de entrada TAB_DestruirTabuleiro
*  Existir um tabuleiro ja criado
* 
*  Fim Assertivas de Entrada TAB_DestruirTabuleiro */

TAB_CondRet TAB_DestruirTabuleiro ( TAB_tpLudo pTabuleiro ) ;

/*  Assertiva de Saida TAB_DestruirTabuleiro
*   O tabuleiro deve ser destruido
*	Para todo pTabuleiro, pTabuleiro = NULL
*   A memoria deve ser liberada para todo pTabuleiro
*   A funcao retorna um TAB_CondRet
*
*   Fim Assertiva de Saida TAB_DestruirTabuleiro */


#undef TABULEIRO_EXT


/*********** Fim do módulo de definição: TAB Modulo Tabuleiro **********/


#else
#endif
