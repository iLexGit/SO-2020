//
// Created by root on 11/3/19.
//

#include "clientService.h"

void clientService(){
    //int socket_client = -1;
    //Connexio* connexions;
    //int numConnexions = 0;
    printf("Creant thread Client MASTER \n");
    char* comanda;
    char prompt[strlen(conf.name +3)];
    sprintf(prompt, "$%s: ", conf.name);
    do{
        write(1, prompt, strlen(prompt));
        comanda = readUntil(0,'\n');
    //}while(!whichCommand(comanda, conf, &socket_client));
    }while(!whichCommand(comanda));
}

int weAreConnected( int p) {
    for (int i = 0; i < numConnexions; i++){
        if (connexions[i].port == p){
            write(1, CLIENT_ALREADY_CONNECTED, strlen(CLIENT_ALREADY_CONNECTED));
            return 1;
        }
    }
    return 0;
}


//int estableixConnexio(int* sockfd, char* dir, int port) {
int estableixConnexio( char* dir, int port) {
       /* *sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (*sockfd < 0) { write(1, SOCK_ERR_CLIENT, strlen(SOCK_ERR_CLIENT)); }
        //Struct pel socket
        struct sockaddr_in s_addr;
        memset(&s_addr, 0, sizeof(s_addr));
        s_addr.sin_family = AF_INET;
        s_addr.sin_port = htons(port);
        inet_aton(dir, &s_addr.sin_addr);

        return connect(*sockfd, (void *) &s_addr, (unsigned int) sizeof(s_addr));*/


       if(!weAreConnected(port)){
        if(numConnexions == 0){
            connexions = (Connexio*) malloc(sizeof(Connexio));
            printf("fem malloc de connexions\n");
        }

        else{
            connexions = (Connexio*) realloc(connexions,sizeof(Connexio) * (numConnexions + 1));
            printf("fem realloc de connexions\n");
        }

        connexions[numConnexions].fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        printf("kepasaaaaa\n");
        if (connexions[numConnexions].fd < 0) {
            printf("numconnexions %d\n",numConnexions);
            printf("fd %d\n", connexions[numConnexions].fd);
            write(1, SOCK_ERR_CLIENT, strlen(SOCK_ERR_CLIENT));
            return -1;
        }
        else{
            //Struct pel socket
            printf("??????\n");
            struct sockaddr_in s_addr;
            memset(&s_addr, 0, sizeof(s_addr));
            s_addr.sin_family = AF_INET;
            s_addr.sin_port = htons(port);
            inet_aton(dir, &s_addr.sin_addr);
            printf("numconnexions %d\n",numConnexions);
            printf("fd %d\n", connexions[numConnexions].fd);
            numConnexions ++;
            printf("numconnexions %d\n",numConnexions);
            printf("fd %d\n", connexions[numConnexions - 1].fd);
            return connect(connexions[numConnexions - 1].fd, (void *) &s_addr, (unsigned int) sizeof(s_addr));
        }


    }
    printf("hola\n");
    return -1;


}


/*

void* serverServiceThread(void* arg){
    Connexio connexio = (Connexio*) arg;
8.8.8.88.8    co


    serverThreadData* data = (serverThreadData*) arg;
    int* conn = &(data->conn);
    Conf* conf = data->config;
    serverServiceThread(conf, *conn);
    return (void*)1;
}
*/
