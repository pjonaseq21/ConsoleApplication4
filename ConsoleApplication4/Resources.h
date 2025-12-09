#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
class Resources
{
public:
    sf::Font font;
    sf::Texture backgroundTexture;
    Resources();
    sf::Sprite backgroundMainMenu;
    Button menuButton;
};

