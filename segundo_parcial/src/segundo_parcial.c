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
#define ADDSUCCESS "\nREGISTRO DE CLIENTE CARGADO CON EXITO\n"
#define ADDERROR "\nERROR EN LA CARGA DEL CLIENTE\n"

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
						printf(ADDSUCCESS);
					}
					else
					{
						printf(ADDERROR);
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
