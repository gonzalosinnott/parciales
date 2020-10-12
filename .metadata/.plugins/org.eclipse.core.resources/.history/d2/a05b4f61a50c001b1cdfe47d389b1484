/*
 ============================================================================
 Name        : primer_parcial.c
 Author      : Sinnott Segura Gonzalo
 Version     :
 Copyright   : 
 Description : Primer parcial Programacion - Laboratorio I
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "newspaper.h"
#include "client.h"
#include "publication.h"


#define TRUE 1
#define FALSE 0
#define QTY_CLIENTS 100
#define QTY_PUBLICATIONS 1000


int main(void) {

	int choosenOption;
	int client_firstLoad = FALSE;
	int publication_firstLoad = FALSE;

	Client arrayClients[QTY_CLIENTS];
	client_initArray(arrayClients, QTY_CLIENTS);
	Publication arrayPublications[QTY_PUBLICATIONS];
	publication_initArray(arrayPublications, QTY_PUBLICATIONS);


	client_addHardcode(arrayClients, QTY_CLIENTS, &client_firstLoad);
	publication_addHardcode(arrayPublications, QTY_PUBLICATIONS, &publication_firstLoad);

	do
		{
			newspaper_getMenu(&choosenOption);
			switch(choosenOption)
			{
				case 1://ALTA CLIENTE (LISTO)
					client_add(arrayClients, QTY_CLIENTS, &client_firstLoad);
					break;
				case 2://MODIFICAR CLIENTE (LISTO)
					client_modifyMenu(arrayClients, QTY_CLIENTS, client_firstLoad);
					break;
				case 3://BAJA CLIENTE (LISTO)
					newspaper_removeClientMenu(arrayClients, QTY_CLIENTS, &client_firstLoad, arrayPublications, QTY_PUBLICATIONS);
					break;
				case 4://ALTA PUBLICACION (LISTO)
					newspaper_addPublicationMenu(arrayClients, QTY_CLIENTS, client_firstLoad, arrayPublications, QTY_PUBLICATIONS, &publication_firstLoad);
					break;
				case 5://PAUSAR PUBLICACION (LISTO)
				case 6://REANUDAR PUBLICACION (LISTO)
					newspaper_publicationStatusMenu(arrayClients, QTY_CLIENTS, arrayPublications, QTY_PUBLICATIONS, publication_firstLoad,choosenOption);
					break;
				case 7://IMPRIMIR CLIENTES CON NUMERO DE PUBLICACIONES
					newspaper_printClientsWithActivePublications(arrayClients, QTY_CLIENTS, client_firstLoad, arrayPublications, QTY_PUBLICATIONS);
					break;
				case 8://INFORMES
					publication_printAll(arrayPublications, QTY_PUBLICATIONS, publication_firstLoad);
					client_printAll(arrayClients, QTY_CLIENTS, client_firstLoad);
					newspaper_getReportMenu(arrayClients, QTY_CLIENTS, client_firstLoad, arrayPublications, QTY_PUBLICATIONS, publication_firstLoad);
					break;
			}
		}while(choosenOption!=9);
		printf("PROGRAMA TERMINADO");
		return EXIT_SUCCESS;
}
