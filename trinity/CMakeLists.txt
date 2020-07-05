cmake_minimum_required(VERSION 3.15)
project(Practica_SO C)

set(CMAKE_C_STANDARD 99)
include_directories(/Users/jvid/CLionProjects/SO-2020/trinity)

add_executable(Practica_SO main.c GestorMissatge.c GestorMissatge.h StringProcess.h StringProcess.c prints.h Options.c main.h Options.h showConnections.c showConnections.h includes.h serverService.c serverService.h clientService.h clientService.c)