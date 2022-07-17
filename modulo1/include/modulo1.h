#ifndef MODULO1_H
#define MODULO1_H

#include "conexiones.h"

t_config* auxConfig;
char* pathConfig;

Config cargarConfig(char* path);
void finalizar();
void iniciarTodo();
void esperarFinalizacionHilos();
void matarHilos();
void recibirComandos();
void asignarArchivoConfig(int argc, char** argv);

#endif