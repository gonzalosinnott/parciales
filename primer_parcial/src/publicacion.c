/*
 ============================================================================
 Name        : publicacion.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Library publicacion.c
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "publicacion.h"

static int publicacion_generateNewId(void);
static int publicacion_checkFirstEmptyIndex(Publicacion* publicacion_list, int publicacion_len, int *emptyIndex);
static int publicacion_getForm(int *publicacion_category, char *publicacion_description, int *publicacion_idCliente);
static int publicacion_addData(Publicacion* publicacion_list,int publicacion_len,int publicacion_id,int publicacion_category, char publicacion_description[], int publicacion_idCliente);
static int publicacion_findById(Publicacion* publicacion_list, int publicacion_len,int id);
static int publicacion_findIndexById(Publicacion* publicacion_list, int publicacion_len,int id);
static int publicacion_modify(Publicacion* publicacion_list, int publicacion_len,int id);
static int publicacion_remove(Publicacion* publicacion_list, int publicacion_len,int id);



int publicacion_addHardcode(Publicacion* publicacion_list, int publicacion_len, int *publicacion_firstLoad)
{
	int retorno = -1;
	if(publicacion_list != NULL && publicacion_len >0)
	{
		int publicacion_id[]={50,60,70,80,1000};
		int publicacion_category[]={3,2,2,1,4};
		char publicacion_description[][LONG_DESCRIPTION]={"Se vende casa en la costa,excelente ubicacion. Llamar a 3256890",
									 	 				  "Venta Ford Ka. 30.000 KM. Tel: 3245546",
														  "Compro auto para Taxi. Interesados comunicarse al 467654.",
														  "Se busca bachero para turno noche. Tel: 423396.",
														  "Vendo Mesa de pool. Poco uso. Msj a pool@gmail.com."};
		int publicacion_idCliente[]={100, 60, 60, 50, 70};
		for(int i = 0; i < 5; i++)
		{
			publicacion_addData(publicacion_list, publicacion_len, publicacion_id[i], publicacion_category[i], publicacion_description[i], publicacion_idCliente[i]);
		}
		*publicacion_firstLoad = TRUE;
	}
	return retorno;
}

/**
 * \brief publicacion_initArray: To indicate that all positions in the array are empty,
 * \this function put the flag (publicacion_isEmpty) in TRUE in all position of the array
 * \param sEmployee* publicacion_list: Pointer to array of employees
 * \param int publicacion_len: Array length
 * \return (-1) Error / (0) Ok
 */

int publicacion_initArray(Publicacion* publicacion_list, int publicacion_len)
{
	int retorno = -1;
	if(publicacion_list != NULL && publicacion_len > 0)
	{
		for(int i=0;i<publicacion_len;i++)
		{
			publicacion_list[i].publicacion_isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief publicacion_alta: Asks the user for the student data
 * \param Publicacion* publicacion_list: Pointer to array of clients
 * \param int publicacion_len: Array length
 * \param int publicacion_firstLoad: Pointer to space in memory where is the
 * \variable to indicate if an entry is loaded
 * \return (-1) Error / (0) Ok
 */

int publicacion_alta(Publicacion* publicacion_list,int publicacion_len, int *publicacion_firstLoad)
{
	int retorno = -1;
	int publicacion_id;
	int publicacion_category;
	char publicacion_description[LONG_DESCRIPTION];
	int publicacion_idCliente;
	int index;

	if(publicacion_list != NULL && publicacion_len > 0 && publicacion_firstLoad >0 && publicacion_checkFirstEmptyIndex(publicacion_list, publicacion_len, &index)==0)
	{
		if(publicacion_getForm(&publicacion_category, publicacion_description, &publicacion_idCliente)== 0)
		{
			publicacion_id=publicacion_generateNewId();
			if(publicacion_addData(publicacion_list, publicacion_len, publicacion_id, publicacion_category, publicacion_description, publicacion_idCliente)==0)
			{
				printf("\nEl ID para: %s es: %d\n",
						publicacion_description,
						publicacion_id);
				*publicacion_firstLoad = TRUE;
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
 * \brief publicacion_checkFirstEmptyIndex: Checks first empty index in the array
 * \this function search the array for the first index with the value TRUE in the publicacion_isEmpty item
 * \param sEmployee* publicacion_list: Pointer to array of clients
 * \param int publicacion_len: Array length
 * \param int *EmptyIndex: Pointer to position of first empty index.
 * \return (-1) Error / (0) Ok
 */

static int publicacion_checkFirstEmptyIndex(Publicacion* publicacion_list, int publicacion_len, int *emptyIndex)
{
	int retorno = -1;
	if(publicacion_list != NULL && publicacion_len >0 && emptyIndex != NULL)
	{
		for(int i = 0; i < publicacion_len; i++)
		{
			if(publicacion_list[i].publicacion_isEmpty == TRUE)
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
 * \brief publicacion_getForm: Brings up a menu for the user to complete with info
 * \param char *publicacion_name: Pointer to place to store publicacion_name
 * \param char *lastName: Pointer to place to store last publicacion_name
 * \param float *salary: Pointer to place to store salary
 * \param int *sector: Pointer to place to store sector
 * \return (-1) Error / (0) Ok
 */

static int publicacion_getForm(int *publicacion_category, char *publicacion_description, int *publicacion_idCliente)
{
	int retorno = -1;

	if(publicacion_category != NULL && publicacion_description != NULL && publicacion_idCliente != NULL )
	{
		if((utn_getIntNumber("Ingrese rubro:"
							 "\n 1-EMPLEOS"
							 "\n 2-AUTOMOTOR"
							 "\n 3-INMOBILIARIOS"
							 "\n 4-COMPRA/VENTA"
							 "\nOpcion: ",
							 "Error, ", publicacion_category, 3, 4, 1)==0) &&
		   (utn_getAlphaNum("Ingrese Descripción:", "Error. ", publicacion_description, 3, LONG_DESCRIPTION)==0) &&
		   (utn_getIntNumber("Ingrese ID del Cliente:", "Error. ", publicacion_idCliente, 3, INT_MAX, 1)==0))
		{
			retorno = 0;
		}
	}
	return retorno;
}

/**
 *  \brief generateNewId: Generates a new ID that's +1 from previous loaded employee ID.
 */

static int publicacion_generateNewId(void)
{
	static int id;

	id = id+1;
	return id;
}

/**
 *  \brief publicacion_addData: add in a existing publicacion_list of clients the values received
 *  as parameters in the first empty position.
 * \param Employee* publicacion_list: Pointer to array of clients
 * \param int publicacion_len: Array length
 * \param int id: id generated by generateNewId() function
 * \param char publicacion_name[]: Input by user from getEmployeeForm
 * \param char lastName[]: Input by user from getEmployeeForm
 * \param float salary: Input by user from getEmployeeForm
 * \param int sector: Input by user from getEmployeeForm
 * \return (-1) Error / (0) Ok
 */

static int publicacion_addData(Publicacion* publicacion_list,int publicacion_len,int publicacion_id,int publicacion_category, char publicacion_description[], int publicacion_idCliente)
{
	int retorno = -1;
	int emptyIndex;

	if(publicacion_checkFirstEmptyIndex(publicacion_list, publicacion_len, &emptyIndex)==0)
	{
		publicacion_list[emptyIndex].publicacion_id=publicacion_id;
		publicacion_list[emptyIndex].publicacion_isEmpty=FALSE;
		publicacion_list[emptyIndex].publicacion_category=publicacion_category;
		strcpy(publicacion_list[emptyIndex].publicacion_description,publicacion_description);
		publicacion_list[emptyIndex].publicacion_idCliente=publicacion_idCliente;
		publicacion_list[emptyIndex].publicacion_status=ACTIVE;
		retorno=0;
	}
    return retorno;
}

/**
 *  \brief publicacion_findIndexById: find an Employee by Id then returns the index position in array.
 * \param Employee* publicacion_list: Pointer to array of clients
 * \param int publicacion_len: Array length
 * \param int id: id to search
 * \return Return employee index position or (-1) if ERROR
 */

static int publicacion_findIndexById(Publicacion* publicacion_list, int publicacion_len,int id)
{
	int retorno;

	if (publicacion_list != NULL && publicacion_len > 0 && id > 0)
	{
		for (int i = 0; i < publicacion_len; i++)
		{
			if(publicacion_list[i].publicacion_isEmpty == FALSE && publicacion_list[i].publicacion_id == id )
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;;
}


/**
 *  \brief publicacion_findById: find a publicacion by Id and returns 0 if ID is found
 * \param Publicacion* publicacion_list: Pointer to array of publicacions
 * \param int publicacion_len: Array length
 * \param int id: id to search
 * \return Return 0 if ID exists or (-1) if ERROR
 */

static int publicacion_findById(Publicacion* publicacion_list, int publicacion_len,int id)
{
	int retorno = -1;

	if (publicacion_list != NULL && publicacion_len > 0 && id > 0)
	{
		for (int i = 0; i < publicacion_len; i++)
		{
			if(publicacion_list[i].publicacion_isEmpty == FALSE && publicacion_list[i].publicacion_id == id )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;;
}

/**
 * \brief publicacion_modifyMenu: Modifies the data of an Employee by given Id.
 * Allows to modify individual fields of the employee by a switch
 * \param Employee* publicacion_list: Pointer to array of clients
 * \param int publicacion_len: Array length
 * \param int publicacion_firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

int publicacion_modifyMenu(Publicacion* publicacion_list, int publicacion_len, int publicacion_firstLoad)
{
	int retorno = -1;
	int idToSearch;

	if(publicacion_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(utn_getIntNumber("Ingrese el ID a modificar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   publicacion_findById(publicacion_list, publicacion_len, idToSearch)== 0)
		{
			if(publicacion_modify(publicacion_list,publicacion_len,idToSearch)==0)
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
 * \brief publicacion_modify: Modifies the data of an Employee by given Id.
 * Allows to modify individual fields of the employee by a switch
 * \param Employee* publicacion_list: Pointer to array of clients
 * \param int publicacion_len: Array length
 * \param int publicacion_firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

static int publicacion_modify(Publicacion* publicacion_list, int publicacion_len,int id)
{
	int retorno = -1;
	int choosenOption;
	char answer;
	int indexToModify;

	Publicacion bufferPublicacion;

	indexToModify = publicacion_findIndexById(publicacion_list, publicacion_len, id);

	if(publicacion_list != NULL && publicacion_len>0 && id > 0 && indexToModify > -1)
	{
		do
		{
			printf("Publicacion a modificar\n");
			printf("Rubro: %d Descripción: %s ID Cliente: %d.\n",
					publicacion_list[indexToModify].publicacion_category,
					publicacion_list[indexToModify].publicacion_description,
					publicacion_list[indexToModify].publicacion_idCliente);
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
										   "Error, ", &bufferPublicacion.publicacion_category, 3, 4, 1)==0)
						{
							publicacion_list[indexToModify].publicacion_category = bufferPublicacion.publicacion_category;
						}
						break;
					case 2:
						if(utn_getAlphaNum("Ingrese Descripción:", "Error. ", bufferPublicacion.publicacion_description, 3, LONG_DESCRIPTION)==0)
						{
							strcpy(publicacion_list[indexToModify].publicacion_description,bufferPublicacion.publicacion_description);
						}
						break;
					case 3:
						if(utn_getIntNumber("Ingrese ID del Cliente:", "Error. ", &bufferPublicacion.publicacion_idCliente, 3, INT_MAX, 1)==0)
						{
							publicacion_list[indexToModify].publicacion_idCliente = bufferPublicacion.publicacion_idCliente;
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
 * \brief publicacion_removeMenu: Remove a Employee by Id (put publicacion_isEmpty Flag in TRUE)
 * \param Employee* publicacion_list: Pointer to array of clients
 * \param int publicacion_len: Array length
 * \param int *publicacion_firstLoad: variable to check if there is even one entry loaded and
 *  safeguard to prevent errors if all data is erased
 * \return (-1) Error / (0) Ok
 */

int publicacion_removeMenu(Publicacion* publicacion_list, int publicacion_len,int *publicacion_firstLoad)
{
	int retorno = -1;
	int idToSearch;

	if(*publicacion_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(utn_getIntNumber("Ingrese el ID a eliminar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   publicacion_findById(publicacion_list, publicacion_len, idToSearch)== 0 &&
		   publicacion_remove(publicacion_list,publicacion_len,idToSearch)== 0)
		{
			for(int i = 0; i < publicacion_len; i++)
			{
				if(publicacion_list[i].publicacion_isEmpty == TRUE)
				{
					*publicacion_firstLoad = FALSE;
				}
				else
				{
					*publicacion_firstLoad = TRUE;
					break;
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief publicacion_remove: Remove a Employee by Id (put publicacion_isEmpty Flag in TRUE)
 * \param Employee* publicacion_list: Pointer to array of clients
 * \param int publicacion_len: Array length
 * \param int id: id value of entry to remove
 *  safeguard to prevent errors if all data is erased
 * \return (-1) Error / (0) Ok
 */

static int publicacion_remove(Publicacion* publicacion_list, int publicacion_len,int id)
{
	int retorno = -1;
	int indexToModify;
	char answer;

	indexToModify = publicacion_findIndexById(publicacion_list, publicacion_len, id);

	if(publicacion_list != NULL && publicacion_len>0 && id > 0 && indexToModify > -1)
	{
		printf("Publicacion a eliminar\n");
		printf("Categoria: %d Descripcion: %s ID Cliente: %d\n", publicacion_list[indexToModify].publicacion_category,publicacion_list[indexToModify].publicacion_description,publicacion_list[indexToModify].publicacion_idCliente);
		utn_getChar("¿Desea eliminar este ID?(Y/N)", "Error. ", &answer, 'Y', 'N', 3);
		switch(answer)
		{
			case 'Y':
				publicacion_list[indexToModify].publicacion_isEmpty = TRUE;
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
 * \brief publicacion_print: print the content of clients array
 * \param Employee* publicacion_list: Pointer to array of clients
 * \param int publicacion_len: Array length
 * \param int publicacion_firstLoad: Pointer to space in memory where is the
 * \variable to indicate if an entry is loaded
 * \return (-1) Error / (0) Ok*
 */

int publicacion_print(Publicacion* publicacion_list, int publicacion_len, int publicacion_firstLoad)
{
	int retorno = -1;

	if(publicacion_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(publicacion_list != NULL && publicacion_len > 0)
		{
			printf("----------------------------------------------------------------------------------------------------\n");
			printf("| CATEGORIA | ID   | DESCRIPCION                                                      | ID CLIENTE |\n");
			printf("----------------------------------------------------------------------------------------------------\n");
			for(int i=0;i< publicacion_len ;i++)
			{
				if(publicacion_list[i].publicacion_isEmpty == FALSE)
				{
					printf("| %-10d| %-5d| %-65s| %-11d|\n",
							publicacion_list[i].publicacion_category,
							publicacion_list[i].publicacion_id,
							publicacion_list[i].publicacion_description,
							publicacion_list[i].publicacion_idCliente);
					printf("----------------------------------------------------------------------------------------------------\n");
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}
