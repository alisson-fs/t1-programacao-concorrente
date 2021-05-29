#include "prateleira.h"

/**
 * ATENÇÃO: Você pode adicionar novas funções com PUBLIC para serem usadas por
 * outros arquivos e adicionar a assinatura da função no .h referente.
 */

/*============================================================================*
 * Definição das variáveis globais (publicas ou privadas)                     *
 *============================================================================*/

PRIVATE arranjo_t prateleira;
PRIVATE arranjo_t equipamentos_ocupados;


/*============================================================================*
 * prateleira_setup()                                                         *
 *============================================================================*/

/**
 * @brief Configura os recursos locais se existirem.
 */
PUBLIC void prateleira_setup(void)
{
	int n_jogadores = 2*params->jogadores_por_equipe;
	// Arranjo para guardar os equipamentos que estão sendo utilizados.
	arranjo_iniciar(&equipamentos_ocupados, n_jogadores);
	// Arranjo para a prateleira.
	arranjo_iniciar(&prateleira, n_jogadores);
	// Define ID dos equipamentos e aloca a quantidade de equipamentos necessária em uma partida.
	for (int ID = 0; ID < n_jogadores; ID++) {
	 	equipamentos_t * equipamentos = (equipamentos_t *)malloc(sizeof(equipamentos_t));
		equipamentos->colete = ID;
		equipamentos->capacete = ID;
		equipamentos->arma = ID;
		arranjo_colocar(&prateleira, equipamentos);
	}
}

/*============================================================================*
 * prateleira_setup()                                                         *
 *============================================================================*/

/**
 * @brief Limpa os recursos locais se existirem.
 */
PUBLIC void prateleira_cleanup(void)
{
	/**
	 * ATENÇÃO: A quantidade de equipamentos de cada tipo ao final da execução
	 * do programa deve ser igual a quantidade inicial.
	 */
	arranjo_destruir(&equipamentos_ocupados);
	arranjo_destruir(&prateleira);
}

/*============================================================================*
 * prateleira_pega_equipamentos()                                             *
 *============================================================================*/

/**
 * @brief Pega equipamentos.
 *
 * @return equipamentos Slot de equipamentos de um jogador.
 *
 * Descrição: O jogador deve tentar pegar da prateleira os equipamentos
 * necessários. Especificamente, um de cada tipo: colete, capacete e arma.
 *
 * Os equipamentos devem ter identificadores únicos variando dentro do intervalo:
 * 0 <= ID < 2 * params->jogadores_por_equipe.
 *
 * ATENÇÃO: Um identificador deve ser único e não pode ser retornado se o mesmo
 * já estiver alocado para um jogador.
 *
 * Dica: Você deve utilizar uma estrutura de dados para armazenar os
 * identificadores dos equipamentos. Para isso, implemente a estrutura "arranjo",
 * cujo esqueleto já foi definido. Veja detalhes de implementação dessa estrutura
 * no arquivo arranjo.h.
 */
PUBLIC void prateleira_pega_equipamentos(equipamentos_t * equipamentos)
{
	// Retira equipamento do arranjo da prateleira.
	equipamentos_t * equipamentos_prateleira = (equipamentos_t*)arranjo_retirar(&prateleira);
	// Coloca o equipamento no arranjo de equipamentos ocupados.
	arranjo_colocar(&equipamentos_ocupados, equipamentos_prateleira);
	// Coloca o equipamento no jogador.
	equipamentos->capacete = equipamentos_prateleira->capacete;
	equipamentos->colete = equipamentos_prateleira->colete;
	equipamentos->arma = equipamentos_prateleira->arma;
	assert(equipamentos);
}

/*============================================================================*
 * prateleira_libera_equipamentos()                                           *
 *============================================================================*/

/**
 * @brief Libera equipamentos após sua limpeza.
 *
 * @return equipamentos Slot de equipamentos limpos.
 *
 * Descrição: O limpador deve armazenar novamente os equipamentos que acabaram
 * de serem limpos.
 *
 * ATENÇÃO: Um identificador deve ser único e não pode ser retornado se o mesmo
 * já estiver alocado para um jogador.
 */
PUBLIC void prateleira_libera_equipamentos(equipamentos_t * equipamentos)
{
	assert(equipamentos);
	// Procura o equipamento no arranjo de equipamentos ocupados.
	int posicao = 0;
	equipamentos_t * equipamentos_liberar = (equipamentos_t*)arranjo_consultar(&equipamentos_ocupados, posicao);
	while (posicao < arranjo_tamanho(&equipamentos_ocupados) && equipamentos->capacete != equipamentos_liberar->capacete) {
		equipamentos_liberar = (equipamentos_t*)arranjo_consultar(&equipamentos_ocupados, posicao);
		posicao++;
	}
	// Coloca o equipamento no arranjo da prateleira.
	arranjo_colocar(&prateleira, equipamentos_liberar);
	// Retira o equipamento do arranjo de equipamentos ocupados.
	arranjo_remover(&equipamentos_ocupados, equipamentos_liberar);
}
