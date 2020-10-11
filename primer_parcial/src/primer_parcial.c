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
#include "diario.h"
#include "cliente.h"
#include "publicacion.h"


#define TRUE 1
#define FALSE 0
#define QTY_CLIENTES 100
#define QTY_PUBLICACIONES 1000


int main(void) {

	int choosenOption;
	int cliente_firstLoad = FALSE;
	int publicacion_firstLoad = FALSE;

	Cliente arrayClientes[QTY_CLIENTES];
	Publicacion arrayPublicaciones[QTY_PUBLICACIONES];

	cliente_initArray(arrayClientes, QTY_CLIENTES);
	publicacion_initArray(arrayPublicaciones, QTY_PUBLICACIONES);


	cliente_addHardcode(arrayClientes, QTY_CLIENTES, &cliente_firstLoad);
	publicacion_addHardcode(arrayPublicaciones, QTY_PUBLICACIONES, &publicacion_firstLoad);
	//ABM ANDANDO
	do
		{
			diario_getMenu(&choosenOption);
			switch(choosenOption)
			{
				case 1://ALTA CLIENTE (LISTO)
					cliente_alta(arrayClientes, QTY_CLIENTES, &cliente_firstLoad);
					break;
				case 2://MODIFICAR CLIENTE (LISTO)
					cliente_modifyMenu(arrayClientes, QTY_CLIENTES, cliente_firstLoad);
					break;
				case 3://BAJA CLIENTE (FALTA LINKEAR A PUBLICACIONES)
					cliente_removeMenu(arrayClientes, QTY_CLIENTES, &cliente_firstLoad);
					break;
				case 4://ALTA PUBLICACION (TEST ALTA PUBLICACION SOLA)
					publicacion_alta(arrayPublicaciones, QTY_PUBLICACIONES, &cliente_firstLoad);
					break;
				case 5://PAUSAR PUBLICACION (TEST MODIFICAR PUBLICACION)
					publicacion_modifyMenu(arrayPublicaciones, QTY_PUBLICACIONES, cliente_firstLoad);
					break;
				case 6://REANUDAR PUBLICACION (TEST BAJA PUBLICACION)
					publicacion_removeMenu(arrayPublicaciones, QTY_PUBLICACIONES, &cliente_firstLoad);
					break;
				case 7://IMPRIMIR CLIENTES (FALTA LINKEAR A PUBLICACIONES) (TEST IMPRIMIR AMBAS)
					cliente_print(arrayClientes, QTY_CLIENTES, cliente_firstLoad);
					publicacion_print(arrayPublicaciones, QTY_PUBLICACIONES, cliente_firstLoad);
					break;
				case 8://INFORMES
					break;
			}
		}while(choosenOption!=9);
		printf("PROGRAMA TERMINADO");
		return EXIT_SUCCESS;



}
