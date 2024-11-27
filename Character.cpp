#include "Character.h"
#include <curses.h>

Character::Character(int startX, int startY, char symbol, int color)
    : x(startX), y(startY), sprite(symbol), colorPair(color) {}

void Character::draw() {
    attron(COLOR_PAIR(colorPair));
    mvaddch(y, x, sprite);
    attroff(COLOR_PAIR(colorPair));
}

void Character::move(int dx, int dy) {
    x += dx;
    y += dy;
}

int Character::getX() const {
    return x;
}

int Character::getY() const {
    return y;
}
