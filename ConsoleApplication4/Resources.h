#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
class Resources
{
private:
    sf::Font& sharedFont;
public:

    sf::Texture backgroundTexture;
    sf::Texture simTexture;

    Resources(sf::Font& font);
    void configPanel();
    sf::Sprite backgroundMainMenu;
    sf::Sprite backgroundSimulation;
    Button menuButton;
    std::vector<Button*> configButtons;
    static float randomNumber(float x1, float x2);

};

