#pragma once
#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "../Interface/GameInterface.h"
#include "Pacman.h"
#include "Ghost.h"

class GameLogic {
private:
    GameInterface* interface;
    Pacman pacman;
    std::vector<Ghost> ghosts;
    int score;
    bool gameOver;

public:
    GameLogic(GameInterface* interface);
    void initialize();
    void run();
    void update();
    void render();
};

#endif

