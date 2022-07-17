#include "shared_utils.h"

char* funcion_compartida_test(){
    return "Hice uso de la shared!";
}

int iniciar_servidor(char* puerto, int cant_conexiones) {  // cant_conexiones = 0 si acepto infinitas
    int socket_servidor;
    struct addrinfo hints, *servinfo;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo((char*)NULL, puerto, &hints, &servinfo);

    bool conecto = false;

    for (struct addrinfo *p = servinfo; p != NULL; p = p->ai_next) {
        socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
        setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int));
        if (socket_servidor == -1)
            continue;

        if (bind(socket_servidor, p->ai_addr, p->ai_addrlen) == -1) {
            close(socket_servidor);
            continue;
        }
        conecto = true;
        break;
    }

    if(!conecto) {
        free(servinfo);
        return 0;
    }

    if (cant_conexiones!=0) listen(socket_servidor, cant_conexiones); // Escuchando cant_conexiones conexiones simultaneas
    else listen(socket_servidor, SOMAXCONN); // Escuchando todas las conexiones simultaneas posibles

    freeaddrinfo(servinfo);

    return socket_servidor;
}

int conectar_a_servidor (char* ip, char* puerto) {
	struct addrinfo hints;
	struct addrinfo *server_info;
	int clientSocket;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if(getaddrinfo(ip, puerto, &hints, &server_info)){   // error
        exit(-1);
    }

    clientSocket = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
    setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    setsockopt(clientSocket, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int));

    if(connect(clientSocket, server_info->ai_addr, server_info->ai_addrlen) == -1){
        return -1;
    }

    freeaddrinfo(server_info);
    return clientSocket;
}
