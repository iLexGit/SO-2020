//
// Created by root on 10/31/19.
//

#ifndef PRACTICA_SO_OPTIONS_H
#define PRACTICA_SO_OPTIONS_H

#include "includes.h"

#include "clientService.h"
#include "main.h"
#include "serverService.h"
#include "showConnections.h"
#include "StringProcess.h"
#include "Connecta.h"

int whichCommand(char *, Conf*, int*);

typedef struct{
    Connexio* connexions;
    int port;
}ClientThreadData;

#endif //PRACTICA_SO_OPTIONS_H
