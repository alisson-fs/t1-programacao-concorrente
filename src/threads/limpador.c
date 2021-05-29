#include "limpador.h"

/**
 * ATENÇÃO: Você pode adicionar novas funções com PUBLIC para serem usadas por
 * outros arquivos e adicionar a assinatura da função no .h referente.
 */

/*============================================================================*
 * limpador_setup()                                                           *
 *============================================================================*/

/**
 * @brief Configura os recursos locais do limpador caso existam.
 */
PUBLIC void limpador_setup(void)
{
}

/*============================================================================*
 * limpador_cleanup()                                                         *
 *============================================================================*/

/**
 * @brief Limpa os recursos locais do limpador caso existam.
 */
PUBLIC void limpador_cleanup(void)
{
}

/*============================================================================*
 * limpador_requisita_limpeza()                                               *
 *============================================================================*/

/**
 * @brief Requisita a limpeza de equipamentos.
 *
 * @param equipamentos Equipamentos para limpeza.
 *
 * Descrição: Os equipamentos devem ser passados para o limpador nesta função.
 */
PUBLIC void limpador_requisita_limpeza(equipamentos_t * equipamentos)
{
	assert(equipamentos);

	// Requisita limpeza.
	
	// Coloca na prateleira.
	prateleira_libera_equipamentos(equipamentos);
	
	// Tira equipamentos do jogador.
	equipamentos->arma     = -1;
	equipamentos->capacete = -1;
	equipamentos->colete   = -1;
}

/*============================================================================*
 * Responsabilidades do Limpador.                                             *
 *============================================================================*/

/**
 * @brief Main do limpador.
 *
 * Descrição: O limpador deve esperar equipamentos para limpar enquanto
 * houverem partidas e jogadores. Quando seu trabalho terminar, o mesmo deve
 * sair.
 */
PUBLIC void * limpador_fn(void * arg)
{
	// Loop para rodar a quantidade de partidas passadas como parametro.
	for (int i = 0; i < params->partidas_max; i++) {
		// Aguarda os jogadores liberarem os equipamentos.
		sem_wait(&partida->aguarda_limpeza);

		// Loop para limpar equipamento de cada jogador.
		for (int j = 0; j < params->jogadores_por_equipe; j++) {
			jogador_t * jogador_a = (jogador_t*)arranjo_consultar(&partida->equipe_a.jogadores, j);
			jogador_t * jogador_b = (jogador_t*)arranjo_consultar(&partida->equipe_b.jogadores, j);
			limpador_requisita_limpeza(&jogador_a->equipamentos);
			limpador_requisita_limpeza(&jogador_b->equipamentos);
		}
		
		// Libera jogadores para irem embora.
		for (int k = 0; k < 2*params->jogadores_por_equipe; k++) {
			sem_post(&partida->jogadores_liberados);
		}
		// Incrementa quantidade de equipamentos.
		for (int l = 0; l < 2*params->jogadores_por_equipe; l++) {
			sem_post(&partida->quantidade_equipamentos);
		}
	}
	return (NULL);
}
