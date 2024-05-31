#ifndef Creditos_hpp
#define Creditos_hpp

#include <SFML/Graphics.hpp>

using namespace sf; 

void Creditos()
{
    Font font;
    font.loadFromFile("Assets/Super Normal.ttf");
    
    Text title("THE BACKROOMS", font, 75);
    title.setFillColor(Color::White);
    title.setOutlineColor(Color::Black);
    title.setOutlineThickness(5);
    title.setPosition(25, 15);

    Text creditos("CREDITOS", font, 45);
    creditos.setFillColor(Color::White);
    creditos.setOutlineColor(Color::Black);
    creditos.setOutlineThickness(5);
    creditos.setPosition(25, 55);

    Text name1("Hecho por:", font, 25);
    name1.setFillColor(Color::White);
    name1.setOutlineColor(Color::Black);
    name1.setOutlineThickness(5);
    name1.setPosition(25, 105);

    Text name2("Rafael de Jesus Ramos Chavez", font, 25);
    name2.setFillColor(Color::White);
    name2.setOutlineColor(Color::Black);
    name2.setOutlineThickness(5);
    name2.setPosition(25, 125);

    Text name3("Diego Enrique Garcia Alpizar", font, 25);
    name3.setFillColor(Color::White);
    name3.setOutlineColor(Color::Black);
    name3.setOutlineThickness(5);
    name3.setPosition(25, 15);

    RenderWindow window(VideoMode(600, 600), "Creditos");
    
    while (window.isOpen())
    {
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
        window.display();
    }

}

#endif