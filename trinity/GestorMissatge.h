
#ifndef PRACTICA_SO_GESTORMISSATGE_H
#define PRACTICA_SO_GESTORMISSATGE_H

#include "includes.h"
#include "main.h"

char* generaTrama(int Opcio, char* data);

#define CON_CLI 1
#define CON_SER_OK 2
#define CON_SER_KO 22
#define SAY_CLI 3
#define SAY_SER 4
#define BROAD_CLI 5
#define BROAD_SER 6



#define CON_CLI_HEADER "[TR_NAME]"
#define CON_SER_OK_HEADER "[CONOK]"
#define CON_SER_KO_HEADER "[CONKO]"

#endif