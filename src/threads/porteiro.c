#include "porteiro.h"

/**
 * ATENÇÃO: Você pode adicionar novas funções com PUBLIC para serem usadas por
 * outros arquivos e adicionar a assinatura da função no .h referente.
 */

/*============================================================================*
 * Definição das variáveis globais (publicas ou privadas)                     *
 *============================================================================*/

PRIVATE int jogadores_saindo;
PRIVATE sem_t catraca;
PRIVATE sem_t checklist;
PRIVATE pthread_mutex_t porta;
PRIVATE jogador_t * jogador_saindo;

/*============================================================================*
 * porteiro_checklist()                                                       *
 *============================================================================*/

/**
 * @brief Jogador notifica termino ao porteiro.
 */
PUBLIC void porteiro_checklist(jogador_t * jogador)
{
	jogador->status = JOGADOR_SAINDO;

	pthread_mutex_lock(&porta);
		jogadores_saindo++;
	pthread_mutex_unlock(&porta);

	sem_wait(&catraca);
		jogador_saindo = jogador;
	sem_post(&checklist);
}

/*============================================================================*
 * verifica_checklist()                                                       *
 *============================================================================*/

/**
 * @brief Verifica se existem jogadores que saíram e
 * que precisam desalocar os seus recursos.
 */
PRIVATE void verifica_checklist(void)
{
	pthread_mutex_lock(&porta);

		while (jogadores_saindo > 0)
		{
			pthread_mutex_unlock(&porta);

			/* Espera jogador assinar o checklist. */
			sem_wait(&checklist);

				/* Verfica que é um jogador válido. */
				assert(jogador_saindo);

				/* Jogadores não podem fazer checklist se não terminaram. */
				assert(jogador_saindo->status == JOGADOR_SAINDO);

				/* Espera jogador terminar. */
				pthread_join(jogador_saindo->tid, NULL);

				/* Limpa jogador. */
				jogador_cleanup(jogador_saindo);

				/* Libera memória do jogador. */
				free(jogador_saindo);

				/* Limpa variável global. */
				jogador_saindo = NULL;

				/* Conta jogador que saiu. */
				sim->jogadores_destruidos++;

			/* Libera catraca. */
			sem_post(&catraca);

			pthread_mutex_lock(&porta);

			/* Anota saída do jogador. */
			jogadores_saindo--;
		}

	pthread_mutex_unlock(&porta);
}

/*============================================================================*
 * Responsabilidades do Porteiro.                                             *
 *============================================================================*/

/**
 * @brief Operações do Porteiro.
 */
PUBLIC void * porteiro_fn(void * arg)
{
	int tamanho_grupo;
	int total_jogadores;
	jogador_t * jogador;

	plog("[porteiro] Iniciou!\n");

	total_jogadores = 2 * params->jogadores_por_equipe * params->partidas_max;

	while (total_jogadores > 0)
	{
		tamanho_grupo = aleatorio(params->grupo_min, params->grupo_max);

		plog("[porteiro] Gerou um grupo de %d jogadores\n", tamanho_grupo);

		/* Criar jogadores do grupo.  */
		for (int i = 0; i < tamanho_grupo && total_jogadores > 0; ++i, --total_jogadores)
		{
			jogador = (jogador_t *) malloc(sizeof(jogador_t));

			jogador_setup(jogador, sim->jogadores_criados++);

			pthread_create(&jogador->tid, NULL, jogador_fn,  (void *) jogador);
		}

		/* Dorme um pouco. */
		msleep(aleatorio(params->delay_min, 2 * params->delay_max));

		/* Verifica se algum jogador já saiu. */
		verifica_checklist();
	}

	/* Espera todos os jogadores saírem. */
	while (sim->jogadores_criados > sim->jogadores_destruidos)
		verifica_checklist();

	assert(sim->jogadores_criados == sim->jogadores_destruidos);

	return (NULL);
}

/*============================================================================*
 * porteiro_setup()                                                           *
 *============================================================================*/

/**
 * @brief Configura o porteiro.
 */
PUBLIC void porteiro_setup(void)
{
	jogadores_saindo = 0;
	jogador_saindo = NULL;

	sem_init(&checklist, 0, 0);
	sem_init(&catraca,   0, 1);

	pthread_mutex_init(&porta, NULL);
}

/*============================================================================*
 * porteiro_cleanup()                                                         *
 *============================================================================*/

/**
 * @brief Limpa porteiro.
 */
PUBLIC void porteiro_cleanup(void)
{
	sem_destroy(&checklist);
	sem_destroy(&catraca);
	pthread_mutex_destroy(&porta);
}
