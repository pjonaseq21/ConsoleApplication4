#include "Resources.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

//klasa odpowiedzialna za przyciski załadowanie tła...
//na ten moment tutaj tworze przyciski
Resources::Resources(sf::Font& font) :sharedFont(font), menuButton(font, "Nowa Gra", {750.f, 580.f}, {200.f, 50.f}), backgroundMainMenu(backgroundTexture), backgroundSimulation(simTexture) {


    if (!backgroundTexture.loadFromFile("assets/background.jpg")) {
        std::cerr << "BLAD: Nie udalo sie zaladowac tekstury!" << std::endl;
    }
    else {
        backgroundMainMenu.setTexture(backgroundTexture, true); //tło

    }
    if (!simTexture.loadFromFile("assets/Simulation_background.jpg")) {
        std::cerr << "BLAD: Nie udalo sie zaladowac tekstury!" << std::endl;
    }
    else {
        backgroundSimulation.setTexture(simTexture, true); //tło

    }
}



float Resources::randomNumber(float x1,float x2) {

    std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(x1, x2);
    return dist(mt);
}

void Resources::simMenu(sf::RenderWindow& window) {
    Overlay.setSize(sf::Vector2f{ 1920,900 });
    Overlay.setFillColor(sf::Color(0, 0, 0, 100));
    window.draw(Overlay);
    simStopButtons.clear();
    float startY = 580.f;
    std::vector<int> options = { 1, 2, 3 };
    for (int optionValue : options) {
        if (optionValue == 1) {
            label = "Restartuj";
        }
        else if (optionValue == 2) {
            label = "Menu Główne";
        }
        else {
            label = "Wróc do gry";
        }
        simStopButtons.emplace_back(sharedFont, label, sf::Vector2f{ 950.f, startY }, sf::Vector2f{ 100.f, 50.f });
       
        startY -= 100.f;
    }
}

void Resources::configPanel()
{
    float startX = 950.f;
   
    configButtons.clear();
    std::vector<int> options = { 1, 2};
    for (int optionValue : options) {
        if (optionValue > 1) {
            label = std::to_string(optionValue) + " osady";
        }
        else {
            label = std::to_string(optionValue) + " osada";
        }

        configButtons.emplace_back(sharedFont, label, sf::Vector2f{ startX, 580.f }, sf::Vector2f{ 100.f, 50.f });
        startX -= 200;
    }
  

}





 
    
   
    



