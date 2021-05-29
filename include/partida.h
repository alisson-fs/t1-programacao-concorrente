#ifndef __PARTIDA_H__
#define __PARTIDA_H__

	#include "config.h"
	#include "equipe.h"
	#include "jogador.h"

	/*============================================================================*
	 * Estrutura                                                                  *
	 *============================================================================*/

	/**
	 * @brief Estados de uma partida.
	 */
	typedef enum PartidaStatus
	{
		PARTIDA_NAO_PREPARADA,
		PARTIDA_PREPARADA,
		PARTIDA_INICIADA,
		PARTIDA_FINALIZADA
	} partida_status_t;

	/**
	 * @brief Resultados de uma partida.
	 */
	typedef enum PartidaResultado
	{
		PARTIDA_RESULTADO_EQUIPE_A_VENCEU,
		PARTIDA_RESULTADO_EQUIPE_B_VENCEU,
		PARTIDA_RESULTADO_EMPATOU,
		PARTIDA_RESULTADO_INDEFINIDO
	} partida_resultado_t;

	/**
	 * @brief Estrutura da uma partida.
	 */
	typedef struct partida
	{
		/**
		 * @brief Equipes.
		 */
		equipe_t equipe_a;         /**< Equipe A.          */
		equipe_t equipe_b;         /**< Equipe B.          */

		/**
		 * @brief Estados de uma partida.
		 */
		partida_status_t status;   /**< Estado da partida. */

		/**
		 * @brief Semaforo de espera equipes se formarem.
		 */
		sem_t espera_equipes;

		/**
		 * @brief Semaforo de espera partida terminar.
		 */
		sem_t espera_terminar;

		/**
		 * @brief Semaforo que espera todos os jogadores estarem jogando.
		 */
		sem_t jogadores_jogando;

		/**
		 * @brief Mutex para aguardar o momento de requisitar limpeza.
		 */
		sem_t aguarda_limpeza;

		/**
		 * @brief Semaforo para controlar tamanho das equipes.
		 */
		sem_t capacidade_equipes;

		/**
		 * @brief Semaforo para controlar tamanho das equipes.
		 */
		sem_t quantidade_equipamentos;

		/**
		 * @brief Semaforo que define se as equipes estão prontas.
		 */
		sem_t equipes_prontas;

		/**
		 * @brief Variavel que define quantos jogadores estão prontos.
		 */
		int jogadores_prontos;

		/**
		 * @brief Flag que define se é o ultimo jogador.
		 */
		int ultimo;

		/**
		 * @brief Semaforo que define quando gerente pode iniciar partida.
		 */
		sem_t comeca_partida;

		/**
		 * @brief Variavel de tempo jogado.
		 */
		int tempo;

		/**
		 * @brief Variavel de jogadores mortos na partida.
		 */
		int jogadores_mortos;

		/**
		 * @brief Variavel que define quantos equipamentos estão liberados para limpeza.
		 */
		int equipamentos_liberados;

		/**
		 * @brief Semaforo que define se os jogadores ja podem ser liberados.
		 */
		sem_t jogadores_liberados;

		/**
		 * @brief Mutex para proteção de escrita.
		 */
		pthread_mutex_t lock;
	} partida_t;

	/**
	 * @brief Variável global da partida.
	 *
	 * @details Essa variável agrupa as equipes e variáveis de proteção para
	 * coordenar as ações dos jogadores.
	 */
	EXTERN partida_t * partida;

	/*============================================================================*
	 * Funções padrão exportadas (utilizadas em arquivos que incluem esse .h)     *
	 *============================================================================*/

	/**
	 * @brief Funções.
	 *
	 * @TODO: Verifique no arquivo src/estruturas/partida.c quais funções você
	 * deve implementar/complementar.
	 */
	EXTERN void partida_setup(void);
	EXTERN void partida_cleanup(void);
	EXTERN int partidas_restantes(void);
	EXTERN partida_status_t partida_status(void);
	EXTERN void partida_nomeia_vencedores(int);
	EXTERN int partida_conta_vivos(equipe_t * equipe);
	EXTERN int partida_conta_vida(equipe_t * equipe);

	/*============================================================================*
	 * Funções extra exportadas (utilizadas em arquivos que incluem esse .h)      *
	 *                                                                            *
	 * ATENCÃO: Insira aqui funções que você quiser adicionar a interface para    *
	 * serem usadas em arquivos que incluem esse header.                          *
	 *                                                                            *
	 * Você pode defini-las EXTERN assinatura (.h) + PUBLIC implementação (.c)    *
	 * ou usar diretamente extern assinatura (.h) + implementacao (.c).           *
	 * O uso dessas macros são para avaliação das funções já estabelecidas e não  *
	 * de novas funções que você precisar.                                        *
	 *============================================================================*/

#endif /*__PARTIDA_H__*/
