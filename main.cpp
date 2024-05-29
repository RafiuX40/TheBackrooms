#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

int cellSize = 25; // Declaración de cellSizes

#include "Cabeceras/map.hpp"
#include "Cabeceras/Enemy.hpp"

int main()
{
<<<<<<< HEAD
    RenderWindow window(VideoMode(screenWidth, screenHeight), "RPG");
    window.setFramerateLimit(60);

    auto image = sf::Image{};
    if (!image.loadFromFile("Assets/pixil-frame-0.png"))
    {
    // Error handling...
    }

    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());


    Texture textura;
    textura.loadFromFile("Assets/pixil-frame-0.png");

    Sprite sprite;
    sprite.setTexture(textura);
    sprite.setOrigin(16,16);

=======
    RenderWindow window(VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(50);
    CircleShape shape(5.f);
    shape.setFillColor(Color::Blue);
>>>>>>> b333b29818a6bfa70383a19fd628673d0252cf08
    Vector2f playerPosition(100.f, 100.f);
    float playerSpeed = 5.0f;

    Enemy enemy(Vector2f(500.f, 500.f), 5.0f); // Creamos un enemigo en una posición y velocidad específicas

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
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
        if (newPlayerPosition.x < 0 || newPlayerPosition.x > screenWidth ||
            newPlayerPosition.y < 0 || newPlayerPosition.y > screenHeight)
        {
            // Si el jugador llega a una de las orillas de la ventana, cambiamos el mapa
            currentMapIndex = (currentMapIndex + 1) % (sizeof(worldMaps) / sizeof(worldMaps[0]));
            // Posicionamos al jugador en una posición inicial en el nuevo mapa
            newPlayerPosition = Vector2f(100.f, 100.f);
        }

        // Comprobamos colisiones con las paredes para el jugador
        int playerCellX = static_cast<int>(newPlayerPosition.x) / cellSize;
        int playerCellY = static_cast<int>(newPlayerPosition.y) / cellSize;
        if (worldMaps[currentMapIndex][playerCellY][playerCellX] != 0 && worldMaps[currentMapIndex][playerCellY][playerCellX] != 3)
        {
            // Si el jugador intenta moverse a una celda no permitida, no actualizamos su posición
            newPlayerPosition = playerPosition;
        }

        playerPosition = newPlayerPosition;

        // Actualizamos la posición del enemigo persiguiendo al jugador
        enemy.update(playerPosition);

        window.clear();

        // Dibujamos el mapa
        for (int i = 0; i < mapHeight; ++i)
        {
            for (int j = 0; j < mapWidth; ++j)
            {
                RectangleShape cell(Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);
                switch (worldMaps[currentMapIndex][i][j])
                {
                case 1:
                    cell.setFillColor(Color::White); // Pared
                    break;
                    case 3:
                    cell.setFillColor(Color::Red);  // da fuerza al player
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
