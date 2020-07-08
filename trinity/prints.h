//
// Created by root on 10/31/19.
//

#ifndef PRACTICA_SO_PRINTS_H
#define PRACTICA_SO_PRINTS_H

//Constants

#define BACKLOG 1

//Prints

#define FILE_NOT_FOUND_ERR "[SYSTEM_ERROR] No s'ha pogut obrir el fitxer de configuració\n"

#define ARGC_ERROR "[SYSTEM_ERROR] No s'han passat el nombre correcte de arguments\n"

#define SERVER_THREAD_ERR "[SERVER_ERROR] No s'ha pogut generar el procés de servidor\n"

#define CLIENT_THREAD_ERR "[CLIENT_ERROR] No s'ha pogut generar el procés de client\n"

#define COMMAND_NOT_FOUND "[CLIENT_ERROR] No s'ha reconegut la comanda introduïda\n"

#define SENT_MESSAGE_ERR "[CLIENT_ERROR] El format del missatge no és correcte\n"

#define SOCK_ERR_CLIENT "[CLIENT_ERROR] No s'ha pogut crear el socket\n"

#define SOCK_ERR_SERVER "[SERVER_ERROR] No s'ha pogut crear el socket\n"

#define BIND_ERR "[SERVER_ERROR] No s'ha pogut fer el bind\n"

#define DOMAIN_ERR "[CLIENT_ERROR] No s'ha trobat el domini IP especificat\n"

#define CONN_ERR_SERVER "[SERVER_ERROR] No s'ha pogut fer el accept del connect\n"

#define CONN_THREAD_ERR "[SERVER_ERROR] No s'ha pogut crear un thread pel client que vol connectar-se\n"

#define STARTING_SYSTEM "\n\nStarting Trinity...\n\n"

#define INVALID_PORT "El port és invàlid"

#define CLIENT_ALREADY_CONNECTED "Aquesta connexió ja ha estat establerta"



#endif //PRACTICA_SO_PRINTS_H
