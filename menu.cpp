#include "Cabeceras/menu.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

Menu::Menu(float w, float h)
{
    if (!font.loadFromFile("Assets/Super Normal.ttf"))
    {
        // handle error
    }

    menu[0].setFont(font);
    menu[0].setFillColor(Color::Red);
    menu[0].setOutlineColor(Color::Black);
    menu[0].setOutlineThickness(5);
    menu[0].setString("PLAY");
    menu[0].setPosition(Vector2f(w/2-50, h / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(Color::White);
    menu[1].setOutlineColor(Color::Black);
    menu[1].setOutlineThickness(5);
    menu[1].setString("CREDITS");
    menu[1].setPosition(Vector2f(w/2-50, h / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(Color::White);
    menu[2].setOutlineColor(Color::Black);
    menu[2].setOutlineThickness(5);
    menu[2].setString("ABOUT");
    menu[2].setPosition(Vector2f(w/2-50, h / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    menu[3].setFont(font);
    menu[3].setFillColor(Color::White);
    menu[3].setOutlineColor(Color::Black);
    menu[3].setOutlineThickness(5);
    menu[3].setString("EXIT");
    menu[3].setPosition(Vector2f(w/2-50, h / (MAX_NUMBER_OF_ITEMS + 1) * 4));

    selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::draw(RenderWindow &window)
{

    

    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::moveUp()
{

    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(Color::Red);
    }
}

void Menu::moveDown()
{

    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(Color:: White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(Color:: Red);
    }
}