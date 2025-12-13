#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
class Resources
{
public:
    int numberOfSettlements = 1;
    sf::Font font;
    sf::Texture backgroundTexture;
    Resources();
    void configPanel();
    void backgroundSim();
    sf::Sprite backgroundMainMenu;
    sf::Sprite backgroundSimulation;
    Button menuButton;
    std::vector<Button*> configButtons;
};

