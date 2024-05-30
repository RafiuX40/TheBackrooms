#ifndef menu_hpp
#define menu_hpp

#include <SFML/Graphics.hpp>

using namespace sf;

#define MAX_NUMBER_OF_ITEMS 3


// Velocidad de los jugadores


class Menu // Clase menu principal
{
public:
    Menu(float w, float h);
    ~Menu();

    void draw(RenderWindow &window);
    void moveUp();
    void moveDown();
    int getPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    Font font;
    Text menu[MAX_NUMBER_OF_ITEMS];
};

#endif