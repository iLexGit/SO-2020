//
// Created by root on 10/31/19.
//

#include "Options.h"




//int whichCommand(char* comanda, Conf* conf, int* socket_client) {
int whichCommand(char* comanda, Conf* conf, Connexio connexions [10]) {
    char *word = selectWord(1, comanda);
    int i =0;
    Trama Rx;
    //Trama MSGOK;
    //Connexio connexions [10]; // els 10 ports assignats



    if (strcmp(word, "SHOW") == 0) {
        free(word);
        word = selectWord(2, comanda);
        if (strcmp(word, "CONNECTIONS") == 0) {
            free(word);
            printf("Show connections reconegut\n");
            scanConnections(conf->direccio, conf->port_list_inicial, conf->port_list_final, conf->port, &connexions);
            free(comanda);
            return 0;
        } else if (strcmp(word, "AUDIOS") == 0) {
            free(word);
            char* user = selectWord(3,comanda);
            for (i=0;i<10;i++) {
                if (connexions[i].name != NULL) {
                    if (strcmp(connexions[i].name, user) == 0) {
                        Trama shaudios= generaTrama(SHAUDIO_CLI,"");
                        write(connexions[i].fd, &shaudios.type, 1);
                        write(connexions[i].fd, shaudios.header, strlen(shaudios.header));
                        write(connexions[i].fd, &shaudios.length, 2);

                        Trama Rx = llegeixTrama(connexions[i].fd);
                        write(1,Rx.data,Rx.length);
                        write(1,"\n",1);
                    }
                }
            }
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

                //if (estableixConnexio(&(*socket_client), conf->direccio, atoi(word)) < 0){
                if (estableixConnexio(connexions, conf->direccio, atoi(word)) < 0){
                    write(1, SOCK_ERR_SERVER, strlen(SOCK_ERR_SERVER)); return 0;
                }else{

                    //Connecta();

                    /*write(*socket_client, &trama.type, 1);
                    write(*socket_client, trama.header, strlen(trama.header));
                    write(*socket_client, &trama.length, 2);
                    write(*socket_client, trama.data, trama.length);*/



                    write(connexions[port%10].fd, &trama.type, 1);
                    write(connexions[port%10].fd, trama.header, strlen(trama.header));
                    write(connexions[port%10].fd, &trama.length, 2);
                    write(connexions[port%10].fd, trama.data, trama.length);





                    //sleep(1);
                    Rx = llegeixTrama(connexions[port%10].fd);


                    if (!strcmp(Rx.header,CON_SER_OK_HEADER) ){
                        connexions[port%10].name = (char*) malloc(Rx.length * sizeof(char) + 2);
                        strcpy(connexions[port%10].name,Rx.data);
                        connexions[port%10].port = port;

                    }
                    else{
                        connexions[port%10].fd = 0;
                    }

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



            for (i=0;i<10;i++){
                if (connexions[i].name != NULL){
                    if (strcmp(connexions[i].name,user)==0) {
                        Trama say = generaTrama(SAY_CLI, message);

                        write(connexions[i].fd, &say.type, 1);
                        write(connexions[i].fd, say.header, strlen(say.header));
                        write(connexions[i].fd, &say.length, 2);
                        write(connexions[i].fd, say.data, say.length);



                        Trama MSGOK = llegeixTrama(connexions[i].fd);


                        break;
                    }

                }
            }

            //write(*socket_client, message, strlen(message));

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

            for (i=0;i<10;i++) {
                if (connexions[i].name != NULL) {
                    if (strcmp(connexions[i].name, user) == 0) {

                        Trama Download = generaTrama(DOWNLOAD_CLI, audio);
                        write(connexions[i].fd, &Download.type, 1);
                        write(connexions[i].fd, Download.header, strlen(Download.header));
                        write(connexions[i].fd, &Download.length, 2);
                        write(connexions[i].fd, Download.data, Download.length);


                        Trama Fitxer = llegeixTrama(connexions[i].fd);
                        if (!strcmp(Fitxer.header,DOWNLOAD_SER_ERR_HEADER)){
                            printf("el fitxer no existeix\n");
                        }
                        else{
                            printf("el fitxer si existeix\n");
                        }

                    }
                }
            }



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
