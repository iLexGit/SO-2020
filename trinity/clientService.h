//
// Created by root on 11/3/19.
//

#ifndef PRACTICA_SO_CLIENTSERVICE_H
#define PRACTICA_SO_CLIENTSERVICE_H

#include "includes.h"

#include "main.h"
#include "Options.h"
#include "serverService.h"
#include "showConnections.h"
#include "StringProcess.h"

void clientService();

//int estableixConnexio(int*, char*, int);
int estableixConnexio( char*, int);

int weAreConnected(int);

#endif //PRACTICA_SO_CLIENTSERVICE_H
