/*
 ============================================================================
 Name        : diario.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Library diario.c
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "cliente.h"


/**
 * \brief getMenu: Menu for choosing options of the program,
 * \param choosenOption* list: Pointer to variable that stores choosen option
 * \return (-1) Error / (0) Ok
 */

int diario_getMenu(int* choosenOption)
{
	int retorno = -1;
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
	return retorno;
}
