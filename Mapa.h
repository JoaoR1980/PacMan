#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <string>

class Mapa {
private:

    // ----------------------------------------------------------------------------------------------

    std::vector<std::string> labirinto; // Armazena o labirinto linha por linha
    int largura; // Largura do labirinto
    int altura;  // Altura do labirinto

public:
    // ----------------------------------------------------------------------------------------------

    Mapa();

    // ----------------------------------------------------------------------------------------------

    bool carregarDeArquivo(const std::string& nomeArquivo); // Carrega labirinto de um ficheiro
    void desenhar() const; // Exibe o labirinto usando pdcurses
    bool verificarColisao(int x, int y) const; // Verifica se a posi��o � um obst�culo
    char obterElemento(int x, int y) const; // Obt�m o caractere em uma posi��o
    void setElemento(int x, int y, char elemento); // Define um caractere em uma posi��o

    // ----------------------------------------------------------------------------------------------

    int getLargura() const { return largura; }
    int getAltura() const { return altura; }
};

#endif
