#ifndef __GERENTE_H__
#define __GERENTE_H__

	#include "prateleira.h"
    #include "config.h"
    #include "partida.h"
    #include "jogador.h"

	/*============================================================================*
	 * Funções padrão exportadas (utilizadas em arquivos que incluem esse .h)     *
	 *============================================================================*/

	/**
	 * @brief Setup do gerente.
	 */
	EXTERN void gerente_setup(void);

	/**
	 * @brief Cleanup do gerente.
	 */
	EXTERN void gerente_cleanup(void);

	/**
	 * @brief Main do gerente.
	 */
	EXTERN void * gerente_fn(void * arg);

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

#endif /*__GERENTE_H__*/
