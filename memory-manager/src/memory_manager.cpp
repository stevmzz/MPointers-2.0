#include "../include/memory_manager.h"       // Inclusión del archivo de cabecera
#include <cstring>                           // Para operaciones de memoria como memset
#include <iostream>                          // Para imprimir mensajes de log
#include <filesystem>                        // Para operaciones con directorios

// constructor: inicializa todo el sistema de gestión de memoria
MemoryManager::MemoryManager(size_t size, const std::string& dumpDir)
    : totalSize(size), usedSize(0), nextBlockId(0), dumpDirectory(dumpDir) {

    // crea el directorio para los volcados de memoria si no existe
    std::filesystem::create_directories(dumpDirectory);

    // reserva un gran bloque continuo de memoria
    memoryPool = malloc(totalSize);
    if (!memoryPool) { // si no se puede, tira una exepción
        throw std::runtime_error("No se pudo reservar la memoria solicitada");
    }

    std::cout << "Memory Manager inicializado con " << totalSize << " bytes" << std::endl;
}

// destructor: libera toda la memoria reservada
MemoryManager::~MemoryManager() {
    if (memoryPool) {
        // libera el bloque principal de memoria
        free(memoryPool);
        memoryPool = nullptr;
    }

    std::cout << "Memory Manager destruido" << std::endl;
}

// busca un bloque libre que tenga al menos el tamaño especificado
int MemoryManager::FindFreeBlock(size_t size) {
    for (size_t i = 0; i < blocks.size(); i++) {
        // verifica si el bloque está libre y tiene suficiente tamaño
        if (blocks[i]->isFree && blocks[i]->size >= size) {
            return i; // retorna el índice del bloque encontrado
        }
    }
    return -1; // retorna -1 si no encuentra ningún bloque adecuado
}

int MemoryManager::Create(size_t size, const std::string& type) {
    std::cout << "Método Create llamado, pero aún no está implementado" << std::endl;
    return -1;
}

bool MemoryManager::Set(int id, const std::string& value) {
    std::cout << "Método Set llamado, pero aún no está implementado" << std::endl;
    return false;
}

std::string MemoryManager::Get(int id) {
    std::cout << "Método Get llamado, pero aún no está implementado" << std::endl;
    return "";
}

int MemoryManager::IncreaseRefCount(int id) {
    std::cout << "Método IncreaseRefCount llamado, pero aún no está implementado" << std::endl;
    return -1;
}

int MemoryManager::DecreaseRefCount(int id) {
    std::cout << "Método DecreaseRefCount llamado, pero aún no está implementado" << std::endl;
    return -1;
}

// Aquí irían:
// Implementación de Create
// Implementación de Set
// Implementación de Get

// También se necesitan:
// Implementación de IncreaseRefCount
// Implementación de DecreaseRefCount
// Implementación de Defragment
// Implementación de DumpMemory