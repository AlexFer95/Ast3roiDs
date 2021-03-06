cmake_minimum_required(VERSION 3.6)
project(Ast3roiDs)

# Activa símbolos de depuración.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Copia el directorio de recursos al directorio de los binarios
file(COPY ${PROJECT_SRC_DIR}Recursos DESTINATION .)

set(BUILD_DEBUG true)

if(BUILD_DEBUG)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread ")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -g -static -mwindows -pthread ")
endif()

project(Ast3roiDs)
set(EXECUTABLE_NAME Ast3roiDs)

set(FUENTES_ASTEROIDS
		matematicas.hpp
		Estados.hpp
		Colisiones.hpp
		Colisiones.cpp
		ControladorSonido.cpp
		ControladorSonido.hpp)

set(FUENTES_2D
		Graficos/Triangular.hpp
		Graficos/Triangular.cpp
		Graficos/Circular.hpp
		Graficos/Circular.cpp
		Graficos/Disparo.hpp
		Graficos/Disparo.cpp
		Graficos/Nave.hpp
		Graficos/Nave.cpp
		Graficos/Asteroide.cpp
		Graficos/Asteroide.hpp
		Graficos/Ovni.cpp
		Graficos/Ovni.hpp
		constantesGlobales.hpp
		Graficos/OvniInteligente.cpp Graficos3D/OvniInteligente3D.cpp Graficos3D/OvniInteligente3D.hpp Graficos3D/fuego.cpp)

set(FUENTES_3D
        Graficos3D/Elemento3D.hpp
        Graficos3D/Elemento3D.cpp
		Graficos3D/Asteroide3D.hpp
		Graficos3D/Asteroide3D.cpp
		Graficos3D/Nave3D.hpp
		Graficos3D/Nave3D.cpp
		Graficos3D/Ovni3D.cpp
		Graficos3D/Ovni3D.hpp
		Graficos3D/Disparo3D.cpp
		Graficos3D/Disparo3D.hpp
        Graficos3D/Esfera.cpp
        Graficos3D/Esfera.hpp
		Graficos3D/Minimapa.cpp
		Graficos3D/Minimapa.hpp
		Util3D/Ventana3D.cpp
		Util3D/Ventana3D.hpp
		Util3D/Shader.hpp
		Util3D/Shader.cpp
		Util3D/Posicionamiento.hpp
		Util3D/Camara.hpp
		Util3D/Textura.cpp
		Util3D/Textura.hpp
		Util3D/ControladorModelos.cpp
		Util3D/ControladorModelos.hpp
		Util3D/ControladorTexturas.cpp
		Util3D/ControladorTexturas.hpp
		Util3D/ControladorShaders.cpp
		Util3D/ControladorShaders.hpp Graficos3D/Fuego.hpp Graficos3D/Fuego.cpp)


add_executable(${EXECUTABLE_NAME} main.cpp ${FUENTES_ASTEROIDS} ${FUENTES_2D} ${FUENTES_3D})

set(SFML_ROOT "C:/Program Files (x86)/SFML")

find_package(OpenGL)
find_package(glew)
# Detecta y linkea SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
add_subdirectory(neural)
include_directories(neural/include/)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} neural)
endif()
