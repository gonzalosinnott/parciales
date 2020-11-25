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
		printf("-------------------------------------------------------------\n");
		printf("| APELLIDO        | NOMBRE          | CUIT            | ID  |\n");
		printf("-------------------------------------------------------------\n");
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
		printf("--------------------------------------------------------------------------------------\n");
		printf("|  ID  | ARCHIVO                  | CANTIDAD  |  ESTADO   |    ZONA     | ID CLIENTE |\n");
		printf("--------------------------------------------------------------------------------------\n");
   		output = ll_map(pArrayListSales, sale_printSingleWithMap);
    }
	return output;
}
