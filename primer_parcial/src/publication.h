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
#define ACTIVE 1
#define PAUSED 0
#define LEN_DESCRIPTION 65


typedef struct
{
	int publication_id;
	int publication_isEmpty;
	int publication_category;
	char publication_description[LEN_DESCRIPTION];
	int publication_idCliente;
	int publication_status;
}Publication;

int publication_initArray(Publication* publication_list, int publication_len);
int publication_addHardcode(Publication* publication_list, int publication_len, int *publication_firstLoad);
int publication_add(Publication* publication_list,int publication_len, int *publication_firstLoad, int clientId);
int publication_modifyMenu(Publication* publication_list, int publication_len, int publication_firstLoad);
int publication_removeMenu(Publication* publication_list, int publication_len,int *publication_firstLoad);
int publication_removebyClientId(Publication* publication_list, int publication_len,int idCliente);
int publication_printAll(Publication* publication_list, int publication_len,int publication_firstLoad);
int publication_printByClientId(Publication* publication_list, int publication_len,int idCliente);



#endif /* PUBLICATION_H_ */
