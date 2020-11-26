#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */

LinkedList* ll_newLinkedList(void)
{
    LinkedList* newlist = NULL;

    newlist=(LinkedList*)malloc(sizeof(LinkedList));

    if(newlist!=NULL)
    {
        newlist->size=0;
        newlist->pFirstNode=NULL;
    }
    return newlist;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int size = -1;

    if(this!=NULL)
    {
    	size=this->size;

    }
    return size;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */


static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* node = NULL;

    if(this!=NULL && nodeIndex>=0 && nodeIndex<ll_len(this))
    {
    	node = this->pFirstNode;
    	for(int i = 0 ; i < nodeIndex; i++)
    	{
    		node = node->pNextNode;
    	}
    }
    return node;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */

static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int retorno=-1;
    Node* pNewNode;
    Node* pPreviousNode;

    if(this!=NULL && nodeIndex>=0 && nodeIndex<=ll_len(this))
    {
    	pNewNode = (Node*)malloc(sizeof(Node));
    	if(pNewNode !=NULL)
    	{
    		pNewNode->pElement = pElement;

			if(nodeIndex == 0)//quiero agregar nodo en la primera posicion
			{
				pNewNode->pNextNode = this->pFirstNode;
				this->pFirstNode = pNewNode;
			}
			else//quiero agregar nodo en otra posicion
			{
				pPreviousNode = getNode(this, nodeIndex-1);
				pNewNode->pNextNode = pPreviousNode->pNextNode;
				pPreviousNode->pNextNode = pNewNode;
			}
			this->size++;
			retorno = 0;
    	}
    }
    return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int retorno = -1;
    int index=ll_len(this);

    if(this!=NULL)
    {
        addNode(this,index,pElement);
        retorno=0;
    }
    return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    Node* auxNode = NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	auxNode=getNode(this,index)->pElement;
    }
    return auxNode;
}



/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int output = -1;
    Node* auxNode = NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	auxNode=getNode(this,index);
    	auxNode->pElement=pElement;
    	output=0;
   }
    return output;
}

/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int output = -1;
    Node* actualNode;
    Node* previousNode;

    if(this!=NULL && index >=0 && index<ll_len(this))
    {
    	actualNode=getNode(this,index);
        if(actualNode!=NULL)
        {
            if(index==0)
            {
                this->pFirstNode = actualNode->pNextNode;
            }
            else
            {
            	previousNode = getNode(this,index-1);
                if(previousNode!=NULL)
                {
                	previousNode->pNextNode = actualNode->pNextNode;
                }
            }
            free(actualNode);
            this->size--;
            output=0;
        }
    }
    return output;
}

/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int output = -1;

    if(this!=NULL)
    {
        while(ll_len(this)!=0)
        {
            ll_remove(this,0);
        }
        this->pFirstNode=NULL;
        output=0;
    }
    return output;
}

/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */

int ll_deleteLinkedList(LinkedList* this)
{
    int output = -1;

    if(this!=NULL)
    {
        while(ll_len(this)!=0)
        {
            ll_remove(this,0);
        }
        free(this);
        output=0;
    }
    return output;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */

int ll_indexOf(LinkedList* this, void* pElement)
{
    int output = -1;
    int len = ll_len(this);
    void* auxNode;

    if(this!=NULL)
    {
        for(int i=0; i<len; i++)
        {
        	auxNode=ll_get(this,i);
            if(auxNode == pElement)
            {
            	output=i;
                break;
            }
        }
    }
    return output;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int output = -1;

    if(this!=NULL)
    {
    	output = 1;
        if(ll_len(this) != 0)
        {
        	output=0;
        }
    }
    return output;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int output = -1;

    if(this!=NULL && index >= 0 && index <= ll_len(this))
    {
        if(addNode(this,index,pElement)==0)
		{
        	output=0;
		}
    }
    return output;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */

void* ll_pop(LinkedList* this,int index)
{
    void* output = NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	output = ll_get(this,index);
        if(ll_remove(this,index))
        {
        	output = NULL;
        }
    }
    return output;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/

int ll_contains(LinkedList* this, void* pElement)
{
    int output = -1;
    int indexElement;

	if(this != NULL)
	{
		indexElement = ll_indexOf(this, pElement);
		if(indexElement >=0)
		{
			output = 1;
		}
		else
		{
			output = 0;
		}
	}
	return output;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int output = -1;
    int len;

    if(this!=NULL && this2!=NULL)
    {
    	output=1;
    	len=ll_len(this2);
        for(int i=0; i<len; i++)
        {
            if(!ll_contains(this,ll_get(this2,i)))
            {
            	output=0;
                break;
            }
        }
    }
    return output;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/

LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray=NULL;

    if(this!=NULL && from>=0 && from>=0 && to>=from && to<=ll_len(this))
    {
        cloneArray=ll_newLinkedList();
        if(cloneArray!=NULL)
        {
            for(int i=from; i<to; i++)
            {
                ll_add(cloneArray,ll_get(this,i));
            }
        }
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/

LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this!=NULL)
    {
        cloneArray=ll_subList(this,0,ll_len(this));
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                        ( 0) Si ok
 */

int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int output = -1;
    void* auxElement;
    int sorted;
    int len = ll_len(this);

    if(this!=NULL && pFunc!=NULL && (order==0 || order==1))
    {
    	do
    	{
    		sorted = 1;
			for(int i=0; i<len-1; i++)
			{

				if((pFunc(ll_get(this,i),ll_get(this,i+1))>0 && order== 1)||
				   (pFunc(ll_get(this,i),ll_get(this,i+1))<0 && order== 0))
				{
					auxElement=ll_get(this,i);
					ll_set(this,i,ll_get(this,i+1));
					ll_set(this,i+1,auxElement);
					sorted = 0;
				}

			}
    	}
        while(sorted == 0);
        output=0;
    }
    return output;
}

/*
 * \brief ll_map: Recorre todos los elementos de la LinkedList para utilizar una función criterio en cada elemento de cada nodo
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                        ( 0) Ok
 */

int ll_map(LinkedList* this, int (*pFunc)(void*))
{
	int output = -1;
    int len = ll_len(this);
    void* pElement;

	if(this!=NULL && pFunc!=NULL)
	{
		for(int i = 0; i < len ; i++)
		{
			pElement = ll_get(this, i);
			pFunc(pElement);
		}
		output = 0;
	}
	return output;
}

/*
 * \brief ll_filter: Recorre todos los elementos de la LinkedList para utilizar una función criterio en cada elemento de cada nodo
 *  y eliminar de la lista a lo que la funcion criterio retorne como 0
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL si pFunc es NULL o si len <= 0
                        ( 0) Ok
 */

int ll_filter(LinkedList * this, int (*pFunc)(void*))
{
	int output = -1;
	void* pElement;
	int i;

	if (this != NULL && pFunc != NULL)
	{
		for (i = ll_len(this) - 1; i >= 0; i--)
		{
			pElement = ll_get(this, i);
			if (pElement != NULL)
			{
				if (pFunc(pElement) == 0)
				{
					ll_remove(this, i);
				}
				output=0;
			}
		}
	}
	return output;
}

/*
 * \brief ll_reduceInt: Recorre todos los elementos de la LinkedList para utilizar una función criterio
 *  en cada elemento de cada nodo y almacenar en un acumulador los retornos de estas funciones
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param id int
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL si pFunc es NULL o si len <= 0 o si newLen != 0
                        ( 0) Ok
 */

int ll_reduceInt(LinkedList* this, int (*pFunc)(void*,int value), int id)
{
	int len = ll_len(this);
	int acumulator=-1;
	void* pElement=NULL;
	if(this!=NULL && pFunc!=NULL && len>-1)
	{
		acumulator = 0;
		for(int i = 0; i<len;i++)
		{
			pElement = ll_get(this, i);
			acumulator+= pFunc(pElement, id);
		}
	}
	return acumulator;
}

