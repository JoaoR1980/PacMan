#include "PacMan.h"
#define POWER_MODE_DURATION 10 // Modo Power dura 10 segundos



PacMan::PacMan(int startX, int startY, char symbol, int color)
    : Character(startX, startY, symbol, color), isInvulnerable(false), invulnerabilityTimer(0), powerMode(false), powerModeStartTime(0), originalColor(color), powerColor(3) {}

PacMan::PacMan() : Character(0, 0, '@', 3) { // Um construtor padr�o que inicializa o PacMan em (0, 0)
    // Inicializa��o adicional, se necess�rio
}

void PacMan::setInvulnerable(bool state, int duration) {
    isInvulnerable = state;
    invulnerabilityTimer = duration;
}

bool PacMan::getInvulnerable() const {
    return isInvulnerable;
}

void PacMan::updateState() {
    if (isInvulnerable && invulnerabilityTimer > 0) {
        --invulnerabilityTimer;
        if (invulnerabilityTimer == 0) {
            isInvulnerable = false; // Perde a invulnerabilidade quando o tempo acaba
        }
    }
}
void PacMan::move(int dx, int dy, const Map& map) {
    int newX = x + dx;
    int newY = y + dy;

    // Verifica se o novo local � caminh�vel
    if (map.isWalkable(newX, newY)) {
        x = newX;
        y = newY;
    }
}
void PacMan::activatePowerMode() { 
    powerMode = true; 
    powerModeStartTime = time(0); // Armazena o tempo de ativa��o do modo Power
}
void PacMan::deactivetedPowerMode() { 
    if (powerMode && (time(0) - powerModeStartTime >= POWER_MODE_DURATION)) {
        powerMode = false;
    }
}
void PacMan::draw(){
    if (powerMode) {
        attron(COLOR_PAIR(powerColor)); // Muda a cor para a cor do Power Mode
    }
    else {
        attron(COLOR_PAIR(originalColor)); // Mantenha a cor original
    }
    mvaddch(y, x, sprite); // Desenha o Pac-Man
    attroff(COLOR_PAIR(originalColor)); // Restaura a cor original
    attroff(COLOR_PAIR(powerColor)); // Restaura a cor do Power Mode
}

void PacMan::updateState(const Map& map) {
    // Tenta trocar para a dire��o armazenada (se existir)
    if (queuedDirectionX != 0 || queuedDirectionY != 0) {
        int queuedX = x + queuedDirectionX;
        int queuedY = y + queuedDirectionY;

        if (map.isWalkable(queuedX, queuedY)) {
            // Atualiza para a nova dire��o
            currentDirectionX = queuedDirectionX;
            currentDirectionY = queuedDirectionY;

            // Reseta a dire��o armazenada
            queuedDirectionX = 0;
            queuedDirectionY = 0;
        }
    }

    // Move na dire��o atual
    int newX = x + currentDirectionX;
    int newY = y + currentDirectionY;

    if (map.isWalkable(newX, newY)) {
        x = newX;
        y = newY;
    }
    else {
        // Para se encontrar um obst�culo
        currentDirectionX = 0;
        currentDirectionY = 0;
    }
}


void PacMan::queueDirection(int dx, int dy) {
    // Adiciona a dire��o � fila, se n�o for a mesma da �ltima dire��o
    queuedDirectionX = dx;
    queuedDirectionY = dy;
}

