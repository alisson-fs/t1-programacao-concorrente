#ifndef __CONFIG__
#define __CONFIG__

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <assert.h>
	#include <stdbool.h>
	#include <time.h>

	#include <pthread.h>
	#include <semaphore.h>

	/**
	 * ATENÇÃO: Não altere essas constantes.
	 */

	/*============================================================================*
	 * Constantes                                                                 *
	 *============================================================================*/

	/**
	 * @brief Modificadores de visualização de funções.
	 */
	#define EXTERN  extern /**< Torna uma definição visível por outros arquivos que enxergam esse EXTERN. */
	#define PRIVATE static /**< Força que uma definição não possa ser chamada por outros arquivos.          */
	#define PUBLIC         /**< Permite que a definição seja exportada (complemento do EXTERN).            */

	/**
	 * @brief Time converter.
	 */
	#define SECOND_TO_MILI(t) ((t) * 1000)
	#define MILI_TO_SECOND(t) ((t) / 1000)
	#define MILI_TO_NANO(t)   ((t) * 1000000)

	/**
	 * @brief Valor padrão no número de jogadores.
	 */
	#ifndef DEFAULT_JOGADORES_POR_EQUIPE
	#define DEFAULT_JOGADORES_POR_EQUIPE 25
	#endif
	#ifndef DEFAULT_GRUPO_MIN
	#define DEFAULT_GRUPO_MIN 1
	#endif
	#ifndef DEFAULT_GRUPO_MAX
	#define DEFAULT_GRUPO_MAX 4
	#endif

	/**
	 * @brief Valores padrões de dano.
	 */
	#ifndef DEFAULT_DANO_MIN
	#define DEFAULT_DANO_MIN  1
	#endif
	#ifndef DEFAULT_DANO_MAX
	#define DEFAULT_DANO_MAX  10
	#endif
	#ifndef DEFAULT_DANO_CURA
	#define DEFAULT_DANO_CURA 5
	#endif

	/**
	 * @brief Valores padrões de delay.
	 */
	#ifndef DEFAULT_DELAY_MIN
	#define DEFAULT_DELAY_MIN  1
	#endif
	#ifndef DEFAULT_DELAY_MAX
	#define DEFAULT_DELAY_MAX  5
	#endif
	#ifndef DEFAULT_DELAY_GERENTE
	#define DEFAULT_DELAY_GERENTE 3
	#endif
	#ifndef DEFAULT_DELAY_LIMPADOR
	#define DEFAULT_DELAY_LIMPADOR 1
	#endif

	/**
	 * @brief Número padrão de partidas.
	 */
	#ifndef DEFAULT_PARTIDAS_MAX
	#define DEFAULT_PARTIDAS_MAX 10
	#endif

	/**
	 * @brief Tempo máximo de uma partida.
	 */
	#ifndef DEFAULT_PARTIDA_TEMPO_MAX
	#define DEFAULT_PARTIDA_TEMPO_MAX SECOND_TO_MILI(0.5)
	#endif

	/**
	 * @brief Configuração default do gerador de números aleatórios.
	 */
	#ifndef DEFAULT_SEMENTE
	#define DEFAULT_SEMENTE 12345
	#endif

	/*============================================================================*
	 * Macros                                                                     *
	 *============================================================================*/

	/**
	 * @brief Verifica se um número está dentro de um intervalo.
	 */
	#define ENTRE(x, min, max) ((min <= x) && (x < max))

	/**
	 * @brief Printa um log em modo debug.
	 */
	#ifndef NDEBUG
		#define plog(...) printf(__VA_ARGS__); fflush(stdout)
	#else
		#define plog(...)
	#endif

	/**
	 * @brief Serapador.
	 */
	#define SEPARADOR "=====================================================================\n"

	/*============================================================================*
	 * Variáveis de controle globais                                              *
	 *============================================================================*/

	/**
	 * @brief Estrutura com os parametros da execução.
	 */
	typedef struct configuracao
	{
		/**
		 * Jogadores.
		 */
		/**@{*/
		const int jogadores_por_equipe; /**< Número de jogadores por partida.                   */
		const int grupo_min;            /**< Quant. mínima de jogadores criados ao mesmo tempo. */
		const int grupo_max;            /**< Quant. máxima de jogadores criados ao mesmo tempo. */
		/**@}*/

		/**
		 * Dano.
		 */
		/**@{*/
		const int dano_min;             /**< Dano mínimo causado a outro jogador.               */
		const int dano_max;             /**< Dano máximo causado a outro jogador.               */
		const int dano_cura;            /**< Dano recuperado pelo procedimento de cura.         */
		/**@}*/

		/**
		 * Delays.
		 */
		/**@{*/
		const int delay_min;            /**< Delay mínimo padrão. Use quando não especificado.  */
		const int delay_max;            /**< Delay máximo padrão. Use quando não especificado.  */
		const int delay_gerente;        /**< Delay do gerente durante a coordenação da partida. */
		const int delay_limpador;       /**< Delay do limpador liberar um set de equipamentos.  */
		/**@}*/

		/**
		 * Partida.
		 */
		/**@{*/
		const int partidas_max;         /**< Quantidade máxima de partidas.                     */
		const int partida_tempo_max;    /**< Tempo máximo de uma partida.                       */
		/**@}*/

		/**
		 * Outros.
		 */
		/**@{*/
		const int semente;              /**< Semente da sequência de números aleatórios.        */
		/**@}*/
	} config_t;

	/**
	 * @brief Estrutura com os informações sobre a execução.
	 */
	typedef struct simulacao
	{
		/**
		 * Jogadores.
		 */
		/**@{*/
		int jogadores_criados;    /**< Número de jogadores criados.    */
		int jogadores_destruidos; /**< Número de jogadores destruídos. */
		int jogadores_curados;    /**< Número de jogadores curados.    */
		int jogadores_mortos;     /**< Número de jogadores mortos.     */
		/**@}*/

		/**
		 * Partidas.
		 */
		/**@{*/
		int partidas_jogadas;     /**< Quant. partidas concluídas.     */
		int tempo_jogado;         /**< Tempo total (tempo partidas).   */
		/**@}*/

		/**
		 * Proteção.
		 */
		/**@{*/
		pthread_mutex_t lock;    /**< Proteção de escrita.             */
		/**@}*/
	} sim_t;

	/**
	 * @brief Variáveis globais que você pode usar para pegar e escrever
	 * informações sobre a execução.
	 */
	/**@{*/
	EXTERN config_t * params; /**< Parâmetros da execução. */
	EXTERN sim_t * sim;       /**< Contadores da execução. */
	/**@}*/

	/*============================================================================*
	 * Funções auxiliares                                                         *
	 *============================================================================*/

	/**
	 * @brief Inicializa o gerador de números aleatórios.
	 *
	 * @param semente Semente do gerador.
	 */
	static inline void aleatorio_semente(unsigned int semente)
	{
		srand(semente);
	}

	/**
	 * @brief Gerador de um número aleatório dentro de um intervalo.
	 *
	 * @param min Limite inferior.
	 * @param max Limite superior.
	 *
	 * @return Valor x | min <= x < max
	 */
	static inline unsigned int aleatorio(unsigned int min, unsigned int max)
	{
		assert(min <= max);

		return (min + (rand() % max));
	}

	/**
	 * @brief Dorme por um período de milissegundos.
	 *
	 * @param milissegundos Tempo em milissegundos.
	 */
	static inline void msleep(long milissegundos)
	{
	   assert(milissegundos >= 0);

	   struct timespec req;

	   req.tv_sec  = (int) MILI_TO_SECOND(milissegundos);
	   req.tv_nsec = MILI_TO_NANO(milissegundos - SECOND_TO_MILI(req.tv_sec));

	   assert(req.tv_sec >= 0);
	   assert(ENTRE(req.tv_nsec, 0, 999999999L));

	   nanosleep(&req, NULL);
	}

#endif /* CONFIG */
