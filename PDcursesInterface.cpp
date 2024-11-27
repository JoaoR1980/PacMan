#include "PDCursesInterface.h"

void PDCursesInterface::initialize() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
}

void PDCursesInterface::shutdown() {
    endwin();
}

void PDCursesInterface::draw(int x, int y, char symbol) {
    mvaddch(y, x, symbol);
}

void PDCursesInterface::clearScreen() {
    clear();
}

void PDCursesInterface::refreshScreen() {
    refresh();
}

char PDCursesInterface::getInput() {
    int ch = getch();
    switch (ch) {
    case KEY_UP:    return 'U';
    case KEY_DOWN:  return 'D';
    case KEY_LEFT:  return 'L';
    case KEY_RIGHT: return 'R';
    default:        return 0;
    }
}

