//
// Created by root on 11/3/19.
//

#ifndef PRACTICA_SO_SERVERSERVICE_H
#define PRACTICA_SO_SERVERSERVICE_H

#include "includes.h"

#include "clientService.h"
#include "main.h"
#include "Options.h"
#include "showConnections.h"
#include "StringProcess.h"
#include "Audios.h"

typedef struct{
    Conf* config;
    int conn;
}serverThreadData;

int serverService();

void* serverServiceThread_aux();

void serverServiceThread(int);
#endif //PRACTICA_SO_SERVERSERVICE_H
