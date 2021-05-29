#include "config.h"
#include "porteiro.h"
#include "limpador.h"
#include "gerente.h"
#include "partida.h"

/*============================================================================*
 * Definição das variáveis globais (publicas ou privadas)                     *
 *============================================================================*/

/**
 * Parâmetros de uma execução.
 */
PUBLIC config_t * params;
PUBLIC sim_t * sim;

/**
 * Funções auxiliares.
 */
PRIVATE int execucao_setup(int argc, char * argv[]);
PRIVATE void execucao_cleanup(void);

/*============================================================================*
 * Responsabilidades do Porteiro.                                             *
 *============================================================================*/

/**
 * Função Main
 *
 * Objetivos: Alocar e configurar as variáveis globais e spawnar as threads
 * básicas do trabalho.
 */
int main(int argc, char* argv[])
{
	pthread_t tids[3];

	plog("[main] Programa iniciando\n");

	if (execucao_setup(argc, argv) < 0) {
		return (-1);
	}

	aleatorio_semente(params->semente);

	prateleira_setup();
	partida_setup();

	gerente_setup();
	limpador_setup();
	porteiro_setup();

	pthread_create(&tids[0], NULL, limpador_fn, NULL);
	pthread_create(&tids[1], NULL, gerente_fn,  NULL);
	pthread_create(&tids[2], NULL, porteiro_fn, NULL);

	for (int i = 0; i < 3; ++i) {
		pthread_join(tids[i], NULL);
	}

	porteiro_cleanup();
	limpador_cleanup();
	gerente_cleanup();

	partida_cleanup();
	prateleira_cleanup();

	execucao_cleanup();
	
	plog("[main] Programa terminou com sucesso!\n");

	return (0);
}

/**
 * Configura parâmetros.
 */
PRIVATE int execucao_setup(int argc, char * argv[])
{
	int i, nparams, aux;
	const int * base;

	params = (config_t *) malloc(sizeof(config_t));
	sim    = (sim_t *) malloc(sizeof(sim_t));

	/* Configura parâmetros. */
	config_t default_params = {
		.jogadores_por_equipe = DEFAULT_JOGADORES_POR_EQUIPE,
		.grupo_min            = DEFAULT_GRUPO_MIN,
		.grupo_max            = DEFAULT_GRUPO_MAX,
		.dano_min             = DEFAULT_DANO_MIN,
		.dano_max             = DEFAULT_DANO_MAX,
		.dano_cura            = DEFAULT_DANO_CURA,
		.delay_min            = DEFAULT_DELAY_MIN,
		.delay_max            = DEFAULT_DELAY_MAX,
		.delay_gerente        = DEFAULT_DELAY_GERENTE,
		.delay_limpador       = DEFAULT_DELAY_LIMPADOR,
		.partidas_max         = DEFAULT_PARTIDAS_MAX,
		.partida_tempo_max    = DEFAULT_PARTIDA_TEMPO_MAX,
		.semente              = DEFAULT_SEMENTE
	};

	memcpy((void *) params, (void *) &default_params, sizeof(config_t));

	/* Lê entrada. */
	if (argc > 1)
	{
		for (i = 1; i < argc; ++i)
		{
			if (argv[i][0] != '-')
				goto error;

			switch (argv[i][1])
			{
				case 'j':
				{
					nparams = 1;
					base    = (const int *) &params->jogadores_por_equipe;
				} break;

				case 'g':
				{
					nparams = 2;
					base    = (const int *) &params->grupo_min;
				} break;

				case 'd':
				{
					nparams = 3;
					base    = (const int *) &params->dano_min;
				} break;

				case 'c':
				{
					nparams = 4;
					base    = (const int *) &params->delay_min;
				} break;

				case 'p':
				{
					nparams = 2;
					base    = (const int *) &params->partidas_max;
				} break;

				case 's':
				{
					nparams = 1;
					base    = (const int *) &params->semente;
				} break;

				case 'h':
					i = -1;
					goto error;

				default:
					goto error;
			}

			for (int j = 0; j < nparams; ++j)
			{
				/* Lista de parâmetros chegou ao fim. */
				if (++i == argc)
					goto error;

				/* Lê parâmetro. */
				aux = atoi(argv[i]);

				/* Escreve parâmetros. */
				memcpy((void *) (base + j), (void *) &aux, sizeof(int));
			}
		}
	}

	/* Configura contadores. */
	memset(sim, 0, sizeof(sim_t));
	pthread_mutex_init(&sim->lock, NULL);

	/* Printa informações. */
	plog(SEPARADOR);
	plog("[main][params] Parametros da execução:\n");
	plog("[main][params] Jogadores por equipe:     %d\n",    params->jogadores_por_equipe);
	plog("[main][params] Grupo mínimo:             %d\n",    params->grupo_min);
	plog("[main][params] Grupo máximo:             %d\n",    params->grupo_max);
	plog("[main][params] Dano mínimo:              %d\n",    params->dano_min);
	plog("[main][params] Dano máximo:              %d\n",    params->dano_max);
	plog("[main][params] Cura de dano:             %d\n",    params->dano_cura);
	plog("[main][params] Delay mínimo:             %d ms\n", params->delay_min);
	plog("[main][params] Delay máximo:             %d ms\n", params->delay_max);
	plog("[main][params] Delay gerente:            %d ms\n", params->delay_gerente);
	plog("[main][params] Delay limpador:           %d ms\n", params->delay_limpador);
	plog("[main][params] Número de partidas:       %d\n",    params->partidas_max);
	plog("[main][params] Tempo máximo por partida: %d ms\n", params->partida_tempo_max);
	plog("[main][params] Semente aleatória:        %d\n",    params->semente);
	plog(SEPARADOR);

	/* Paramêtros mínimos para a execução. */
	assert(params->jogadores_por_equipe > 0);
	assert(params->partidas_max         > 0);
	assert(params->partida_tempo_max    > 0);

	/* Sucesso. */
	return (0);

error:
	if (i >= 0) {
		plog("[main] Parâmetro %d incorreto:                           \n", i);
		plog("[main] Deveria ser uma configuração:                     \n");
	} else {
		plog("[main] Você pode configurar as seguintes opções:         \n");
	}
	plog("[main] 	-j jogadores_por_equipe                            \n");
	plog("[main] 	-g grupo_min grupo_max                             \n");
	plog("[main] 	-d dano_min dano_max dano_cura                     \n");
	plog("[main] 	-c delay_min delay_max delay_gerente delay_limpador\n");
	plog("[main] 	-p partidas_max partida_tempo_max                  \n");
	plog("[main] 	-s semente                                         \n");
	plog("[main] 	-h imprime ajuda.                                  \n");

	/* Fracasso. */
	return (-1);
}

/**
 * Libera parâmetros.
 */
PRIVATE void execucao_cleanup(void)
{
	/* Printa contadores. */
	plog(SEPARADOR);
	plog("[main][sim] Contadores da execução:    \n");
	plog("[main][sim] Jogadores criados:       %d\n", sim->jogadores_criados);
	plog("[main][sim] Jogadores destruidos:    %d\n", sim->jogadores_destruidos);
	plog("[main][sim] Jogadores curados:       %d\n", sim->jogadores_curados);
	plog("[main][sim] Jogadores mortos:        %d\n", sim->jogadores_mortos);
	plog("[main][sim] Quant. partidas jogadas: %d\n", sim->partidas_jogadas);
	plog("[main][sim] Tempo jogado:            %d/%d\n",
		sim->tempo_jogado,
		(params->partidas_max * params->partida_tempo_max)
	);
	plog(SEPARADOR);

	pthread_mutex_destroy(&sim->lock);

	free((void *) sim);
	free((void *) params);
}

