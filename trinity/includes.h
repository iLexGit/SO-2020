//
// Created by root on 11/3/19.
//

#ifndef PRACTICA_SO_INCLUDES_H
#define PRACTICA_SO_INCLUDES_H

#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

#include "prints.h"



/*#include "clientService.h"
#include "main.h"
#include "Options.h"
#include "serverService.h"
#include "showConnections.h"
#include "StringProcess.h"*/

#define Num_Connexions (int)(sizeof(connexions)/sizeof(Connexio))


typedef struct{
    char* name;
    char* audio_folder;
    char* IPaddress;
    int port;
    char* direccio;
    int port_list_inicial;
    int port_list_final;
} Conf;

typedef struct{
    char type;
    char* header;
    short length;
    char* data;
} Trama;

typedef struct{
    char* name;
    int port;
    int fd;
} Connexio;



#endif //PRACTICA_SO_INCLUDES_H
