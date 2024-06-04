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
    creditos.setPosition(200, 105);

    Text name1("Hecho por:", font, 25);
    name1.setFillColor(Color::White);
    name1.setOutlineColor(Color::Black);
    name1.setOutlineThickness(5);
    name1.setPosition(230, 165);

    Text name2("Rafael de Jesus Ramos Chavez", font, 25);
    name2.setFillColor(Color::White);
    name2.setOutlineColor(Color::Black);
    name2.setOutlineThickness(5);
    name2.setPosition(120, 205);

    Text name3("Diego Enrique Garcia Alpizar", font, 25);
    name3.setFillColor(Color::White);
    name3.setOutlineColor(Color::Black);
    name3.setOutlineThickness(5);
    name3.setPosition(125, 255);

    Text name4("Basado en:", font, 25);
    name4.setFillColor(Color::White);
    name4.setOutlineColor(Color::Black);
    name4.setOutlineThickness(5);
    name4.setPosition(230, 300);

    Text name5("The Backrooms por Kane Pixels", font, 25);
    name5.setFillColor(Color::White);
    name5.setOutlineColor(Color::Black);
    name5.setOutlineThickness(5);
    name5.setPosition(110, 330);

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
        window.display();
    }

}

#endif