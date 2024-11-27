#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "UIManager.h"
#include "Map.h"
#include "PacMan.h"
#include "Ghost.h"
#include <vector>
#include "ctime"
#include "PowerPellet.h"

class GameLogic {
private:
    UIManager ui;
    Map map;
    PacMan pacman; // Instância de PacMan
    std::vector<Ghost> ghosts; // Vetor de instâncias de Ghost
    std::vector<PowerPellet> powerPellets;  // Usando um vetor para armazenar múltiplos Power Pellets
    int score;
    int lives;
    bool victory; // Nova variável para rastrear se o Pac-Man venceu

public:
    GameLogic();

    void initGame();
    void updateGame();
    void movePacman(int dx, int dy);
    void endGame(bool vitoty);
    void checkCollisionWithGhost();
    bool isVictory() const; // Getter para verificar vitória
    void checkVictory();                       // Método de verificação de vitória
    void handleInput();
};

#endif // GAMELOGIC_H
