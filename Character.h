#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
protected:
    int x, y;          // Posição do personagem
    char sprite;       // Representação visual
    int colorPair;     // Cor do personagem
    char symbol;

public:
    Character(int startX, int startY, char symbol, int color);

    virtual void draw() = 0;// Tornamos draw() uma função virtual pura
    virtual void move(int dx, int dy);

    virtual int getX() const;
    virtual int getY() const;

    virtual void updateState() = 0; // Método virtual puro, obrigatório em subclasses
    
    virtual ~Character() = default; // Defina um destrutor virtual para evitar problemas
};

#endif // CHARACTER_H
