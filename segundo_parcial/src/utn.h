/*
 ============================================================================
 Name        : utn.h
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Header for Library utn.c
 ============================================================================
 */

#ifndef UTN_H_
#define UTN_H_

int utn_getIntNumber(char* msj, char* errorMsj, int* pValue,int retries,int max,int min);
int utn_getFloatNumber(char* msj, char* errorMsj, float* pValue,int retries, float max, float min);
int utn_getString(char* msj, char* errorMsj, char* pValue,int retries, int len);
int utn_getAlphaNum(char* msj, char* errorMsj, char* pValue,int retries, int len);
int utn_getCuit(char* msj, char* errorMsj, char* pValue,int retries, int len);

#endif /* UTN_H_ */
