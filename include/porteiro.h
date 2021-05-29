#ifndef __PORTEIRO_H__
#define __PORTEIRO_H__

	#include "config.h"
	#include "partida.h"
	#include "jogador.h"

	/*============================================================================*
	 * Funções padrão exportadas (utilizadas em arquivos que incluem esse .h)     *
	 *============================================================================*/

	/**
	 * @brief Setup do porteiro.
	 */
	EXTERN void porteiro_setup(void);

	/**
	 * @brief Cleanup do porteiro.
	 */
	EXTERN void porteiro_cleanup(void);

	/**
	 * @brief Jogador notifica término ao porteiro.
	 */
	EXTERN void porteiro_checklist(jogador_t * jogador);

	/**
	 * @brief Main do porteiro.
	 */
	EXTERN void * porteiro_fn(void * arg);

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

#endif /*__PORTEIRO_H__*/

