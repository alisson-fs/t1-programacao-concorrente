#ifndef __ARRANJO_H__
#define __ARRANJO_H__

	#include "config.h"

	/*============================================================================*
	 * Estrutura                                                                  *
	 *============================================================================*/

	/**
	 * @brief Estrutura de um arranjo genérico.
	 */
	typedef struct arranjo
	{
		/**
		 * @brief Adicione aqui o código necessário para implementar a estrutura de
		 * dados. Tenha em mente que vários tipos de estruturas de dados podem ser
		 * usados (fila, pilha, lista, ...). Você poderá implementar a estrutura de
		 * dados que achar mais adequada para o trabalho. 
		 */

		/**
	 	 * @brief Array onde devem ser colocados os elementos.
	 	 */
		void* * data;
		
		/**
	 	 * @brief Indice onde irá ocorrer a próxima inserção ou remoção.
	 	 */
		int last_index;
		
		/**
	 	 * @brief Quantos elementos cabem em data.
	 	 */
		int capacity;
		
		/**
	 	 * @brief Quantos elementos estão em data.
	 	 */
		int size;
		
		/**
	 	 * @brief Mutex para controle de escrita e leitura do arranjo.
	 	 */
		pthread_mutex_t lock;
	} arranjo_t;


	/*============================================================================*
	 * Funções padrão exportadas (utilizadas em arquivos que incluem esse .h)     *
	 *============================================================================*/

	EXTERN void arranjo_iniciar(arranjo_t * arranjo, int capacidade);
	EXTERN void arranjo_destruir(arranjo_t * arranjo);
	EXTERN void arranjo_colocar(arranjo_t * arranjo, void * valor);
	EXTERN void * arranjo_retirar(arranjo_t * arranjo);
	EXTERN void * arranjo_consultar(arranjo_t * arranjo, int posicao);
	EXTERN void arranjo_remover(arranjo_t * arranjo, void * valor);
	EXTERN int arranjo_vazio(arranjo_t * arranjo);
	EXTERN int arranjo_cheio(arranjo_t * arranjo);
	EXTERN int arranjo_tamanho(arranjo_t * arranjo);

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

#endif /*__ARRANJO_H__*/
