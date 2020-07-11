
#include "main.h"
#include <pthread.h>

Connexio * connexions;
int numConnexions = 0;
Conf conf;
int* srvconnfds;
int srv_numConnexions = 0;
int sockfd = 0;
int server = 0;
int client=0;




void* startClient(void* arg){
    printf("start client\n");
    clientService();
    return (void*)1;
}

void* startServer(void* arg){
    printf("start server\n");
    serverService();
    return (void*) 1;
}
static void closeProgram(int signal){
    Trama Desconnexio;
    //Trama recepcio;
    switch (signal) {

        case SIGINT:
            for (int i = 0; i < numConnexions ; ++i) {
                if (connexions[i].name != NULL){

                    Desconnexio = generaTrama(EXIT_CLI,conf.name);

                    if (write(connexions[i].fd, &Desconnexio.type, 1) != 0){
                        write(connexions[i].fd, Desconnexio.header, strlen(Desconnexio.header));
                        write(connexions[i].fd, &Desconnexio.length, 2);
                        write(connexions[i].fd, Desconnexio.data, Desconnexio.length);

                        llegeixTrama(connexions[i].fd);

                        close(connexions[i].fd);
                        printf("hem tancat connexió amb user %s\n",connexions[i].name);

                    }
                    free(connexions[i].name);

                }
            }

            for (int j = 0; j < srv_numConnexions; ++j) {
                if (srvconnfds[j] != 0){
                    printf("\n1tancat\n");
                    close(srvconnfds[j]);
                }
            }
            close (sockfd);

            free(srvconnfds);
            free(connexions);
            exit(1);

            break;
        default:
            break;

    }
}

int main(int argc, char *argv[])
{
    signal(SIGINT, closeProgram);
    write(1, STARTING_SYSTEM, strlen(STARTING_SYSTEM));

    if (argc  != 2){
        write(1,ARGC_ERROR,strlen(ARGC_ERROR));
        return -1;
    }

	int x = readConfigurationFile(argv[1]);
	if (x == -1){
		return 0;
	}
    pthread_t t_server, t_client;

	server = pthread_create(&t_server, NULL, startServer,NULL);
	if(server != 0){
	    write(1, SERVER_THREAD_ERR, strlen(SERVER_THREAD_ERR));
	    return -1;
	}
	client = pthread_create(&t_client, NULL, startClient, NULL);
    if(client != 0){
        write(1, CLIENT_THREAD_ERR, strlen(CLIENT_THREAD_ERR));
        return -1;

    }

    pthread_join(t_client, NULL);
    printf("[CLIENT] Thread closed\n");

    pthread_join(t_server, NULL);
    printf("[SERVER] Thread closed\n");

    printf("Exiting main...\n");

	return 0;
}