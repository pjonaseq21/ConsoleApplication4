#include "Resources.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

//klasa odpowiedzialna za przyciski załadowanie tła...
//na ten moment tutaj tworze przyciski
Resources::Resources(sf::Font& font) :sharedFont(font), menuButton(font, "Nowa Gra", { (float)desktop_Size.size.x / 2,(float)desktop_Size.size.y / 2 }, { 200.f, 50.f }), 
backgroundMainMenu(backgroundTexture), backgroundSimulation(simTexture), 
simEndButton(font, "Zrestartuj Gre", { (float)desktop_Size.size.x / 2,(float)desktop_Size.size.y / 2 }, { 150.f, 50.f }), endGameText(font){


    endGameText.setFont(sharedFont);
    endGameText.setCharacterSize(60);
    endGameText.setFillColor(sf::Color::White);
    endGameText.setOutlineColor(sf::Color::Black);
    endGameText.setOutlineThickness(3.0f);

    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        std::cerr << "BLAD: Nie udalo sie zaladowac tekstury!" << std::endl;
    }
    else {
        backgroundMainMenu.setTexture(backgroundTexture, true); //tło menu
      //  scaleSprite(backgroundTexture, backgroundMainMenu);
    }
    if (!simTexture.loadFromFile("assets/unnamed.png")) {
        std::cerr << "BLAD: Nie udalo sie zaladowac tekstury!" << std::endl;
    }
    else {
        backgroundSimulation.setTexture(simTexture, true); //tło
      //  scaleSprite(simTexture, backgroundSimulation);
    }
}



float Resources::randomNumber(float x1,float x2) {

    std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(x1, x2);
    return dist(mt);
}
void Resources::scaleSprite( sf::RenderWindow& window) {
    sf::Vector2u textureSize = simTexture.getSize();
    float scaleX = (float)window.getSize().x / textureSize.x;
    float scaleY = (float)window.getSize().y / textureSize.y;
    backgroundSimulation.setScale({ scaleX,scaleY });
    backgroundMainMenu.setScale({ scaleX,scaleY });
}

void Resources::simMenu(sf::RenderWindow& window) {
    float screenWidth = (float)desktop_Size.size.x;
    float screenHeight = (float)desktop_Size.size.y;
    Overlay.setSize({ screenWidth,screenHeight });
    Overlay.setFillColor(sf::Color(0, 0, 0, 100));
    window.draw(Overlay);
    simStopButtons.clear();
    float startY = screenHeight/2 + 100;
    std::vector<int> options = { 1, 2, 3 };
    for (int optionValue : options) {
        if (optionValue == 1) {
            label = "Restartuj";


        }
        else if (optionValue == 2) {
            label = L"Menu Główne";
        }
        else {
            label = L"Wróc do gry";

        }
        simStopButtons.emplace_back(sharedFont, label, sf::Vector2f{ screenWidth/2, startY }, sf::Vector2f{ 150.f, 50.f });
       
        startY -= 100.f;
    }
}

void Resources::endGamePanel(sf::RenderWindow& window,int winningFamily) {
    float screenWidth = (float)desktop_Size.size.x;
    float screenHeight = (float)desktop_Size.size.y;
    Overlay.setSize({ screenWidth,screenHeight });
    Overlay.setFillColor(sf::Color(0, 0, 0, 100));
    window.draw(Overlay);
    switch (winningFamily) {
    case 0: 
        endGameText.setString(L"wygrała rodzina żółtych");
        break;

    case 1:
        endGameText.setString(L"wygrala rodzina czerwonych");

        break;
    }
    endGameText.setPosition(sf::Vector2f((screenWidth/2)-250.f, (screenHeight/2  - 150.0f)));
    window.draw(endGameText);
}


void Resources::configPanel()
{
    float screenWidth = (float)desktop_Size.size.x;
    float screenHeight = (float)desktop_Size.size.y;
    float startX = screenWidth/2 +50;
   
    configButtons.clear();
    std::vector<int> options = { 1, 2};
    for (int optionValue : options) {
        if (optionValue > 1) {
            label = std::to_string(optionValue) + " osady";
        }
        else {
            label = std::to_string(optionValue) + " osada";
        }

        configButtons.emplace_back(sharedFont, label, sf::Vector2f{ startX, screenHeight/2 }, sf::Vector2f{ 100.f, 50.f });
        startX -= 150;
    }
  

}





 
    
   
    



