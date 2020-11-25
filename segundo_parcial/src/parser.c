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
