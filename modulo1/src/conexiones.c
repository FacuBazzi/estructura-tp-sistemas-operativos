#include "modulo1.h"

void abrirServidor() {
    socketServer = iniciar_servidor(config.PUERTO_ESCUCHA, 0);
    if (pthread_create(&hiloServer, NULL, (void*) &esperarCliente, NULL) != 0) {
        log_error(logger, "Error al crear el hilo del server");
	}
    log_info(logger,"Servidor iniciado y esperando que lleguen clientes");
}

void esperarCliente(){
    socketCliente = accept(socketServer, NULL, NULL);
    log_info(logger,"Cliente conectado!");
    recibirMensajes();
}

void recibirMensajes() {
    void* buffer;
    int size, desplazamiento;
    uint32_t numero; // ejemplo
    CODIGO_MENSAJE mensaje;
	while(1) {
        desplazamiento=sizeof(CODIGO_MENSAJE);
        recv(socketCliente, &size, sizeof(int), 0);
        buffer = malloc(size);
        recv(socketCliente, buffer, size, 0);
        memcpy(&mensaje,buffer,sizeof(CODIGO_MENSAJE));
        switch(mensaje) {
            case MENSAJE_1:
                log_info(logger,"Recibi un MENSAJE_1, respondo el doble del numero recibido");
                memcpy(&numero,buffer+desplazamiento,sizeof(uint32_t));
                numero*=2;
                send(socketCliente, &numero, sizeof(uint32_t), 0);
                break;
            case MENSAJE_2:
                log_info(logger,"Recibi un MENSAJE_2, respondo el triple del numero recibido");
                memcpy(&numero,buffer+desplazamiento,sizeof(uint32_t));
                numero*=3;
                send(socketCliente, &numero, sizeof(uint32_t), 0);
                break;
            case MENSAJE_3:
                log_info(logger,"Recibi un MENSAJE_3");
                // ...
                break;
            default:
                log_info(logger,"Me llegó un mensaje desconocido");
        }
        free(buffer);
    }
}
