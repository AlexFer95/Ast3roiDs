#include <iostream>
#include "Nave.hpp"

//Constructor
Nave::Nave(sf::Vector2f posicion_inicial){
    if (!bufferSonidoDisparo.loadFromFile("Recursos/Sonido/fire.wav")){
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/fire.wav\"");
    }
    if (!bufferSonidoPropulsion.loadFromFile("Recursos/Sonido/thrust.wav")){
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/thrust.wav\"");
    }
    if (!bufferSonidoDestruccion.loadFromFile("Recursos/Sonido/bangSmall.wav")){
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/bangSmall.wav\"");
    }

    reproductorDeSonidoPropulsion.setBuffer(bufferSonidoPropulsion);
    reproductorDeSonidoDisparos.setBuffer(bufferSonidoDisparo);
    reproductorDeSonidoDestruccion.setBuffer(bufferSonidoDestruccion);

    puntos[0] = sf::Vector2f(1.0f,0.0f);
    puntos[1] = sf::Vector2f(-0.7071067812f,0.7071067812f);
    puntos[2] = sf::Vector2f(-0.7071067812f,-0.7071067812f);
    puntos[3] = sf::Vector2f(-0.4f,0.0f);

    direccion = (float)-PI/2.0f;

    //Posicion de la nave
    posicion = posicion_inicial;

    //Velocidad de la nave
    sf::Vector2f velocidad = sf::Vector2f(0.0, 0.0);

    //Disparos
    num_disparos = 0;
    for(int i=0 ; i<MAX_DISPAROS ; i++){
        disparos[i] = Disparo(sf::Vector2f(0.0, 0.0));
    }
}

//Destructor
Nave::~Nave(){}

//Setters
void Nave::setPuntos(sf::Vector2f ps[4]){
    puntos[0] = ps[0];
    puntos[1] = ps[1];
    puntos[2] = ps[2];
    puntos[3] = ps[3];
}

void Nave::setDireccion(float dir){
    direccion = dir;
}

void Nave::setPosicion(sf::Vector2f pos){
    posicion = pos;
}

void Nave::setVelocidad(sf::Vector2f vel){
    velocidad = vel;
}

//Getters
sf::Vector2f* Nave::getPuntos(){
    return puntos;
}

float Nave::getDireccion(){
    return direccion;
}

sf::Vector2f Nave::getPosicion(){
    return posicion;
}

sf::Vector2f Nave::getVelocidad(){
    return velocidad;
}

//Dibujo
void Nave::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::Vertex linea01[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[0].x*TAMANO*cos(direccion)-puntos[0].y*TAMANO*sin(direccion),posicion.y+puntos[0].y*TAMANO*cos(direccion)+puntos[0].x*TAMANO*sin(direccion)),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[1].x*TAMANO*cos(direccion)-puntos[1].y*TAMANO*sin(direccion),posicion.y+puntos[1].y*TAMANO*cos(direccion)+puntos[1].x*TAMANO*sin(direccion)),sf::Color::White),
    };

    sf::Vertex linea13[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[1].x*TAMANO*cos(direccion)-puntos[1].y*TAMANO*sin(direccion),posicion.y+puntos[1].y*TAMANO*cos(direccion)+puntos[1].x*TAMANO*sin(direccion)),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[3].x*TAMANO*cos(direccion)-puntos[3].y*TAMANO*sin(direccion),posicion.y+puntos[3].y*TAMANO*cos(direccion)+puntos[3].x*TAMANO*sin(direccion)),sf::Color::White),
    };

    sf::Vertex linea32[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[3].x*TAMANO*cos(direccion)-puntos[3].y*TAMANO*sin(direccion),posicion.y+puntos[3].y*TAMANO*cos(direccion)+puntos[3].x*TAMANO*sin(direccion)),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[2].x*TAMANO*cos(direccion)-puntos[2].y*TAMANO*sin(direccion),posicion.y+puntos[2].y*TAMANO*cos(direccion)+puntos[2].x*TAMANO*sin(direccion)),sf::Color::White),
    };

    sf::Vertex linea20[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[2].x*TAMANO*cos(direccion)-puntos[2].y*TAMANO*sin(direccion),posicion.y+puntos[2].y*TAMANO*cos(direccion)+puntos[2].x*TAMANO*sin(direccion)),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[0].x*TAMANO*cos(direccion)-puntos[0].y*TAMANO*sin(direccion),posicion.y+puntos[0].y*TAMANO*cos(direccion)+puntos[0].x*TAMANO*sin(direccion)),sf::Color::White),
    };

    target.draw(linea01, 2, sf::Lines);
    target.draw(linea13, 2, sf::Lines);
    target.draw(linea32, 2, sf::Lines);
    target.draw(linea20, 2, sf::Lines);

    //Dibujar los disparos
    for(int i=0 ; i<num_disparos ; i++){
        target.draw(disparos[i]);
    }
}

//Otros
void Nave::disparar(){
    if(num_disparos<MAX_DISPAROS){
        sf::Vector2f inicio = puntos[0];
        inicio.x = (float)(puntos[0].x*TAMANO*cos(direccion)-puntos[0].y*TAMANO*sin(direccion));
        inicio.y = (float)(puntos[0].y*TAMANO*cos(direccion)+puntos[0].x*TAMANO*sin(direccion));
        disparos[num_disparos] = Disparo(posicion+inicio);
        disparos[num_disparos].setDireccion(direccion);
        num_disparos++;
        reproductorDeSonidoDisparos.play();
    }
}

void Nave::rotarIzda(){
    direccion -= V_ANGULAR;
    if(direccion<0.0){
        direccion += 2*PI;
    }
}

void Nave::rotarDcha(){
    direccion += V_ANGULAR;
    if(direccion>2.0*PI){
        direccion -= 2*PI;
    }
}

void Nave::mover(sf::Vector2u limites){
    //Mover la nave
    posicion.x += velocidad.x;
    if(posicion.x-1>=limites.x){
        posicion.x -= limites.x;
    }
    else if(posicion.x+1<=0.0){
        posicion.x += limites.x;
    }

    posicion.y += velocidad.y;
    if(posicion.y-1>=limites.y){
        posicion.y -= limites.y;
    }
    else if(posicion.y+1<=0.0){
        posicion.y += limites.y;
    }

    //Mover los disparos
    for(int i=0 ; i<num_disparos ; i++){
        disparos[i].mover(limites);
        if(disparos[i].comprobarAlcance()){
            if(disparos[i].comprobarAlcance()){
                recuperarDisparo(i);
            }
            else if(disparos[i].comprobarColision()){
                recuperarDisparo(i);
            }
        }
    }
}

void Nave::recuperarDisparo(int d){
    for(int i=d; i<num_disparos-1 ; i++){
        disparos[i] = disparos[i+1];
    }
    num_disparos--;
}

void Nave::acelerar(){
    if(velocidad.x*velocidad.x+velocidad.y*velocidad.y<MAX_VELOCIDAD*MAX_VELOCIDAD){
        velocidad.x += ACELERACION*cos(direccion);
        velocidad.y += ACELERACION*sin(direccion);
    }
    if (reproductorDeSonidoPropulsion.getStatus() == sf::Sound::Status::Stopped){
        reproductorDeSonidoPropulsion.play();
    }
}

void Nave::frenar(){
    if(velocidad.x*velocidad.x+velocidad.y*velocidad.y<UMBRAL){
        velocidad.x = 0;
        velocidad.y = 0;
    }
    else{
        velocidad.x *= DECELERACION;
        velocidad.y *= DECELERACION;
    }
}