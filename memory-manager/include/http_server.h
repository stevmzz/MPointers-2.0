#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <memory>
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "memory_manager.h"

/**
 * Clase que implementa el servidor HTTP utilizando Pistache.
 */
class HttpServer {
private:
    int port;                                                // puerto que escuchará el server
    std::shared_ptr<MemoryManager> memoryManager;            // puntero al administrador de memoria
    std::shared_ptr<Pistache::Http::Endpoint> endpoint;      // endpoint de pistache
    Pistache::Rest::Router router;                           // router para manejar las rutas
    void setupRoutes();                                      // configuración de las rutas

public:

    HttpServer(int port, std::shared_ptr<MemoryManager> memoryManager); // constructor que inicializa el servidor (puerto, puntero)

    void start();           // inicia el server
    void stop();            // detiene el server

    // maneja la solicitud de crear un bloque de memoria
    void handleCreate(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

    // maneja la solicitud para establecer un valor en un bloque de memoria
    void handleSet(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

    // maneja la solicitud para obtener el valor de un bloque de memoria
    void handleGet(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

    // maneja la solicitud para incrementar el contador de referencias de un bloque
    void handleIncreaseRefCount(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

    // maneja la solicitud para decrementar el contador de referencias de un bloque
    void handleDecreaseRefCount(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

    // maneja la solicitud para realizar una desfragmentación de memoria
    void handleDefragment(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

    // maneja la solicitud para obtener un volcado del estado de la memoria
    void handleDumpMemory(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};

#endif // HTTP_SERVER_H