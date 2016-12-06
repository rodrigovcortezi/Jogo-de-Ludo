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

typedef struct jogo * JOGO_tpLudo ;


JOGO_CondRet JOGO_InicializaJogo ( JOGO_tpLudo * pJogo , int num , int *cor ) ;

JOGO_CondRet JOGO_RealizaJogada ( JOGO_tpLudo pJogo , int cor ) ;

//JOGO_CondRet JOGO_VerificaGanhador ( JOGO_tpLudo pJogo , int *cond ) ;		

