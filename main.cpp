#include <curses.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Mapa.h"
#include "PacMan.h"
#include "Fantasma.h"
#include <chrono> // Para medir o tempo de power-up
#include <thread>

// ------------------------------------------------------------------------------------------------

void pausa(int milissegundos) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milissegundos));
}

// ------------------------    Inicialização de cores   -------------------------------------------

void inicializarCores() {
    if (has_colors()) {
        start_color();
        // Definir combinações de cores (foreground, background)
        init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Pac-Man
        init_pair(2, COLOR_RED, COLOR_BLACK);    // Fantasmas
        init_pair(3, COLOR_BLUE, COLOR_BLACK);   // Labirinto
        init_pair(4, COLOR_WHITE, COLOR_BLACK);  // Texto padrão
        init_pair(5, COLOR_CYAN, COLOR_BLACK);   // Power-up
    }
}

// --------------------------------------------------------------------------------------

bool pacmanPowerUp = false;
std::chrono::steady_clock::time_point powerUpInicio;
int duracaoPowerUp = 10; // Em segundos

int main() {

    // ---------------   Inicializa PDCurses  -------------------------------------------

    initscr();            // Inicializa a tela
    noecho();             // Evita exibir entradas do teclado
    curs_set(0);          // Esconde o cursor
    inicializarCores();   // Inicializa as cores

    srand(time(nullptr)); // Inicializa a semente para números aleatórios

    // ----------------   Carregar o mapa  ----------------------------------------------
    Mapa mapa;
    if (!mapa.carregarDeArquivo("labirinto.txt")) {
        endwin();
        return 1;
    }

    // -----------------   Criar o Pac-Man  ---------------------------------------------
    PacMan pacman(1, 1, 'C');

    // ----------------    Criar os fantasmas  ------------------------------------------

    std::vector<Fantasma> fantasmas = {
        Fantasma(5, 5, 'F'),
        Fantasma(10, 3, 'F'),
        Fantasma(15, 6, 'F')
    };

    // -----------------   Loop principal do jogo  --------------------------------------
    char entrada;
    bool jogoAtivo = true;
    do {
        clear();

        // ------------  Desenhar o labirinto e o Pac-Man  ------------------------------

        mapa.desenhar();
        pacman.desenhar(pacmanPowerUp);

        // ------------  Desenhar os fantasmas  -----------------------------------------

        for (const auto& fantasma : fantasmas) {
            fantasma.desenhar();
        }

        // ------------  Exibir pontuação  ----------------------------------------------

        mvprintw(mapa.getAltura(), 0, "Pontuacao: %d", pacman.getPontuacao());

        // ----------   Verificar se o power-up ainda está ativo  -----------------------
        if (pacmanPowerUp) {
            auto agora = std::chrono::steady_clock::now();
            int tempoDecorrido = std::chrono::duration_cast<std::chrono::seconds>(agora - powerUpInicio).count();
            if (tempoDecorrido > duracaoPowerUp) {
                pacmanPowerUp = false; // Power-up expirou
            }
        }

        // ---------------   Atualizar a tela  ------------------------------------------

        refresh();

        // ---------------------  Capturar entrada do jogador  --------------------------

        entrada = getch();
        pacman.mover(entrada, mapa);

        // --------------------  Mover os fantasmas   -----------------------------------

        for (auto& fantasma : fantasmas) {
            if (pacmanPowerUp) {
                fantasma.moverEvasivo(pacman.getX(), pacman.getY(), mapa); // Evitar o Pac-Man
            }
            else {
                fantasma.moverInteligente(pacman.getX(), pacman.getY(), mapa); // Perseguir o Pac-Man
            }

            // -----------   Verificar colisão com o Pac-Man  ---------------------------

            if (fantasma.verificarColisao(pacman.getX(), pacman.getY())) {
                if (pacmanPowerUp) {
                    // Fantasma é derrotado; recomeça em posição inicial
                    fantasma = Fantasma(5, 5, 'F'); // Posição inicial do fantasma
                    for (int i = 0; i < 3; ++i) { // Piscar 3 vezes
                        attron(COLOR_PAIR(5)); // Cor especial
                        mvaddch(fantasma.getY(), fantasma.getX(), 'X'); // Exibir "explosão"
                        refresh();
                        pausa(100);
                        attroff(COLOR_PAIR(5));
                        clear(); // Limpa a tela temporariamente
                        refresh();
                        pausa(100);
                    }

                }
                else {
                    jogoAtivo = false; // Pac-Man foi alcançado
                    break;
                }
            }
        }
        for (auto& fantasma : fantasmas) {
            if (pacmanPowerUp) {
                fantasma.moverEvasivo(pacman.getX(), pacman.getY(), mapa);
            }
            else {
                fantasma.moverInteligente(pacman.getX(), pacman.getY(), mapa);
            }
            pausa(100); // Atraso de 100 ms para simular animação
        }


        // --------- Simular power-up (exemplo: se Pac-Man coletar um item especial -----------------

        if (entrada == 'p') { // Simula o Pac-Man ativando um power-up
            pacmanPowerUp = true;
            powerUpInicio = std::chrono::steady_clock::now();
        }

    } while (jogoAtivo && entrada != 'q'); // Sai do jogo ao pressionar 'q' ou em caso de derrota


    // ----------------------  Exibir mensagem de fim de jogo  --------------------------------------

    clear();
    if (!jogoAtivo) {
        mvprintw(mapa.getAltura() / 2, mapa.getLargura() / 2 - 5, "GAME OVER!");
    }
    else {
        mvprintw(mapa.getAltura() / 2, mapa.getLargura() / 2 - 5, "SAIU DO JOGO!");
    }
    refresh();
    getch();

    // Finaliza a interface
    endwin();

    return 0;
}




/*int main() {
	initscr(); // Initialize the curses library
	noecho(); // Don't echo user input to the screen
	cbreak(); // Disable line buffering
	keypad(stdscr, TRUE); // Enable special keys
	int x = COLS / 2; // Center the object horizontally
	int y = LINES / 2; // Center the object vertically
	int ch = 0; // To store user input
	while (ch != 'q') {
		clear(); // Clear the screen
		mvprintw(y, x, "X"); // Print the object at the current position
		refresh(); // Refresh the screen
		ch = getch(); // Get user input
		// Check user input and update object position
		switch (ch) {
		case KEY_UP:
			if (y > 0) y--;
			break;
		case KEY_DOWN:
			if (y < LINES - 1) y++;
			break;
		case KEY_LEFT:
			if (x > 0) x--;
			break;
		case KEY_RIGHT:
			if (x < COLS - 1) x++;
			break;
		}
	}
	endwin(); // End the curses library
	return 0;	
}*/