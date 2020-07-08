//
// Created by root on 10/30/19.
//

#ifndef PRACTICA_SO_STRINGPROCESS_H
#define PRACTICA_SO_STRINGPROCESS_H

#include "includes.h"

#include "clientService.h"
#include "main.h"
#include "Options.h"
#include "serverService.h"
#include "showConnections.h"

int readTextInput(char*, char*);

char* readUntil(int, char);

int readConfigurationFile(char* , Conf*);

char* selectWord(int, char*);

int SizeWord(int n, char* texto);

#endif //PRACTICA_SO_STRINGPROCESS_H
