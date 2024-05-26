#ifndef Enemy_hpp
#define Enemy_hpp

#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy {
public:
    Enemy(Vector2f startPos, float spd) : position(startPos), speed(spd), shape(5.f) {
        shape.setFillColor(Color::Red); // Color del enemigo
    }

    void update(const Vector2f& playerPos) {
        // Calculamos el vector de dirección hacia el jugador
        Vector2f direction = playerPos - position;
        // Normalizamos el vector de dirección
        float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= magnitude;
        // Movemos al enemigo en dirección al jugador con una velocidad constante
        Vector2f newPosition = position + direction * speed;

        // Comprobamos colisiones con las paredes para el enemigo
        int newCellX = static_cast<int>(newPosition.x) / cellSize;
        int newCellY = static_cast<int>(newPosition.y) / cellSize;
        if (worldMap[newCellY][newCellX] != 0) {
            // Si el enemigo intenta moverse a una celda no permitida, no actualizamos su posición
            return;
        }

        position = newPosition;
    }

    const Vector2f& getPosition() const {
        return position;
    }

    void setPosition(const Vector2f& newPosition) {
        position = newPosition;
    }

    const FloatRect getGlobalBounds() const {
        return shape.getGlobalBounds();
    }

    void draw(RenderWindow& window) {
        shape.setPosition(position);
        window.draw(shape);
    }

private:
    Vector2f position;
    float speed;
    CircleShape shape; // Forma del enemigo
};

#endif