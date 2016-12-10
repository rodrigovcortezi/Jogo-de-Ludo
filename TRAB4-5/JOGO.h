#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
 *
 *  $MCD Módulo de definição: JOGO Módulo Jogo / Principal
 *
 *  Arquivo gerado:              JOGO.h
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
 *  $ED Descrição do módulo
 *     Este módulo implementa o módulo jogo que contém a implementação
 *       das regras do Jogo de Ludo juntamente com a manipulação das
 *       peças do mesmo.
 *
 *     Módulo responsável pela verificação de vencedores atraves de
 *       quantidade de peças que cada jogador possui na casa final, pela
 *       apresentação do placar ao final de cada partida e principalmente
 *       pela manipiulação e controle das rodadas.
 *
 ***************************************************************************/

#if defined( JOGO_OWN )
#define JOGO_EXT
#else
#define JOGO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um jogo */

typedef struct jogo * JOGO_tpLudo ;

/***********************************************************************
 *
 *  $TC Tipo de dados: JOGO Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções do módulo JOGO.
 *
 ***********************************************************************/

typedef enum {

	JOGO_CondRetOK,
	/* Concluiu corretamente */   

	JOGO_CondRetFaltouMemoria, 
	/* Faltou Memoria */
			   
	JOGO_CondRetNumeroDeJogadoresInvalido,
	/* Número de jogadores inválido */

	JOGO_CondRetCorJaEscolhida,
	/* Cor já foi escolhida por outro jogador */

	JOGO_CondRetCorInvalida
	/* Cor inválida */
   
   } JOGO_CondRet ;

/***********************************************************************
 *
 *  $FC Função: JOGO  &Inicializa Jogo
 *
 *  $ED Descrição da função
 *     Inicializa um jogo de Ludo.
 *
 *  $EP Parâmetros
 *     pJogo     - ponteiro para jogo.
 *      num      - numero referente a quantidade de jogadores.
 *      cor      - cor da peça referente ao jogador.
 *
 *  $FV Valor retornado
 *     JOGO_CondRetOK - Caso a inicialização foi correta.  
 *     JOGO_CondRetFaltouMemoria - Caso tenha faltado memória.
 *     JOGO_CondRetCorJaEscolhida - Caso a cor já tenha sido escolhida.
 *     JOGO_CondRetCorInvalida - Caso a cor indicada seja inválida.
 *     JOGO_CondRetNumeroDeJogadoresInvalido - Caso o numero de jogadores indicado
 *                                               é incorreto.
 *
 ***********************************************************************/

/* Assertivas de Entrada JOGO_InicializaJogo
 *  Ter memoria suficiente para criacao da estrutura.
 *  A quantidade de jogadores a jogar devem estar corretas.
 *  Os ponteiros recebidos como parâmetros devem fazer referência correta
 *
 *  Fim Assertivas de Entrada JOGO_InicializaJogo */

JOGO_CondRet JOGO_InicializaJogo ( JOGO_tpLudo * pJogo , int num , int *cor ) ;

/* Assertivas de Saida JOGO_InicializaJogo
 *  A memoria referente a estrutura tem que ser alocada.
 *  O jogo deverá ter sido corretamente inicializado.
 *  A funcao retornara um JOGO_CondRet
 *
 *  Fim Assertiva de Saida JOGO_InicializaJogo */

/***********************************************************************
 *
 *  $FC Função: JOGO  &Realiza Jogada
 *
 *  $ED Descrição da função
 *     Realiza uma jogada no Jogo de Ludo.
 *
 *  $EP Parâmetros
 *     pJogo     - ponteiro para jogo.
 *      cor      - cor da peça referente ao jogador.
 *
 *  $FV Valor retornado
 *     JOGO_CondRetOK - Caso a jogada foi corretamente relizada. 
 *
 ***********************************************************************/

/* Assertivas de Entrada JOGO_RealizaJogada
 *  O ponteiro recebido como parâmetro deve fazer referência correta.
 *  A cor indicada deverá estar correta.
 *
 *  Fim Assertivas de Entrada JOGO_RealizaJogada */

JOGO_CondRet JOGO_RealizaJogada ( JOGO_tpLudo pJogo , int cor ) ;

/* Assertivas de Saida JOGO_RealizaJogada
 *  A jogada deverá ter sido realizada.
 *  A funcao retornara um JOGO_CondRet
 *
 *  Fim Assertiva de Saida JOGO_RealizaJogada */

/***********************************************************************
 *
 *  $FC Função: JOGO  &Verifica Ganhador
 *
 *  $ED Descrição da função
 *     Verifica a ocorrência de um possível vencedor, ou seja, se
 *       algum jogador tem suas 4 peças na casa final.
 *
 *  $EP Parâmetros
 *     pJogo     - ponteiro para jogo.
 *      cond     - ponteiro para receber a informação se há ou não ganhador.
 *
 *  $FV Valor retornado
 *     JOGO_CondRetOK - Caso tenha informado corretamente. 
 *
 ***********************************************************************/

/* Assertivas de Entrada JOGO_VerificaGanhador
 *  Os ponteiros recebidos como parâmetro devem fazer referência correta.
 *
 *  Fim Assertivas de Entrada JOGO_VerificaGanhador */

JOGO_CondRet JOGO_VerificaGanhador ( JOGO_tpLudo pJogo , int * cond ) ;		

/* Assertivas de Saida JOGO_VerificaGanhador
 *  O ponteiro * cond deverá ser preenchido.
 *  A funcao retornara um JOGO_CondRet.
 *
 *  Fim Assertiva de Saida JOGO_VerificaGanhador */

#undef JOGO_EXT

/****** Fim do módulo de definição: Módulo JOGO ******/

#else
#endif
