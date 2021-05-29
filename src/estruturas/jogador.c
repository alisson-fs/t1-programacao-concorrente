#include "jogador.h"

/**
 * ATENÇÃO: Você pode adicionar novas funções com PUBLIC para serem usadas por
 * outros arquivos e adicionar a assinatura da função no .h referente.
 */

/*============================================================================*
 * jogador_setup()                                                            *
 *============================================================================*/

/**
 * @brief Configura valores padrão de um jogador.
 */
PUBLIC void jogador_setup(jogador_t * jogador, int id)
{
	assert(jogador != NULL);

	/**
	 * Inicialmente o jogador possui 100% de vida, encontra-se no estado
	 * "entrando" e não possui equipe.
	 */
	jogador->id     = id;
	jogador->vida   = 100;
	jogador->status = JOGADOR_ENTRANDO;
	jogador->equipe = EQUIPE_INVALIDA;

	/**
	 * Inicialmente o jogador não possui equipamento.
	 */
	jogador->equipamentos.capacete = -1;
	jogador->equipamentos.colete   = -1;
	jogador->equipamentos.arma     = -1;
}

/*============================================================================*
 * jogador_cleanup()                                                          *
 *============================================================================*/

/**
 * @brief Limpa jogador.
 */
PUBLIC void jogador_cleanup(jogador_t * jogador)
{
}
