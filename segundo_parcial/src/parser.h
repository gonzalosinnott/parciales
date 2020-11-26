 /*
 ============================================================================
 Name        : parser.h
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header for Library parser.c
 ============================================================================
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "LinkedList.h"

 int parser_ClientFromText(FILE* pFile , LinkedList* ListClient);
 int parser_SalesFromText(FILE* pFile , LinkedList* ListClient);
 int parser_paidListToText(FILE* pFile , LinkedList* ListPaid);
int parser_notPaidListToText(FILE* pFile , LinkedList* ListNotPaid);
int parser_ClientToText(FILE* pFile , LinkedList* ListClient);
int parser_SalesToText(FILE* pFile , LinkedList* ListSales);


#endif /* PARSER_H_ */
