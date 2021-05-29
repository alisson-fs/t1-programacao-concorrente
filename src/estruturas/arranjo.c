#include "arranjo.h"

/**
 * ATENÇÃO: Você pode adicionar novas funções com PUBLIC para serem usadas por
 * outros arquivos e adicionar a assinatura da função no .h referente.
 */

/*============================================================================*
 * arranjo_iniciar()                                                          *
 *============================================================================*/

/**
 * @brief Inicia e aloca os recursos de um arranjo.
 *
 * @param arranjo    Ponteiro de um arranjo.
 * @param capacidade Tamanho do arranjo.
 */
PUBLIC void arranjo_iniciar(arranjo_t * arranjo, int capacidade)
{
	arranjo->data = malloc(capacidade * sizeof(void*));
	arranjo->last_index = -1;
	arranjo->capacity = capacidade;
    arranjo->size = 0;
}

/*============================================================================*
 * arranjo_destruir()                                                         *
 *============================================================================*/

/**
 * @brief Libera recursos de um arranjo.
 *
 * @param arranjo Ponteiro de um arranjo.
 */
PUBLIC void arranjo_destruir(arranjo_t * arranjo)
{
	for (int i = 0; i < arranjo->size; i++) {
		if (arranjo->data[i] != NULL) {
			free(arranjo->data[i]);
		}
	}
    free(arranjo->data);
}

/*============================================================================*
 * arranjo_colocar()                                                          *
 *============================================================================*/

/**
 * @brief Coloca um elemento no arranjo.
 *
 * @param arranjo  Ponteiro de um arranjo.
 * @param elemento Elemento a ser armazenado no arranjo.
 */
PUBLIC void arranjo_colocar(arranjo_t * arranjo, void * elemento)
{
	pthread_mutex_lock(&arranjo->lock);
	if (arranjo_cheio(arranjo) == 0) {
        arranjo->last_index++;
        arranjo->data[arranjo->last_index] = elemento;
        arranjo->size++;
    } else {
		plog("[arranjo] Arranjo cheio, não foi possivel adicionar o elemento!\n");
	}
	pthread_mutex_unlock(&arranjo->lock);
}

/*============================================================================*
 * arranjo_retirar()                                                          *
 *============================================================================*/

/**
 * @brief Retira um elemento do arranjo.
 *
 * @param arranjo Ponteiro de um arranjo.
 *
 * @return Se o arranjo estiver vazio retorna NULL. Caso contrário, retorna
 * um elemento do arranjo.
 */
PUBLIC void * arranjo_retirar(arranjo_t * arranjo)
{
	void * elemento = NULL;
	pthread_mutex_lock(&arranjo->lock);
	if (arranjo_vazio(arranjo) == 0) {
		elemento = arranjo->data[arranjo->last_index];
		arranjo->last_index--;
		arranjo->size--;
	}
	pthread_mutex_unlock(&arranjo->lock);
	return elemento;
}


/*============================================================================*
 * arranjo_consultar()                                                        *
 *============================================================================*/

/**
 * @brief Remove um elemento do arranjo.
 *
 * @param arranjo  Ponteiro de um arranjo.
 * @param posicao  Posição do elemento a ser consultado.
 */
PUBLIC void * arranjo_consultar(arranjo_t * arranjo, int posicao)
{
	void * elemento = NULL;
	pthread_mutex_lock(&arranjo->lock);
	if (posicao < arranjo->size || posicao >= 0) {
		elemento = arranjo->data[posicao];
	}
	pthread_mutex_unlock(&arranjo->lock);
	return elemento;
}

/*============================================================================*
 * arranjo_remover()                                                          *
 *============================================================================*/

/**
 * @brief Remove um elemento do arranjo.
 *
 * @param arranjo  Ponteiro de um arranjo.
 * @param elemento    Elemento a ser removido.
 */
PUBLIC void arranjo_remover(arranjo_t * arranjo, void * elemento)
{
	int position = 0;
	pthread_mutex_lock(&arranjo->lock);
    while (position < arranjo->size && elemento != arranjo->data[position]) {
		position++;
    }
	if (position < arranjo->size) {
		if (elemento == arranjo->data[position]) {
			while (position < arranjo->last_index) {
				arranjo->data[position] = arranjo->data[position + 1];
				position++;
			}
			arranjo->last_index--;
			arranjo->size--;
		}
	}
	pthread_mutex_unlock(&arranjo->lock);
}

/*============================================================================*
 * arranjo_vazio()                                                            *
 *============================================================================*/

/**
 * @brief Verifica se o arranjo está vazio.
 *
 * @param arranjo Ponteiro de um arranjo.
 */
PUBLIC int arranjo_vazio(arranjo_t * arranjo)
{
	if (arranjo->size == 0) {
		return 1;
	} else {
		return 0;
	}
}

/*============================================================================*
 * arranjo_cheio()                                                            *
 *============================================================================*/

/**
 * @brief Verifica se o arranjo está cheio.
 *
 * @param arranjo Ponteiro de um arranjo.
 */
PUBLIC int arranjo_cheio(arranjo_t * arranjo)
{
	if (arranjo->size == arranjo->capacity) {
		return 1;
	} else {
		return 0;
	}
}

/*============================================================================*
 * arranjo_tamanho()                                                          *
 *============================================================================*/

/**
 * @brief Verifica o tamanho do arranjo.
 *
 * @param arranjo Ponteiro de um arranjo.
 *
 * @return Retorna o tamanho atual do arranjo.
 */
PUBLIC int arranjo_tamanho(arranjo_t * arranjo)
{
	return arranjo->size;
}
