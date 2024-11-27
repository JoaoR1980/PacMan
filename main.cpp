
/*PacMan/
├── main.cpp
├── Logic/
│   ├── GameLogic.h
│   ├── GameLogic.cpp
│   ├── PacMan.h
│   ├── PacMan.cpp
│   ├── Ghost.h
│   ├── Ghost.cpp
├── Interface/
│   ├── GameInterface.h
│   ├── GameInterface.cpp
│   ├── PDCursesInterface.h
│   ├── PDCursesInterface.cpp
├── Utils/
│   ├── LinkedList.h
│   ├── LinkedList.cpp
├── Makefile
*/

#include "GameLogic.h"

int main() {

    initscr();          // Inicializa a tela
    start_color();      // Inicializa o sistema de cores
    cbreak();           // Desativa o buffer de linha
    noecho();           // Desativa o eco de entrada
    curs_set(0);        // Desativa o cursor

    // Configuração de pares de cores
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Par 1: Cor de fundo preta, cor de texto amarela
    init_pair(2, COLOR_BLUE, COLOR_BLACK);   // Par 2: Cor de fundo preta, cor de texto azul
    init_pair(3, COLOR_CYAN, COLOR_BLACK);   // Par 3: Cor de fundo preta, cor de texto ciano

    //------------------------------------------------------------------------

    GameLogic game;

    game.initGame();

    while (true) {
        game.updateGame();
        //game.handleInput();
        int ch = getch();
        switch (ch) {
        case 'q': // Sair do jogo
            game.endGame(true);
            return 0;

        case KEY_UP:
            game.movePacman(0, -1);
            break;

        case KEY_DOWN:
            game.movePacman(0, 1);
            break;

        case KEY_LEFT:
            game.movePacman(-1, 0);
            break;

        case KEY_RIGHT:
            game.movePacman(1, 0);
            break;
        }
    }
    system("pause");
    return 0;
}
