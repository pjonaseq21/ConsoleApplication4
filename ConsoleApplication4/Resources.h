#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
class Resources
{
private:
    sf::Font& sharedFont;
    std::string label;
public:
    sf::RectangleShape Overlay;
    sf::Texture backgroundTexture;
    sf::Texture simTexture;
    void simMenu(sf::RenderWindow& window);
    Resources(sf::Font& font);
    void configPanel();
    sf::Sprite backgroundMainMenu;
    sf::Sprite backgroundSimulation;
    Button menuButton;
    std::vector<Button> configButtons;
    std::vector<Button> simStopButtons;
    static float randomNumber(float x1, float x2);

};

