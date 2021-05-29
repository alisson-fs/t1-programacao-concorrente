#include "gerente.h"

/**
 * ATENÇÃO: Você pode adicionar novas funções com PUBLIC para serem usadas por
 * outros arquivos e adicionar a assinatura da função no .h referente.
 */

/*============================================================================*
 * Protótipo das funções locais.                                              *
 *============================================================================*/

PRIVATE void gerente_coordena_partida(void);
PRIVATE void gerente_verifica_equipes(void);

/*============================================================================*
 * gerente_setup()                                                            *
 *============================================================================*/

/**
 * @brief Configura os recursos locais do gerente se houverem.
 */
PUBLIC void gerente_setup(void)
{
}

/*============================================================================*
 * gerente_cleanup()                                                          *
 *============================================================================*/

/**
 * @brief Limpa os recursos locais do gerente se houverem.
 */
PUBLIC void gerente_cleanup(void)
{
}

/*============================================================================*
 * Responsabilidades do Gerente.                                              *
 *============================================================================*/

/**
 * @brief Main do gerente.
 *
 * Descrição: O Gerente deve coordenar as partidas, ou seja:
 * - Esperar que as equipes se formarem.
 * - Iniciar a partida.
 * - Enquanto o tempo de partida não ultrapassar params->partida_tempo_max
 *   e ainda existem jogadores vivos em ambas as equipes:
 * --- Esperar params->delay_gerente
 * --- Perioricamente, curar todos os jogadores vivos com params->dano_cura.
 *
 * ATENÇÃO: Você deve incrementar os contadores do sim_t referente a partida
 * e jogadores curados.
 */
PUBLIC void * gerente_fn(void * arg)
{
	plog("[gerente] Iniciou.\n");

	if (false) {
		gerente_coordena_partida();
	}

	// Loop para rodar a quantidade de partidas passadas como parametro.
	while (params->partidas_max - sim->partidas_jogadas != 0) {
		// Define os valores iniciais de inicio de partida.
		partida->equipe_a.jogadores_vivos = params->jogadores_por_equipe;
		partida->equipe_b.jogadores_vivos = params->jogadores_por_equipe;
		
		pthread_mutex_lock(&partida->lock);
		partida->jogadores_mortos = 0;
		partida->jogadores_prontos = 0;
		pthread_mutex_unlock(&partida->lock);
		
		// Espera equipes ficarem prontas.
		gerente_verifica_equipes();

		// Liberando os jogadores para irem jogar.
		for (int i = 0; i < 2*params->jogadores_por_equipe; i++) {
			sem_post(&partida->espera_equipes);
		}

		// Espera os jogadores irem jogar para que o gerente inicie a partida.
		sem_wait(&partida->comeca_partida);
		partida->status = PARTIDA_INICIADA;

		// Libera os jogadores para começar o jogo.
		for (int j = 0; j < 2*params->jogadores_por_equipe; j++) {
			sem_post(&partida->jogadores_jogando);
		}

		// Gerente coordena a partida até o fim.
		gerente_coordena_partida();
		partida->status = PARTIDA_FINALIZADA;

		// Nomeia os vencedores da partida.
		partida_nomeia_vencedores(partida->tempo);

		// Libera jogadores depois que a partida terminou.
		for (int k = 0; k < (2*params->jogadores_por_equipe); k++) {
			sem_post(&partida->espera_terminar);
		}

		// Atualiza os valores da simulação.
		pthread_mutex_lock(&sim->lock);
		sim->tempo_jogado += params->partida_tempo_max - partida->tempo;
		sim->partidas_jogadas++;
		sim->jogadores_mortos += partida->jogadores_mortos;
		pthread_mutex_unlock(&sim->lock);
	}

	return (NULL);
}

/*============================================================================*
 * gerente_cura_jogadores()                                                   *
 *============================================================================*/

/**
 * @brief Gerente cura os jogadores.
 */
PRIVATE int gerente_cura_jogadores(void)
{
	int curados = 0;

	plog("[gerente] Curando jogadores.\n");

	// Loop para curar todos os jogadores.
	for (int i = 0; i < params->jogadores_por_equipe; i++) {
		jogador_t jogador_a = *((jogador_t*)arranjo_consultar(&partida->equipe_a.jogadores, i));
		jogador_t jogador_b = *((jogador_t*)arranjo_consultar(&partida->equipe_b.jogadores, i));
		// Cura jogadores da equipe A.
		if (jogador_a.status != JOGADOR_MORREU && jogador_a.vida < 100) {
			// Verifica se o jogador ficará com mais vida que o total após a cura, caso fique, ele fica com vida total.
			if (jogador_a.vida + params->dano_cura > 100) {
				jogador_a.vida = 100;
			} else {
				jogador_a.vida += params->dano_cura;
			}
			// Incrementa o número de curados.
			curados++;
		}
		// Cura jogadores da equipe B.
		if (jogador_b.status != JOGADOR_MORREU && jogador_b.vida < 100) {
			// Verifica se o jogador ficará com mais vida que o total após a cura, caso fique, ele fica com vida total.
			if (jogador_b.vida + params->dano_cura > 100) {
				jogador_b.vida = 100;
			} else {
				jogador_b.vida += params->dano_cura;
			}
			// Incrementa o número de curados.
			curados++;
		}
	}
	return (curados);
}

/*============================================================================*
 * gerente_coordena_partida()                                                 *
 *============================================================================*/

/**
 * @brief Loop principal da partida.
 */
PRIVATE void gerente_coordena_partida(void)
{
	plog("[gerente] Coordenando partida.\n");

	if (false) {
		gerente_cura_jogadores();
	}
	
	
	partida->tempo = params->partida_tempo_max;
	// Loop para coordenar a partida até que o tempo acabe.
	while (partida->tempo > 0 &&
		  !(partida->equipe_a.jogadores_vivos == 0 ||
		  partida->equipe_b.jogadores_vivos == 0)) {
		// Thread espera delay do gerente.
		msleep(params->delay_gerente);
		// Gerente cura jogadores e recebe número de jogadores curados.
		int curados = gerente_cura_jogadores();
		// Atualiza número de jogadores curados da simulação.
		pthread_mutex_lock(&sim->lock);
		sim->jogadores_curados += curados;
		pthread_mutex_unlock(&sim->lock);
		// Atualiza tempo da partida com o delay do gerente.
		pthread_mutex_lock(&partida->lock);
		partida->tempo -= params->delay_gerente;
		if (partida->tempo < 0) {
			partida->tempo = 0;
		}
		pthread_mutex_unlock(&partida->lock);
	}
}

/*============================================================================*
 * gerente_verifica_equipes()                                                 *
 *============================================================================*/

/**
 * @brief Verifica se as equipes estão prontas.
 */
PRIVATE void gerente_verifica_equipes(void)
{
	// Espera equipes ficarem prontas.
	sem_wait(&partida->equipes_prontas);
	partida->status = PARTIDA_PREPARADA;
}
