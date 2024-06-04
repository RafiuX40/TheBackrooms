#ifndef Info_hpp
#define Info_hpp

#include <SFML/Graphics.hpp>

using namespace sf;

void info()
{
    
    Font font;
    font.loadFromFile("Assets/Super Normal.ttf");
    
    Text title("THE BACKROOMS", font, 75);
    title.setFillColor(Color::White);
    title.setOutlineColor(Color::Black);
    title.setOutlineThickness(5);
    title.setPosition(25, 15);

    Text creditos("HISTORIA", font, 45);
    creditos.setFillColor(Color::Cyan);
    creditos.setOutlineColor(Color::Black);
    creditos.setOutlineThickness(5);
    creditos.setPosition(200, 105);

    Text name1("Eres una persona normal que tuvo la", font, 25);
    name1.setFillColor(Color::White);
    name1.setOutlineColor(Color::Black);
    name1.setOutlineThickness(5);
    name1.setPosition(55, 165);

    Text name2("Desfortuna de hacer noclip Cayendo a los ", font, 25);
    name2.setFillColor(Color::White);
    name2.setOutlineColor(Color::Black);
    name2.setOutlineThickness(5);
    name2.setPosition(35, 205);

    Text name3("The Backrooms", font, 25);
    name3.setFillColor(Color::Red);
    name3.setOutlineColor(Color::Black);
    name3.setOutlineThickness(5);
    name3.setPosition(200, 250);

    Text name4("CONTROLES", font, 25);
    name4.setFillColor(Color::Cyan);
    name4.setOutlineColor(Color::Black);
    name4.setOutlineThickness(5);
    name4.setPosition(230, 300);

    Text name5("WASD / Movimiento", font, 25);
    name5.setFillColor(Color::White);
    name5.setOutlineColor(Color::Black);
    name5.setOutlineThickness(5);
    name5.setPosition(180, 330);

    Text name6("Click izquierdo / Disparo", font, 25);
    name6.setFillColor(Color::White);
    name6.setOutlineColor(Color::Black);
    name6.setOutlineThickness(5);
    name6.setPosition(150, 380);

    RenderWindow window(VideoMode(600, 600), "Creditos");
    
    while (window.isOpen() && !Keyboard::isKeyPressed(Keyboard::BackSpace))
    {


        auto image = Image{};
    if (!image.loadFromFile("Assets/Logo.png"))
    {
        // Error handling...
    }

    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(title);
        window.draw(creditos);
        window.draw(name1);
        window.draw(name2);
        window.draw(name3);
        window.draw(name4);
        window.draw(name5);
        window.draw(name6);
        window.display();
    }
}

#endif