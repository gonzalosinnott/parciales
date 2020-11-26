/*
============================================================================
Name        : sales.h
Author      : Gonzalo Sinnott Segura
Version     :
Copyright   :
Description : Header for Library sales.c
============================================================================
*/
#include "LinkedList.h"

#ifndef SALES_H_
#define SALES_H_

#define TRUE 1
#define FALSE 0
#define LEN_NAME 4096
#define PAID 1
#define TO_PAY 2
#define CABA 1
#define ZONA_SUR 2
#define ZONA_OESTE 3

typedef struct
{
	int sale_id;
	int sale_clientId;
	int sale_amount;
	char sale_fileName[LEN_NAME];
	int sale_zone;
	int sale_status;

}Sale;

Sale* sale_new();
Sale* sale_newParametros(char* sale_id,char* sale_clientId,char* sale_amount,char* sale_fileName,char* sale_zone, char* sale_status);
void sale_delete();

int sale_setIdFromTxtFile(Sale* this,char* sale_id);
int sale_setId(Sale* this, int sale_id);
int sale_getId(Sale* this,int* sale_id);
int sale_generateNewId(LinkedList* pArrayListSale);
int sale_findMaxId(LinkedList* pArrayListSale);

int sale_setClientIdFromTxtFile(Sale* this,char* sale_clientId);
int sale_setClientId(Sale* this, int sale_clientId);
int sale_getClientId(Sale* this,int* sale_clientId);
int sale_getClientId2(Sale* this);

int sale_setAmountFromTxtFile(Sale* this,char* sale_amount);
int sale_setAmount(Sale* this, int sale_amount);
int sale_getAmount(Sale* this,int* sale_amount);
int sale_getAmount2(Sale* this);

int sale_setFileName(Sale* this,char* sale_fileName);
int sale_getFileName(Sale* this,char* sale_fileName);

int sale_setZoneFromTxtFile(Sale* this,char* sale_zone);
int sale_setZone(Sale* this,int sale_zone);
int sale_getZone(Sale* this,int* sale_zone);

int sale_setStatusFromTxtFile(Sale* this,char* sale_status);
int sale_setStatus(Sale* this,int sale_status);
int sale_getStatus(Sale* this,int* sale_status);

int sale_filterByNotPayed (void* pSale);
int sale_filterByPayed (void* pSale);
int sale_getSalesByClientId(LinkedList* listSale,int clientId,int* salesQuantity);
int sale_getPostersbyId(void* this, int idClient);

void* sales_findById(LinkedList* list, int id);
int sale_printSingleWithMap(void* pSale);

#endif /* SALES_H_ */
