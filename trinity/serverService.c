//
// Created by root on 11/3/19.
//

#include "serverService.h"

void* serverServiceThread_aux(void* arg){
    //Conf* conf = (Conf*) arg;
    //int* conn = (int*)arg;
    serverThreadData* data = (serverThreadData*) arg;
    int* conn = &(data->conn);
    Conf* conf = data->config;
    serverServiceThread(conf, *conn);
    return (void*)1;
}

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
    serverThreadData data;
    //Fem el accept
    while(1){

        int connection = accept (sockfd, NULL, NULL);

        if (connection<0){
                Trama Error = generaTrama(CON_SER_KO, "");
                write(sockfd, &Error.type, 1);
                write(sockfd, Error.header, strlen(CON_SER_KO_HEADER));
                write(sockfd, &Error.length, 2);
                write(sockfd, Error.data, Error.length);
                write(1, CONN_ERR_SERVER, strlen(CONN_ERR_SERVER));
                //return -1;

        }else{
            printf("Connect OK\t%d\n", connection);

            //crear thread
            //connectaServer(1, conf)
            clients = (pthread_t*)realloc(clients, sizeof(clients)+sizeof(pthread_t));
            data.config = conf;
            data.conn = connection;
            int client = pthread_create(&clients[client_num],NULL, serverServiceThread_aux, &data);
            if(client != 0){write(1, CONN_THREAD_ERR, strlen(CONN_THREAD_ERR));}
            else{client_num++;}
        }
    }

    return 0;
}

void serverServiceThread(Conf* conf, int conn){
    Trama Rx = llegeixTrama(conn);
    printf("%c\n%s\n%d\n%s\n", Rx.type, Rx.header, Rx.length, Rx.data);


    printf("eyaaaaaaaa\n");

    Trama tx = generaTrama(CON_SER_OK, conf->name);
    write(conn, &tx.type, 1);
    write(conn, tx.header, strlen(CON_SER_OK_HEADER));
    write(conn, &tx.length, 2);
    write(conn, tx.data, tx.length);

    printf("%c\n%s\n%d\n%s\n", tx.type, tx.header, tx.length, tx.data);



//    if(strcmp(Rx.header, ""))
//    char* trama = generaTrama(CON_SER)
//    write(conn, "Hola\n", strlen("Hola"));
//    printf("%s\t%d\n",conf->name, conn);
//    //tramaStruct rx
    while(1){
        printf("abans llegeixtrama\n");
        Trama recepcio = llegeixTrama(conn);
        printf("despres llegeixtrama\n");
        printf("%c\n%s\n%d\n%s\n", recepcio.type, recepcio.header, recepcio.length, recepcio.data);
        switch(atoi(Rx.type)){
            case 1:

                break;
            case 2:
                printf("%s     %s-\n",Rx.data,recepcio.data);


        }
    }
}
