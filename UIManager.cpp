#include "UIManager.h"

void UIManager::initUI() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    initColors();
}

void UIManager::endUI() {
    endwin();
}

void UIManager::initColors() {
    if (has_colors()) {
        initscr();
        start_color();
        init_pair(1, COLOR_BLUE, COLOR_BLACK); // Paredes
        init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Pontos
        init_pair(3, COLOR_RED, COLOR_BLACK); // Pac-Man
        init_pair(4, COLOR_CYAN, COLOR_BLACK); // Fantasmas
        noecho();
        curs_set(0);
    }
}

void UIManager::drawBackground() {
    attron(COLOR_PAIR(1));
    for (int y = 0; y < LINES; y++) {
        for (int x = 0; x < COLS; x++) {
            mvaddch(y, x, ' ');
        }
    }
    attroff(COLOR_PAIR(1));
}

void UIManager::drawUI(int score, int lives) {
    box(stdscr, 0, 0); // Borda
    mvprintw(0, 2, "Score: %d", score);
    mvprintw(0, COLS - 12, "Lives: %d", lives);
}
