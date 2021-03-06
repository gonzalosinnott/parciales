/*
 ============================================================================
 Name        : publication.h
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header for Library publication.c
 ============================================================================
 */

#ifndef PUBLICATION_H_
#define PUBLICATION_H_

#define TRUE 1
#define FALSE 0
#define ACTIVE "ACTIVA"
#define PAUSED "PAUSADA"
#define LEN_DESCRIPTION 65
#define LEN_CATEGORY 20
#define LEN_STATUS 8

typedef struct
{
	int publication_id;
	int publication_isEmpty;
	char publication_category[LEN_CATEGORY];
	char publication_description[LEN_DESCRIPTION];
	int publication_idClient;
	char publication_status[LEN_STATUS];
}Publication;

int publication_initArray(Publication* publication_list, int publication_len);
int publication_addHardcode(Publication* publication_list, int publication_len, int *publication_firstLoad);
int publication_add(Publication* publication_list,int publication_len, int *publication_firstLoad, int clientId);
int publication_findById(Publication* publication_list, int publication_len,int id, int* clientId);
int publication_findIndexById(Publication* publication_list, int publication_len,int id);
int publication_removebyClientId(Publication* publication_list, int publication_len,int clientId);
int publication_pause(Publication* publication_list, int publication_len,int id);
int publication_active(Publication* publication_list, int publication_len,int id);
int publication_countPaused(Publication* publication_list, int publication_len, int publication_firstLoad);
int publication_countCategory(Publication* publication_list, int publication_len, int publication_firstLoad);
int publication_printAll(Publication* publication_list, int publication_len,int publication_firstLoad);
int publication_printActive(Publication* publication_list, int publication_len);
int publication_printPaused(Publication* publication_list, int publication_len);
int publication_printByClientId(Publication* publication_list, int publication_len,int clientId);
int publication_printById(Publication* publication_list, int publication_len,int Id);




#endif /* PUBLICATION_H_ */
