#include "Mapa.h"
#include <fstream>
#include <iostream>
#include <curses.h> // Biblioteca PDCurses

// ------------------------------------------------------------------------------------------------

Mapa::Mapa() : largura(0), altura(0) {}

// ---------------------------------  Carrega o labirinto de um ficheiro --------------------------

bool Mapa::carregarDeArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return false;
    }

    labirinto.clear();
    std::string linha;
    while (std::getline(arquivo, linha)) {
        labirinto.push_back(linha);
        if (linha.length() > largura) {
            largura = linha.length();
        }
    }
    altura = labirinto.size();
    arquivo.close();
    return true;
}

// ------------------------------------------------------------------------------------------------

// Desenha o labirinto na tela usando pdcurses
/*void Mapa::desenhar() const {
    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {
            mvaddch(y, x, labirinto[y][x]);
        }
    }
    refresh();
}*/

// ------------------------------------------------------------------------------------------------

void Mapa::desenhar() const {
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            if (labirinto[i][j] == '#') {
                attron(COLOR_PAIR(3)); // Cor do labirinto
                mvaddch(i, j, '#');   // Parede
                attroff(COLOR_PAIR(3));
            }
            else if (labirinto[i][j] == '.') {
                mvaddch(i, j, '.');   // Ponto
            }
        }
    }
}

// --------------------- Verifica colisão (retorna true se for obstáculo, false se não for) -------

bool Mapa::verificarColisao(int x, int y) const {
    if (x < 0 || y < 0 || x >= largura || y >= altura) {
        return true; // Fora dos limites do mapa é considerado obstáculo
    }
    return labirinto[y][x] == '#'; // '#' é considerado obstáculo no exemplo
}

// ------------    Obtém o caractere em uma posição do labirinto   ---------------------------------

char Mapa::obterElemento(int x, int y) const {
    if (x < 0 || y < 0 || x >= largura || y >= altura) {
        return ' '; // Fora dos limites
    }
    return labirinto[y][x];
}

// -------------------  Define um caractere em uma posição do labirinto  ---------------------------

void Mapa::setElemento(int x, int y, char elemento) {
    if (x >= 0 && y >= 0 && x < largura && y < altura) {
        labirinto[y][x] = elemento;
    }
}
