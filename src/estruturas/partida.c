#include "partida.h"

/**
 * ATENÇÃO: Você pode adicionar novas funções com PUBLIC para serem usadas por
 * outros arquivos e adicionar a assinatura da função no .h referente.
 */

/*============================================================================*
 * Definição das variáveis globais (públicas ou privadas)                     *
 *============================================================================*/

/**
 * ATENÇÃO: Você pode adicionar novas funções com PUBLIC para serem usadas por
 * outros arquivos e adicionar a assinatura da função no .h referente.
 */

/**
 * @brief Definição de variáveis globais.
 */
PUBLIC partida_t * partida;

/*============================================================================*
 * partida_setup()                                                            *
 *============================================================================*/

/**
 * @brief Configura a estrutura de partida.
 */
PUBLIC void partida_setup(void)
{
	assert((partida = (partida_t *) malloc(sizeof(partida_t))) != NULL);

	/**
	 * Setup Equipes.
	 */
	equipe_setup(&partida->equipe_a, EQUIPE_A, params->jogadores_por_equipe);
	equipe_setup(&partida->equipe_b, EQUIPE_B, params->jogadores_por_equipe);

	/**
	 * Setup Atributos da partida.
	 */
	partida->status = PARTIDA_NAO_PREPARADA;
	partida->equipamentos_liberados = 0;
	sim->jogadores_mortos = 0;

	/**
	 * Inicia os semaforos e mutexes
	 */
	sem_init(&partida->espera_equipes, 0, 0);
	sem_init(&partida->espera_terminar, 0, 0);
	sem_init(&partida->jogadores_jogando, 0, 0);
	sem_init(&partida->aguarda_limpeza, 0, 0);
	sem_init(&partida->capacidade_equipes, 0, params->jogadores_por_equipe*2);
	sem_init(&partida->quantidade_equipamentos, 0, params->jogadores_por_equipe*2);
	sem_init(&partida->equipes_prontas, 0, 0);
	sem_init(&partida->comeca_partida, 0, 0);
	sem_init(&partida->jogadores_liberados, 0, 0);
	pthread_mutex_init(&partida->lock, NULL);
}

/*============================================================================*
 * partida_cleanup()                                                          *
 *============================================================================*/

/**
 * @brief Limpa os recursos de uma partida.
 */
PUBLIC void partida_cleanup(void)
{
	/**
	 * Cleanup Equipes.
	 */
	equipe_cleanup(&partida->equipe_a);
	equipe_cleanup(&partida->equipe_b);

	/**
	 * Destroi os semaforos e mutexes.
	 */
	sem_destroy(&partida->espera_equipes);
	sem_destroy(&partida->espera_terminar);
	sem_destroy(&partida->jogadores_jogando);
	sem_destroy(&partida->aguarda_limpeza);
	sem_destroy(&partida->capacidade_equipes);
	sem_destroy(&partida->equipes_prontas);
	sem_destroy(&partida->comeca_partida);
	sem_destroy(&partida->jogadores_liberados);
	sem_destroy(&partida->quantidade_equipamentos);
	pthread_mutex_destroy(&partida->lock);

	/* Libera partida. */
	free(partida);
}

/*============================================================================*
 * partida_status()                                                           *
 *============================================================================*/

/**
 * @brief Verifica o status da partida.
 *
 * @return Retorna o status da partida.
 */
PUBLIC partida_status_t partida_status(void)
{
	partida_status_t status;

	status = partida->status;

	return (status);
}

/*============================================================================*
 * partida_nomeia_vencedores()                                                *
 *============================================================================*/

/**
 * @brief Imprime equipe vencedora.
 */
PRIVATE void partida_print_resultado(int tempo_restante, int sobreviventes, partida_resultado_t res)
{
	switch (res)
	{
		case PARTIDA_RESULTADO_EQUIPE_A_VENCEU:
			plog("[resultado] Partida %d: Equipe A venceu com %d sobreviventes! (tempo %d/%d)\n",
				sim->partidas_jogadas,
				sobreviventes,
				tempo_restante,
				params->partida_tempo_max
			);
			break;

		case PARTIDA_RESULTADO_EQUIPE_B_VENCEU:
			plog("[resultado] Partida %d: Equipe B venceu com %d sobreviventes! (tempo %d/%d)\n",
				sim->partidas_jogadas,
				sobreviventes,
				tempo_restante,
				params->partida_tempo_max
			);
			break;

		case PARTIDA_RESULTADO_EMPATOU:
			plog("[resultado] Partida %d: Ocorreu um empate, quantidade de jogadores em cada equipe %d (tempo %d/%d)\n",
				sim->partidas_jogadas,
				sobreviventes,
				tempo_restante,
				params->partida_tempo_max
			);
			break;

		default:
			assert(false);
			break;
	}

	fflush(stdout);
}

/*============================================================================*
 * partida_conta_vida()                                                *
 *============================================================================*/

/**
 * @brief Conta vida total da equipe.
 */

PUBLIC int partida_conta_vida(equipe_t * equipe)
{
	// Soma total da vida dos jogadores da equipe
	int vida_equipe = 0;
	for (int i = 0; i < params->jogadores_por_equipe; i++) {
		jogador_t * jogador = (jogador_t*)arranjo_consultar(&equipe->jogadores, i);
		vida_equipe += jogador->vida;
	}
	return vida_equipe;
}


/*============================================================================*
 * partida_nomeia_vencedores()                                                *
 *============================================================================*/

/**
 * @brief Verifica qual equipe venceu e imprime o resultado informando o tempo
 * restante da partida, a quantidade de sobreviventes na equipe vencedora (ou
 * em cada equipe se ouver empate) e o número da partida.
 *
 * Condições de vitória:
 * - Se ambas as equipes tiverem a mesma quantidade de jogadores vivos, ocorre
 *   um empate.
 * - Se uma equipe tiver 0 jogadores vivos, a outra equipe vence.
 *
 * Utilize a função partida_print_resultado para te auxiliar.
 */
PUBLIC void partida_nomeia_vencedores(int tempo_restante)
{
	if (false) {
		partida_print_resultado(0, 0, PARTIDA_RESULTADO_INDEFINIDO);
	}

	// Soma total da vida dos jogadores de cada equipe.
	int vida_equipe_a = partida_conta_vida(&partida->equipe_a);
	int vida_equipe_b = partida_conta_vida(&partida->equipe_b);

	if (tempo_restante != 0) { // Se o tempo não acabou, vence a quipe que ainda possui jogadores vivos.
		if (partida->equipe_b.jogadores_vivos == 0) {
			partida_print_resultado(tempo_restante, partida->equipe_a.jogadores_vivos, PARTIDA_RESULTADO_EQUIPE_A_VENCEU);
		} else {
			partida_print_resultado(tempo_restante, partida->equipe_b.jogadores_vivos, PARTIDA_RESULTADO_EQUIPE_B_VENCEU);
		}
	} else { // Se o tempo acabou, vence quem tem mais jogadores vivos e em caso de empate, vence quem possui mais vida total na equipe.
		if (partida->equipe_a.jogadores_vivos > partida->equipe_b.jogadores_vivos) {
			partida_print_resultado(tempo_restante, partida->equipe_a.jogadores_vivos, PARTIDA_RESULTADO_EQUIPE_A_VENCEU);
		} else if (partida->equipe_a.jogadores_vivos < partida->equipe_b.jogadores_vivos) {
			partida_print_resultado(tempo_restante, partida->equipe_b.jogadores_vivos, PARTIDA_RESULTADO_EQUIPE_B_VENCEU);
		} else if (vida_equipe_a > vida_equipe_b) {
			partida_print_resultado(tempo_restante, partida->equipe_a.jogadores_vivos, PARTIDA_RESULTADO_EQUIPE_A_VENCEU);
		} else if (vida_equipe_a < vida_equipe_b) {
			partida_print_resultado(tempo_restante, partida->equipe_b.jogadores_vivos, PARTIDA_RESULTADO_EQUIPE_B_VENCEU);
		} else {
			partida_print_resultado(tempo_restante, partida->equipe_a.jogadores_vivos, PARTIDA_RESULTADO_EMPATOU);
		}
	}
}
