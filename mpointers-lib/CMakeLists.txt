# Fuentes para la biblioteca MPointers
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Crear biblioteca estática
add_library(mpointers STATIC ${SOURCES})

# Enlazar con bibliotecas necesarias
target_link_libraries(mpointers
        ${NLOHMANN_JSON_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
)

# Incluir directorios para encontrar cabeceras de dependencias
target_include_directories(mpointers PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${NLOHMANN_JSON_INCLUDE_DIRS}
)