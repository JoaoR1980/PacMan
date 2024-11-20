#include "Fantasma.h"
#include <curses.h>
#include <cmath> // Para abs()

// ----------------------------------------------------------------------------------------------

Fantasma::Fantasma(int posX, int posY, char simbolo)
    : x(posX), y(posY), simbolo(simbolo) {}

// -------------------------  Move o fantasma de forma evasiva ----------------------------------

void Fantasma::moverEvasivo(int pacX, int pacY, const Mapa& mapa) {
    // Direções possíveis: cima, baixo, esquerda, direita
    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    int melhorX = x;
    int melhorY = y;
    int maiorDistancia = std::abs(pacX - x) + std::abs(pacY - y); // Distância atual

    // Testar todas as direções
    for (int i = 0; i < 4; ++i) {
        int novoX = x + dx[i];
        int novoY = y + dy[i];

        // Verifica se a posição é válida
        if (!mapa.verificarColisao(novoX, novoY)) {
            int distancia = std::abs(pacX - novoX) + std::abs(pacY - novoY);
            if (distancia > maiorDistancia) {
                maiorDistancia = distancia;
                melhorX = novoX;
                melhorY = novoY;
            }
        }
    }

    // Atualiza a posição para a melhor encontrada
    x = melhorX;
    y = melhorY;
}

// ---------------------------------------------------------------------------------------------

/*void Fantasma::desenhar() const {
    mvaddch(y, x, simbolo);
}*/

// ------------------------------------------------------------------------------------------------

void Fantasma::desenhar() const {
    attron(COLOR_PAIR(2)); // Ativar cor do fantasma
    mvaddch(y, x, simbolo); // Desenhar fantasma
    attroff(COLOR_PAIR(2)); // Desativar cor
}

// ------------------------------------------------------------------------------------------------

bool Fantasma::verificarColisao(int pacX, int pacY) const {
    return x == pacX && y == pacY;
}

// ----------------------------  mover fantasma de forma inteligente  -----------------------------

void Fantasma::moverInteligente(int pacX, int pacY, const Mapa& mapa) {
    // Direções possíveis: cima, baixo, esquerda, direita
    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    int melhorX = x;
    int melhorY = y;
    int menorDistancia = std::abs(pacX - x) + std::abs(pacY - y); // Distância atual

    // Testar todas as direções
    for (int i = 0; i < 4; ++i) {
        int novoX = x + dx[i];
        int novoY = y + dy[i];

        // Verifica se a posição é válida
        if (!mapa.verificarColisao(novoX, novoY)) {
            int distancia = std::abs(pacX - novoX) + std::abs(pacY - novoY);
            if (distancia < menorDistancia) {
                menorDistancia = distancia;
                melhorX = novoX;
                melhorY = novoY;
            }
        }
    }

    // Atualiza a posição para a melhor encontrada
    x = melhorX;
    y = melhorY;
}


