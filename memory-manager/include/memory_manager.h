#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <string>      // para strings
#include <vector>      // para arrays que almacenan bloques
#include <mutex>       // para sincronización en entornos multihilo
#include <map>         // para el mapeo rápido de id

/**
 * Estructura que representa un bloque de memoria administrado.
 */
struct MemoryBlock {
    int id;              // identificador único del bloque
    void* address;       // dirección física en memoria donde comienza este bloque
    size_t size;         // tamaño en bytes que ocupa el bloque
    std::string type;    // tipo de dato almacenado
    int refCount;        // contador de referencias
    bool isFree;         // indicador si el bloque está disponible para ser reutilizado

    // constructor que inicializa un nuevo bloque con valores por defecto
    MemoryBlock(int id, void* address, size_t size, std::string type)
    : id(id), address(address), size(size), type(std::move(type)), refCount(1), isFree(false) {}
    // Nota: refCount comienza en 1 porque al crear un bloque ya hay una referencia
    // isFree comienza como false porque está en uso al crearse
};

/**
 * Clase que administra un bloque de memoria reservado.
 */
class MemoryManager {
private:
    void* memoryPool;                    // puntero al inicio del gran bloque de memoria reservado
    size_t totalSize;                    // tamaño total del bloque de memoria (en bytes)
    size_t usedSize;                     // cantidad de memoria actualmente en uso (en bytes)
    std::vector<MemoryBlock*> blocks;    // vector que almacena punteros a todos los bloques
    std::map<int, size_t> blockIndexMap; // mapeo de id de bloque a su posición en el vector
    int nextBlockId;                     // id que se asignará al siguiente bloque creado
    std::string dumpDirectory;           // directorio donde se guardarán los dumps de memoria
    std::mutex mutex;                    // mutex para proteger el acceso concurrente

public:
    // constructor: inicializa el sistema con un tamaño y directorio para volcados
    MemoryManager(size_t size, const std::string& dumpDir = "./dumps");

    // destructor: libera toda la memoria reservada
    ~MemoryManager();

    // métodos públicos para interactuar con la memoria
    int Create(size_t size, const std::string& type);   // crea un nuevo bloque de memoria
    bool Set(int id, const std::string& value);         // establece un valor en un bloque
    std::string Get(int id);                            // obtiene el valor de un bloque
    int IncreaseRefCount(int id);                       // incrementa contador de referencias
    int DecreaseRefCount(int id);                       // decrementa contador de referencias
    bool Defragment();                                  // reorganiza la memoria para consolidar espacio libre
    std::string DumpMemory();                           // crea un volcado del estado de la memoria

private:
    // método interno para encontrar un bloque libre del tamaño requerido
    int FindFreeBlock(size_t size);
};


    // Aquí irían:
    // Constructor que inicializa el Memory Manager
    // Destructor que libera la memoria reservada
    // Create(size_t size, const std::string& type)
    // Set(int id, const std::string& value)
    // Get(int id)

    // También se necesitan:
    // IncreaseRefCount(int id)
    // DecreaseRefCount(int id)
    // Defragment()
    // DumpMemory()


#endif // MEMORY_MANAGER_H