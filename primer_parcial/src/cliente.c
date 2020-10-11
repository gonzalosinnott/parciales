/*
 ============================================================================
 Name        : cliente.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Library cliente.c
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "cliente.h"

static int cliente_generateNewId(void);
static int cliente_checkFirstEmptyIndex(Cliente* cliente_list, int cliente_len, int *emptyIndex);
static int cliente_getForm(char *cliente_name, char *cliente_lastName, char *cliente_cuit);
static int cliente_addData(Cliente* cliente_list,int cliente_len,int cliente_id,char cliente_name[], char cliente_lastName[], char cliente_cuit[]);
static int cliente_findById(Cliente* cliente_list, int cliente_len,int id);
static int cliente_findIndexById(Cliente* cliente_list, int cliente_len,int id);
static int cliente_modify(Cliente* cliente_list, int cliente_len,int id);
static int cliente_remove(Cliente* cliente_list, int cliente_len,int id);


/**
 * \brief cliente_addHardcode: Adds Hardcoded data for testing purposes
 * \param Cliente* cliente_list: Pointer to array of clients
 * \param int cliente_len: Array length
 * \param int cliente_firstLoad: Pointer to space in memory where is the
 * \variable to indicate if an entry is loaded
 * \return (-1) Error / (0) Ok
 */

int cliente_addHardcode(Cliente* cliente_list, int cliente_len, int *cliente_firstLoad)
{
	int retorno = -1;
	if(cliente_list != NULL && cliente_len >0)
	{
		int cliente_id[]={50,60,70,80,100};
		char cliente_name[][LONG_NAME]={"Juan Carlos",
										"Marcos",
										"Anabel",
										"Ricardo",
										"Florencia"};
		char cliente_lastName[][LONG_NAME]={"Gomez",
									 	 	"Sanchez",
											"Pereira Iraola",
											"Guzman",
											"Bianchi"};
		char cliente_cuit[][LONG_CUIT]={"23304560989",
										"26249359947",
										"21450453475",
										"27103649264",
										"21369834576"};
		for(int i = 0; i < 5; i++)
		{
			cliente_addData(cliente_list, cliente_len, cliente_id[i], cliente_name[i], cliente_lastName[i], cliente_cuit[i]);
		}
		*cliente_firstLoad = TRUE;
	}
	return retorno;
}

/**
 * \brief cliente_initArray: To indicate that all positions in the array are empty,
 * \this function put the flag (cliente_isEmpty) in TRUE in all position of the array
 * \param sEmployee* cliente_list: Pointer to array of clients
 * \param int cliente_len: Array length
 * \return (-1) Error / (0) Ok
 */

int cliente_initArray(Cliente* cliente_list, int cliente_len)
{
	int retorno = -1;
	if(cliente_list != NULL && cliente_len > 0)
	{
		for(int i=0;i<cliente_len;i++)
		{
			cliente_list[i].cliente_isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief cliente_alta: Asks the user for the student data
 * \param Cliente* cliente_list: Pointer to array of clients
 * \param int cliente_len: Array length
 * \param int cliente_firstLoad: Pointer to space in memory where is the
 * \variable to indicate if an entry is loaded
 * \return (-1) Error / (0) Ok
 */

int cliente_alta(Cliente* cliente_list,int cliente_len, int *cliente_firstLoad)
{
	int retorno = -1;
	int cliente_id;
	char cliente_name[LONG_NAME];
	char cliente_lastName[LONG_NAME];
	char cliente_cuit[LONG_CUIT];
	int index;

	if(cliente_list != NULL && cliente_len > 0 && cliente_firstLoad >0 && cliente_checkFirstEmptyIndex(cliente_list, cliente_len, &index)==0)
	{
		if(cliente_getForm(cliente_name, cliente_lastName, cliente_cuit)== 0)
		{
			cliente_id=cliente_generateNewId();
			if(cliente_addData(cliente_list, cliente_len, cliente_id, cliente_name, cliente_lastName, cliente_cuit)==0)
			{
				printf("\nEl ID para %s %s es: %d\n",
						cliente_lastName,
						cliente_name,
						cliente_id);
				*cliente_firstLoad = TRUE;
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
 * \brief cliente_checkFirstEmptyIndex: Checks first empty index in the array
 * \this function search the array for the first index with the value TRUE in the cliente_isEmpty item
 * \param sEmployee* cliente_list: Pointer to array of clients
 * \param int cliente_len: Array length
 * \param int *EmptyIndex: Pointer to position of first empty index.
 * \return (-1) Error / (0) Ok
 */

static int cliente_checkFirstEmptyIndex(Cliente* cliente_list, int cliente_len, int *emptyIndex)
{
	int retorno = -1;
	if(cliente_list != NULL && cliente_len >0 && emptyIndex != NULL)
	{
		for(int i = 0; i < cliente_len; i++)
		{
			if(cliente_list[i].cliente_isEmpty == TRUE)
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
 * \brief cliente_getForm: Brings up a menu for the user to complete with info
 * \param char *cliente_name: Pointer to place to store cliente_name
 * \param char *lastName: Pointer to place to store last cliente_name
 * \param float *salary: Pointer to place to store salary
 * \param int *sector: Pointer to place to store sector
 * \return (-1) Error / (0) Ok
 */

static int cliente_getForm(char *cliente_name, char *cliente_lastName, char *cliente_cuit)
{
	int retorno = -1;

	if(cliente_name != NULL && cliente_lastName != NULL && cliente_cuit != NULL )
	{
		if((utn_getString("Ingrese Apellido:", "Error. ", cliente_lastName, 3, LONG_NAME)==0) &&
		   (utn_getString("Ingrese Nombre:", "Error. ", cliente_name, 3, LONG_NAME)==0) &&
		   (utn_getAlphaNum("Ingrese CUIT(SIN GUIONES):", "Error. ", cliente_cuit, 3, LONG_CUIT)==0))
		{
			retorno = 0;
		}
	}
	return retorno;
}

/**
 *  \brief generateNewId: Generates a new ID that's +1 from previous loaded employee ID.
 */

static int cliente_generateNewId(void)
{
	static int id;

	id = id+1;
	return id;
}

/**
 *  \brief cliente_addData: add in a existing cliente_list of clients the values received
 *  as parameters in the first empty position.
 * \param Employee* cliente_list: Pointer to array of clients
 * \param int cliente_len: Array length
 * \param int id: id generated by generateNewId() function
 * \param char cliente_name[]: Input by user from getEmployeeForm
 * \param char lastName[]: Input by user from getEmployeeForm
 * \param float salary: Input by user from getEmployeeForm
 * \param int sector: Input by user from getEmployeeForm
 * \return (-1) Error / (0) Ok
 */

static int cliente_addData(Cliente* cliente_list,int cliente_len,int cliente_id,char cliente_name[], char cliente_lastName[], char cliente_cuit[])
{
	int retorno = -1;
	int emptyIndex;

	if(cliente_checkFirstEmptyIndex(cliente_list, cliente_len, &emptyIndex)==0)
	{
		cliente_list[emptyIndex].cliente_id=cliente_id;
		cliente_list[emptyIndex].cliente_isEmpty=FALSE;
		strcpy(cliente_list[emptyIndex].cliente_name,cliente_name);
		strcpy(cliente_list[emptyIndex].cliente_lastName,cliente_lastName);
		strcpy(cliente_list[emptyIndex].cliente_cuit,cliente_cuit);
		retorno=0;
	}
    return retorno;
}

/**
 *  \brief cliente_findIndexById: find an Employee by Id then returns the index position in array.
 * \param Employee* cliente_list: Pointer to array of clients
 * \param int cliente_len: Array length
 * \param int id: id to search
 * \return Return employee index position or (-1) if ERROR
 */

static int cliente_findIndexById(Cliente* cliente_list, int cliente_len,int id)
{
	int retorno;

	if (cliente_list != NULL && cliente_len > 0 && id > 0)
	{
		for (int i = 0; i < cliente_len; i++)
		{
			if(cliente_list[i].cliente_isEmpty == FALSE && cliente_list[i].cliente_id == id )
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;;
}


/**
 *  \brief cliente_findById: find a cliente by Id and returns 0 if ID is found
 * \param Cliente* cliente_list: Pointer to array of clientes
 * \param int cliente_len: Array length
 * \param int id: id to search
 * \return Return 0 if ID exists or (-1) if ERROR
 */

static int cliente_findById(Cliente* cliente_list, int cliente_len,int id)
{
	int retorno = -1;

	if (cliente_list != NULL && cliente_len > 0 && id > 0)
	{
		for (int i = 0; i < cliente_len; i++)
		{
			if(cliente_list[i].cliente_isEmpty == FALSE && cliente_list[i].cliente_id == id )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;;
}

/**
 * \brief cliente_modifyMenu: Modifies the data of an Employee by given Id.
 * Allows to modify individual fields of the employee by a switch
 * \param Employee* cliente_list: Pointer to array of clients
 * \param int cliente_len: Array length
 * \param int cliente_firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

int cliente_modifyMenu(Cliente* cliente_list, int cliente_len, int cliente_firstLoad)
{
	int retorno = -1;
	int idToSearch;

	if(cliente_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(utn_getIntNumber("Ingrese el ID a modificar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   cliente_findById(cliente_list, cliente_len, idToSearch)== 0)
		{
			if(cliente_modify(cliente_list,cliente_len,idToSearch)==0)
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
 * \brief cliente_modify: Modifies the data of an Employee by given Id.
 * Allows to modify individual fields of the employee by a switch
 * \param Employee* cliente_list: Pointer to array of clients
 * \param int cliente_len: Array length
 * \param int cliente_firstLoad: variable to check if there is even one entry loaded
 * \return (-1) Error / (0) Ok
 */

static int cliente_modify(Cliente* cliente_list, int cliente_len,int id)
{
	int retorno = -1;
	int choosenOption;
	char answer;
	int indexToModify;

	Cliente bufferCliente;

	indexToModify = cliente_findIndexById(cliente_list, cliente_len, id);

	if(cliente_list != NULL && cliente_len>0 && id > 0 && indexToModify > -1)
	{
		do
		{
			printf("Cliente a modificar\n");
			printf("Apellido y Nombre: %s %s CUIT: %s.\n",
					cliente_list[indexToModify].cliente_lastName,
					cliente_list[indexToModify].cliente_name,
					cliente_list[indexToModify].cliente_cuit);
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
						if(utn_getString("\nApellido:","\nError. ",bufferCliente.cliente_lastName,2,LONG_NAME)==0)
						{
							strcpy(cliente_list[indexToModify].cliente_lastName,bufferCliente.cliente_lastName);
						}
						break;
					case 2:
						if(utn_getString("\nNombre:","\nError. ",bufferCliente.cliente_name,2,LONG_NAME)==0)
						{
							strcpy(cliente_list[indexToModify].cliente_name,bufferCliente.cliente_name);
						}
						break;
					case 3:
						if(utn_getAlphaNum("\nCUIT (SIN GUIONES):","\nError. ",bufferCliente.cliente_cuit,2,LONG_CUIT)==0)
						{
							strcpy(cliente_list[indexToModify].cliente_cuit,bufferCliente.cliente_cuit);
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
 * \brief cliente_removeMenu: Remove a Employee by Id (put cliente_isEmpty Flag in TRUE)
 * \param Employee* cliente_list: Pointer to array of clients
 * \param int cliente_len: Array length
 * \param int *cliente_firstLoad: variable to check if there is even one entry loaded and
 *  safeguard to prevent errors if all data is erased
 * \return (-1) Error / (0) Ok
 */

int cliente_removeMenu(Cliente* cliente_list, int cliente_len,int *cliente_firstLoad)
{
	int retorno = -1;
	int idToSearch;

	if(*cliente_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(utn_getIntNumber("Ingrese el ID a eliminar:","Error, no es un ID valido. ",&idToSearch,3,INT_MAX,1)==0 &&
		   cliente_findById(cliente_list, cliente_len, idToSearch)== 0 &&
		   cliente_remove(cliente_list,cliente_len,idToSearch)== 0)
		{
			for(int i = 0; i < cliente_len; i++)
			{
				if(cliente_list[i].cliente_isEmpty == TRUE)
				{
					*cliente_firstLoad = FALSE;
				}
				else
				{
					*cliente_firstLoad = TRUE;
					break;
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * \brief cliente_remove: Remove a Employee by Id (put cliente_isEmpty Flag in TRUE)
 * \param Employee* cliente_list: Pointer to array of clients
 * \param int cliente_len: Array length
 * \param int id: id value of entry to remove
 *  safeguard to prevent errors if all data is erased
 * \return (-1) Error / (0) Ok
 */

static int cliente_remove(Cliente* cliente_list, int cliente_len,int id)
{
	int retorno = -1;
	int indexToModify;
	char answer;

	indexToModify = cliente_findIndexById(cliente_list, cliente_len, id);

	if(cliente_list != NULL && cliente_len>0 && id > 0 && indexToModify > -1)
	{
		printf("Cliente a eliminar\n");
		printf("Apellido y Nombre: %s %s  CUIL: %s\n", cliente_list[indexToModify].cliente_lastName,cliente_list[indexToModify].cliente_name,cliente_list[indexToModify].cliente_cuit);
		utn_getChar("¿Desea eliminar este ID?(Y/N)", "Error. ", &answer, 'Y', 'N', 3);
		switch(answer)
		{
			case 'Y':
				cliente_list[indexToModify].cliente_isEmpty = TRUE;
				printf("\nREGISTRO DE CLIENTE BORRADO CON EXITO.\n");
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
 * \brief cliente_print: print the content of clients array
 * \param Employee* cliente_list: Pointer to array of clients
 * \param int cliente_len: Array length
 * \param int cliente_firstLoad: Pointer to space in memory where is the
 * \variable to indicate if an entry is loaded
 * \return (-1) Error / (0) Ok*
 */

int cliente_print(Cliente* cliente_list, int cliente_len, int cliente_firstLoad)
{
	int retorno = -1;

	if(cliente_firstLoad == FALSE)
	{
		printf("\nERROR. NO HAY DATOS INGRESADOS.\n");
	}
	else
	{
		if(cliente_list != NULL && cliente_len > 0)
		{
			printf("-------------------------------------------------------------\n");
			printf("| APELLIDO        | NOMBRE          | CUIT            | ID  |\n");
			printf("-------------------------------------------------------------\n");
			for(int i=0;i< cliente_len ;i++)
			{
				if(cliente_list[i].cliente_isEmpty == FALSE)
				{
					printf("| %-16s| %-16s| %-16s| %-3d |\n",
							cliente_list[i].cliente_lastName,
							cliente_list[i].cliente_name,
							cliente_list[i].cliente_cuit,
							cliente_list[i].cliente_id);
					printf("-------------------------------------------------------------\n");
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}