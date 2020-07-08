#include "Connecta.h"

void connectaClient(int port, Conf* conf){
    printf("estás en connexión\n");
    //connect to the port specified in the attributes of the function
    Trama trama;
    char* data;
    data = (char*)malloc(sizeof(char) * (strlen(conf->name) + 2));
    sprintf(data,"[%s]",conf->name);
    trama = generaTrama(1,data);
    //printf("%s\n",trama.data );
    //printf("ConnectaClient.c\n");
}



void connectaServer(int establised, Conf* conf){





	
}