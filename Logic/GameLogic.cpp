#include "GameLogic.h"

GameLogic::GameLogic(GameInterface* iface) : interface(iface), score(0), gameOver(false) {
    initialize();
}

void GameLogic::initialize() {
    pacman = Pacman(5, 5); // Posiciona o Pacman
    ghosts.push_back(Ghost(10, 10)); // Adiciona um fantasma
}

void GameLogic::run() {
    while (!gameOver) {
        interface->clearScreen();
        update();
        render();
        interface->refreshScreen();
        interface->wait(100); // Delay para movimentação
    }
}

void GameLogic::update() {
    int input = interface->getInput();
    pacman.move(input);

    for (auto& ghost : ghosts) {
        ghost.move(); // Movimento automático dos fantasmas
        if (pacman.getPosition() == ghost.getPosition()) {
            gameOver = true;
        }
    }
}

void GameLogic::render() {
    interface->drawCharacter(pacman.getX(), pacman.getY(), '@');
    for (const auto& ghost : ghosts) {
        interface->drawCharacter(ghost.getX(), ghost.getY(), 'G');
    }
}
