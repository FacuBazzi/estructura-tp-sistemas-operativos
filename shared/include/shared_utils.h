#ifndef SHARED_UTILS_H
#define SHARED_UTILS_H

#include "shared_estructuras.h"

char* funcion_compartida_test();
int iniciar_servidor(char* puerto, int cant_conexiones);
int conectar_a_servidor (char* ip, char* puerto);

#endif