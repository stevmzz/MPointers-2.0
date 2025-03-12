cmake_minimum_required(VERSION 3.10)
project(MPointers_2_0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Asegurarnos de que podemos encontrar las dependencias
find_package(PkgConfig REQUIRED)
pkg_check_modules(PISTACHE REQUIRED libpistache)
pkg_check_modules(NLOHMANN_JSON REQUIRED nlohmann_json)
find_package(Threads REQUIRED)

# Mostrar información de depuración para verificar las rutas de Pistache
message(STATUS "Pistache include dirs: ${PISTACHE_INCLUDE_DIRS}")
message(STATUS "Pistache library dirs: ${PISTACHE_LIBRARY_DIRS}")
message(STATUS "Pistache libraries: ${PISTACHE_LIBRARIES}")

# Definir el ejecutable principal directamente aquí
file(GLOB MEMORY_MANAGER_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/memory-manager/src/*.cpp"
)

# Incluir directorios de cabecera globales
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/memory-manager/include
        ${CMAKE_CURRENT_SOURCE_DIR}/mpointers-lib/include
        ${PISTACHE_INCLUDE_DIRS}
        ${NLOHMANN_JSON_INCLUDE_DIRS}
)

# Añadir directorios de bibliotecas
link_directories(${PISTACHE_LIBRARY_DIRS})

# Crear el ejecutable principal (mismo nombre que el proyecto)
add_executable(MPointers_2_0 ${MEMORY_MANAGER_SOURCES})

# Enlazar con bibliotecas necesarias
target_link_libraries(MPointers_2_0
        ${PISTACHE_LIBRARIES}
        ${NLOHMANN_JSON_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        pistache
)

# Ahora incluir los subdirectorios para los demás componentes
add_subdirectory(memory-manager)
add_subdirectory(mpointers-lib)
add_subdirectory(examples)