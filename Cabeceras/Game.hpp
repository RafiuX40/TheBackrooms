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
    bool hasPassedYellowTile = false;
    bool gamePaused = false;
    bool gameWon = false;

    SoundBuffer buffer;
    if (!buffer.loadFromFile("Assets/Audios/The-Complex.wav"))
    {
        // Error handling...
    }
    Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    SoundBuffer shot;
    if (!shot.loadFromFile("Assets/Audios/Shot.wav"))
    {
        // Error handling...
    }
    Sound shoting;
    shoting.setBuffer(shot);

    RenderWindow window(VideoMode(screenWidth, screenHeight), "The Backrooms");
    window.setFramerateLimit(60);

    auto image = sf::Image{};
    if (!image.loadFromFile("Assets/Logo.png"))
    {
        // Error handling...
    }

    Font font;
    font.loadFromFile("Assets/Super Normal.ttf");

    Text winText("YOU WON", font, 50);
    winText.setFillColor(Color::Green);
    winText.setOutlineColor(Color::Black);
    winText.setOutlineThickness(5);
    winText.setPosition(screenWidth / 2 - winText.getLocalBounds().width / 2, screenHeight / 2 - winText.getLocalBounds().height / 2);

    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    Texture textura;
    textura.loadFromFile("Assets/Player/Player-stop.png");

    Texture walkTexture1;
    walkTexture1.loadFromFile("Assets/Player/Walk-1.png");

    Texture walkTexture2;
    walkTexture2.loadFromFile("Assets/Player/Walk-2.png");

    vector<Texture> playerWalkTextures = {walkTexture1, walkTexture2}; // Vector de texturas de la animación

    int currentWalkFrame = 0; // Índice de la textura actual de la animación
    bool isWalking = false;   // Estado de la animación

    Sprite sprite;
    sprite.setTexture(textura);
    sprite.setOrigin(16, 13);

    Texture arma;
    arma.loadFromFile("Assets/pistol.png");

    Sprite gun;
    gun.setTexture(arma);

    Texture background;
    background.loadFromFile("Assets/pixilart-drawing.png");

    Sprite fondo;
    fondo.setTexture(background);

    Vector2f playerPosition(100.f, 100.f);
    float playerSpeed = 3.0f;
    float playerHealth = 500.0f;

    Enemy enemy(Vector2f(500.f, 500.f), 2.5f); // Creamos un enemigo en una posición y velocidad específicas
    Enemy enemy2(Vector2f(500.f, 500.f), 2.5f);

    vector<CircleShape> bullets;
    vector<float> angles;
    Clock c;
    Clock s;

    while (window.isOpen() && !Keyboard::isKeyPressed(Keyboard::BackSpace) && !gameWon)
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

        if (Mouse::isButtonPressed(Mouse::Left) && c.getElapsedTime().asSeconds() > 0.5)
        {
            bullets.push_back(CircleShape());
            bullets.back().setRadius(5);
            bullets.back().setPosition(sprite.getPosition());
            angles.push_back(atan2(Mouse::getPosition(window).y - sprite.getPosition().y, Mouse::getPosition(window).x - sprite.getPosition().x));
            shoting.play();
            c.restart();
        }

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
            do
            {
                randomX2 = rand() % screenWidth;
            } while (randomX2 == randomX);

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

        if (worldMaps[currentMapIndex][playerCellY][playerCellX] == 4)
        {
            if (!hasPassedYellowTile)
            {
                // Si el jugador no ha tocado ningún cuadro amarillo, reiniciamos su posición
                newPlayerPosition = playerPosition;
            }
            else
            {
                // Si el jugador ha tocado al menos un cuadro amarillo, cambiamos el color del sprite
                sprite.setColor(Color::Green);
            }
        }

        // Verificamos colisiones con los cuadros amarillos (case 5) y actualizamos hasPassedYellowTile si es necesario
        if (worldMaps[currentMapIndex][playerCellY][playerCellX] == 4)
        {
            hasPassedYellowTile = true;
        }
        else if (worldMaps[currentMapIndex][playerCellY][playerCellX] == 3)
        {
            // Si el jugador toca un cuadro verde antes de los amarillos, reiniciamos su posición
            if (!hasPassedYellowTile)
            {
                newPlayerPosition = playerPosition;
            }
            else
            {
                // Si el jugador ha pasado por los cuadros amarillos y toca el cuadro verde, muestra el texto "YOU WON" y pausa el juego
                gamePaused = true;
            }
        }

        if (worldMaps[currentMapIndex][playerCellY][playerCellX] == 1)
        {
            // Si el jugador colisiona con una pared, reiniciamos su posición
            newPlayerPosition = playerPosition;
        }
        else if (worldMaps[currentMapIndex][playerCellY][playerCellX] == 3)
        {
            // Si el jugador intenta tocar un cuadro verde antes de los amarillos, reiniciamos su posición
            if (!hasPassedYellowTile)
            {
                newPlayerPosition = playerPosition;
            }
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
                    cell.setFillColor(Color::Green); // Ganar
                    break;
                case 4:
                    cell.setFillColor(Color::Yellow); // Llave
                    break;
                case 5:
                    cell.setFillColor(Color::Cyan); // Shotgun
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
        for (int i = 0; i < bullets.size(); i++)
        {
            window.draw(bullets[i]);
            bullets[i].move(5 * cos(angles[i]), 5 * sin(angles[i]));

            // Verificar colisiones con enemigos
            for (int i = 0; i < bullets.size(); i++)
            {
                if (bullets[i].getGlobalBounds().intersects(enemy.getGlobalBounds()))
                {
                    // Reducir la vida del enemigo
                    enemy.reduceHealth(10); // Por ejemplo, reduce la vida en 10 puntos
                    // Eliminar el proyectil
                    bullets.erase(bullets.begin() + i);
                    angles.erase(angles.begin() + i);
                    // Decrementar i para evitar errores al modificar el vector dentro del bucle
                    i--;
                    break; // Salir del bucle, ya que el proyectil solo puede golpear al enemigo una vez
                }
            }

            for (int i = 0; i < bullets.size(); i++)
            {
                bullets[i].move(5 * cos(angles[i]), 5 * sin(angles[i]));

                // Verificar colisiones con las paredes
                int bulletCellX = static_cast<int>(bullets[i].getPosition().x) / cellSize;
                int bulletCellY = static_cast<int>(bullets[i].getPosition().y) / cellSize;
                if (worldMaps[currentMapIndex][bulletCellY][bulletCellX] != 0)
                {
                    // Si la bala colisiona con una pared, eliminarla
                    bullets.erase(bullets.begin() + i);
                    angles.erase(angles.begin() + i);
                    i--; // Decrementar i para evitar errores al modificar el vector dentro del bucle
                }
            }

            for (int i = 0; i < bullets.size(); i++)
            {
                if (bullets[i].getGlobalBounds().intersects(enemy2.getGlobalBounds()))
                {
                    // Reducir la vida del enemigo
                    enemy2.reduceHealth(10); // Por ejemplo, reduce la vida en 10 puntos
                    // Eliminar el proyectil
                    bullets.erase(bullets.begin() + i);
                    angles.erase(angles.begin() + i);
                    // Decrementar i para evitar errores al modificar el vector dentro del bucle
                    i--;
                    break; // Salir del bucle, ya que el proyectil solo puede golpear al enemigo una vez
                }
            }
        }

        if (sprite.getGlobalBounds().intersects(enemy.getGlobalBounds()))
        {
            // Reducir la salud del jugador si hay colisión con enemy
            playerHealth -= 10; // Por ejemplo, reduce 10 puntos de salud
            if (playerHealth <= 0)
            {
                // El jugador ha perdido, puedes hacer lo que necesites aquí
                window.close(); // Por ejemplo, cerrar la ventana del juego
                currentMapIndex = 0;
            }

            if (sprite.getGlobalBounds().intersects(enemy2.getGlobalBounds()))
            {
                // Reducir la salud del jugador si hay colisión con enemy2
                playerHealth -= 10; // Por ejemplo, reduce 10 puntos de salud
                if (playerHealth <= 0)
                {
                    // El jugador ha perdido, puedes hacer lo que necesites aquí
                    window.close(); // Por ejemplo, cerrar la ventana del juego
                }
            }
        }

        Vector2i mousePosition = Mouse::getPosition(window);

        // Calcular el ángulo entre la posición del puntero y la posición del personaje
        float angle = atan2(mousePosition.y - sprite.getPosition().y, mousePosition.x - sprite.getPosition().x);
        angle = angle * 180 / 3.14159265; // Convertir el ángulo de radianes a grados

        // Rotar el sprite del personaje según ese ángulo
        gun.setRotation(angle);

        // Posición relativa del arma respecto al jugador
        float gunOffsetX = 3.0f; // Ajusta este valor para cambiar la posición horizontal del arma
        float gunOffsetY = 3.0f; // Ajusta este valor para cambiar la posición vertical del arma

        // Calculamos la posición del arma en relación con el jugador
        float gunPositionX = playerPosition.x + gunOffsetX;
        float gunPositionY = playerPosition.y + gunOffsetY;

        // Calculamos el ángulo entre el jugador y el puntero del ratón
        float angleToMouse = atan2(playerPosition.y - mousePosition.y, playerPosition.x - mousePosition.x);
        angleToMouse = angleToMouse * 180 / 3.14159265; // Convertimos el ángulo de radianes a grados

        // Ajustamos el ángulo para que el arma mire hacia el puntero del ratón desde el lado opuesto al jugador
        float gunRotation = angleToMouse + 180.0f; // Sumamos 180 grados para invertir el ángulo

        // Establecemos la posición y la rotación del arma
        gun.setPosition(gunPositionX, gunPositionY);
        gun.setRotation(gunRotation);

        // Dibujamos el arma
        window.draw(gun);
        enemy.draw(window);
        enemy2.draw(window);

        if (gamePaused)
        {
            window.draw(winText);
        }

        window.display();
    }

    if (gameWon)
    {
        window.draw(winText);
        window.display();
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                }
            }
        }
    }
}

#endif
