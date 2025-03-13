#include <iostream>
#include <string>
#include "../include/memory_manager.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Memory Manager Test" << endl;

    // TEST: crear un Memory Manager con 1MB de memoria
    try {
        MemoryManager manager(1024 * 1024, "./dumps");
        cout << "Memory Manager creado correctamente" << endl;

    } catch (const std::exception& e) {
        cout << "Error al crear el Memory Manager: " << e.what() << endl;
    }

    return 0;
}