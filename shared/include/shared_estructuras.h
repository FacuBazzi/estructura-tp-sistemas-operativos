#ifndef SHARED_ESTRUCTURAS_H
#define SHARED_ESTRUCTURAS_H

#include <stdio.h>
#include <commons/log.h>
#include <stdbool.h>
#include <stdlib.h>
#include <commons/config.h>
#include <readline/readline.h>
#include <commons/collections/list.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <netdb.h>
#include <commons/collections/dictionary.h>
#include <commons/collections/queue.h>
#include <commons/collections/node.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>
#include <time.h>
#include <sys/socket.h>
#include <stdint.h>
#include <math.h>
#include <commons/string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

// no importa si hay includes de más, ya fue

typedef enum {
	MENSAJE_1,
	MENSAJE_2,
	MENSAJE_3
} CODIGO_MENSAJE;

typedef struct {
	CODIGO_MENSAJE codigo_mensaje;
	uint32_t int_ejemplo;
	t_list* lista_ejemplo;
	char* string_ejemplo;
} NombreDelStruct;

#endif