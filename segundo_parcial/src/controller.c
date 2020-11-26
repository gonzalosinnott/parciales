/*
============================================================================
Name        : Controller.C
Author      : Gonzalo Sinnott Segura
Version     :
Copyright   :
Description : Library Controller.c
============================================================================
*/

#include <stdio_ext.h>
#include <stdlib.h>
#include <limits.h>

#include "parser.h"
#include "LinkedList.h"
#include "clients.h"
#include "sales.h"
#include "utn.h"
#include "menu.h"

#define CLIENT_HEADER "-------------------------------------------------------------\n| APELLIDO        | NOMBRE          | CUIT            | ID  |\n-------------------------------------------------------------\n"
#define SALE_HEADER "--------------------------------------------------------------------------------------\n|  ID  | ARCHIVO                  | CANTIDAD  |  ESTADO   |    ZONA     | ID CLIENTE |\n--------------------------------------------------------------------------------------\n"
#define MODIFYERROR_MSJ "ERROR, EL CAMPO NO PUDO SER MODIFICADO"

static int controller_findClientPostersSold(LinkedList* clientList,LinkedList* salesList, int order);
static int controller_findSalePostersSold(LinkedList* clientList,LinkedList* salesList, int order);
static int controller_printSalesWithClientInfo(LinkedList* ListClients,LinkedList* ListSales);


/*
 * \brief controller_loadFromText: Carga los datos de los empleados desde el archivo data.csv (modo texto).
 * \param path char*: ruta del archivo a cargar
 * \param pArrayListEmployee LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int controller_loadClientsFromText(char* path, LinkedList* pArrayList)
{
	int output = -1;
	FILE *pArch;

	ll_clear(pArrayList);

	if (path != NULL && pArrayList != NULL)
	{
		pArch = fopen(path, "r");
		if (pArch != NULL)
		{
			output = parser_ClientFromText(pArch, pArrayList);
		}
		else
		{
			printf("ERROR, EL ARCHIVO NO EXISTE");
		}
	}
	fclose(pArch);
	return output;
}

int controller_loadSalesFromText(char* path, LinkedList* pArrayList)
{
	int output = -1;
	FILE *pArch;

	ll_clear(pArrayList);

	if (path != NULL && pArrayList != NULL)
	{
		pArch = fopen(path, "r");
		if (pArch != NULL)
		{
			output = parser_SalesFromText(pArch, pArrayList);
		}
		else
		{
			printf("ERROR, EL ARCHIVO NO EXISTE");
		}
	}
	fclose(pArch);
	return output;
}

int controller_saveClientsToText(char* path, LinkedList* pArrayList)
{
	int output = -1;
	FILE *pArch;

	if (path != NULL && pArrayList != NULL)
	{
		pArch = fopen(path, "w");
		if (pArch != NULL)
		{
			output = parser_ClientToText(pArch, pArrayList);
		}
		else
		{
			printf("\nERROR, NO SE PUDO GUARDAR EL ARCHIVO\n");
		}
	}
	fclose(pArch);
	return output;
}


int controller_saveSalesToText(char* path, LinkedList* pArrayList)
{
	int output = -1;
	FILE *pArch;

	if (path != NULL && pArrayList != NULL)
	{
		pArch = fopen(path, "w");
		if (pArch != NULL)
		{
			output = parser_SalesToText(pArch, pArrayList);
		}
		else
		{
			printf("\nERROR, NO SE PUDO GUARDAR EL ARCHIVO\n");
		}
	}
	fclose(pArch);
	return output;
}

/** \brief controller_ListClients: Imprime la lista de clientes
 * \param pArrayListEmployee LinkedList*: puntero al array de empleados
 * \return (-1) Error / (0) Ok
 */

int controller_ListClients(LinkedList* pArrayListClients)
{
    int output = -1;

    if(pArrayListClients != NULL)
    {
    	printf("-------------------------------------------------------------\n");
		printf("|                    LISTADO DE CLIENTES                    |\n");
		printf(CLIENT_HEADER);
		output = ll_map(pArrayListClients, client_printSingleWithMap);
    }
	return output;
}


int controller_ListSales(LinkedList* pArrayListSales)
{
    int output = -1;

    if(pArrayListSales != NULL)
    {
		printf("--------------------------------------------------------------------------------------\n");
		printf("|                                 LISTADO DE VENTAS                                  |\n");
		printf(SALE_HEADER);
   		output = ll_map(pArrayListSales, sale_printSingleWithMap);
    }
	return output;
}

int controller_addClient(LinkedList* pArrayList)
{
	int output = -1;
	Client* pClient;
	Client bufferClient;

	if (pArrayList != NULL)
	{
		pClient = client_new();
		if(pClient != NULL &&
		   utn_getString("Ingrese Apellido: ", "Error", bufferClient.client_lastName, 3, sizeof(bufferClient.client_lastName)) == 0 &&
		   utn_getString("Ingrese Nombre: ", "Error", bufferClient.client_name, 3, sizeof(bufferClient.client_name)) == 0 &&
		   utn_getCuit("Ingrese CUIT (SIN GUIONES): ", "Error", bufferClient.client_cuit, 3,LEN_CUIT) == 0)
		{
			bufferClient.client_id = client_generateNewId(pArrayList);
			if (client_cuitExists(pArrayList, bufferClient.client_cuit) != 0)
			{
				client_setLastName(pClient, bufferClient.client_lastName);
				client_setName(pClient, bufferClient.client_name);
				client_setCuit(pClient, bufferClient.client_cuit);
				client_setId(pClient,bufferClient.client_id);
				output = ll_add(pArrayList, pClient);
			}
			else
			{
				printf("\nERROR, EL CUIT INGRESADO YA PERTENECE A UN CLIENTE REGISTRADO\n");
				client_delete(pClient);
			}
		}
	}
	return output;
}

int controller_addSale(LinkedList* pArrayListClients,LinkedList* pArrayListSales)
{
	int output = -1;
	int clientId;
	Sale* pSale;
	Sale bufferSale;

	if (pArrayListClients != NULL && pArrayListSales != NULL  )
	{
		pSale = sale_new();
		controller_ListClients(pArrayListClients);
		utn_getIntNumber("Ingrese ID del Cliente: ", "Error, ", &clientId, 3, client_findMaxId(pArrayListClients), 1);
		if(client_findById(pArrayListClients, clientId)!=NULL)
		{
			if(pSale != NULL &&
			   utn_getAlphaNum("Ingrese Nombre del archivo: ", "Error", bufferSale.sale_fileName, 3, sizeof(bufferSale.sale_fileName)) == 0 &&
			   utn_getIntNumber("Ingrese cantidad de Afiches: ", "Error", &bufferSale.sale_amount, 3, INT_MAX, 1) == 0 &&
			   utn_getIntNumber("Ingrese zona (1-CABA, 2-ZONA SUR, 3-ZONA OESTE): ", "Error", &bufferSale.sale_zone, 3, 3, 1) == 0)
			{
				bufferSale.sale_id = sale_generateNewId(pArrayListSales);
				sale_setId(pSale, bufferSale.sale_id);
				sale_setAmount(pSale, bufferSale.sale_amount);
				sale_setClientId(pSale, clientId);
				sale_setFileName(pSale,bufferSale.sale_fileName);
				sale_setStatus(pSale,TO_PAY);
				sale_setZone(pSale,bufferSale.sale_zone);
				output = ll_add(pArrayListSales, pSale);

			}
			output = 0;
		}
		else
		{
			printf("ERROR NO EXISTE EL ID INGRESADO");
			sale_delete(pSale);
		}
	}
	return output;
}

int controller_modifySale(LinkedList* pArrayListClients,LinkedList* pArrayListSales)
{
	int output = -1;
	int Id;
	int choosenOption;

	LinkedList* toPayList = NULL;

	Sale* pSale;
	Sale bufferSale;
	Client* pClient;

	if (pArrayListClients != NULL && pArrayListSales != NULL  )
	{
		toPayList = ll_clone(pArrayListSales);
		if(toPayList!=NULL)
		{
			if(ll_filter(toPayList, sale_filterByNotPayed)==0)
			{
				controller_ListSales(toPayList);
				utn_getIntNumber("Ingrese ID de la venta a modificar: ", "Error, ", &Id, 3, sale_findMaxId(toPayList), 1);
				pSale = sales_findById(toPayList, Id);
				if(pSale!=NULL)
				{
					sale_getClientId(pSale, &bufferSale.sale_clientId);
					pClient = client_findById(pArrayListClients, bufferSale.sale_clientId);
					printf("\nLa publicacion: \n");
					printf(SALE_HEADER);
					sale_printSingleWithMap(pSale);
					printf("Pertenece al cliente: \n");
					printf(CLIENT_HEADER);
					client_printSingleWithMap(pClient);
					do
					{
						menu_getModifyMenu(&choosenOption);
						switch (choosenOption)
						{
							case 1:
								if (utn_getAlphaNum("Ingrese nombre del archivo: ", "Error", bufferSale.sale_fileName, 3, sizeof(bufferSale.sale_fileName)) == 0)
								{
									sale_setFileName(pSale, bufferSale.sale_fileName);
									output = 0;
								}
								else
								{
									printf(MODIFYERROR_MSJ);
								}
								break;
							case 2:
								if (utn_getIntNumber("Ingrese Cantidad: ", "Error", &bufferSale.sale_amount, 3,INT_MAX ,1) == 0)
								{
									sale_setAmount(pSale, bufferSale.sale_amount);
									output = 0;
								}
								else
								{
									printf(MODIFYERROR_MSJ);
								}
								break;
							case 3:
								if (utn_getIntNumber("Ingrese zona (1-CABA, 2-ZONA SUR, 3-ZONA OESTE):", "Error", &bufferSale.sale_zone, 3,3 ,1) == 0)
								{
									sale_setZone(pSale, bufferSale.sale_zone);
									output = 0;
								}
								else
								{
									printf(MODIFYERROR_MSJ);
								}
								break;
						}
					} while (choosenOption != 4);
				}
				else
				{
					printf("ERROR EL ID INGRESADO NO SE PUEDE MODIFICAR");
				}
			}
		}
	}
	ll_clear(toPayList);
	ll_deleteLinkedList(toPayList);
	return output;
}


int controller_chargeSale(LinkedList* pArrayListClients,LinkedList* pArrayListSales)
{
	int output = -1;
	int Id;
	int choosenOption;

	LinkedList* toPayList = NULL;

	Sale* pSale;
	Sale bufferSale;
	Client* pClient;

	if (pArrayListClients != NULL && pArrayListSales != NULL  )
	{
		toPayList = ll_clone(pArrayListSales);
		if(toPayList!=NULL)
		{
			if(ll_filter(toPayList, sale_filterByNotPayed)==0)
			{
				controller_ListSales(toPayList);
				utn_getIntNumber("Ingrese ID de la venta a modificar: ", "Error, ", &Id, 3, sale_findMaxId(toPayList), 1);
				pSale = sales_findById(toPayList, Id);
				if(pSale!=NULL)
				{
					sale_getClientId(pSale, &bufferSale.sale_clientId);
					pClient = client_findById(pArrayListClients, bufferSale.sale_clientId);
					printf("\nLa publicacion: \n");
					printf(SALE_HEADER);
					sale_printSingleWithMap(pSale);
					printf("Pertenece al cliente: \n");
					printf(CLIENT_HEADER);
					client_printSingleWithMap(pClient);
					utn_getIntNumber("¿Desea cobrar la venta?\n 1-SI\n 2-NO\nOpcion: ", "Error ", &choosenOption, 3, 2, 1);
					if(choosenOption== 1)
					{
						sale_setStatus(pSale, PAID);
						output = 0;
					}
				}
				else
				{
					printf("ERROR EL ID INGRESADO NO SE PUEDE COBRAR");
				}
			}
		}
	}
	ll_clear(toPayList);
	ll_deleteLinkedList(toPayList);
	return output;
}

int controller_createPaidReport(LinkedList* pArrayListClients,LinkedList* pArrayListSales)
{
	int output = -1;
	int bufferClientId;
	int salesQuantity = 0;
	Client* pClient;

	LinkedList* salesPaidList = ll_clone(pArrayListSales);
	LinkedList* clientPaidList = ll_newLinkedList();


	if (pArrayListClients != NULL && pArrayListSales != NULL &&
		ll_filter(salesPaidList, sale_filterByPayed)==0)
	{
		for(int i = 0; i < ll_len(pArrayListClients);i++)
		{
			if((pClient = (Client*) ll_get(pArrayListClients,i))!=NULL)
			{

				client_getId(pClient, &bufferClientId);
				sale_getSalesByClientId(salesPaidList,bufferClientId,&salesQuantity);
				client_setPaidSales(pClient, salesQuantity);
				output= ll_add(clientPaidList,pClient);
			}
		}
		printf("\n-----------------------------------------------------------------------------\n");
		printf("|                LISTADO DE CLIENTES CON NUMERO DE VENTAS PAGAS             |");
		printf("\n-----------------------------------------------------------------------------\n");
		printf("|  ID  | APELLIDO        | NOMBRE          | CUIT            | VENTAS PAGAS |");
	    printf("\n-----------------------------------------------------------------------------\n");
		ll_map(clientPaidList, client_printPaidWithMap);

		FILE *pArch;
		if (clientPaidList != NULL)
		{
			pArch = fopen("ventaspagas.txt", "w");
			if (pArch != NULL)
			{
				parser_paidListToText(pArch, clientPaidList);
			}
			else
			{
				printf("\nERROR, NO SE PUDO GUARDAR EL ARCHIVO\n");
			}
		}
		fclose(pArch);
	}
	else
	{
		printf("NO EXISTEN VENTAS PAGAS");
	}
	ll_clear(salesPaidList);
	ll_deleteLinkedList(salesPaidList);
	ll_clear(clientPaidList);
	ll_deleteLinkedList(clientPaidList);
	return output;
}


int controller_createNotPaidReport(LinkedList* pArrayListClients,LinkedList* pArrayListSales)
{
	int output = -1;
	int bufferClientId;
	int salesQuantity = 0;
	Client* pClient;

	LinkedList* salesNotPaidList = ll_clone(pArrayListSales);
	LinkedList* clientNotPaidList = ll_newLinkedList();


	if (pArrayListClients != NULL && pArrayListSales != NULL &&
		ll_filter(salesNotPaidList, sale_filterByNotPayed)==0)
	{
		for(int i = 0; i < ll_len(pArrayListClients);i++)
		{
			if((pClient = (Client*) ll_get(pArrayListClients,i))!=NULL)
			{

				client_getId(pClient, &bufferClientId);
				sale_getSalesByClientId(salesNotPaidList,bufferClientId,&salesQuantity);
				client_setNotPaidSales(pClient, salesQuantity);
				output= ll_add(clientNotPaidList,pClient);
			}
		}
		printf("\n-------------------------------------------------------------------------------\n");
		printf("|                LISTADO DE CLIENTES CON NUMERO DE VENTAS IMPAGAS             |");
		printf("\n-------------------------------------------------------------------------------\n");
		printf("|  ID  | APELLIDO        | NOMBRE          | CUIT            | VENTAS IMPAGAS |");
		printf("\n-------------------------------------------------------------------------------\n");
		ll_map(clientNotPaidList, client_printNotPaidWithMap);

		FILE *pArch;
		if (clientNotPaidList != NULL)
		{
			pArch = fopen("ventasnopagas.txt", "w");
			if (pArch != NULL)
			{
				parser_notPaidListToText(pArch, clientNotPaidList);
			}
			else
			{
				printf("\nERROR, NO SE PUDO GUARDAR EL ARCHIVO\n");
			}
		}
		fclose(pArch);
	}
	else
	{
		printf("NO EXISTEN VENTAS IMPAGAS");
	}
	ll_clear(salesNotPaidList);
	ll_deleteLinkedList(salesNotPaidList);
	ll_clear(clientNotPaidList);
	ll_deleteLinkedList(clientNotPaidList);
	return output;
}

int controller_generateStatistics(LinkedList* pListClients,LinkedList* pListSales)
{
	int output = -1;
	int choosenOption;

	LinkedList* salesPaidList = ll_clone(pListSales);

	if (pListClients != NULL && pListSales != NULL &&
		ll_filter(salesPaidList, sale_filterByPayed)==0)
	{
		do
		{
			menu_getStatisticsMenu(&choosenOption);
			switch(choosenOption)
			{
				case 1:
				case 2:
					controller_findClientPostersSold(pListClients,salesPaidList,choosenOption);
					break;
				case 3:
					controller_findSalePostersSold(pListClients,salesPaidList,choosenOption);
					break;
				}
		}while(choosenOption != 4);
		output = 0;
	}
	else
	{
		printf("NO EXISTEN VENTAS PAGAS");
	}
	return output;
}


static int controller_findClientPostersSold(LinkedList* clientList,LinkedList* salesList, int order)
{
	int output = -1;
	int clientsLen = ll_len(clientList);
	int acumulator;
	int maxValue;
	int client_id;
	Client* bufferClient;
	LinkedList* newList = ll_newLinkedList();
	if(clientList!=NULL && salesList!=NULL)
	{
		for (int i = 0; i< clientsLen;i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient != NULL)
			{
				client_getId(bufferClient, &client_id);
				acumulator = ll_reduceInt(salesList, sale_getPostersbyId,client_id);
				if(i == 0)
				{
					ll_add(newList, bufferClient);
					maxValue = acumulator;
				}
				else
				{
					if((order == 1 && acumulator > maxValue) ||
					   (order == 2 && acumulator < maxValue))
					{
						ll_clear(newList);
						ll_add(newList, bufferClient);
						maxValue = acumulator;
					}
					else if(acumulator == maxValue)
					{
						ll_add(newList, bufferClient);
					}
				}
			}
		}
		if(order ==1)
		{
			printf("\nCLIENTES CON MAS AFICHES PAGOS\n");
		}
		else
		{
			printf("\nCLIENTES CON MENOS AFICHES PAGOS\n");
		}
		printf("\nCANTIDAD: %d\n",maxValue);
		printf("\n-------------------------------------------------------------\n");
		printf("|                    LISTADO DE CLIENTES                    |\n");
		printf(CLIENT_HEADER);
		ll_map(newList,client_printSingleWithMap);
		output = 0;
	}
	ll_clear(newList);
	ll_deleteLinkedList(newList);
	return output;
}

static int controller_findSalePostersSold(LinkedList* clientList,LinkedList* salesList, int order)
{
	int output = -1;
	int salesLen = ll_len(salesList);
	int maxValue;
	int sale_amount;
	Sale* bufferSale;
	LinkedList* newList = ll_newLinkedList();
	if(clientList!=NULL && salesList!=NULL)
	{
		for (int i = 0; i< salesLen;i++)
		{
			bufferSale = ll_get(salesList, i);
			sale_getAmount(bufferSale, &sale_amount);
			if(bufferSale != NULL)
			{
				if(i==0)
				{
					maxValue = sale_amount;
					ll_add(newList, bufferSale);
				}
				else
				{
					if((order == 3 && sale_getAmount2(bufferSale) > maxValue) ||
					   (order == 4 && sale_getAmount2(bufferSale) < maxValue))
					{
						ll_clear(newList);
						ll_add(newList, bufferSale);
						maxValue = sale_amount;
					}
					else if(sale_amount == maxValue)
					{
						ll_add(newList, bufferSale);
					}
				}
			}
		}
		if(order ==3)
		{
			printf("\nVENTAS CON MAS AFICHES PAGOS\n");
		}
		else
		{
			printf("\nVENTAS CON MENOS AFICHES PAGOS\n");
		}
		printf("\nCANTIDAD: %d\n",maxValue);
		controller_printSalesWithClientInfo(clientList, newList);
		output = 0;
	}
	ll_clear(newList);
	ll_deleteLinkedList(newList);
	return output;
}


static int controller_printSalesWithClientInfo(LinkedList* ListClients,LinkedList* ListSales)
{
	int output = -1;
	int indexClient;
	int sale_clientId;
	int sale_id;
	char client_cuit[LEN_FORMATEDCUIT];
	char sale_fileName[LEN_NAME];
	int len = ll_len(ListSales);
	Client* bufferClient;
	Sale* bufferSale;
	if(ListSales != NULL && len > 0)
	{
		printf("\n--------------------------------------------------------\n");
		printf("| ID VENTA |      NOMBRE ARCHIVO      |  CUIT CLIENTE  |");
		printf("\n--------------------------------------------------------\n");
		for(int i = 0; i < len;i++)
		{
			bufferSale = ll_get(ListSales, i);
			sale_getClientId(bufferSale, &sale_clientId);
			indexClient = client_findByIdInt(ListClients, sale_clientId);
			bufferClient = ll_get(ListClients,indexClient);
			sale_getId(bufferSale, &sale_id);
			sale_getFileName(bufferSale, sale_fileName);
			client_getCuit(bufferClient, client_cuit);
			printf("| %-9d| %-25s| %-15s| ",sale_id, sale_fileName, client_cuit);
			printf("\n--------------------------------------------------------\n");

		}

		output = 0;
	}
    return output;
}



