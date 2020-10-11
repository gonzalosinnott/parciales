/*
 ============================================================================
 Name        : cliente.h
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header for Library cliente.c
 ============================================================================
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#define TRUE 1
#define FALSE 0
#define LONG_NAME 50
#define LONG_CUIT 13 //1-11111111-1


typedef struct
{
	int cliente_id;
	int cliente_isEmpty;
	char cliente_name[LONG_NAME];
	char cliente_lastName[LONG_NAME];
	char cliente_cuit[LONG_CUIT];
}Cliente;

int cliente_initArray(Cliente* cliente_list, int cliente_len);
int cliente_addHardcode(Cliente* cliente_list, int cliente_len, int *cliente_firstLoad);
int cliente_alta(Cliente* cliente_list,int cliente_len, int *cliente_firstLoad);
int cliente_modifyMenu(Cliente* cliente_list, int cliente_len, int cliente_firstLoad);
int cliente_removeMenu(Cliente* cliente_list, int cliente_len,int *cliente_firstLoad);
int cliente_print(Cliente* cliente_list, int cliente_len,int cliente_firstLoad);




#endif /* CLIENTE_H_ */
