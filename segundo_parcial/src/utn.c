/*
 ============================================================================
 Name        : utn.c
 Author      : Gonzalo Sinnott Segura
 Version     :
 Copyright   :
 Description : Library utn.c
 ============================================================================
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"

#define BUFFER_STRING_LEN 500

static int myGets(char *string, int len);
static int getInt(int *pValue);
static int isInt(char* string);
static int getFloat(float* pValue);
static int isFloat(char* string);
static int checkString(char* string,int len);
static int checkAlphaNum(char* string, int len);

/**
 * \brief myGets: Reads from stdin until a '\n' (finalization character)
 *  or until it has copied a string of a length of lenght - 1 characters .
 * \param char *string: Pointer to memory space where string will be copied
 * \param int len: String lenght
 * \return (-1) Error / (0) Ok
 */

static int myGets(char *string, int len)
{
	int output = -1;
	__fpurge(stdin);
	if(string != NULL && len > 0 && fgets (string, len, stdin) == string)
	{
		if(string[strlen(string)-1]=='\n')
		{
			string[strlen (string) - 1] = '\0';
		}
		output = 0;
	}
	return output;
}

/**
 * \brief utn_getIntNumber: Asks the user for an int value
 * \param char* msj: Message for the user
 * \param char* errorMsj: Error message
 * \param int* pValue: Pointer to store value given by user
 * \param int retries: amount of retries permitted
 * \param int max: max value admitted
 * \param int min: min value admitted
 * \return (-1) Error / (0) Ok
 */

int utn_getIntNumber(char* msj, char* errorMsj, int* pValue,int retries,int max,int min)
{
	int output = -1;
	int bufferInt;

	if(msj != NULL && errorMsj != NULL && pValue != NULL && retries >= 0 && min <= max)
	{
		do
		{
			printf("%s",msj);
			if(getInt(&bufferInt) == 0 && bufferInt >= min && bufferInt <= max)
			{
				*pValue = bufferInt;
				output = 0;
				break;
			}
			else
			{
				printf("%s Quedan %d reintentos\n",errorMsj, retries);
				retries--;
			}
		}while(retries >= 0);
	}
	return output;
}

/**
 * \brief getInt: Asks the user for an integer number, converts it to string,
 *  then validates said value and returns it as an integer.
 * \param int* pValue: pointer to Value given by user.
 * \return (-1) Error / (0) Ok
 */

static int getInt(int *pValue)
{
	int output = -1;
	char buffer[64];
	if(pValue != NULL)
	{
		if(myGets(buffer,sizeof(buffer))==0 && isInt(buffer))
		{
			*pValue = atoi(buffer);
			output = 0;
		}
	}
	return output;
}

/**
 * \brief isInt:Checks if the string entered by the user is a number
 * \param char *string: string of characters to analize
 * \return (0) Error / (1) Ok
 */

static int isInt(char* string)
{
	int output = 1;
	int i = 0;

	if(string != NULL)
	{
		if(string[0] == '-')
		{
			i = 1;
		}
		if(string != NULL && strlen(string) > 0)
		{
			while(string[i] != '\0')
			{
				if(string[i] < '0' || string[i] > '9' )
				{
					output = 0;
					break;
				}
				i++;
			}
		}
	}
	return output;
}
/**
 * \brief utn_getFloat: Asks the user for a float value
 * \param char* msj: Message for the user
 * \param char* errorMsj: Error message
 * \param int* pValue: Pointer to store value given by user
 * \param int retries: amount of retries permitted
 * \return (-1) Error / (0) Ok
 */

int utn_getFloatNumber(char* msj, char* errorMsj, float* pValue,int retries, float max, float min)
{
	int output = -1;
	float bufferFloat;

		if(msj != NULL && errorMsj != NULL && pValue != NULL && retries >= 0 && min <= max)
		{
			do
			{
				printf("%s",msj);
				if(getFloat(&bufferFloat) == 0 && bufferFloat >= min && bufferFloat <= max)
				{
					*pValue = bufferFloat;
					output = 0;
					break;
				}
				else
				{
					printf("%s Quedan %d reintentos\n",errorMsj, retries);
					retries--;
				}
			}while(retries > 0);
		}
		return output;
}

/**
 * \brief getFloat: Asks the user for a float number, converts it to string,
 *  then validates said value and returns it as an float.
 * \param int* pValue: pointer to Value given by user.
 * \return (-1) Error / (0) Ok
 */

static int getFloat(float* pValue)
{
	int output = -1;
	char buffer[64];
	if(pValue != NULL)
	{
		if(myGets(buffer,sizeof(buffer))==0 && isFloat(buffer))
		{
			*pValue = atof(buffer);
			output = 0;
		}
	}
	return output;
}

/**
 * \brief isFloat:Checks if the string entered by the user is a number
 * \param char *string: string of characters to analize
 * \return (0) Error / (1) Ok
 */

static int isFloat(char* string)
{
	int output = 1;
	int i = 0;
	int comaCount = 0;

	if(string[0] == '-')
	{
		i = 1;
	}
	if(string != NULL && strlen(string) > 0)
	{
		while(string[i] != '\0')
		{
			if(string[i] == '.')
			{
				comaCount++;
				if(((string[i] < '0' || string[i] > '9') && string[i] != '.') || comaCount > 1)
				{
					output = 0;
					break;
				}
			}
			i++;
		}
	}
	return output;
}
/**
 * \brief utn_getString Asks the user for an string value
 * \param char* msj: Message for the user
 * \param char* errorMsj: Error message
 * \param int* pValue: Pointer to store value given by user
 * \param int retries: amount of retries permitted
 * \param int len: length allowed for the value entered.
 * \return (-1) Error / (0) Ok
 */

int utn_getString(char* msj, char* errorMsj, char* pValue,int retries, int len)
{
	char bufferString[BUFFER_STRING_LEN];
	int output = -1;

	if(msj != NULL && errorMsj != NULL && pValue != NULL && retries >= 0 && len > 0)
	{
		do
		{
			printf("%s",msj);
			if(myGets(bufferString,BUFFER_STRING_LEN) == 0 &&
			   strnlen(bufferString,sizeof(bufferString)-1)<= len &&
			   checkString(bufferString,len) == 0 )
			{
				strncpy(pValue,bufferString,len);
				output = 0;
				break;
			}
			else
			{
				printf("%s Quedan %d reintentos\n",errorMsj, retries);
				retries--;
			}
		}while(retries >= 0);
	}
	return output;
}

/**
 * \brief checkString: Checks the string for invalid characters
 * Allows upper and lower case letters and spaces
 * \param char* string: Pointer to string to check
 * \param int len: max length allowed of the string
 * \return (-1) Error / (0) Ok
 */

static int checkString(char* string,int len)
{
	int output = 0;

	if( string != NULL && len > 0)
	{
		for(int i=0; i<=len && string[i] != '\0';i++)
		{
			if(	(string[i] < 'A' || string[i] > 'Z') &&
				(string[i] < 'a' || string[i] > 'z') &&
				 string[i] != ' ')
			{
				output = -1;
				break;
			}
		}
	}
	return output;
}

/**
 * \brief utn_getAlphaNum: Asks the user for an alphanumeric value
 * \param char* msj: Message for the user
 * \param char* errorMsj: Error message
 * \param int* pValue: Pointer to store value given by user
 * \param int retries: amount of retries permitted
 * \param int len: length allowed for the value entered.
 * \return (-1) Error / (0) Ok
 */

int utn_getAlphaNum(char* msj, char* errorMsj, char* pValue,int retries, int len)
{
	char bufferString[BUFFER_STRING_LEN];
	int output = -1;

	if(msj != NULL && errorMsj != NULL && pValue != NULL && retries >= 0 && len > 0)
	{
		do
		{
			printf("%s",msj);
			if(myGets(bufferString,BUFFER_STRING_LEN) == 0 &&
			   strnlen(bufferString,sizeof(bufferString)-1)<= len &&
			   checkAlphaNum(bufferString,len) == 0 )
			{
				strncpy(pValue,bufferString,len);
				output = 0;
				break;
			}
			else
			{
				printf("%s Quedan %d reintentos\n",errorMsj, retries);
				retries--;
			}
		}while(retries >= 0);
	}
	return output;
}

/**
 * \brief checkAlphaNum: Checks the string for invalid characters
 * Allows upper and lower case letters, numbers and spaces
 * \param char* string: Pointer to string to check
 * \param int len: max lenght allowed of the string
 * \return (-1) Error / (0) Ok
 */

static int checkAlphaNum(char* string, int len)
{
	int output = 0;

	if(string != NULL && len > 0)
	{
		for(int i=0; i<=len && string[i] != '\0';i++)
		{
			if((string[i] != ' ') &&
			   (string[i] != '.') &&
			   (string[i] != '-') &&
			   (string[i] != '@') &&
			   (string[i] < 'a' || string[i] > 'z') &&
			   (string[i] < 'A' || string[i] > 'Z') &&
			   (string[i] < '0' || string[i] > '9'))
			{
				output = -1;
				break;
			}
		}
	}
	return output;
}

/**
 * \brief utn_getCuit: Asks the user for a CUIT value
 * \param char* msj: Message for the user
 * \param char* errorMsj: Error message
 * \param int* pValue: Pointer to store value given by user
 * \param int retries: amount of retries permitted
 * \param int len: length allowed for the value entered.
 * \return (-1) Error / (0) Ok
 */

#define LEN_FORMATEDCUIT 14
#define LEN_CUIT 12

int utn_getCuit(char* msj, char* errorMsj, char* pValue,int retries, int len)
{
	int output = -1;
	char formatedCUIT[LEN_FORMATEDCUIT];
	char bufferString[len];

	if(msj != NULL && errorMsj != NULL && pValue != NULL && retries >= 0 && len >0 )
	{

		do
		{
			printf("%s",msj);
			if(myGets(bufferString,len) == 0 &&
			   strnlen(bufferString,sizeof(len)-1) <= len &&
			   checkAlphaNum(bufferString,len) == 0)
			{
				if(strlen(bufferString) > (len-1) || strlen(bufferString) < (len-1))
				{
					printf("%s Quedan %d reintentos\n",errorMsj, retries);
					printf("INGRESE UN NUMERO DE 11 DIGITOS\n");
					retries--;
				}
				else
				{
					sprintf(formatedCUIT,"%.2s-%.8s-%s", bufferString,bufferString+2,bufferString+10);
					strncpy(pValue,formatedCUIT,LEN_FORMATEDCUIT);
					output = 0;
					break;
				}
			}

		}while(retries >= 0);

	}
	return output;
}




