#include "Cabeceras/Game.hpp"
#include "Cabeceras/menu.hpp"

int main()
{
    RenderWindow window(VideoMode(screenWidth, screenHeight), "The Backrooms");

    auto image = sf::Image{};
    if (!image.loadFromFile("Asstes/Logo.png"))
    {
    // Error handling...
    }

    Texture background;
    background.loadFromFile("Asstes/Background.jfif");

    Sprite BackMenu;
    BackMenu.setTexture(background);

    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {

            case Event::KeyReleased:
                switch (event.key.code)
                {
                case Keyboard::Up:
                    menu.moveUp();
                    break;
                case Keyboard::Down:
                    menu.moveDown();
                    break;

                case Keyboard::Return:
                    switch (menu.getPressedItem())
                    {
                    case 0:
                        Game();
                        break;
                    case 1:
                        
                        break;
                    case 2:
                        window.close();
                    }

                    break;
                }

                break;
            case Event::Closed:
                window.close();
                break;
            }
        }

        window.clear();
        window.draw(BackMenu);
        menu.draw(window);
        window.display();
    }

    return 0;
}