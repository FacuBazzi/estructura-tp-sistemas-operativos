#include "modulo2.h"

void conectarConServidor() {
    socketServidor = conectar_a_servidor (config.IP_SERVIDOR, config.PUERTO_SERVIDOR);
    if (socketServidor == -1) {
        log_error(logger,"Falló la conexión con el servidor");
        exit(-1);
    } else {
        log_info(logger,"Conexion exitosa con el servidor");
        enviarMensajes();
    }
}

void enviarMensajes() {  // ejemplo
    int numero;
    int desplazamiento;
    CODIGO_MENSAJE codigo;
    int size = sizeof(CODIGO_MENSAJE) + sizeof(uint32_t);
    void* buffer;

    // primer mensaje ejemplo
    buffer = malloc(size);
    desplazamiento = 0;
    codigo = MENSAJE_1;
    numero = 4;
    memcpy(buffer+desplazamiento,&codigo,sizeof(CODIGO_MENSAJE));
    desplazamiento+=sizeof(CODIGO_MENSAJE);
    memcpy(buffer+desplazamiento,&numero,sizeof(uint32_t));
    desplazamiento+=sizeof(uint32_t);
    printf("Pido el doble de %d\n",numero);
    send(socketServidor, &size, sizeof(int), 0);
    send(socketServidor, buffer, size, 0);
    recv(socketServidor, &numero, sizeof(int), 0);
    printf("La respuesta es %d\n",numero);
    free(buffer);

    // segundo mensaje ejemplo
    buffer = malloc(size);
    desplazamiento = 0;
    codigo = MENSAJE_2;
    numero = 5;
    memcpy(buffer+desplazamiento,&codigo,sizeof(CODIGO_MENSAJE));
    desplazamiento+=sizeof(CODIGO_MENSAJE);
    memcpy(buffer+desplazamiento,&numero,sizeof(uint32_t));
    desplazamiento+=sizeof(uint32_t);
    printf("Pido el triple de %d\n",numero);
    send(socketServidor, &size, sizeof(int), 0);
    send(socketServidor, buffer, size, 0);
    recv(socketServidor, &numero, sizeof(int), 0);
    printf("La respuesta es %d\n",numero);
    free(buffer);
}
