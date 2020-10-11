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



/**
 * \brief getMenu: Menu for choosing options of the program,
 * \param choosenOption* list: Pointer to variable that stores choosen option
 * \return (-1) Error / (0) Ok
 */

int newspaper_getMenu(int* choosenOption)
{
	int retorno = -1;
	if(utn_getIntNumber("\nIngrese una opción:"
					   "\n 1-Alta de cliente."
					   "\n 2-Modificar datos del client."
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
	return retorno;
}


int newspaper_removeClientMenu(Client* client_list, int client_len,int *client_firstLoad, Publication* publication_list, int publication_len)
{
	int retorno = -1;
	int idToSearch;

	if(*client_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY CLIENTES INGRESADOS.\n");
	}
	else
	{
		if(utn_getIntNumber("Ingrese el ID a eliminar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   client_findById(client_list, client_len, idToSearch)== 0)
		{
			client_printById(client_list, client_len, idToSearch);
			publication_printByClientId(publication_list, publication_len,idToSearch);
			client_remove(client_list,client_len,idToSearch);
			publication_removebyClientId(publication_list, publication_len, idToSearch);
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
			printf("\nERROR, ID INEXISTENTE.\n");
		}

	}
	return retorno;
}

int newspaper_addPublicationMenu(Client* client_list, int client_len,int client_firstLoad, Publication* publication_list, int publication_len, int* publication_firstLoad)
{
	int retorno = -1;
	int idToSearch;
	int firstLoad;

	if(client_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY CLIENTES INGRESADOS.\n");
	}
	else
	{
		if(utn_getIntNumber("Ingrese el ID del Cliente:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   client_findById(client_list, client_len, idToSearch)== 0)
		{
			publication_add(publication_list, publication_len, &firstLoad, idToSearch);
			*publication_firstLoad = firstLoad;
		}
		else
		{
			printf("\nERROR, ID INEXISTENTE.\n");
		}
	}
	return retorno;
}
