#include "Map.h"
#include <fstream>
#include <curses.h> // Para mvaddch
#include <stdexcept>

Map::Map() {}

void Map::loadMap(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Erro ao abrir o arquivo do mapa.");
    }

    layout.clear();
    std::string line;
    while (std::getline(file, line)) {
        layout.push_back(line);
    }

    file.close();
}

void Map::draw() const {
    for (size_t y = 0; y < layout.size(); ++y) {
        for (size_t x = 0; x < layout[y].size(); ++x) {
            char tile = layout[y][x];
            switch (tile) {
            case '#':
                attron(COLOR_PAIR(1)); // Paredes com cor
                mvaddch(y, x, tile);
                attroff(COLOR_PAIR(1));
                break;
            case '.':
                attron(COLOR_PAIR(2)); // Pontos com cor
                mvaddch(y, x, tile);
                attroff(COLOR_PAIR(2));
                break;
            default:
                mvaddch(y, x, tile); // Outros caracteres
                break;
            }
        }
    }
    //----------------------------------------------------------
    
}

char Map::getTile(int x, int y) const {
    if (y < 0 || y >= static_cast<int>(layout.size()) || x < 0 || x >= static_cast<int>(layout[y].size())) {
        return '#'; // Fora dos limites, considere como parede
    }
    return layout[y][x];
}

void Map::setTile(int x, int y, char newTile) {
    if (y >= 0 && y < static_cast<int>(layout.size()) && x >= 0 && x < static_cast<int>(layout[y].size())) {
        layout[y][x] = newTile;
    }
}

bool Map::isWalkable(int x, int y) const {
    char tile = getTile(x, y);
    return tile == '.' || tile == ' '; // Caminhável se for ponto ou espaço
    
}

int Map::countDots() const {
    int count = 0;
    for (const auto& row : layout) {
        count += std::count(row.begin(), row.end(), '.');
    }
    return count;
}

