#ifndef POWERPELLET_H
#define POWERPELLET_H

#include "Character.h"
#include <curses.h>

class PowerPellet : public Character {
    bool consumed = false;
public:
    // Construtor explicitamente definido, sem construtor padrão
    PowerPellet(int startX, int startY, char symbol, int color);
    void draw() override;
    void consume(); 
    void updateState() override;
};

#endif // POWERPELLET_H
