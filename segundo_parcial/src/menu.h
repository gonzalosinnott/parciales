 /*
 ============================================================================
 Name        : menu.h
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header for Library menu.c
 ============================================================================
 */

#ifndef MENU_H_
#define MENU_H_

int menu_getMainMenu(int* choosenOption);
int menu_getModifyMenu(int* choosenOption);
int menu_getSortMenu(int* choosenOption, int* choosenOrder);
int menu_exitMenu(int* choosenOption);

#endif /* MENU_H_ */
