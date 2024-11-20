#include "PacMan.h"
#include <curses.h> // Biblioteca PDCurses


// ------------------------------------------------------------------------------------------------

PacMan::PacMan(int posX, int posY, char simbolo)
    : x(posX), y(posY), simbolo(simbolo), pontuacao(0) {}

// ------------------    Move o Pac-Man   ---------------------------------------------------------

void PacMan::mover(char direcao, const Mapa& mapa) {
    int novoX = x;
    int novoY = y;

    // Calcula a nova posição com base na direção
    switch (direcao) {
    case 'w': // Cima
        novoY--;
        break;
    case 's': // Baixo
        novoY++;
        break;
    case 'a': // Esquerda
        novoX--;
        break;
    case 'd': // Direita
        novoX++;
        break;
    default:
        return; // Direção inválida
    }

    // Verifica se a nova posição é válida
    if (!mapa.verificarColisao(novoX, novoY)) {
        x = novoX;
        y = novoY;

        // Verifica se há um ponto ('.') na nova posição
        if (mapa.obterElemento(x, y) == '.') {
            pontuacao++;
        }
    }
}

// Desenha o Pac-Man na tela
/*void PacMan::desenhar() const {
    mvaddch(y, x, simbolo); // Desenha o Pac-Man na posição atual
}*/

/*void PacMan::desenhar() const {
    attron(COLOR_PAIR(1)); // Ativar cor do Pac-Man
    mvaddch(y, x, 'P');    // Desenhar Pac-Man
    attroff(COLOR_PAIR(1)); // Desativar cor
}*/

// ------------------------------------------------------------------------------------------------

void PacMan::desenhar(bool powerUp) const {
    if (powerUp) {
        attron(COLOR_PAIR(5)); // Ativar cor de power-up
    }
    else {
        attron(COLOR_PAIR(1)); // Cor padrão do Pac-Man
    }
    mvaddch(y, x, 'P'); // Desenhar Pac-Man
    attroff(COLOR_PAIR(powerUp ? 5 : 1)); // Desativar cor
}