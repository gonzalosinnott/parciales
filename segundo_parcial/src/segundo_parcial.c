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

#define TRUE 1
#define FALSE 0

int main(void)
{


	LinkedList* clientsList = ll_newLinkedList();
	LinkedList* salesList = ll_newLinkedList();

	controller_loadClientsFromText(PATHCLIENTS, clientsList);
	controller_loadSalesFromText(PATHSALES, salesList);

	controller_ListClients(clientsList);
	controller_ListSales(salesList);


}
