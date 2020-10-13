/*
 ============================================================================
 Name        : client.h
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header for Library client.c
 ============================================================================
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#define TRUE 1
#define FALSE 0
#define LEN_NAME 50
#define LEN_CUIT 12
#define LEN_FORMATEDCUIT 14

typedef struct
{
	int client_id;
	int client_isEmpty;
	char client_name[LEN_NAME];
	char client_lastName[LEN_NAME];
	char client_cuit[LEN_FORMATEDCUIT];
}Client;

int client_initArray(Client* client_list, int client_len);
int client_addHardcode(Client* client_list, int client_len, int *client_firstLoad);
int client_add(Client* client_list,int client_len, int *client_firstLoad);
int client_findById(Client* client_list, int client_len,int id);
int client_modifyMenu(Client* client_list, int client_len, int client_firstLoad);
int client_removeMenu(Client* client_list, int client_len,int *client_firstLoad);
int client_remove(Client* client_list, int client_len,int id);
int client_printAll(Client* client_list, int client_len,int client_firstLoad);
int client_printById(Client* client_list, int client_len, int idClient);

#endif /* CLIENT_H_ */
