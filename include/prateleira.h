#ifndef __PRATELEIRA_H__
#define __PRATELEIRA_H__

	#include "config.h"
	#include "arranjo.h"

	/*============================================================================*
	 * Estrutura                                                                  *
	 *============================================================================*/

	/**
	 * @brief Estrutura dos equipamentos APENAS PARA O JOGADOR.
	 */
	typedef struct equipamentos
	{
		int colete;   /**< Identificador único do colete.   */
		int capacete; /**< Identificador único do capacete. */
		int arma;     /**< Identificador único da arma.     */
	} equipamentos_t;

	/*============================================================================*
	 * Funções padrão exportadas (utilizadas em arquivos que incluem esse .h)     *
	 *============================================================================*/

	/**
	 * @brief Configura as prateleiras.
	 */
	EXTERN void prateleira_setup(void);

	/**
	 * @brief Limpa prateleiras.
	 */
	EXTERN void prateleira_cleanup(void);

	/**
	 * @brief Função que permite o jogador pegar os equipamentos da prateleira.
	 */
	EXTERN void prateleira_pega_equipamentos(equipamentos_t * equipamentos);

	/**
	 * @brief Função que permite o jogador devolver os equipamentos após o uso.
	 */
	EXTERN void prateleira_libera_equipamentos(equipamentos_t * equipamentos);

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

#endif /*__PRATELEIRA_H__*/
