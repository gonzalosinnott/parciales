/*
============================================================================
Name        : sales.c
Author      : Gonzalo Sinnott Segura
Version     :
Copyright   :
Description : Library sales.c
============================================================================
*/

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "sales.h"

static int sale_isValidInt(char* string, int len);
static int sale_isValidName(char* string, int len);
static int formatdata(int data1, int data2, char* data1Formatted, char* data2formatted);


/*
 * \brief sale_new:Pide memoria para generar un nuevo registro de empleado
 * \param void:
 * \return puntero con espacio de memoria con tipo Sale*
 */

Sale* sale_new(void)
{
	return (Sale*) malloc(sizeof(Sale));
}

/*
 * \brief sale_newParametros: Pide memoria para un nuevo empleado y sus campos correspondientes
 * \param id char*: campo id
 * \param nombre char*: campo nombre
 * \param horasTrabajadas char*: campo Horas trabajadas
 * \param sueldo char*: campo sueldo
 * \return int Return puntero con espacio de memoria con tipo Sale* con el espacio para los campos correspondientes
 */

Sale* sale_newParametros(char* sale_id,char* sale_clientId,char* sale_amount,char* sale_fileName,char* sale_zone, char* sale_status)
{
	Sale* pSale = NULL;

	if (sale_id != NULL && sale_clientId != NULL && sale_amount != NULL && sale_fileName != NULL && sale_zone != NULL && sale_status != NULL)
	{
		pSale = sale_new();
		if (pSale != NULL &&
			sale_setIdFromTxtFile(pSale, sale_id) == 0 &&
			sale_setClientIdFromTxtFile(pSale, sale_clientId) == 0 &&
			sale_setAmountFromTxtFile(pSale, sale_amount) == 0 &&
			sale_setFileName(pSale, sale_fileName) == 0 &&
			sale_setZoneFromTxtFile(pSale, sale_zone) == 0 &&
			sale_setStatusFromTxtFile(pSale, sale_status) ==0)

			{
			return pSale;
		}
		else
		{
			pSale = NULL;
		}
	}
	return pSale;
}

/*
 * \brief sale_delete: Libera espacio de memoria de un empleado
 * \param this Sale*: puntero a empleado
 * \return void
 */

void sale_delete(Sale* this)
{
	free(this);
}

/*
 * \brief sale_setIdFromTxtFile: Carga el id obtenido como texto en el campo del empleado
 * \param this Sale*: puntero a empleado
 * \param id char*: puntero al id que va a cargar
 * \return (-1) Error / (0) Ok
 */

int sale_setIdFromTxtFile(Sale* this, char* sale_id)
{
    int output = -1;
    if (this != NULL && sale_id != NULL && sale_isValidInt(sale_id,sizeof(sale_id))==0)
    {
        this->sale_id = atoi(sale_id);
        output = 0;
    }
    return output;
}

/*
 * \brief sale_setId: Carga el id en el campo del empleado
 * \param this Sale*: puntero a empleado
 * \param id int: id a cargar
 * \return (-1) Error / (0) Ok
 */

int sale_setId(Sale* this, int sale_id)
{
	int output = -1;
	if (this != NULL && sale_id >= 0)
	{
		this->sale_id = sale_id;
		output = 0;
	}
	return output;
}


/*
 * \brief sale_getId: Obtiene el id del empleado
 * \param this Sale*: puntero a empleado
 * \param id int*: puntero al espacio donde va a guardar el id obtenido
 * \return (-1) Error / (0) Ok
 */

int sale_getId(Sale* this,int* sale_id)
{
    int output = -1;
    if (this != NULL && sale_id != NULL)
    {
        *sale_id = this->sale_id;
        output = 0;
    }
    return output;
}

/*
 * \brief sale_findMaxId: Busca en el array el maximo id existente
 * \param pArrayListSale LinkedList* puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int sale_findMaxId(LinkedList* pArrayListSale)
{
	Sale* pSale;
	int len;
	int i;
	int max;
	int id = -1;

	if(pArrayListSale != NULL)
	{
		len = ll_len(pArrayListSale);
		for(i=0;i<len;i++)
		{
			pSale = ll_get(pArrayListSale,i);
			sale_getId(pSale,&id);
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
 * \brief sale_generateNewId:Genera un nuevo id para una nuevo empleado
 * \param pArrayListSale LinkedList* puntero al array de ventas
 * \return (-1) Error / (0) Ok
 */

int sale_generateNewId(LinkedList* pArrayListSale)
{
    static int id = -1;

    if(pArrayListSale != NULL)
    {
    	if(ll_isEmpty(pArrayListSale)==0)
    	{
    		id = sale_findMaxId(pArrayListSale);
    		id++;
    	}
    }
    return id;
}

/*
 * \brief sale_setClientIdFromTxtFile: Carga el id  del cliente aosciado obtenido como texto en el campo de la  venta
 * \param this Sale*: puntero a venta
 * \param id char*: puntero al id que va a cargar
 * \return (-1) Error / (0) Ok
 */

int sale_setClientIdFromTxtFile(Sale* this, char* sale_clientId)
{
    int output = -1;
    if (this != NULL && sale_clientId != NULL && sale_isValidInt(sale_clientId,sizeof(sale_clientId))==0)
    {
        this->sale_clientId= atoi(sale_clientId);
        output = 0;
    }
    return output;
}

/*
 * \brief sale_setClientId: Carga el id del cliente en el campo de la venta
 * \param this Sale*: puntero a empleado
 * \param id int: id a cargar
 * \return (-1) Error / (0) Ok
 */

int sale_setClientId(Sale* this, int sale_clientId)
{
	int output = -1;
	if (this != NULL && sale_clientId >= 0)
	{
		this->sale_clientId = sale_clientId;
		output = 0;
	}
	return output;
}

/*
 * \brief sale_getClientId: Obtiene el id del empleado
 * \param this Sale*: puntero a empleado
 * \param id int*: puntero al espacio donde va a guardar el id obtenido
 * \return (-1) Error / (0) Ok
 */

int sale_getClientId(Sale* this,int* sale_clientId)
{
    int output = -1;
    if (this != NULL && sale_clientId != NULL)
    {
        *sale_clientId = this->sale_clientId;
        output = 0;
    }
    return output;
}


/*
 * \brief sale_setClientIdFromTxtFile: Carga el id  del cliente aosciado obtenido como texto en el campo de la  venta
 * \param this Sale*: puntero a venta
 * \param id char*: puntero al id que va a cargar
 * \return (-1) Error / (0) Ok
 */

int sale_setAmountFromTxtFile(Sale* this, char* sale_amount)
{
    int output = -1;
    if (this != NULL && sale_amount != NULL && sale_isValidInt(sale_amount,sizeof(sale_amount))==0)
    {
        this->sale_amount = atoi(sale_amount);
        output = 0;
    }
    return output;
}

/*
 * \brief sale_setClientId: Carga el id del cliente en el campo de la venta
 * \param this Sale*: puntero a empleado
 * \param id int: id a cargar
 * \return (-1) Error / (0) Ok
 */

int sale_setAmount(Sale* this, int sale_amount)
{
	int output = -1;
	if (this != NULL && sale_amount >= 0)
	{
		this->sale_amount = sale_amount;
		output = 0;
	}
	return output;
}

/*
 * \brief sale_getClientId: Obtiene el id del empleado
 * \param this Sale*: puntero a empleado
 * \param id int*: puntero al espacio donde va a guardar el id obtenido
 * \return (-1) Error / (0) Ok
 */

int sale_getAmount(Sale* this,int* sale_amount)
{
    int output = -1;
    if (this != NULL && sale_amount != NULL)
    {
        *sale_amount = this->sale_amount;
        output = 0;
    }
    return output;
}


/*
 * \brief sale_setLastName: Carga el Apellido en el campo del empleado
 * \param this Sale*: puntero a empleado
 * \param nombre char*: nombre a cargar
 * \return (-1) Error / (0) Ok
 */

int sale_setFileName(Sale* this,char* sale_fileName)
{
	int output = -1;
	if (this != NULL && sale_fileName != NULL && sale_isValidName(sale_fileName, LEN_NAME)==0)
	{
		strncpy(this->sale_fileName, sale_fileName, LEN_NAME);
		output = 0;
	}
	return output;
}

/*
 * \brief sale_getLastName: Obtiene el Apellido del empleado
 * \param this Sale*: puntero a empleado
 * \param nombre char*: puntero al espacio donde va a guardar el nombre obtenido
 * \return (-1) Error / (0) Ok
 */

int sale_getFileName(Sale* this,char* sale_fileName)
{
    int output = -1;
    if (this != NULL && sale_fileName != NULL)
    {
        strncpy(sale_fileName, this->sale_fileName,LEN_NAME);
        output = 0;
    }
    return output;
}


int sale_setZoneFromTxtFile(Sale* this, char* sale_zone)
{
    int output = -1;
    if (this != NULL && sale_zone != NULL && sale_isValidInt(sale_zone,sizeof(sale_zone))==0)
    {
        this->sale_zone = atoi(sale_zone);
        output = 0;
    }
    return output;
}

/*
 * \brief sale_setId: Carga el id en el campo del empleado
 * \param this Sale*: puntero a empleado
 * \param id int: id a cargar
 * \return (-1) Error / (0) Ok
 */

int sale_setZone(Sale* this, int sale_zone)
{
	int output = -1;
	if (this != NULL && sale_zone >= 0)
	{
		this->sale_zone = sale_zone;
		output = 0;
	}
	return output;
}

/*
 * \brief sale_getName: Obtiene el Nombre del empleado
 * \param this Sale*: puntero a empleado
 * \param nombre char*: puntero al espacio donde va a guardar el nombre obtenido
 * \return (-1) Error / (0) Ok
 */

int sale_getZone(Sale* this,int* sale_zone)
{
    int output = -1;
    if (this != NULL && sale_zone != NULL)
    {
        *sale_zone = this->sale_zone;
        output = 0;
    }
    return output;
}

/*
 * \brief sale_setCuit: Carga el cuit en el campo del empleado
 * \param this Sale*: puntero a empleado
 * \param nombre char*: nombre a cargar
 * \return (-1) Error / (0) Ok
 */

int sale_setStatusFromTxtFile(Sale* this, char* sale_status)
{
    int output = -1;
    if (this != NULL && sale_status != NULL && sale_isValidInt(sale_status,sizeof(sale_status))==0)
    {
        this->sale_status = atoi(sale_status);
        output = 0;
    }
    return output;
}

/*
 * \brief sale_setId: Carga el id en el campo del empleado
 * \param this Sale*: puntero a empleado
 * \param id int: id a cargar
 * \return (-1) Error / (0) Ok
 */

int sale_setStatus(Sale* this, int sale_status)
{
	int output = -1;
	if (this != NULL && sale_status >= 0)
	{
		this->sale_status = sale_status;
		output = 0;
	}
	return output;
}

/*
 * \brief sale_getName: Obtiene el Nombre del empleado
 * \param this Sale*: puntero a empleado
 * \param nombre char*: puntero al espacio donde va a guardar el nombre obtenido
 * \return (-1) Error / (0) Ok
 */

int sale_getStatus(Sale* this,int* sale_status)
{
    int output = -1;
    if (this != NULL && sale_status != NULL)
    {
        *sale_status = this->sale_status;
        output = 0;
    }
    return output;
}



/*
 * \brief sale_isValidNombre:Valida que la cadena recibida solo tenga letras, espacios o guiones
 * \param string char*: puntero a la cadena a validar
 * \param len int: largo de la cadena a validar
 * \return (0) FALSE (1) TRUE (-1) ERROR
 */

static int sale_isValidName(char* string, int len)
{
	int output = 0;

	if( string != NULL && len > 0)
	{
		for(int i=0; i<=len && string[i] != '\0';i++)
		{
			if(	(string[i] < 'A' || string[i] > 'Z') &&
				(string[i] < 'a' || string[i] > 'z') &&
				(string[i] < '0' || string[i] > '9') &&
				string[i] != '.' && string[i] != '-' &&
				string[i] != '_')
			{
				output = -1;
				break;
			}
		}
	}
	return output;
}

/*
 * \brief sale_isValidInt: Valida que la cadena recibida solo tenga numeros
 * \param string char*: puntero a la cadena a validar
 * \param len int: largo de la cadena a validar
 * \return (0) FALSE (1) TRUE (-1) ERROR
 */

static int sale_isValidInt(char* string, int len)
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


int sale_printSingleWithMap(void* pSale)
{
	int output = -1;
	Sale* bufferSale;
	bufferSale = (Sale*) pSale;

	int bufferId;
	int bufferClientId;
	int bufferAmount;
	char bufferFileName[LEN_NAME];
	int bufferZone;
	int bufferStatus;
	char bufferZoneformatted[LEN_NAME];
	char bufferStatusformatted[LEN_NAME];

	if(bufferSale != NULL &&
	   sale_getId(bufferSale, &bufferId) ==0 &&
	   sale_getClientId(bufferSale, &bufferClientId) ==0 &&
	   sale_getAmount(bufferSale, &bufferAmount) ==0 &&
	   sale_getFileName(bufferSale, bufferFileName) ==0 &&
	   sale_getZone(bufferSale, &bufferZone) ==0 &&
	   sale_getStatus(bufferSale, &bufferStatus)==0 )
	{
		formatdata(bufferStatus,bufferZone,bufferStatusformatted,bufferZoneformatted);

		printf("| %-5d| %-25s| %-9d | %-9s | %-11s | %-10d |\n",
				bufferId,
				bufferFileName,
				bufferAmount,
				bufferStatusformatted,
				bufferZoneformatted,
				bufferClientId);
		printf("--------------------------------------------------------------------------------------\n");
		output = 0;
	}
	return output;
}

static int formatdata(int data1, int data2, char* data1Formatted, char* data2Formatted)
{
	int output = -1;

	switch(data1)
	{
		case TO_PAY:
			strcpy(data1Formatted,"A COBRAR");
			break;
		case PAID:
			strcpy(data1Formatted,"COBRADA");
			break;
	}

	switch(data2)
	{
		case CABA:
			strcpy(data2Formatted,"CABA");
			break;
		case ZONA_SUR:
			strcpy(data2Formatted,"ZONA SUR");
			break;
		case ZONA_OESTE:
			strcpy(data2Formatted,"ZONA OESTE");
			break;
	}

	return output;
}

int sale_filterByNotPayed (void* pSale)
{
	int output = -1;
	Sale* bufferSale;
	bufferSale = (Sale*) pSale;
	int bufferStatus;
	sale_getStatus(bufferSale, &bufferStatus);
	if(bufferStatus!=TO_PAY)
	{
		output = 0;
	}
	return output;
}

int sale_filterByPayed (void* pSale)
{
	int output = -1;
	Sale* bufferSale;
	bufferSale = (Sale*) pSale;
	int bufferStatus;
	sale_getStatus(bufferSale, &bufferStatus);
	if(bufferStatus==TO_PAY)
	{
		output = 0;
	}
	return output;
}


int sale_getSalesByClientId(LinkedList* listSale,int clientId,int* salesQuantity)
{
	int output = -1;
	int counter = 0;
	Sale* pSale;
	int bufferIdClient;

	if (listSale != NULL && salesQuantity != NULL && clientId > 0)
	{
		for (int i = 0; i < ll_len(listSale); i++)
		{
			pSale = (Sale*) ll_get(listSale,i);
			if(pSale != NULL)
			{
				sale_getClientId(pSale,&bufferIdClient);
				if(bufferIdClient == clientId)
				{
					counter++;
				}
			}
		}
		*salesQuantity = counter;
		output = 0;
	}
	return output;
}

void* sales_findById(LinkedList* list, int id)
{
	void* result = NULL;
	void* pElement;
	int i;
	int bufferId;
	int resultAux;


	for (i = 0; i < ll_len(list); i++)
	{

		pElement = (Sale*)ll_get(list,i);
		resultAux = sale_getId(pElement,&bufferId);


		if(resultAux == 0 && bufferId == id)
		{
			result = pElement;
			break;
		}

	}
	return result;
}
