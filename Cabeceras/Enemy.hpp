#ifndef Enemy_hpp
#define Enemy_hpp

#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy
{
public:
    Enemy(Vector2f startPos, float spd) : position(startPos), speed(spd), health(50)
    {
        enemy.setOrigin(16,13);
    }

    void update(const Vector2f &playerPos)
    {
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
        if (worldMaps[currentMapIndex][newCellY][newCellX] != 0)
        {
            // Si el enemigo intenta moverse a una celda no permitida, no actualizamos su posición
            return;
        }

        position = newPosition;
    }

    const Vector2f &getPosition() const
    {
        return position;
    }

    void setPosition(const Vector2f &newPosition)
    {
        position = newPosition;
    }

    const FloatRect getGlobalBounds() const
    {
        return enemy.getGlobalBounds();
    }

    void draw(RenderWindow &window)
    {
        Texture enemyT;
        enemyT.loadFromFile("Assets/Skinsteler.png");
        enemy.setPosition(position);
        enemy.setTexture(enemyT);
        window.draw(enemy);
    }

    void reduceHealth(float amount) {
        health -= amount;
        if (health <= 0) {
            position = Vector2f(-1000.f, -1000.f);
        }
    }

private:
    Vector2f position;
    float speed;
    Sprite enemy; // Forma del enemigo
    int health;
};

#endif