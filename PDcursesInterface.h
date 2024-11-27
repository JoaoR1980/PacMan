#ifndef PDCURSESINTERFACE_H
#define PDCURSESINTERFACE_H

#include "GameInterface.h"
#include <curses.h>

class PDCursesInterface : public GameInterface {
public:
    void initialize() override;
    void shutdown() override;
    void draw(int x, int y, char symbol) override;
    void clearScreen() override;
    void refreshScreen() override;
    char getInput() override;

    ~PDCursesInterface() {}
};

#endif
