/*
============================================================================
Name        : Controller.h
Author      : Gonzalo Sinnott Segura
Version     :
Copyright   :
Description : Header for Library Controller.c
============================================================================
*/

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "LinkedList.h"


int controller_loadClientsFromText(char* path , LinkedList* pArrayList);
int controller_loadSalesFromText(char* path, LinkedList* pArrayList);
int controller_addClient(LinkedList* pArrayList);
int controller_addSale(LinkedList* pArrayListClients,LinkedList* pArrayListSales);
int controller_modifySale(LinkedList* pArrayListClients,LinkedList* pArrayListSales);
int controller_chargeSale(LinkedList* pArrayListClients,LinkedList* pArrayListSales);


int controller_ListClients(LinkedList* pArrayListClients);
int controller_ListSales(LinkedList* pArrayListClients);



#endif /* CONTROLLER_H_ */
