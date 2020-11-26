 /*
 ============================================================================
 Name        : parser.C
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Library parser.c
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "clients.h"
#include "sales.h"


#define BUFFER_LEN 4096

/*
 * \brief parser_ClientFromText: Parsea los datos de los clientes desde el archivo clientes.txt (modo texto).
 * \param pFile FILE* puntero al archivo a cargar
 * \param pArrayListEmployee LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int parser_ClientFromText(FILE* pFile , LinkedList* pArrayListClient)
{
	int output = -1;
	Client* pClient;
	char bufferHeader[BUFFER_LEN];
	char bufferId[BUFFER_LEN];
	char bufferLastName[BUFFER_LEN];
	char bufferName[BUFFER_LEN];
	char bufferCuit[BUFFER_LEN];

	if (pFile != NULL && pArrayListClient != NULL)
	{
		fscanf(pFile, "%[^\n]\n", bufferHeader);
		do
		{
			if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", bufferId, bufferLastName, bufferName, bufferCuit) == 4)
			{
				pClient = client_newParametros(bufferId, bufferLastName, bufferName, bufferCuit);
				if (pClient != NULL)
				{
					output = ll_add(pArrayListClient, pClient);
				}
				else
				{
					output = -1;
					break;
				}
			}
		}while (!feof(pFile));
	}
	return output;
}


int parser_SalesFromText(FILE* pFile , LinkedList* pArrayListSales)
{
	int output = -1;
	Sale* pSale;
	char bufferHeader[BUFFER_LEN];
	char bufferId[BUFFER_LEN];
	char bufferClientId[BUFFER_LEN];
	char bufferAmount[BUFFER_LEN];
	char bufferFileName[BUFFER_LEN];
	char bufferZone[BUFFER_LEN];
	char bufferStatus[BUFFER_LEN];

	if (pFile != NULL && pArrayListSales != NULL)
	{
		fscanf(pFile, "%[^\n]\n", bufferHeader);
		do
		{
			if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
				bufferId, bufferFileName, bufferAmount, bufferZone, bufferStatus, bufferClientId) == 6)
			{
				pSale = sale_newParametros(bufferId, bufferClientId, bufferAmount, bufferFileName, bufferZone, bufferStatus);
				if (pSale != NULL)
				{
					output = ll_add(pArrayListSales, pSale);
				}
				else
				{
					output = -1;
					break;
				}
			}
		}while (!feof(pFile));
	}
	return output;
}


int parser_paidListToText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int output = -1;
	Client *pClient;
	int bufferId;
	char BufferLastName[LEN_NAME];
	char bufferName[LEN_NAME];
	char bufferCuit[LEN_FORMATEDCUIT];
	int bufferPaidSales;
	int len;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		fprintf(pFile, "ID,APELLIDO,NOMBRE,CUIT,CANTIDAD DE VENTAS PAGAS\n");
		for (int i = 0; i < len; i++)
		{
			pClient = (Client*)ll_get(pArrayListEmployee, i);
			if (pClient != NULL &&
				client_getId(pClient, &bufferId) == 0 &&
				client_getLastName(pClient, BufferLastName) == 0 &&
				client_getName(pClient, bufferName) == 0 &&
				client_getCuit(pClient, bufferCuit) == 0 &&
				client_getPaidSales(pClient, &bufferPaidSales) == 0)
			{
				fprintf(pFile, "%d,%s,%s,%s,%d\n", bufferId, BufferLastName, bufferName, bufferCuit,bufferPaidSales);
				output = 0;
			}
		}
	}
	return output;
}

int parser_notPaidListToText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int output = -1;
	Client *pClient;
	int bufferId;
	char BufferLastName[LEN_NAME];
	char bufferName[LEN_NAME];
	char bufferCuit[LEN_FORMATEDCUIT];
	int bufferNotPaidSales;
	int len;

	if (pFile != NULL && pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		fprintf(pFile, "ID,APELLIDO,NOMBRE,CUIT,CANTIDAD DE VENTAS IMPAGASPAGAS\n");
		for (int i = 0; i < len; i++)
		{
			pClient = (Client*)ll_get(pArrayListEmployee, i);
			if (pClient != NULL &&
				client_getId(pClient, &bufferId) == 0 &&
				client_getLastName(pClient, BufferLastName) == 0 &&
				client_getName(pClient, bufferName) == 0 &&
				client_getCuit(pClient, bufferCuit) == 0 &&
				client_getNotPaidSales(pClient, &bufferNotPaidSales) == 0)
			{
				fprintf(pFile, "%d,%s,%s,%s,%d\n", bufferId, BufferLastName, bufferName, bufferCuit,bufferNotPaidSales);
				output = 0;
			}
		}
	}
	return output;
}

int parser_ClientToText(FILE* pFile , LinkedList* pArrayListClient)
{
	int output = -1;
	Client* pClient;
	int bufferId;
	char bufferLastName[BUFFER_LEN];
	char bufferName[BUFFER_LEN];
	char bufferCuit[BUFFER_LEN];
	int len = ll_len(pArrayListClient);

	if (pFile != NULL && pArrayListClient != NULL)
	{
		fprintf(pFile,"ID,APELLIDO,NOMBRE,CUIT\n");
		for(int i = 0; i < len; i++)
		{
			pClient = (Client*) ll_get(pArrayListClient,i);
			if(pClient != NULL &&
			   client_getId(pClient, &bufferId)==0 &&
			   client_getLastName(pClient, bufferLastName)==0 &&
			   client_getName(pClient, bufferName)==0 &&
			   client_getCuit(pClient, bufferCuit)==0)
			{
				fprintf(pFile,"%d,%s,%s,%s\n",bufferId,bufferLastName,bufferName,bufferCuit);
				output = 0;
			}
		}
	}
	return output;
}


int parser_SalesToText(FILE* pFile , LinkedList* pArrayListSales)
{
	int output = -1;
	Sale* pSale;
	int bufferId;
	int bufferClientId;
	int bufferAmount;
	char bufferFileName[BUFFER_LEN];
	int bufferZone;
	int bufferStatus;
	int len = ll_len(pArrayListSales);

	if (pFile != NULL && pArrayListSales != NULL)
	{
		fprintf(pFile, "ID,NOMBRE ARCHIVO,CANTIDAD,ZONA,ESTADO,ID CLIENTE");
		for(int i = 0; i < len ; i++)
		{
			pSale = (Sale*) ll_get(pArrayListSales,i);
			if(pSale != NULL &&
			   sale_getId(pSale, &bufferId)==0 &&
			   sale_getFileName(pSale, bufferFileName)==0 &&
			   sale_getAmount(pSale, &bufferAmount)==0 &&
			   sale_getZone(pSale, &bufferZone)==0 &&
			   sale_getStatus(pSale, &bufferStatus)==0 &&
			   sale_getClientId(pSale, &bufferClientId)==0)
			{
				fprintf(pFile, "%d,%s,%d,%d,%d,%d\n",bufferId,bufferFileName,bufferAmount,bufferZone,bufferStatus,bufferClientId);
				output = 0;
			}
		}
	}
	return output;
}

