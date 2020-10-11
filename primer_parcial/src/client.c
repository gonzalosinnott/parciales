/*
 ============================================================================
 Name        : client.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Library client.c
 ============================================================================
 */

#include "client.h"

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "client.h"
#include "utn.h"

static int client_generateNewId(void);
static int client_checkFirstEmptyIndex(Client* client_list, int client_len, int *emptyIndex);
static int client_getForm(char *client_name, char *client_lastName, char *client_cuit);
static int client_addData(Client* client_list,int client_len,int client_id,char client_name[], char client_lastName[], char client_cuit[]);
static int client_findIndexById(Client* client_list, int client_len,int id);
static int client_modify(Client* client_list, int client_len,int id);


/**
 * \brief client_addHardcode: Adds Hardcoded data for testing purposes
 * \param Client* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \param int client_firstLoad: Pointer to space in memory where is the
 * \variable to indicate if an entry is loaded
 * \return (-1) Error / (0) Ok
 */

int client_addHardcode(Client* client_list, int client_len, int *client_firstLoad)
{
	int retorno = -1;
	if(client_list != NULL && client_len >0)
	{
		int client_id[]={50,60,70,80,100};
		char client_name[][LEN_NAME]={"Juan Carlos",
										"Marcos",
										"Anabel",
										"Ricardo",
										"Florencia"};
		char client_lastName[][LEN_NAME]={"Gomez",
									 	 	"Sanchez",
											"Pereira Iraola",
											"Guzman",
											"Bianchi"};
		char client_cuit[][LEN_CUIT]={"23304560989",
										"26249359947",
										"21450453475",
										"27103649264",
										"21369834576"};
		for(int i = 0; i < 5; i++)
		{
			client_addData(client_list, client_len, client_id[i], client_name[i], client_lastName[i], client_cuit[i]);
		}
		*client_firstLoad = TRUE;
	}
	return retorno;
}

/**
 * \brief client_initArray: To indicate that all positions in the array are empty,
 * \this function put the flag (client_isEmpty) in TRUE in all position of the array
 * \param sEmployee* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \return (-1) Error / (0) Ok
 */

int client_initArray(Client* client_list, int client_len)
{
	int retorno = -1;
	if(client_list != NULL && client_len > 0)
	{
		for(int i=0;i<client_len;i++)
		{
			client_list[i].client_isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief client_add: Asks the user for the student data
 * \param Client* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \param int client_firstLoad: Pointer to space in memory where is the
 * \variable to indicate if an entry is loaded
 * \return (-1) Error / (0) Ok
 */

int client_add(Client* client_list,int client_len, int *client_firstLoad)
{
	int retorno = -1;
	int client_id;
	char client_name[LEN_NAME];
	char client_lastName[LEN_NAME];
	char client_cuit[LEN_CUIT];
	int index;

	if(client_list != NULL && client_len > 0 && client_firstLoad >0 && client_checkFirstEmptyIndex(client_list, client_len, &index)==0)
	{
		if(client_getForm(client_name, client_lastName, client_cuit)== 0)
		{
			client_id=client_generateNewId();
			if(client_addData(client_list, client_len, client_id, client_name, client_lastName, client_cuit)==0)
			{
				printf("\nEl ID para %s %s es: %d\n",
						client_lastName,
						client_name,
						client_id);
				*client_firstLoad = TRUE;
				retorno=0;
			}
		}
		else
		{
			printf("\nERROR EN LA CARGA DEL EMPLEADO.\n");
		}
	}
	else
	{
		printf("\nNO SE PUEDEN CARGAR MAS REGISTROS.\n");
	}
	return retorno;
}

/**
 * \brief client_checkFirstEmptyIndex: Checks first empty index in the array
 * \this function search the array for the first index with the value TRUE in the client_isEmpty item
 * \param sEmployee* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \param int *EmptyIndex: Pointer to position of first empty index.
 * \return (-1) Error / (0) Ok
 */

static int client_checkFirstEmptyIndex(Client* client_list, int client_len, int *emptyIndex)
{
	int retorno = -1;
	if(client_list != NULL && client_len >0 && emptyIndex != NULL)
	{
		for(int i = 0; i < client_len; i++)
		{
			if(client_list[i].client_isEmpty == TRUE)
			{
				*emptyIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief client_getForm: Brings up a menu for the user to complete with info
 * \param char *client_name: Pointer to place to store client_name
 * \param char *lastName: Pointer to place to store last client_name
 * \param float *salary: Pointer to place to store salary
 * \param int *sector: Pointer to place to store sector
 * \return (-1) Error / (0) Ok
 */

static int client_getForm(char *client_name, char *client_lastName, char *client_cuit)
{
	int retorno = -1;

	if(client_name != NULL && client_lastName != NULL && client_cuit != NULL )
	{
		if((utn_getString("Ingrese Apellido:", "Error. ", client_lastName, 3, LEN_NAME)==0) &&
		   (utn_getString("Ingrese Nombre:", "Error. ", client_name, 3, LEN_NAME)==0) &&
		   (utn_getAlphaNum("Ingrese CUIT(SIN GUIONES):", "Error. ", client_cuit, 3, LEN_CUIT)==0))
		{
			retorno = 0;
		}
	}
	return retorno;
}

/**
 *  \brief generateNewId: Generates a new ID that's +1 from previous loaded employee ID.
 */

static int client_generateNewId(void)
{
	static int id;

	id = id+1;
	return id;
}

/**
 *  \brief client_addData: add in a existing client_list of clients the values received
 *  as parameters in the first empty position.
 * \param Employee* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \param int id: id generated by generateNewId() function
 * \param char client_name[]: Input by user from getEmployeeForm
 * \param char lastName[]: Input by user from getEmployeeForm
 * \param float salary: Input by user from getEmployeeForm
 * \param int sector: Input by user from getEmployeeForm
 * \return (-1) Error / (0) Ok
 */

static int client_addData(Client* client_list,int client_len,int client_id,char client_name[], char client_lastName[], char client_cuit[])
{
	int retorno = -1;
	int emptyIndex;

	if(client_checkFirstEmptyIndex(client_list, client_len, &emptyIndex)==0)
	{
		client_list[emptyIndex].client_id=client_id;
		client_list[emptyIndex].client_isEmpty=FALSE;
		strcpy(client_list[emptyIndex].client_name,client_name);
		strcpy(client_list[emptyIndex].client_lastName,client_lastName);
		strcpy(client_list[emptyIndex].client_cuit,client_cuit);
		retorno=0;
	}
    return retorno;
}

/**
 *  \brief client_findIndexById: find an Employee by Id then returns the index position in array.
 * \param Employee* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \param int id: id to search
 * \return Return employee index position or (-1) if ERROR
 */

static int client_findIndexById(Client* client_list, int client_len,int id)
{
	int retorno;

	if (client_list != NULL && client_len > 0 && id > 0)
	{
		for (int i = 0; i < client_len; i++)
		{
			if(client_list[i].client_isEmpty == FALSE && client_list[i].client_id == id )
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;;
}


/**
 *  \brief client_findById: find a client by Id and returns 0 if ID is found
 * \param Client* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \param int id: id to search
 * \return Return 0 if ID exists or (-1) if ERROR
 */

int client_findById(Client* client_list, int client_len,int id)
{
	int retorno = -1;

	if (client_list != NULL && client_len > 0 && id > 0)
	{
		for (int i = 0; i < client_len; i++)
		{
			if(client_list[i].client_isEmpty == FALSE && client_list[i].client_id == id )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;;
}

/**
 * \brief client_modifyMenu: Modifies the data of an Employee by given Id.
 * Allows to modify individual fields of the employee by a switch
 * \param Employee* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \param int client_firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

int client_modifyMenu(Client* client_list, int client_len, int client_firstLoad)
{
	int retorno = -1;
	int idToSearch;

	if(client_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(utn_getIntNumber("Ingrese el ID a modificar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   client_findById(client_list, client_len, idToSearch)== 0)
		{
			if(client_modify(client_list,client_len,idToSearch)==0)
			{
				printf("\nREGISTRO DE CLIENTE MODIFICADO CON EXITO.\n");
				retorno = 0;
			}

		}
		else
		{
			printf("\nERROR, ID INEXISTENTE.\n");
		}
	}
	return retorno;
}

/**
 * \brief client_modify: Modifies the data of an Employee by given Id.
 * Allows to modify individual fields of the employee by a switch
 * \param Employee* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \param int client_firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

static int client_modify(Client* client_list, int client_len,int id)
{
	int retorno = -1;
	int choosenOption;
	char answer;
	int indexToModify;

	Client bufferClient;

	indexToModify = client_findIndexById(client_list, client_len, id);

	if(client_list != NULL && client_len>0 && id > 0 && indexToModify > -1)
	{
		do
		{
			printf("Client a modificar\n");
			printf("Apellido y Nombre: %s %s CUIT: %s.\n",
					client_list[indexToModify].client_lastName,
					client_list[indexToModify].client_name,
					client_list[indexToModify].client_cuit);
			if(utn_getIntNumber("\nQue campo desea modificar:"
								"\n 1-Apellido."
								"\n 2-Nombre."
								"\n 3-CUIT(SIN GUIONES):"
								"\n 4-Salir"
								"\nOpcion:", "\nError.", &choosenOption, 3, 4, 1)==0)
			{
				switch(choosenOption)
				{
					case 1:
						if(utn_getString("\nApellido:","\nError. ",bufferClient.client_lastName,2,LEN_NAME)==0)
						{
							strcpy(client_list[indexToModify].client_lastName,bufferClient.client_lastName);
						}
						break;
					case 2:
						if(utn_getString("\nNombre:","\nError. ",bufferClient.client_name,2,LEN_NAME)==0)
						{
							strcpy(client_list[indexToModify].client_name,bufferClient.client_name);
						}
						break;
					case 3:
						if(utn_getAlphaNum("\nCUIT (SIN GUIONES):","\nError. ",bufferClient.client_cuit,2,LEN_CUIT)==0)
						{
							strcpy(client_list[indexToModify].client_cuit,bufferClient.client_cuit);
						}
						break;
					case 4:
						answer = 'N';
						break;
				}
			}
			if(choosenOption!=4)
			{
				utn_getChar("¿Desea seguir modificando este ID?(Y/N)", "Error. ", &answer, 'Y', 'N', 3);
			}
		}while(answer!='N');
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief client_removeMenu: Remove a Employee by Id (put client_isEmpty Flag in TRUE)
 * \param Employee* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \param int *client_firstLoad: variable to check if there is even one entry loaded and
 *  safeguard to prevent errors if all data is erased
 * \return (-1) Error / (0) Ok
 */

int client_removeMenu(Client* client_list, int client_len,int *client_firstLoad)
{
	int retorno = -1;
	int idToSearch;

	if(*client_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(utn_getIntNumber("Ingrese el ID a eliminar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   client_findById(client_list, client_len, idToSearch)== 0 &&
		   client_remove(client_list,client_len,idToSearch)== 0)
		{
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
	}
	return retorno;
}

/**
 * \brief client_remove: Remove a Employee by Id (put client_isEmpty Flag in TRUE)
 * \param Employee* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \param int id: id value of entry to remove
 *  safeguard to prevent errors if all data is erased
 * \return (-1) Error / (0) Ok
 */

int client_remove(Client* client_list, int client_len,int id)
{
	int retorno = -1;
	int indexToModify;
	char answer;

	indexToModify = client_findIndexById(client_list, client_len, id);

	if(client_list != NULL && client_len>0 && id > 0 && indexToModify > -1)
	{
		utn_getChar("\n¿Desea eliminar este ID y sus publicaciones asociadas?(Y/N):", "Error. ", &answer, 'Y', 'N', 3);
		switch(answer)
		{
			case 'Y':
				client_list[indexToModify].client_isEmpty = TRUE;
				printf("\nREGISTRO DE CLIENTE BORRADO CON EXITO.\n");
				retorno = 0;
				break;
			case'N':
				printf("\nREGISTRO NO BORRADO\n");
				break;
			default:
				printf("\nERROR, INGRESE 'Y' PARA BORRAR EL REGISTRO.\n");
		}
	}
	return retorno;
}

/**
 * \brief client_print: print the content of clients array
 * \param Employee* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \param int client_firstLoad: Pointer to space in memory where is the
 * \variable to indicate if an entry is loaded
 * \return (-1) Error / (0) Ok*
 */

int client_printAll(Client* client_list, int client_len, int client_firstLoad)
{
	int retorno = -1;

	if(client_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(client_list != NULL && client_len > 0)
		{
			printf("-------------------------------------------------------------\n");
			printf("|                    LISTADO DE CLIENTES                    |\n");
			printf("-------------------------------------------------------------\n");
			printf("| APELLIDO        | NOMBRE          | CUIT            | ID  |\n");
			printf("-------------------------------------------------------------\n");
			for(int i=0;i< client_len ;i++)
			{
				if(client_list[i].client_isEmpty == FALSE)
				{
					printf("| %-16s| %-16s| %-16s| %-3d |\n",
							client_list[i].client_lastName,
							client_list[i].client_name,
							client_list[i].client_cuit,
							client_list[i].client_id);
					printf("-------------------------------------------------------------\n");
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief client_print: print the client associated to the id given
 * \param Employee* client_list: Pointer to array of clients
 * \param int client_len: Array length
 * \param int client_firstLoad: Pointer to space in memory where is the variable to indicate if an entry is loaded
 * \param int int client_id): Value to search and print associated info
 * \return (-1) Error / (0) Ok*
 */

int client_printById(Client* client_list, int client_len, int idClient)
{
	int retorno = -1;

	if(client_list != NULL && client_len > 0)
	{
		for(int i=0;i< client_len ;i++)
		{
			if(client_list[i].client_isEmpty == FALSE && client_list[i].client_id == idClient)
			{
				printf("-------------------------------------------------------\n");
				printf("| DATOS DEL CLIENTE ID: %d                            |\n",idClient);
				printf("-------------------------------------------------------\n");
				printf("| APELLIDO        | NOMBRE          | CUIT            |\n");
				printf("-------------------------------------------------------\n");
				printf("| %-16s| %-16s| %-16s|\n",
						client_list[i].client_lastName,
						client_list[i].client_name,
						client_list[i].client_cuit);
				printf("-------------------------------------------------------\n");
				retorno = 0;
			}
		}
	}
	return retorno;
}