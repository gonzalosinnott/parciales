/*
============================================================================
Name        : Client.c
Author      : Gonzalo Sinnott Segura
Version     :
Copyright   :
Description : Library Client.c
============================================================================
*/

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"

static int client_isValidName(char* string, int len);
static int client_isValidCuit(char* string, int len);
static int client_isValidInt(char* string, int len);

/*
 * \brief client_new:Pide memoria para generar un nuevo registro de cliente
 * \param void:
 * \return puntero con espacio de memoria con tipo Client*
 */

Client* client_new(void)
{
	return (Client*) malloc(sizeof(Client));
}

/*
 * \brief client_newParametros: Pide memoria para un nuevo cliente y sus campos correspondientes
 * \param client_id char*: campo id
 * \param client_lastName char*: campo apellido
 * \param client_name char*: campo nombre
 * \param client_cuit char*: campo cuit
 * \return int Return puntero con espacio de memoria con tipo Client* con el espacio para los campos correspondientes
 */

Client* client_newParametros(char* client_id,char* client_lastName,char* client_name, char* client_cuit)
{
	Client* pClient = NULL;

	if (client_id != NULL && client_lastName != NULL && client_name != NULL && client_cuit != NULL)
	{
		pClient = client_new();
		if (pClient != NULL &&
			client_setIdFromTxtFile(pClient, client_id) == 0 &&
			client_setLastName(pClient, client_lastName) == 0 &&
			client_setName(pClient, client_name) == 0 &&
			client_setCuit(pClient, client_cuit) ==0)

			{
			return pClient;
		}
		else
		{
			pClient = NULL;
		}
	}
	return pClient;
}

/*
 * \brief client_delete: Libera espacio de memoria de un cliente
 * \param this Client*: puntero a cliente
 * \return void
 */

void client_delete(Client* this)
{
	free(this);
}

/*
 * \brief client_setIdFromTxtFile: Carga el id obtenido desde un archivo txt en el campo del cliente
 * \param this Client*: puntero a cliente
 * \param client_id char*: puntero al id que va a cargar
 * \return (-1) Error / (0) Ok
 */

int client_setIdFromTxtFile(Client* this, char* client_id)
{
    int output = -1;
    if (this != NULL && client_id != NULL && client_isValidInt(client_id,sizeof(client_id))==0)
    {
        this->client_id = atoi(client_id);
        output = 0;
    }
    return output;
}

/*
 * \brief client_setId: Carga el id en el campo del cliente
 * \param this Client*: puntero a cliente
 * \param client_id int: id a cargar
 * \return (-1) Error / (0) Ok
 */

int client_setId(Client* this, int client_id)
{
	int output = -1;
	if (this != NULL && client_id >= 0)
	{
		this->client_id = client_id;
		output = 0;
	}
	return output;
}


/*
 * \brief client_getId: Obtiene el id del cliente
 * \param this Client*: puntero a cliente
 * \param client_id int*: puntero al espacio donde va a guardar el id obtenido
 * \return (-1) Error / (0) Ok
 */

int client_getId(Client* this,int* client_id)
{
    int output = -1;
    if (this != NULL && client_id != NULL)
    {
        *client_id = this->client_id;
        output = 0;
    }
    return output;
}


/*
 * \brief client_findMaxId: Busca en el array el maximo id existente
 * \param ListClient LinkedList* puntero al array de clientes
 * \return (-1) Error / (0) Ok
 */

int client_findMaxId(LinkedList* ListClient)
{
	Client* pClient;
	int len;
	int i;
	int max;
	int id = -1;

	if(ListClient != NULL)
	{
		len = ll_len(ListClient);
		for(i=0;i<len;i++)
		{
			pClient = ll_get(ListClient,i);
			client_getId(pClient,&id);
			if (i == 0 || id > max)
			{
				max = id;
			}
		}
		id = max;
	}
	return id;
}

/*
 * \brief client_generateNewId:Genera un nuevo id para un nuevo cliente
 * \param ListClient LinkedList* puntero al array de clientes
 * \return (-1) Error / (0) Ok
 */

int client_generateNewId(LinkedList* ListClient)
{
    static int id = -1;

    if(ListClient != NULL)
    {
    	if(ll_isEmpty(ListClient)==0)
    	{
    		id = client_findMaxId(ListClient);
    		id++;
    	}
    }
    return id;
}

/*
 * \brief client_setLastName: Carga el Apellido en el campo del cliente
 * \param this Client*: puntero a cliente
 * \param client_lastName char*: apellido a cargar
 * \return (-1) Error / (0) Ok
 */

int client_setLastName(Client* this,char* client_lastName)
{
	int output = -1;
	if (this != NULL && client_lastName != NULL && client_isValidName(client_lastName, LEN_NAME)==0)
	{
		strncpy(this->client_lastName, client_lastName, LEN_NAME);
		output = 0;
	}
	return output;
}

/*
 * \brief client_getLastName: Obtiene el Apellido del cliente
 * \param this Client*: puntero a cliente
 * \param client_lastName char*: puntero al espacio donde esta el apellido obtenido
 * \return (-1) Error / (0) Ok
 */

int client_getLastName(Client* this,char* client_lastName)
{
    int output = -1;
    if (this != NULL && client_lastName != NULL)
    {
        strncpy(client_lastName, this->client_lastName,LEN_NAME);
        output = 0;
    }
    return output;
}

/*
 * \brief client_setName: Carga el Nombre en el campo del cliente
 * \param this Client*: puntero a cliente
 * \param client_name char*: nombre a cargar
 * \return (-1) Error / (0) Ok
 */

int client_setName(Client* this,char* client_name)
{
	int output = -1;
	if (this != NULL && client_name != NULL && client_isValidName(client_name, LEN_NAME)==0)
	{
		strncpy(this->client_name, client_name, LEN_NAME);
		output = 0;
	}
	return output;
}

/*
 * \brief client_getName: Obtiene el Nombre del cliente
 * \param this Client*: puntero a cliente
 * \param client_name char*: puntero al espacio donde va esta el nombre obtenido
 * \return (-1) Error / (0) Ok
 */

int client_getName(Client* this,char* client_name)
{
    int output = -1;
    if (this != NULL && client_name != NULL)
    {
        strncpy(client_name, this->client_name,LEN_NAME);
        output = 0;
    }
    return output;
}

/*
 * \brief client_setCuit: Carga el cuit en el campo del cliente
 * \param this Client*: puntero a cliente
 * \param client_cuit char*: nombre a cargar
 * \return (-1) Error / (0) Ok
 */

int client_setCuit(Client* this,char* client_cuit)
{
	int output = -1;
	if (this != NULL && client_cuit != NULL && client_isValidCuit(client_cuit, LEN_FORMATEDCUIT)==0)
	{

			strncpy(this->client_cuit, client_cuit, LEN_FORMATEDCUIT);
			output = 0;
	}
	return output;
}

/*
 * \brief client_getCuit: Obtiene el Cuit del cliente
 * \param this Client*: puntero a cliente
 * \param client_cuit char*: puntero al espacio donde esta el nombre obtenido
 * \return (-1) Error / (0) Ok
 */

int client_getCuit(Client* this,char* client_cuit)
{
    int output = -1;
    if (this != NULL && client_cuit != NULL)
    {
        strncpy(client_cuit, this->client_cuit,LEN_FORMATEDCUIT);
        output = 0;
    }
    return output;
}


/*
 * \brief client_setPaidSales: Carga las ventas pagadas en el campo del cliente
 * \param this Client*: puntero a cliente
 * \param paidSales int*: numero ventas pagas a cargar
 * \return (-1) Error / (0) Ok
 */


int client_setPaidSales(Client* this, int paidSales)
{
	int output = -1;
	if (this != NULL && paidSales >= 0)
	{
		this->paidSales = paidSales;
		output = 0;
	}
	return output;
}

/*
 * \brief client_getPaidSales: Obtiene las ventas pagas del cliente
 * \param this Client*: puntero a cliente
 * \param paidSales int*: puntero al espacio donde esta el parametro obtenido
 * \return (-1) Error / (0) Ok
 */

int client_getPaidSales(Client* this,int* paidSales)
{
	int output = -1;
	if (this != NULL && paidSales != NULL)
	{
		*paidSales = this->paidSales;
		output = 0;
	}
	return output;
}

/*
 * \brief client_setNotPaidSales: Carga las ventas no pagadas en el campo del cliente
 * \param this Client*: puntero a cliente
 * \param notPaidSales int*: numero ventas no pagas a cargar
 * \return (-1) Error / (0) Ok
 */

int client_setNotPaidSales(Client* this, int notPaidSales)
{
	int output = -1;
	if (this != NULL && notPaidSales >= 0)
	{
		this->notPaidSales = notPaidSales;
		output = 0;
	}
	return output;
}

/*
 * \brief client_getNotPaidSales: Obtiene las ventas no pagas del cliente
 * \param this Client*: puntero a cliente
 * \param notPaidSales int*: puntero al espacio donde esta el parametro obtenido
 * \return (-1) Error / (0) Ok
 */

int client_getNotPaidSales(Client* this,int* notPaidSales)
{
	int output = -1;
	if (this != NULL && notPaidSales != NULL)
	{
		*notPaidSales = this->notPaidSales;
		output = 0;
	}
	return output;
}

/*
 * \brief client_isValidNombre:Valida que la cadena recibida solo tenga letras, espacios o guiones
 * \param string char*: puntero a la cadena a validar
 * \param len int: largo de la cadena a validar
 * \return (-1) Error / (0) Ok
 */

static int client_isValidName(char* string, int len)
{
	int output = 0;

	if( string != NULL && len > 0)
	{
		for(int i=0; i<=len && string[i] != '\0';i++)
		{
			if(	(string[i] < 'A' || string[i] > 'Z') &&
				(string[i] < 'a' || string[i] > 'z') &&
				string[i] != ' ' && string[i] != '-')
			{
				output = -1;
				break;
			}
		}
	}
	return output;
}

/*
 * \brief client_isValidCuit:Valida que la cadena recibida solo tenga numeros y guiones
 * \param string char*: puntero a la cadena a validar
 * \param len int: largo de la cadena a validar
 * \return (-1) Error / (0) Ok
 */

static int client_isValidCuit(char* string, int len)
{
	int output = 0;

	if( string != NULL && len > 0)
	{
		for(int i=0; i<=len && string[i] != '\0';i++)
		{
			if((string[i] < '0' || string[i] > '9') &&
				string[i] != '-')
			{
				output = -1;
				break;
			}
		}
	}
	return output;
}

/*
 * \brief client_isValidInt: Valida que la cadena recibida solo tenga numeros
 * \param string char*: puntero a la cadena a validar
 * \param len int: largo de la cadena a validar
 * \return (-1) Error / (0) Ok
 */

static int client_isValidInt(char* string, int len)
{
	int output = -1;
	int i = 0;

	if(string!= NULL && len > 0)
	{
		output = 0;
		if(string[0] == '-' || string[0] == '+')
		{
			i = 1;
		}
		for(i = 1; string[i]!= '\0' && i < len; i++)
		{
			if(string[i] < '0' || string[i] > '9')
			{
				output = -1;
				break;
			}
		}
	}
	return output;
}

/*
 * \brief client_cuitExists: Chequea que el cuit ingresado ya no este asignado a algun cliente
 * \param this Client*: puntero a cliente
 * \param client_cuit char*: puntero al espacio donde esta el campo obtenido
 * \return (-1) NO EXISTE / (0) EXISTE
 */

int client_cuitExists(LinkedList* this, char* cuit)
{
	int output = -1;
	char bufferCuit[LEN_FORMATEDCUIT];
	Client* pClient;

	if(this !=  NULL && cuit != NULL)
	{
		for (int i = 0; i < ll_len(this); i++)
		{
			pClient = (Client*)ll_get(this,i);
			if(pClient!= NULL)
			{
				client_getCuit(pClient,bufferCuit);
				if (strncmp(bufferCuit,cuit,LEN_FORMATEDCUIT)==0)
				{
					output = 0;
					break;
				}
			}
		}
	}
	return output;
}

/*
 * \brief client_findById: Busca un cliente a partir de un ID dado
 * \param this Client*: puntero a cliente
 * \param id int: ID a comparar
 * \return (NULL) NO EXISTE / (pElement) EXISTE
 */

void* client_findById(LinkedList* ListClient, int id)
{
	void* result = NULL;
	void* pElement;
	int i;
	int bufferId;
	int resultAux;


	for (i = 0; i < ll_len(ListClient); i++)
	{

		pElement = (Client*)ll_get(ListClient,i);
		resultAux = client_getId(pElement,&bufferId);


		if(resultAux == 0 && bufferId == id)
		{
			result = pElement;
			break;
		}

	}
	return result;
}

/*
 * \brief client_findByIdInt: Busca un cliente a partir de un ID dado
 * \param this Client*: puntero a cliente
 * \param id int: ID a comparar
 * \return (-1) NO EXISTE / (0) EXISTE
 */

int client_findByIdInt(LinkedList* ListClients, int id)
{
	int output = -1;
	int len;
	int client_id;
	Client* bufferClient;
	if (ListClients != NULL)
	{
		output = 0;
		len = ll_len(ListClients);

		for(int i = 0; i < len; i++)
		{
			bufferClient = ll_get(ListClients, i);
			client_getId(bufferClient, &client_id);
			if(client_id == id)
			{
				output = i;
				break;
			}
		}
	}
	return output;
}

/*
 * \brief client_printSingleWithMap: Imprime un cliente a partir de su puntero
 * \param pClient void*: puntero a cliente
 * \return (-1) Error / (0) Ok
 */

int client_printSingleWithMap(void* pClient)
{
	int output = -1;
	Client* bufferClient;
	bufferClient = (Client*) pClient;

	int bufferId;
	char bufferlastName[LEN_NAME];
	char bufferName[LEN_NAME];
	char bufferCuit[LEN_FORMATEDCUIT];

	if(bufferClient != NULL &&
	   client_getId(bufferClient, &bufferId) ==0 &&
	   client_getLastName(bufferClient, bufferlastName) ==0 &&
	   client_getName(bufferClient, bufferName) ==0 &&
	   client_getCuit(bufferClient, bufferCuit)==0 )
	{

		printf("| %-16s| %-16s| %-16s| %-3d |\n",
				bufferlastName,
				bufferName,
				bufferCuit,
				bufferId);
		printf("-------------------------------------------------------------\n");
		output = 0;

	}
	return output;
}

/*
 * \brief client_printPaidWithMap: Imprime un cliente con la cantidad de ventas pagas a partir de su puntero
 * \param pClient void*: puntero a cliente
 * \return (-1) Error / (0) Ok
 */

int client_printPaidWithMap(void* pClient)
{
	int output = -1;
	Client* bufferClient;
	bufferClient = (Client*) pClient;

	int bufferId;
	char bufferlastName[LEN_NAME];
	char bufferName[LEN_NAME];
	char bufferCuit[LEN_FORMATEDCUIT];
	int bufferPaidSales;

	if(bufferClient != NULL &&
	   client_getId(bufferClient, &bufferId) ==0 &&
	   client_getLastName(bufferClient, bufferlastName) ==0 &&
	   client_getName(bufferClient, bufferName) ==0 &&
	   client_getPaidSales(bufferClient, &bufferPaidSales) ==0 &&
	   client_getCuit(bufferClient, bufferCuit)==0 )
	{

		printf("| %-5d| %-16s| %-16s| %-16s| %-13d|\n",
				bufferId,
				bufferlastName,
				bufferName,
				bufferCuit,
				bufferPaidSales);
	    printf("-----------------------------------------------------------------------------\n");
		output = 0;

	}
	return output;
}

/*
 * \brief client_printNotPaidWithMap: Imprime un cliente con la cantidad de ventas no pagas a partir de su puntero
 * \param pClient void*: puntero a cliente
 * \return (-1) Error / (0) Ok
 */

int client_printNotPaidWithMap(void* pClient)
{
	int output = -1;
	Client* bufferClient;
	bufferClient = (Client*) pClient;

	int bufferId;
	char bufferlastName[LEN_NAME];
	char bufferName[LEN_NAME];
	char bufferCuit[LEN_FORMATEDCUIT];
	int bufferNotPaidSales;

	if(bufferClient != NULL &&
	   client_getId(bufferClient, &bufferId) ==0 &&
	   client_getLastName(bufferClient, bufferlastName) ==0 &&
	   client_getName(bufferClient, bufferName) ==0 &&
	   client_getNotPaidSales(bufferClient, &bufferNotPaidSales) ==0 &&
	   client_getCuit(bufferClient, bufferCuit)==0 )
	{

		printf("| %-5d| %-16s| %-16s| %-16s| %-15d|\n",
				bufferId,
				bufferlastName,
				bufferName,
				bufferCuit,
				bufferNotPaidSales);
		printf("-------------------------------------------------------------------------------\n");
		output = 0;

	}
	return output;
}


