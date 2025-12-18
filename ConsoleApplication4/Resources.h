#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
class Resources
{
public:
    int numberOfSettlements = 1;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Texture simTexture;

    Resources();
    void configPanel();
    sf::Sprite backgroundMainMenu;
    sf::Sprite backgroundSimulation;
    Button menuButton;
    std::vector<Button*> configButtons;
    static float randomNumber(float x1, float x2);

};

