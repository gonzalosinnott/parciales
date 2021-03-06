/*
 ============================================================================
 Name        : info.h
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header for Library info.c
 ============================================================================
 */

#ifndef INFO_H_
#define INFO_H_

#define TRUE 1
#define FALSE 0
#define ACTIVE "ACTIVA"
#define PAUSED "PAUSADA"

#include "client.h"
#include "publication.h"

int info_getMenu(int* choosenOption);
int info_removeClientMenu(Client* client_list, int client_len,int *client_firstLoad, Publication* publication_list, int publication_len);
int info_addPublicationMenu(Client* client_list, int client_len,int client_firstLoad, Publication* publication_list, int publication_len, int* publication_firstLoad);
int info_publicationStatusMenu(Client* client_list, int client_len, Publication* publication_list, int publication_len, int publication_firstLoad, int choosenOption);
int info_printClientsWithActivePublications(Client* client_list, int client_len,int client_firstLoad, Publication* publication_list, int publication_len);
int info_getReportMenu(Client* client_list, int client_len,int client_firstLoad, Publication* publication_list, int publication_len, int publication_firstLoad);

#endif /* INFO_H_ */
