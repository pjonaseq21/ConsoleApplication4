#pragma once 
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Throngle.h"
enum class GameState {
    MENU,
    SIMULATION,
    CONFIG,
    GAME_OVER
};

class Game {
public:
    Game(); 
    void run(); 

private:
    void processEvents(); 
    void update(sf::Time dt);       
    void render();   
    GameState m_state;
    Resources m_resources;
    sf::RenderWindow window;
    Throngle throngle;
    float m_timer;
    
};