
#include "main.h"

void* startClient(void* arg){
    //printf("THREAD PER GENERAL EL PROCÉS DE CLIENT\n");
    Conf* conf = (Conf*) arg;
    clientService(conf);
    //FREE's
    return (void*)1;
}

void* startServer(void* arg){
    //printf("THREAD PER A GENERAR EL PROCÉS DE SERVIDOR\n");
    Conf* conf = (Conf*) arg;
    serverService(conf);
    return (void*) conf;
}


int main(int argc, char *argv[])
{

    write(1, STARTING_SYSTEM, strlen(STARTING_SYSTEM));

    if (argc  != 2){
        write(1,ARGC_ERROR,strlen(ARGC_ERROR));
        return -1;
    }
	Conf conf;
	int x = readConfigurationFile(argv[1],&conf);
	if (x == -1){
		return 0;
	}

    //printf("%s\n",conf.name );
    //printf("%s\n",conf.audio_folder);
    //printf("%s\n",conf.IPaddress );
    //printf("%d\n",conf.port );
    //printf("%s\n",conf.direccio );
    //printf("%d\n",conf.port_list_inicial);
    //printf("%d\n",conf.port_list_final);*/

    pthread_t t_server, t_client;

	int server = pthread_create(&t_server, NULL, startServer, &conf);
	if(server != 0){
	    write(1, SERVER_THREAD_ERR, strlen(SERVER_THREAD_ERR));
	    return -1;
	}
	int client = pthread_create(&t_client, NULL, startClient, &conf);
    if(client != 0){
        write(1, CLIENT_THREAD_ERR, strlen(CLIENT_THREAD_ERR));
        return -1;

    }

    pthread_join(t_client, NULL);
    printf("[CLIENT] Thread closed\n");

    pthread_join(t_server, NULL);
    printf("[SERVER] Thread closed\n");

    printf("Exiting main...\n");

    //FREE de conf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //free(&conf);
	return 0;
}