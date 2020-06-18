#include "Connecta.h"

void connectaClient(int port, Conf* conf){
    printf("estás en connexión\n");
    //connect to the port specified in the attributes of the function
    char* trama;
    char* data;
    data = (char*)malloc(sizeof(char) * (strlen(conf->name) + 2));
    sprintf(data,"[%s]",conf->name);
    trama = generaTrama(CON_CLI,data);
    printf("%s\n",trama );
}



void connectaServer(int establised, Conf* conf){





	
}