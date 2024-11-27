#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class GameInterface {
public:
    virtual void initialize() = 0;
    virtual void shutdown() = 0;
    virtual void draw(int x, int y, char symbol) = 0;
    virtual void clearScreen() = 0;
    virtual void refreshScreen() = 0;
    virtual char getInput() = 0;

    virtual ~GameInterface() {}
};

#endif
