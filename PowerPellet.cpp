#include "PowerPellet.h"

// Construtor explicitamente definido, sem construtor padr�o
PowerPellet::PowerPellet(int startX, int startY, char symbol, int color)
    : Character(startX, startY, symbol, color) {}  // 'P' como s�mbolo, 2 como cor

void PowerPellet::draw(){
    if (!consumed) {
        attron(COLOR_PAIR(colorPair));
        mvaddch(y, x, sprite);  // Desenha o Power Pellet
        attroff(COLOR_PAIR(colorPair));
    }   
}

void PowerPellet::consume() {
    mvaddch(y, x, ' ');  // Remove da tela substituindo por um espa�o
    symbol = ' ';        // Atualiza o sprite para indicar que foi consumido
    consumed = true;
}

void PowerPellet::updateState(){
    // PowerPellets n�o precisam de l�gica de movimenta��o
}