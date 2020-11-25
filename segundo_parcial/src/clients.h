/*
============================================================================
Name        : Client.h
Author      : Gonzalo Sinnott Segura
Version     :
Copyright   :
Description : Header for Library Client.c
============================================================================
*/

#include "LinkedList.h"

#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
#define NOMBRE_LEN 500

#define TRUE 1
#define FALSE 0
#define LEN_NAME 4096
#define LEN_FORMATEDCUIT 14

typedef struct
{
	int client_id;
	char client_lastName[LEN_NAME];
	char client_name[LEN_NAME];
	char client_cuit[LEN_FORMATEDCUIT];
}Client;

Client* client_new();
Client* client_newParametros(char* client_id,char* client_lastName,char* client_name, char* client_cuit);
void client_delete();

int client_setIdFromTxtFile(Client* this,char* client_id);
int client_setId(Client* this, int client_id);
int client_getId(Client* this,int* client_id);
int client_generateNewId(LinkedList* pArrayListClient);
int client_findMaxId(LinkedList* pArrayListClient);

int client_setLastName(Client* this,char* client_lastName);
int client_getLastName(Client* this,char* client_lastName);

int client_setName(Client* this,char* client_name);
int client_getName(Client* this,char* client_name);

int client_setCuit(Client* this,char* client_cuit);
int client_getCuit(Client* this,char* client_cuit);

int client_printSingleWithMap(void* pClient);


#endif // CLIENT_H_INCLUDED
