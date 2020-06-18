//
// Created by root on 11/1/19.
//

#include "showConnections.h"
#define ERRPipe "Error en crear la pipe\n"

int checkDomain(char* domain, struct in_addr* address){
    if (!inet_aton(domain, address)){
        struct hostent *host = gethostbyname (domain);
        if(host!=NULL){
            bcopy (host->h_addr, &address->s_addr, host->h_length);
            return 1;
        }
        return 0;
    }
    return 1;
}



void scanConnections (char* domain, int start , int end, int self){
    printf("Procedim a escanejar adreça %s tot els ports del rang %d => %d\n", domain, start, end);
    //char* puertos[2];
    int pfd[2];
    char* return_hijo;
    self++;
    char portInicial[5];
    char portFinal[5];

    sprintf(portInicial,"%d",start);
    sprintf(portFinal,"%d",end);


    if (pipe (pfd) < 0){
        write(1,ERRPipe,strlen(ERRPipe));
        
    }
    switch (fork()){
        case -1:
            printf("errorsito\n");
        break;
        case 0: //fill
            
            
            printf("soc el fill i acabo de enxier\n");
            dup2 (pfd[1],1);
            
            execl("./show_connections.sh","",portInicial,portFinal,NULL);
            //free(atoi_start); free(atoi_end);
            //write(1,"soc el fill i ara moriré\n",strlen("soc el fill i ara moriré\n"));
            //printf("END OF PIPE\n");

            exit(0);

        break;

        default: // pare
            
            wait(NULL);
            close(pfd[1]);
            printf("soc el pare i ara escriure\n");
            
            while(1){
                return_hijo = readUntil(pfd[0],'\n');
                if(!strcmp(return_hijo,"EOF")){
                    break;
                }
                write(1,return_hijo,strlen(return_hijo));
                write(1,"\n",1);

            }
            //read(pfd[0],return_hijo,strlen("soc el fill i ara moriré\n"));
            close(pfd[0]);
            

        break;
    }
    

}



/*
void scanConnections (char* domain, int start , int end, int self){
    char port[5];
    printf("Procedim a escanejar adreça %s tot els ports del rang %d => %d\n", domain, start, end);
    int sockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0){write(1, SOCK_ERR_CLIENT, strlen(SOCK_ERR_CLIENT));}
    else {
        struct sockaddr_in s_addr;
        memset (&s_addr, 0, sizeof (s_addr));
        s_addr.sin_family = AF_INET;
        if(!checkDomain(domain, &s_addr.sin_addr)){
            write(1, DOMAIN_ERR, strlen(DOMAIN_ERR));
        }else {
            for (int i = start; i <= end; i++) {
                if (i != self) {
                    s_addr.sin_port = htons(i);
                    if (connect (sockfd, (void *) &s_addr, sizeof (s_addr)) >= 0){                        
                        sprintf(port, "%d\n", i);
                        write(1, port, strlen(port));
                        close(sockfd);
                    }else{printf("Port %d => Tancat\n", i);}
                }else{printf("Port %d => Self, not tested\n", i);}
            }
        }
    }
}
*/