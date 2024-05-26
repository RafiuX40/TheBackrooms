#include <SFML/Graphics.hpp>
#include <math.h>
#include "Cabeceras/map.hpp"

using namespace sf;

class Enemy {
public:
    Enemy(Vector2f startPos, float spd) : position(startPos), speed(spd) {}

    void update(const Vector2f& playerPos) {
        // Calculamos el vector de dirección hacia el jugador
        Vector2f direction = playerPos - position;
        // Normalizamos el vector de dirección
        float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= magnitude;
        // Movemos al enemigo en dirección al jugador
        position += direction * speed;
    }

    const Vector2f& getPosition() const {
        return position;
    }

private:
    Vector2f position;
    float speed;
};

int main() {
    RenderWindow window(VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(50);
    CircleShape shape(5.f); 
    shape.setFillColor(Color::Blue);
    Vector2f playerPosition(100.f, 100.f);
    float playerSpeed = 5.0f; 
    int cellSize = 25;

    Enemy enemy(Vector2f(500.f, 500.f), 3.0f); // Creamos un enemigo en una posición y velocidad específicas

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Movimiento del jugador
        Vector2f newPlayerPosition = playerPosition;
        if (Keyboard::isKeyPressed(Keyboard::W))
            newPlayerPosition.y -= playerSpeed;
        if (Keyboard::isKeyPressed(Keyboard::S))
            newPlayerPosition.y += playerSpeed;
        if (Keyboard::isKeyPressed(Keyboard::A))
            newPlayerPosition.x -= playerSpeed;
        if (Keyboard::isKeyPressed(Keyboard::D))
            newPlayerPosition.x += playerSpeed;
        
        // Limitamos la posición del jugador dentro de la ventana
        if (newPlayerPosition.x < 0)
            newPlayerPosition.x = 0;
        if (newPlayerPosition.y < 0)
            newPlayerPosition.y = 0;
        if (newPlayerPosition.x > window.getSize().x - shape.getRadius() * 2)
            newPlayerPosition.x = window.getSize().x - shape.getRadius() * 2;
        if (newPlayerPosition.y > window.getSize().y - shape.getRadius() * 2)
            newPlayerPosition.y = window.getSize().y - shape.getRadius() * 2;

        // Actualizamos la posición del enemigo persiguiendo al jugador
        enemy.update(newPlayerPosition);

        // Comprobamos si el jugador está lo suficientemente cerca del enemigo para hacer daño
        float distance = sqrt(pow(playerPosition.x - enemy.getPosition().x, 2) + pow(playerPosition.y - enemy.getPosition().y, 2));
        if (distance < 20) {
            // Aquí puedes agregar la lógica para hacer daño al enemigo
            // Por ejemplo, restar vida al enemigo o eliminarlo
        }

        playerPosition = newPlayerPosition;

        window.clear();

        // Dibujamos el mapa
        for (int i = 0; i < mapHeight; ++i) {
            for (int j = 0; j < mapWidth; ++j) {
                RectangleShape cell(Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);
                switch (worldMap[i][j]) {
                    case 1:
                        cell.setFillColor(Color::White); // Pared
                        break;
                    case 2:
                        cell.setFillColor(Color::Blue); // Otro tipo de celda
                        break;
                    case 3:
                        cell.setFillColor(Color::Yellow); // Otro tipo de celda
                        break;
                    case 4:
                        cell.setFillColor(Color::Red); // Celda peligrosa
                        break;
                    case 5:
                        cell.setFillColor(Color::Yellow); // Premio
                        break;
                         case 6:
                        cell.setFillColor(Color::Cyan); // Premio
                        break;
                    default:
                        cell.setFillColor(Color::Black); // Espacio vacío
                        break;
                }
                window.draw(cell);
            }
        }

        // Dibujamos al jugador y al enemigo
        shape.setPosition(playerPosition);
        window.draw(shape);

        CircleShape enemyShape(5.f);
        enemyShape.setFillColor(Color::Red);
        enemyShape.setPosition(enemy.getPosition());
        window.draw(enemyShape);

        window.display();
    }

    return 0;
}
