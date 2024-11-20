#ifndef PACMAN_H
#define PACMAN_H

#include "Mapa.h"

class PacMan {
private:

    //----------------------------------------------------------------------------------

    int x; // Posição X do Pac-Man
    int y; // Posição Y do Pac-Man
    char simbolo; // Símbolo usado para representar o Pac-Man
    int pontuacao; // Pontuação do jogador

public:

    // ---------------------------------------------------------------------------------

    PacMan(int posX = 1, int posY = 1, char simbolo = 'C');

    // ---------------------------------------------------------------------------------

    void mover(char direcao, const Mapa& mapa); // Move o Pac-Man
    //void desenhar() const; // Desenha o Pac-Man na tela
    void desenhar(bool powerUp) const;
    int getPontuacao() const { return pontuacao; } // Retorna a pontuação

    // ---------------------------------------------------------------------------------

    int getX() const { return x; }
    int getY() const { return y; }
};

#endif
