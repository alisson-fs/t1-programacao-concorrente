#ifndef __JOGADOR_H__
#define __JOGADOR_H__

	#include "config.h"
	#include "equipe.h"
	#include "prateleira.h"

	/*============================================================================*
	 * Estrutura                                                                  *
	 *============================================================================*/

	/**
	 * @brief Estados de um jogador.
	 */
	typedef enum JogadorStatus
	{
		JOGADOR_ENTRANDO,
		JOGADOR_ESCOLHENDO_EQUIPE,
		JOGADOR_PEGANDO_EQUIPAMENTO,
		JOGADOR_ESPERANDO,
		JOGADOR_JOGANDO,
		JOGADOR_MORREU,
		JOGADOR_LIBERANDO_EQUIPAMENTO,
		JOGADOR_SAINDO
	} jogador_status_t;

	/**
	 * @brief Estrutura do jogador.
	 */
	typedef struct jogador
	{
		/**
		 * @brief Identificadores do jogador.
		 */
		int id;                      /**< Identificador do jogador.         */
		pthread_t tid;               /**< Thread ID do jogador.             */

		/**
		 * @brief Informações da partida do jogador.
		 */
		int vida;                    /**< Porcentagem de vida do jogador.   */
		jogador_status_t status;     /**< Status do jogador.                */
		equipe_id_t equipe;          /**< Equipe de LaserGun.               */

		/**
		 * @brief Equipamentos.
		 */
		equipamentos_t equipamentos; /**< Equipamentos alocados.            */

		/**
		 * @brief Mutex para proteção de escrita.
		 */
		pthread_mutex_t lock;
	} jogador_t;

	/*============================================================================*
	 * Funções padrão exportadas (utilizadas em arquivos que incluem esse .h)     *
	 *============================================================================*/

	/**
	 * @brief Funções.
	 *
	 * @TODO: Verifique no arquivo src/estruturas/jogador.c
	 * e src/threads/jogador.c quais funções você deve
	 * implementar/complementar.
	 */
	EXTERN void jogador_setup(jogador_t * jogador, int id);
	EXTERN void jogador_cleanup(jogador_t * jogador);

	/**
	 * @brief Main do Jogador.
	 */
	EXTERN void * jogador_fn(void * arg);

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

#endif /*__JOGADOR_H__*/
