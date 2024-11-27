#pragma once
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <curses.h>

class UIManager {
public:
    void initUI();
    void endUI();
    void initColors();
    void drawBackground();
    void drawUI(int score, int lives);
};

#endif // UIMANAGER_H

