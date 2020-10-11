/*
 ============================================================================
 Name        : publication.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Library publication.c
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "publication.h"

static int publication_generateNewId(void);
static int publication_checkFirstEmptyIndex(Publication* publication_list, int publication_len, int *emptyIndex);
static int publication_getForm(int *publication_category, char *publication_description);
static int publication_addData(Publication* publication_list,int publication_len,int publication_id,int publication_category, char publication_description[], int publication_idCliente);
static int publication_findById(Publication* publication_list, int publication_len,int id);
static int publication_findIndexById(Publication* publication_list, int publication_len,int id);
static int publication_modify(Publication* publication_list, int publication_len,int id);
static int publication_remove(Publication* publication_list, int publication_len,int id);



int publication_addHardcode(Publication* publication_list, int publication_len, int *publication_firstLoad)
{
	int retorno = -1;
	if(publication_list != NULL && publication_len >0)
	{
		int publication_id[]={50,60,70,80,1000};
		int publication_category[]={3,2,2,1,4};
		char publication_description[][LEN_DESCRIPTION]={"Se vende casa en la costa,excelente ubicacion. Llamar a 3256890",
									 	 				  "Venta Ford Ka. 30.000 KM. Tel: 3245546",
														  "Compro auto para Taxi. Interesados comunicarse al 467654.",
														  "Se busca bachero para turno noche. Tel: 423396.",
														  "Vendo Mesa de pool. Poco uso. Msj a pool@gmail.com."};
		int publication_idCliente[]={100, 60, 60, 50, 70};
		for(int i = 0; i < 5; i++)
		{
			publication_addData(publication_list, publication_len, publication_id[i], publication_category[i], publication_description[i], publication_idCliente[i]);
		}
		*publication_firstLoad = TRUE;
	}
	return retorno;
}

/**
 * \brief publication_initArray: To indicate that all positions in the array are empty,
 * \this function put the flag (publication_isEmpty) in TRUE in all position of the array
 * \param sEmployee* publication_list: Pointer to array of employees
 * \param int publication_len: Array length
 * \return (-1) Error / (0) Ok
 */

int publication_initArray(Publication* publication_list, int publication_len)
{
	int retorno = -1;
	if(publication_list != NULL && publication_len > 0)
	{
		for(int i=0;i<publication_len;i++)
		{
			publication_list[i].publication_isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief publication_add: Asks the user for the student data
 * \param Publication* publication_list: Pointer to array of clients
 * \param int publication_len: Array length
 * \param int publication_firstLoad: Pointer to space in memory where is the
 * \variable to indicate if an entry is loaded
 * \return (-1) Error / (0) Ok
 */

int publication_add(Publication* publication_list,int publication_len, int *publication_firstLoad, int clientId)
{
	int retorno = -1;
	int publication_id;
	int publication_category;
	char publication_description[LEN_DESCRIPTION];
	int publication_idCliente;
	int index;

	publication_idCliente = clientId;

	if(publication_list != NULL && publication_len > 0 && publication_firstLoad >0 && publication_checkFirstEmptyIndex(publication_list, publication_len, &index)==0)
	{
		if(publication_getForm(&publication_category, publication_description)== 0)
		{
			publication_id=publication_generateNewId();
			if(publication_addData(publication_list, publication_len, publication_id, publication_category, publication_description, publication_idCliente)==0)
			{
				printf("\nEl ID para: %s es: %d\n",
						publication_description,
						publication_id);
				*publication_firstLoad = TRUE;
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
 * \brief publication_checkFirstEmptyIndex: Checks first empty index in the array
 * \this function search the array for the first index with the value TRUE in the publication_isEmpty item
 * \param sEmployee* publication_list: Pointer to array of clients
 * \param int publication_len: Array length
 * \param int *EmptyIndex: Pointer to position of first empty index.
 * \return (-1) Error / (0) Ok
 */

static int publication_checkFirstEmptyIndex(Publication* publication_list, int publication_len, int *emptyIndex)
{
	int retorno = -1;
	if(publication_list != NULL && publication_len >0 && emptyIndex != NULL)
	{
		for(int i = 0; i < publication_len; i++)
		{
			if(publication_list[i].publication_isEmpty == TRUE)
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
 * \brief publication_getForm: Brings up a menu for the user to complete with info
 * \param char *publication_name: Pointer to place to store publication_name
 * \param char *lastName: Pointer to place to store last publication_name
 * \param float *salary: Pointer to place to store salary
 * \param int *sector: Pointer to place to store sector
 * \return (-1) Error / (0) Ok
 */

static int publication_getForm(int *publication_category, char *publication_description)
{
	int retorno = -1;

	if(publication_category != NULL && publication_description != NULL)
	{
		if((utn_getIntNumber("Ingrese rubro:"
							 "\n 1-EMPLEOS"
							 "\n 2-AUTOMOTOR"
							 "\n 3-INMOBILIARIOS"
							 "\n 4-COMPRA/VENTA"
							 "\nOpcion: ",
							 "Error, ", publication_category, 3, 4, 1)==0) &&
		   (utn_getAlphaNum("Ingrese Descripción:", "Error. ", publication_description, 3, LEN_DESCRIPTION)==0))
		{
			retorno = 0;
		}
	}
	return retorno;
}

/**
 *  \brief generateNewId: Generates a new ID that's +1 from previous loaded employee ID.
 */

static int publication_generateNewId(void)
{
	static int id;

	id = id+1;
	return id;
}

/**
 *  \brief publication_addData: add in a existing publication_list of clients the values received
 *  as parameters in the first empty position.
 * \param Employee* publication_list: Pointer to array of clients
 * \param int publication_len: Array length
 * \param int id: id generated by generateNewId() function
 * \param char publication_name[]: Input by user from getEmployeeForm
 * \param char lastName[]: Input by user from getEmployeeForm
 * \param float salary: Input by user from getEmployeeForm
 * \param int sector: Input by user from getEmployeeForm
 * \return (-1) Error / (0) Ok
 */

static int publication_addData(Publication* publication_list,int publication_len,int publication_id,int publication_category, char publication_description[], int publication_idCliente)
{
	int retorno = -1;
	int emptyIndex;

	if(publication_checkFirstEmptyIndex(publication_list, publication_len, &emptyIndex)==0)
	{
		publication_list[emptyIndex].publication_id=publication_id;
		publication_list[emptyIndex].publication_isEmpty=FALSE;
		publication_list[emptyIndex].publication_category=publication_category;
		strcpy(publication_list[emptyIndex].publication_description,publication_description);
		publication_list[emptyIndex].publication_idCliente=publication_idCliente;
		publication_list[emptyIndex].publication_status=ACTIVE;
		retorno=0;
	}
    return retorno;
}

/**
 *  \brief publication_findIndexById: find an Employee by Id then returns the index position in array.
 * \param Employee* publication_list: Pointer to array of clients
 * \param int publication_len: Array length
 * \param int id: id to search
 * \return Return employee index position or (-1) if ERROR
 */

static int publication_findIndexById(Publication* publication_list, int publication_len,int id)
{
	int retorno;

	if (publication_list != NULL && publication_len > 0 && id > 0)
	{
		for (int i = 0; i < publication_len; i++)
		{
			if(publication_list[i].publication_isEmpty == FALSE && publication_list[i].publication_id == id )
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;;
}


/**
 *  \brief publication_findById: find a publication by Id and returns 0 if ID is found
 * \param Publication* publication_list: Pointer to array of publications
 * \param int publication_len: Array length
 * \param int id: id to search
 * \return Return 0 if ID exists or (-1) if ERROR
 */

static int publication_findById(Publication* publication_list, int publication_len,int id)
{
	int retorno = -1;

	if (publication_list != NULL && publication_len > 0 && id > 0)
	{
		for (int i = 0; i < publication_len; i++)
		{
			if(publication_list[i].publication_isEmpty == FALSE && publication_list[i].publication_id == id )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;;
}

/**
 *  \brief publication_findByClienteId: find a publication by Cliente Id and returns 0 if ID is found
 * \param Publication* publication_list: Pointer to array of publications
 * \param int publication_len: Array length
 * \param int id: id to search
 * \return Return 0 if ID exists or (-1) if ERROR
 */

static int publication_findByClienteId(Publication* publication_list, int publication_len,int id)
{
	int retorno = -1;

	if (publication_list != NULL && publication_len > 0 && id > 0)
	{
		for (int i = 0; i < publication_len; i++)
		{
			if(publication_list[i].publication_isEmpty == FALSE && publication_list[i].publication_idCliente == id )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;;
}

/**
 * \brief publication_modifyMenu: Modifies the data of an Employee by given Id.
 * Allows to modify individual fields of the employee by a switch
 * \param Employee* publication_list: Pointer to array of clients
 * \param int publication_len: Array length
 * \param int publication_firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

int publication_modifyMenu(Publication* publication_list, int publication_len, int publication_firstLoad)
{
	int retorno = -1;
	int idToSearch;

	if(publication_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(utn_getIntNumber("Ingrese el ID a modificar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   publication_findById(publication_list, publication_len, idToSearch)== 0)
		{
			if(publication_modify(publication_list,publication_len,idToSearch)==0)
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
 * \brief publication_modify: Modifies the data of an Employee by given Id.
 * Allows to modify individual fields of the employee by a switch
 * \param Employee* publication_list: Pointer to array of clients
 * \param int publication_len: Array length
 * \param int publication_firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

static int publication_modify(Publication* publication_list, int publication_len,int id)
{
	int retorno = -1;
	int choosenOption;
	char answer;
	int indexToModify;

	Publication bufferPublication;

	indexToModify = publication_findIndexById(publication_list, publication_len, id);

	if(publication_list != NULL && publication_len>0 && id > 0 && indexToModify > -1)
	{
		do
		{
			printf("Publication a modificar\n");
			printf("Rubro: %d Descripción: %s ID Cliente: %d.\n",
					publication_list[indexToModify].publication_category,
					publication_list[indexToModify].publication_description,
					publication_list[indexToModify].publication_idCliente);
			if(utn_getIntNumber("\nQue campo desea modificar:"
								"\n 1-RUBRO."
								"\n 2-DESCRIPCION."
								"\n 3-ID CLIENTE:"
								"\n 4-Salir"
								"\nOpcion:", "\nError.", &choosenOption, 3, 4, 1)==0)
			{
				switch(choosenOption)
				{
					case 1:
						if(utn_getIntNumber("Ingrese rubro:"
										   "\n 1-EMPLEOS"
										   "\n 2-AUTOMOTOR"
										   "\n 3-INMOBILIARIOS"
										   "\n 4-COMPRA/VENTA"
										   "\nOpcion: ",
										   "Error, ", &bufferPublication.publication_category, 3, 4, 1)==0)
						{
							publication_list[indexToModify].publication_category = bufferPublication.publication_category;
						}
						break;
					case 2:
						if(utn_getAlphaNum("Ingrese Descripción:", "Error. ", bufferPublication.publication_description, 3, LEN_DESCRIPTION)==0)
						{
							strcpy(publication_list[indexToModify].publication_description,bufferPublication.publication_description);
						}
						break;
					case 3:
						if(utn_getIntNumber("Ingrese ID del Cliente:", "Error. ", &bufferPublication.publication_idCliente, 3, INT_MAX, 1)==0)
						{
							publication_list[indexToModify].publication_idCliente = bufferPublication.publication_idCliente;
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
 * \brief publication_removeMenu: Remove a Employee by Id (put publication_isEmpty Flag in TRUE)
 * \param Employee* publication_list: Pointer to array of clients
 * \param int publication_len: Array length
 * \param int *publication_firstLoad: variable to check if there is even one entry loaded and
 *  safeguard to prevent errors if all data is erased
 * \return (-1) Error / (0) Ok
 */

int publication_removeMenu(Publication* publication_list, int publication_len,int *publication_firstLoad)
{
	int retorno = -1;
	int idToSearch;

	if(*publication_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(utn_getIntNumber("Ingrese el ID a eliminar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   publication_findById(publication_list, publication_len, idToSearch)== 0 &&
		   publication_remove(publication_list,publication_len,idToSearch)== 0)
		{
			for(int i = 0; i < publication_len; i++)
			{
				if(publication_list[i].publication_isEmpty == TRUE)
				{
					*publication_firstLoad = FALSE;
				}
				else
				{
					*publication_firstLoad = TRUE;
					break;
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief publication_remove: Remove a Employee by Id (put publication_isEmpty Flag in TRUE)
 * \param Employee* publication_list: Pointer to array of clients
 * \param int publication_len: Array length
 * \param int id: id value of entry to remove
 *  safeguard to prevent errors if all data is erased
 * \return (-1) Error / (0) Ok
 */

static int publication_remove(Publication* publication_list, int publication_len,int id)
{
	int retorno = -1;
	int indexToModify;
	char answer;

	indexToModify = publication_findIndexById(publication_list, publication_len, id);

	if(publication_list != NULL && publication_len>0 && id > 0 && indexToModify > -1)
	{
		printf("Publication a eliminar\n");
		printf("Categoria: %d Descripcion: %s ID Cliente: %d\n", publication_list[indexToModify].publication_category,publication_list[indexToModify].publication_description,publication_list[indexToModify].publication_idCliente);
		utn_getChar("¿Desea eliminar este ID?(Y/N)", "Error. ", &answer, 'Y', 'N', 3);
		switch(answer)
		{
			case 'Y':
				publication_list[indexToModify].publication_isEmpty = TRUE;
				printf("\nREGISTRO DE PUBLICIDAD BORRADO CON EXITO.\n");
				break;
			case'N':
				printf("\nREGISTRO NO BORRADO\n");
				break;
			default:
				printf("\nERROR, INGRESE 'Y' PARA BORRAR EL REGISTRO.\n");
		}
		retorno = 0;
	}
	else
	{
		printf("\nERROR, ID INEXISTENTE.\n");
	}
	return retorno;
}

/**
 * \brief publication_remove: Remove a Employee by Id (put publication_isEmpty Flag in TRUE)
 * \param Employee* publication_list: Pointer to array of clients
 * \param int publication_len: Array length
 * \param int id: id value of entry to remove
 *  safeguard to prevent errors if all data is erased
 * \return (-1) Error / (0) Ok
 */

int publication_removebyClientId(Publication* publication_list, int publication_len,int idCliente)
{
	int retorno = -1;

	for(int i=0;i< publication_len ;i++)
	{
		if(publication_list[i].publication_isEmpty == FALSE && publication_list[i].publication_idCliente == idCliente)
		{
			publication_list[i].publication_isEmpty = TRUE;
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief publication_printAll: print the content of publicationes array
 * \param Employee* publication_list: Pointer to array of clients
 * \param int publication_len: Array length
 * \param int publication_firstLoad: Pointer to space in memory where is the
 * \variable to indicate if an entry is loaded
 * \return (-1) Error / (0) Ok*
 */

int publication_printAll(Publication* publication_list, int publication_len, int publication_firstLoad)
{
	int retorno = -1;

	if(publication_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(publication_list != NULL && publication_len > 0)
		{
			printf("----------------------------------------------------------------------------------------------------\n");
			printf("| CATEGORIA | ID   | DESCRIPCION                                                      | ID CLIENTE |\n");
			printf("----------------------------------------------------------------------------------------------------\n");
			for(int i=0;i< publication_len ;i++)
			{
				if(publication_list[i].publication_isEmpty == FALSE)
				{
					printf("| %-10d| %-5d| %-65s| %-11d|\n",
							publication_list[i].publication_category,
							publication_list[i].publication_id,
							publication_list[i].publication_description,
							publication_list[i].publication_idCliente);
					printf("----------------------------------------------------------------------------------------------------\n");
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief publication_printByClienteId: print the content of a given publication by client ID
 * \param Employee* publication_list: Pointer to array of publications
 * \param int publication_len: Array length
 * \param int publication_firstLoad: Pointer to space in memory where is the variable to indicate if an entry is loaded
 * \param int idCliente: Value to search and print asociated info
 * \return (-1) Error / (0) Ok*
 */

int publication_printByClientId(Publication* publication_list, int publication_len,int idCliente)
{
	int retorno = -1;

		if(publication_findByClienteId(publication_list, publication_len, idCliente) != 0)
		{
			printf("\nNO POSEE PUBLICACIONES INGRESADAS.\n");
		}
		else
		{
			if(publication_list != NULL && publication_len > 0)
			{
				printf("------------------------------------------------------------------------------------------------------------\n");
				printf("| PUBLICACIONES DEL ID : %d                                                                                |\n",idCliente);
				printf("------------------------------------------------------------------------------------------------------------\n");
				printf("| CATEGORIA | ID   | DESCRIPCION                                                      | ESTADO PUBLICACION |\n");
				printf("------------------------------------------------------------------------------------------------------------\n");
				for(int i=0;i< publication_len ;i++)
				{
					if(publication_list[i].publication_isEmpty == FALSE && publication_list[i].publication_idCliente == idCliente)
					{
						printf("| %-10d| %-5d| %-65s| %-19d|\n",
								publication_list[i].publication_category,
								publication_list[i].publication_id,
								publication_list[i].publication_description,
								publication_list[i].publication_status);
						printf("------------------------------------------------------------------------------------------------------------\n");
						retorno = 0;
					}
				}

			}
		}
		return retorno;
}

