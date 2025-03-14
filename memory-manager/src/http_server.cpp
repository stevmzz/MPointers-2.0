#include "../include/http_server.h"
#include <nlohmann/json.hpp>
#include <iostream>
using json = nlohmann::json; // para usar json

HttpServer::HttpServer(int port, std::shared_ptr<MemoryManager> memoryManager): // constructor: inicializa el servidor con el puerto y el manager
    port(port), memoryManager(memoryManager) {

    // crea el endpoint de Pistache en el puerto especificado
    auto opts = Pistache::Http::Endpoint::options().threads(1);
    endpoint = std::make_shared<Pistache::Http::Endpoint>(Pistache::Address(Pistache::Ipv4::any(), Pistache::Port(port)));
    endpoint -> init(opts);

    // configura las rutas del servidor
    setupRoutes();

    std::cout << "HTTP Server inicializado en el puerto " << port << std::endl;
}

// configura las rutas del servidor
void HttpServer::setupRoutes() {
    using namespace Pistache::Rest;

    // definición de rutas para las operaciones del memory manager
    Routes::Post(router, "/memory/create", Routes::bind(&HttpServer::handleCreate, this));
    Routes::Put(router, "/memory/:id", Routes::bind(&HttpServer::handleSet, this));
    Routes::Get(router, "/memory/:id", Routes::bind(&HttpServer::handleGet, this));
    Routes::Post(router, "/memory/:id/increaseRefCount", Routes::bind(&HttpServer::handleIncreaseRefCount, this));
    Routes::Post(router, "/memory/:id/decreaseRefCount", Routes::bind(&HttpServer::handleDecreaseRefCount, this));
    Routes::Post(router, "/memory/defragment", Routes::bind(&HttpServer::handleDefragment, this));
    Routes::Get(router, "/memory/dump", Routes::bind(&HttpServer::handleDumpMemory, this));

    // configura el router en el endpoint
    endpoint->setHandler(router.handler());
}

// inicia el servidor
void HttpServer::start() {
    endpoint -> serve();
    std::cout << "Server iniciado en el puerto: " << port << std::endl;
}

// detiene el servidor
void HttpServer::stop() {
    endpoint -> shutdown();
    std::cout << "Server detenido" << std::endl;
}



// implementación de los métodos de manejo de solicitudes HTTP:
void HttpServer::handleCreate(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    // parsear la solicitud como json
    auto body = request.body();
    json requestData;

    try {
        requestData = json::parse(body);

        // extraer los parametros necesarios
        if (!requestData.contains("size") || !requestData.contains("type")) {
            json error;
            error["status"] = "error";
            error["message"] = "Se requieren los campos 'size' y 'type'";
            response.send(Pistache::Http::Code::Bad_Request, error.dump());
            return;
        }

        size_t size = requestData["size"];
        std::string type = requestData["type"];

        // llamada al método memory manger
        int id = memoryManager -> Create(size, type);

        if (id >= 0) {
            // Éxito: devolver el id del bloque creado
            json result;
            result["status"] = "ok";
            result["id"] = id;
            result["size"] = size;
            result["type"] = type;
            response.send(Pistache::Http::Code::Created, result.dump());

        } else {
            // Error: no se pudo crear el bloque
            json error;
            error["status"] = "error";
            error["message"] = "No se pudo crear el bloque de memoria";
            response.send(Pistache::Http::Code::Internal_Server_Error, error.dump());
        }

    } catch (const std::exception& e) {
        // error al parsear u otros errores
        json error;
        error["status"] = "error";
        error["message"] = std::string("Error: ") + e.what();
        response.send(Pistache::Http::Code::Bad_Request, error.dump());
    }
}



void HttpServer::handleSet(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    // obtener el id del bloque
    auto idParam = request.param(":id").as<int>();

    // parsear la solicitud como json
    auto body = request.body();
    json requestData;

    try {
        requestData = json::parse(body);

        // extraer los parametros necesarios
        if (!requestData.contains("value")) {
            json error;
            error["status"] = "error";
            error["message"] = "Se requiere el campo 'value'";
            response.send(Pistache::Http::Code::Bad_Request, error.dump());
            return;
        }

        std::string type = requestData["value"];

        // llamada al método memory manger
        bool success = memoryManager -> Set(idParam, type);

        if (success) {
            // Éxito: valor establecido correctamente
            json result;
            result["status"] = "ok";
            result["id"] = idParam;
            result["message"] = "Valor establecido correctamente";
            response.send(Pistache::Http::Code::Created, result.dump());

        } else {
            // Error: no se pudo establecer el valor
            json error;
            error["status"] = "error";
            error["message"] = "No se pudo establecer el valor en el bloque " + std::to_string(idParam);
            response.send(Pistache::Http::Code::Internal_Server_Error, error.dump());
        }

    } catch (const std::exception& e) {
        // error al parsear u otros errores
        json error;
        error["status"] = "error";
        error["message"] = std::string("Error: ") + e.what();
        response.send(Pistache::Http::Code::Bad_Request, error.dump());
    }
}

void HttpServer::handleGet(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    auto id = request.param(":id").as<int>();

    json result;
    result["status"] = "ok";
    result["message"] = "Get endpoint funcionando";
    result["endpoint"] = "/memory/" + std::to_string(id);
    response.send(Pistache::Http::Code::Ok, result.dump());
}

void HttpServer::handleIncreaseRefCount(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    auto id = request.param(":id").as<int>();

    json result;
    result["status"] = "ok";
    result["message"] = "IncreaseRefCount endpoint funcionando";
    result["endpoint"] = "/memory/" + std::to_string(id) + "/increaseRefCount";
    response.send(Pistache::Http::Code::Ok, result.dump());
}

void HttpServer::handleDecreaseRefCount(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    auto id = request.param(":id").as<int>();

    json result;
    result["status"] = "ok";
    result["message"] = "DecreaseRefCount endpoint funcionando";
    result["endpoint"] = "/memory/" + std::to_string(id) + "/decreaseRefCount";
    response.send(Pistache::Http::Code::Ok, result.dump());
}

void HttpServer::handleDefragment(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    json result;
    result["status"] = "ok";
    result["message"] = "Defragment endpoint funcionando";
    result["endpoint"] = "/memory/defragment";
    response.send(Pistache::Http::Code::Ok, result.dump());
}

void HttpServer::handleDumpMemory(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    json result;
    result["status"] = "ok";
    result["message"] = "DumpMemory endpoint funcionando";
    result["endpoint"] = "/memory/dump";
    response.send(Pistache::Http::Code::Ok, result.dump());
}