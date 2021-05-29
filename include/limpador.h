#ifndef __LIMPADOR_H__
#define __LIMPADOR_H__

	#include "prateleira.h"
	#include "config.h"
	#include "partida.h"

	/*============================================================================*
	 * Funções padrão exportadas (utilizadas em arquivos que incluem esse .h)     *
	 *============================================================================*/

	/**
	 * @brief Setup do limpador.
	 */
	EXTERN void limpador_setup(void);

	/**
	 * @brief Cleanup do limpador.
	 */
	EXTERN void limpador_cleanup(void);

	/**
	 * @brief Jogador notifica término ao porteiro.
	 */
	EXTERN void limpador_requisita_limpeza(equipamentos_t * equipamentos);

	/**
	 * @brief Main do limpador.
	 */
	EXTERN void * limpador_fn(void * arg);

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

#endif /*__LIMPADOR_H__*/

