
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
    pacman.updateState(map); // Movimenta o PacMan continuamente
    
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
        pacman.activatePowerMode();
        pacman.draw();
        score += 50;
    }

    pacman.deactivetedPowerMode(); // Verifica se o modo Power deve ser desativado
    pacman.draw();

    // Atualiza e desenha os fantasmas
    for (Ghost& ghost : ghosts) {
        ghost.updateState();
        ghost.moveAutomatically(pacman, map, ghosts);
        ghost.draw();
    }

    // Verifica a colisão entre Pac-Man e Fantasmas
    checkCollisionWithGhost();

    // Verifica condição de vitória
    checkVictory();

    // Atualiza a UI do placar e vidas
    ui.drawUI(score, lives);

    refresh();
}

void GameLogic::checkCollisionWithGhost() {
    // Verifica colisão com Power Pellets
    for (auto it = powerPellets.begin(); it != powerPellets.end();) {
        if (pacman.getX() == it->getX() && pacman.getY() == it->getY()) {
            it->consume();
            pacman.activatePowerMode();
            it = powerPellets.erase(it);
        }
        else {
            ++it;
        }
    }

    // Verifica colisão com fantasmas
    for (auto it = ghosts.begin(); it != ghosts.end();) {
        if (pacman.getX() == it->getX() && pacman.getY() == it->getY()) {
            if (!pacman.powerMode) {

                lives--;              
                pacman.draw();               
                
            }if(lives == 0){
                 
                    endGame(false);
                    
                    return;
                    system("pause");
            }
            else {
                map.setTile(it->getX(), it->getY(), ' '); // Remove do mapa
                it = ghosts.erase(it);                   // Remove do vetor
                score += 200;
                continue; // Evita avançar o iterador novamente
            }
        }
        ++it; // Avança o iterador
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
    char tile = map.getTile(pacman.getX(), pacman.getY());
    if (tile == '.') {
        map.setTile(pacman.getX(), pacman.getY(), ' ');
        score += 10;
    }
}

bool GameLogic::isVictory() const {
    return victory;
}

void GameLogic::handleInput() {
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
}




/*GameLogic::GameLogic() : pacman(10, 10, '@', 2), score(0), lives(3){
    initscr();               // Inicializa a biblioteca ncurses
    start_color();           // Ativa a funcionalidade de cores
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Pac-Man original (amarelo)
    init_pair(2, COLOR_RED, COLOR_BLACK);    // Fantasmas (vermelhos)
    init_pair(3, COLOR_BLUE, COLOR_BLACK);   // Pac-Man no modo Power (azul claro)
    init_pair(4, COLOR_BLUE, COLOR_BLACK);   // Pac-Man no modo Power (azul claro)
    cbreak();                // Desativa o buffer de linha
    noecho();                // Não exibe a entrada do usuário
    curs_set(0);             // Desativa o cursor

    // Adiciona fantasmas
    ghosts.emplace_back(30, 20, 'G', 2);
    ghosts.emplace_back(32, 20, 'G', 2);
    ghosts.emplace_back(34, 20, 'G', 2);
    ghosts.emplace_back(36, 20, 'G', 2);
    ghosts.emplace_back(38, 20, 'G', 2);
    ghosts.emplace_back(40, 20, 'G', 2);
    // Adiciona Pellets
    powerPellets.emplace_back(70,10,'P',4);
    powerPellets.emplace_back(65,24,'P',4);
    powerPellets.emplace_back(20,24,'P',4);

}


void GameLogic::initGame() {
    ui.initUI();
    map.loadMap("map.txt");
}

void GameLogic::updateGame() {
    ui.drawBackground();
    map.draw();

    // Atualiza o estado do Pac-Man
    pacman.updateState();
    char tile = map.getTile(pacman.getX(), pacman.getY());

    // Atualizar e desenhar Power Pellets
    for (auto& pellet : powerPellets) {
        pellet.draw();
    }

    // Verifica se Pac-Man comeu um ponto ou uma Power Pellet
    if (tile == '.') {
        map.setTile(pacman.getX(), pacman.getY(), ' '); // Remove ponto
        score += 10; // Incrementa o placar
    }
    else if (tile == 'P') { // verifica se o pac-man comeu 'P' seja a Power Pellet
        map.setTile(pacman.getX(), pacman.getY(), ' '); // Remove Power Pellet
        pacman.activatePowerMode(); // Ativa o modo Power
        score += 50; // Incrementa o placar
        
    }

    pacman.deactivetedPowerMode(); // Verifica se o modo Power deve ser desativado

    pacman.draw();

    // Atualiza e desenha os fantasmas
    for (Ghost& ghost : ghosts) {
        ghost.updateState();
        //ghost.moveAutomatically(map); // Passa o mapa para verificar colisões
        ghost.moveAutomatically(pacman, map);
        ghost.draw();
    }

    // Verifica a colisão entre Pac-Man e Fantasmas
    checkCollisionWithGhost();

    // Verifica condição de vitória
    checkVictory();

    // Atualiza a UI do placar e vidas
    ui.drawUI(score, lives);
    refresh();
}

void GameLogic::endGame(bool vitory ) {
    checkVictory();
    if (!vitory) {
        //mvprintw(10, 10, "!! WINNER !!");
        mvprintw(LINES / 2, COLS / 2 - 5, "!! GAME OVER !!");
    }
   // else {
        //mvprintw(LINES / 2, COLS / 2 - 5, "!! GAME OVER !!");
    //}

    refresh();
    getch(); // Espera o jogador pressionar uma tecla antes de sair
    endwin(); // Finaliza o ncurses
    exit(0); // Encerra o jogo
    ui.endUI();
}

void GameLogic::movePacman(int dx, int dy) {
    pacman.move(dx, dy, map); // Passa o mapa para verificar colisões

    // Verifica se Pac-Man comeu um ponto
    char tile = map.getTile(pacman.getX(), pacman.getY());
    if (tile == '.') {
        map.setTile(pacman.getX(), pacman.getY(), ' '); // Remove ponto do mapa
        score += 10; // Incrementa o placar
    }
}


void GameLogic::checkCollisionWithGhost(){

    // Verifica colisão com Power Pellets
    for (auto it = powerPellets.begin(); it != powerPellets.end(); ) {
        if (pacman.getX() == it->getX() && pacman.getY() == it->getY()) {
            it->consume();               // Faz o Power Pellet desaparecer
            pacman.activatePowerMode();  // Ativa o modo de poder do Pac-Man
            it = powerPellets.erase(it); // Remove o Power Pellet do vetor
            
        }
        else {
            ++it;  // Avança no vetor
        }
    }


    // 1. Verificar colisão com os fantasmas
    for (auto it = ghosts.begin(); it != ghosts.end();) {  // Iterador para manipular o array
        Ghost& ghost = *it;  // Referência ao fantasma atual

        // Verifica se o Pac-Man está na mesma posição que um fantasma
        if (pacman.getX() == ghost.getX() && pacman.getY() == ghost.getY()) {
            if (!pacman.powerMode) {
                endGame(true);  // Finaliza o jogo se não estiver no modo Power
                return;
            }
            else {
                // Remove o fantasma do mapa
                map.setTile(ghost.getX(), ghost.getY(), ' ');

                // Remove o fantasma do array
                it = ghosts.erase(it); // Apaga o fantasma e avança o iterador
                if (ghosts.empty() || score >= 2000) {
                    ghost.setDefeated(true);// Define o estado de vitória
                    endGame(true);      // Finaliza o jogo com a vitória
                }
                score += 200; // Incrementa o placar
                continue;     // Evita avançar o iterador novamente
            }
        }
        ++it;  // Avança o iterador se não foi apagado
    }  
}
bool GameLogic::isVictory() const { return victory; }

void GameLogic::checkVictory() {

    if (ghosts.empty() || score >= 2000) {
        victory = true; // Define o estado de vitória
        endGame(true);      // Finaliza o jogo com a vitória
        mvprintw(10, 10, "!! WINNER !!");
    }
   
}*/
    