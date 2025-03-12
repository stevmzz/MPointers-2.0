# Fuentes para Memory Manager
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Crear ejecutable para el memory manager
add_executable(mem-mgr ${SOURCES})

# Enlazar con bibliotecas necesarias
target_link_libraries(mem-mgr
        ${PISTACHE_LIBRARIES}
        ${NLOHMANN_JSON_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
)

# Incluir directorios para encontrar cabeceras de dependencias
target_include_directories(mem-mgr PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${PISTACHE_INCLUDE_DIRS}
        ${NLOHMANN_JSON_INCLUDE_DIRS}
)