/*
 ============================================================================
 Name        : segundo_parcial.c
 Author      : Sinnott Segura Gonzalo
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>

#include "clients.h"
#include "controller.h"
#include "LinkedList.h"
#include "utn.h"
#include "menu.h"

#define PATHCLIENTS "clientes.txt"
#define PATHSALES "ventas.txt"
#define ADDCLIENTSUCCESS "\nREGISTRO DE CLIENTE CARGADO CON EXITO\n"
#define ADDCLIENTERROR "\nERROR EN LA CARGA DEL CLIENTE\n"
#define ADDSALESUCCESS "\nREGISTRO DE VENTAS CARGADO CON EXITO\n"
#define ADDSALEERROR "\nERROR EN LA CARGA DE LA VENTA\n"
#define MODIFYSALESUCCESS "\nREGISTRO DE VENTAS MODIFICADO CON EXITO\n"
#define MODIFYSALEERROR "\nERROR EN LA MODIFICACION DE LA VENTA\n"
#define CHARGESALESUCCESS "\nREGISTRO DE VENTAS COBRADO CON EXITO\n"
#define CHARGESALEERROR "\nVENTA NO COBRADA\n"

#define TRUE 1
#define FALSE 0

int main(void)
{
	int choosenOption;


	LinkedList* clientsList = ll_newLinkedList();
	LinkedList* salesList = ll_newLinkedList();

	if(controller_loadClientsFromText(PATHCLIENTS, clientsList)== 0 &&
	   controller_loadSalesFromText(PATHSALES, salesList)== 0)
	{

		do
		{
			menu_getMainMenu(&choosenOption);
			switch(choosenOption)
			{
				case 1://Agregar cliente
					if(controller_addClient(clientsList)==0)
					{
						printf(ADDCLIENTSUCCESS);
					}
					else
					{
						printf(ADDCLIENTERROR);
					}
					break;
				case 2://Vender afiche
					if(controller_addSale(clientsList,salesList)==0)
					{
						printf(ADDSALESUCCESS);
					}
					else
					{
						printf(ADDSALEERROR);
					}
					break;
				case 3://Editar ventas no cobradas
					if(controller_modifySale(clientsList,salesList)==0)
					{
						printf(MODIFYSALESUCCESS);
					}
					else
					{
						printf(MODIFYSALEERROR);
					}
					break;
				case 4://Cobrar ventas no cobradas
					if(controller_chargeSale(clientsList,salesList)==0)
					{
						printf(CHARGESALESUCCESS);
					}
					else
					{
						printf(CHARGESALEERROR);
					}
					break;
				case 7://CONTROL DE LISTAS
					controller_ListClients(clientsList);
					controller_ListSales(salesList);
					break;

			}

		}while(choosenOption!=8);


	}

}
