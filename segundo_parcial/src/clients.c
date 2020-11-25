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
 * \brief client_new:Pide memoria para generar un nuevo registro de empleado
 * \param void:
 * \return puntero con espacio de memoria con tipo Client*
 */

Client* client_new(void)
{
	return (Client*) malloc(sizeof(Client));
}

/*
 * \brief client_newParametros: Pide memoria para un nuevo empleado y sus campos correspondientes
 * \param id char*: campo id
 * \param nombre char*: campo nombre
 * \param horasTrabajadas char*: campo Horas trabajadas
 * \param sueldo char*: campo sueldo
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
 * \brief client_delete: Libera espacio de memoria de un empleado
 * \param this Client*: puntero a empleado
 * \return void
 */

void client_delete(Client* this)
{
	free(this);
}

/*
 * \brief client_setIdFromTxtFile: Carga el id obtenido como texto en el campo del empleado
 * \param this Client*: puntero a empleado
 * \param id char*: puntero al id que va a cargar
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
 * \brief client_setId: Carga el id en el campo del empleado
 * \param this Client*: puntero a empleado
 * \param id int: id a cargar
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
 * \brief client_getId: Obtiene el id del empleado
 * \param this Client*: puntero a empleado
 * \param id int*: puntero al espacio donde va a guardar el id obtenido
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
 * \param pArrayListClient LinkedList* puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int client_findMaxId(LinkedList* pArrayListClient)
{
	Client* pClient;
	int len;
	int i;
	int max;
	int id = -1;

	if(pArrayListClient != NULL)
	{
		len = ll_len(pArrayListClient);
		for(i=0;i<len;i++)
		{
			pClient = ll_get(pArrayListClient,i);
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
 * \brief client_generateNewId:Genera un nuevo id para un nuevo empleado
 * \param pArrayListClient LinkedList* puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int client_generateNewId(LinkedList* pArrayListClient)
{
    static int id = -1;

    if(pArrayListClient != NULL)
    {
    	if(ll_isEmpty(pArrayListClient)==0)
    	{
    		id = client_findMaxId(pArrayListClient);
    		id++;
    	}
    }
    return id;
}

/*
 * \brief client_setLastName: Carga el Apellido en el campo del empleado
 * \param this Client*: puntero a empleado
 * \param nombre char*: nombre a cargar
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
 * \brief client_getLastName: Obtiene el Apellido del empleado
 * \param this Client*: puntero a empleado
 * \param nombre char*: puntero al espacio donde va a guardar el nombre obtenido
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
 * \brief client_setName: Carga el Nombre en el campo del empleado
 * \param this Client*: puntero a empleado
 * \param nombre char*: nombre a cargar
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
 * \brief client_getName: Obtiene el Nombre del empleado
 * \param this Client*: puntero a empleado
 * \param nombre char*: puntero al espacio donde va a guardar el nombre obtenido
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
 * \brief client_setCuit: Carga el cuit en el campo del empleado
 * \param this Client*: puntero a empleado
 * \param nombre char*: nombre a cargar
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
 * \brief client_getCuit: Obtiene el Cuit del empleado
 * \param this Client*: puntero a empleado
 * \param nombre char*: puntero al espacio donde va a guardar el nombre obtenido
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
 * \brief client_isValidNombre:Valida que la cadena recibida solo tenga letras, espacios o guiones
 * \param string char*: puntero a la cadena a validar
 * \param len int: largo de la cadena a validar
 * \return (0) FALSE (1) TRUE (-1) ERROR
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
 * \return (0) FALSE (1) TRUE (-1) ERROR
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
 * \return (0) FALSE (1) TRUE (-1) ERROR
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



