#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
class Resources
{
private:
    sf::Font& sharedFont;
    sf::String label;
    sf::VideoMode desktop_Size = sf::VideoMode::getDesktopMode();
public:
    void scaleSprite(sf::RenderWindow& window);
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

