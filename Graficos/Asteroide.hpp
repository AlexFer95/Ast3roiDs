#ifndef AST3ROIDS_ASTEROIDE_HPP
#define AST3ROIDS_ASTEROIDE_HPP

#include <SFML/Graphics.hpp>

#include "../Estados.hpp"
#include "Circular.hpp"
#include "../Estados.hpp"
#include "../matematicas.hpp"
#include "../constantesGlobales.hpp"

class Asteroide : public sf::Drawable, public Circular {

private:
    float direccion;
    Tipo version;
    sf::VertexArray poligono;

    sf::VertexArray punto;
    sf::Vector2f posicion0, posicion1, posicion2, posicion3, posicion4, posicion5, posicion6, posicion7;
    bool recienDestruida = false;
    sf::Vector2f velocidad;
    Tamano tipoTamano;
    sf::Vector2u limites;
    sf::Color color;
    clock_t start;
public:

    Asteroide(sf::Vector2f posicion_inicial, float dir, sf::Vector2f vel, Tipo tipo, Tamano tam,
              sf::Vector2u limitesPantalla, sf::Color color);

    ~Asteroide() {};

    sf::VertexArray getPuntos();

    float getDireccion();

    sf::Vector2f getVelocidad();

    virtual int getPuntuacion() const;

    void mover();

    void explotar() {};

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    //Otros
    virtual void cambiarEstado(int nuevoEstado);

    void gestionarDestruccion(std::vector<Asteroide> &v);

    static void nuevosAsteroidesAleatorios(std::vector<Asteroide> &vectorAsteroides, unsigned int numAsteroides,
                                           sf::Vector2u limitesPantalla, sf::Color color) {
        vectorAsteroides.clear();
        for (int i = 0; i < numAsteroides; ++i) {
            float velocidad = valorAleatorio(0.2, 2.0) * limitesPantalla.y / (float) RESOLUCION_BASE.y;
            float direccion = anguloAleatorio();

            int posX = limitesPantalla.x / 2;
            int posY = limitesPantalla.y / 2;

            while (std::abs(posX - limitesPantalla.x / 2) < limitesPantalla.x * 0.05) {
                posX = enteroAleatorio(0, limitesPantalla.x);
            }
            while (std::abs(posY - limitesPantalla.y / 2) < limitesPantalla.y * 0.05) {
                posY = enteroAleatorio(0, limitesPantalla.y);
            }

            vectorAsteroides.push_back(Asteroide(
                    {(float) posX, (float) posY},
                    direccion, {velocidad * (float) cos(direccion), velocidad * (float) sin(direccion)},
                    (Tipo) enteroAleatorio(0, 2), TAM_2, limitesPantalla, color));
        }

    }
};


#endif //AST3ROIDS_ASTEROIDE_HPP
