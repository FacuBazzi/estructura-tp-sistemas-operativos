#include "modulo1.h"

int main(int argc, char ** argv){
        asignarArchivoConfig(argc, argv);
        iniciarTodo();
        abrirServidor();
        esperarFinalizacionHilos();
        finalizar();
        return 0;
}

void asignarArchivoConfig(int cantidadArgumentos, char** argumentos) {  // ejecutando ./modulo1 nombre (sin el .config)
        pathConfig = string_new();
        if (cantidadArgumentos > 1) {
                string_append(&pathConfig, "./cfg/");
                string_append(&pathConfig, argumentos[1]);
                string_append(&pathConfig, ".config");
        }
        else string_append(&pathConfig, "./cfg/modulo1.config");  // por defecto si no le paso un config especifico
}

void recibirComandos() {  // comandos para testear o manejar el modulo
        int fin=0;
        char* lectura;
        while(!fin) {
                lectura=readline("");
                if(!strcmp(lectura,"fin")) fin=1;
                if(!strcmp(lectura,"messi")) printf("Aguante Messi\n");
                free(lectura);
        }
        matarHilos();
}

void esperarFinalizacionHilos() {    // espera q todos los hilos finalicen para terminar
        pthread_join(hiloServer,NULL);
        pthread_join(hiloParaComandos,NULL);
}

void iniciarTodo() {   // todo lo que debe hacerse al iniciar el modulo
	logger = log_create("./cfg/modulo1.log", "modulo1", true, LOG_LEVEL_INFO);
	log_info(logger,"Inicia el modulo1 haciendo uso de shared: %s", funcion_compartida_test());
	config = cargarConfig(pathConfig);
        pthread_create(&hiloParaComandos, NULL, (void*) &recibirComandos, NULL);
}

void matarHilos() {        // finaliza a los hilos en caso de querer terminar la ejecucion
        pthread_cancel(hiloServer);
}

void finalizar() {      // todo lo que debe hacerse al finalizar el modulo
	log_info(logger,"Finalizando el modulo1");
	log_destroy(logger);
	config_destroy(auxConfig);
        close(socketServer);
        close(socketCliente);
//	... Hacer los free/close/destroy
}

Config cargarConfig(char* path) {    // cargar configuracion
	Config config;
	auxConfig = config_create(path);
	if (auxConfig != NULL) {
                config.PUERTO_ESCUCHA = config_get_string_value(auxConfig, "PUERTO_ESCUCHA");
		config.STRING_EJEMPLO = config_get_string_value(auxConfig, "STRING_EJEMPLO");
		config.INT_EJEMPLO = config_get_int_value(auxConfig, "INT_EJEMPLO");
		log_info(logger,"Configuración cargada correctamente desde %s",path);
	}
	else log_info(logger,"No se pudo cargar la configuración desde %s",path);
	return config;

        /*
        Configurar de acuerdo al archivo de configuración que corresponda
           Para leer int: config_get_int_value(auxConfig, "NOMBRE");
           Para leer string: config_get_string_value(auxConfig, "NOMBRE");
        */
}
