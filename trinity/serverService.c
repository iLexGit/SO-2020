//
// Created by root on 11/3/19.
//

#include <dirent.h>
#include "serverService.h"
#include "GestorMissatge.h"


void* serverServiceThread(void* arg){
    serverThreadData* data = (serverThreadData*)arg;

    char* Rx_data = data->rx_data;
    int conn = data->conn;

    char *String;
    Trama recepcio;
    printf("buenosdias\n");

    printf("no hem descartat\n");

    printf("eyaaaaaaaa\n");

    Trama tx = generaTrama(CON_SER_OK, conf.name);
    write(srvconnfds[conn], &tx.type, 1);
    write(srvconnfds[conn], tx.header, strlen(CON_SER_OK_HEADER));
    write(srvconnfds[conn], &tx.length, 2);
    write(srvconnfds[conn], tx.data, tx.length);

    printf("%c\n%s\n%d\n%s\n", tx.type, tx.header, tx.length, tx.data);



//    if(strcmp(Rx.header, ""))
//    char* trama = generaTrama(CON_SER)
//    write(conn, "Hola\n", strlen("Hola"));
//    printf("%s\t%d\n",conf.name, conn);
//    //tramaStruct rx
    while(1){
        printf("abans llegeixtrama\n");

        /*recepcio.header = (char*) realloc(recepcio.header,0);
        recepcio.data = (char*) realloc(recepcio.data,0);
        free(recepcio.header);
        free(recepcio.data);*/

        recepcio = llegeixTrama(srvconnfds[conn]);
        printf("despres llegeixtrama type es %c\n",recepcio.type);
        //printf("%c\n%s\n%d\n%s\n", recepcio.type, recepcio.header, recepcio.length, recepcio.data);
        switch(recepcio.type - '0') {
            case 1:

                break;

            case 2:
                //printf("%s     %s-\n",Rx.data,recepcio.data);
                String = (char *) malloc(sizeof(char) * (5 + strlen(Rx_data) + strlen(recepcio.data)));
                sprintf(String, "[%s]:\t%s\n", Rx_data, recepcio.data);
                write(1, String, strlen(String));
                Trama Tx = generaTrama(SAY_SER, "");
                //printf("%c\n%s\n%d\n%s\n", Tx.type, Tx.header, Tx.length, Tx.data);
                write(srvconnfds[conn], &Tx.type, 1);
                write(srvconnfds[conn], Tx.header, strlen(CON_SER_SAY_HEADER));
                write(srvconnfds[conn], &Tx.length, 2);
                //write(conn, Tx.data, tx.length);

                break;


            case 3: {
                String = (char *) malloc(sizeof(char) * (5 + strlen(Rx_data) + strlen(recepcio.data)));
                sprintf(String, "[%s]:\t%s\n", Rx_data, recepcio.data);
                write(1, String, strlen(String));

                Trama Cool = generaTrama(BROAD_SER, "");

                write(srvconnfds[conn], &Cool.type, 1);
                write(srvconnfds[conn], Cool.header, strlen(BROAD_SER_HEADER));
                write(srvconnfds[conn], &Cool.length, 2);
                break;
            }

            case 4: {
                Trama AudioList;
                int i =0;
                char* List = (char*) malloc(sizeof(char));
                strcpy(List,"\n");
                struct dirent *de;  // Pointer for directory entry

                // opendir() returns a pointer of DIR type.
                //DIR *dr = opendir("../Audios1");
                DIR *dr = opendir(conf.audio_folder);

                if (dr == NULL)  // opendir returns NULL if couldn't open directory
                {
                    printf("Could not open current directory\n" );
                    break;
                    //return 0;
                }else {

                    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
                    // for readdir()
                    while ((de = readdir(dr)) != NULL) {
                        if (i >= 2){
                            //printf("%s\n", de->d_name);
                            List = (char *) realloc(List, sizeof(List) + sizeof(de->d_name) + 1);
                            sprintf(List, "%s%s\n", List, de->d_name);
                        }
                        i++;
                    }
                    closedir(dr);
                    List[strlen(List)-1] = '\0';

                    for(int x=1; x <= (int)(strlen(List));x++){
                        List[x-1]=List[x];
                    }
                    printf("%s\n",List);
                    AudioList = generaTrama(SHAUDIO_SER,List);
                    write(srvconnfds[conn], &AudioList.type, 1);
                    write(srvconnfds[conn], AudioList.header, strlen(SHAUDIO_SER_HEADER));
                    write(srvconnfds[conn], &AudioList.length, 2);
                    write(srvconnfds[conn], AudioList.data, AudioList.length);
                    printf("trama show audios enviada\n");
                    break;
                }
            }

            case 5: {

                printf("Rebut %s %s\n", recepcio.header, recepcio.data);

                struct dirent *de;  // Pointer for directory entry
                //DIR *dr = opendir("../Audios1");
                DIR *dr = opendir(conf.audio_folder);
                int i = 0;
                int existeix = 0;
                Trama Resposta;
                int fd=-1;
                char* path;
                int endofile = 0;
                char* lectura;
                char caracter;
                int j =0;

                if (dr == NULL)  // opendir returns NULL if couldn't open directory
                {
                    printf("Could not open current directory\n" );
                    //return 0;
                }else {

                    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
                    // for readdir()
                    while ((de = readdir(dr)) != NULL && !existeix) {
                        if (i >= 2) {
                            if (!strcmp(de->d_name, recepcio.data)) {
                                existeix = 1;

                            }
                        }


                        i++;
                    }
                    if (existeix){


                        //path = (char*) malloc(sizeof("../Audios1") + sizeof(recepcio.data) + 1);
                        //sprintf(path,"../Audios1/%s",recepcio.data);
                        //fd = open(path, O_RDONLY);

                        path = (char*) malloc(sizeof(conf.audio_folder) + sizeof(recepcio.data) + 1);
                        sprintf(path,"%s/%s",conf.audio_folder,recepcio.data);
                        printf("%s\n",path);
                        fd = open(path, O_RDONLY);

                        if (fd < 0) {
                            write(1, FILE_NOT_FOUND_ERR, strlen(FILE_NOT_FOUND_ERR));
                            endofile = 1;
                        }
                        else{

                            while (!endofile){

                                if (read(fd,&caracter,1) == 0){
                                    endofile = 1;
                                }
                                if (!endofile && j<20){
                                    if (lectura == NULL){
                                        lectura = (char*) malloc(1);
                                    }else{
                                        lectura = (char*) realloc(lectura,sizeof(lectura) + sizeof(char));
                                    }
                                    lectura[j] = caracter;
                                    j++;
                                    printf("Lectura : %s\n",lectura);
                                    printf("j : %d\n",j);

                                }
                                if (j == 20){
                                    Resposta = generaTramaAudio(lectura,j);
                                    write(srvconnfds[conn], &Resposta.type, 1);
                                    write(srvconnfds[conn], Resposta.header, strlen(DOWNLOAD_SER_DATA_HEADER));
                                    write(srvconnfds[conn], &Resposta.length, 2);
                                    write(srvconnfds[conn], Resposta.data, Resposta.length);
                                    j = 0;

                                    lectura = (char*) realloc(lectura,0);
                                    /*Resposta.header = (char*) realloc(Resposta.header,0);
                                    Resposta.data = (char*) realloc(Resposta.data,0);
                                    free(Resposta.header);
                                    free(Resposta.data);*/
                                }

                            }

                            if(lectura != NULL){
                                //Resposta = generaTrama(DOWNLOAD_SER_DATA,lectura);
                                Resposta = generaTramaAudio(lectura,j);
                                write(srvconnfds[conn], &Resposta.type, 1);
                                write(srvconnfds[conn], Resposta.header, strlen(DOWNLOAD_SER_DATA_HEADER));
                                write(srvconnfds[conn], &Resposta.length, 2);
                                printf("%s\n",Resposta.data);
                                if(Resposta.length > 0){write(conn, Resposta.data, Resposta.length);}
                                lectura = (char*) realloc(lectura,0);

                                /*Resposta.header = (char*) realloc(Resposta.header,0);
                                Resposta.data = (char*) realloc(Resposta.data,0);
                                free(Resposta.header);
                                free(Resposta.data);*/

                            }
                            free(lectura);


                            char* sum = checksum(path);
                            printf("suuuuuuuuuum   %s\n",sum);
                            Resposta = generaTrama(DOWNLOAD_SER_EOF,sum);
                            printf("akiiiii\n");
                            write(srvconnfds[conn], &Resposta.type, 1);
                            write(srvconnfds[conn], Resposta.header, strlen(DOWNLOAD_SER_EOF_HEADER));
                            write(srvconnfds[conn], &Resposta.length, 2);
                            write(srvconnfds[conn], Resposta.data, Resposta.length);

                            /*Resposta.header = (char*) realloc(Resposta.header,0);
                            Resposta.data = (char*) realloc(Resposta.data,0);
                            free(Resposta.header);
                            free(Resposta.data);*/


                            close(fd);
                        }

                    }
                    else{
                        Resposta = generaTrama(DOWNLOAD_SER_ERR,"");
                        write(srvconnfds[conn], &Resposta.type, 1);
                        write(srvconnfds[conn], Resposta.header, strlen(DOWNLOAD_SER_ERR_HEADER));
                        write(srvconnfds[conn], &Resposta.length, 2);
                        write(srvconnfds[conn], Resposta.data, Resposta.length);

                        /*Resposta.header = (char*) realloc(Resposta.header,0);
                        Resposta.data = (char*) realloc(Resposta.data,0);
                        free(Resposta.header);
                        free(Resposta.data);*/
                    }


                    closedir(dr);
                    free(lectura);


                    break;
                }
                break;
            }

            case 6: {
                Trama Resposta = generaTrama(EXIT_SER_OK, "");
                write(srvconnfds[conn], &Resposta.type, 1);
                write(srvconnfds[conn], Resposta.header, strlen(DOWNLOAD_SER_ERR_HEADER));
                write(srvconnfds[conn], &Resposta.length, 2);
                write(srvconnfds[conn], Resposta.data, Resposta.length);

                close(srvconnfds[conn]);
                return (void*)1;

                break;
            }
        }
    }
}



int serverService(){
    //Creem el socket

    printf("Creant thread servidor MASTER\n");
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0){write(1, SOCK_ERR_SERVER, strlen(SOCK_ERR_SERVER)); return -1;}

    //Struct pel socket
    struct sockaddr_in s_addr;
    memset (&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(conf.port);
    inet_aton(conf.IPaddress, &s_addr.sin_addr);

    printf("%s\n", conf.IPaddress);
    //Fem el bind
    if (bind(sockfd, (void*)&s_addr, sizeof(s_addr)) < 0){
        write(1, BIND_ERR, strlen(BIND_ERR));
        return -1;
    }

    //Convertim el socket en passiu
    listen (sockfd, BACKLOG);
    printf("[SERVER] esperant connexió\n");

    //pthread_t* clients = (pthread_t*)malloc(sizeof(pthread_t));
    pthread_t clients;
    srvconnfds = (int*) malloc(sizeof(int));

    //Fem el accept
    while(1){

        srvconnfds[srv_numConnexions] = accept (sockfd, NULL, NULL);
        printf("el fd val %d\n",srvconnfds[numConnexions]);


        if (srvconnfds[srv_numConnexions]<0){
            //Trama Error = generaTrama(CON_SER_KO, "");
            //write(sockfd, &Error.type, 1);
            //write(sockfd, Error.header, strlen(CON_SER_KO_HEADER));
            //write(sockfd, &Error.length, 2);
            //write(sockfd, Error.data, Error.length);
            write(1, CONN_ERR_SERVER, strlen(CONN_ERR_SERVER));
            //return -1;

        }else{
            serverThreadData data;
            printf("abans llegeix trama i conn = %d\n",srvconnfds[srv_numConnexions]);
            Trama Rx = llegeixTrama(srvconnfds[srv_numConnexions]);
            printf("comprovacio si es connect del show connections\n");
            //printf("%c\n%s\n%d\n%s\n", Rx.type, Rx.header, Rx.length, Rx.data);
            if (Rx.type < '0' || Rx.type > '6'){
                printf("hem descartat\n");
            } else {
                //crear thread
                data.conn = srv_numConnexions;
                data.rx_data = Rx.data;
                int client = pthread_create(&clients, NULL, serverServiceThread, (void*)&data);
                if (client != 0) { write(1, CONN_THREAD_ERR, strlen(CONN_THREAD_ERR)); }
                else {
                    srvconnfds = (int *) realloc(srvconnfds, sizeof(int) * (srv_numConnexions + 1));
                    srv_numConnexions++;
                    printf("else d crear thread\n");
                }
            }
        }
    }

    return 0;
}

