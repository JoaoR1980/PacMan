#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>


class Map {
private:
    std::vector<std::string> layout; // Representa��o do labirinto

public:
    
    Map();// Construtor
    void loadMap(const std::string& filename);// Carrega o labirinto de um arquivo   
    void draw() const; // Desenha o labirinto na tela   
    char getTile(int x, int y) const;// Retorna o caractere em uma posi��o espec�fica  
    void setTile(int x, int y, char newTile);// Atualiza o caractere em uma posi��o espec�fica  
    bool isWalkable(int x, int y) const;// Verifica se uma posi��o � v�lida para o movimento   
    int countDots() const;// Retorna o n�mero de pontos restantes no labirinto   
};

#endif // MAP_H
