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

int parser_ClientFromText(FILE* pFile , LinkedList* pArrayListClient);
int parser_SalesFromText(FILE* pFile , LinkedList* pArrayListClient);
int parser_paidListToText(FILE* pFile , LinkedList* pArrayListEmployee);
int parser_notPaidListToText(FILE* pFile , LinkedList* pArrayListEmployee);


#endif /* PARSER_H_ */
