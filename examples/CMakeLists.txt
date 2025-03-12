# Crear ejecutable para el ejemplo de lista enlazada
add_executable(linked_list linked_list.cpp)

# Enlazar con la biblioteca mpointers
target_link_libraries(linked_list
        mpointers
        ${CMAKE_THREAD_LIBS_INIT}
)

# Incluir directorios de cabecera
target_include_directories(linked_list PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../mpointers-lib/include
)