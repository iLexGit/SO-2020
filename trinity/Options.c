//
// Created by root on 10/31/19.
//

#include "Options.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* threadBroadcastRead(void* arg){
    int i = (int)arg;
    llegeixTrama(connexions[i].fd);
    char* String = (char*)malloc(sizeof(char)*(strlen("[] Cool!\n")+strlen(connexions[i].name)+1));
    sprintf(String,"[%s] Cool!\n", connexions[i].name);

    pthread_mutex_lock(&mutex);
    printf("Thread broadcast wait per => %s", connexions[i].name);
    write(1, String, strlen(String));
    pthread_mutex_unlock(&mutex);

    return (void*)1;
}



int whichCommand(char* comanda) {
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
            scanConnections(conf.port_list_inicial, conf.port_list_final, conf.port);
            free(comanda);
            return 0;
        } else if (strcmp(word, "AUDIOS") == 0) {
            free(word);
            char* user = selectWord(3,comanda);
            for (i=0;i<numConnexions;i++) {
                if (connexions[i].name != NULL) {
                    if (strcmp(connexions[i].name, user) == 0) {
                        Trama shaudios= generaTrama(SHAUDIO_CLI,"");
                        write(connexions[i].fd, &shaudios.type, 1);
                        write(connexions[i].fd, shaudios.header, strlen(shaudios.header));
                        if(!PIPE_SIGNAL){
                            write(connexions[i].fd, &shaudios.length, 2);

                            /*shaudios.header = (char*) realloc(shaudios.header,0);
                            shaudios.data = (char*) realloc(shaudios.data,0);
                            free(shaudios.header);
                            free(shaudios.data);*/


                            Trama Rx = llegeixTrama(connexions[i].fd);
                            printf("trama sh audios rebuda\n");
                            printf("header %s  data %s\n", Rx.header, Rx.data);
                            write(1, Rx.data, Rx.length);
                            write(1, "\n", 1);
                        }
                        else{
                            PIPE_SIGNAL = 0;
                            char* text = (char*)malloc((strlen(connexions[i].name) + strlen("l'usuari  ja no està connectat\n")) * sizeof(char) + 1);

                            sprintf(text,"l'usuari %s ja no està connectat\n",connexions[i].name);
                            write(1,text,strlen(text));
                            free(connexions[i].name);
                            connexions[i].fd = 0;
                            connexions[i].port = 0;
                            free(text);
                        }
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

                if (port == conf.port){
                    printf("no et pots connectar a tu mateix\n");
                }
                else{
                    Trama trama = generaTrama(1, conf.name);


                    if (estableixConnexio(conf.direccio, atoi(word)) < 0){
                        write(1, SOCK_ERR_SERVER, strlen(SOCK_ERR_SERVER)); return 0;
                    }else{

                        //Connecta();

                        /*write(*socket_client, &trama.type, 1);
                        write(*socket_client, trama.header, strlen(trama.header));
                        write(*socket_client, &trama.length, 2);
                        write(*socket_client, trama.data, trama.length);*/



                        write(connexions[numConnexions - 1].fd, &trama.type, 1);
                        write(connexions[numConnexions - 1].fd, trama.header, strlen(trama.header));
                        write(connexions[numConnexions - 1].fd, &trama.length, 2);
                        write(connexions[numConnexions - 1].fd, trama.data, trama.length);

                        trama.header = (char*) realloc(trama.header,0);
                        trama.data = (char*) realloc(trama.data,0);
                        free(trama.header);
                        free(trama.data);





                        //sleep(1);
                        Rx = llegeixTrama(connexions[numConnexions - 1].fd);


                        if (!strcmp(Rx.header,CON_SER_OK_HEADER) ){
                            connexions[numConnexions - 1].name = (char*) malloc(Rx.length * sizeof(char) + 2);
                            strcpy(connexions[numConnexions - 1].name,Rx.data);
                            connexions[numConnexions - 1].port = port;

                        }
                        else{
                            connexions[numConnexions - 1].fd = 0;
                            numConnexions--;
                        }

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
        printf("options.c message %s\n",message);
        printf("options.c user %s\n",user);
        if((strcmp(user, "ERROR")!=0) && (strcmp(message, "ERROR")!=0)){

            printf("\n");
            //free(message);
            if(!readTextInput(comanda, message)){write(0, SENT_MESSAGE_ERR, strlen(SENT_MESSAGE_ERR)); free(user); return 0;}

            char* missatge = extreuMissatge(comanda);
            if(strcmp(missatge, "ERROR") == 0){write(0, SENT_MESSAGE_ERR, strlen(SENT_MESSAGE_ERR)); free(user); return 0;}

            printf("SAY reconegut => missatge: '%s'\n", missatge);
            for (i=0;i<numConnexions;i++){
                if (connexions[i].name != NULL){
                    if (strcmp(connexions[i].name,user)==0) {
                        printf("options.c message %s\n",missatge);
                        printf("el file descriptor es %d\n",connexions[i].fd);
                        Trama say = generaTrama(SAY_CLI, missatge);

                        write(connexions[i].fd, &say.type, 1);
                        write(connexions[i].fd, say.header, strlen(say.header));
                        printf("El write ens ha deixat PIPE_SIGNAL a %d\n", PIPE_SIGNAL);
                        if (!PIPE_SIGNAL){

                            write(connexions[i].fd, &say.length, 2);
                            write(connexions[i].fd, say.data, say.length);

                            say.header = (char*) realloc(say.header,0);
                            say.data = (char*) realloc(say.data,0);
                            free(say.header);
                            free(say.data);

                            //Trama MSGOK =
                            llegeixTrama(connexions[i].fd);
                        }
                        else{
                            PIPE_SIGNAL=0;
                            /*char* text;// = (char*)malloc((strlen(connexions[i].name) + strlen("l'usuari  ja no està connectat\n")) * sizeof(char) + 1);

                            sprintf(text,"l'usuari %s ja no està connectat\n",connexions[i].name);
                            write(1,text,strlen(text));*/
                            printf("l'usuari %s ja no està connectat\n",connexions[i].name);
                            free(connexions[i].name);
                            connexions[i].fd = 0;
                            connexions[i].port = 0;
                            //free(text);
                        }
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
            //free(message);
            if(!readTextInput(comanda, message)){write(0, SENT_MESSAGE_ERR, strlen(SENT_MESSAGE_ERR)); return 0;}

            char* missatge = extreuMissatge(comanda);
            if(strcmp(missatge, "ERROR") == 0){write(0, SENT_MESSAGE_ERR, strlen(SENT_MESSAGE_ERR)); return 0;}

            printf("BROADCAST reconegut => missatge: '%s'\n", missatge);

            Trama broadcast = generaTrama(BROAD_CLI, missatge);
            for (int i = 0; i < numConnexions; i++){
                if (connexions[i].name != NULL) {
                    //if de comprovació de canal obert
                    write(connexions[i].fd, &broadcast.type, 1);
                    write(connexions[i].fd, broadcast.header, strlen(broadcast.header));
                    printf("El write ens ha deixat PIPE_SIGNAL a %d\n", PIPE_SIGNAL);
                    if (!PIPE_SIGNAL) {
                        write(connexions[i].fd, &broadcast.length, 2);
                        write(connexions[i].fd, broadcast.data, broadcast.length);
                    }else{
                        PIPE_SIGNAL=0;
                        /*char* text;// = (char*)malloc((strlen(connexions[i].name) + strlen("l'usuari  ja no està connectat\n")) * sizeof(char) + 1);

                        sprintf(text,"l'usuari %s ja no està connectat\n",connexions[i].name);
                        write(1,text,strlen(text));*/
                        printf("l'usuari %s ja no està connectat\n",connexions[i].name);
                        free(connexions[i].name);
                        connexions[i].fd = 0;
                        connexions[i].port = 0;
                        //free(text);
                    }

                    pthread_t thread_broadcast;
                    pthread_create(&thread_broadcast, NULL, threadBroadcastRead, i);
                }
            }

            free(missatge);
            free(message);
            free(comanda);
            return 0;
        }


    } else if (strcmp(word, "DOWNLOAD") == 0) {
        char *user = selectWord(2, comanda);
        char *audio = selectWord(3, comanda);
        int fd;
        char * path;
        char * sum;


        /*char* test = checksum("../Audios1/uni");*/
        if((strcmp(user, "ERROR")!=0) && (strcmp(audio, "ERROR")!=0)) {

            for (i=0;i<numConnexions;i++) {
                if (connexions[i].name != NULL) {
                    if (strcmp(connexions[i].name, user) == 0) {

                        Trama Download = generaTrama(DOWNLOAD_CLI, audio);
                        write(connexions[i].fd, &Download.type, 1);
                        write(connexions[i].fd, Download.header, strlen(Download.header));
                        if(!PIPE_SIGNAL){
                            write(connexions[i].fd, &Download.length, 2);
                            write(connexions[i].fd, Download.data, Download.length);

                            Download.header = (char*) realloc(Download.header,0);
                            Download.data = (char*) realloc(Download.data,0);
                            free(Download.header);
                            free(Download.data);

                            Trama Fitxer = llegeixTrama(connexions[i].fd);
                            if (!strcmp(Fitxer.header,DOWNLOAD_SER_ERR_HEADER)){
                                printf("el fitxer no existeix\n");
                            }
                            else{
                                //printf("el fitxer si existeix\n");

                                //path = (char*) malloc(sizeof("../Audios2") + sizeof(audio) + 1);
                                //sprintf(path,"../Audios1/%s",audio);
                                //fd = open(path, O_WRONLY | O_CREAT);

                                path = (char*) malloc(sizeof(conf.audio_folder) + sizeof(audio) + 1);
                                sprintf(path,"%s/%s",conf.audio_folder,audio);
                                printf("%s\n",path);
                                fd = open(path, O_WRONLY | O_CREAT, 0755);

                                if (fd < 0) {
                                    write(1, FILE_NOT_FOUND_ERR, strlen(FILE_NOT_FOUND_ERR));
                                }
                                else{
                                    while(strcmp(Fitxer.header,DOWNLOAD_SER_EOF_HEADER)){
                                        printf("header %s data %s\n",Fitxer.header,Fitxer.data);
                                        write(fd,Fitxer.data,Fitxer.length);
                                        Fitxer = llegeixTrama(connexions[i].fd);

                                    }
                                    printf("EOF---> %s\n",Fitxer.data);



                                    close(fd);

                                    sum = checksum(path);

                                    if(strcmp(sum,Fitxer.data)){
                                        remove(path);
                                        printf("esborrat\n");
                                    }



                                }



                            }
                        } else{
                            PIPE_SIGNAL = 0;
                            char* text = (char*)malloc((strlen(connexions[i].name) + strlen("l'usuari  ja no està connectat\n")) * sizeof(char) + 1);

                            sprintf(text,"l'usuari %s ja no està connectat\n",connexions[i].name);
                            write(1,text,strlen(text));
                            free(connexions[i].name);
                            connexions[i].fd = 0;
                            connexions[i].port = 0;
                            free(text);
                        }

                    }
                }
            }



            free(user);free(audio);
            free(comanda);

            //if(sum != NULL){free (sum);}
            //if (path != NULL){free(path);}

            return 0;
        }
    } else if (strcmp(word, "EXIT") == 0) {
        printf("Desconnextant...\n");


        free(word);
        free(comanda);

        raise(SIGINT);
        return 1;
    }
    write(0, COMMAND_NOT_FOUND, strlen(COMMAND_NOT_FOUND));
    free(comanda);
    return 0;
}
