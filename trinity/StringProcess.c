//
// Created by root on 10/30/19.
//
#include "StringProcess.h"

int readTextInput(char* text, char* string) {
    int i = 0;
    string = (char*)malloc(sizeof(char));

    while(text[i] != '"'){
        i++;
        if(text[i-1] == '\0'){free(string); return 0;}
    }
    i++;

    int posicio = 0;
    while(text[i] != '"'){
        if(text[i] == '\0'){free(string); return 0;}
        string[posicio] = text[i];
        string = (char*)realloc(string,sizeof(char) * (posicio + 2));
        posicio++;
        i++;
    }
    string[posicio] = '\0';
    return 1;
}

char* readUntil(int fd, char end) {
    int i = 0;
    char c = '\0';
    int EndOFile = 1;
    char* string = (char*)malloc(sizeof(char));

    while (c != end) {
        EndOFile = read(fd, &c, sizeof(char));
        if (EndOFile == 0){
            return "EOF";
        }
        if (c != end) {
            string = (char*)realloc(string, sizeof(char) * (i + 2));
            string[i] = c;
        }
        i++;
    }

    string[i - 1] = '\0';
    return string;
}

int readConfigurationFile(char * path){

    int fd = open(path, O_RDONLY);

    if (fd < 0) {
        write(1, FILE_NOT_FOUND_ERR, strlen(FILE_NOT_FOUND_ERR));
        return -1;
    }


    char* aux;

    conf.name = readUntil(fd, '\n');
    conf.audio_folder = readUntil(fd, '\n');
    conf.IPaddress = readUntil(fd, '\n');

    aux = readUntil(fd, '\n');
    conf.port = atoi(aux);
    free(aux);

    conf.direccio = readUntil(fd, '\n');

    aux = readUntil(fd, '\n');
    conf.port_list_inicial = atoi(aux);
    free(aux);

    aux = readUntil(fd, '\n');
    conf.port_list_final = atoi(aux);
    free(aux);

    close(fd);

    return 0;

}

char* extreuMissatge(char* text){
    printf("Extreurem missatge de:\n\t\t%s\n", text);
    char* retornar = (char*)malloc(sizeof(char));
    int i = 0;
    int scanner = 0;
    while(text[scanner] != '\"'){scanner++;}
    scanner++;
    while(text[scanner] != '\"'){
        retornar[i] = text[scanner];
        i++;
        retornar = (char*)realloc(retornar, i+1);
        scanner++;
    }
    printf("extreuMissatge:\t%s\n", retornar);
    if ((text[scanner+1] =='\0' || text[scanner+1] =='\n') && strlen(retornar) < 180){
        return retornar;
    }
    return "ERROR\0";

}


char* selectWord(int n, char* texto){

    int i = 0;
    int lletra= 0;
    int posicio;
    char* word;

    while (i < n){
        word = (char*)malloc(sizeof(char));
        posicio = 0;
        while((texto[lletra] != ' ') && (texto[lletra] != '\0')){
            if(texto[lletra] != '\"'){
                word[posicio] = texto[lletra];
                word = (char*)realloc(word,sizeof(char) * (posicio + 2));
                posicio++;
                lletra++;
            }
        }


        word[posicio] = '\0';
        i++;
        lletra++;

        if(i<n){word = (char*)realloc(word,0);free(word);}
        if(texto[lletra-1] == '\0'){break;}
    }
    if(i<n){
        //printf("No existeix la paraula en la posició %d\n", n);
        return "ERROR\0";
    }

    return word;
}
