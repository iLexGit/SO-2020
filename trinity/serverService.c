//
// Created by root on 11/3/19.
//

#include "serverService.h"

int serverService(Conf* conf){
    //Creem el socket
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0){write(1, SOCK_ERR_SERVER, strlen(SOCK_ERR_SERVER)); return -1;}

    //Struct pel socket
    struct sockaddr_in s_addr;
    memset (&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(conf->port);
    inet_aton(conf->IPaddress, &s_addr.sin_addr);

    printf("%s\n", conf->IPaddress);
    //Fem el bind
    if (bind(sockfd, (void*)&s_addr, sizeof(s_addr)) < 0){
        write(1, BIND_ERR, strlen(BIND_ERR));
        return -1;
    }

    //Convertim el socket en passiu
    listen (sockfd, BACKLOG);
    printf("[SERVER] esperant connexió\n");

    pthread_t* clients = (pthread_t*)malloc(sizeof(pthread_t));
    int client_num=0;
    //Fem el accept
    while(1){


        int connection = accept (sockfd, (void*) &s_addr, (unsigned int*)sizeof(s_addr));
            if (connection<0){
                //write(1, CONN_ERR_SERVER, strlen(CONN_ERR_SERVER));
                //return -1;

            }else{
                //crear thread
                //connectaServer(1, conf);
                client_num++;
                clients = (pthread_t*)realloc(clients, sizeof(clients)+sizeof(pthread_t));
                //int client = pthread_create(&clients[client_num],NULL, clientConnection);
                //if(clients[client_num] != 0){write(1, CONN_THREAD_ERR, strlen(CONN_THREAD_ERR));}
                //else{gestionaClient();}
            }
        }

    return 0;
}