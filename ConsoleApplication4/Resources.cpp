#include "Resources.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//klasa odpowiedzialna za przyciski załadowanie tła...
//na ten moment tutaj tworze przyciski
Resources::Resources() :menuButton(font, "Nowa Gra", { 750.f, 580.f }, { 200.f, 50.f }), backgroundMainMenu(backgroundTexture), backgroundSimulation(backgroundTexture) {


    if (!backgroundTexture.loadFromFile("assets/background.jpg")) {
        std::cerr << "BLAD: Nie udalo sie zaladowac tekstury!" << std::endl;
    }
    else {
        backgroundMainMenu.setTexture(backgroundTexture, true); //tło

    }
}

void Resources::backgroundSim() {
    if (!backgroundTexture.loadFromFile("assets/Simulation_background.jpg")) {
        std::cerr << "BLAD: Nie udalo sie zaladowac tekstury!" << std::endl;
    }

}

void Resources::configPanel()
{
    float startX = 950.f;
   
    for (auto btn: configButtons) {
        delete btn;
    }
    std::vector<int> options = { 1,2,3 };
    std::string label;
    for (int optionValue : options) {
        if (optionValue > 1) {
            label = std::to_string(optionValue) + " osady";
        }
        else {
            label = std::to_string(optionValue) + " osada";
        }

        Button* newBtn = new Button(font, label, { startX, 580.f }, { 100.f, 50.f });
        configButtons.push_back(newBtn);
        startX -= 200;
    }
  

}





 
    
   
    



