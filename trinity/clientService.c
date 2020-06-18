//
// Created by root on 11/3/19.
//

#include "clientService.h"

void clientService(Conf* conf){
    int socket_client = -1;
    char* comanda;
    char prompt[strlen(conf->name +3)];
    sprintf(prompt, "$%s: ", conf->name);
    do{
        write(1, prompt, strlen(prompt));
        comanda = readUntil(0,'\n');
    }while(!whichCommand(comanda, conf, &socket_client));
}

int estableixConnexio(int* sockfd, char* dir, int port) {
    *sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*sockfd < 0) { write(1, SOCK_ERR_CLIENT, strlen(SOCK_ERR_CLIENT)); }
    //Struct pel socket
    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    inet_aton(dir, &s_addr.sin_addr);

    return connect(*sockfd, (void *) &s_addr, (unsigned int) sizeof(s_addr));
}