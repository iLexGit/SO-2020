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

#endif //PRACTICA_SO_MAIN_H
