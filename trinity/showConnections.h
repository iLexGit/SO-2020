//
// Created by root on 11/1/19.
//

#ifndef PRACTICA_SO_SHOWCONNECTIONS_H
#define PRACTICA_SO_SHOWCONNECTIONS_H

#include "includes.h"

#include "clientService.h"
#include "main.h"
#include "Options.h"
#include "serverService.h"
#include "StringProcess.h"

int checkDomain(char*, struct in_addr*);

void scanConnections(int, int, int);

#endif //PRACTICA_SO_SHOWCONNECTIONS_H
