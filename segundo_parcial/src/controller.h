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


 int controller_loadClientsFromText(char* path , LinkedList* List);
 int controller_loadSalesFromText(char* path, LinkedList* List);
 int controller_saveClientsToText(char* path, LinkedList* List);
 int controller_saveSalesToText(char* path, LinkedList* List);


 int controller_addClient(LinkedList* List);
 int controller_addSale(LinkedList* ListClients,LinkedList* ListSales);
 int controller_modifySale(LinkedList* ListClients,LinkedList* ListSales);
 int controller_chargeSale(LinkedList* ListClients,LinkedList* ListSales);
 int controller_createPaidReport(LinkedList* ListClients,LinkedList* ListSales);
 int controller_createNotPaidReport(LinkedList* ListClients,LinkedList* ListSales);
int controller_generateStatistics(LinkedList* ListClients,LinkedList* ListSales);

 int controller_ListClients(LinkedList* ListClients);
 int controller_ListSales(LinkedList* ListSales);



#endif /* CONTROLLER_H_ */
