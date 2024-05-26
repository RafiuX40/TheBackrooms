#include <SFML/Graphics.hpp>
#include <cmath>


using namespace sf;

int cellSize = 25; // Declaración de cellSizes

#include "Cabeceras/map.hpp"
#include "Cabeceras/Enemy.hpp"

int main() {
    RenderWindow window(VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(50);
    CircleShape shape(5.f);
    shape.setFillColor(Color::Blue);
    Vector2f playerPosition(100.f, 100.f);
    float playerSpeed = 5.0f;

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

        // Comprobamos colisiones con las paredes para el jugador
        int playerCellX = static_cast<int>(newPlayerPosition.x + shape.getRadius()) / cellSize;
        int playerCellY = static_cast<int>(newPlayerPosition.y + shape.getRadius()) / cellSize;
        if (worldMap[playerCellY][playerCellX] != 0) {
            // Si el jugador intenta moverse a una celda no permitida, no actualizamos su posición
            newPlayerPosition = playerPosition;
        }

        playerPosition = newPlayerPosition;

        // Actualizamos la posición del enemigo persiguiendo al jugador
        enemy.update(playerPosition);

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

        enemy.draw(window);

        window.display();
    }

    return 0;
}
