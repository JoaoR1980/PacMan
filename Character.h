#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
protected:
    int x, y;          // Posi��o do personagem
    char sprite;       // Representa��o visual
    int colorPair;     // Cor do personagem
    char symbol;

public:
    Character(int startX, int startY, char symbol, int color);

    virtual void draw() = 0;// Tornamos draw() uma fun��o virtual pura
    virtual void move(int dx, int dy);

    virtual int getX() const;
    virtual int getY() const;

    virtual void updateState() = 0; // M�todo virtual puro, obrigat�rio em subclasses
    
    virtual ~Character() = default; // Defina um destrutor virtual para evitar problemas
};

#endif // CHARACTER_H
