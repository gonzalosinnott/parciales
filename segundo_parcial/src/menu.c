 /*
 ============================================================================
 Name        : menu.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Library menu.c
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "menu.h"
#include "utn.h"


#define MAINMENU_HEADER "|                               REGISTRO DE EMPLEADOS                          |\n"
#define MAINMENU_MSJ "\nIngrese una opción:\n 1-Cargar los datos de los empleados desde el archivo(modo texto).\n 2-Cargar los datos de los empleados desde el archivo (modo binario).\n 3-Alta de empleado.\n 4-Modificar datos de empleado.\n 5-Baja de empleado.\n 6-Listar empleados.\n 7-Ordenar empleados.\n 8-Guardar los datos de los empleados en el archivo (modo texto).\n 9-Guardar los datos de los empleados en el archivo (modo binario).\n 10-Salir.\nOpcion:"
#define MODIFYMENU_MSJ "\nIngrese campo a modificar: \n 1-Nombre: \n 2-Horas trabajadas: \n 3-Sueldo: \n 4-Volver al menu principal\nOpcion: "
#define ERROR_MSJ "ERROR, INGRESE UNA OPCION VALIDA. "
#define SORTMENU "\nIngrese campo a ordenar:\n 1-Id\n 2-Nombre\n 3-Horas trabajadas\n 4-Sueldo\n 5-Volver al menu principal\n\nOpcion:"
#define CRITERIAMENU "\nIngrese el criterio con el que desea ordenar:\n 1-ASCENDENTE\n 0-DESCEDENTE\nOpcion:"
#define EXITMENU_MSJ "\n¿Desea guardar el archivo?\n 1-SI\n 2-NO\nOpcion: "


/**
 * \brief menu_getMainMenu: Menu principal del programa
 * \param choosenOption* int: Puntero a la direccion nde memoria de la variable que almacena la opcion elegida
 * \return (-1) Error / (0) Ok
 */

int menu_getMainMenu(int* choosenOption)
{
	int output = -1;
	if(choosenOption !=NULL)
	{
		printf("\n--------------------------------------------------------------------------------\n");
		printf(MAINMENU_HEADER);
		printf("--------------------------------------------------------------------------------\n");
		if(utn_getIntNumber(MAINMENU_MSJ,ERROR_MSJ, choosenOption, 3, 10, 1)==0)
		{
			output =0;
		}
		else
		{
			*choosenOption = 10;
		}
	}
	return output;
}

/**
 * \brief menu_getModifyMenu: Menu para elegir el campo a modificar
 * \param choosenOption* int: Puntero a la direccion nde memoria de la variable que almacena la opcion elegida
 * \return (-1) Error / (0) Ok
 */

int menu_getModifyMenu(int* choosenOption)
{
	int output = -1;
	if(choosenOption !=NULL)
	{
		if(utn_getIntNumber(MODIFYMENU_MSJ,ERROR_MSJ, choosenOption, 3, 4, 1)==0)
		{
			output =0;
		}
		else
		{
			*choosenOption = 4;
		}
	}
	return output;
}

/**
 * \brief menu_getSortMenu: Menu para elegir el campo a partir del cual ordenar la lista y el orden de la misma
 * \param choosenOption* int: Puntero a la direccion nde memoria de la variable que almacena la opcion elegida
 * \param choosenOrder* int: Puntero a la direccion nde memoria de la variable que almacena la opcion elegida
 * \return (-1) Error / (0) Ok
 */

int menu_getSortMenu(int* choosenOption, int* choosenOrder)
{
	int output = -1;

	if(choosenOption != NULL && choosenOrder != NULL)
	{
		if(utn_getIntNumber(SORTMENU, ERROR_MSJ, choosenOption, 3, 5, 1)==0 &&
		   *choosenOption != 5)
		{
			if(utn_getIntNumber(CRITERIAMENU, ERROR_MSJ, choosenOrder, 3, 1, 0)==0)
			{
				printf("\nORDENANDO.....\n");
				output =0;
			}
		}
		else if (*choosenOption != 5)
		{
			output = 0;
		}
	}
	return output;
}

/**
 * \brief menu_exitMenu: Menu para salir del programa
 * \param choosenOption* int: Puntero a la direccion nde memoria de la variable que almacena la opcion elegida
 * \return (-1) Error / (0) Ok
 */

int menu_exitMenu(int* choosenOption)
{
	int output = -1;
	int exitAnswer;

	if(choosenOption != NULL)
	{
		if(utn_getIntNumber(EXITMENU_MSJ,ERROR_MSJ, &exitAnswer, 3, 2, 1)==0)
		{
			if(exitAnswer==1)
			{
				*choosenOption = 0;
			}
			else if(exitAnswer==2)
			{
				*choosenOption = 10;
			}
		}
		else
		{
			printf("\nERROR, ELIGA UNA OPCION VALIDA\n");
			*choosenOption = 0;
		}
		output =0;
	}
	return output;
}
