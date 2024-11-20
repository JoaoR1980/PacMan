#ifndef FANTASMA_H
#define FANTASMA_H

#include "Mapa.h"

class Fantasma {
private:
    int x; // Posição X do fantasma
    int y; // Posição Y do fantasma
    char simbolo; // Símbolo usado para representar o fantasma

public:
    // ----------------------------------------------------------------------------------------------------------

    Fantasma(int posX, int posY, char simbolo = 'F');

    // ----------------------------------------------------------------------------------------------------------

    void moverEvasivo(int pacX, int pacY, const Mapa& mapa); // Move o fantasma de forma evasiva
    void moverInteligente(int pacX, int pacY, const Mapa& mapa); // Move o fantasma de forma inteligente
    void desenhar() const; // Desenha o fantasma na tela
    bool verificarColisao(int pacX, int pacY) const; // Verifica se colidiu com o Pac-Man

    // ----------------------------------------------------------------------------------------------------------

    int getX() const { return x; }
    int getY() const { return y; }
};

#endif
