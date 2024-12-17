
#include "GameLogic.h"



// Construtor
GameLogic::GameLogic() : pacman(2, 2, '@', 2), score(0), lives(3), victory(false) {
    
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Pac-Man original (amarelo)
    init_pair(2, COLOR_RED, COLOR_BLACK);    // Fantasmas (vermelhos)
    init_pair(3, COLOR_BLUE, COLOR_BLACK);   // Pac-Man no modo Power (azul claro)
    init_pair(4, COLOR_GREEN, COLOR_BLACK);   // PowerPellets 
   
  
    cbreak();
    noecho();
    curs_set(0);

    // Adiciona fantasmas
    ghosts.emplace_back(10, 10, 'G', 2);
    ghosts.emplace_back(20, 10, 'G', 2);
    ghosts.emplace_back(30, 10, 'G', 2);
    ghosts.emplace_back(40, 10, 'G', 2);
    //ghosts.emplace_back(45, 10, 'G', 2);
    ghosts.emplace_back(50, 10, 'G', 2);

    // Adiciona Power Pellets
    powerPellets.emplace_back(7, 4, 'P', 4);
    powerPellets.emplace_back(25, 6, 'P', 4);
    powerPellets.emplace_back(51, 2, 'P', 4);
}

void GameLogic::initGame() {
    ui.initUI();
    map.loadMap("map.txt");
}

void GameLogic::updateGame() {
    ui.drawBackground();
    map.draw();

    // Atualiza o estado do Pac-Man
    char tile = map.getTile(pacman.getX(), pacman.getY());

    // Atualiza e desenha Power Pellets
    for (auto& powerPellet : powerPellets) {
        powerPellet.draw();
    }

    // Verifica se Pac-Man comeu um ponto ou uma Power Pellet
    if (tile == '.') {
        map.setTile(pacman.getX(), pacman.getY(), ' '); // Remove ponto
        score += 10; // Incrementa o placar
    }
    else if (tile == 'P') {
        map.setTile(pacman.getX(), pacman.getY(), ' '); // Remove Power Pellet
        pacman.activatePowerMode(); // Ativa o modo Power
        score += 50;
    }

    // Atualiza e desenha os fantasmas
    for (Ghost& ghost : ghosts) {
        ghost.updateState();
        ghost.moveAutomatically(pacman, map, ghosts);
        ghost.draw();
    }

    // Verifica a colisão entre Pac-Man e Fantasmas
    checkCollision();

    // Verifica se o modo Power deve ser desativado (depois das colisões)
    pacman.deactivetedPowerMode();
    pacman.draw();

    // Verifica condição de vitória
    checkVictory();

    // Atualiza a UI  - vidas
    ui.drawUI(score, lives);

    refresh();
}

/////////////////////////////////////////////////
void GameLogic::checkCollision() {
    // Verifica colisão com PowerPellets
    for (auto it = powerPellets.begin(); it != powerPellets.end();) {
        if (pacman.getX() == it->getX() && pacman.getY() == it->getY()) {
            it->consume();
            pacman.activatePowerMode();
            it = powerPellets.erase(it);
            pacman.draw();
        }
        else {
            ++it;
        }
    }

    // Verifica colisão com fantasmas
    for (auto it = ghosts.begin(); it != ghosts.end();) {
        if (pacman.getX() == it->getX() && pacman.getY() == it->getY()) {
            if (pacman.powerMode) {
                // Modo Power: Pac-Man "come" o fantasma
                it = ghosts.erase(it);  // Remove o fantasma da lista
                score += 200;           // Acrescenta 200 pontos
                pacman.draw();          // Redesenha Pac-Man
                continue;               // Evita avançar o iterador novamente
            }
            else {
                // Modo normal: Pac-Man perde uma vida
                lives--;

                if (lives == 0) {
                    endGame(false);  // Encerra o jogo por derrota
                    return;
                }
                

                // Reposiciona Pac-Man no spawn inicial
                pacman.setPosition(2,2);  // Define a posição inicial
                //pacman.resetDirection();                             // Reseta direção para parar ou iniciar
                pacman.draw();                                      // Redesenha Pac-Man

                // Pequeno delay para visualização do respawn (opcional)
                napms(500); // Pausa de 500ms para permitir recuperação visual

                break; // Sai do loop de verificação, já que a colisão foi tratada
            }
        }
        else {
            ++it;  // Avança o iterador
        }
    }
}

void GameLogic::checkVictory() {
    // Vitória se todos os fantasmas forem derrotados ou o placar atingir 2000 pontos
    if (ghosts.empty() || score >= 2000) {
        victory = true;
        endGame(true);
    }
}

void GameLogic::endGame(bool victory) {
    clear(); // Limpa a tela antes de exibir a mensagem
    if (victory) {
        mvprintw(LINES / 2, COLS / 2 - 6, "!! YOU WIN !!");
    }
    else {
        mvprintw(LINES / 2, COLS / 2 - 15, "!! GAME OVER! YOU LOST !!");
    }

    refresh();
    getch();  // Espera o jogador pressionar uma tecla
    endwin(); // Finaliza ncurses
    exit(0);  // Encerra o programa
}

void GameLogic::movePacman(int dx, int dy) {
    pacman.move(dx, dy, map);
    //pacman.movePacAutomatically(map);
    char tile = map.getTile(pacman.getX(), pacman.getY());
    if (tile == '.') {
        map.setTile(pacman.getX(), pacman.getY(), ' ');
        score += 10;
    }
    
}

bool GameLogic::isVictory() const {
    return victory;
}

/*void GameLogic::handleInput() {
    int ch = getch(); // Captura a entrada do jogador
    switch (ch) {
    case KEY_UP:
        pacman.queueDirection(0, -1); // Armazena o movimento para cima
        break;
    case KEY_DOWN:
        pacman.queueDirection(0, 1); // Armazena o movimento para baixo
        break;
    case KEY_LEFT:
        pacman.queueDirection(-1, 0); // Armazena o movimento para esquerda
        break;
    case KEY_RIGHT:
        pacman.queueDirection(1, 0); // Armazena o movimento para direita
        break;
    default:
        break;
    }
}*/




