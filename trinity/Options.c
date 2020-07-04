//
// Created by root on 10/31/19.
//

#include "Options.h"




//int whichCommand(char* comanda, Conf* conf, int* socket_client) {
int whichCommand(char* comanda, Conf* conf, Connexio* connexions) {
    char *word = selectWord(1, comanda);
    int i =0;
    //Connexio connexions [10]; // els 10 ports assignats



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
                printf("abans generatrama\n");
                Trama trama = generaTrama(1, conf->name);
                printf("despresgeneratrama\n");
                //if (estableixConnexio(&(*socket_client), conf->direccio, atoi(word)) < 0){
                if (estableixConnexio(connexions, conf->direccio, atoi(word)) < 0){
                    write(1, SOCK_ERR_SERVER, strlen(SOCK_ERR_SERVER)); return 0;
                }else{

                    //Connecta();

                    /*write(*socket_client, &trama.type, 1);
                    write(*socket_client, trama.header, strlen(trama.header));
                    write(*socket_client, &trama.length, 2);
                    write(*socket_client, trama.data, trama.length);*/

                    printf("filedescriptor es %d\n",connexions[4].fd);

                    write(connexions[port%10].fd, &trama.type, 1);
                    write(connexions[port%10].fd, trama.header, strlen(trama.header));
                    write(connexions[port%10].fd, &trama.length, 2);
                    write(connexions[port%10].fd, trama.data, trama.length);


                    printf("%c\n%s\n%d\n%s\n", trama.type, trama.header, trama.length, trama.data);

                    sleep(1);
                    Trama Rx = llegeixTrama(connexions[port%10].fd);
                    printf("%c\n%s\n%d\n%s\n", Rx.type, Rx.header, Rx.length, Rx.data);

                    if (!strcmp(Rx.header,CON_SER_OK_HEADER) ){
                        connexions[port%10].name = (char*) malloc(Rx.length * sizeof(char) + 1);
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

            printf("Say reconegut => user: %s\tmissatge: '%s'\n", user, message);

            for (i=4;i<10;i++){
                if (strcmp(connexions[i].name,user)==0){
                    Trama say = generaTrama(SAY_CLI, message);

                    write(connexions[i].fd, &say.type, 1);
                    write(connexions[i].fd, say.header, strlen(say.header));
                    write(connexions[i].fd, say.length, 2);
                    write(connexions[i].fd, say.data, say.length);



                    printf("%c\n%s\n%d\n%s\n", say.type, say.header, say.length, say.data);

                    break;

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
