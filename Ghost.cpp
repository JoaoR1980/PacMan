#include "Ghost.h"



Ghost::Ghost(int startX, int startY, char symbol, int color)
    : Character(startX, startY, 'G', startColor), state(NORMAL), vulnerableTimer(0), defeated(false), startColor(3) {}



void Ghost::setState(GhostState newState, int duration) {
    state = newState;
    vulnerableTimer = duration;
}

GhostState Ghost::getState() const {
    return state;
}

// Implementação do método updateState() para atualizar o estado do fantasma
void Ghost::updateState() {
    if (state == VULNERABLE && vulnerableTimer > 0) {
        --vulnerableTimer;
        if (vulnerableTimer == 0) {
            state = NORMAL; // Volta ao estado normal quando o tempo acaba
        }
    }
}

void Ghost::moveAutomatically(const PacMan& pacman, const Map& map, const std::vector<Ghost>& ghosts) {
    // Direções possíveis: cima, baixo, esquerda, direita
    int dx[] = { 0, 0, -1, 1 };  // Direções em X
    int dy[] = { -1, 1, 0, 0 };  // Direções em Y

    int melhorX = getX();
    int melhorY = getY();

    int initialDistance = pacman.powerMode ? 0 : INT_MAX;

    // Testar todas as 4 direções possíveis (cima, baixo, esquerda, direita)
    for (int i = 0; i < 4; ++i) {
        int novoX = getX() + dx[i];
        int novoY = getY() + dy[i];

        // Verifica se a posição é válida (caminhável) e dentro dos limites do mapa
        if (map.isWalkable(novoX, novoY)) {
            // Verificar se outro fantasma está a ocupar a posição
            bool ocupadoPorOutroFantasma = false;
            for (const auto& outroGhost : ghosts) {
                if (outroGhost.getX() == novoX && outroGhost.getY() == novoY) {
                    ocupadoPorOutroFantasma = true;
                    break;
                }
            }

            // Ignorar a posição se já estiver ocupada
            if (ocupadoPorOutroFantasma) {
                continue;
            }

            // Calcular a distância até o PacMan
            int distancia = std::abs(pacman.getX() - novoX) + std::abs(pacman.getY() - novoY);

           if (pacman.powerMode) {
                // Fugir: procurar a posição mais distante do PacMan
                if (distancia > initialDistance) {
                    initialDistance = distancia;
                    melhorX = novoX;
                    melhorY = novoY;
                }
            }
            else {
                // Aproximar-se: procurar a posição mais próxima do PacMan
                if (distancia < initialDistance) {
                    initialDistance = distancia;
                    melhorX = novoX;
                    melhorY = novoY;
                }
            }

        }
        
    }

    // Atualiza a posição do fantasma
    x = melhorX;
    y = melhorY;
}

void Ghost:: draw() {

    attron(COLOR_PAIR(startColor)); // Aplica a cor
    mvaddch(y, x, sprite);     // Desenha o fantasma na posição (x, y)
    attroff(COLOR_PAIR(startColor)); // Desativa a cor
}

bool Ghost::isDefeated() const {
    return defeated;  // A variável 'defeated' indica se o fantasma foi derrotado
}

void Ghost::setDefeated(bool state) { 
    defeated = state; 
}

