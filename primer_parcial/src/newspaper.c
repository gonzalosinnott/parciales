/*
 ============================================================================
 Name        : newspaper.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Library newspaper.c
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "client.h"
#include "publication.h"
#include "utn.h"


#define LEN_NAME 50
#define LEN_FORMATEDCUIT 14 //11-11111111-1
#define QTY_CLIENTS 100

typedef struct
{
	int aux_id;
	char aux_name[LEN_NAME];
	char aux_lastName[LEN_NAME];
	char aux_cuit[LEN_FORMATEDCUIT];
	int aux_publicationNumber;
}ClientAuxiliar;


static int newspaper_pauseMenu(Client* client_list, int client_len, Publication* publication_list, int publication_len);
static int newspaper_activeMenu(Client* client_list, int client_len, Publication* publication_list, int publication_len);
static int newspaper_activePublicationCountbyClientId(Publication* publication_list, int publication_len, int clientId, int* publicationCount);
static int newspaper_clientWithMostAds(Client* client_list, int client_len, Publication* publication_list, int publication_len,int publication_firstLoad);

/**
 * \brief newspaper_getMenu: Menu for choosing options of the program,
 * \param choosenOption* list: Pointer to variable that stores choosen option
 * \return (-1) Error / (0) Ok
 */

int newspaper_getMenu(int* choosenOption)
{
	int retorno = -1;
	if(choosenOption !=NULL)
	{
		if(utn_getIntNumber("\nIngrese una opción:"
						   "\n 1-Alta de cliente."
						   "\n 2-Modificar datos del cliente."
						   "\n 3-Baja de cliente."
						   "\n 4-Publicar."
						   "\n 5-Pausar publicación."
						   "\n 6-Reanudar publicación."
						   "\n 7-Imprimir clientes."
						   "\n 8-Informar."
						   "\n 9-Salir."
						   "\nOpcion:", "\nError.", choosenOption, 3, 9, 1)==0)
		{
			retorno =0;
		}
		else
		{
			*choosenOption = 9;
		}
	}
	return retorno;
}

/**
 * \brief newspaper_removeClientMenu: Asks the user for a client ID and erases it's data and associated publications
 * \param Client* client_list: Pointer to array of clients
 * \param int client_len: Clients Array length
 * \param Publication* publication_list: Pointer to array of publications
 * \param int publication_len: Publications Array length
 * \param int client_firstLoad: Pointer to space in memory where is the variable to indicate if clients array is empty
 * \return (-1) Error / (0) Ok
 */

int newspaper_removeClientMenu(Client* client_list, int client_len,int *client_firstLoad, Publication* publication_list, int publication_len)
{
	int retorno = -1;
	int idToSearch;
	int firstLoad = *client_firstLoad;

	if(client_list !=NULL && client_len > 0 && publication_list !=NULL && publication_len > 0)
	{
		if(*client_firstLoad == FALSE)
		{
			printf("\nERROR. NO HAY CLIENTES INGRESADOS.\n");
		}
		else
		{
			client_printAll(client_list, client_len, firstLoad);
			if(utn_getIntNumber("Ingrese el ID de cliente a eliminar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
			   client_findById(client_list, client_len, idToSearch)== 0)
			{
				client_printById(client_list, client_len, idToSearch);
				publication_printByClientId(publication_list, publication_len,idToSearch);
				if(client_remove(client_list,client_len,idToSearch)==0)
				{
					publication_removebyClientId(publication_list, publication_len, idToSearch);
				}
				for(int i = 0; i < client_len; i++)
				{
					if(client_list[i].client_isEmpty == TRUE)
					{
						*client_firstLoad = FALSE;
					}
					else
					{
						*client_firstLoad = TRUE;
						break;
					}
				}
				retorno = 0;
			}
			else
			{
				printf("\nERROR, ID DE CLIENTE INEXISTENTE.\n");
			}
		}
	}
	return retorno;
}

/**
 * \brief newspaper_addPublicationMenu: Asks the user for a client ID and adds a publication associated to said ID
 * \param Client* client_list: Pointer to array of clients
 * \param int client_len: Clients Array length
 * \param Publication* publication_list: Pointer to array of publications
 * \param int publication_len: Publications Array length
 * \param int client_firstLoad: Pointer to space in memory where is the variable to indicate if clients array is empty
 * \param int publication_firstLoad: Pointer to space in memory where is the variable to indicate if publications array is empty
 * \return (-1) Error / (0) Ok
 */

int newspaper_addPublicationMenu(Client* client_list, int client_len,int client_firstLoad, Publication* publication_list, int publication_len, int* publication_firstLoad)
{
	int retorno = -1;
	int idToSearch;
	int firstLoad;

	if(client_list !=NULL && client_len > 0 && publication_list !=NULL && publication_len > 0)
	{
		if(client_firstLoad == FALSE)
		{
			printf("\nERROR. NO HAY CLIENTES INGRESADOS.\n");
		}
		else
		{
			client_printAll(client_list, client_len, client_firstLoad);
			if(utn_getIntNumber("Ingrese el ID del Cliente:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
			   client_findById(client_list, client_len, idToSearch)== 0)
			{
				publication_add(publication_list, publication_len, &firstLoad, idToSearch);
				*publication_firstLoad = firstLoad;
				retorno = 0;
			}
			else
			{
				printf("\nERROR, ID DE CLIENTE INEXISTENTE.\n");
			}
		}
	}
	return retorno;
}

/**
 * \brief newspaper_publicationStatusMenu: Menu for choosing options for pausing or activating a publication
 * \param Client* client_list: Pointer to array of clients
 * \param int client_len: Clients Array length
 * \param Publication* publication_list: Pointer to array of publications
 * \param int publication_len: Publications Array length
 * \param int publication_firstLoad: Pointer to space in memory where is the variable to indicate if publications array is empty
 * \param choosenOption* list: Pointer to variable that stores choosen option
 * \return (-1) Error / (0) Ok
 */

int newspaper_publicationStatusMenu(Client* client_list, int client_len, Publication* publication_list, int publication_len, int publication_firstLoad, int choosenOption)
{
	int retorno = -1;

	if(client_list !=NULL && client_len > 0 && publication_list !=NULL && publication_len > 0 && choosenOption != 0)
	{
		if(publication_firstLoad == FALSE)
		{
			printf("\nERROR. NO HAY PUBLICACIONES INGRESADAS.\n");
		}
		else
		{
			switch(choosenOption)
			{
				case 5:
					newspaper_pauseMenu(client_list, client_len, publication_list, publication_len);
					break;
				case 6:
					newspaper_activeMenu(client_list, client_len, publication_list, publication_len);
					break;
			}
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief newspaper_pauseMenu: Asks the user for a publication ID and changes its publication_status to PAUSED
 * \param Client* client_list: Pointer to array of clients
 * \param int client_len:Clients Array length
 * \param Publication* publication_list: Pointer to array of publications
 * \param int publication_len: Publications Array length
 * \return (-1) Error / (0) Ok
 */

static int newspaper_pauseMenu(Client* client_list, int client_len, Publication* publication_list, int publication_len)
{
	int retorno = -1;
	int idToSearch;
	int clientId;
	int indexToModify;

	if(client_list !=NULL && client_len > 0 && publication_list !=NULL && publication_len > 0)
	{
		publication_printActive(publication_list, publication_len);
		if(utn_getIntNumber("\nIngrese el ID de publicacion a pausar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   publication_findById(publication_list, publication_len, idToSearch, &clientId)== 0)
		{
			indexToModify = publication_findIndexById(publication_list, publication_len, idToSearch);
			if(strcmp(publication_list[indexToModify].publication_status,ACTIVE)==0)
			{
				publication_printById(publication_list, publication_len, idToSearch);
				client_printById(client_list, client_len, clientId);
				publication_pause(publication_list, publication_len, idToSearch);
				retorno = 0;
			}
			else
			{
				printf("\nERROR, PUBLICIDAD YA PAUSADA.\n");
			}
		}
		else
		{
			printf("\nERROR, ID DE PUBLICACION INEXISTENTE.\n");
		}
	}
	return retorno;
}

/**
 * \brief newspaper_activeMenu: Asks the user for a publication ID and changes its publication_status to ACTIVE
 * \param Client* client_list: Pointer to array of clients
 * \param int client_len:Clients Array length
 * \param Publication* publication_list: Pointer to array of publications
 * \param int publication_len: Publications Array length
 * \return (-1) Error / (0) Ok
 */

static int newspaper_activeMenu(Client* client_list, int client_len, Publication* publication_list, int publication_len)
{
	int retorno = -1;
	int idToSearch;
	int clientId;
	int indexToModify;

	if(client_list !=NULL && client_len > 0 && publication_list !=NULL && publication_len > 0)
	{
		publication_printPaused(publication_list, publication_len);
		if(utn_getIntNumber("\nIngrese el ID de publicacion a reanudar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   publication_findById(publication_list, publication_len, idToSearch, &clientId)== 0)
		{
			indexToModify = publication_findIndexById(publication_list, publication_len, idToSearch);
			if(strcmp(publication_list[indexToModify].publication_status,PAUSED)==0)
			{
				publication_printById(publication_list, publication_len, idToSearch);
				client_printById(client_list, client_len, clientId);
				publication_active(publication_list, publication_len, idToSearch);
				retorno = 0;
			}
			else
			{
				printf("\nERROR, PUBLICIDAD YA ACTIVA.\n");
			}
		}
		else
		{
			printf("\nERROR, ID DE PUBLICACION INEXISTENTE.\n");
		}
	}
	return retorno;
}

/**
 * \brief newspaper_printClientsWithActivePublications: Prints the clients info with number of publications associated to each client
 * \param Client* client_list: Pointer to array of clients
 * \param int client_len: Clients Array length
 * \param Publication* publication_list: Pointer to array of publications
 * \param int publication_len: Publications Array length
 * \param int client_firstLoad: Pointer to space in memory where is the variable to indicate if clients array is empty
 * \return (-1) Error / (0) Ok
 */

int newspaper_printClientsWithActivePublications(Client* client_list, int client_len,int client_firstLoad, Publication* publication_list, int publication_len)
{
	int retorno = -1;
	int publicationCount;
	int idClient;
	if(client_list !=NULL && client_len > 0 && publication_list !=NULL && publication_len > 0)
	{
		if(client_firstLoad == FALSE)
		{
			printf("\nERROR. NO HAY CLIENTES INGRESADOS.\n");
		}
		else
		{
			printf("-------------------------------------------------------------------------------------\n");
			printf("|             LISTADO DE CLIENTES CON CANTIDAD DE PUBLICACIONES ACTIVAS             |\n");
			printf("-------------------------------------------------------------------------------------\n");
			printf("| APELLIDO        | NOMBRE          | CUIT            |  ID  |   ANUNCIOS ACTIVOS   |\n");
			printf("-------------------------------------------------------------------------------------\n");
			for(int i=0;i< client_len ;i++)
			{
				if(client_list[i].client_isEmpty == FALSE)
				{
					idClient = client_list[i].client_id;
					newspaper_activePublicationCountbyClientId(publication_list, publication_len, idClient, &publicationCount);
					printf("| %-16s| %-16s| %-16s| %-4d | %-21d|\n",
							client_list[i].client_lastName,
							client_list[i].client_name,
							client_list[i].client_cuit,
							client_list[i].client_id,
							publicationCount);
					printf("-------------------------------------------------------------------------------------\n");
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief newspaper_activePublicationCountbyClientId: Returns the number of publications associated to a given client ID
 * \param Publication* publication_list: Pointer to array of publications
 * \param int publication_len: Publications Array length
 * \param int clientId: Value of client_ID to search associated publications
 * \param int publicationCount: Pointer to space in memory where number of publications associated to given ID will be stored
 * \return (-1) Error / (0) Ok
 */

static int newspaper_activePublicationCountbyClientId(Publication* publication_list, int publication_len, int clientId, int* publicationCount)
{
	int retorno = -1;
	int count = 0;

	if(publication_list !=NULL && publication_len > 0 && clientId > 0 && publicationCount != NULL)
	{
		for(int i=0;i< publication_len ;i++)
		{
			if(publication_list[i].publication_isEmpty == FALSE && strcmp(publication_list[i].publication_status,ACTIVE)==0 && publication_list[i].publication_idClient == clientId)
			{
				count++;
			}
		}
		*publicationCount = count;
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief newspaper_getReportMenu: Menu for choosing options for:
 * -Client with the most publications
 * -Amount of PAUSED publications
 * -Category with the most publications
 * \param Client* client_list: Pointer to array of clients
 * \param int client_len: Clients Array length
 * \param int client_firstLoad: Pointer to space in memory where is the variable to indicate if clients array is empty
 * \param Publication* publication_list: Pointer to array of publications
 * \param int publication_len: Publications Array length
 * \param int publication_firstLoad: Pointer to space in memory where is the variable to indicate if publications array is empty
 * \return (-1) Error / (0) Ok
 */

int newspaper_getReportMenu(Client* client_list, int client_len,int client_firstLoad, Publication* publication_list, int publication_len, int publication_firstLoad)
{
	int retorno = -1;
	int choosenOption;

	if(client_list !=NULL && client_len > 0 && publication_list !=NULL && publication_len > 0)
	{
		if(client_firstLoad == FALSE)
		{
			printf("\nERROR. NO HAY CLIENTES INGRESADOS.\n");
		}
		else
		{
			if(utn_getIntNumber("\nIngrese una opción:"
								"\n 1-Cliente con mas avisos."
								"\n 2-Cantidad de avisos pausados."
								"\n 3-Rubro con mas avisos."
								"\n 4-Salir."
								"\nOpcion:", "\nError.", &choosenOption, 3, 4, 1)==0)
			{
				switch(choosenOption)
				{
					case 1:
						newspaper_clientWithMostAds(client_list, client_len, publication_list, publication_len, publication_firstLoad);
						break;
					case 2:
						publication_countPaused(publication_list,publication_len,publication_firstLoad);
						break;
					case 3:
						publication_countCategory(publication_list, publication_len, publication_firstLoad);
						break;
				}
				retorno =0;
			}
		}
	}
	return retorno;
}

/**
 * \brief newspaper_clientWithMostAds: Prints the information of the clients with the most publications
 * \param Client* client_list: Pointer to array of clients
 * \param int client_len: Clients Array length
 * \param Publication* publication_list: Pointer to array of publications
 * \param int publication_len: Publications Array length
 * \param int publication_firstLoad: Pointer to space in memory where is the variable to indicate if publications array is empty
 * \return (-1) Error / (0) Ok
 */

static int newspaper_clientWithMostAds(Client* client_list, int client_len, Publication* publication_list, int publication_len,int publication_firstLoad)
{
	int retorno = -1;
	int count;
	int maxCount = 0;
	int idClient;

	ClientAuxiliar arrayAux[QTY_CLIENTS];

	if(client_list !=NULL && client_len > 0 && publication_list !=NULL && publication_len > 0)
	{
		if(publication_firstLoad == FALSE)
		{
			printf("\nERROR. NO HAY PUBLICIDADES INGRESADAS.\n");
		}
		else
		{
			for(int i=0;i< client_len ;i++)
			{
				if(client_list[i].client_isEmpty == FALSE)
				{
					count = 0;
					idClient = client_list[i].client_id;
					for(int j=0;j< publication_len ;j++)
					{

						if(publication_list[j].publication_isEmpty == FALSE && publication_list[j].publication_idClient == idClient)
						{
							count++;
							if(count>=maxCount)
							{
								maxCount = count;
								arrayAux[i].aux_id=client_list[i].client_id;
								strncpy(arrayAux[i].aux_name,client_list[i].client_name,LEN_NAME);
								strncpy(arrayAux[i].aux_lastName,client_list[i].client_lastName,LEN_NAME);
								strncpy(arrayAux[i].aux_cuit,client_list[i].client_cuit,LEN_FORMATEDCUIT);
								arrayAux[i].aux_publicationNumber = count;
							}
						}
					}
				}
			}
			printf("-------------------------------------------------------------------------------------\n");
			printf("|                          CLIENTES CON MAS PUBLICIDADES                            |\n");
			printf("-------------------------------------------------------------------------------------\n");
			printf("| APELLIDO        | NOMBRE          | CUIT            |  ID  | CANTIDAD DE ANUNCIOS |\n");
			printf("-------------------------------------------------------------------------------------\n");
			for(int i=0;i< 100  ;i++)
			{
				if(arrayAux[i].aux_publicationNumber == maxCount)
				{
					printf("| %-16s| %-16s| %-16s| %-4d | %-21d|\n",
							arrayAux[i].aux_lastName,
							arrayAux[i].aux_name,
							arrayAux[i].aux_cuit,
							arrayAux[i].aux_id,
							maxCount);
					printf("-------------------------------------------------------------------------------------\n");
				}
			}
		}
	}
	return retorno;
}



