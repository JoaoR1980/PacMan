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
    PacMan pacman; // Inst�ncia de PacMan
    std::vector<Ghost> ghosts; // Vetor de inst�ncias de Ghost
    std::vector<PowerPellet> powerPellets;  // Vetor de inst�ncias de Power Pellets
    int score;
    int lives;
    bool victory; // vari�vel para verificar se o Pac-Man venceu

public:
    GameLogic();

    void initGame();
    void updateGame();
    void movePacman(int dx, int dy);
    void endGame(bool vitoty);
    void checkCollision();
    bool isVictory() const; // Getter para verificar vit�ria
    void checkVictory();    // M�todo de verifica��o de vit�ria
    //void handleInput();
};

#endif // GAMELOGIC_H
