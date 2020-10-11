/*
 ============================================================================
 Name        : publicacion.h
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header for Library publicacion.c
 ============================================================================
 */

#ifndef PUBLICACION_H_
#define PUBLICACION_H_

#define TRUE 1
#define FALSE 0
#define ACTIVE 1
#define PAUSED 0
#define LONG_DESCRIPTION 65

typedef struct
{
	int publicacion_id;
	int publicacion_isEmpty;
	int publicacion_category;
	char publicacion_description[LONG_DESCRIPTION];
	int publicacion_idCliente;
	int publicacion_status;
}Publicacion;

int publicacion_initArray(Publicacion* publicacion_list, int publicacion_len);
int publicacion_addHardcode(Publicacion* publicacion_list, int publicacion_len, int *publicacion_firstLoad);
int publicacion_alta(Publicacion* publicacion_list,int publicacion_len, int *publicacion_firstLoad);
int publicacion_modifyMenu(Publicacion* publicacion_list, int publicacion_len, int publicacion_firstLoad);
int publicacion_removeMenu(Publicacion* publicacion_list, int publicacion_len,int *publicacion_firstLoad);
int publicacion_print(Publicacion* publicacion_list, int publicacion_len,int publicacion_firstLoad);



#endif /* PUBLICACION_H_ */
