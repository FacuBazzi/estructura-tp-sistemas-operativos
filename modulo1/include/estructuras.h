#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include "shared_utils.h"

typedef struct {
	char* PUERTO_ESCUCHA;  // leer a las ip y puertos como strings
    char* STRING_EJEMPLO;
	int INT_EJEMPLO;
} Config;
Config config;

t_log* logger;
int socketServer, socketCliente;

pthread_t hiloParaComandos;
pthread_t hiloServer;

#endif