#ifndef __EQUIPE_H__
#define __EQUIPE_H__

	#include "config.h"
	#include "arranjo.h"

	/*============================================================================*
	 * Estrutura                                                                  *
	 *============================================================================*/

	/**
	 * @brief Identificação de uma equipe.
	 */
	typedef enum EquipeID
	{
		EQUIPE_INVALIDA,
		EQUIPE_A,
		EQUIPE_B
	} equipe_id_t;

	/**
	 * @brief Estrutura de uma equipe.
	 */
	typedef struct equipe
	{
		/**
		 * @brief Identificador.
		 */
		equipe_id_t id;

		/**
		 * @brief Capacidade máxima de jogadores.
		 */
		int capacidade;

		/**
		 * @brief Arranjo de jogadores que entraram na equipe.
		 */
		arranjo_t jogadores;

		/**
		 * @brief Número de jogadores vivos.
		 */
		int jogadores_vivos;
	} equipe_t;

	/*============================================================================*
	 * Funções padrão exportadas (utilizadas em arquivos que incluem esse .h)     *
	 *============================================================================*/

	EXTERN void equipe_setup(equipe_t * equipe, equipe_id_t id, int njogadores);
	EXTERN void equipe_cleanup(equipe_t * equipe);

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


#endif /*__EQUIPE_H__*/
