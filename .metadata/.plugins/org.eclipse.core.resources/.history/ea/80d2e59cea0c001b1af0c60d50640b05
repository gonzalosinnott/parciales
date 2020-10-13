/*
 ============================================================================
 Name        : newspaper.h
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header for Library newspaper.c
 ============================================================================
 */

#ifndef NEWSPAPER_H_
#define NEWSPAPER_H_

#define TRUE 1
#define FALSE 0
#define LEN_NAME 50
#define LEN_FORMATEDCUIT 14 //11-11111111-1


#include "client.h"
#include "publication.h"

int newspaper_getMenu(int* choosenOption);
int newspaper_removeClientMenu(Client* client_list, int client_len,int *client_firstLoad, Publication* publication_list, int publication_len);
int newspaper_addPublicationMenu(Client* client_list, int client_len,int client_firstLoad, Publication* publication_list, int publication_len, int* publication_firstLoad);
int newspaper_publicationStatusMenu(Client* client_list, int client_len, Publication* publication_list, int publication_len, int publication_firstLoad, int choosenOption);
int newspaper_printClientsWithActivePublications(Client* client_list, int client_len,int client_firstLoad, Publication* publication_list, int publication_len);
int newspaper_getReportMenu(Client* client_list, int client_len,int client_firstLoad, Publication* publication_list, int publication_len, int publication_firstLoad);

#endif /* NEWSPAPER_H_ */
