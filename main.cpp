#include <SFML/Graphics.hpp>
#include "map.hpp"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    CircleShape shape(10.f); // Reducí el tamaño del círculo para que sea más visible en la ventana pequeña
    shape.setFillColor(Color::Green);

    // Posición inicial del personaje
    Vector2f position(100.f, 100.f);
    float speed = 5.0f; // Velocidad de movimiento del personaje

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Movimiento del personaje
        if (Keyboard::isKeyPressed(Keyboard::Up))
            position.y -= speed;
        if (Keyboard::isKeyPressed(Keyboard::Down))
            position.y += speed;
        if (Keyboard::isKeyPressed(Keyboard::Left))
            position.x -= speed;
        if (Keyboard::isKeyPressed(Keyboard::Right))
            position.x += speed;

        // Limitar la posición del personaje para que no salga de la ventana
        if (position.x < 0)
            position.x = 0;
        if (position.y < 0)
            position.y = 0;
        if (position.x > window.getSize().x - shape.getRadius() * 2) // Resta el radio del círculo para ajustar el límite derecho
            position.x = window.getSize().x - shape.getRadius() * 2;
        if (position.y > window.getSize().y - shape.getRadius() * 2) // Resta el radio del círculo para ajustar el límite inferior
            position.y = window.getSize().y - shape.getRadius() * 2;

        // Establecer la posición del personaje
        shape.setPosition(position);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}