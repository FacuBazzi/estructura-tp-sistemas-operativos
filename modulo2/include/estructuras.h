#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include "shared_utils.h"

typedef struct {
	char* IP_SERVIDOR;		// leer a las ip y puertos como strings
	char* PUERTO_SERVIDOR;	// leer a las ip y puertos como strings
    char* STRING_EJEMPLO;
	int INT_EJEMPLO;
} Config;
Config config;

t_log* logger;
int socketServidor;

pthread_t hiloParaComandos;
pthread_t hiloConexion;

#endif