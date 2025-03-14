#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <csignal>
#include "../include/memory_manager.h"
#include "../include/http_server.h"

using namespace std;

// variable global para controlar la ejecución del programa
volatile sig_atomic_t running = 1;

// manejador de señales para terminar el programa limpiamente
void signalHandler(int signal) {
    cout << "\nSeñal recibida (" << signal << "). Terminando servidor..." << endl;
    running = 0;
}

int main(int argc, char* argv[]) {
    signal(SIGINT, signalHandler);
    cout << "Memory Manager Test" << endl;
    int port = 9080;
    if (argc > 1) {
        port = std::stoi(argv[1]);
    }

    // TEST: crear un Memory Manager con 1MB de memoria
    try {
        // crear Memory Manager
        auto manager = std::make_shared<MemoryManager>(1024 * 1024, "./dumps");
        cout << "Memory Manager creado correctamente con 1MB de memoria" << endl;

        // crear el servidor http
        HttpServer server(port, manager);
        cout << "Servidor HTTP creado en puerto " << port << endl;

        // iniciar el servidor en un hilo separado
        std::thread serverThread([&server]() {
            cout << "Iniciando servidor HTTP..." << endl;
            server.start();
        });

        cout << "Servidor en ejecución. Presiona Ctrl+C para detener." << endl;

        // bucle principal del programa
        while(running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // detener el servidor y esperar a que el hilo termine
        cout << "Deteniendo servidor..." << endl;
        server.stop();

        if (serverThread.joinable()) {
            serverThread.join();
        }

        cout << "Servidor detenido correctamente" << endl;

    } catch (const std::exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    cout << "Programa finalizado" << endl;
    return 0;
}