//
// Created by root on 10/31/19.
//

#include "Options.h"

int whichCommand(char* comanda, Conf* conf, int* socket_client) {
    char *word = selectWord(1, comanda);
    if (strcmp(word, "SHOW") == 0) {
        free(word);
        word = selectWord(2, comanda);
        if (strcmp(word, "CONNECTIONS") == 0) {
            free(word);
            //printf("Show connections reconegut\n");
            scanConnections(conf->direccio, conf->port_list_inicial, conf->port_list_final, conf->port);
            free(comanda);
            return 0;
        } else if (strcmp(word, "AUDIOS") == 0) {
            free(word);
            //printf("Show audios reconegut\n");
            free(comanda);
            return 0;
        }
    } else if (strcmp(word, "CONNECT") == 0) {
        free(word);
        word = selectWord(2, comanda);
        
        if (strcmp(word, "ERROR") != 0) {
            
            int port = atoi(word);
            
            if(!port){//per si el format introduït del port és erroni
                write(1,INVALID_PORT,strlen(INVALID_PORT));
            }
            else{
                //AQuí toca fer el connect
                Trama trama = generaTrama(1, conf->name);
                if (estableixConnexio(&(*socket_client), conf->direccio, atoi(word)) < 0){
                    write(1, SOCK_ERR_SERVER, strlen(SOCK_ERR_SERVER)); return 0;
                }else{
                    write(*socket_client, &trama.type, 1);
                    write(*socket_client, trama.header, strlen(trama.header));
                    write(*socket_client, &trama.length, 2);
                    write(*socket_client, trama.data, trama.length);

                    printf("%c\n%s\n%d\n%s\n", trama.type, trama.header, trama.length, trama.data);
                }

            }
            free(word);
            //printf("Connect reconegut => port: %d\n", port);
            //CONNECTEM AMB AQUEST PORT
            free(comanda);
            return 0;
        }

    } else if (!strcmp(word, "SAY")) {
        free(word);
        char *user = selectWord(2, comanda);
        char *message = selectWord(3, comanda);
        if((strcmp(user, "ERROR")!=0) && (strcmp(message, "ERROR")!=0)){
            free(message);

            if(!readTextInput(comanda, message)){write(0, SENT_MESSAGE_ERR, strlen(SENT_MESSAGE_ERR)); free(user); return 0;}

            printf("Say reconegut => user: %s\tmissatge: '%s'\n", user, message);

            write(*socket_client, message, strlen(message));

            free(user);free(message);
            free(comanda);
            return 0;
        }

    } else if (strcmp(word, "BROADCAST") == 0) {
        free(word);
        char* message = selectWord(2, comanda);
        if(strcmp(message, "ERROR")!=0){
            free(message);
            if(!readTextInput(comanda, message)){write(0, SENT_MESSAGE_ERR, strlen(SENT_MESSAGE_ERR)); return 0;}

            //printf("Broadcast reconegut => missatge: '%s'\n", message);

            free(message);
            free(comanda);
            return 0;
        }


    } else if (strcmp(word, "DOWNLOAD") == 0) {
        char *user = selectWord(2, comanda);
        char *audio = selectWord(3, comanda);
        if((strcmp(user, "ERROR")!=0) && (strcmp(audio, "ERROR")!=0)) {

            //printf(("Donwload reconegut => usuari: %s\taudio: %s\n"), user, audio);
            free(user);free(audio);
            free(comanda);
            return 0;
        }
    } else if (strcmp(word, "EXIT") == 0) {
        free(word);
        free(comanda);
        return 1;
    }
    write(0, COMMAND_NOT_FOUND, strlen(COMMAND_NOT_FOUND));
    free(comanda);
    return 0;
}
