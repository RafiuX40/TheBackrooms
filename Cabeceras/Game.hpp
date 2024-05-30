#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib> // Para generar números aleatorios
using namespace std;
using namespace sf;
int cellSize = 25; // Declaración de cellSizes
#include "map.hpp"
#include "Enemy.hpp"

void Game()
{
    RenderWindow window(VideoMode(screenWidth, screenHeight), "The Backrooms");
    window.setFramerateLimit(60);

    auto image = sf::Image{};
    if (!image.loadFromFile("Assets/Logo.png"))
    {
        // Error handling...
    }

    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    Texture textura;
    textura.loadFromFile("Assets/Player-stop.png");

    Texture walkTexture1;
    walkTexture1.loadFromFile("Assets/Walk-1.png");

    Texture walkTexture2;
    walkTexture2.loadFromFile("Assets/Walk-2.png");

    vector<Texture> playerWalkTextures = {walkTexture1, textura, walkTexture2}; // Vector de texturas de la animación

    int currentWalkFrame = 0; // Índice de la textura actual de la animación
    bool isWalking = false;   // Estado de la animación

    Sprite sprite;
    sprite.setTexture(textura);
    sprite.setOrigin(16, 13);

    Texture background;
    background.loadFromFile("Assets/pixilart-drawing.png");

    Sprite fondo;
    fondo.setTexture(background);

    Vector2f playerPosition(100.f, 100.f);
    float playerSpeed = 5.0f;

    Enemy enemy(Vector2f(500.f, 500.f), 3.0f); // Creamos un enemigo en una posición y velocidad específicas
    Enemy enemy2(Vector2f(500.f, 500.f), 3.0f);

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

        if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::S) ||
            Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D))
        {
            isWalking = true; // El jugador está caminando si alguna tecla de movimiento está presionada
        }
        else
        {
            isWalking = false; // El jugador no está caminando si ninguna tecla de movimiento está presionada
        }

        if (isWalking)
        {
            // Cambiar la textura del jugador para simular la animación de caminar
            sprite.setTexture(playerWalkTextures[currentWalkFrame]);
            // Incrementar el índice del frame de la animación
            currentWalkFrame = (currentWalkFrame + 1) % playerWalkTextures.size();
        }
        else
        {
            // El jugador no está caminando, usar la textura estática
            sprite.setTexture(textura);
        }

        // Limitamos la posición del jugador dentro de la ventana
        if (newPlayerPosition.x < 0 || newPlayerPosition.x > screenWidth ||
            newPlayerPosition.y <= -cellSize || newPlayerPosition.y > screenHeight)
        {
            // Determinamos qué orilla ha alcanzado el jugador y ajustamos la posición del jugador
            if (newPlayerPosition.x < 0)
            { // Límite izquierdo
                currentMapIndex = (currentMapIndex + 3) % (sizeof(worldMaps) / sizeof(worldMaps[0]));
                newPlayerPosition.x = screenWidth - 1; // Aparecer en el lado contrario
            }
            else if (newPlayerPosition.x > screenWidth)
            { // Límite derecho
                currentMapIndex = (currentMapIndex + 1) % (sizeof(worldMaps) / sizeof(worldMaps[0]));
                newPlayerPosition.x = 0; // Aparecer en el lado contrario
            }
            else if (newPlayerPosition.y <= -cellSize)
            { // Límite superior
                currentMapIndex = (currentMapIndex + 2) % (sizeof(worldMaps) / sizeof(worldMaps[0]));
                newPlayerPosition.y = screenHeight - 1; // Aparecer en el lado contrario
            }
            else if (newPlayerPosition.y > screenHeight)
            { // Límite inferior
                currentMapIndex = (currentMapIndex + 4) % (sizeof(worldMaps) / sizeof(worldMaps[0]));
                newPlayerPosition.y = 0; // Aparecer en el lado contrario
            }

            // Generamos una posición aleatoria para el enemigo dentro del nuevo mapa
            srand(time(NULL)); // Inicializamos la semilla del generador de números aleatorios
            int randomX = rand() % screenWidth;
            int randomX2;
            do{
                randomX2 = rand() % screenWidth;
            }while(randomX2 == randomX);

            int randomY = rand() % screenHeight;
            int randomY2;

            do
            {
                randomY2 = rand() % screenHeight;
            } while (randomY2 == randomY);
            

            

            enemy.setPosition(Vector2f(randomX, randomY));
            enemy2.setPosition(Vector2f(randomX2, randomY2));
        }

        // Comprobamos colisiones con las paredes para el jugador
        int playerCellX = static_cast<int>(newPlayerPosition.x) / cellSize;
        int playerCellY = static_cast<int>(newPlayerPosition.y) / cellSize;
        if (worldMaps[currentMapIndex][playerCellY][playerCellX] != 0)
            if (worldMaps[currentMapIndex][playerCellY][playerCellX] == 5)
            {
                // Si el jugador intenta moverse a una celda no permitida, no actualizamos su posición
                sprite.setColor(Color::Red);
            }

            else if (worldMaps[currentMapIndex][playerCellY][playerCellX] != 0)
            {

                newPlayerPosition = playerPosition;
            }

        playerPosition = newPlayerPosition;

        // Actualizamos la posición del enemigo persiguiendo al jugador
        enemy.update(playerPosition);
        enemy2.update(playerPosition);

        window.clear();
        // Dibujamos el mapa

        window.draw(fondo);

        for (int i = 0; i < mapHeight; ++i)
        {

            for (int j = 0; j < mapWidth; ++j)
            {

                RectangleShape cell(Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);
                switch (worldMaps[currentMapIndex][i][j])
                {
                case 1:
                    cell.setFillColor(Color(166, 145, 63)); // Pared
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
                    cell.setFillColor(Color(0, 0, 0, 0)); // Espacio vacío
                    break;
                }

                window.draw(cell);
            }
        }

        // Dibujamos al jugador y al enemigo

        sprite.setPosition(playerPosition);
        window.draw(sprite);
        enemy.draw(window);
        enemy2.draw(window);
        window.display();
    }
}

#endif