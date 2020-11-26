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
 * \param ListClient LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int parser_ClientFromText(FILE* pFile , LinkedList* ListClient)
{
	int output = -1;
	Client* pClient;
	char bufferHeader[BUFFER_LEN];
	char bufferId[BUFFER_LEN];
	char bufferLastName[BUFFER_LEN];
	char bufferName[BUFFER_LEN];
	char bufferCuit[BUFFER_LEN];

	if (pFile != NULL && ListClient != NULL)
	{
		fscanf(pFile, "%[^\n]\n", bufferHeader);
		do
		{
			if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", bufferId, bufferLastName, bufferName, bufferCuit) == 4)
			{
				pClient = client_newParametros(bufferId, bufferLastName, bufferName, bufferCuit);
				if (pClient != NULL)
				{
					output = ll_add(ListClient, pClient);
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

/*
 * \brief parser_SalesFromText: Parsea los datos de las ventas desde el archivo ventas.txt (modo texto).
 * \param pFile FILE* puntero al archivo a cargar
 * \param ListSales LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int parser_SalesFromText(FILE* pFile , LinkedList* ListSales)
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

	if (pFile != NULL && ListSales != NULL)
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
					output = ll_add(ListSales, pSale);
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

/*
 * \brief parser_paidListToText: Parsea los datos de los clientes con cantidad de ventas pagas
 * hacia el archivo ventaspagas.txt (modo texto).
 * \param pFile FILE* puntero al archivo a cargar
 * \param ListPaid LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int parser_paidListToText(FILE* pFile , LinkedList* ListPaid)
{
	int output = -1;
	Client *pClient;
	int bufferId;
	char BufferLastName[LEN_NAME];
	char bufferName[LEN_NAME];
	char bufferCuit[LEN_FORMATEDCUIT];
	int bufferPaidSales;
	int len;

	if (pFile != NULL && ListPaid != NULL)
	{
		len = ll_len(ListPaid);
		fprintf(pFile, "ID,APELLIDO,NOMBRE,CUIT,CANTIDAD DE VENTAS PAGAS\n");
		for (int i = 0; i < len; i++)
		{
			pClient = (Client*)ll_get(ListPaid, i);
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

/*
 * \brief parser_notPaidListToText: Parsea los datos de los clientes con cantidad de ventas no pagas
 * hacia el archivo ventasnopagas.txt (modo texto).
 * \param pFile FILE* puntero al archivo a cargar
 * \param ListPaid LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int parser_notPaidListToText(FILE* pFile , LinkedList* ListNotPaid)
{
	int output = -1;
	Client *pClient;
	int bufferId;
	char BufferLastName[LEN_NAME];
	char bufferName[LEN_NAME];
	char bufferCuit[LEN_FORMATEDCUIT];
	int bufferNotPaidSales;
	int len;

	if (pFile != NULL && ListNotPaid != NULL)
	{
		len = ll_len(ListNotPaid);
		fprintf(pFile, "ID,APELLIDO,NOMBRE,CUIT,CANTIDAD DE VENTAS IMPAGASPAGAS\n");
		for (int i = 0; i < len; i++)
		{
			pClient = (Client*)ll_get(ListNotPaid, i);
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

/*
 * \brief parser_ClientToText: Parsea los datos de los clientes hacia el archivo clientes.txt (modo texto).
 * \param pFile FILE* puntero al archivo a cargar
 * \param ListClient LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int parser_ClientToText(FILE* pFile , LinkedList* ListClient)
{
	int output = -1;
	Client* pClient;
	int bufferId;
	char bufferLastName[BUFFER_LEN];
	char bufferName[BUFFER_LEN];
	char bufferCuit[BUFFER_LEN];
	int len = ll_len(ListClient);

	if (pFile != NULL && ListClient != NULL)
	{
		fprintf(pFile,"ID,APELLIDO,NOMBRE,CUIT\n");
		for(int i = 0; i < len; i++)
		{
			pClient = (Client*) ll_get(ListClient,i);
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

/*
 * \brief parser_SalesToText: Parsea los datos de las ventas hacia el archivo ventas.txt (modo texto).
 * \param pFile FILE* puntero al archivo a cargar
 * \param ListSales LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int parser_SalesToText(FILE* pFile , LinkedList* ListSales)
{
	int output = -1;
	Sale* pSale;
	int bufferId;
	int bufferClientId;
	int bufferAmount;
	char bufferFileName[BUFFER_LEN];
	int bufferZone;
	int bufferStatus;
	int len = ll_len(ListSales);

	if (pFile != NULL && ListSales != NULL)
	{
		fprintf(pFile, "ID,NOMBRE ARCHIVO,CANTIDAD,ZONA,ESTADO,ID CLIENTE");
		for(int i = 0; i < len ; i++)
		{
			pSale = (Sale*) ll_get(ListSales,i);
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

