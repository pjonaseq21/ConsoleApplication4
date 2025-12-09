#include "Resources.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//klasa odpowiedzialna za przyciski załadowanie tła...
//na ten moment tutaj tworze przyciski
Resources::Resources():menuButton(font, "Nowa Gra", { 750.f, 580.f }), backgroundMainMenu(backgroundTexture){


    if (!backgroundTexture.loadFromFile("assets/background.jpg")) {
        std::cerr << "BLAD: Nie udalo sie zaladowac tekstury!" << std::endl;
    }
    else {
        backgroundMainMenu.setTexture(backgroundTexture, true); //tło

    }





 
    
   
    
}


