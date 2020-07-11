//
// Created by root on 10/31/19.
//

#ifndef PRACTICA_SO_MAIN_H
#define PRACTICA_SO_MAIN_H

#include "includes.h"

#include "clientService.h"
#include "Options.h"
#include "serverService.h"
#include "showConnections.h"
#include "StringProcess.h"


int main(int, char**);
void* startClientService(void*);
void* startServerService(void*);
extern Connexio * connexions;
extern int numConnexions;
extern Conf conf;
extern int* srvconnfds;
extern int srv_numConnexions;
extern int sockfd;
#endif //PRACTICA_SO_MAIN_H
