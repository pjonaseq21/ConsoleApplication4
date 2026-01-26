#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
class Resources
{
private:
    sf::Font& sharedFont;
    sf::String label;
    sf::Text endGameText;
    sf::VideoMode desktop_Size = sf::VideoMode::getDesktopMode();
public:
    sf::Texture appleSpawnTexture;
    sf::Sprite appleSpawnSprite;
    sf::Texture speedUpTexture;
    sf::Sprite speedUpSprite;
    sf::Texture appleTexture;

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
    Button simEndButton;
    std::vector<Button> simStopButtons;
    void endGamePanel(sf::RenderWindow& window,int winningFamily);
    static float randomNumber(float x1, float x2);

};

