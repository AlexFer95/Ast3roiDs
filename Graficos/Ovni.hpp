#ifndef AST3ROIDS_OVNI_HPP
#define AST3ROIDS_OVNI_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

#include "../Colisiones.hpp"
#include "Circular.hpp"
#include "Disparo.hpp"

#define PI 3.14159265358979323846

class Ovni : public sf::Drawable, public Circular {

    private:
        static constexpr float VELOCIDAD = 10.0;
        //Numero maximo de disparos activos
        static const int MAX_DISPAROS = 2;
        //Direccion en que se mueve el ovni
        float direccion;

        sf::VertexArray poligono;

        sf::Vector2f velocidad;

        //Numero de disparos
        int num_disparos;
        //Vector de disparos
        Disparo disparos[MAX_DISPAROS];

        // Buffers de los distintos sonidos de un ovni
        sf::SoundBuffer bufferSonidoOvni;
        sf::SoundBuffer bufferSonidoDisparo;

        // Reproductores de sonido
        sf::Sound reproductorDeSonidoDisparos;
        sf::Sound reproductorDeSonidoOvni;

    public:
        Ovni(sf::Vector2u limites);
        ~Ovni();

        //Getters
        float getDireccion();
        sf::Vector2f getVelocidad();
        virtual int getPuntuacion() const;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void disparar();
        void mover(sf::Vector2u limites, std::vector<Asteroide> v);

        void recuperarDisparo(int d);
        bool comprobarColision(Circular& c);
};


#endif //AST3ROIDS_OVNI_HPP
