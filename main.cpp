#include <SFML/Graphics.hpp>
#include "map.hpp"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(50);
    CircleShape shape(5.f); // Reducí el tamaño del círculo para que sea más visible en la ventana pequeña
    shape.setFillColor(Color::White);

    // Posición inicial del personaje
    Vector2f position(100.f, 100.f);
    float speed = 5.0f; // Velocidad de movimiento del personaje

    // Tamaño de cada celda en el mapa
    int cellSize = 25;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Movimiento del personaje
        Vector2f newPosition = position;
        if (Keyboard::isKeyPressed(Keyboard::W))
            newPosition.y -= speed;
        if (Keyboard::isKeyPressed(Keyboard::S))
            newPosition.y += speed;
        if (Keyboard::isKeyPressed(Keyboard::A))
            newPosition.x -= speed;
        if (Keyboard::isKeyPressed(Keyboard::D))
            newPosition.x += speed;
            
        // Limitar la posición del personaje para que no salga de la ventana
        if (newPosition.x < 0)
            newPosition.x = 0;
        if (newPosition.y < 0)
            newPosition.y = 0;
        if (newPosition.x > window.getSize().x - shape.getRadius() * 2) // Resta el radio del círculo para ajustar el límite derecho
            newPosition.x = window.getSize().x - shape.getRadius() * 2;
        if (newPosition.y > window.getSize().y - shape.getRadius() * 2) // Resta el radio del círculo para ajustar el límite inferior
            newPosition.y = window.getSize().y - shape.getRadius() * 2;

        // Obtener la celda actual y la nueva celda del mapa
        int currentCellX = static_cast<int>(position.x + shape.getRadius()) / cellSize;
        int currentCellY = static_cast<int>(position.y + shape.getRadius()) / cellSize;
        int newCellX = static_cast<int>(newPosition.x + shape.getRadius()) / cellSize;
        int newCellY = static_cast<int>(newPosition.y + shape.getRadius()) / cellSize;

        // Comprobar colisiones con el mapa
        if (worldMap[newCellY][newCellX] == 5) {
            // El jugador llega a la celda roja (gana el juego)
            shape.setFillColor(Color::Green); // Cambia el color para indicar victoria
        } else if (worldMap[newCellY][newCellX] != 0) {
            // Si el jugador intenta moverse a una celda no permitida, no actualiza su posición
            newPosition = position;
        }

        // Actualizar la posición del personaje solo si no colisiona con una pared
        position = newPosition;
        shape.setPosition(position);

        window.clear();

        // Dibujar el mapa
        for (int i = 0; i < mapHeight; ++i)
        {
            for (int j = 0; j < mapWidth; ++j)
            {
                RectangleShape cell(Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);

                switch (worldMap[i][j])
                {
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

        window.draw(shape);
        window.display();
    }

    return 0;
}
