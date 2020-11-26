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


#define MAINMENU_HEADER "|     REGISTRO DE CLIENTES Y VENTAS     |\n"
#define MAINMENU_MSJ "\nIngrese una opción:\n 1-Agregar cliente.\n 2-Vender afiches.\n 3-Modificar venta.\n 4-Cobrar venta.\n 5-Generar informe de cobros.\n 6-Generar informe de deudas.\n 7-Generar estadisticas.\n 8-Guardar los datos y salir.\nOpcion:"
#define MODIFYMENU_MSJ "\nIngrese campo a modificar: \n 1-Nombre del Archivo: \n 2-Cantidad: \n 3-Zona: \n 4-Volver al menu principal\nOpcion: "
#define STATISTICSMENU_MSJ "\n¿Que desea averiguar?\n 1-Cliente al que se le vendió mas afiches: \n 2-Cliente al que se le vendió menos afiches: \n 3-Venta con mas afiches vendidos: \n 4-Venta con menos afiches vendidos: \n 5-Volver al menu principal\nOpcion: "
#define ERROR_MSJ "ERROR, INGRESE UNA OPCION VALIDA. "


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
		printf("\n-----------------------------------------\n");
		printf(MAINMENU_HEADER);
		printf("-----------------------------------------\n");
		if(utn_getIntNumber(MAINMENU_MSJ,ERROR_MSJ, choosenOption, 3, 8, 1)==0)
		{
			output =0;
		}
		else
		{
			*choosenOption = 8;
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

int menu_getStatisticsMenu(int* choosenOption)
{
	int output = -1;
	if(choosenOption !=NULL)
	{
		if(utn_getIntNumber(STATISTICSMENU_MSJ,ERROR_MSJ, choosenOption, 3, 5, 1)==0)
		{
			output =0;
		}
		else
		{
			*choosenOption = 5;
		}
	}
	return output;
}


