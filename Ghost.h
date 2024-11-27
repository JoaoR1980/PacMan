#ifndef GHOST_H
#define GHOST_H

#include "Map.h"
#include "Character.h"
#include <cstdlib> // Necessário para rand
#include <curses.h>
#include "PacMan.h"



enum GhostState { NORMAL, VULNERABLE }; // Estados possíveis do fantasma

class Ghost : public Character {
    
private:
    int startColor; // cor original
    int endColor; // cor do pac-Man qunado em power mode

    GhostState state; // Estado atual do fantasma
    int vulnerableTimer; // Tempo restante no estado vulnerável

    PacMan pacman;  // Ponteiro para PacMan para seguir o Pac-Man
    Map map;

    bool defeated;

public:
    // Construtor
    Ghost(int startX, int startY, char symbol, int color);
    
    // Métodos específicos do fantasma
    void setState(GhostState newState, int duration = 0); // Altera o estado do fantasma
    GhostState getState() const;                         // Retorna o estado atual
    void updateState() override;                                  // Atualiza o estado (ex.: decrementa o timer)
    void moveAutomatically(const PacMan& pacman, const Map& map, const std::vector<Ghost>& ghosts);
    void draw();
    bool isDefeated() const;
    void setDefeated(bool state);

};

#endif // GHOST_H

