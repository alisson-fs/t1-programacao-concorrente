#include "equipe.h"

/**
 * ATENÇÃO: Você pode adicionar novas funções com PUBLIC para serem usadas por
 * outros arquivos e adicionar a assinatura da função no .h referente.
 */

/*============================================================================*
 * equipe_setup()                                                             *
 *============================================================================*/

/**
 * @brief Configura a estrutura de equipe.
 *
 * @param jogadores_por_equipe Número de jogadores por equipe.
 */
PUBLIC void equipe_setup(equipe_t * equipe, equipe_id_t id, int njogadores)
{
	assert(njogadores > 0);
	assert(id == EQUIPE_A || id == EQUIPE_B);

	equipe->id = id;
	equipe->capacidade = njogadores;

	arranjo_iniciar(&equipe->jogadores, equipe->capacidade);
}

/*============================================================================*
 * equipe_cleanup()                                                           *
 *============================================================================*/

/**
 * @brief Limpa equipe.
 */
PUBLIC void equipe_cleanup(equipe_t * equipe)
{
	assert(equipe->id == EQUIPE_A || equipe->id == EQUIPE_B);

	arranjo_destruir(&equipe->jogadores);
}
