#include <SFML/Audio.hpp>

#include "Cabeceras/Game.hpp"
#include "Cabeceras/menu.hpp"
#include "Cabeceras/Creditos.hpp"
#include "Cabeceras/Info.hpp"

int main()
{

    SoundBuffer buffer;
    if (!buffer.loadFromFile("Assets/Audios/Government-Funding.wav"))
    {
        // Error handling...
    }
    Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    Font font;
    font.loadFromFile("Assets/Super Normal.ttf");
    Text title("THE BACKROOMS", font, 75);
    title.setFillColor(Color::White);
    title.setOutlineColor(Color::Black);
    title.setOutlineThickness(5);
    title.setPosition(25, 15);

    RenderWindow window(VideoMode(screenWidth, screenHeight), "The Backrooms");

    auto image = Image{};
    if (!image.loadFromFile("Assets/Logo.png"))
    {
        // Error handling...
    }

    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    Texture background;
    background.loadFromFile("Assets/Background.jfif");

    Sprite BackMenu;
    BackMenu.setTexture(background);
    BackMenu.setScale(float(screenWidth) / background.getSize().x, float(screenHeight) / background.getSize().y);

    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape))
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
                        sound.stop();
                        Game();
                        currentMapIndex = 0;
                        sound.play();
                        break;
                    case 1:
                        Creditos();
                        break;
                    case 2:
                        info();
                        break;
                    case 3:
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
        window.draw(title);
        menu.draw(window);
        window.display();
    }

    return 0;
}